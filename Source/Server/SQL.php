<?php
	require 'public_html/src/config.php';

	class SQLConnection
	{
		private $sqlConnection;

		function __construct( )
		{
			$sqlConnection = new mysqli( $config[ 'db' ][ 'host' ], $config[ 'db' ][ 'username' ], $config[ 'db' ][ 'password' ], $config[ 'db' ][ 'dbname' ] )
		}
	}
?>