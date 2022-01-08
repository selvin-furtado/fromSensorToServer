<?php

	$servername = "localhost";
	$dbname = "atalFdpTest";
	$username = "root";
	$password = "";
	$conn = new mysqli($servername, $username, $password, $dbname);
	$sql = "SELECT * FROM `serverroom` ORDER BY `id` DESC LIMIT 1;";
	$result = $conn->query($sql);
	$row = $result->fetch_assoc();
	$row_temperature = $row["temperature"];
	$row_humidity = $row["humidity"];
	$result->free();
	$conn->close();
	
	//echo json_encode(array("temp"=>$row_temperature,"hum"=> $row_humidity));
	echo $row_temperature
?>
<?php // Connection and Request stuff

	$servername = "localhost";
	$dbname = "atalFdpTest";
	$username = "root";
	$password = "";
	$conn = new mysqli($servername, $username, $password, $dbname);
	$sql = "SELECT * FROM `serverroom` ORDER BY `id` DESC LIMIT 10;";
  $req = $bdd->query($sql);

  while ($data = $req->fetch()){
      $id = addslashes($data['temperature']);
      $charge_batt = intval($data['humidity']);
      $result .= "['".$id."' , ".$charge_batt."],";
  }

  $result = substr($result, 0, -1); // Erase the last ","
  echo $result;

?>
