<?php
include 'connect.php';

$hari = mysqli_real_escape_string($connection, $_REQUEST['hari']);
$tanggal = mysqli_real_escape_string($connection, $_REQUEST['tanggal']);
$kondisi = mysqli_real_escape_string($connection, $_REQUEST['kondisi']);
$kebutuhan = mysqli_real_escape_string($connection, $_REQUEST['kebutuhan']);
$kurang = mysqli_real_escape_string($connection, $_REQUEST['kurang']);
$do = mysqli_real_escape_string($connection, $_REQUEST['do']);
$ds = mysqli_real_escape_string($connection, $_REQUEST['ds']);
$temp = mysqli_real_escape_string($connection, $_REQUEST['temp']);
$presentase = mysqli_real_escape_string($connection, $_REQUEST['presentase']);

$sql = "INSERT INTO `data_oxg` (`id`, `hari`, `tanggal`, `kondisi`, `kebutuhan`, `kurang`, `do`, `ds`, `temp`, `presentase`) VALUES (NULL, '$hari', '$tanggal', '$kondisi', '$kebutuhan', '$kurang', '$do', '$ds', '$temp', '$presentase');";

if(mysqli_query($connection, $sql)){
    echo "Records added successfully.";
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($connection);
}

mysqli_close($connection);
?>