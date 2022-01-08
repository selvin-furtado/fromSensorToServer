<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "atalFdpTest";
// REPLACE with Database user
$username = "root";
// REPLACE with Database user password
$password = "";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "xxxxxxx";

$api_key = $mote = $location = "";
$temperature = $humidity = $doorStatus = "";
$counter=0;
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if (isset($_POST["api_key"])){
		$api_key = test_input($_POST["api_key"]);
		if($api_key == $api_key_value) {
			if (isset($_POST["mote"])){
				$mote = test_input($_POST["mote"]);
				$counter+=5;
			}
			
			if (isset($_POST["location"])){
				$location = test_input($_POST["location"]);
				$counter+=5;
			}
			
			if (isset($_POST["temperature"])){
				$temperature = test_input($_POST["temperature"]);
				$counter+=1;
			}
			
			if (isset($_POST["humidity"])){
				$humidity = test_input($_POST["humidity"]);
				$counter+=1;
			}
			
			if (isset($_POST["doorStatus"])){
				$doorStatus = test_input($_POST["doorStatus"]);
				$counter+=1;
			}
			
			if($counter>10){
				// Create connection
				$conn = new mysqli($servername, $username, $password, $dbname);
				// Check connection
				if ($conn->connect_error) {
					die("Connection failed: " . $conn->connect_error);
				} 
				
				$sql = "INSERT INTO serverroom(mote, location, temperature, humidity, doorStatus) 
					VALUES('". $mote ."','". $location ."','". $temperature ."','". $humidity ."','". $doorStatus ."')";
				if ($conn->query($sql) === TRUE) {
					echo "New record created successfully";
				} 
				else {
					echo "Error: " . $sql . "<br>" . $conn->error;
				}
			
				$conn->close();
			}else{
				echo "Insufficient Data.";
			}
		}
		else {
			echo "Wrong API Key provided.";
		}
	}else{
		echo "User authentication failed";
	}

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
