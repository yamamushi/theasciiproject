// config.php
<?php

$host="localhost"; // Host name 
$username="mysql"; // Mysql username 
$password=""; // Mysql password 
$db_name="ascii_project"; // Database name 
$tbl_name="users"; // users table name

//Connect to server and select database.
mysql_connect("$host", "$username", "$password")or die("cannot connect to server"); 
mysql_select_db("$db_name")or die("cannot select DB");

?>
