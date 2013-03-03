
// Checklogin.php
############### Code

<?php
include('config.php');

// username and password sent from form 
$myusername=$_POST['myusername']; 
$mypassword=$_POST['mypassword']; 

// MD5 username and password
$encrypted_mypassword=md5($mypassword);
$encrypted_myusername=$myusername;

// To protect MySQL injection (more detail about MySQL injection)
$ecrypted_myusername = stripslashes($encrypted_myusername);
$encrypted_mypassword = stripslashes($encrypted_mypassword);
$encrypted_myusername = mysql_real_escape_string($encrypted_myusername);
$encrypted_mypassword = mysql_real_escape_string($encrypted_mypassword);
$sql="SELECT * FROM $tbl_name WHERE username='$encrypted_myusername' and pass='$encrypted_mypassword'";
$result=mysql_query($sql);

// Mysql_num_row is counting table row
$count=mysql_num_rows($result);

// If result matched $myusername and $mypassword, table row must be 1 row
if($count==1){

// Register $myusername, $mypassword and redirect to file "login_success.php"
session_register("myusername");
session_register("mypassword"); 
header("location:login_success.php");
}
else {
echo "Wrong Username or Password";
}
?>
