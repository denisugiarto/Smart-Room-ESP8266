<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//Creating Array for JSON response
$response = array();
$conn = mysqli_connect ("localhost", "root", "", "iot");

    // Fire SQL query to get weather data by id
	$result1 = mysqli_query ($conn,"SELECT suhu, cahaya FROM sensor ORDER BY id DESC LIMIT 1"); 
	$result2 = mysqli_query ($conn,"SELECT thsuhu, thcahaya FROM batas"); 	
	$result3 = mysqli_query ($conn,"SELECT nama, status FROM aktuator");
	
	$SENSOR = array();
	$TRESHOLD = array();
	$AKTUATOR = array();

	// Storing the returned array in response
	$response["SENSOR"] = array();
	$row1 = mysqli_fetch_array($result1);
	$SENSOR["suhu"] 	= $row1["suhu"];
	$SENSOR["cahaya"] 	= $row1["cahaya"];
	array_push($response["SENSOR"]  , $SENSOR);
	
	$response["TRESHOLD"] = array();
	$row2 = mysqli_fetch_array($result2);
	$TRESHOLD["suhu"] 	  = $row2["thsuhu"];
	$TRESHOLD["cahaya"]   = $row2["thcahaya"];
	array_push($response["TRESHOLD"], $TRESHOLD);
	
	$response["AKTUATOR"] = array();
	while ($row3 = mysqli_fetch_assoc($result3)){
	$AKTUATOR["nama"] = $row3["nama"];
	$AKTUATOR["status"] = $row3["status"];
	array_push($response["AKTUATOR"], $AKTUATOR);
	}	
    // Show JSON response
    echo json_encode($response);
?>