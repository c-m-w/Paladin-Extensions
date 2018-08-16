<?php
	require '../../include.php';

	session_start( );

	BanUser( $_SESSION[ "user_id" ] );
	return;
?>