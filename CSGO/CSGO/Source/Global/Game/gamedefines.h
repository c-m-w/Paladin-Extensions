#pragma once

#define FL_ONGROUND (1 << 0) // At rest / on the ground
#define FL_DUCKING (1 << 1) // Player FLAG -- Player is fully crouched
#define MAX_ANGLE_DELTA 22.f // Max angle delta per tick
#define ACTION_NONE 0b0 // -command
#define ACTION_PRESS 0b1 // +command
#define ACTION_TICK 0b10 // +command, tick, -command
#define ACTION_DEFAULT 0b100 // default command state
#define ENTITY_DISTANCE 0x10 // Distance between entities

#define MAX_SENSITIVITY 1000.f
#define MIN_SENSITIVITY 0.f
#define MAX_FLASHALPHA 255.f
#define MIN_FLASHALPHA 0.f
#define MAX_FIELDOFVIEW 180
#define MIN_FIELDOFVIEW 0
#define MAX_PITCH 89.f
#define MIN_PITCH (-89.f)
#define MAX_YAW 180.f
#define MIN_YAW (-180.f)
#define MAX_ROLL 50.f
#define MIN_ROLL 50.f
