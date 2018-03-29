<?php

require 'include.php';

if( $connection->connect_error )
	die( ReturnKeys[ "Establishing Failure" ] );

// Todo: xf_loader_atmp logging
// Todo: DLL Streaming
// Todo: DLL Compilation (separate website)
// Todo: Sanitize input

// Get info from database
// Info retrieved...
//  xf_user:                user_id ->    secondary_group_ids
//                          user_id ->    is_banned
//                          user_id ->    is_staff
//                          user_id ->    secret_key
//  xf_user_upgrade_active: user_id ->    end_date
//  xf_rm_resource:         title   ->    current_version_id
//  xf_user_field_value:    user_id ->    field_value WHERE field_id = "unique_id"
//  xf_loader_atmp:         *

$identifiers = array( "id" 		=> GenerateIdentifier( "id" ),
						"ext" 	=> GenerateIdentifier( "ext" ),
						"sk" 	=> GenerateIdentifier( "sk" ),
						"uid"	=> GenerateIdentifier( "uid" ) );
						

$sqlcommands    = array( "xf_user"
                                => 'SELECT secondary_group_ids, is_banned, is_staff, secret_key FROM xf_user WHERE user_id = "' . SanitizeInput( Decrypt( $_POST[ $identifiers[ "id" ] ] ) ) . '"',
                            "xf_user_upgrade_active"
                                => 'SELECT end_date FROM xf_user_upgrade_active WHERE user_id = "' . SanitizeInput( Decrypt( $_POST[ $identifiers[ "id" ] ] ) ) . '"',
                            "xf_rm_resource"
                                => 'SELECT current_version_id FROM xf_rm_resource WHERE title = "' . SanitizeInput( Decrypt( $_POST[ $identifiers[ "ext" ] ] ) ) . '"',
                            "xf_user_field_value"
                                => 'SELECT field_value FROM xf_user_field_value WHERE field_id = "unique_id", user_id = "' . SanitizeInput( Decrypt( $_POST[ $identifiers[ "id" ] ] ) ) . '"',
                            "xf_loader_atmp"
                                => 'SELECT * FROM xf_loader_atmp');
$results        = array( "xf_user"
                                => $sql_connection->query( $sqlcommands[ "xf_user" ] ),
                            "xf_user_upgrade_active"
                                => $sql_connection->query( $sqlcommands[ "xf_user_upgrade_active" ] ),
                            "xf_rm_resource"
                                => $sql_connection->query( $sqlcommands[ "xf_rm_resource" ] ),
                            "xf_user_field_value"
                                => $sql_connection->query( $sqlcommands[ "xf_user_field_value" ] ),
                            "xf_loader_atmp"
                                => $sql_connection->query( $sqlcommands[ "xf_loader_atmp" ] ) );

if ( $results[ "xf_user" ]->connect_error ||
        $results[ "xf_user_upgrade_active" ]->connect_error ||
        $results[ "xf_rm_resource" ]->connect_error ||
        $results[ "xf_user_field_value" ]->connect_error ||
        $results[ "xf_loader_atmp" ]->connect_error )
    die( ReturnKeys[ "Establishing Failure" ] );

if ( $results[ "xf_user" ]->num_rows > 0 &&
        $results[ "xf_user_upgrade_active" ]->num_rows > 0 &&
        $results[ "xf_rm_resource" ]->num_rows > 0 &&
        $results[ "xf_user_field_value" ]->num_rows > 0 &&
        $results[ "xf_loader_atmp" ]->num_rows > 0 )
{
    $rows       = array( "xf_user"
                              => $results[ "xf_user" ]->fetch_assoc( ),
                          "xf_user_upgrade_active"
                              => $results[ "xf_user_upgrade_active" ]->fetch_assoc( ),
                          "xf_rm_resource"
                              => $results[ "xf_rm_resource" ]->fetch_assoc( ),
                          "xf_user_field_value"
                              => $results[ "xf_user_field_value" ]->fetch_assoc( ),
                          "xf_loader_atmp"
                              => $results[ "xf_loader_atmp" ]->fetch_assoc( ) );

    if ( $rows[ "xf_user" ][ "is_banned" ] == 1 )
        die( ReturnKeys[ "Banned" ] );

    if ( $rows[ "xf_user" ][ "secondary_group_ids" ] == 5 &&
            ( $rows[ "xf_user_upgrade_active" ][ "end_date" ] > time( ) ||
                $rows[ "xf_user_upgrade_active" ][ "end_date" ] == 0 ) )
    {
        if ( $rows[ "xf_user" ][ "secret_key" ] == SanitizeInput( Decrypt( $_POST[ $identifiers[ "sk" ] ] ) ) )
        {
            if ( $rows[ "xf_user_field_value" ][ "field_value" ] == SanitizeInput( Decrypt( $_POST[ $identifiers[ "uid" ] ] ) ) )
            {
				StartSession( );
                if ( $rows[ "xf_user" ][ "is_staff" ] == 1 ) // if ( SanitizeInput( Decrypt( $_POST[ "dll" ] ) ) )
                    die( ReturnKeys[ "Staff Success" ] ); // { send = compile_dll( SanitizeInput( Decrypt( $_POST[ "ext" ] ) ) ); }
                die( ReturnKeys[ "Success" ] );
            }
            die( ReturnKeys[ "Identity Mismatch" ] );
        }
        die( ReturnKeys[ "Identity Mismatch" ] );
    }
    die( ReturnKeys[ "Inactive Premium" ] );
}
die( ReturnKeys[ "Establishing Failure" ] );

?>
