<?php
    require "include.php";

    $keys = GenerateKeys( );
   echo openssl_encrypt( "biohazard is a huge fucking faggot", EncryptionMethod, $keys[ "key" ], 0, $keys[ "iv" ] );
?>