<?php
	class Logging
	{
		private $logBuffer;

		function __construct( )
		{
			$this->rawLog( "[Session Begin " . $this->getDate( ) . "]" );
		}

		function __destruct( )
		{
			$this->rawLog( '[Session End]' );
		}

		private function getDate( ): string
		{
			return strftime( "%B %e, 20%g" );
		}

		private function getTime( ): string
		{
			return strftime( "%H:%M:%S" );
		}

		private function getLogFile( ): string
		{
			return "Logs/" . strftime( "%Y-%m-%d" );
		}

		private function rawLog( $message ): void
		{
			$logFile = $this->getLogFile( );
			$currentContents = file_get_contents( $logFile );
			if( $currentContents === FALSE )
				$currentContents = '[Log File Begin]' . PHP_EOL;

			$currentContents = $currentContents . $message . PHP_EOL;
			file_put_contents( $logFile, $currentContents );
		}

		public function log( $message ): void
		{
			$this->rawLog( '[' . $this->getTime( ) . ']\t' . $_SERVER[ 'REMOTE_ADDR' ] . $message );
		}
	}
?>