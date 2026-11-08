# TLADListKey

A small ASI plugin for GTA IV Complete Edition that moves the game's **Tab** action (the TLAD biker/club member list) to a different key (**F6**), allowing other mods that use Tab (e.g. Liberty Loadout's weapon and radio wheels) to function properly.

## Why

In TLAD, Tab toggles an on-screen list of club members with a bar for each (top-left of the screen). Liberty Loadout also uses Tab (hold) for its weapon and radio wheels, so holding Tab to open a wheel also toggles the list. Hittle Tab again to toggle the off the list turns off the radio. Holding down Tab to turn the radio back on toggles the list back on, creating a vicious cycle. The game's Tab action isn't in the controls menu or `ControlMap.dat`, so it can't be rebound in game.

<img width="586" height="275" alt="20261107163518_1" src="https://github.com/user-attachments/assets/f60730e0-0dca-4999-bb3e-f55e60671876" />

### What the list is

Most likely TLAD's crew **toughness** display: one bar per Lost MC member (Billy, Jim, Terry, Clay, Brian, Jason at the start of the DLC). This is inferred from community guides, which describe toughness bars in the top-left of the screen and a toughness readout under Stats > Player. No official Rockstar or PC controls documentation mentions the Tab binding, so treat the key as a hard-coded input. Confirmed on the tested setup that the list is base game: it still appears on Tab with all mods and plugins disabled.

## How it works

The plugin swaps two keys (default: **Tab ↔ F6**) in what the *game* sees, and leaves everything else alone:

- Pressing **F6** looks like Tab to the game, so it toggles the biker list.
- Real **Tab** no longer reaches the game's own Tab action, but other plugins that read the keyboard through the Windows API still see it, so the wheels stay on Tab.

Findings from logging on the tested setup (Steam, Complete Edition, FusionFix):

- The game reads the keyboard through DirectInput 8 on the **Unicode** interface (`IDirectInputDevice8W`), using `GetDeviceState` and `GetDeviceData`.
- The game exe also calls `GetKeyboardState`.
- It does not use `GetAsyncKeyState`, `GetKeyState`, key window messages or `WM_INPUT` for this.

The plugin patches the DirectInput device vtables (ANSI and Unicode) and the exe's `GetKeyboardState` import. It does not modify any game files, and there is no game source code involved.

## Install

1. Put `TLADListKey.asi` and `TLADListKey.ini` in `GTAIV\plugins` (an ASI loader is required, as for FusionFix and similar mods).
2. Keep Liberty Loadout's `KeyboardWheelKey` and `RadioWheelKey` at `9` (Tab).
3. Launch the game. Press **F6** for the biker list; hold **Tab** for the wheels.

To uninstall, delete the `.asi` and `.ini`.

## Config (`TLADListKey.ini`)

| Key | Default | Meaning |
|---|---|---|
| `Keys/GameKey` | `9` | The key the game uses (Tab). Windows virtual-key code, decimal. |
| `Keys/NewKey` | `117` | The key you press instead (F6). Other examples: `118` F7, `20` Caps Lock, `71` G. |
| `Hooks/DirectInput` | `1` | Required on the tested setup. |
| `Hooks/WinApi` | `1` | Required on the tested setup (`GetKeyboardState`). |
| `Hooks/Messages` | `0` | Not needed on the tested setup. |
| `Misc/Log` | `0` | Set to `1` to write `TLADListKey.log` beside the plugin (useful for troubleshooting). |

## Troubleshooting

Set `Log=1`, restart, play for a minute, then check `TLADListKey.log`. Lines starting `GAME READS` or `GAME CALLS` show which input path the game is using, and the 60-second summary line gives call counts. If none fire after a game or FusionFix update, the game is reading input some other way and the hooks need updating.

## Build

32-bit (the game is 32-bit). With MinGW-w64 (`i686`):

```sh
i686-w64-mingw32-g++ -O2 -shared -static -static-libgcc -static-libstdc++ \
  -o TLADListKey.asi TLADListKey.cpp -ldinput8 -ldxguid -Wl,--kill-at
```

## Known limits

- The swap hides real Tab from the game entirely. If Tab does something else in a menu or minigame, that action now sits on F6.
- Controllers are unaffected.
- A game or FusionFix update could change how input is read; the log shows which path stopped firing.

## AI disclosure

This plugin, its source code, and this README were written by Claude (an AI model made by Anthropic) in conversation with the repository owner, who tested it in-game and supplied the logs used to debug it. It has been tested on one setup only, so review the code before relying on it.

## Status

Personal project, tested on one setup only (GTA IV Complete Edition via Steam, FusionFix, Liberty Loadout). Use at your own risk and back up before installing.
