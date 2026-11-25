# GTA IV: The Lost and Damned - what the Tab-toggled six-name list is

Research notes for the LoadoutTabFix repo. Compiled by Claude (Anthropic) on 8 Nov 2026 from community guides, wikis and forum posts. None of this was checked against the game's files, so the inferences are inferences.

## Bottom line

The list is almost certainly TLAD's built-in crew **toughness** display: a base-game HUD panel in the top-left corner showing one grey bar per Lost MC member. Players usually see it pop up after missions and Gang Wars. Confidence is moderate to high (about 75%). No located source documents a Tab binding for it, explains why it shows Billy, Jim, Terry, Clay, Brian and Jason, or confirms Gemini's "health bars and battle toughness" wording. Those parts are inference.

## Short version

- **What it is:** players describe a six-slot toughness display with bars in the top-left of the screen. A TrueAchievements guide says that after completing the mission, the increase in toughness shows on bars in the top-left. A GTAForums player described "six full bars on the toughness display." Static, unequal fills that were identical in a firefight and a calm ride fit a stored stat better than live health.
- **Why those six names:** they are the six named Lost members who ride with Johnny at the start of the DLC (the welcome-home party in "Clean and Serene"). The display seems to fill its six slots with whoever is in Johnny's crew. Later the slots hold the Gang War crew (Terry, Clay, Jim plus three generic bikers). Inference.
- **Input and Gemini's claim:** no source says which button shows the list. On consoles, D-pad Down is radar zoom (and the multiplayer scoreboard), so it is plausible but unverified. On PC, Tab is probably a hard-coded scoreboard-style key, which would explain why it is not in the controls menu or `ControlMap.dat`. Gemini's cited YouTube video is a cheat-codes video and does not support the claim. MobyGames' remark that the members' health bars are shown on screen is the closest real source.

## Confirmed facts (sourced)

- **Toughness is an official TLAD stat.** The GTA Wiki (Fandom) page says it is new in The Lost and Damned and is basically the combat skill level of the fellow members who travel with Johnny: Jim Fitzgerald, Clay Simons and Terry Thorpe. Terry's weapons go from Automatic Pistol to Micro-SMG to assault rifle to M4A1; Clay's go from Pump Shotgun to Sawn-off to Combat Shotgun to Assault Shotgun. At 100%, Terry has a Carbine Rifle and a Micro Uzi, Clay has an Assault Shotgun and Molotov Cocktails, and Jim has an Assault Rifle. Generic brothers who die are replaced by a new member and have their toughness reset.
- **Toughness is shown as bars in the top-left.** On the TrueAchievements "Full Chat" page, user Gamechamp3000 writes that after completing the mission the increase in toughness shows on bars in the top-left of the screen, and the achievement unlocks once the bars are filled. A snippet of Hydro_PT's GameFAQs PC achievement guide says that after a Gang War the game displays how tough Terry and Clay are.
- **The display has six bars.** A GTAForums user (Grievous, 2013) wrote that with three generic bikers (Tug, Bruce, Pat) plus Terry, Clay and Jim all maxed out, there were "six full bars on the toughness display." That matches the six slots seen in the game.
- **Toughness also appears in the pause menu.** PlayStationTrophies.org says to press Start, go to Stats, and under Player the names and toughness levels appear. Guides disagree on when Terry and Clay can first be called: PlayStationTrophies.org says from "Liberty City Choppers", a TrueAchievements commenter says after "Hit the Pipe."
- **Growth rates.** A PlayStationTrophies.org trophy guide (DudeInDistress, Apr 14, 2010) says that without grinding, toughness is about 60% by the final mission. It says there are 25 Gang Wars, each adding 2-4% to Terry and Clay, plus about 1% per minute of driving, and estimates the trophy pops between Gang Wars 11 and 13. XboxAchievements and GTAForums guides give +12% if they start a mission with the player, +8% if called in during one, and +4% per Gang War.
- **The six names match the opening crew.** GTA4.net's walkthrough of "Clean and Serene" says Billy is greeted at the hospital by Jimmy, Brian, Terry, Jason, Clay and Johnny. Fandom's The Lost MC page lists roles: Billy Grey, president; Jim Fitzgerald, treasurer; Brian Jeremy, secretary; Clay Simons, road captain; Terry Thorpe, sergeant-at-arms; Jason Michaels, enforcer.
- **The Gang War crew is different.** Fandom and Grand Theft Wiki say Clay, Terry and Jim (until "Was It Worth It?") plus three non-story bikers assist in Gang Wars, drawn from 24 non-storyline members. When one dies the next takes his place; if all die the list resets. Completing a Gang War earns money and raises the toughness of surviving Lost MC members.
- **Press descriptions mention crew bars.** MobyGames: "Their health bars are also shown on the screen." Game Informer says bikers who survive gunfights become hardened soldiers with much larger health bars. These are loose descriptions, but they show reviewers saw per-member bars and tied them to health and survivability.
- **Default GTA IV controls.** Radar Zoom is T on PC and D-pad Down on 360/PS3 (GTA Wiki, Controls for GTA IV). StrategyWiki labels the same control "Radar zoom / Show scoreboard (in multiplayer)." No source maps Tab to anything in single-player.

## Inference (not confirmed by any source)

- **The bars show toughness, not live health.** The strongest evidence is the in-game observation: identical fills during a firefight and a calm ride, with a different value per member. Toughness probably scales each member's maximum health and accuracy (Grand Theft Wiki, Backup page: increased toughness gives more health and better accuracy), which would explain why reviewers called them health bars.
- **Why Billy, Brian and Jason appear.** They are not in the Gang War pool, and Brian and Jason leave the story early, so they are probably shown only because they are in the current crew. The unequal starting values (Billy highest, Brian and Jason lowest) look like preset per-character values. Brian and Jason should disappear later, with the slots switching to Terry, Clay, Jim and the generic bikers.
- **Why Tab is not in the controls menu.** GTA IV had a multiplayer scoreboard. On console it shares D-pad Down with radar zoom; on PC it was most likely a fixed key. The crew list probably reuses that hard-coded input, which fits the game polling the key directly through DirectInput and `GetKeyboardState`.
- **Why Stats > Player shows no crew rows early in the DLC.** Those rows probably appear only once Terry and Clay become backup characters. Guides place that anywhere from "Hit the Pipe" to "Liberty City Choppers"; none says exactly when the rows appear.

## Gemini's claim, checked

Gemini said Tab (PC) or D-pad Down (console) shows the names, health bars and battle toughness of the active crew.

- **Partly supported:** a crew list with per-member bars exists (TrueAchievements, GTAForums, MobyGames), and linking it to toughness is supported by community guides.
- **Not supported:** no located source says Tab on PC or D-pad Down on console. The "health bars" wording is only partly right: MobyGames and Game Informer call them health bars, but the static readings point to toughness.
- **The cited sources:** the YouTube video (CT253fozLus) is titled "GTA IV Episodes from Liberty City" and its description says it shows codes and cheats, so it is not a source for a HUD toggle (no transcript could be fetched). The Fandom "Characters in The Lost and Damned" snippets only cover bios and mission spans, with nothing about a HUD list. The claim looks like a plausible synthesis that its own citations do not back up.

## Ranked explanations

1. **Crew toughness display (most likely, about 75%).** The same panel that pops up after missions and Gang Wars, toggled manually on PC with a hard-coded Tab key. The bars are stored toughness.
2. **Crew health display (about 15%).** The bars show current health relative to a toughness-scaled maximum. Less likely given the identical readings, unless nobody was damaged in either screenshot.
3. **Leftover multiplayer scoreboard or debug panel showing crew data (about 10%).** The GTA IV scoreboard component repurposed in single-player.

## In-game tests to confirm

1. **Health or toughness:** during a ride, let an ally get clipped by traffic or a stray hit, then press Tab right away. A bar that drops and recovers means health; a bar that does not move means toughness.
2. **Update after a mission:** note the bars, finish "Clean and Serene" or the next mission, and check whether the same panel pops up on its own and whether any bar grows.
3. **Match against Stats:** once Stats > Player shows Terry and Clay, compare their percentages with their bar lengths.
4. **Roster change:** after Jason and Brian leave, and in the first Gang War (available after the 9th mission, "Coming Down", per a PSNProfiles trophy guide, no link saved), check whether the names switch to generic bikers.
5. **Console button:** with an Xbox controller, press D-pad Down, and also try T on the keyboard, to see whether the list appears alongside radar zoom.
6. **Text keys (optional):** in OpenIV, search TLAD's text file (for example `TLAD/common/text/american.gxt`) for "TOUGH" or the member names to find the HUD label keys. Suggested, not verified.

## Caveats

- No Rockstar manual, PC controls document, GXT dump or decompiled script reference describing this toggle or its key turned up. The Tab and D-pad Down mappings are unconfirmed.
- The six-bar and top-left descriptions come from community posts, not official documentation. Growth percentages vary between guides (2-4% versus a flat 4% per Gang War).
- MobyGames' and Game Informer's health-bar wording is reviewer description, not a technical spec.
- The Hydro_PT GameFAQs quote is a fragment from a search snippet; GameFAQs blocked fetching the full guide.

## Sources

- GTA Wiki (Fandom): Toughness - https://gta.fandom.com/wiki/Toughness
- TrueAchievements: TLAD Full Chat achievement - https://www.trueachievements.com/a61934/tlad-full-chat-achievement
- GameFAQs: TLAD PC achievement guide (Hydro_PT) - https://gamefaqs.gamespot.com/pc/987736-grand-theft-auto-iv-the-lost-and-damned/faqs/60475
- GTAForums: Replaying The Lost and Damned today, after GTAV - https://gtaforums.com/topic/602657-replaying-the-lost-and-damned-today-after-gtav/
- PlayStationTrophies: TLAD Full Chat trophy - https://www.playstationtrophies.org/game/grand-theft-auto-iv/trophy/14886-tlad-full-chat.html
- PlayStationTrophies: TLAD DLC road map and trophy guide - https://www.playstationtrophies.org/forum/topic/41592-grand-theft-auto-iv-the-lost-and-damned-dlc-road-map-and-trophy-guide/
- XboxAchievements: TLAD Full Chat achievement - https://www.xboxachievements.com/game/grand-theft-auto-iv/achievement/23945-tlad-full-chat.html
- XboxAchievements forum: Clay/Terry Toughness? - https://www.xboxachievements.com/forum/topic/113221-clayterry-toughness/
- GTAForums: The Lost and Damned FAQ - https://gtaforums.com/topic/398974-the-lost-and-damned-faq/
- GTA Wiki (Fandom): The Lost MC - https://gta.fandom.com/wiki/The_Lost_MC
- GTA Wiki (Fandom): Characters in TLAD - https://gta.fandom.com/wiki/Characters_in_TLAD
- GTA Wiki (Fandom): Gang Wars in TLAD - https://gta.fandom.com/wiki/Gang_Wars_in_TLAD
- Grand Theft Wiki: Gang Warfare in The Lost and Damned - https://www.grandtheftwiki.com/Gang_Warfare_in_The_Lost_and_Damned
- Grand Theft Wiki: Backup - https://www.grandtheftwiki.com/Backup
- GTA4.net: The Lost and Damned missions walkthrough - https://www.gta4.net/lost-and-damned/missions.php
- MobyGames: The Lost and Damned - https://www.mobygames.com/game/39360/grand-theft-auto-iv-the-lost-and-damned/
- Game Informer: The Lost and Damned review - https://gameinformer.com/games/grand_theft_auto_iv_the_lost__damned/b/xbox360/archive/2009/09/22/review
- GTA Wiki (Fandom): Controls for GTA IV - https://gta.fandom.com/wiki/Controls_for_GTA_IV
- StrategyWiki: Grand Theft Auto IV / Controls - https://strategywiki.org/wiki/Grand_Theft_Auto_IV/Controls
- YouTube: GTA IV Episodes from Liberty City (cited by Gemini) - https://www.youtube.com/watch?v=CT253fozLus
