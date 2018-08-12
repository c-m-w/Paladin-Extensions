<?php
    require '../../include.php';

    session_start( );
    if( !isset( $_SESSION[ "key" ] ) || !isset( $_SESSION[ "iv" ] ) || !isset( $_SESSION[ "is_staff" ] ) || !isset( $_SESSION[ "user_id" ] ) )
    	return;

    $game_id = SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "ext" ) ] ) );
    $send_info = SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "file" ) ] ) );
    	
    if ( $send_info == 0 )
    	die( Encrypt( json_encode( array( "DLL" => GetDLL( $game_id ), "Functions" => json_decode( file_get_contents( "../../Extensions/functions.json" ), true ) ) ) ) );
    die( GetInformation( $game_id ) );
?>