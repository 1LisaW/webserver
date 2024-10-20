<?php
$f = fopen( 'php://stdin', 'r' );

while( $line = fgets( $f ) ) {
  echo $line;
}

fclose( $f );
// print "one";
// include 'b.php';
// print "three";
?>
