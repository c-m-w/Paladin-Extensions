<?php
	require '../../include.php';

	if ( mysqli_connect_errno( ) || $sql_connection->connect_error )
		die( Encrypt( ReturnKeys[ "Establishing Failure" ] ) );

// Todo: xf_loader_atmp logging
// Todo: DLL Streaming
// Todo: DLL Compilation (separate website)
// Todo: Sanitize input

// Get info from database
// Info retrieved...
//	xf_user:				user_id ->	secondary_group_ids
//							user_id ->	is_banned
//							user_id ->	is_staff
//							user_id ->	secret_key
//	xf_user_upgrade_active:	user_id ->	end_date
//	xf_rm_resource:			title	->	current_version_id
//	xf_user_field_value:	user_id ->	field_value WHERE field_id = "unique_id"
//	xf_loader_atmp:			*

	$identifiers = array(
		"id"	=> GenerateIdentifier( "id" ),
		"sk"	=> GenerateIdentifier( "sk" ),
		"hw"	=> GenerateIdentifier( "hw" ),
		"hash"	=> GenerateIdentifier( "hash" ) );

	$user_id	= SanitizeInput( Decrypt( $_POST[ $identifiers[ "id" ] ] ) );
	$secret_key	= SanitizeInput( Decrypt( $_POST[ $identifiers[ "sk" ] ] ) );
	$hardware	= json_decode( Decrypt( $_POST[ $identifiers[ "hw" ] ] ), true );

	if ( !ValidUser( $user_id, $secret_key ) )
		die( Encrypt( ReturnKeys[ "Establishing Failure" ] ) );

	if ( $is_banned )
		die( PutLoginAttempt( $user_id, 0, $hardware, ReturnKeys[ "Banned" ] ) );

	 $unique_id = GetUniqueID( $user_id );
	if ( $unique_id == 0 || $hardware === NULL )
		die( PutLoginAttempt( $user_id, $unique_id, $hardware, ReturnKeys[ "Hardware Mismatch" ] ) );

	if ( !ValidateHardware( $unique_id, $user_id, $hardware ) )
		die( PutLoginAttempt( $user_id, $unique_id, $hardware, ReturnKeys[ "Hardware Mismatch" ] ) );

	BeginSession( $user_id );
	die( PutLoginAttempt( $user_id, $unique_id, $hardware, $is_staff
		? ReturnKeys[ "Staff Success" ]
		: ReturnKeys[ "Success" ], $secondary_group_ids ) );
?>