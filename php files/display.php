<!DOCTYPE html>
<html>
<head>
<title> Access Log</title>
<style>
	body {
		width: 35em;
		margin: 0 auto;
		font-family: Tahoma, Verdana, Arial, sans-serif;
		font-size: 30px;
	}
</style>
<meta http-equiv="refresh" content="2">
</head>
<body>
<h1> Access Logs </h1>
<?php

$servername = "localhost";
// REPLACE with your Database name
$dbname = "atalFdpTest";
// REPLACE with Database user
$username = "root";
// REPLACE with Database user password
$password = "";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
	echo "DB connection failed";
} 

$sql = "SELECT * FROM serverroom ORDER BY id DESC LIMIT 5";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td> ID</td> 
        <td> Sensor</td> 
        <td> Location</td> 
        <td> Temperature</td> 
        <td> Humidity</td> 
        <td> Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_mote = $row["mote"];
        $row_location = $row["location"];
        $row_temperature = $row["temperature"];
        $row_humidity = $row["humidity"];
        $row_reading_time = $row["readingTime"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_mote . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_temperature . '</td> 
                <td>' . $row_humidity . '</td>
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
