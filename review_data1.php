
<?php 
// https://www.developphp.com/video/JavaScript/Ajax-Post-to-PHP-File-XMLHttpRequest-Object-Return-Data-Tutorial
	// Start MySQL Connection
	
	// http://ardu.mooo.com/php/review_data1.php
	header("Access-Control-Allow-Origin: *");
	include('dbconnect.php'); 

	// Retrieve all records and display them
	$result = mysql_query("SELECT * FROM setpoint ORDER BY id ASC");
	
	// Used for row color toggle
	$oddrow = true;
	
	// process every record
	while( $row = mysql_fetch_array($result) )
	{
		if ($oddrow) 
		{ 
			$css_class=' class="table_cells_odd"'; 
		}
		else
		{ 
			$css_class=' class="table_cells_even"'; 
		}
		
		$oddrow = !$oddrow;
		if ($row["id"] == '1') {
		// XML 
		/* echo '<?xml version = "1.0" ?>';
		echo '<inputs>';
		echo '<analog>'.$row["analog1"].'</analog>';
		echo '<analog>'.$row["analog2"].'</analog>';
		echo '<analog>'.$row["analog3"].'</analog>';
		echo '<analog>'.$row["analog4"].'</analog>';
		echo '<analog>'.$row["analog5"].'</analog>';
		echo '<analog>'.$row["analog6"].'</analog>';
		echo '<analog>'.$row["digital0"].'</analog>';
		echo '<analog>'.$row["digital1"].'</analog>';
		echo '<analog>'.$row["digital2"].'</analog>';
		echo '<analog>'.$row["digital3"].'</analog>';
		echo '<analog>'.$row["digital4"].'</analog>';
		echo '<analog>'.$row["pwm0"].'</analog>';
		echo '<analog>'.$row["pwm1"].'</analog>';
		echo '<analog>'.$row["pwm2"].'</analog>';
		echo '</inputs>';
		*/
		// http://www.w3schools.com/json/json_example.asp  
		$outp = "[";
		$outp .= '{"analog1":"'  . $row["analog1"] . '",';
		$outp .= '"analog2":"'   . $row["analog2"] . '",';
		$outp .= '"analog3":"'   . $row["analog3"] . '",';
		$outp .= '"analog4":"'   . $row["analog4"] . '",';
		$outp .= '"analog5":"'   . $row["analog5"] . '",';
		$outp .= '"analog6":"'   . $row["analog6"] . '"},'; 
		$outp .= '{"digital0":"'  . $row["digital0"] . '",';
		$outp .= '"digital1":"'   . $row["digital1"] . '",';
		$outp .= '"digital2":"'   . $row["digital2"] . '",';
		$outp .= '"digital3":"'   . $row["digital3"] . '",';
		$outp .= '"digital4":"'   . $row["digital4"] . '"},';
        $outp .= '{"pwm0":"'  . $row["pwm0"] . '",';
		$outp .= '"pwm1":"'   . $row["pwm1"] . '",';
		$outp .= '"pwm2":"'   . $row["pwm2"] . '"}';		
		$outp .="]";
		echo($outp);

		//echo '   <td'.$css_class.'>'.$row["id"].'</td>';
		//echo '   <td'.$css_class.'>'.$row["event"].'</td>';
		//echo '   <td'.$css_class.'>'.$row["valueset"].'</td>';
		//echo '   <td'.$css_class.'>'.$row["units"].'</td>';
		}
	}
?>
