<?php
ob_start();
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//Creating Array for JSON response
$response = array();
 
// Check if we got the field from the user
if 	(isset($_GET['status'])) {
 
    $status= $_GET['status'];
    
	// Include data base connect class
	$con = mysql_connect("localhost", "root", "") or die(mysql_error());
 
    // Selecing database
    $db = mysql_select_db("iot") or die(mysql_error()) or die(mysql_error());
 
	// Fire SQL query to update aktuator status data by id
    $result = mysql_query("UPDATE aktuator SET status= '$status' WHERE id='3'");
 
    // Check for succesfull execution of query and no results found
    if ($result) {
        // successfully updation of aktuator status (status)
        $response["success"] = 1;
        $response["message"] = "aktuator Status successfully updated.";
 
        // Show JSON response
        echo json_encode($response);
    } else {
 
    }
	} 
	else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Parameter(s) are missing. Please check the request";
 
    // Show JSON response
    echo json_encode($response);
}
$host=$_SERVER['HTTP_HOST'];
header("Location: http://$host/smartroom/setting.php");
exit();
?>