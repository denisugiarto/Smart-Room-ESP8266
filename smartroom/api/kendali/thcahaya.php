<?php
ob_start();
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//Creating Array for JSON response
$response = array();
 
// Check if we got the field from the user
if (isset($_GET['batas'])) {
    $thcahaya= $_GET['batas'];
	// Include data base connect class
	$con = mysql_connect("localhost", "root", "") or die(mysql_error());
 
    // Selecing database
    $db = mysql_select_db("iot") or die(mysql_error()) or die(mysql_error());
 
	// Fire SQL query to update treshold cahaya
    $result = mysql_query("UPDATE batas SET thcahaya= '$thcahaya'");
 
    // Check for succesfull execution of query and no results found
    if ($result) {
        // successfully updation of LED status (status)
        $response["success"] = 1;
        $response["message"] = "nilai batas cahaya updated.";
 
        // Show JSON response
        echo json_encode($response);
    } else {}
} else {
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

