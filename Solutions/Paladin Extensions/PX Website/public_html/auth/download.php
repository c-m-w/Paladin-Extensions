<?php
    require '../../include.php';

    session_start( );
    if( !isset( $_SESSION[ "key" ] ) || !isset( $_SESSION[ "iv" ] ) || !isset( $_SESSION[ "is_staff" ] ) || !isset( $_SESSION[ "user_id" ] ) )
    	return;

    $extension_id = SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "ext" ) ] ) );
    $send_info = SanitizeInput( Decrypt( $_POST[ GenerateIdentifier( "file" ) ] ) );

    // somehow requested an extension without the proper permissions, most likely memory editing the manager.
    if( strpos( $_SESSION[ "secondary_group_ids" ], $extension_id ) === FALSE )
        return;
    	
    if ( $send_info == 0 )
    	die( Encrypt( json_encode( array( "DLL" => GetDLL( $extension_id ), "Functions" => json_decode( file_get_contents( "../../Extensions/functions.json" ), true ) ) ) ) );
    die( GetInformation( $extension_id ) );
?>