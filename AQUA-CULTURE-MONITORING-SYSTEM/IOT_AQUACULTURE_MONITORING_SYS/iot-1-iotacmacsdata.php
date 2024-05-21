<!DOCTYPE html>
<html>
    <head>
        
        <meta http-equiv="refresh" content="1" >
        <title>IOT BASED AQUA CULTURE MONITORING AND CONTROLLING SYSTEM</title>
        <meta name="viewport" content="width=device-width, initial-scale=0.1, maximum-scale=0.1, user-scalable=no">
 
    <style>
        .parameter {
            margin-bottom: 10px;
        }
        .parameter label {
            display: inline-block;
            width: 120px;
            font-weight: bold;
        }
        .parameter-value {
            margin-left: 10px;
        }
    </style>

        <head\>
<body>
           <style>
  main {
    background: #d9d7d5;
    display: flex;
    flex-wrap: wrap;
    justify-content: space-between;
  }

  div {
    background: #767775;
    flex-basis: 100%;
    height: 100px;
    margin-bottom: 0.5rem;
  }

  @media (min-width: 600px) {
    main {
      flex-wrap: nowrap;
    }

    div {
      flex-basis: 33%;
    }
  }
</style>
 
  <body style="background-color:#6ed3cf">
  <font color="BLUE"> <h1>IOT BASED AQUA CULTURE MONITORING AND CONTROLLING SYSTEM</h1> </font>
 
   <style>
    body {
      min-width: 310px;
    	max-width: 800px;
    	height: 400px;
      margin: 0 auto;
    }
    h1 {
      font-family: Arial;
      font-size: 4rem;
      text-align: center;
    }
     
  </style>
  
  
  

<style>

.box{
    background-color: white;
    border-radius: 50px;
    border: none;
    color: BLACK;
    padding: 28px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 30px;
    margin: 4px 2px;
    
}
</style>

   <?php
   
    // Define the parameters
    $parameters = array(
        "Parameter 1" => "Value 1",
        "Parameter 2" => "Value 2",
        "Parameter 3" => "Value 3",
        "Parameter 4" => "Value 4",
        "Parameter 5" => "Value 5",
        "Parameter 6" => "Value 6",
        "Parameter 7" => "Value 7",
        "Parameter 8" => "Value 8",
        "Parameter 9" => "Value 9",
        "Parameter 10" => "Value 10"
    );
   
   
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

$servername = "localhost";

// REPLACE with your Database name
$dbname = "u220614042_iotacmacs";
// REPLACE with Database user
$username = "u220614042_iotacmacs";
// REPLACE with Database user password
$password = "Mahesh@416";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, sensor, location, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, reading_time FROM SensorData ORDER BY id DESC LIMIT 1";

if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_sensor = $row["sensor"];
        $row_location = $row["location"];
        $row_value1 = $row["value1"];
        $row_value2 = $row["value2"]; 
        $row_value3 = $row["value3"]; 
        $row_value4 = $row["value4"];
        $row_value5 = $row["value5"]; 
        $row_value6 = $row["value6"]; 
        $row_value7 = $row["value7"];
        $row_value8 = $row["value8"]; 
        $row_value9 = $row["value9"]; 
        $row_value10 = $row["value10"]; 
        //$row_reading_time = $row["reading_time"];
        $row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 330 minutes"));
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
    }

    $result->free();
}

$conn->close();
?> 

   
    
    <span class='box' ><img src="iot-1-iotacmacs-images/PHSENSOR.png" width="200" height="200" ><br>Ph</span>
    <span class='box' ><?php echo $row_value1; ?>PH</span><br>
   
    
  
    <span class='box' ><img src="iot-1-iotacmacs-images/TDSSENSOR.png" width="200" height="200" ><br>TDS</span>
    <span class='box' ><?php echo $row_value3; ?>PPM</span><br>

    
    
    <span class='box' ><img src="iot-1-iotacmacs-images/TEMP.gif" width="200" height="200" > <br>TEMP</span>
    <span class='box' ><?php echo $row_value4; ?>°C</span><br>
    
    
   
    <span class='box' ><img src="iot-1-iotacmacs-images/TUBIDITYSENSOR.png" width="200" height="200" ><br>TURB</span>
    <span class='box' ><?php echo $row_value2; ?>NTU</span>
    

</table>

</body>

</html>