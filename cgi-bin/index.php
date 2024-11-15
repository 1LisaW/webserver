<?php
$config = parse_ini_file(".user.ini");
$uploaddir = $config['database'];


if ($_SERVER['REQUEST_METHOD'] == 'GET')
{
  if ($_GET && $_GET['filename'])
  {
    $filename =  $uploaddir . $_GET['filename'];;
    if (file_exists($filename) && is_file($filename))
    {
      header('Status: 200 OK');
      $cont_disp = "attachment; filename=" . $_GET['filename'];
      header("Content-Disposition: $cont_disp");
      $size = filesize($filename);
      header("Content-length: $size");
      readfile($filename);
    }
    else if (!is_file($filename))
    {
      header('Status: 404 Not Found');
    }
    exit();
  }

  http_response_code(200);
  header('Status: 200 OK');
  include('./upload_listing/upload_listing.php');

  exit();

}
if ($_SERVER['REQUEST_METHOD'] == 'DELETE')
{
  // printf("DELETE!!!");
  // printf($_SERVER['QUERY_STRING']);
  $filename = $uploaddir . $_GET['filename'];
  if (file_exists($filename) && is_file($filename))
  {
    unlink($filename);
    header('Status: 200 OK');
    header('Content-length: 0');
  }
  else
  {
    header('Status: 204 No Content');
  }
  // printf($filename);
  // print_r($_SERVER);
  // print_r($_GET);
  // print_r($_POST);
  // print_r($_FILES);
  // print_r($_ENV);
  // print_r($_FILES['filename']['error']);
  exit();

  // if (file_exists($uploadfile))
  // {

  // }
  // else{

  // }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  // echo "Received POST data:\n";

  $uploadfile = $uploaddir . basename($_FILES['filename']['name']);

   if (move_uploaded_file($_FILES['filename']['tmp_name'], $uploadfile)) {
    http_response_code(200);
    header($_SERVER['SERVER_PROTOCOL'] . '200 OK');
    // header('Location: https://localhost:5000');

    ob_start();
    echo "<head>";
    echo '<meta http-equiv="refresh" content="0; url=//localhost:5000/" /> ';
    echo "</head>";
    echo "<div>";
    echo "File is valid, and was successfully uploaded.\n";
    echo "</div>";
    // print('\0');
    ob_end_flush();

  } else {
    print_r($_FILES['filename']['error']);
    http_response_code(404);
    header($_SERVER["SERVER_PROTOCOL"] . "404 Not Found");
    ob_start();
    echo "<div>";
      echo "Possible file upload attack!\n";
    echo "</div>";
    print('\0');
    ob_end_flush();
  }

// echo 'Here is some more debugging info:';
// print_r($_FILES);

// print "</pre>";
  print_r($_SERVER);
  print_r($_GET);
  print_r($_POST);
  print_r($_FILES);
  print_r($_ENV);
  print_r($_FILES['filename']['error']);
} else {
  echo "No POST data received.";
}
// echo "this is the page content";
// header('Content-Length: '.ob_get_length());
// var_dump(http_response_code());
// print($http_response_header);

// print('/PHP SCRIPT');
// fclose( $f );

// print "one";
// include 'b.php';
// print "three";
// header('Location: http://stackoverflow.com');
exit();
?>
