# GTA IV: The Lost and Damned - what the Tab-toggled six-name list is

Research notes for the LoadoutTabFix repo. Compiled by Claude (Anthropic) on 8 Nov 2026 from community guides, wikis and forum posts, then updated on 25 Nov 2026 with the game's own help text, seen while playing the start of TLAD. Nothing was checked against the game's files.

## Bottom line

The list is TLAD's built-in crew **toughness** display, and Tab is its official PC key. This is now confirmed by the game itself: early in TLAD a help box says "At any time during a job press TAB to view how battle hardened the Lost gang members with you are," and the post-job tutorial says the panel shows "how fight hardened your Lost gang members are." The list is only available during missions; outside one the key does nothing. The console button is unconfirmed.

## Short version

- **What it is:** the crew toughness panel, top-left of the screen, one bar per Lost member on the job with you. The game's tutorial says so directly (see "Confirmed in game" below).
- **The key:** Tab on PC, as stated by the game's own help prompt. It only works during a mission (a "job"); free roaming, the key does nothing. It is still absent from the controls menu and `ControlMap.dat`, so it can't be rebound in game. The console button is unconfirmed.
- **Why those six names:** they are the six named Lost members who ride with Johnny at the start of the DLC (the welcome-home party in "Clean and Serene"). The tutorial says the panel covers "the Lost gang members with you," so it fills its slots with the current crew.

## Confirmed in game (25 Nov 2026)

Seen on the PC version at the start of TLAD:

- **The Tab prompt.** While riding with the club, a help box reads: "At any time during a job press TAB to view how battle hardened the Lost gang members with you are." So Tab is the intended key, and only during a job.
- **Missions only.** The list toggles only while a mission is active. The opening of the DLC is a mission, which is why it worked during the first rides with the club. The panel also appears on its own at the end of a mission. Free roaming Liberty City, the key (F6 with this plugin) does nothing.
- **The tutorial after the first job.** Back at the clubhouse the panel pops up on its own with three help boxes in turn:
  1. "The details displayed above the radar show how fight hardened your Lost gang members are. This is represented by the colored bar next to their names."
  2. "Gang members get harder each time they complete a job with you. They will become more effective in gun battles."
  3. "If they die on a job they will be replaced by a new Lost gang member."
- **The bars are toughness, not health.** The tutorial names the stat ("fight hardened") and says it grows per completed job. That settles the health-vs-toughness question and makes Game Informer's and MobyGames' "health bars" a loose description.
- **New gains show in a second color.** In the post-job panel each bar has a white part followed by a teal part. During the job (on Tab) the bars were white only. The teal part is the toughness earned on that job. Billy's and Jim's teal parts were longer than the other four.
- **Six slots at the start.** The same six names (Billy, Jim, Terry, Clay, Brian, Jason) appear both during the first job and in the post-job tutorial, with Billy highest and Brian and Jason among the lowest.
- **The panel pops up automatically after a job**, which matches the community reports of bars appearing top-left after missions.

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

- **What toughness does mechanically.** The game says only that tougher members "become more effective in gun battles." Grand Theft Wiki's Backup page says increased toughness gives more health and better accuracy, which would explain why reviewers called them health bars. Not checked in game.
- **Why Billy, Brian and Jason appear.** They are not in the Gang War pool, and Brian and Jason leave the story early, so they are probably shown only because they are in the current crew. The unequal starting values (Billy highest, Brian and Jason lowest) look like preset per-character values.
- **Why Tab is not in the controls menu.** The game confirms Tab is the key but doesn't list it. GTA IV had a multiplayer scoreboard; on console it shares D-pad Down with radar zoom, and on PC it was most likely a fixed key. The crew list probably reuses that hard-coded input, which fits the game polling the key directly through DirectInput and `GetKeyboardState`.
- **Why Stats > Player shows no crew rows early in the DLC.** Those rows probably appear only once Terry and Clay become backup characters. Guides place that anywhere from "Hit the Pipe" to "Liberty City Choppers"; none says exactly when the rows appear.

## Gemini's claim, checked

Gemini said Tab (PC) or D-pad Down (console) shows the names, health bars and battle toughness of the active crew.

- **Confirmed:** Tab on PC shows the crew's names and toughness ("battle hardened" in the game's own prompt).
- **Wrong:** the bars are not health bars. The game's tutorial describes them as how fight hardened each member is.
- **Unconfirmed:** D-pad Down on console.
- **The cited sources:** the YouTube video (CT253fozLus) is titled "GTA IV Episodes from Liberty City" and its description says it shows codes and cheats, so it is not a source for a HUD toggle (no transcript could be fetched). The Fandom "Characters in The Lost and Damned" snippets only cover bios and mission spans, with nothing about a HUD list. The claim looks like a plausible synthesis that its own citations do not back up.

## Settled

The earlier ranked explanations (toughness display, health display, leftover scoreboard) and the health-vs-toughness and post-mission tests are settled by the game's help text: it is the toughness display, it pops up after a job, and Tab toggles it during missions. Which members fill the slots later (Gang War crews, Brian and Jason leaving) is out of scope for this mod and wasn't pursued.

## Remaining in-game tests

1. **Match against Stats:** once Stats > Player shows Terry and Clay, compare their percentages with their bar lengths.
2. **Console button:** with an Xbox controller, press D-pad Down to see whether the list appears alongside radar zoom.
3. **Text keys (optional):** in OpenIV, search TLAD's text file (for example `TLAD/common/text/american.gxt`) for the help text above to find its label keys. Suggested, not verified.

## Caveats

- No Rockstar manual, PC controls document, GXT dump or decompiled script reference describing this toggle turned up. The Tab key is confirmed only by the in-game help text; D-pad Down is unconfirmed.
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
