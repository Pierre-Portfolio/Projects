<?php
###########################################################################################
# File   : adm_search.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Gestion des données pour le moteur de recherche
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:adm_users";
$role_codes = array(0,1,2,3,9);
$role_names = array("webmaster","design","admin","clerk","normal");
$role_max = count($role_codes);
#
$START_ROLE = $role_max - 1;
for ($j=0;$j<$role_max;$j++) {
    $code = $role_codes[$j];
    $roleNames[$code] = $role_names[$j];
    if ($code == $LEVEL) $START_ROLE = $j;
}
#
if (isset($_POST["DEBUG"])) $DEBUG = $_POST["DEBUG"];
else $DEBUG = 0;
switch ($DEBUG) {
case 1:
    echo "<pre>";
    print_r($_POST);
    exit;
}
#
switch ($OP) {
case 'create':
    $now = date("Y/m/d");
    $psw =  password_hash("new2day", PASSWORD_DEFAULT);
    #$newUSER = strtolower(utf8_decode($USR_LOGIN));
    #$nwFIRST = utf8_decode($FNAME);
    #$newNAME = strtoupper(utf8_decode($LNAME));
    $newUSER = strtolower($USR_LOGIN);
    $nwFIRST = $FNAME;
    $newNAME = strtoupper($LNAME);
    $newMAIL = strtolower($EMAIL);
    $VALUES = "'$newUSER','$ROLE','$psw','$nwFIRST','$newNAME','$newMAIL','$now','',''";
    #
    $SQL1 = "INSERT INTO orsay_login (login,level,passwd,fname,lname,email,created,laccess,chgpass) VALUES ($VALUES)";
    if ($DEBUG > 0) {
	#echo "<pre>$QUERY\n$SQL1\n$SQL2\n";print_r($_POST);exit;
	echo "<pre>\n$SQL1\n";print_r($_POST);exit;
    }
    WRITE($SQL1);
    $_POST["UID"] = control("val","SELECT uid FROM orsay_login WHERE uid=LAST_INSERT_ID()");
    break;

case 'update':
    #$newUSER = strtolower(utf8_decode($USR_LOGIN));
    #$nwFIRST = utf8_decode($FNAME);
    #$newNAME = strtoupper(utf8_decode($LNAME));
    $newUSER = strtolower($USR_LOGIN);
    $nwFIRST = $FNAME;
    $newNAME = strtoupper($LNAME);
    $newMAIL = strtolower($EMAIL);
    $SQL1 = "UPDATE orsay_login set level=$ROLE";
    $QUERY = "SELECT login,fname,lname,email FROM orsay_login WHERE uid=$UID";
    QUERY($QUERY);
    if ($MAX > 0) {
	$old_login = RESULT(0,0);
	$old_fname = RESULT(0,1);
	$old_lname = RESULT(0,2);
	$old_email = RESULT(0,3);
	if ($old_login != $newUSER) {
	    $SQL1 .= ",titre='$newUSER'";
	}
	if ($old_fname != $nwFIRST) {
	    $nwFIRST = addslashes($nwFIRST);
	    $SQL1 .= ",fname='$nwFIRST'";
	}
	if ($old_lname != $newNAME) {
	    $nwFIRST = addslashes($newNAME);
	    $SQL1 .= ",lname='$newNAME'";
	}
	if ($old_email != $newMAIL) {
	    $SQL1 .= ",email='$newMAIL'";
	}
	$SQL1 .= " WHERE uid=$UID";
	if ($DEBUG == 0) WRITE($SQL1);
    }
    if ($DEBUG > 0) {
	echo "<pre>DEBUG=$DEBUG\nmax=$MAX\n$QUERY\n$SQL1\n";print_r($_POST);exit;
    }
    break;

case 'delete':
    $SQL1 = "DELETE FROM orsay_login WHERE uid=$UID";
    WRITE($SQL1);
    break;

case 'raz':
    $psw =  password_hash("new2day", PASSWORD_DEFAULT);
    $SQL1 = "UPDATE orsay_login set passwd='$psw' WHERE uid=$UID";
    WRITE($SQL1);
    break;
}
#
#########################
# PREPARE RESULTS TABLE
#########################
$FIELDS = "uid,login,level,fname,lname,email,laccess";
$QUERY = "SELECT $FIELDS FROM orsay_login ORDER BY lname,fname";
#
$KEYWORDS = "";
if (isset($_POST["keywords"])) {
    if (strlen(trim($_POST["keywords"])) > 0) {
	$format = "list";
	$KEYWORDS = $_POST["keywords"];
	include_once "users_utility.inc";
    }
}
QUERY($QUERY);
$result_max = $MAX;
#
if ($result_max > 0) {
    for ($j=0;$j<$result_max;$j++) {
	$UID[$j] = RESULT($j,0);
	$LOGINS[$j] = RESULT($j,1);
	$ROLES[$j] = RESULT($j,2);
	#$FNAMES[$j] = utf8_encode(RESULT($j,3));
	#$LNAMES[$j] = utf8_encode(RESULT($j,4));
	$FNAMES[$j] = RESULT($j,3);
	$LNAMES[$j] = RESULT($j,4);
	$EMAILS[$j] = RESULT($j,5);
	$ACCESS[$j] = RESULT($j,6);
    }
}
#
#
#
#################
# FRAME CONTENT
#################
echo "
<head>
<link rel=stylesheet type='text/css' href='css/perfect-scrollbar.css'>
<script src='js/perfect-scrollbar.js'></script>
</head>

<form id=admUsers TARGET=_self action='$SN' method=POST enctype='multipart/form-data'>
<input type=hidden name=innerREQ value=1>
<input type=hidden name=mode value='Users'>
<input type=hidden name=OP id=OP value='create'>
<input type=hidden name=MENU id=MENU value='users'>
<input type=hidden name=UID id=uid_ref value=0>";
#
#############
# Page title
#############
echo "
  <div style='position:absolute;top:14px;left:100px;margin:0px;padding:1px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:4px 12px 4px 12px;text-align:center;
	background-color:$color14;font-size:16px;'>Gestion des utilisateurs</div>
  </div>";
#
#############
# POSITIONS
#############
$TOP0 = 22;
$DELTA = 32;
$TOP1 = $DELTA + $TOP0;
$TOP2 = $DELTA + $TOP1;
$TOP3 = $DELTA + $TOP2;
$TOP4 = $DELTA + $TOP3;
$TOP5 = $DELTA + $TOP4;
$TOP_ERR = $TOP1;
$ROLE_MARGIN = $TOP4 - 1000;
$LEFT_ID = 630;
$LEFT_FIRST = 17 + $LEFT_ID;
$LEFT_LAST  = 40 + $LEFT_ID;
$LEFT_RAZ = 306 + $LEFT_ID;
$LEFT_MAIL  = 34 + $LEFT_ID;
$LEFT_ROLE  = 39 + $LEFT_ID;
$LEFT_SUBMIT = 310 + $LEFT_ID;
$LEFT_SUBMIT2 = 320 + $LEFT_ID;
$LEFT_NEW = 220 + $LEFT_ID;
$LEFT_SUPPRESS = 158 + $LEFT_ID;
$LEFT_CONFIRM = 22 + $LEFT_ID;
#
################
# Champ ERREUR
################
echo "
  <div id=errorFrame style='position:absolute;top:${TOP_ERR}px;left:401px;margin:0px;padding:2px;border:1px solid $color17;
    background-color:$color14;display:none;'>
    <div id=recordError class=blackArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color8;margin:0px;color:$color14;'></div>
  </div>";
#
#############
# RECHERCHE
#############
echo "
  <div style='position:absolute;top:${TOP1}px;left:100px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white_space:nowrap;'>Recherche</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=keywords id=search_user1 class=dBlueArial12B value='$KEYWORDS'
	    style='width:190px;padding:1px 3px 1px 3px;border:0px;' autocomplete='off'
	    OnMouseOver=\"this.focus();document.getElementById('errorFrame').style.display = 'none';\"
	    OnKeyPress=\"return(auto_search0(event));\"
	    OnKeyUp=\"auto_search('AUTO_SEARCH','user',event);\"></div>
  </div>";
#
###############
# Champ LOGIN
###############
echo "
  <div style='position:absolute;top:${TOP0}px;left:${LEFT_ID}px;margin:0px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white-space:nowrap;'>Identifiant</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=USR_LOGIN id=USR_LOGIN class=dBlueArial12B value='' maxLength=16
	    style='width:120px;padding:1px 3px 1px 3px;border:0px;text-transform:lowercase;' autocomplete='off'
	    OnMouseOver='this.focus();'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"></div>
  </div>";
#
##########
# PRENOM
##########
echo "
  <div style='position:absolute;top:${TOP1}px;left:${LEFT_FIRST}px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white_space:nowrap;'>Pr&eacute;nom</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=FNAME id=FNAME class=dBlueArial12B value='' maxLength=30
	    style='width:200px;padding:1px 3px 1px 3px;border:0px;' autocomplete='off'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"></div>
  </div>";
#
#######
# NOM
#######
echo "
  <div style='position:absolute;top:${TOP2}px;left:${LEFT_LAST}px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white_space:nowrap;'>Nom</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=LNAME id=LNAME class=dBlueArial12B value='' maxLength=30
	    style='width:200px;padding:1px 3px 1px 3px;border:0px;text-transform:uppercase;' autocomplete='off'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"></div>
  </div>";
#
####################
# RAZ mot de passe
####################
echo "
    <div id=raz_mdp class='whiteArial12B mbutton'
      style='position:absolute;top:${TOP2}px;left:${LEFT_RAZ}px;margin:0px;padding:4px 10px 4px 12px;background-color:#990000;
      border:2px solid #E00000;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;display:none;'
      OnClick='raz_passwd();'>RAZ mot de passe</div>";
#
#########
# EMAIL
#########
echo "
  <div style='position:absolute;top:${TOP3}px;left:${LEFT_MAIL}px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white_space:nowrap;'>Email</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=EMAIL id=EMAIL class=dBlueArial12B value='' maxLength=50
	    style='width:350px;padding:1px 3px 1px 3px;border:0px;' autocomplete='off'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"></div>
  </div>";
#
########
# ROLE
########
echo "
  <div style='position:absolute;top:${TOP4}px;left:${LEFT_ROLE}px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white_space:nowrap;'>R&ocirc;le</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=hidden name=ROLE id=ROLE value=9>
	<input type=text id=ROLENAME class=dBlueArial12B value='normal'
	    style='width:70px;padding:1px 3px 1px 3px;border:0px;text-align:center;' readonly
	    OnMouseOver=\"set_role('fetch',0,0);
			  document.getElementById('errorFrame').style.display = 'none';\"
	    OnMouseOut=\"document.getElementById('role_menu').style.top='0px';\"></div>
  </div>";
#
########################
# CREATE/UPDATE button
########################
echo "
  <div id=manageButton style='position:absolute;top:${TOP4}px;left:${LEFT_SUBMIT}px;width:50px;height:24px;margin:0px;padding:0px;'>
    <div id=manageRecord class='whiteArial12B mbutton'
      style='position:absolute;top:0px;left:0px;margin:0px;padding:4px 10px 4px 12px;background-color:$color5;
      border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick='manage_user();'>cr&eacute;er utilisateur</div>
  </div>";
#
################
# Nouvel index
################
echo "
    <div id=clearData class='whiteArial12B mbutton'
      style='position:absolute;top:${TOP4}px;left:${LEFT_NEW}px;margin:0px;padding:4px 10px 4px 10px;background-color:$color5;
      border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;display:none;'
      OnClick='clear_user_data();'>RAZ</div>";
#
###################
# SUPPRESS button
###################
echo "
    <div id=delete_button class='whiteArial12B mbutton'
      style='position:absolute;top:${TOP5}px;left:${LEFT_SUPPRESS}px;margin:0px;padding:4px 10px 4px 12px;background-color:#990000;
      border:2px solid #E00000;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;display:none;'
      OnClick=\"document.getElementById('delete_confirm').style.display='inline';\">supprimer cet utilisateur</div>";
#
##################################
# Confirmation de la suppression
##################################
echo "
<div id=delete_confirm style='position:absolute;top:${TOP5}px;left:${LEFT_CONFIRM}px;padding:2px;border:1px solid white;
  background-color:$color17;margin-top:-2px;display:none;'>
  <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:3px 8px 1px 8px;float:left;
	height:20px;background-color:$color14;margin:0px;white_space:nowrap;'>Confirmer la suppression :</div>

  <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px;float:left;
	height:20px;background-color:$color14;margin:0px;white_space:nowrap;'>
    <div class='whiteArial12B mbutton'
	style='position:relative;top:0px;left:0px;margin:0px;padding:1px 10px 1px 10px;background-color:white;float:left;
	border:2px solid $color17;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
	OnClick='delete_user();'>confirmation</div>
  </div>

  <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 10px 2px 10px;float:left;
	height:20px;background-color:$color14;margin:0px;white_space:nowrap;'>
      <div class='whiteArial12B mbutton'
	style='position:relative;top:0px;left:0px;margin:0px;padding:1px 10px 1px 10px;background-color:white;float:left;
	border:2px solid $color17;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
	OnClick=\"document.getElementById('delete_confirm').style.display='none';\">abandon</div>
  </div>
</div>
</form>\n";
#
###########################
# Affichage des resultats
###########################
$width_login = 70;
$width_first = 150;
$width_last = 150;
$width_laccess = 118;
$width_button = 66;
$BG1 = "steelblue";
$BG1 = $color7;
$BG2 = $color5;
#
echo "
<div style='position:absolute;top:${TOP2}px;left:10px;width:${LEFT_ID}px;bottom:20px;border:0px solid red;'
    OnMouseOver=\"new PerfectScrollbar('#users_display');\">
  <div style='position:absolute;top:4px;left:16px;right:16px;bottom:4px;
    font-family:arial,Helvetica;font-size:12px;color:#606060;margin:0px;
    box-shadow:0px 0px 10px yellow;background-color:ivory;border-radius:16px;-moz-border-radius:16px;'>

    <div style='position:absolute;top:58px;left:1px;right:1px;height:39px;margin:0px;border:0px;'>
	<table border=0 cellspacing=2 cellpadding=0 style='margin:0px;'>
	<tr class=dBlueArial12B style='text-align:center;'>
	<td style='width:${width_login}px;padding:2px;background-color:$BG1;'>Login</td>
	<td style='vertical-align:top;width:${width_first}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG1;'>Pr&eacute;nom</td>
	<td style='vertical-align:top;width:${width_last}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG1;'>Nom</td>
	<td style='vertical-align:top;width:${width_laccess}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG1;'>Dernier acc&egrave;s</td></tr>

	<tr class=dBlueArial12B style='text-align:center;'>
	<td style='width:${width_login}px;padding:1px 2px 1px 2px;background-color:$BG2;'>R&ocirc;le</td>
	<td colspan=3 style='vertical-align:top;width:${width_first}px;padding:1px 0px 1px 6px;white-space:nowrap;
	    background-color:$BG2;'>Email</td></tr>
	</table>
    </div>

    <div id=users_display style='position:absolute;top:99px;left:1px;right:1px;bottom:20px;margin:0px;border:0px solid black;
	overflow:hidden;overflow-y:scroll;'>
      <div id=user_results style='position:relative;top:0px;left:0px;margin:0px 12px 0px 0px;padding:0px;'>
	<table border=0 cellspacing=2 cellpadding=0 style='margin:0px;width:100%;'>";
#
if ($result_max == 0) {
    echo "
	<tr class=dBlueArial12B><td style='text-align:center;padding:4px 0px 4px 0px;'>Aucun document disponible</td></tr>";
}
else {
    for ($j=0;$j<$result_max;$j++) {
	$sel_uid = $UID[$j];
	$sel_login = $LOGINS[$j];
	$role = $ROLES[$j];
	$fname = $FNAMES[$j];
	$lname = $LNAMES[$j];
	$email = $EMAILS[$j];
	$laccess = $ACCESS[$j];
	#
	echo "
	<tr class=dBlueArial12B><td style='width:${width_login}px;padding:2px;text-align:center;
	    background-color:$BG1;'>$sel_login</td>
	<td style='vertical-align:top;width:${width_first}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG1;'>$fname</td>
	<td style='vertical-align:top;width:${width_last}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG1;'>$lname</td>
	<td style='vertical-align:top;width:${width_laccess}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG1;'>$laccess</td>
	<td rowspan=2>";
	#
	if ($uid != $sel_uid && $LEVEL <= $role) {
	    echo "<div class='whiteArial12B mbutton'
	    style='position:relative;top:0px;left:0px;margin:2px;padding:1px 8px 1px 8px;background-color:$color5;text-align:center;
	    border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
	    OnClick=\"edit_user($sel_uid);\">&eacute;diter</div>";
	}
	#
	echo "</td></tr>

	<tr class=dBlueArial12B><td style='width:${width_login}px;padding:2px;text-align:center;
	    background-color:$BG2;'>$roleNames[$role]</td>
	<td colspan=3 style='vertical-align:top;width:${width_first}px;padding:2px 0px 2px 6px;white-space:nowrap;
	    background-color:$BG2;'>$email</td></tr>";
    }
}
#
echo "
	</table>
      </div>
    </div>
  </div>

  <div class=rbanner_left style='border-color:transparent $color17 transparent transparent;'></div>
  <div class=rbanner_right style='border-color:transparent transparent transparent $color17;'></div>
  <div class=rbanner_text style='background-color:$color14;color:$color6;'>Liste des utilisateurs</div>
</div>";
#
#############
# Menu ROLE
#############
echo "
<div id=role_menu style='position:absolute;top:0px;left:${LEFT_ROLE}px;width:144px;height:125px;border:1px solid white;
  background-color:$color17;margin-top:${ROLE_MARGIN}px;'
  OnMouseOver=\"this.style.top='1000px';\" OnMouseOut=\"this.style.top='0px';\">
  <div style='position:absolute;top:1px;left:1px;right:1px;bottom:1px;background-color:white;paddin:0px;'>
    <div class=whiteArial12B style='position:relative;margin:0px;padding:3px 2px 4px 2px;text-align:center;
      background-color:$color14;'>Nouveau r&ocirc;le</div>
      <div style='position:absolute;top:21px;left:2px;right:2px;bottom:3px;overflow:hidden;margin:0px;padding:0px;'>";
#
for ($j=0;$j<$role_max;$j++) {
  $role_code = $role_codes[$j];
  if ($LEVEL > $role_code) continue;
  $role_label = $role_names[$j];
  echo "
	<div class='mbutton dBlueArial12B' id=code$j OnClick=\"set_role('set',$role_code,'$role_label');\"
	  style='position:relative;top:0px;margin:2px 0px 1px 0px;padding:2px 2px 2px 6px;background-color:$color6;
	  text-align:center;'>$role_label</div>";
}
echo "
      </div>
    </div>
  </div>
</div>";
#
##########
# Script
##########
echo "
<script language=JavaScript>
var code,
codes = new Array(0,1,2,3,9),
roles = new Array('webmaster','design','admin','clerk','normal'),
role_by_index = new Array();
for (j=0;j<codes.length;j++) {
    code = parseInt(codes[j]);
    role_by_index[code] = roles[j];
}

//////////////////////////
// EDITER UN UTILISATEUR
///////////////////////////
var remember_uid = 0;
function edit_user(uid) {
	remember_uid = uid;

	var params='action=EDIT_USER';
	params+='&user_id='+uid;
	params+='&LOGIN='+login;
	params+='&LEVEL='+level;
	n++;
	params+='&n='+n;

	var xhr_object = getXMLHTTP();
	xhr_object.open('POST',ajax, true);
	xhr_object.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
	xhr_object.send(params);

	// wait for the answer
	xhr_object.onreadystatechange = function() {
	    if(xhr_object.readyState == 4) {
		var field = xhr_object.responseText.split('|');
		switch (parseInt(field[0])) {
		case 1:
			document.getElementById('OP').value = 'update';
			document.getElementById('uid_ref').value = field[1];
			document.getElementById('USR_LOGIN').value = field[2];
			document.getElementById('FNAME').value = field[3];
			document.getElementById('LNAME').value = field[4];
			document.getElementById('EMAIL').value = field[5];
			code = parseInt(field[6]);
			document.getElementById('ROLE').value = code;
			document.getElementById('ROLENAME').value = role_by_index[code];
			document.getElementById('manageRecord').innerHTML = 'mettre &agrave; jour';
			document.getElementById('manageButton').style.left = \"${LEFT_SUBMIT2}px\";
			document.getElementById('clearData').style.display = 'inline';
			document.getElementById('delete_button').style.display = 'inline';
			if ($LEVEL < 3) {
			    document.getElementById('raz_mdp').style.display = 'inline';
			}
			break;

		default:
		    alert('echec edit: '+remember_uid);
		}
	    }
	}
	return false;
}

////////////////
// SUBMIT_USER
////////////////
function manage_user() {
    if (document.getElementById('USR_LOGIN').value.length < 3) {
	document.getElementById('recordError').innerHTML = 'Le champ Identifiant est vide';
	document.getElementById('errorFrame').style.display = 'inline';
	return false;
    }
    if (document.getElementById('FNAME').value.length < 3) {
	document.getElementById('recordError').innerHTML = \"Le pr&eacute;nom n'est pas renseign&eacute;\";
	document.getElementById('errorFrame').style.display = 'inline';
	return false;
    }
    if (document.getElementById('LNAME').value.length < 3) {
	document.getElementById('recordError').innerHTML = \"Le nom n'est pas renseign&eacute;\";
	document.getElementById('errorFrame').style.display = 'inline';
	return false;
    }
    document.getElementById('admUsers').submit();
}

////////////////
// DELETE USER
////////////////
function delete_user() {
	document.getElementById('OP').value = 'delete';
	document.getElementById('admUsers').submit();
}

//////////////////////
// RAZ user password
//////////////////////
function raz_passwd() {
	document.getElementById('OP').value = 'raz';
	document.getElementById('admUsers').submit();
}

////////////////
// ROLE CHANGE
////////////////
function clear_user_data() {
	document.getElementById('OP').value = 'create';
	document.getElementById('uid_ref').value = 0;
	document.getElementById('USR_LOGIN').value = '';
	document.getElementById('FNAME').value = '';
	document.getElementById('LNAME').value = '';
	document.getElementById('EMAIL').value = '';
	document.getElementById('ROLE').value = 9;
	document.getElementById('ROLENAME').value = role_by_index[9];
	document.getElementById('manageRecord').innerHTML = 'cr&eacute;er utilisateur';
	document.getElementById('manageButton').style.left = \"${LEFT_SUBMIT}px\";
	document.getElementById('clearData').style.display = 'none';
	document.getElementById('raz_mdp').style.display = 'none';
	document.getElementById('delete_button').style.display = 'none';
	document.getElementById('delete_confirm').style.display = 'none';
}

////////////////
// ROLE CHANGE
////////////////
function set_role(action,rid,val) {
    switch (action) {
    case 'fetch':
	rid = document.getElementById('ROLE').value;
	break;
    default:
	document.getElementById('ROLE').value = rid;
	document.getElementById('ROLENAME').value = val;
    }
    for (j=$START_ROLE;j<$role_max;j++) {
	if (parseInt(codes[j]) == parseInt(rid)) {
	    document.getElementById('code'+j).style.backgroundColor = '$color17';
	}
	else {
	    document.getElementById('code'+j).style.backgroundColor = '$color6';
	}
    }

    switch (action) {
    case 'fetch':
	document.getElementById('role_menu').style.top = '1000px';
	break;
    default:
	document.getElementById('role_menu').style.top = '0px';
    }
}

if ($LEVEL == 0) allow_right_mouse = 1;
new PerfectScrollbar('#users_display');
</script>";
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>