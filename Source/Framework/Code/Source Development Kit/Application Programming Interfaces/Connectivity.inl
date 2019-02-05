/// Connectivity.inl

#pragma once

template< typename _t > bool CConnectivity::SetConnectionParameter( CURLoption _Option, _t _Value )
{
	if ( hInstance == nullptr )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Attempted to set connection parameter without initializing cURL." ) );
		return false;
	}

	const auto _Code = curl_easy_setopt( hInstance, _Option, _Value );
	if ( _Code != CURLE_OK )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CONNECTIVITY, XOR( "Failed to set cURL parameter %i. Error code: %i." ), _Option, _Code );
		return false;
	}
	return true;
}
