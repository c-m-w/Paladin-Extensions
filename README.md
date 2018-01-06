# Paladin
- Thread Hijack Injector
- CSGO Internal/External

## INJECTOR TODO
##### Open
##### Jeremy
##### Mike
- Add multiple injection methods (MM, TH)
##### Hunter
##### John
##### Cole

## CSGO TODO
##### Open
- Encrypt Strings
- Polymorphic Junk Code
##### Jeremy
- Velocity Based Backtrack
- Aimbot
- Legit Antiaim
- Move Log to C:/ Drive
- Check for multiple instances
##### Mike
- Pattern Scanning
- Config
- Log file implementation
- Define User/HWID for yourself
##### Hunter
- Menu
- Define HWID for yourself
##### John
- Glow
- ClientCMD
- ClientCMDUnrestricted
- UserCMD
##### Cole
- Change all ints to longs, and rename it from iVar to lVar
- Refactor all variables to match conventions
   - address_t< CPlayer > aplr **SHOULD BE** plr
   - address_t< int > ai **SHOULD BE** i
- Check CPlayer variables that they work
- Stop copying of plrs - plrLocalPlayerCopy should just be plrLocalPlayer._My_val.xValue
- Check for modifying of ._My_val and replace it with a plr duplicate (._My_val is unmodifiable)
   - ._My_val is for reading
   - Copy plr for writing, then use Setplr functions
