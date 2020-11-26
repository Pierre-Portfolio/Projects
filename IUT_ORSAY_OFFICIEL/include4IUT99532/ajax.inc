<?php
#
###########################################################################################
# File : ajax_orsay.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Traitement Ajax global.
###########################################################################################
#
#~~~~~~
# Init
#~~~~~~~
$TOOLDB = $activeDB = "iutorsay";
$DEBUG = 0;
if (!isset($LOGIN) || $LOGIN == "") {
	$trueLOGIN = $LOGIN = "nobody";
	switch ($action) {
	case "MENU_SETUP":
	case "LOAD_RECORD":
	      $action = "MENU_SETUP";
	      $FLAG = 9;
	}
}
#
$LEVEL = 9;
if (isset($uid)) {
  $QUERY = "SELECT level FROM $IDENTIFIER_TABLE WHERE uid=$uid";
  QUERY($QUERY);
  if ($MAX > 0) {
    $LEVEL = RESULT(0,0);
  }
}
#
$COMPARE = array("\\","'");
$SUBSTITUTE = array("","\'");
#
#~~~~~~~~~~~~~~~~
# POST variables
#~~~~~~~~~~~~~~~~~
$post_count=count($_POST);
if ($post_count > 0) {
        $post_data=array_keys($_POST);
        for ($i=0;$i<$post_count;$i++) {
                $temp = $post_data[$i];
		$$temp = $_POST["$temp"];
       }
}
$_GET = array();
#
$response = "0|ajax: $action";
$PAGE_2_DISP = "";
$GLOBALS["SQL_SOURCE"] = "OSE:ajax";
#
###########################################
##########    DISPLAY RESULTS    ##########
###########################################
#
$bonus = 0;
switch ($action) {
case "ADM_LOGIN":
	#~~~~~~~~~~~
	# ADM_LOGIN
	#~~~~~~~~~~~~
	$auth_connect = 0;
	$LEVEL = 9;
	include_once "identity_control.inc";
	$response = "$authentication|$err|$bonus|$LEVEL|0";
	#~~~~~~~~~~~~~~~~~~
	# End of ADM_LOGIN
	#~~~~~~~~~~~~~~~~~~~
	break;

case "AUTO_SEARCH":
	#~~~~~~~~~~~~~
	# AUTO_SEARCH
	#~~~~~~~~~~~~~~
	switch ($format) {
	case "user":
	    include_once "users_utility.inc";
	    break;

	default:
	    include_once "regular_search.inc";
	}
	#~~~~~~~~~~~~~~~~~~~~
	# End of AUTO_SEARCH
	#~~~~~~~~~~~~~~~~~~~~~
	break;

case "EDIT_RECORD":
	#~~~~~~~~~~~~~
	# EDIT_RECORD
	#~~~~~~~~~~~~~~
	include_once "edit_record.inc";
	#~~~~~~~~~~~~~~~~~~~~
	# End of EDIT_RECORD
	#~~~~~~~~~~~~~~~~~~~~~
	break;

case "EDIT_USER":
	#~~~~~~~~~~~
	# EDIT_USER
	#~~~~~~~~~~~~
	$format = "edit";
	include_once "users_utility.inc";
	#~~~~~~~~~~~~~~~~~~
	# End of EDIT_USER
	#~~~~~~~~~~~~~~~~~~~
	break;

case "LOGIN_PAGE":
	#~~~~~~~~~~
	# GET_PAGE
	#~~~~~~~~~~~
	include_once "login.inc";
	if (strlen($PAGE_2_DISP) == 0) break;
	$response = "1|" . $PAGE_2_DISP;
	#~~~~~~~~~~~~~~~~~
	# End of GET_PAGE
	#~~~~~~~~~~~~~~~~~~
	break;

case "MENU_SETUP":
	#~~~~~~~~~~~~
	# MENU_SETUP
	#~~~~~~~~~~~~~
	$auth_connect = 1;
	$page = "";
	$bonus = $LOGIN;
/*
#
	########################
	# Si timeout du Cookie
	########################
	if ($LEVEL > 3) $FLAG = 9;
*/
	#
	switch (intval($FLAG)) {
	case 1:
	      break;

	case 0:
	case 2:
	case 3:
	case 4:
	case 5:
	      include_once "fetchMenuData.inc";
	      include_once "adm_menu.inc";
	      break;

	default:
	      SetCookie("$COOKIE_NAME","",time()+5,"/");
	      $_SESSION = array();
	      $FLAG = 9;
	}
	$response = "1|$FLAG|$page|$bonus|0|\nLEVEL=$LEVEL";
	#
	#~~~~~~~~~~~~~~~~~~~
	# End of MENU_SETUP
	#~~~~~~~~~~~~~~~~~~~~
	break;
}
#
switch ($action) {
case "skip":
	break;
default:
	echo $response;
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
# avec insertion <br>
function Secure2($str) {
  $str = htmlspecialchars(stripslashes(nl2br(trim($str))));
  return $str;
}
#
# sans insertion <br>
function Secure3($str) {
  $str = htmlspecialchars(trim($str));
  return $str;
}
?>
