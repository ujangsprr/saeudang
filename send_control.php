<?php
if(isset($_GET['venturi']) && isset($_GET['state'])){
    include 'connect.php';

    $state = $_GET['state'];
    $venturi = $_GET['venturi'];

    if($venturi == '1'){
        mysqli_query($connection, "UPDATE `control_oxg` SET ven1='$state'");
    }else if($venturi == '2'){
        mysqli_query($connection, "UPDATE `control_oxg` SET ven2='$state'");
    }else if($venturi == '3'){
        mysqli_query($connection, "UPDATE `control_oxg` SET ven3='$state'");
    }else if($venturi == '4'){
        mysqli_query($connection, "UPDATE `control_oxg` SET ven4='$state'");
    }else if($venturi == 'all'){
        mysqli_query($connection, "UPDATE `control_oxg` SET ven1='$state'");
        mysqli_query($connection, "UPDATE `control_oxg` SET ven2='$state'");
        mysqli_query($connection, "UPDATE `control_oxg` SET ven3='$state'");
        mysqli_query($connection, "UPDATE `control_oxg` SET ven4='$state'");
    }
    header('location: control.php');
    exit;
}
?>