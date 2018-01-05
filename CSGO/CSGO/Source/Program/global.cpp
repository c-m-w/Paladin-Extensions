#include "../dllmain.h"

std::string strLog;

void LogDebugMsg( EDebugMessage dmType, char *szMessage, ... )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	if ( hConsole && hConsole != INVALID_HANDLE_VALUE )
	{
		std::cout << std::endl;
		switch ( dmType )
		{
			case SCS:
				SetConsoleTextAttribute( hConsole, 10 );
				std::cout << "[SCS] ";
				break;
			case WRN:
				SetConsoleTextAttribute( hConsole, 14 );
				std::cout << "[WRN] ";
				break;
			case ERR:
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << "[ERR] ";
				break;
			case LER:
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << "[LER] ";
				break;
			default:
				SetConsoleTextAttribute( hConsole, 15 );
				std::cout << "[DBG] ";
		}
		SetConsoleTextAttribute( hConsole, 7 );
		//Ideally we want to dynamically allocate this, might do later (for now, stick to a max of 2047 data characters)
		char chBuffer[2048] { '\0' };
		va_list vaList;
		va_start( vaList, szMessage );
		vsnprintf( chBuffer, sizeof chBuffer, szMessage, vaList );
		va_end( vaList );
		std::cout << chBuffer;
		strLog.append( chBuffer );
	}
}

// Look up errors here: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
void LogLastError( )
{
	DWORD dwError = GetLastError( );
	if ( !dwError )
	{
		DEBUG( LER, "No error" );
		return;
	}
	LPSTR lpstrError = nullptr;
	if ( !FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), LPSTR( &lpstrError ), 0, nullptr ) )
	{
		DEBUG( LER, "[0x%08lu] - Unable to retrieve error description", dwError );
	}
	else
	{
		DEBUG( LER, "[0x%08lu] - %s", dwError, lpstrError );
	}
	strLog.append( lpstrError );
	LocalFree( lpstrError );
}

bool angle_t::operator==( angle_t rhs )
{
	return flPitch == rhs.flPitch && flYaw == rhs.flYaw && flRoll == rhs.flRoll;
}

bool angle_t::operator!=( angle_t rhs )
{
	return !( *this == rhs );
}

angle_t angle_t::operator+( angle_t rhs )
{
	flPitch += rhs.flPitch;
	flYaw += rhs.flYaw;
	flRoll += rhs.flRoll;
	return *this;
}

angle_t angle_t::operator-( angle_t rhs )
{
	flPitch -= rhs.flPitch;
	flYaw -= rhs.flYaw;
	flRoll -= rhs.flRoll;
	return *this;
}

angle_t angle_t::operator*( float rhs )
{
	flPitch *= rhs;
	flYaw *= rhs;
	flRoll *= rhs;
	return *this;
}

angle_t angle_t::operator/( float rhs )
{
	flPitch /= rhs;
	flYaw /= rhs;
	flRoll /= rhs;
	return *this;
}

angle_t angle_t::operator+=( angle_t rhs )
{
	return *this + rhs;
}

angle_t angle_t::operator-=( angle_t rhs )
{
	return *this - rhs;
}

angle_t angle_t::operator/=( float rhs )
{
	return *this / rhs;
}

vector_t::vector_t( )
{
	flDeltaX = 0;
	flDeltaY = 0;
	flDeltaZ = 0;
}

angle_t angle_t::operator*=( float rhs )
{
	return *this * rhs;
}

vector_t::vector_t( coordinate_t corOrigin, coordinate_t corDestination )
{
	flDeltaX = corDestination.flX - corOrigin.flX;
	flDeltaY = corDestination.flY - corOrigin.flY;
	flDeltaZ = corDestination.flZ - corOrigin.flZ;
}

void Wait( unsigned long ulSleepTime )
{
	std::this_thread::sleep_for( std::chrono::milliseconds( ulSleepTime ) );
}

moment GetMoment( )
{
	return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
}
