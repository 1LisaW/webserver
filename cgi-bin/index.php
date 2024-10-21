<?php
$config = parse_ini_file("config.ini");
print('PHP SCRIPT');

print($config['database']);
$f = fopen( 'php://stdin', 'r' );
while( $line = fgets( $f ) ) {
  echo $line;
}

// fclose( $f );

// print "one";
// include 'b.php';
// print "three";
?>
