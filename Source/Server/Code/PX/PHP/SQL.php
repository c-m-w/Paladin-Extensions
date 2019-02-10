<?php
    include '/home/palavpvb/public_html/src/config.php';

	class SQLConnection
	{
		private $sqlConnection;

		function __construct( )
		{
            global $config;

			$this->sqlConnection = new mysqli( 'localhost', 'palavpvb_admin', '_paladin_ext()++', 'palavpvb_xenforo' );
            if ( $this->sqlConnection->connect_error )
                $this->sqlConnection = new mysqli( $config[ 'db' ][ 'host' ], $config[ 'db' ][ 'username' ], $config[ 'db' ][ 'password' ], $config[ 'db' ][ 'dbname' ] );
		}

		public function escape( $string ): string
		{
			return $this->sqlConnection->escape_string( $string );
		}

		public function selectRows( $rows, $table, $conditions )
		{
			return $this->sqlConnection->query( 'SELECT ' . $rows . ' FROM ' . $table . ' WHERE ' . $conditions );
		}

		public function insertRow( $table, $values )
		{
			return $this->sqlConnection->query( 'INSERT INTO ' . $table . ' VALUES (' . $values . ')');
		}

		public function updateRow( $table, $column, $value, $conditions )
		{
			return $this->sqlConnection->query( 'UPDATE ' . $table . ' SET ' . $column . ' = "' . $value . '" WHERE ' . $conditions );
		}
	}
?>