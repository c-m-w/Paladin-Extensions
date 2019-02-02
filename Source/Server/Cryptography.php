<?php
	define( "generationInterval", 3600 );
	define( "encryptionKeySize", 32 );
	define( "initializationVectorSize", 16 );
	define( "encryptionMethod", "AES-256-CBC" );

	class Cryptography
	{
		private $lastGenerationTime;
		private $encryptionKey;
		private $initializationVector;

		function __construct( )
		{
			generateKeys( );
		}

		private function generateKeys( ): void
		{
			if ( time( ) - $lastGenerationTime < generationInterval
				&& strlen( $encryptionKey ) > 0 && strlen( $initializationVector ) > 0 )
				return;

			$unhashedKey = ( string )( time( ) / generationInterval );
			$hash = generateHash( $unhashedKey );
			$encryptionKey = substr( $hash, 0, encryptionKeySize );
			$initializationVector = substr( $hash, 0, initializationVectorSize );
		}

		public function generateHash( $bytes ): string
		{
			return sha1( $bytes );
		}

		public function encrypt( $bytes ): string
		{
			generateKeys( );

			return openssl_encrypt( $bytes, encryptionMethod, $encryptionKey, 0, $initializationVector );
		}

		public function decrypt( $bytes ): string
		{
			generateKeys( );
			
			return openssl_decrypt( $bytes, encryptionMethod, $encryptionKey, 0, $initializationVector );
		}
	}
?>