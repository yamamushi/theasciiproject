// signup_ac.php

############### Code

<?php

include('config.php');

// table name 
$tbl_name2=temp_members_db;

// Random confirmation code 
$confirm_code=md5(uniqid(rand())); 
$registered=date("y-m-d h:i:s"); // date and time user registration sent to server
// values sent from form 
$name=$_POST['name'];
$name_enc=$name;
$email=$_POST['email'];
$country=$_POST['country'];
$password=$_POST['password'];
$password_encrypted=md5($password);

// Insert data into database 
$sql="INSERT INTO $tbl_name2(confirm_code, name, email, password, country, registered)VALUES('$confirm_code', '$name_enc', '$email', 
'$password_encrypted', '$country', '$registered')";
$result=mysql_query($sql);

// if suceesfully inserted data into database, send confirmation link to email 
if($result){
// ---------------- SEND MAIL FORM ----------------

// send e-mail to ...
$to=$email;

// Your subject
$subject="Your confirmation link here";

// From
$header="from: no-reply@theasciiproject.org";

// Your message
$message="Your Comfirmation link \r\n";
$message.="Click on this link to activate your account \r\n";
$message.="http://www.yourweb.com/confirmation.php?passkey=$confirm_code";

// send email
$sentmail = mail($to,$subject,$message,$header);
}

// if not found 
else {
echo "Not found your email in our database";
}

// if your email succesfully sent
if($sentmail){
echo "Your Confirmation link Has Been Sent To Your Email Address.";
}
else {
echo "Cannot send Confirmation link to your e-mail address";
}
?>
