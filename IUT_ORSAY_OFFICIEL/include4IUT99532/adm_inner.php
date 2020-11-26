<?php
###########################################################################################
# File   : adm_inner.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# Distribution des tâches.
# -----------------------------------------------------------------------------------------
#
# Init
if (isset($_SESSION["LEVEL"])) $LEVEL = $_SESSION["LEVEL"];
if (isset($LOGIN))  $trueLOGIN = $LOGIN;
include "colors.default";
$remote = $_SERVER["REMOTE_ADDR"];
$now = date("Y/m/d H:i:s");
#
$GLOBALS["SQL_SOURCE"] = "OSE:adm_inner";
$activeDB = $TOOLDB;
#
$DEBUG = 0;
if ($DEBUG == 1) {
	echo "<pre>";
	print_r($_POST);
	exit;
}
#
switch ($mode) {
case 'cat':
        $focusOLD = 1;
        include "adm_categories.inc";
        break;

case 'makeSearch':
        if ($LEVEL < 5)  include "adm_search.inc";
        else include "make_search.inc";
        break;

case 'Passwd':
        $focusOLD = 1;
        include "NewPass.inc";
        break;

case 'Users':
        $focusOLD = 1;
        include "users.inc";
        break;

default:
	$DEBUG = 0;
	switch ($DEBUG) {
	case '1':
		echo "<PRE>[dispatcher_inner]: default MISSING mode ($mode)\n\n";
		print_r($_POST);
		closeDB();
		exit;
	}
}
#
# Fonction
function DoubleDisplayMenu($Lsel,$list1,$list2,$separator=",") {
	$item1 = explode($separator,$list1);
	$item2 = explode($separator,$list2);
	$Lmax = count($item1);
	for ($i=0;$i<$Lmax;$i++) {
		$checked = "";
		if ($item1[$i] == "$Lsel") { $checked =" selected"; }
		print "\t\t<option value='$item1[$i]'$checked>$item2[$i]\n";
	}
}
#
function stripAccents($string) {
    $COMPARE = array(' ',',,','à','á','â','ã','ä','ç','è','é','ê','ë','ì','í','î','ï','ñ','ò','ó','ô','õ','ö','ù','ú', 'û','ü','ý','ÿ');   
    $REPLACE = array(',',',', 'a','a','a','a','a','c','e','e','e','e','i','i','i','i','n','o','o','o','o','o','u','u', 'u','u','y','y');   
    return str_replace($COMPARE,$REPLACE,strtolower($string));
}
#
# supprimer les caractères parasites
function clean_str($str) {
  $compare = array('"','"',";");
  $replace = array('','','');
  $str = str_replace($compare,$replace,$str);
  return $str;
}
#
# sans insertion <br>
function Secure($str) {
  $str = htmlspecialchars(stripslashes(trim($str)));
  return $str;
}
#
function Secure3($str) {
  $str = htmlspecialchars(trim($str));
  return $str;
}
#
closeDB();
?>
