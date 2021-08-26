<?php
if(isset($_POST['token'])){
    include 'connect.php';
    $key = $_POST['token'];

    $sql = mysqli_query($connection, "SELECT * FROM `control_oxg` WHERE token='$key'");
    $query = mysqli_num_rows($sql);

    if($query > 0){
        $data = mysqli_fetch_assoc($sql);
    }else{
        $data = ["token" => "Not Valid"];
    }
    $res = json_encode($data);
    echo $res;
}
?>