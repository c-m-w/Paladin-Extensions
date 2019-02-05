<?php
	define( "generationInterval", 3600 );
	define( "encryptionKeySize", 32 );
	define( "initializationVectorSize", 16 );
	define( "encryptionMethod", "AES-256-CBC" );
	define( "identifierSize", 16 );

	class Cryptography
	{
		private $lastGenerationTime;
		private $encryptionKey;
		private $initializationVector;

		function __construct( )
		{
			$this->generateKeys( );
		}

		private function generateKeys( ): void
		{
			if ( time( ) - $this->lastGenerationTime < generationInterval
				&& strlen( $this->encryptionKey ) > 0 && strlen( $this->initializationVector ) > 0 )
				return;

			$unhashedKey = ( string )( ( int )( time( ) / generationInterval ) );
			$hash = $this->generateHash( $unhashedKey );
			$this->encryptionKey = substr( $hash, 0, encryptionKeySize );
			$this->initializationVector = substr( $hash, 0, initializationVectorSize );
		}

		public function generateHash( $bytes ): string
		{
			return sha1( $bytes );
		}

		public function hashFile( $filename ): string
		{
			return $this->generateHash( file_get_contents( $filename ) );
		}

		public function encrypt( $bytes ): string
		{
			$this->generateKeys( );

			return openssl_encrypt( $bytes, encryptionMethod, $this->encryptionKey, 0, $this->initializationVector );
		}

		public function decrypt( $bytes ): string
		{
			$this->generateKeys( );

			return openssl_decrypt( $bytes, encryptionMethod, $this->encryptionKey, 0, $this->initializationVector );
		}

		public function generateIdentifier( $id )
		{
			return substr( $this->generateHash( $id ), 0, identifierSize );
		}
	}
?>