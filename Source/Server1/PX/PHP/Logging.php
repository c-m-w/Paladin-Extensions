<?php
	class Logging
	{
		private $logBuffer;

		function __construct( )
		{
			rawLog( '[Session Begin ' . getDate( ) . ']' );
		}

		function __destruct( )
		{
			rawLog( '[Session End]' );
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
			return "Logs\\" + strftime( "%Y-%m-%d" );
		}

		private function rawLog( $message ): void
		{
			$logFile = getLogFile( );
			$currentContents = file_get_contents( $logFile );
			if( $currentContents === FALSE )
				$currentContents = '[Log File Begin]' . PHP_EOL;

			$currentContents = $currentContents . $message . PHP_EOL;
			file_put_contents( $logFile, $currentContents );
		}

		public function log( $message ): void
		{
			return rawLog( '[' . getTime( ) . ']\t' . $_SERVER[ 'REMOTE_ADDR' ] . $message );
		}
	}
?>