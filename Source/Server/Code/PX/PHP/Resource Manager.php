<?php
    define( "resourceFolderName", "Resources" );
    define( "resourceFolder", "/home/palavpvb/PX/" . resourceFolderName );

    class ResourceManager
    {
        private $data;

        private function getFilesInDirectory( $directory ): void
        {
            $files = scandir( $directory );

            foreach ( $files as $file )
				if ( !is_dir( $directory . '/' . $file ) )
                {
                    $relativeFolder = substr( $directory, strlen( resourceFolder ) - strlen( resourceFolderName ) );
                    $path = substr( str_replace( '/', '\\', $relativeFolder ) . '\\' . $file, strlen( resourceFolderName ) + 1 );
                    $filePath = $directory . '/' . $file;
                    $data = file_get_contents( $filePath );
                    $this->data[ ] = array( "Path" => $path, "Data" => base64_encode( $data ) );
                }
        }

        private function getFoldersInDirectory( $directory )
        {
            $files = scandir( $directory );
            $return = array( );

            foreach ( $files as $file )
                if ( is_dir( $file ) && $file != '.' && $file != '..' )
                    $return[ ] = $file;

            return sizeof( $return ) == 0 ? NULL : $return;
        }

        private function getResourceFiles( $directory = resourceFolder ): void
        {
            $oldDirectory = realpath( '' );
            chdir( $directory );
            if ( $directory == resourceFolder )
            {
				// Reset everything
                $this->count = 0;
                $this->data = array( );
            }

            $this->getFilesInDirectory( $directory );
            $folders = $this->getFoldersInDirectory( $directory );
            if ( $folders === NULL )
                return;

            foreach ( $folders as $folder )
                $this->getResourceFiles( $directory . '/' . $folder );

            chdir( $oldDirectory );
        }

        public function getResourceHashes( ): string
        {
            $hash = array( );

            $this->getResourceFiles( );
            foreach ( $this->data as $file )
                $hash[ ] = array( 'Path' => $file[ 'Path' ], 'Hash' => sha1( base64_decode( $file[ 'Data' ] ) ) );

            return json_encode( $hash );
        }

        public function getResourceData( ): string
        {
            $this->getResourceFiles( );
            return json_encode( $this->data );
        }
    }
?>