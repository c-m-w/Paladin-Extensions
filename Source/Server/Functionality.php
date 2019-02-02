<?php
	require 'Cryptography.php';
	require 'Logging.php';
	require 'SQL.php';

	define( "unsafeTerms", array(
		" drop ", " delete ", " select ", " alter ", " table ", " class ",
		" DROP ", " DELETE ", " SELECT ", " ALTER ", " TABLE ", " CLASS " ) );
	define( "exitCodes", array(
		"Establishing Failure"	=> "1",		// Couldn't connect / set up database info or unique id and secret key aren't found / debugger is found
		"Invalid Hash"			=> "2",
		"Banned"				=> "3",		// banned login attempt
		"Hardware Mismatch"		=> "4",
		"Inactive Premium"		=> "5",		// premium time exceeded
		"Success"				=> "6",		// regular user logged in
		"Staff Success"			=> "7" ) );	// staff member logged in
	define( "launcherFile", "../Extensions/Launcher.exe" );

	$cryptography	= new Cryptography( );
	$log			= new Logging( );
	$sql			= new SQLConnection( );

	class Functionality
	{
		$connection_info;

		public function sanitize( $input ): string
		{
			return $sql->escape( strip_tags( trim( str_replace( unsafeTerms, "", $input ) ) ) );
		}

		public function getPostData( $id ): string
		{
			global $cryptography;

			$accessIdentifier = $cryptography->generateIdentifier( $id );
			return sanitize( $cryptography->decrypt( $_POST[ $accessIdentifier ] ) );
		}

		public function exit( $exit_code, $other_data = 'none' ): void
		{
			global $log;
			global $cryptography;

			$log->log( 'Exiting with code ' . $exit_code . ' [' . exitCodes[ $exit_code ] . '].' );
			die( $cryptography->encrypt( json_encode( array( 'Exit Code' => exitCodes[ $exit_code ],
																'Other Data' => $other_data ) ) ) );
		}

		function getConnectionInfo( )
		{
			$curl = curl_init( );

			curl_setopt( $curl, CURLOPT_URL, "http://v2.api.iphub.info/ip/" . $_SERVER[ "REMOTE_ADDR" ] );
			curl_setopt( $curl, CURLOPT_RETURNTRANSFER, true );
			curl_setopt( $curl, CURLOPT_HTTPHEADER, array( "X-Key: MjkxMzpaTFZoNVVjakR2bGU0ZmlucW95WlFrMWhxMmtVMzNlNA==" ) );

			$response = json_decode( curl_exec( $curl ), true );
			curl_close( $curl );
			$connection_info = $response;
		}

		function getServiceProvider( ): string
		{
			return $connection_info[ 'isp' ];
		}

		function getCountryCode( ): string
		{
			return $connection_info[ 'countryCode' ];
		}
	}

	$functionality	= new Functionality( );

	class Authentication
	{
		$user;
		$key;
		$hardware;
		$hash;
		$xfUser;
		$unique

		private function parsePostData( ):
		{
			global $functionality;

			$user		= $functionality->getPostData( 'id' );
			$key		= $functionality->getPostData( 'sk' );
			$hardware	= json_decode( $functionality->getPostData( 'hw' ), true );
			$hash		= $functionality->getPostData( 'hw' );
		}

		private function validateHash( ): void
		{
			global $cryptography;
			global $log;
			global $functionality;

			if ( $hash != $cryptography->hashFile( launcherFile ) )
			{
				$log->log( 'Hash sent over post data did not match what the server computed.' );
				$functionality->exit( 'Invalid Hash' );
			}
		}

		private function getUserInformation( ): void
		{
			global $sql;
			global $log;
			global $functionality;

			$result = $sql->selectRows( 'secondary_group_ids, is_banned, is_staff', 'xf_user', 'user_id = ' . $user . ' AND secret_key = "' . $key . '"' );
			if ( $result->num_rows == 0 )
			{
				$log->log( 'Could not find user with id of ' . $user . ' and secret key of ' . $key . ' in table xf_user.' );
				$functionality->exit( 'Establishing Failure' );
			}

			$xfUser = $result->fetch_assoc( );
		}

		private function logAttempt( $exit_code ): void
		{
			global $sql;

			if ( $hardware == NULL
				|| ( $row = $sql->selectRows( 'unique_id', 'px_unique_id', 'user_id = ' . $user_id
				. ' AND cpu = "' . $hardware[ "cpu" ]
				. '" AND gpu = "' . $hardware[ "gpu" ]
				. '" AND display = "' . $hardware[ "display" ]
				. '" AND pc = "' . $hardware[ "pc" ]
				. '" AND os = "' . $hardware[ "os" ]
				, '" AND drive = "' . $hardware[ "drive" ]
				. '" AND board = "' . $hardware[ "board" ] . '"' ) )->num_rows == 0 )
				$unique_id = 0;
			else
				$unqiue_id = $row->fetch_assoc( )[ 'unique_id' ];

			$sql->insert( 'px_logins', ( int )$user_id . ', '
					. ( int )time( ) . ', '
					. ( int )$cur_unique_id . ', '
					. $unique_id . ', "'
					. ( string )$info[ "ip" ] . '", "'
					. ( string )$info[ "isp" ] . '", "'
					. ( string )$info[ "countryCode" ] . '", '
					. ( int )$exit_code );
			$functionality->exit( $exit_code, $xfUser[ 'secondary_group_ids' ] )
		}

		private function ensureValidUser( ): void
		{
			global $sql;
			global $log;

			if ( $xfUser[ 'is_banned' ] )
				logAttempt( 'Banned' );

			if ( $hardware == NULL )
			{
				$log->log( 'Invalid hardware was passed through post data.' );
				logAttempt( 'Hardware Mismatch' );
			}

			$result = $sql->selectRows( 'field_value', 'xf_user_field_value', 'field_id = "unique_id" AND user_id = ' . $user );
			if ( $result->num_rows == 0 )
			{
				$log->log( 'Could not obtain unique id from xf_user_field_value. User ID: ' . $user . '.' );
				logAttempt( 'Establishing Failure' );
			}

			$unique = $result->fetch_assoc( )[ 'field_value' ];

			$result = $sql->selectRows( 'px_unique_id', '*', 'user_id = ' . $user_id
						. ' AND cpu = "' . $hardware[ "cpu" ]
						. '" AND gpu = "' . $hardware[ "gpu" ]
						. '" AND display = "' . $hardware[ "display" ]
						. '" AND pc = "' . $hardware[ "pc" ]
						. '" AND os = "' . $hardware[ "os" ]
						. '" AND drive = "' . $hardware[ "drive" ]
						. '" AND board = "' . $hardware[ "board" ] . '"' );
			if ( $result->num_rows == 0 )
			{
				$sql->insertRow( 'px_unique_id', '0, '
							. $user_id . ', "'
							. $hardware[ "cpu" ] . '", "'
							. $hardware[ "gpu" ] . '", "'
							. $hardware[ "display" ] . '", "'
							. $hardware[ "pc" ] . '", "'
							. $hardware[ "os" ] . '", "'
							. $hardware[ "drive" ] . '", "'
							. $hardware[ "board" ] . '")' );
				logAttempt( 'Hardware Mismatch' );
			}

			if ( $result->fetch_assoc( )[ 'unique_id' ] != $unique )
			{
				$sql->updateRow( 'xf_user_field_value', 'field_value', 0, 'field_id = "unique_id" AND user_id = ' . $user );
				logAttempt( 'Hardware Mismatch' );
			}
		}

		private function beginSession( )
		{
			session_start( );
			$_SESSION[ 'user' ] = xfUser;
		}

		public function login( ): void
		{
			parsePostData( );
			validateHash( );
			getUserInformation( );
			ensureValidUser( );
			beginSession( );
			logAttempt( xfUser[ 'is_staff' ] ? 'Staff Success' : 'Success' );
		}
	}
?>