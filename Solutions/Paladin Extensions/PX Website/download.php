<?php
require 'include.php';

session_start( );
if( !isset( $_SESSION[ "enc_key" ] ) || !isset( $_SESSION[ "iv" ] ) )
	die( ReturnKeys[ "Establishing Failure" ] );
else
{
	$game_id_id = CreateIdentifier( "ext" );
	$file_id = CreateIdentifier( "file" );
	$game_id = SanitizeInput( Decrypt( $_POST[ $game_id_id ] ) );
	$file = SanitizeInput( Decrypt( $_POST[ $file_id ] ) );
	
	if ( !$file )
	{
		CompileCheat( $game_id );
		SendCheat( $game_id );
	}
	else if ( $file == 1 )
		SendInformation( $game_id );
	else
	{
		session_destroy( );
		die( ReturnKeys[ "Establishing Failure" ] );
	}
}
?>