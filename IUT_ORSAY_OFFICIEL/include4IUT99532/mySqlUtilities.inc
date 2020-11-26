<?php
#######################################################################################
# File: mysql_utilities.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# MySQL en PHP5.
# -------------------------------------------------------------------------------------
#
$GLOBALS["ERR_LOG"]  = "/localdisk/user_data/SERVER/LOGS/ERRORS.log";
$GLOBALS["ERR_MAIL"] = "/localdisk/user_data/SERVER/MAILS/err_mail.";
#
if (isset($_SERVER["HTTP_USER_AGENT"])) {
	$qlUG = strtoupper($_SERVER["HTTP_USER_AGENT"]);
	if (stristr($qlUG,'MSIE 6.0')) { $GLOBALS["sqlUG"] = "IE6"; }
	else if (stristr($qlUG,'MSIE 7.0')) { $GLOBALS["sqlUG"] = "IE8"; }
	else if (stristr($qlUG,'GECKO')) { $GLOBALS["sqlUG"] = "FIREFOX"; }
}
else $GLOBALS["sqlUG"] = "UNKNOWN";
#
function QUERY($request) {
	global $LINK, $activeDB, $MAX, $ERR, $qresult;
	$GLOBALS["SERV_INI_REQ"] = $request;
	if (isset($GLOBALS["BACK_ACTION"])) {
		$GLOBALS["SERV_INI_REQ"] .= "\n\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
	}

	$db_selected = mysql_select_db($activeDB, $GLOBALS["db"]);

if (!$db_selected) {
   die ($GLOBALS["SQL_SOURCE"] . ': Impossible de selectionner la base de donnees : ' . mysql_error());
}
	$qresult = mysql_query($request);
	if (mysql_errno() > 0) {
		mysql_error($GLOBALS["db"]);
		$ERR = $GLOBALS["SQL_SOURCE"].":".mysql_errno()."<br>$request";
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS["sqlUG"];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS["SQL_SOURCE"]."]: err = ".mysql_errno()."\nREQ: $request\n";
		if (isset($_SESSION["LOGIN_NAME"])) {
			if (isset($_SESSION["user"])) $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"]." (".$_SESSION["user"].")\n";
			else $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"]."\n";
		}
		if (isset($GLOBALS["BACK_ACTION"])) {
			$ERROR .= "\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
			$ERR   .= "<br>### Backdoor action = ".$GLOBALS["BACK_ACTION"]."<br>".str_replace("&","<br>",$_SERVER["QUERY_STRING"]);
		}
		$MAX = -1;
/*
		$fw = fopen($GLOBALS["CFM_ERR_LOG"],"a");
		fwrite($fw, $ERROR);
		fclose($fw);
		$target_mail = $GLOBALS["CFM_ERR_MAIL"].date("Y_m_d_H_i_s");
		$fw = fopen($target_mail,"a");
		fwrite($fw, $ERROR);
		fclose($fw);
*/
		return 0;
	}
	list($cmd, $dummy) = explode(" ", $request);
	if (strtoupper($cmd) != "INSERT") $MAX = mysql_Num_Rows($qresult);
	return 1;
}

function WRITE($request) {
	global $activeDB, $ERR;

	mysql_select_db($activeDB, $GLOBALS["db"]);
	$qresult = mysql_query($request);
	if (mysql_errno() > 0) {
		mysql_error($GLOBALS["db"]);
		$ERR = 1;
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS["sqlUG"];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS["SQL_SOURCE"]."]: err = ".mysql_errno()."\nREQ: $request\n";
		if (isset($_SESSION["LOGIN_NAME"])){
			if (isset($_SESSION["user"])) $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"]." (".$_SESSION["user"].")\n";
			else  $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"].")\n";
		}
		if (isset($GLOBALS["BACK_ACTION"])) {
			$ERROR .= "\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
			$ERR   .= "<br>### Backdoor action = ".$GLOBALS["BACK_ACTION"]."<br>".str_replace("&","<br>",$_SERVER["QUERY_STRING"]);
		}
/*
		$fw = fopen($GLOBALS["CFM_ERR_LOG"],"a");
		fwrite($fw, $ERROR);
		fclose($fw);
		$target_mail = $GLOBALS["CFM_ERR_MAIL"].date("Y_m_d_H_i_s");
		$fw = fopen($target_mail,"a");
		fwrite($fw, $ERROR);
		fclose($fw);
*/
	}
	else $ERR = 0;
}

function RESULT($a, $b) {
	global $qresult;
	$result = mysql_result($qresult,$a, $b);
	if (mysql_errno() > 0) {
		mysql_error($GLOBALS["db"]);
		$ERR = 1;
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS["sqlUG"];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS["SQL_SOURCE"]."]: err = ".mysql_errno()."\nRESULT($a,$b)";
		$ERROR .= " from: ".$GLOBALS["SERV_INI_REQ"]."\n";
		if (isset($_SESSION["LOGIN_NAME"])) $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"]." (".$_SESSION["user"].")\n";
/*
		$fw = fopen($GLOBALS["CFM_ERR_LOG"],"a");
		fwrite($fw, $ERROR);
		fclose($fw);
		$target_mail = $GLOBALS["CFM_ERR_MAIL"].date("Y_m_d_H_i_s");
		$fw = fopen($target_mail,"a");
		fwrite($fw, $ERROR);
		fclose($fw);
*/
	}
	return $result;
}

function control($flag,$req) {
	global $activeDB, $ERR;

	mysql_select_db($activeDB, $GLOBALS["db"]);
	$qresult = mysql_query($req);
	
	if (mysql_errno() > 0) {
		mysql_error($GLOBALS["db"]);
		$ERR = mysql_errno()."<br>$req";
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS["sqlUG"];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS["SQL_SOURCE"]."]: err = ".mysql_errno()."\nREQ: $req\n";
		if (isset($_SESSION["LOGIN_NAME"])){
                        if (isset($_SESSION["user"])) $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"]." (".$_SESSION["user"].")\n";
                        else  $ERROR .= "Login: ".$_SESSION["LOGIN_NAME"].")\n";
                }
		if (isset($GLOBALS["BACK_ACTION"])) {
			$ERROR .= "\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
			$ERR   .= "<br>### Backdoor action = ".$GLOBALS["BACK_ACTION"]."<br>".str_replace("&","<br>",$_SERVER["QUERY_STRING"]);
		}
/*
		$fw = fopen($GLOBALS["CFM_ERR_LOG"],"a");
		fwrite($fw, $ERROR);
		fclose($fw);
		$target_mail = $GLOBALS["CFM_ERR_MAIL"].date("Y_m_d_H_i_s");
		$fw = fopen($target_mail,"a");
		fwrite($fw, $ERROR);
		fclose($fw);
*/
		return "";
	}
	if (mysql_Num_Rows($qresult) == 0) return 0;

	switch($flag) {
	case 'next':
		return (1 + mysql_result($qresult,0,0));
		break;

	case 'val':
		return mysql_result($qresult,0,0);
		break;

	case 'list':
		$res = '';
		$comma = '';
		for ($j=0;$j<mysql_Num_Rows($qresult);$j++) {
			$res .= $comma . mysql_result($qresult,$j,0);
			$comma = ',';
		}
		return $res;
		break;
	}
	return mysql_Num_Rows($qresult);
}
?>
