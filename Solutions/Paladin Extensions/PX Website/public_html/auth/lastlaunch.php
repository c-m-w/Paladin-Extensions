<?php
    require '../../include.php';

    session_start( );
    if( !isset( $_SESSION[ "key" ] ) || !isset( $_SESSION[ "iv" ] ) || !isset( $_SESSION[ "is_staff" ] ) || !isset( $_SESSION[ "user_id" ] ) )
    	return;

    die( Encrypt( json_encode( GetLastLaunchTime( SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "ext" ) ] ) ) ) ) ) );
?>