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
- Rounding & Normalization
- Debug Class
- HWID Class
- Config
- Memory
- Global
##### Mike
- Finish Base
  - Restructure location for offsets & multiclassed functions in logical manner since they aren't required by all classes (e.g. rounding and clamping)
  - Class Inheritance in logical manner
  - Pattern Scanning + create area for offsets
- Web app for web interface with normal app(?)
- Call Reason Detatch
##### Hunter
- ImGui (+ debug tab for debug build)
##### John
- Find as many features as externally possible
##### Cole
- Help Mike with restructure and inheritance by basing off of his code

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
  - [ ] FOV Changer
  - [ ] Viewmodel FOV Changer
  - [ ] Auto Pistol
  - [ ] Auto Jump
    - Following Minimum Delay [int]
  - [ ] Edge Jump
