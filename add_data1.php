<?php
// https://www.developphp.com/video/JavaScript/Ajax-Post-to-PHP-File-XMLHttpRequest-Object-Return-Data-Tutorial
	// Connect to MySQL
	
	include("dbconnect.php");
	
	$counter=1;
	
	while ( isset( $_GET["analog".$counter] ) )
	{
		// Prepare the SQL statement
		//$SQL = "INSERT INTO test.temperature (sensor ,celsius) VALUES ('".$_GET["serial".$counter]."', '".$_GET["temperature".$counter]."')";     
      //	http://10.0.0.14/php/add_data1.php?serial1=111111111111111111&&temperature1=35&&id=1
	  // http://ardu.mooo.com/php/add_data.php?analog1=111&analog2=222&analog3=333&analog4=444&analog5=555&analog6=666&digital0=10&digital1=11&digital2=12&digital3=13&digital4=14&pwm0=20&pwm1=30&pwm2=40
	  
		$SQL="UPDATE test.setpoint SET analog1='".$_GET["analog1"]."', analog2='".$_GET["analog2"]."', analog3='".$_GET["analog3"]."', analog4='".$_GET["analog4"]."', analog5='".$_GET["analog5"]."', analog6='".$_GET["analog6"]."', digital0='".$_GET["digital0"]."', digital1='".$_GET["digital1"]."', digital2='".$_GET["digital2"]."', digital3='".$_GET["digital3"]."', digital4='".$_GET["digital4"]."', pwm0='".$_GET["pwm0"]."', pwm1='".$_GET["pwm1"]."', pwm2='".$_GET["pwm2"]."' WHERE id='1'";
		// Execute SQL statement
		mysql_query($SQL);
		
		// Increase counter
		$counter++;
	}
	
	// Go to the review_data.php (optional)
	header("Location: review_data1.php");
?>
