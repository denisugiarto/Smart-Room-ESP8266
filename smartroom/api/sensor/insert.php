<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//Creating Array for JSON response
$response = array();
 
// Check if we got the field from the user
if (isset($_GET['suhu']) && isset($_GET['cahaya'])) {
 
    $suhu = $_GET['suhu'];
    $cahaya = $_GET['cahaya'];
 
	// Include data base connect class
	$con = mysql_connect("localhost", "root", "") or die(mysql_error());
 
    // Selecing database
    $db = mysql_select_db("iot") or die(mysql_error()) or die(mysql_error());
 
    // Fire SQL query to insert data in weather
    $result = mysql_query("INSERT INTO sensor(suhu,cahaya) VALUES('$suhu','$cahaya')");
 
    // Check for succesfull execution of query
    if ($result) {
        // successfully inserted 
        $response["success"] = 1;
        $response["message"] = "Data Sensor Berhasil Terkirim.";
 
        // Show JSON response
        echo json_encode($response);
    } else {
        // Failed to insert data in database
        $response["success"] = 0;
        $response["message"] = "Error";
 
        // Show JSON response
        echo json_encode($response);
    }
} else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Masukkan salah";
 
    // Show JSON response
    echo json_encode($response);
}
?>