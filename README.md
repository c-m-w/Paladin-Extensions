# Paladin
- Thread Hijack Injector
- CSGO Internal/External

## INJECTOR TODO
##### Open
##### Jeremy
##### Mike
- Add multiple injection methods [++]
##### Hunter
##### John
##### Cole

## CSGO TODO
##### Open
- Trace Ray (https://www.unknowncheats.me/forum/counterstrike-global-offensive/136361-external-ray-tracing-ray-aabb.html) [Engine]
##### Jeremy
- Finish Base [++]
- HWID [General]
- Check for multiple instances [General]
- Admin Check [General]
- Anticheat Check [General]
- Features [Engine ++]
- Everything else [++]
##### Mike
- Help finish Base [++]
- Cheat Threads [Main]
- Menu [Interface]
##### Hunter
- Menu [Interface]
##### John
- Features [Engine ++]
##### Cole

# Features:
- Combat
  - [ ] Aimbot
    - Attack Teammates [bool]
    - BSilent (new psilent idea i have, always does psilent even if out of fov) [bool]
	- Spotted Only vs Vis Check Only [bool]
	- Overaim [float]
	- Vertical Displacement [float]
    - Smoothness [int]
    - Hitbox/Bone [int/string to int]
    - Curve [float]
    - FOV/Crosshair [float&bool]
    - Timeout [int]
	- HP / Distance / FOV Priority  [int]
    - Backtrack [int]
  - [ ] Recoil Control
    - Only When Firing [bool]
    - Scale Pitch & Yaw [float]
    - Bullets to ignore [int]
    - Smoothness based on time to next shot [int]
    - Timeout [int]
  - [ ] Triggerbot
    - Delay (spotted) [int]
    - In Cross/Trace Ray [bool]
    - Max Bullet Count [int]
    - Post Burst [int]
    - Slow Trigger [bool]
  - [ ] Slow Aim
    - Factor [int]
    - Timeout [int]
- Awareness
  - [ ] Glow
    - RGBA [int]
    - Enemy Only [bool]
    - HP [bool]
    - Spotted Only [bool]
    - Weapons | Nades | Bomb [bool]
  - [ ] Chams
    - Flat White [bool]
    - RGBA [int]
    - Through Walls [bool]
	- HP [bool]
  - [ ] Hit Sound
    - Pitch & Duration [int]
    - Sound File [bool]
  - [ ] In Game Radar
    - Square mode [bool]
  - [ ] Less Flash
    - Alpha factor at < 255 [int]
  - [ ] Sonar
    - Pitch & Duration & Speed [int]
	- File & Speed [int]
    - Curve Factor [int]
	- Max Distance [int]
- Misc
  - [ ] Inventory Changer
    - Model (Knife & Glove) [string to int]
	- Skin [string to int]
	- Wear [string to float]
	- StatTrak [int]
	- Name [string]
	- Seed [int]
	- Shows in real inventory
  - [ ] FOV Changer
  - [ ] Viewmodel FOV Changer
  - [ ] Auto Pistol
  - [x] Auto Jump
    - Following Minimum Delay [int]
  - [ ] Edge Jump