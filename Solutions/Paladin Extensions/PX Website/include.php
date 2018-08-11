<?php
	// This file should be placed a directory upward of the website.
	// TODO: Logging include file.
	// TODO: Encrypting and decrypting and generating encryption keys, ivs and post identifiers.
	// TODO: Check loader hash.
	
	define("ReturnKeys",
		array( 
        "Establishing Failure" 			=> "1", // Couldn't connect / set up database info or unique id and secret key arent found / debugger is found
        "Invalid Hash"			        => "2",
        "Banned" 						=> "3", // banned login attempt
        "Hardware Mismatch"             => "4",
        "Inactive Premium" 				=> "5", // premium time exceeded
        "Success" 						=> "6", // regular user logged in
        "Staff Success" 				=> "7"  // staff member logged in
        ) );
	
	$sql_connection = new mysqli( "localhost", "palatfef_admin", "_paladin_ext()++", "palatfef_xenforo" );

	function GenerateKeys( )
	{
        $time = ( int )( time( ) / 100 );
        $keys[ "key" ] = substr( sha1( $time ), 0, 32 );
		$keys[ "iv" ] = substr( $keys[ "key" ], 0, 16) ;
		return $keys;
	}

    define( "Keys", GenerateKeys( ) );
	
	function GenerateIdentifier( $identifier ) // Anything indexing the $_POST global needs to be one of these identifiers.
	{
		return substr( sha1( sha1( Keys[ "iv" ] ) . sha1( $identifier ) ), 0, 16 ); // encrypt the identifier for a random hash each time
	}
	
	define( "EncryptionMethod", "AES-256-CBC" );
	
	function Encrypt( $plain_text )
	{
		return openssl_encrypt( $plain_text, EncryptionMethod,isset( $_SESSION[ "key" ] ) ? $_SESSION[ "key" ] : Keys[ "key" ], 0, isset( $_SESSION[ "iv" ] ) ? $_SESSION[ "iv" ] : Keys[ "iv" ] ); // Base64 encode then encrypt.
	}
	
	function Decrypt( $cipher_text )
	{
        // We remove the == at the end so its not obvious if someone is packet sniffing that it's base 64'd. CryptoPP adds a \n at the end for some reason so we also have to re-add that.
		return openssl_decrypt( str_replace( " ", "+", $cipher_text ) . PHP_EOL, EncryptionMethod, isset( $_SESSION[ "key" ] ) ? $_SESSION[ "key" ] : Keys[ "key" ], 0, isset( $_SESSION[ "iv" ] ) ? $_SESSION[ "iv" ] : Keys[ "iv" ] ); // Base64 decode then decrypt.
	}

    function GetUserFromIP( )
    {
        global $sql_connection;

        $ip = "0x" . dechex( ip2long( $_SERVER[ "REMOTE_ADDR"] ) );
        $result = $sql_connection->query( 'SELECT user_id FROM xf_ip WHERE ip =' . $ip );

        if( $result->num_rows == 0 )
            return false;

        $row = $result->fetch_assoc( );
        $user_id = $row[ "user_id" ];
        $result = $sql_connection->query( 'SELECT secret_key FROM xf_user WHERE user_id = "' . $user_id . '"' );

        if( $result->num_rows == 0 )
            return false;

        return array( "id" => $user_id, "sk" => $result->fetch_assoc( )[ "secret_key" ] );
    }
	
	define( "UnsafeKeywords", array( " drop ", " delete ", " select ", " alter ", " table ", " class ", " DROP ", " DELETE ", " SELECT ", " ALTER ", " TABLE ", " CLASS " ) ); // TODO: Add all unsafe keywords.
	
	function SanitizeInput( $string )
	{
        global $sql_connection;
		return $sql_connection->escape_string( strip_tags( trim( str_replace( UnsafeKeywords, "", $string ) ) ) );
	}

    $secondary_group_ids = 0;
    $is_staff = false;
    $is_banned = false;

    function ValidUser( $user_id, $secret_key )
    {
        global $sql_connection;
        global $secondary_group_ids;
        global $is_staff;
        global $is_banned;

        $result = $sql_connection->query( "SELECT secondary_group_ids, is_banned, is_staff FROM xf_user WHERE user_id = " . $user_id . " AND secret_key = '" . $secret_key . "'" );
        
        if( $result->num_rows == 0 )
            return false;

        $row = $result->fetch_assoc( );
        $secondary_group_ids = $row[ "secondary_group_ids" ];
        $is_staff = $row[ "is_staff" ];
        $is_banned = $row[ "is_banned" ];
        return true;
    }

    function GetUniqueID( $user_id )
    {
        global $sql_connection;

        $result = $sql_connection->query( "SELECT field_value FROM xf_user_field_value WHERE field_id = 'unique_id' AND user_id = '" . $user_id . "'" );
        
        if( $result->num_rows == 0 )
            return 0;
        return $result->fetch_assoc( )[ "field_value" ];
    }

    // https://iphub.info/api
    function GetIPInformation( )
    {
        $curl = curl_init( );

        curl_setopt( $curl, CURLOPT_URL, "http://v2.api.iphub.info/ip/" . $_SERVER[ "REMOTE_ADDR" ] );
        curl_setopt( $curl, CURLOPT_RETURNTRANSFER, true );
        curl_setopt( $curl, CURLOPT_HTTPHEADER, array( "X-Key: MjkxMzpaTFZoNVVjakR2bGU0ZmlucW95WlFrMWhxMmtVMzNlNA==" ) );

        $response = json_decode( curl_exec( $curl ), true );
        curl_close( $curl );
        return $response;
    }

    function PutLoginAttempt( $user_id, $cur_unique_id, $hardware, $code )
    {
        global $sql_connection;

        $info = GetIPInformation( );
        if( $hardware == NULL )
            $unique_id = 0;
         else
         {
            $result = $sql_connection->query( 'SELECT unique_id FROM px_unique_id WHERE user_id = '. $user_id . ' AND cpu = "' . $hardware[ "cpu" ] . '" AND gpu = "' . $hardware[ "gpu" ] . '" AND display = "' . $hardware[ "display" ] . '" AND os = "' . $hardware[ "os" ] . '" AND board = "' . $hardware[ "board" ] . '"' );
            if( $result->num_rows == 0 )
                $unique_id = NULL;
            else
                $unique_id = $result->fetch_assoc( )[ "unique_id" ];
         }
        $sql_connection->query( 'INSERT INTO px_logins VALUES (' . ( int )$user_id . ', ' . ( int )time( ) . ', ' . ( int )$cur_unique_id . ', ' . $unique_id . ', "' . ( string )$info[ "ip" ] . '", "' . ( string )$info[ "isp" ] . '", "' . ( string )$info[ "countryCode" ] . '", ' . ( int )$code . ')' );
        return ( string )$code;
    }

    function InsertNewHardware( $unique_id, $user_id, $hardware )
    {
        global $sql_connection;

         // Don't break the query line.
        $sql_connection->query( 'INSERT INTO px_unique_id VALUES (0, ' . $user_id . ', "' . $hardware[ "cpu" ] . '", "' . $hardware[ "gpu" ] . '", "' . $hardware[ "display" ] . '", "' . $hardware[ "os" ] . '", "' . $hardware[ "board" ] . '")' );
    }

    function ValidateHardware( $unique_id, $user_id, $hardware )
    {
        global $sql_connection;

        $result = $sql_connection->query( 'SELECT * FROM px_unique_id WHERE user_id = '. $user_id . ' AND cpu = "' . $hardware[ "cpu" ] . '" AND gpu = "' . $hardware[ "gpu" ] . '" AND display = "' . $hardware[ "display" ] . '" AND os = "' . $hardware[ "os" ] . '" AND board = "' . $hardware[ "board" ] . '"' );

        if( $result->num_rows == 0 )
        {
             InsertNewHardware( $unique_id, $user_id, $hardware );
             return false;
        }
        
        $row = $result->fetch_assoc( );
        return $row[ "unique_id" ] == $unique_id;
    }
	
	function BeginSession( $user_id )
	{
        global $is_staff;

		session_start( );
		$_SESSION[ "key" ] = Keys[ "key" ];
		$_SESSION[ "iv" ] = Keys[ "iv" ];
        $_SESSION[ "is_staff" ] = $is_staff;
        $_SESSION[ "user_id" ] = $user_id;
	}
	
    define( "ExtensionID", array( "manager" => 1, "csgo" => 2, "pubg" => 3, "rsix" => 4 ) );

	define( "GameInfo", array( 2 => "../../Extensions/csgo.info", 3 => "../../Extensions/pubg.info" ) );
	define( "GameCheat", array( 2 => "../../Extensions/csgo.dll", 3 => "../../Extensions/pubg.dll" ) );
	
	function CompileCheat( $game_id )
	{
		// -o 'output file' 'file to compile'
		exec( "g++ -o ".GameCheat[ $game_id ]." **FILE TO COMPILE**" );
	}
	
    define( "FileSections", 7 );

    function GenerateRandomOrder( )
    {
        for( $i = 0; $i < FileSections; $i++ )  
        {
            do
            {
                $number = rand( 0, FileSections - 1 );
            } while( $used_sections[ $number ] === true );

            $used_sections[ $number ] = true;
            $section_order[ $i ] = $number;
        }
        return $section_order;
    }

    function GenerateSections( $file_name, $order )
    {
        clearstatcache( );
        $file_data = file_get_contents( $file_name );
        $file_size = strlen( $file_data );
        $size_per_section = ( int )ceil( $file_size / FileSections );
        
        for( $i = 0; $i < FileSections; $i++ )
            $ordered_sections[ $i ] = Encrypt( substr( $file_data, $size_per_section * $i, $size_per_section ) );
        
        for( $i = 0; $i < FileSections; $i++ )
            $sections[ $i ] = $ordered_sections[ $order[ $i ] ];
        return $sections;
    }

	function GetDLL( $game_id )
	{
        $order = GenerateRandomOrder( );
		return Encrypt( json_encode( array( "Order" => $order, "Sections" => GenerateSections( GameCheat[ $game_id ], $order ) ) ) );
	}
	
	function SendInformation( $game_id )
	{
		session_start( );
		if( $_SESSION[ "logged_in" ] == TRUE )
			echo openssl_encrypt( file_get_contents( GameInfo[ $game_id ] ), EncryptionMethod, $_SESSION[ "key" ], 0, $_SESSION[ "iv" ] );
		else
			echo ReturnKeys[ "Establishing Failure" ];
		session_destroy( );
	}

    function GetExtensionInformation( )
    {
        global $sql_connection;

        $result = $sql_connection->query( "SELECT * FROM px_extension_info" );

        while( ( $row = $result->fetch_assoc( ) ) != NULL )
        {
            $info = array( "Name" => ( string )$row[ "name" ], "Status" => ( string )$row[ "status" ], "Estimated Next Update" => ( string )$row[ "estimated_next_update" ], "Last Update" => ( string )$row[ "last_update" ], "Version" => ( string )$row[ "version" ] );

            $return[ "Info" ][ ExtensionID[ $row[ "name" ] ] ] = $info;
            $return[ "Count" ]++;
        }

        return json_encode( $return );
    }

    function GetLastLaunchTime( )
    {
        global $sql_connection;

        for( $i = ExtensionID[ "csgo" ]; $i <= ExtensionID[ "rsix" ]; $i++ )
        {
            $result = $sql_connection->query( "SELECT MAX( time ) FROM px_extension_load WHERE user_id = " . $_SESSION[ "user_id" ] . " AND ext = " . $i );
            if( $result->num_rows < 1 )
                $launchtimes[ $i ] = 0;

            $row = $result->fetch_assoc( );
            $launchtimes[ $i ] = ( int )$row[ "time" ];
        }
        return $launchtimes;
    }
?>