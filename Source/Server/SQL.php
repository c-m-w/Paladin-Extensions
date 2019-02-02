<?php
	require 'public_html/src/config.php';

	class SQLConnection
	{
		private $sqlConnection;

		function __construct( )
		{
			$sqlConnection = new mysqli( $config[ 'db' ][ 'host' ], $config[ 'db' ][ 'username' ], $config[ 'db' ][ 'password' ], $config[ 'db' ][ 'dbname' ] )
		}

		public function escape( $string ): string
		{
			return $sqlConnection->escape_string( $string );
		}

		public function selectRows( $rows, $table, $conditions )
		{
			return $sqlConnection->query( 'SELECT ' . $rows . ' FROM ' . $table . ' WHERE ' . $conditions );
		}

		public function insertRow( $table, $values )
		{
			return $sqlConnection->query( 'INSERT INTO ' . $table . ' VALUES (' . $values . ')');
		}

		public function updateRow( $table, $column, $value, $conditions )
		{
			return $sqlConnection->query( 'UPDATE ' . $table . ' SET ' . $column . ' = "' . $value . '" WHERE ' . $conditions );
		}
	}
?>