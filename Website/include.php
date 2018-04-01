<?php
	// This file should be placed a directory upward of the website.
	// TODO: Logging include file.
	// TODO: Encrypting and decrypting and generating encryption keys, ivs and post identifiers.
	// TODO: Check loader hash.
	
	define("ReturnKeys",
		array( "Invalid Hash"			=> "-1",
		"Establishing Failure" 			=> "0", // Couldn't connect / set up database info
        "Banned" 						=> "1", // banned login attempt
        "Identity Mismatch" 			=> "2", // secret_key / unique_id mismatch
        "Inactive Premium" 				=> "3", // premium time exceeded
        "Staff Success" 				=> "8", // staff member logged in
        "Success" 						=> "9" ) );
	
	define( "SQL", array( "ServerName" => "localhost", "DatabaseUsername" => "palatfef_admin", "DatabasePassword" => "", "DatabaseName" => "palatfef_xenforo" ) );
	$sql_connection = new mysqli( SQL[ "ServerName" ], SQL[ "DatabaseUsername" ], SQL[ "DatabasePassword" ], SQL[ "DatabaseName" ] );
	
	function GenerateKeys( )
	{
		$time = microtime(false);
		$time = substr($time, 11, strlen($time) - 11);
		$time = floor($time / 10);
		$keys[ "iv" ] = substr(md5($time), 0, 16);
		$keys[ "enc_key" ] = $keys[ "iv " ] . $keys[ "iv" ];
		return $keys;
	}
	
	define( "Keys", GenerateKeys( ) );
	
	function GenerateIdentifier( $plain_text ) // Anything indexing the $_POST global needs to be one of these identifiers.
	{
		return substr( md5( md5( global Keys[ "iv" ] ) . md5( $plain_text) ), 4, 14); // Start and finish can be random, as long as they match the client
	}
	
	define( "EncryptionMethod", "AES-256-CBC" );
	
	function Encrypt( $plain_text )
	{
		return openssl_encrypt( $plain_text, EncryptionMethod, Keys[ "enc_key" ], 0, Keys[ "iv" ] ); // Base64 encode then encrypt.
	}
	
	function Decrypt( $cipher_text )
	{
		return openssl_decrypt( $cipher_text, EncryptionMethod, Keys[ "enc_key" ], 0, Keys[ "iv" ] ); // Base64 decode then decrypt.
	}
	
	define( "UnsafeKeywords", array( " drop ", " delete " ) ); // TODO: Add all unsafe keywords.
	
	function SanitizeInput( $userinfo )
	{
		foreach( $userinfo as $info )
		{
			$info = global $sql_connection->real_escape_string( strip_tags( trim( $info ) ) ) );
			str_replace( global UnsafeKeywords, "", $info );
			$returninfo[ ] = $info;
		}
		return $returninfo;
	}
	
	function BeginSession( $enckey, $iv )
	{
		session_start( );
		$_SESSION[ "enc_key" ] = $enckey;
		$_SESSION[ "iv" ] = $iv;
	}
	
	define( "ExtensionDirectory", "../Extensions/" );
	define( "GameID", array( "CS: GO" => 2, "PUBG" => 3 ) );
	define( "GameInfo", array( 2 => ExtensionDirectory . "csgo.info", 3 => ExtensionDirectory . "pubg.info" ) );
	define( "GameCheat", array( 2=> ExtensionDirectory . "csgo.dll", 3 => ExtensionDirectory . "pubg.dll" ) );
	
	function CompileCheat( $game_id )
	{
		// -o 'output file' 'file to compile'
		exec( "g++ -o ".GameCheat[ $game_id ]." **FILE TO COMPILE**" );
	}
	
	function SendCheat( $game_id )
	{
		session_start( );
		if( $_SESSION[ "logged_in" ] == TRUE )
			echo openssl_encrypt( file_get_contents( global GameCheat[ $game_id ] ), global EncryptionMethod, $_SESSION[ "enc_key" ], 0, $_SESSION[ "iv" ] );
		else
			echo global ReturnKeys[ "Establishing Failure" ];
	}
	
	function SendInformation( $game_id )
	{
		session_start( );
		if( $_SESSION[ "logged_in" ] == TRUE )
			echo openssl_encrypt( file_get_contents( global GameInfo[ $game_id ] ), global EncryptionMethod, $_SESSION[ "enc_key" ], 0, $_SESSION[ "iv" ] );
		else
			echo global ReturnKeys[ "Establishing Failure" ];
		session_destroy( );
	}
?>