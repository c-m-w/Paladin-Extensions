<?php
    require 'include.php';

    session_start( );
    if( !isset( $_SESSION[ "key" ] ) || !isset( $_SESSION[ "iv" ] ) || !isset( $_SESSION[ "is_staff" ] ) )
    	die( ReturnKeys[ "Establishing Failure" ] );
    else
    {
    	$game_id = SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "ext" ) ] ) );
    	$send_info = SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "file" ) ] ) );
    	
    	if ( $send_info == 0 )
    		die( GetDLL( $game_id ) );
        die( GetInformation( $game_id ) );
    }
?>