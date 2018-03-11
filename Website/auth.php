<?php

// Todo: xf_loader_atmp logging
// Todo: DLL Streaming
// Todo: DLL Compilation (separate website)

// Error keys
$return_keys 		= array( "Establishing Failure" => 0, // Couldn't connect / set up database info
								"Banned" => 1, // banned login attempt
								"Identity Mismatch" => 2, // secret_key / unique_id mismatch
								"Inactive Premium" => 3, // premium time exceeded
								"Staff Success" => 8, // staff member logged in
								"Success" => 9 );

// Access database as XenForo
$server_name		= "localhost";
$database_username	= "palatfef_admin";
$database_password	= "_paladin_ext()++";
$database_name		= "palatfef_xenforo";
$sql_connection	 	= new mysqli( $server_name, $database_username, $database_password, $database_name );

// Get info from database
// Info retrieved...
//	xf_user:				user_id	->	secondary_group_ids
//							user_id ->	is_banned
//							user_id	->	is_staff
//							user_id	->	secret_key
//	xf_user_upgrade_active:	user_id	->	end_date
//	xf_rm_resource:			title	->	current_version_id
//	xf_user_field_value:	user_id	->	field_value WHERE field_id = "unique_id"
//	xf_loader_atmp:			*

$sqlcommands		= array( "xf_user"
									=> 'SELECT secondary_group_ids, is_banned, is_staff, secret_key FROM xf_user WHERE user_id = "' . $_POST[ "id" ] . '"',
								"xf_user_upgrade_active"
									=> 'SELECT end_date FROM xf_user_upgrade_active WHERE user_id = "' . $_POST[ "id" ] . '"',
								"xf_rm_resource"
									=> 'SELECT current_version_id FROM xf_rm_resource WHERE title = "' . $_POST[ "ext" ] . '"',
								"xf_user_field_value"
									=> 'SELECT field_value FROM xf_user_field_value WHERE field_id = "unique_id", user_id = "' . $_POST[ "id" ] . '"',
								"xf_loader_atmp"
									=> 'SELECT * FROM xf_loader_atmp');
$results			= array( "xf_user"
									=> $sql_connection->query( $sqlcommands[ "xf_user" ] ),
								"xf_user_upgrade_active"
									=> $sql_connection->query( $sqlcommands[ "xf_user_upgrade_active" ] ),
								"xf_rm_resource"
									=> $sql_connection->query( $sqlcommands[ "xf_rm_resource" ] ),
								"xf_user_field_value"
									=> $sql_connection->query( $sqlcommands[ "xf_user_field_value" ] ),
								"xf_loader_atmp"
									=> $sql_connection->query( $sqlcommands[ "xf_loader_atmp" ] ) );

if ( $results[ "xf_user" ]->connect_error OR
		$results[ "xf_user_upgrade_active" ]->connect_error OR
		$results[ "xf_rm_resource" ]->connect_error OR
		$results[ "xf_user_field_value" ]->connect_error OR
		$results[ "xf_loader_atmp" ]->connect_error )
	die( $return_keys[ "Establishing Failure" ] );

if ( $results[ "xf_user" ]->num_rows > 0 AND
		$results[ "xf_user_upgrade_active" ]->num_rows > 0 AND
		$results[ "xf_rm_resource" ]->num_rows > 0 AND
		$results[ "xf_user_field_value" ]->num_rows > 0 AND
		$results[ "xf_loader_atmp" ]->num_rows > 0 )
{
    $rows			= array( "xf_user"
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
		die( $return_keys[ "Banned" ] );

    if ( $rows[ "xf_user" ][ "secondary_group_ids" ] == 5 AND
			( $rows[ "xf_user_upgrade_active" ][ "end_date" ] > time( ) OR
				$rows[ "xf_user_upgrade_active" ][ "end_date" ] == 0 ) )
    {
        if ( $rows[ "xf_user" ][ "secret_key" ] == $_POST[ "sk" ] )
        {
            if ( $rows[ "xf_user_field_value" ][ "field_value" ] == $_POST[ "uid" ] )
            {
                if ( $rows[ "xf_user" ][ "is_staff" ] == 1 ) // if ( $_POST[ "dll" ] )
                    die( $return_keys[ "Staff Success" ] ); // { send = compile_dll( $_POST[ "ext" ] ); }
				die( $return_keys[ "Success" ] );
            }
			die( $return_keys[ "Identity Mismatch" ] );
        }
		die( $return_keys[ "Identity Mismatch" ] );
    }
	die( $return_keys[ "Inactive Premium" ] );
}
die( $return_keys[ "Establishing Failure" ] );

?>
