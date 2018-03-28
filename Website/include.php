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
	
	function StartSession( $enckey, $iv )
	{
		session_start( );
		$_SESSION[ "enc_key" ] = $enckey;
		$_SESSION[ "iv" ] = $iv;
	}
	
	define( "ExtensionDirectory", "../Extensions/" );
	define( "GameID", array( "CS: GO" => 2, "PUBG" => 3 ) );
	define( "GameInfo", array( 2 => ExtensionDirectory . "csgo.info", 3 => ExtensionDirectory . "pubg.info" ) );
	define( "GameCheat", array( 2=> ExtensionDirectory . "csgo.dll", 3 => ExtensionDirectory . "pubg.dll" ) );
	
	define( "EncryptionMethod", "AES-256-CBC" );
	
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