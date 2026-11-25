// LoadoutTabFix.asi v2 - swaps two keys in what the GAME sees, leaving other
// plugins (Liberty Loadout etc.) on the real keys.
//
// Default: game sees F6 as Tab and Tab as F6. Covers every way the game could
// read the keyboard, and logs which one it actually uses:
//   1. DirectInput 8 keyboard devices, ANSI and Unicode interfaces
//   2. GetAsyncKeyState / GetKeyState / GetKeyboardState called from GTAIV.exe
//   3. WM_KEYDOWN/UP messages on the game's window thread
// 32-bit, loaded by an ASI loader. Config: LoadoutTabFix.ini beside the .asi.

#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <dinput.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>

typedef HRESULT (WINAPI *DI8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
typedef HRESULT (STDMETHODCALLTYPE *GetDeviceState_t)(void*, DWORD, LPVOID);
typedef HRESULT (STDMETHODCALLTYPE *GetDeviceData_t)(void*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);

static int  g_vkA = VK_TAB, g_vkB = VK_F6;
static BYTE g_dikA = 0x0F, g_dikB = 0x40;
static char g_logPath[MAX_PATH];
static bool g_logEnabled = true;
static HMODULE g_self = nullptr;
static volatile LONG c_diState[2], c_diData[2], c_gaks, c_gks, c_gkbs, c_msgKey, c_msgInput, c_swaps;

static void Log(const char* fmt, ...) {
    if (!g_logEnabled) return;
    FILE* f = fopen(g_logPath, "a"); if (!f) return;
    va_list ap; va_start(ap, fmt); vfprintf(f, fmt, ap); va_end(ap);
    fputc('\n', f); fclose(f);
}
static inline int MapVk(int vk) { return vk == g_vkA ? g_vkB : (vk == g_vkB ? g_vkA : vk); }
static void CallerName(void* addr, char* out, size_t n) {
    HMODULE m = nullptr; out[0] = 0;
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)addr, &m) && m) {
        char p[MAX_PATH]; GetModuleFileNameA(m, p, MAX_PATH);
        const char* s = strrchr(p, '\\'); snprintf(out, n, "%s", s ? s + 1 : p);
    }
}

// ---------------------------------------------------------------- DirectInput
static void* g_cache[2][48]; static int g_cacheN[2][2]; // [iface][isKb] counts (kb list 0..15, notkb 16..47)
static GetDeviceState_t g_origState[2] = {};
static GetDeviceData_t  g_origData[2]  = {};

static bool IsKb(int w, void* dev) {
    void** kb = &g_cache[w][0]; void** nk = &g_cache[w][16];
    for (int i = 0; i < g_cacheN[w][0]; i++) if (kb[i] == dev) return true;
    for (int i = 0; i < g_cacheN[w][1]; i++) if (nk[i] == dev) return false;
    bool isKb = false;
    if (w == 0) { DIDEVICEINSTANCEA di; ZeroMemory(&di, sizeof(di)); di.dwSize = sizeof(di);
        if (SUCCEEDED(((IDirectInputDevice8A*)dev)->GetDeviceInfo(&di))) isKb = ((di.dwDevType & 0xFF) == DI8DEVTYPE_KEYBOARD); }
    else        { DIDEVICEINSTANCEW di; ZeroMemory(&di, sizeof(di)); di.dwSize = sizeof(di);
        if (SUCCEEDED(((IDirectInputDevice8W*)dev)->GetDeviceInfo(&di))) isKb = ((di.dwDevType & 0xFF) == DI8DEVTYPE_KEYBOARD); }
    if (isKb) { if (g_cacheN[w][0] < 16) kb[g_cacheN[w][0]++] = dev; Log("DirectInput keyboard device found (%s interface)", w ? "Unicode" : "ANSI"); }
    else      { if (g_cacheN[w][1] < 32) nk[g_cacheN[w][1]++] = dev; }
    return isKb;
}
template<int W> static HRESULT STDMETHODCALLTYPE HookState(void* self, DWORD cb, LPVOID data) {
    HRESULT hr = g_origState[W](self, cb, data);
    if (SUCCEEDED(hr) && cb == 256 && data && IsKb(W, self)) {
        if (InterlockedIncrement(&c_diState[W]) == 1) Log("GAME READS KEYBOARD VIA DirectInput GetDeviceState (%s)", W ? "Unicode" : "ANSI");
        BYTE* k = (BYTE*)data; BYTE t = k[g_dikA]; k[g_dikA] = k[g_dikB]; k[g_dikB] = t;
        if ((k[g_dikA] | k[g_dikB]) & 0x80) if (InterlockedIncrement(&c_swaps) <= 10) Log("DI state swap applied");
    }
    return hr;
}
template<int W> static HRESULT STDMETHODCALLTYPE HookData(void* self, DWORD cb, LPDIDEVICEOBJECTDATA d, LPDWORD n, DWORD fl) {
    HRESULT hr = g_origData[W](self, cb, d, n, fl);
    if (SUCCEEDED(hr) && d && n && cb == sizeof(DIDEVICEOBJECTDATA) && IsKb(W, self)) {
        if (InterlockedIncrement(&c_diData[W]) == 1) Log("GAME READS KEYBOARD VIA DirectInput GetDeviceData (%s)", W ? "Unicode" : "ANSI");
        for (DWORD i = 0; i < *n; i++) {
            if (d[i].dwOfs == g_dikA)      { d[i].dwOfs = g_dikB; if (InterlockedIncrement(&c_swaps) <= 10) Log("DI buffered swap A->B"); }
            else if (d[i].dwOfs == g_dikB) { d[i].dwOfs = g_dikA; if (InterlockedIncrement(&c_swaps) <= 10) Log("DI buffered swap B->A"); }
        }
    }
    return hr;
}
static bool PatchSlot(void** vtbl, int idx, void* hook, void** orig) {
    DWORD old; if (!VirtualProtect(&vtbl[idx], sizeof(void*), PAGE_READWRITE, &old)) return false;
    *orig = vtbl[idx]; vtbl[idx] = hook; VirtualProtect(&vtbl[idx], sizeof(void*), old, &old); return true;
}
static void HookDirectInput() {
    HMODULE di = LoadLibraryA("dinput8.dll");
    DI8Create_t create = di ? (DI8Create_t)GetProcAddress(di, "DirectInput8Create") : nullptr;
    if (!create) { Log("DI: DirectInput8Create not available"); return; }
    for (int w = 0; w < 2; w++) {
        void* iface = nullptr;
        HRESULT hr = create(GetModuleHandleA(nullptr), DIRECTINPUT_VERSION, w ? IID_IDirectInput8W : IID_IDirectInput8A, &iface, nullptr);
        if (FAILED(hr) || !iface) { Log("DI(%s): create failed 0x%08lX", w ? "W" : "A", hr); continue; }
        void* dev = nullptr;
        if (w == 0) hr = ((IDirectInput8A*)iface)->CreateDevice(GUID_SysKeyboard, (IDirectInputDevice8A**)&dev, nullptr);
        else        hr = ((IDirectInput8W*)iface)->CreateDevice(GUID_SysKeyboard, (IDirectInputDevice8W**)&dev, nullptr);
        if (FAILED(hr) || !dev) { Log("DI(%s): CreateDevice failed 0x%08lX", w ? "W" : "A", hr); continue; }
        void** vt = *(void***)dev;
        bool a = w ? PatchSlot(vt, 9, (void*)HookState<1>, (void**)&g_origState[1]) : PatchSlot(vt, 9, (void*)HookState<0>, (void**)&g_origState[0]);
        bool b = w ? PatchSlot(vt, 10,(void*)HookData<1>,  (void**)&g_origData[1])  : PatchSlot(vt, 10,(void*)HookData<0>,  (void**)&g_origData[0]);
        Log("DI(%s) hooks: state=%d data=%d", w ? "Unicode" : "ANSI", a, b);
    }
}

// ------------------------------------------------------- Win32 API (exe IAT)
static SHORT (WINAPI *o_GetAsyncKeyState)(int) = nullptr;
static SHORT (WINAPI *o_GetKeyState)(int) = nullptr;
static BOOL  (WINAPI *o_GetKeyboardState)(PBYTE) = nullptr;
static void NoteCall(const char* api, int vk, void* ret, volatile LONG* ctr) {
    if (vk == g_vkA || vk == g_vkB) {
        LONG n = InterlockedIncrement(ctr);
        if (n <= 3) { char c[MAX_PATH]; CallerName(ret, c, sizeof(c)); Log("GAME CALLS %s(vk=%d) from %s (swap active)", api, vk, c); }
    }
}
static SHORT WINAPI H_GetAsyncKeyState(int vk) { NoteCall("GetAsyncKeyState", vk, __builtin_return_address(0), &c_gaks); return o_GetAsyncKeyState(MapVk(vk)); }
static SHORT WINAPI H_GetKeyState(int vk)      { NoteCall("GetKeyState", vk, __builtin_return_address(0), &c_gks);      return o_GetKeyState(MapVk(vk)); }
static BOOL  WINAPI H_GetKeyboardState(PBYTE k) {
    BOOL r = o_GetKeyboardState(k);
    if (r && k) { if (InterlockedIncrement(&c_gkbs) == 1) Log("GAME CALLS GetKeyboardState (swap active)"); BYTE t = k[g_vkA]; k[g_vkA] = k[g_vkB]; k[g_vkB] = t; }
    return r;
}
static int PatchIAT(HMODULE mod, const char* dll, const char* fn, void* hook, void** orig) {
    BYTE* base = (BYTE*)mod; auto dos = (PIMAGE_DOS_HEADER)base; if (dos->e_magic != IMAGE_DOS_SIGNATURE) return 0;
    auto nt = (PIMAGE_NT_HEADERS)(base + dos->e_lfanew);
    auto dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]; if (!dir.VirtualAddress) return 0;
    int patched = 0;
    for (auto d = (PIMAGE_IMPORT_DESCRIPTOR)(base + dir.VirtualAddress); d->Name; d++) {
        if (_stricmp((const char*)(base + d->Name), dll) != 0) continue;
        auto nameThunk = (PIMAGE_THUNK_DATA)(base + (d->OriginalFirstThunk ? d->OriginalFirstThunk : d->FirstThunk));
        auto addrThunk = (PIMAGE_THUNK_DATA)(base + d->FirstThunk);
        for (; nameThunk->u1.AddressOfData; nameThunk++, addrThunk++) {
            if (nameThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) continue;
            auto ibn = (PIMAGE_IMPORT_BY_NAME)(base + nameThunk->u1.AddressOfData);
            if (strcmp((const char*)ibn->Name, fn) != 0) continue;
            DWORD old; if (!VirtualProtect(&addrThunk->u1.Function, sizeof(void*), PAGE_READWRITE, &old)) continue;
            if (!*orig) *orig = (void*)addrThunk->u1.Function;
            addrThunk->u1.Function = (DWORD)hook;
            VirtualProtect(&addrThunk->u1.Function, sizeof(void*), old, &old); patched++;
        }
    }
    return patched;
}
static void HookWinApi() {
    HMODULE exe = GetModuleHandleA(nullptr);
    int a = PatchIAT(exe, "USER32.dll", "GetAsyncKeyState", (void*)H_GetAsyncKeyState, (void**)&o_GetAsyncKeyState);
    int b = PatchIAT(exe, "USER32.dll", "GetKeyState",      (void*)H_GetKeyState,      (void**)&o_GetKeyState);
    int c = PatchIAT(exe, "USER32.dll", "GetKeyboardState", (void*)H_GetKeyboardState, (void**)&o_GetKeyboardState);
    Log("exe IAT patched: GetAsyncKeyState=%d GetKeyState=%d GetKeyboardState=%d", a, b, c);
}

// ------------------------------------------------------ window messages hook
static LRESULT CALLBACK MsgProc(int code, WPARAM w, LPARAM l) {
    if (code >= 0 && l) {
        MSG* m = (MSG*)l;
        if (m->message == WM_KEYDOWN || m->message == WM_KEYUP || m->message == WM_SYSKEYDOWN || m->message == WM_SYSKEYUP) {
            int nv = MapVk((int)m->wParam);
            if (nv != (int)m->wParam) {
                if (InterlockedIncrement(&c_msgKey) <= 3) Log("GAME RECEIVES key messages for vk=%d (swap active)", (int)m->wParam);
                m->wParam = (WPARAM)nv;
                UINT sc = MapVirtualKeyA((UINT)nv, MAPVK_VK_TO_VSC);
                m->lParam = (LPARAM)(((DWORD)m->lParam & ~(0x1FFu << 16)) | (sc << 16));
            }
        } else if (m->message == WM_INPUT) {
            if (InterlockedIncrement(&c_msgInput) == 1) Log("note: game window receives WM_INPUT (raw input) messages");
        }
    }
    return CallNextHookEx(nullptr, code, w, l);
}
struct FindCtx { DWORD pid; DWORD tid; };
static BOOL CALLBACK EnumProc(HWND h, LPARAM p) {
    FindCtx* c = (FindCtx*)p; DWORD pid = 0; DWORD tid = GetWindowThreadProcessId(h, &pid);
    if (pid == c->pid && IsWindowVisible(h) && !GetWindow(h, GW_OWNER)) { c->tid = tid; return FALSE; }
    return TRUE;
}
static void HookMessages() {
    FindCtx c = { GetCurrentProcessId(), 0 };
    for (int i = 0; i < 240 && !c.tid; i++) { EnumWindows(EnumProc, (LPARAM)&c); if (!c.tid) Sleep(500); }
    if (!c.tid) { Log("messages: game window not found"); return; }
    HHOOK h = SetWindowsHookExA(WH_GETMESSAGE, MsgProc, g_self, c.tid);
    Log("message hook on thread %lu: %s", c.tid, h ? "installed" : "FAILED");
}

// ------------------------------------------------------------------- startup
static bool g_doDI = true, g_doApi = true, g_doMsg = true;
static DWORD WINAPI Worker(LPVOID) {
    Sleep(500);
    if (g_doApi) HookWinApi();
    if (g_doDI)  HookDirectInput();
    Sleep(60000);
    Log("after 60s: DI state A/W=%ld/%ld, DI data A/W=%ld/%ld, GetAsyncKeyState=%ld, GetKeyState=%ld, GetKeyboardState=%ld, key messages=%ld, WM_INPUT=%ld",
        c_diState[0], c_diState[1], c_diData[0], c_diData[1], c_gaks, c_gks, c_gkbs, c_msgKey, c_msgInput);
    return 0;
}
static DWORD WINAPI MsgWorker(LPVOID) { Sleep(1000); HookMessages(); return 0; }

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_self = mod; DisableThreadLibraryCalls(mod);
        char path[MAX_PATH]; GetModuleFileNameA(mod, path, MAX_PATH);
        char* dot = strrchr(path, '.'); if (dot) *dot = 0;
        char ini[MAX_PATH]; snprintf(ini, MAX_PATH, "%s.ini", path); snprintf(g_logPath, MAX_PATH, "%s.log", path);
        DeleteFileA(g_logPath);
        g_vkA = GetPrivateProfileIntA("Keys", "GameKey", VK_TAB, ini);
        g_vkB = GetPrivateProfileIntA("Keys", "NewKey", VK_F6, ini);
        g_logEnabled = GetPrivateProfileIntA("Misc", "Log", 1, ini) != 0;
        g_doDI  = GetPrivateProfileIntA("Hooks", "DirectInput", 1, ini) != 0;
        g_doApi = GetPrivateProfileIntA("Hooks", "WinApi", 1, ini) != 0;
        g_doMsg = GetPrivateProfileIntA("Hooks", "Messages", 1, ini) != 0;
        g_dikA = (BYTE)MapVirtualKeyA(g_vkA, MAPVK_VK_TO_VSC); g_dikB = (BYTE)MapVirtualKeyA(g_vkB, MAPVK_VK_TO_VSC);
        Log("LoadoutTabFix v2 loaded: GameKey vk=%d NewKey vk=%d (DirectInput=%d WinApi=%d Messages=%d)", g_vkA, g_vkB, g_doDI, g_doApi, g_doMsg);
        if (!g_dikA || !g_dikB || g_vkA == g_vkB) { Log("ERROR: invalid key configuration, plugin disabled"); return TRUE; }
        CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
        if (g_doMsg) CreateThread(nullptr, 0, MsgWorker, nullptr, 0, nullptr);
    }
    return TRUE;
}
