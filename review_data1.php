
<?php 
// https://www.developphp.com/video/JavaScript/Ajax-Post-to-PHP-File-XMLHttpRequest-Object-Return-Data-Tutorial
	// Start MySQL Connection
	
	// http://ardu.mooo.com/php/review_data1.php
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
		
		//echo '   <td'.$css_class.'>'.$row["id"].'</td>';
		//echo '   <td'.$css_class.'>'.$row["event"].'</td>';
		//echo '   <td'.$css_class.'>'.$row["valueset"].'</td>';
		//echo '   <td'.$css_class.'>'.$row["units"].'</td>';
		}
	}
?>
