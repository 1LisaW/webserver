<?php
$config = parse_ini_file(".user.ini");
$uploaddir = $config['database'];
$maxFileSize = 3 * 1024 * 1024; // 2MB

if ($_SERVER['REQUEST_METHOD'] == 'GET')
{
  if ($_GET && $_GET['filename'])
  {
    $filename =  $uploaddir . $_GET['filename'];;
    if (file_exists($filename) && is_file($filename))
    {
      $size = filesize($filename);
      if ($size > $maxFileSize)
      {
        header("HTTP/1.0 500 Internal Server Error");
        exit();
      }
      header('Status: 200 OK');
      $cont_disp = "attachment; filename=" . $_GET['filename'];
      header("Content-Disposition: $cont_disp");
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

  exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

  $uploadfile = $uploaddir . basename($_FILES['filename']['name']);

   if (move_uploaded_file($_FILES['filename']['tmp_name'], $uploadfile)) {
    http_response_code(200);
    header($_SERVER['SERVER_PROTOCOL'] . '200 OK');

    ob_start();
    echo "<head>";
    echo '<meta http-equiv="refresh" content="0; url=//localhost:5000/" /> ';
    echo "</head>";
    echo "<div>";
    echo "File is valid, and was successfully uploaded.\n";
    echo "</div>";
    ob_end_flush();
    exit();
  }
  else {
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
}

exit();
?>
