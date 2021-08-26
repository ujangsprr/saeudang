<?php
$dbhost = 'localhost';
$dbuser = 'root';
$dbpswd = '';
$dbname = 'saeudang';

// $dbhost = 'sql104.epizy.com';
// $dbuser = 'epiz_29335770';
// $dbpswd = '7CLjfSrPLZx';
// $dbname = 'epiz_29335770_saeudang';

$connection = mysqli_connect($dbhost, $dbuser, $dbpswd, $dbname);  
 if(!$connection) {
    die("Database connection failed");
}

?>
