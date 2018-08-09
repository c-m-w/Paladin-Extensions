<?php
	require 'include.php';

    if( !isset( $_POST[ GenerateIdentifier( "client" ) ] ) )
        return;

    $user = GetUserFromIP( );

    if( $user === false )
        return;

    die( base64_encode( json_encode( $user ) ) );
?>