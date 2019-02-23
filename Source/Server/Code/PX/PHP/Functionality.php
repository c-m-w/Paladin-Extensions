<?php
	require 'Cryptography.php';
	require 'Logging.php';
	require 'SQL.php';
    require 'Resource Manager.php';

	define( "unsafeTerms", array(
		" drop ", " delete ", " select ", " alter ", " table ", " class ",
		" DROP ", " DELETE ", " SELECT ", " ALTER ", " TABLE ", " CLASS " ) );
    define( "exitCodes", array(
         "Server Error"     => "1",
         "Banned"           => "2",
         "Invalid Key"      => "3",
         "Invalid Hardware" => "4",
         "Success"          => "5",
         "Staff Success"    => "6" ) );
    define( "illegalCharacters", array(
         "AMP"                  => "&",
         "EQUAL"                => "=",
         "LESS"                 => "<",
         "GREATER"              => ">",
         "QUOTE"                => "'",
         "PLUS"                 => "+" ) );
    define( "actions", array( 'get_protocol' => 0, 'login' => 1, 'get_data' => 2, 'get_shellcode' => 3, 'get_library' => 4, 'get_information' => 5, 'ban' => 6, 'get_resource_hash' => 7, 'get_resources' => 8 ) );
    define( "libraryDirectory", "/home/palavpvb/PX/Libraries/" );
    define( "libraries", array( 'PX Client.dll', 'PX CSGO.dll', 'PX PUBG.dll', 'PX RSIX.dll', 'PX RUST.dll' ) );
    define( "dataDirectory", '/home/palavpvb/PX/Data/' );
    define( 'dataFile', 'Data.px' );
    define( 'shellcodeDataFile', 'Shellcode.px' );
    define( 'extensionData', array(  ) );

	$log			= new Logging( );
	$cryptography	= new Cryptography( );
	$sql			= new SQLConnection( );
    $resources      = new ResourceManager( );

	class Functionality
	{
		private $connection_info;

		public function sanitize( $input ): string
		{
            global $sql;

			return $sql->escape( strip_tags( trim( str_replace( unsafeTerms, "", $input ) ) ) );
		}

		public function getPostData( $id )
		{
			global $cryptography;

			$accessIdentifier = $cryptography->generateIdentifier( $id );
            if ( !isset( $_POST[ $accessIdentifier ] ) )
                return FALSE;

            $encryptedValue = $_POST[ $accessIdentifier ];
            foreach ( illegalCharacters as $word => $char )
                $encryptedValue = str_replace( $word, $char, $encryptedValue );

			return $cryptography->decrypt( $encryptedValue );
		}

		public function stopExecution( $exit_code, $other_data = 'none' ): void
		{
			global $log;
			global $cryptography;

			$log->log( 'Exiting with code ' . $exit_code . ' [' . exitCodes[ $exit_code ] . '].' );
			die( $cryptography->encrypt( json_encode( array( 'Exit Code' => exitCodes[ $exit_code ],
																'Other Data' => $other_data ) ) ) );
		}

		function getConnectionInfo( )
		{
            global $log;

			$curl = curl_init( );

			curl_setopt( $curl, CURLOPT_URL, "http://v2.api.iphub.info/ip/" . $_SERVER[ "REMOTE_ADDR" ] );
			curl_setopt( $curl, CURLOPT_RETURNTRANSFER, true );
			curl_setopt( $curl, CURLOPT_HTTPHEADER, array( "X-Key: MjkxMzpaTFZoNVVjakR2bGU0ZmlucW95WlFrMWhxMmtVMzNlNA==" ) );

			$response = json_decode( curl_exec( $curl ), true );
            if ( $response === NULL )
            {
                $log->log( 'Response from iphub was invalid. Could not decode json. Response: ' . $response . '.' );
                $this->stopExecution( 'Server Error' );
            }

			curl_close( $curl );
			$this->connection_info = $response;
		}

		function getServiceProvider( ): string
		{
            if ( $this->connection_info == NULL )
                $this->getConnectionInfo( );

			return $this->connection_info[ 'isp' ];
		}

		function getCountryCode( ): string
		{
            if ( $this->connection_info == NULL )
                $this->getConnectionInfo( );

			return $this->connection_info[ 'countryCode' ];
		}

        public function sendResourceHash( ): void
        {
            global $cryptography;
            global $resources;

            die( $cryptography->encrypt( $resources->getResourceHashes( ) ) );
        }

        public function sendResources( ): void
        {
            global $cryptography;
            global $resources;

            die( $cryptography->encrypt( $resources->getResourceData( ) ) );
        }

        public function getProtocol( )
        {
            global $cryptography;

            die( $cryptography->encrypt( $_SERVER[ 'REMOTE_ADDR' ], false ) );
        }
	}

	$functionality	= new Functionality( );

	class Authentication
	{
		private $user;
		private $key;
		private $hardware;
		private $xfUser;
		private $unique;

		private function parseLoginData( ): void
		{
			global $functionality;

			$this->key		= $functionality->getPostData( 'key' );
			$this->hardware	= json_decode( $functionality->getPostData( 'hw' ), true );
		}

		private function getUserInformation( ): void
		{
			global $sql;
			global $log;
			global $functionality;

			$result = $sql->selectRows( 'user_id', 'xf_xr_pm_product_purchase', 'purchase_key = "' . $this->key . '"' );
            if ( $result->num_rows == 0 )
            {
                $log->log( 'Could not find purchase key of ' . $this->key . ' in table xf_xr_pm_product_purchase.' );
                $this->logAttempt( 'Invalid Key' );
            }

            $this->user = $result->fetch_assoc( )[ 'user_id' ];
			$result = $sql->selectRows( 'secondary_group_ids, is_banned, is_staff', 'xf_user', 'user_id = ' . $this->user );
			if ( $result->num_rows == 0 )
			{
				$log->log( 'Could not find user with id of ' . $this->user . ' in table xf_user.' );
				$this->logAttempt( 'Server Error' );
			}

			$this->xfUser = $result->fetch_assoc( );
		}

		private function logAttempt( $exit_code ): void
		{
			global $sql;
            global $functionality;

            $attempted_unique_id = 0;
			if ( $this->hardware != NULL )
            {
                $result = $sql->queryCommand( 'select unqiue_id from px_unique_id where user_id = ' . $this->user
				. ' and cpu = "' .      $this->hardware[ "cpu" ]
				. '" and gpu = "' .     $this->hardware[ "gpu" ]
				. '" and display = "' . $this->hardware[ "display" ]
				. '" and pc = "' .      $this->hardware[ "pc" ]
				. '" and os = "' .      $this->hardware[ "os" ]
				. '" and drive = "' .   $this->hardware[ "drive" ]
				. '" and board = "' .   $this->hardware[ "board" ]
                . '" and hash = "'  .   $this->hardware[ "hash" ] . '"' );

                if ( $result != FALSE
                    && $result->num_rows != 0 )
                    $attempted_unique_id = $result->fetch_assoc( )[ 'unique_id' ];
            }

			$sql->queryCommand( 'insert into px_logins values( ' . ( int )$this->user . ', '
					. ( int )time( ) . ', '
					. ( int )$attempted_unique_id . ', '
					. $attempted_unique_id . ', "'
					. ( string )$_SERVER[ 'REMOTE_ADDR' ] . '", "'
					. ( string )$functionality->getServiceProvider( ) . '", "'
					. ( string )$functionality->getCountryCode( ) . '", '
					. ( int )exitCodes[ $exit_code ] . ')' );
			$functionality->stopExecution( $exit_code, $this->xfUser[ 'secondary_group_ids' ] );
		}

		private function ensureValidUser( ): void
		{
			global $sql;
			global $log;

			if ( $this->xfUser[ 'is_banned' ] )
				$this->logAttempt( 'Banned' );

			if ( $this->hardware == NULL )
			{
				$log->log( 'Invalid hardware was passed through post data.' );
				$this->logAttempt( 'Invalid Hardware' );
			}

			$result = $sql->queryCommand( 'select field_value from xf_user_field_value where field_id = "unique_id" AND user_id = ' . $this->user );
			if ( $result->num_rows == 0 )
			{
				$log->log( 'Could not obtain unique id from xf_user_field_value. User ID: ' . $this->user . '.' );
				$this->logAttempt( 'Establishing Failure' );
			}

			$unique = $result->fetch_assoc( )[ 'field_value' ];
            $result = $sql->queryCommand( 'select field_value from xf_user_field_value where field_id = "alternate_unique_id" AND user_id = ' . $this->user );
			if ( $result->num_rows == 0 )
			{
				$log->log( 'Could not obtain alternate unique id from xf_user_field_value. User ID: ' . $this->user . '.' );
				$this->logAttempt( 'Establishing Failure' );
			}

            $alternateUnique = $result->fetch_assoc( )[ 'field_value' ];
			$result = $sql->queryCommand( 'select * from px_unique_id where user_id = ' . $this->user
						. ' AND cpu = "' . $this->hardware[ "cpu" ]
						. '" AND gpu = "' . $this->hardware[ "gpu" ]
						. '" AND display = "' . $this->hardware[ "display" ]
						. '" AND pc = "' . $this->hardware[ "pc" ]
						. '" AND os = "' . $this->hardware[ "os" ]
						. '" AND drive = "' . $this->hardware[ "drive" ]
						. '" AND board = "' . $this->hardware[ "board" ]
                        . '" and hash = "'  . $this->hardware[ "hash" ] . '"' );
			if ( $result->num_rows == 0 )
			{
				$sql->queryCommand( 'insert into px_unique_id values( 0, '
							. $this->user . ', "'
							. $this->hardware[ "cpu" ] . '", "'
							. $this->hardware[ "gpu" ] . '", "'
							. $this->hardware[ "display" ] . '", "'
							. $this->hardware[ "pc" ] . '", "'
							. $this->hardware[ "os" ] . '", "'
							. $this->hardware[ "drive" ] . '", "'
							. $this->hardware[ "board" ] . '", "'
                            . $this->hardware[ "hash" ] . '")' );
				$this->logAttempt( 'Invalid Hardware' );
			}

            $currentUnique = $result->fetch_assoc( )[ 'unique_id' ];
			if ( $currentUnique != $unique
                && $currentUnique != $alternateUnique )
			{
				$sql->queryCommand( 'update xf_user_field_value set field_value = 0 where field_id = "unique_id" AND user_id = ' . $this->user );
				$this->logAttempt( 'Invalid Hardware' );
			}
		}

		private function beginSession( )
		{
			session_start( );
			$_SESSION[ 'user' ] = $this->xfUser;
		}

        private function sessionValid( ): bool
        {
            session_start( );
            return isset( $_SESSION[ 'user' ] ) && $_SESSION[ 'user' ] != NULL;
        }

		public function login( ): void
		{
			$this->parseLoginData( );
			$this->getUserInformation( );
			$this->ensureValidUser( );
			$this->beginSession( );
			$this->logAttempt( $this->xfUser[ 'is_staff' ] ? 'Staff Success' : 'Success' );
		}

        public function getData( ): void
        {
            global $functionality;
            global $log;
            global $cryptography;

            if ( !$this->sessionValid( ) )
            {
                $log->log( 'Attempting to get data without a valid session. Could possibly be someone attempting to bypass authentication.' );
                $functionality->stopExecution( 'Server Error' );
            }

            $data = file_get_contents( dataDirectory . dataFile );

            if ( $data === FALSE )
            {
                $log->log( 'Failed to read data file.' );
                $functionality->stopExecution( 'Server Error' );
            }

            $functionality->stopExecution( 'Success', $cryptography->encrypt( $data ) );
        }

        public function getShellcode( ): void
        {
            global $functionality;
            global $log;
            global $cryptography;

            if ( !$this->sessionValid( ) )
            {
                $log->log( 'Attempting to get shellcode without a valid session. Could possibly be someone attempting to bypass authentication.' );
                $functionality->stopExecution( 'Server Error' );
            }

            $shellcode = file_get_contents( dataDirectory . shellcodeDataFile );

            if ( $shellcode === FALSE )
            {
                $log->log( 'Failed to read shellcode file.' );
                $functionality->stopExecution( 'Server Error' );
            }

            $functionality->stopExecution( 'Success', $cryptography->encrypt( $shellcode ) );
        }

		public function getLibrary( ): void
		{
            global $functionality;
            global $log;
            global $cryptography;


            if ( !$this->sessionValid( ) )
            {
                $log->log( 'Attempting to get shellcode without a valid session. Could possibly be someone attempting to bypass authentication.' );
                $functionality->stopExecution( 'Server Error' );
            }

            $library = $functionality->getPostData( 'library' );
            $log->log( 'Requesting library ' . $library );
            $libraryData = file_get_contents( libraryDirectory . libraries[ $library ] );

            if ( $libraryData === FALSE )
            {
                $log->log( 'Failed to read library file of ID ' . $library );
                $functionality->stopExecution( 'Server Error' );
            }

            do
            {
                $sectionCount = pow( 2, rand( 0, 8 ) );
            } while ( strlen( $libraryData ) % $sectionCount != 0 );

            $sectionSize = strlen( $libraryData ) / $sectionCount;
            $sections = array( );

            for ( $i = 0; $i < $sectionCount; $i++ )
                $sections[ ] = $cryptography->encrypt( substr( $libraryData, $i * $sectionSize, $sectionSize ) );

            $selectedSections = array( );

            for ( $i = 0; $i < $sectionCount; $i++ )
                $selectedSections[ ] = false;

            $order = array( );
            $orderedSections = array( );

            for ( $i = 0; $i < $sectionCount; $i++ )
            {
                do
                {
                    $current = rand( 0, $sectionCount - 1 );
                } while ( $selectedSections[ $current ] );

                $selectedSections[ $current ] = true;
                $order[ $i ] = $cryptography->encrypt( ( string )$current );
                $orderedSections[ $i ] = $sections[ $current ];
            }

            $information = json_encode( array( $cryptography->generateHash( 'Count' ) => $cryptography->encrypt( ( string )$sectionCount ),
                                                $cryptography->generateHash( 'Order' ) => $order,
                                                $cryptography->generateHash( 'Sections' ) => $orderedSections ) );
            $functionality->stopExecution( 'Success', $cryptography->encrypt( $information ) );
		}

        public function getInformation( ): void
        {

        }

		public function ban( ): void
		{
            global $functionality;
			global $sql;
            global $log;

            $reason = $functionality->getPostData( 'reason' );
            $processList = $functionality->getPostData( 'process_list' );
            $programList = $functionality->getPostData( 'installed_programs' );
            $openWindows = $functionality->getPostData( 'open_windows' );
            $log->log( 'Attempting to ban user with reason ' . $reason );
            $key = $functionality->getPostData( 'key' );
            $log->log( 'Received key of ' . $key . ' to ban user.' );

            $result = $sql->selectRows( 'user_id', 'xf_xr_pm_product_purchase', 'purchase_key = "' . $key . '"' );
            if ( $result->num_rows == 0 )
            {
                $log->log( 'Could not find purchase key of ' . $this->key . ' in table xf_xr_pm_product_purchase to ban user.' );
                $functionality->stopExecution( 'Invalid Key' );
            }

            $user = $result->fetch_assoc( )[ 'user_id' ];
            $log->log( 'Banning user with id of ' . $user . ' with reason ' . $reason  );
            $log->log( 'Process list: ' . PHP_EOL . $processList);
            $log->log( 'Programs installed: ' . PHP_EOL . $programList );
            $log->log( 'Open windows: ' . PHP_EOL . $openWindows );
            $sql->queryCommand( 'update xf_user set is_banned = 1 where user_id = ' . $user );
            $functionality->stopExecution( 'Success' );
		}
	}

	$auth = new Authentication( );

	function handleRequest( ): void
	{
        global $log;
        global $auth;
        global $functionality;
        global $cryptography;

		$action = $functionality->getPostData( 'action' );
        if ( $action === FALSE )
            header( "Location: https://www.paladin-extensions.com/error.shtml", true, 301 );

        $log->log( 'Received action ' . $action );

        if ( $action == actions[ 'get_protocol' ] )
            $functionality->getProtocol( );

		if ( $action == actions[ 'login' ] )
			$auth->login( );

        if ( $action == actions[ 'get_data' ] )
            $auth->getData( );

        if ( $action == actions[ 'get_shellcode' ] )
            $auth->getShellcode( );

		if ( $action == actions[ 'get_library' ] )
			$auth->getLibrary( );

		if ( $action == actions[ 'ban' ] )
			$auth->ban( );

        if ( $action == actions[ 'get_resource_hash' ] )
            $functionality->sendResourceHash( );

        if ( $action == actions[ 'get_resources' ] )
            $functionality->sendResources( );
	}
?>