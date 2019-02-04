<?php
    define( "resourceFolderName", "Resources" );
    define( "resourceFolder", "/home/palavpvb/PX/" . resourceFolderName );

    class ResourceManager
    {
        private $count;
        private $data;

        private function getFilesInDirectory( $directory ): void
        {
            $files = scandir( $directory );

            foreach ( $files as $file )
                if ( !is_dir( realpath( $file ) ) )
                    $return[ $this->count++ ] = $file;
        }

        private function getFoldersInDirectory( $directory ): array
        {
            $files = scandir( $directory );
            $return = array( );
            $count = 0;

            foreach ( $files as $file )
                if ( is_dir( realpath( $file ) ) )
                    $return[ $count++ ] = $file;

            return $return;
        }

        private function getResourceFiles( $directory = resourceFolder ): void
        {
            $current = realpath( '' );
            chdir( $directory );
            $this->getFilesInDirectory( $directory );
            foreach ( $this->getFoldersInDirectory( $directory ) as $folder )
            {
                echo $folder . ' ';
                $this->getResourceFiles( $folder );
            }

            chdir( $current );
        }

        public function getResourceHashes( ): string
        {
            $this->count = 0;
            $this->data = array( );
            return '';
        }

        public function getResourceData( ): string
        {
            $this->count = 0;
            $this->data = array( );
            $this->getResourceFiles( );

            return json_encode( $this->data );
        }
    }
?>