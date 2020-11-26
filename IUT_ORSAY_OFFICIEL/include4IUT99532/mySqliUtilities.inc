<?php
#######################################################################################
# File: mySqlUtilities.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# MySQLi in PHP7.
# -------------------------------------------------------------------------------------
#
$MSQLI_RESULT = array();
function QUERY($request) {
	global $LINK, $activeDB, $MAX, $ERR, $qresult, $MSQLI_RESULT;
	$MSQLI_RESULT = array();
	$GLOBALS["INI_REQ"] = $request;
	if (isset($GLOBALS["BACK_ACTION"])) {
		$GLOBALS["INI_REQ"] .= "\n\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
	}

	$qresult = mysqli_query($GLOBALS["db"],$request);
	if (mysqli_errno($GLOBALS["db"]) > 0) {
		$ERR = $GLOBALS['SQL_SOURCE'].":".mysqli_errno($GLOBALS["db"])."<br>$request";
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS["sqlUG"];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS['SQL_SOURCE']."]: err = ".mysqli_errno($GLOBALS["db"])."\nREQ: $request\n";
		if (isset($GLOBALS["LOGIN_NAME"])) $ERROR .= "Login: ".$GLOBALS["LOGIN_NAME"]." (".$GLOBALS["user"].")\n";
		if (isset($GLOBALS["BACK_ACTION"])) {
			$ERROR .= "\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
			$ERR   .= "<br>### Backdoor action = ".$GLOBALS["BACK_ACTION"]."<br>".str_replace("&","<br>",$_SERVER["QUERY_STRING"]);
		}
		$MAX = -1;
		return 0;
	}
	list($cmd, $dummy) = explode(" ", $request);
	switch (strtoupper($cmd)) {
	case "SELECT":
		$MAX = mysqli_Num_Rows($qresult);
		if ($MAX == 0) break;
		#
		#~~~~~~~~~~~~~~~~~~~~~~~
		# Retrieve fields name
		#~~~~~~~~~~~~~~~~~~~~~~~~
		$colMAX = mysqli_field_count($GLOBALS["db"]);
		#
		#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		# Put results into a global array
		#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		for ($j=0;$j<$MAX;$j++) {
			$qrow = $qresult->fetch_array();
			for ($k=0;$k<$colMAX;$k++) {
				##$msqli_field = $qfield[$k];
				##$MSQLI_RESULT[$j][$k] = $qrow["$msqli_field"];
				$MSQLI_RESULT[$j][$k] = $qrow[$k];
			}
		}
	}
	return 1;
}

function WRITE($request) {
	global $activeDB, $ERR;

	$qresult = mysqli_query($GLOBALS["db"],$request);
	if (mysqli_errno($GLOBALS["db"]) > 0) {
		$ERR = 1;
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS['sqlUG'];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS['SQL_SOURCE']."]: err = ".mysqli_errno($GLOBALS["db"])."\nREQ: $request\n";
		if (isset($GLOBALS["LOGIN_NAME"])) $ERROR .= "Login: ".$GLOBALS['LOGIN_NAME']." (".$GLOBALS['user'].")\n";
		if (isset($GLOBALS["BACK_ACTION"])) {
			$ERROR .= "\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
			$ERR   .= "<br>### Backdoor action = ".$GLOBALS["BACK_ACTION"]."<br>".str_replace("&","<br>",$_SERVER["QUERY_STRING"]);
		}
	}
	else $ERR = 0;
}

function RESULT($a, $b) {
	global $MSQLI_RESULT;
	if (isset($MSQLI_RESULT[$a][$b])) {
		return $MSQLI_RESULT[$a][$b];
	}
	else return false;
}

function control($flag,$req) {
	global $activeDB, $ERR;

	$qresult = mysqli_query($GLOBALS["db"],$req);
	
	if (mysqli_errno($GLOBALS["db"]) > 0) {
		$ERR = mysqli_errno($GLOBALS["db"])."<br>$request";
		$ERROR  = date("Y/m/d H:i:s").": ".$GLOBALS["sqlUG"];
		$ERROR .= ": PORT ".$_SERVER['SERVER_PORT'].": [".$GLOBALS["SQL_SOURCE"]."]: err = ".mysqli_errno($GLOBALS["db"])."\nREQ: $req\n";
		if (isset($GLOBALS["LOGIN_NAME"])) $ERROR .= "Login: ".$GLOBALS["LOGIN_NAME"]." (".$GLOBALS["user"].")\n";
		if (isset($GLOBALS["BACK_ACTION"])) {
			$ERROR .= "\n### Backdoor action: ".$GLOBALS["BACK_ACTION"]."\n".str_replace("&","\n",$_SERVER["QUERY_STRING"])."\n";
			$ERR   .= "<br>### Backdoor action = ".$GLOBALS["BACK_ACTION"]."<br>".str_replace("&","<br>",$_SERVER["QUERY_STRING"]);
		}
		return "";
	}
	if (mysqli_Num_Rows($qresult) == 0) return 0;
	#
	$qrow = $qresult->fetch_array();
	$VALUE = $qrow[0];
	#
	switch($flag) {
	case 'next':
		return (1 + $VALUE);
		break;

	case 'val':
		return $VALUE;
		break;

	case 'list':
		$res = '';
		$comma = '';
		for ($j=0;$j<mysqli_Num_Rows($qresult);$j++) {
			$qrow = $qresult->fetch_array();
			$res .= $comma . $qrow[0];
			$comma = ',';
		}
		return $res;
		break;
	}
	return mysqli_Num_Rows($qresult);
}

function closeDB() {
	mysqli_close($GLOBALS["db"]);
}
?>
