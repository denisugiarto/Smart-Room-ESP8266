<?php 
	$ip= $_SERVER["HTTP_HOST"];
?>
<link href="icon/icon.png" rel="shortcut icon">
<?php
$host		= "localhost";
$username 	= "root";
$pass		= "";
$db_name	= "iot";

$conn		=mysqli_connect($host, $username, $pass);
mysqli_select_db($conn, $db_name);
?>
