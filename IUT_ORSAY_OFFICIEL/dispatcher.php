<?php
#######################################################################################
# File: dispatcher.php(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Gestion du menu d'administration.
#######################################################################################
#
#~~~~~~
# Init
#~~~~~~~
if (! isset($_POST["OP"])) {
	exit;
}
#
$OnLoad = "";
$IMAGES = "./images";
$uid = 0; # When Cookie is gone
$LOGIN = "nobody";
$LEVEL = 9;
#
session_start();
set_time_limit(180);
#
set_include_path("./include4IUT99532");
include_once "main.php";
include_once("colors.default");
$activeDB = $TOOLDB;
if (isset($uid)) {
  $QUERY = "SELECT level FROM $IDENTIFIER_TABLE WHERE uid=$uid";
  QUERY($QUERY);
  if ($MAX > 0) {
    $LEVEL = RESULT(0,0);
  }
}
#
$common = "https://" . $_SERVER["HTTP_HOST"] . dirname($_SERVER["SCRIPT_NAME"]);
#
header("Cache-Control:no-cache");
switch ($OP) {
case "authenticate":
case "login":
	break;

default:
	$body = 1;
	echo "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>
	<html lang='fr_FR'>
	<head>
	<META HTTP-EQUIV='expires' CONTENT='-1'>
	<META HTTP-EQUIV='Pragma' CONTENT='no-cache'>
	<meta http-equiv='content-type' content='text/html; charset=utf8'>

	<link rel=stylesheet type='text/css' href='css/basic.css'>
	<script language=JavaScript>var ajax = './ajax.php';</script>
	<script type='text/javascript' language=JavaScript src='$xmlObjects'></script>
	</head>

	<body id=blank style='border:0px solid black;margin:0px;padding:1px;z-index:2;overflow-x:hidden;background-color:#000080;'
		OnLoad=\"$OnLoad\">\n\n";
}

if (isset($innerREQ)) {
	include_once "adm_inner.php";
}
else {
	echo "<pre>";print_r($_POST);exit;
	echo "<FORM name=swap id=swap TARGET=_top action='index.php' method=POST></FORM>
	<script>
	document.getElementById('swap').submit();
	</script>\n";
}
#
if ($LEVEL < 1) {
  echo "<script>allow_right_mouse = 1;</script>";
}
echo "
<script language=JavaScript>
var login = '$LOGIN';
</script>
</body></html>\n";
?>
