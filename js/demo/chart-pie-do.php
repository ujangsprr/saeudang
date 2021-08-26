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

$data = mysqli_query($connection, "SELECT * FROM `data_oxg` ORDER BY `data_oxg`.`id` DESC LIMIT 1");
  while($p = mysqli_fetch_array($data)) {
?>

// Set new default font family and font color to mimic Bootstrap's default styling
Chart.defaults.global.defaultFontFamily = 'Nunito', '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
Chart.defaults.global.defaultFontColor = '#858796';

// Pie Chart Example
var ctx = document.getElementById("myPieChart");
var myPieChart = new Chart(ctx, {
  type: 'doughnut',
  data: {
    labels: ["Kebutuhan", "Tersedia", "Kurang"],
    datasets: [{
      data: [<?php echo '"' .$p['kebutuhan'].'",'; echo '"' .$p['do'].'",'; echo '"' .$p['kurang'].'",';}?>],
      backgroundColor: ['#4e73df', '#1cc88a', '#36b9cc'],
      hoverBackgroundColor: ['#2e59d9', '#17a673', '#2c9faf'],
      hoverBorderColor: "rgba(234, 236, 244, 1)",
    }],
  },
  options: {
    maintainAspectRatio: false,
    tooltips: {
      backgroundColor: "rgb(255,255,255)",
      bodyFontColor: "#858796",
      borderColor: '#dddfeb',
      borderWidth: 1,
      xPadding: 15,
      yPadding: 15,
      displayColors: false,
      caretPadding: 10,
    },
    legend: {
      display: false
    },
    cutoutPercentage: 80,
  },
});