<?php
header("Access-Control-Allow-Origin: *");

// Include data base connect class
$con = mysql_connect("localhost", "root", "") or die(mysql_error());
 
// Selecting database
$db = mysql_select_db("iot") or die(mysql_error()) or die(mysql_error());
 
 // Fire SQL query to get all data from kendali
$result = mysql_query("SELECT thcahaya FROM batas") or die(mysql_error());
 
// While loop to store all the returned response in variable
while ($row = mysql_fetch_array($result,MYSQL_ASSOC)){
    echo $row["thcahaya"];
}
?>