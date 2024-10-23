<?php
$config = parse_ini_file("config.ini");
print('PHP SCRIPT');

// print($config['database']);
// $f = fopen( 'php://stdin', 'r' );
// while( $line = fgets( $f ) ) {
//   echo $line;
// }


if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  echo "Received POST data:\n";
  $uploaddir = $config['database'];

  $uploadfile = $uploaddir . basename($_FILES['filename']['name']);

  print_r($uploadfile);

  echo '<pre>';
  if (move_uploaded_file($_FILES['filename']['tmp_name'], $uploadfile)) {
      echo "File is valid, and was successfully uploaded.\n";
  } else {
      echo "Possible file upload attack!\n";
  }

echo 'Here is some more debugging info:';
print_r($_FILES);

print "</pre>";
  // print_r($_SERVER);
  // print_r($_GET);
  // print_r($_POST);
  // print_r($_FILES);
} else {
  echo "No POST data received.";
}


print('/PHP SCRIPT');

// fclose( $f );

// print "one";
// include 'b.php';
// print "three";
?>
