# Paladin
- Thread Hijack Injector
- CSGO Internal/External

## INJECTOR TODO
##### Open
- Start
##### Jeremy
##### Mike
##### Hunter
##### John
##### Cole

## CSGO TODO
##### Open
##### Jeremy
- Finish Base
##### Mike
- Clean up Base
- Menu
- Config
##### Hunter
- Menu
##### John
##### Cole
- Clean up Base
  - Move all hInline declarations into cpp

# Features:
- Combat
  - [ ] Aimbot
    - Attack Teammates [bool]
    - BSilent (new psilent idea i have, always does psilent even if out of fov) [bool]
	- Spotted [bool]
	- Overaim [float]
	- Vertical Displacement [int]
    - Smoothness based on denominating factor [int]
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
  - [ ] Auto Jump
    - Following Minimum Delay [int]
  - [ ] Edge Jump