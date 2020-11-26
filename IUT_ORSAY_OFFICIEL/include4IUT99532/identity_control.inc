<?php
###########################################################################################
# File : identity_control.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Authentification
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:identity_control";
$set_cookie = 0;
#
switch ($auth_connect) {
case 0:
    $authentication = 0;
    $err = 0;
    if (isset($LOGIN)) {
	if (!isset($psw)) $psw = "";
	if (strlen($psw) == 0) {
		$err = 1;
		break;
	}
	#
	$id=strtolower($LOGIN);
	$QUERY = "select uid,passwd,level,fname,lname,laccess from $IDENTIFIER_TABLE where login='$id'";
	QUERY($QUERY);
	if ($MAX > 0) {
		$foundUID = 0;
		$uid=RESULT(0,0);
		$pswcheck=RESULT(0,1);
		$LEVEL=RESULT(0,2);
		$fn=RESULT(0,3);
		$ln=RESULT(0,4);
		#
		#~~~~~~~~~~~~~~~~~~~~~~~~
		# Check recovery request
		#~~~~~~~~~~~~~~~~~~~~~~~~~
/*
		if ($psw == "new2day") {
			$now = time();
			$diff = strtotime(RESULT(0,5)) - $now;
			if ($diff < 0) {
			    $authentication = 3;
			    $err = $uid;
			    $bonus = "$id diff: $diff ";
			    break;
			}
		}
*/
		#
		#~~~~~~~~~~~~~~~~~~~~~~~~
		# Check private password
		#~~~~~~~~~~~~~~~~~~~~~~~~~
		if (password_verify($psw,$pswcheck) == $pswcheck) $foundUID = 1;
		else {
			#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			# Failed: any Admin password ?
			#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			$where = "WHERE tool='site' AND level=0";
			$QUERY = "select uid from admin $where";
			QUERY($QUERY);
			$maxUID = $MAX;
			if ($maxUID>0) {
				$uidList = "";
				$separator = "";
				for ($j=0;$j<$maxUID;$j++) {
					$z = RESULT($j,0);
					$uidList = "${uidList}${separator}${z}";
					$separator = "','";
				}
				$where = "WHERE uid in ('$uidList')";
				$QUERY= "select passwd from $IDENTIFIER_TABLE $where";
				QUERY($QUERY);
				$maxUID = $MAX;
				if ($maxUID>0) {
					#~~~~~~~~~~~~~~~~~~~~~~~~~
					# Check Admin password(s)
					#~~~~~~~~~~~~~~~~~~~~~~~~~~
					for ($iUID=0;$iUID<$maxUID;$iUID++) {
						$pswcheck2 = RESULT($iUID,0);
						if (password_verify($psw,$pswcheck2) == $pswcheck2) $foundUID = 1;
					}
				}
			}
		}
		#
		#~~~~~~~~~~~~~~~~~~~~
		# Password found :o)
		#~~~~~~~~~~~~~~~~~~~~~
		if ($foundUID == 1) {
			$debug = 0;
			if ($debug == 1) {
				echo "0|2.<br>foundUID = $foundUID<PRE>";
				print_r($_POST);
				echo "InitCookie({$COOKIE_NAME},$id,$uid)";
				echo "</PRE>";
				exit;
			}
			$authentication = 1;
			$set_cookie = 1;
			if ($psw == "new2day") $err = 1;
			$now = date("Y:m/d H:i:s");
			$SQL = "UPDATE $IDENTIFIER_TABLE set laccess='$now' WHERE uid=$uid";
			WRITE($SQL);
		}
	}
    }
    break;

case 1:
    include_once "fetchMenuData.inc";
    include_once "adm_menu.inc";
    break;

case 3:
    $HOME_SCRIPT = "javascript:void(0);";
    $page .= "
    <head>
	<meta http-equiv='content-type' content='text/html; charset=utf8'>
	<link rel=stylesheet type='text/css' href='./css/basic.css'>
	<link rel=stylesheet type='text/css' href='./css/style.css'>
	<link rel=stylesheet type='text/css' href='./css/local.css'>
    </head>
    <table border=0 cellspacing=0 cellpadding=0 style='width:100%;height:100%;margin:0px;'>
    <tr><td style='height:10px;'></td>
    <tr><td style='width:144px;vertical-align:top;padding: 0px 2px 0px 0px;'>";

    include_once "fetchMenuData.inc";
    include_once "adm_menu.inc";

    $page .= "</td>
    <td style='padding:2px;vertical-align:top;background-color:$color7;'>
    <div id=work2 class=gframe style='background-color:white;margin:0px;border:0px;height:100%;'>
    <IFRAME name=iFrame1 id=iFrame1 class=gFrame1 src='$HOME_SCRIPT'
	style='border:0px;margin:0px;padding:0px;width:100%;height:100%;'></IFRAME>
    </div></td><td style='width:4px;'></td></tr>

    <tr style='text-align:center'><td></td>
    <td class=dBlueArial12B style='height:20px;padding:0px;'>Administrateur: $LOGIN</td></tr></table>";
    break;
}

switch ($set_cookie) {
case 1:
    $refreshTIME = time()+10*60;
    $timeOUT = time()+2*3600;
    SetCookie("$COOKIE_NAME","${LOGIN}_${uid}_${refreshTIME}_$timeOUT",$timeOUT,"/");
    $bonus = "${LOGIN}_${uid}_${refreshTIME}_$timeOUT";
}