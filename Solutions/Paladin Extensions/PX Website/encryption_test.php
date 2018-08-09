<?php
    require "include.php";
    $result = GetIPInformation( );
    echo $result[ "countryName" ];
?>