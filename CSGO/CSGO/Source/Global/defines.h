#pragma once

#define PI 3.141593f
#define MILLISECONDS_PER_SECOND 1000.f

#define PREMIUM_USERS unsigned __int8(55)
#define MESSAGE( Title, Text, Type ) MessageBox( nullptr, Text, Title, (Type) | MB_OK )
#define DECEMBER_FIRST moment(1512086400000) // time since epoch in milliseconds to december first 2017
#define DAY moment(8640000) // day in milliseconds
