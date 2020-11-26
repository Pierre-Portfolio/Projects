<?php
#######################################################################################
# File: index.php(3)
# ~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# prototype
#######################################################################################
#
set_include_path("./include4IUT99532");
session_start();
set_time_limit(180);
#
if (isset($_SESSION["new2day"])) $force_new2day = 1;
else $force_new2day = 0;
#
$HEAD_SELECT = $MAP_POSITION = $RESET_PASSWORD = 0;
$LOGIN = 'nobody';
$LOGIN_ON = "none";
$activeDB = "iutorsay";
$LINKS_TOP = "-50%";
$BAND_HEIGHT = $r = 0;
include_once "main.php";
#
$common = "https://" . $_SERVER["HTTP_HOST"] . dirname($_SERVER["SCRIPT_NAME"]);
#
$HOME_SCRIPT = "empty.php";
$COMPARE = array("\\", 'é', 'è', 'ê', 'ë', 'à', 'â', 'ù', 'û', 'ô', 'Ã©', 'Ãš', 'ÃŽ', 'Ã«', 'Ãª', 'Ã');   
$SUBSTITUTE = array("", "&eacute;", "&egrave;", "&ecirc;", "&euml;", "&agrave;", "&acirc;", "&ugrave;", "&ucirc;", "&ocirc;", "&eacute;", "&egrave;", "&ocirc;", "&euml;", "&euml;", "&agrave;");
#
if (isset($uid)) {
  $QUERY = "SELECT level FROM $IDENTIFIER_TABLE WHERE uid=$uid";
  QUERY($QUERY);
  if ($MAX > 0) {
    $LEVEL = RESULT(0,0);
  }
}
if (! isset($LEVEL)) $LEVEL = 9;
#echo "<pre>LEVEL=$LEVEL\n";print_r($_SESSION);print_r($_COOKIE);exit;
#
####################
# QUERY categories
####################
$QUERY = "SELECT cid,name FROM orsay_categories ORDER BY rank";
QUERY($QUERY);
$cat_max = $MAX;
if ($cat_max > 0) {
  for ($j=0;$j<$cat_max;$j++) {
    $CID[$j] = RESULT($j,0);
    #$CAT_TTL[$j] = utf8_encode(RESULT($j,1));
    $CAT_TTL[$j] = RESULT($j,1);
  }
}
#
include "colors.default";
$ICON_TYPE ="x-icon";
$TOP_WIDTH = 62;
#
#####################
# MAIN PAGE CONTENT
#####################
$LOGIN_MODE = $ADMIN_MODE = 0;
$MNGT_FRAME_LEFT = "0px";
switch ($r) {
case 99:
    $LOGIN_MODE = 1;
    $LOGIN_ON = "online";
    if ($LEVEL < 6) {
	$ADMIN_MODE = 1;
	$MNGT_FRAME_LEFT = "100%";
    }
    #echo "<pre>LOGIN: $LOGIN\nLEVEL: $LEVEL";exit;
    break;

case 9:
    $LINKS_TOP = "50%";
    break;
}
#
##########
# HEADER
##########
echo "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>
<html lang='fr_FR'>
<head>
  <title>Moteur de recherche de l'IUT d'Orsay</title>
  <meta http-equiv='content-type' content='text/html; charset=utf8'>
  <meta name='robots' content='index'>
  <meta name='author' content='Pierre'>
  <meta name='copyright' content='Copyright IUT d'Orsay'>
  <meta name='keywords' content='moteur, recherche, orsay'>

  <link rel='icon' type='image/$ICON_TYPE' href='$ICON_IMAGE' sizes='32x32'>
  <link rel='icon' type='image/$ICON_TYPE' href='$ICON_IMAGE' sizes='16x16'>

  <link rel='stylesheet' type='text/css' href='css/basic.css'>
  <link rel='stylesheet' type='text/css' href='css/perfect-scrollbar.css'>
  <script src='js/perfect-scrollbar.js'></script>

  <script language=JavaScript>
  var ajax = './ajax.php',
  login_mode = $LOGIN_MODE;
  </script>

  <script type='text/javascript' language=JavaScript src='$xmlObjects'></script>
</head>";
#
#####################
# MAIN DISPLAY FRAME
#####################
echo"
<body id=main style='background-color:#000080;' OnLoad='check_conditions()'>

<div id=main_div class=div_main style='background-image: url($IMAGES/blue-moon.jpg);'>
<SPAN id=main_container>";
include_once "welcome_text.inc";

echo "</SPAN></div>\n";
#
#############
# TOP FRAME
#############
$MS_HEIGHT = 70;
$loginHeight = 24;
$first = $CAT_TTL[0];
echo "
<div id=main_top class=abs_div0>
  <div class=iut_div><img class=iut_logo src='$IMAGES/iut_orsay.jpg'></div>
  <div class=look_div>
    <img class=look_logo src='$IMAGES/select_all1.png'>

    <input type=text id=search_cat1 class=search_cat value='Tout' readonly
	OnMouseOver=\"document.getElementById('cat_frame').style.top='200px'\"
	OnMouseOut=\"document.getElementById('cat_frame').style.top='0px'\">

    <input type=text id=search_input1 class=search_input1 value='' OnMouseOver='this.focus();'
	OnKeyPress=\"return(auto_search0(event));\"
	OnKeyUp=\"auto_search('AUTO_SEARCH','search',event);\">
  </div>

  <div class=login_div OnClick='mode_select(99,99);'
	OnMouseOver='if (login_mode == 0) extend_menu(1);'
	OnMouseOut='reduce_menu(1);'>
	<img class=login_logo style='height:24px;' src='$IMAGES/unselect_login.png'>
	<img id=img_login class=login_logo style='display:$LOGIN_ON;' src='$IMAGES/select_login.png'>
  </div>";
#
####################
# CALL MENU BUTTON
####################
if ($LEVEL < 6) $CALL_MENU_TOP = "21px";
else $CALL_MENU_TOP = "-100px";
#
echo "
  <div class=login_div id=swap_menu style='top:$CALL_MENU_TOP;' OnClick='show_mngt_menu();'>
	<img class=login_logo src='$IMAGES/select_login2.png'></div>
</div>";
#
####################
# End of TOP BANNER
####################
echo "</div>";
#
#######################
# End of HIDDEN FRAME
#######################
echo "</div></div>";
#
###############
# ADMIN FRAME
###############
echo "
<FORM TARGET=iFrame1 name=FS0 id=form_FS0 action='empty.php' method=POST></FORM>

<FORM TARGET=iFrame1 name=FS1 id=form_FS1 action='dispatcher.php' method=POST>
<input type=hidden name=innerREQ value=1>
<input type=hidden name=mode id=mode_FS1 value=none>
<input type=hidden name=OP id=mode_OP value=none>
<input type=hidden name=idx_edit id=idx_edit value=0>
<input type=hidden name=new_record id=new_record value=0>
<input type=hidden name=search_cat0 id=search_cat0 value=0>
<input type=hidden name=search_input0 id=search_input0 value=''>
<input type=hidden name=reset_password id=reset_password value=$RESET_PASSWORD>
<input type=hidden name=masterSN value='$SN'>
</FORM>

<script language=JavaScript>
var FS1 = document.getElementById('form_FS1');
var mode_FS1 = document.getElementById('mode_FS1');
var mode_OP = document.getElementById('mode_OP');
</script>

<div id=mngt_frame style='position:absolute;top:70px;bottom:0px;left:$MNGT_FRAME_LEFT;margin:0px 0px 0px -100%;width:100%;
      padding:0px;background-color:$color6;'>
<table border=0 cellspacing=0 cellpadding=0 style='width:100%;height:100%;'>
<tr><td style='height:10px;'></td>\n\n";
#
#~~~~~~~~~~~
# Left menu
#~~~~~~~~~~~~
echo "<tr><td style='width:${menuWIDTH}px;vertical-align:top;padding: 0px 2px 0px 0px;'>
<div id=td_menu class=blueArial12B style='position:relative;top:1px;left:4px;width:140px;height:99%;margin:0px;padding:0px;border:0px;'>";
#
if ($LEVEL < 6 && $force_new2day == 0) {
    $page = "";
    $auth_connect = 1;
    include "fetchMenuData.inc";
    include "adm_menu.inc";
    echo $page;
}
echo "</div></td>

<td style='padding:2px;vertical-align:top;background-color:$color7;'>
<div id=work class=gframe style='background-color:white;'>
<div id=work2 class=gframe style='background-color:white;margin:0px 1px 0px 0px;border:0px;'>
<IFRAME name=iFrame1 id=iFrame1 class=gFrame1 style='padding:0px;' src='$HOME_SCRIPT'></IFRAME>
</div></div></td><td style='width:4px;'></td></tr>

<tr style='text-align:center'><td></td>
<td class=dBlueArial12B style='height:20px;padding:0px;'>&nbsp;</td></tr></table>
</div>

<div style=\"position:absolute;top:${MS_HEIGHT}px;left:0px;width:100%;height:10px;margin-top:-4px;
  background-image:url('./images/chaines_longue.png');background-repeat:repeat-x;\"></div>";
#
##################
# Menu Catégorie
##################
echo "
<div id=cat_frame style='position:absolute;top:0px;left:50%;margin:-180px 0px 0px -154px;width:162px;height:129px;border:1px solid white;
  background-color:$color17;'
  OnMouseOver=\"this.style.top='200px'\" OnMouseOut=\"this.style.top='0px'\">
  <div style='position:absolute;top:1px;left:1px;right:1px;bottom:1px;background-color:white;'>
    <div class=whiteArial12B style='position:relative;margin:0px;padding:3px 2px 4px 2px;text-align:center;background-color:$color14;'>
    Modifier la cat&eacute;gorie</div>

    <div id=cat_scroll style='position:absolute;top:24px;left:2px;right:0px;bottom:3px;overflow:hidden;overflow-x:auto;'>
      <div style='position:absolute;top:0px;left:0px;right:13px;bottom:0px;margin:0px;padding:0px;'>";
#
for ($j=0;$j<$cat_max;$j++) {
  $cid = $CID[$j];
  $cat_label = addslashes($CAT_TTL[$j]);
  if ($j == 0) $BGcolor = $color7;
  else $BGcolor = $color6;
  echo "
    <div class='mbutton dBlueArial12B' style='position:relative;top:0px;margin:2px 0px 2px 0px;padding:2px 2px 2px 6px;
    background-color:$BGcolor;' OnClick=\"select_category($cid,'$cat_label');\">$CAT_TTL[$j]</div>";
}
echo "
      </div>
    </div>
  </div>
</div>";
#
##############
# JavaScript
##############
echo "
<script language=JavaScript>
var j=0, k=0,
force_new2day = $force_new2day,
login_mode = 0;
var search_results = document.getElementById('main_container');
var searchElement = document.getElementById('search_input1');
var search_ref = document.getElementById('search_input0');
var searchCategory = document.getElementById('search_cat0');
level = $LEVEL;

////////////////////
// CATEGORY CHANGE
////////////////////
function select_category(cid,val) {
    searchCategory.value = cid;
    document.getElementById('search_cat1').value = val;
    document.getElementById('cat_frame').style.top = '0px';
    auto_search('AUTO_SEARCH','restart');
}

////////////////////////////
// TOP MENU CHANGE CONTROL
////////////////////////////
var selected_menu = 0;
function mode_select(rank,val) {
	if (val == 99) {
		login_mode = 1;
	}
	else {
		login_mode = 0;
		document.getElementById('img_login').style.display='none';
	}
	if (parseInt(val) == 99) {
	    if (parseInt(level) < 6) return false;
	}
	selected_menu = val;

	var url=ajax;
	var params='action=LOGIN_PAGE';
	n++;
	params+='&n='+n;

	var xhr_object = getXMLHTTP();
	xhr_object.open('POST',url, true);
	xhr_object.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
	xhr_object.send(params);

	// wait for the answer
	xhr_object.onreadystatechange = function() {
	    if(xhr_object.readyState == 4) {
		var field = xhr_object.responseText.split('|');
		switch (parseInt(field[0])) {
		case 1:
		    search_results.innerHTML = field[1];
		    document.getElementById('mngt_frame').style.left = '0px';

		    document.getElementById('login').focus();
		    //alert('selected_menu = '+selected_menu);
		    break;
		default:
		    //alert('ajax returns: ' + xhr_object.responseText);
		}
	    }
	}
	return false;
}

/////////////////
// Extend MENUS
/////////////////
function extend_menu(val) {
	switch (parseInt(val)) {
	case 1:
		// LOGIN
		document.getElementById('img_login').style.display='inline';
		break;
	}
	return false;
}

/////////////////
// Reduce MENUS
/////////////////
function reduce_menu(val) {
	switch (parseInt(val)) {
	case 1:
		// LOGIN
		if (login_mode == 0) document.getElementById('img_login').style.display='none';
		break;
	}
	return false;
}

////////////////////////
// Verify LOGIN status
////////////////////////
function check_conditions() {
  if (parseInt(login_mode) == 1) {
    if (document.getElementById('psw1')) document.getElementById('psw1').value='';
    if (document.getElementById('login')) {
      document.getElementById('login').value='';
      document.getElementById('login').focus();
    }
  }
  else {
    document.getElementById('search_input1').focus();
  }
}

new PerfectScrollbar('#cat_scroll');
</script>";
#
############
# PAGE END
############
echo "
</body>\n</html>";
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>
