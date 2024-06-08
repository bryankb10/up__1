<?php
include 'phpqrcode/qrlib.php';
$hostname = gethostname();
$ipAddress = gethostbyname($hostname);

$content = 'http://'. $ipAddress .'/restaurant/menurestaurant.php';
$historyqr = 'http://'. $ipAddress .'/restaurant/orderHistory.php';
$filepath = 'qrcode.png';
$filepath_2 = 'historyqrcode.png';
QRcode::png($content, $filepath);
QRcode::png($history, $filepath_2);
header('Content-Type: image/png');
readfile($filePath);
readfile($filepath_2);
?>