<?php
#######################################################################################
# File   : HostVariables.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Gestion du login
# -------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "HostVariables";
#
switch ($LOGIN_BY_COOKIE) {
case 1:
	if (isset($cookieSET)) {
		#echo "<pre>";print_r($_POST);exit;
		echo "<html>
		<body OnLoad=\"document.getElementById('refresh').submit()\">
		<FORM target=_top id=refresh action='$masterSN' method=POST></FORM>
		</body></html>";
		exit;
	}
	elseif (isset($LOGOUT)) {
		$_SESSION = array();
		SetCookie("$COOKIE_NAME","",time()+3,"/");
		$_SESSION["force_connect"] = 1;
		$_SESSION["CONNECT"] = "off";
	}
	elseif (isset($_COOKIE[$COOKIE_NAME])) {
		## Retrieve ID from COOKIE & check if expired
		$LEVEL = 9;
		unset($_SESSION["force_connect"]);
		list ($LOGIN,$uid,$TimeToRefresh,$TimeOut) = explode('_',$_COOKIE[$COOKIE_NAME]);
		$Now = time();
		if ($Now >= $TimeOut) {
			##~~~~~~~~~
			## Expired
			##~~~~~~~~~~
			$_SESSION = array();
			SetCookie("$COOKIE_NAME","",time()+3,"/");
			$_SESSION["force_connect"] = 1;
		}
		elseif ($Now >= $TimeToRefresh) {
			##~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			## Time to refresh the COOKIE
			##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			$refreshTIME = time()+10*60;
			$timeOUT = time()+2*3600;
			SetCookie("$COOKIE_NAME","${LOGIN}_${uid}_${refreshTIME}_$timeOUT",$timeOUT,"/");
		}
	}
	else $_SESSION["force_connect"] = 1;
	break;
default:
	##~~~~~~~~~~~~~~
	## Useless case
	##~~~~~~~~~~~~~~~
}
#echo "<pre>";print_r($_SESSION);print_r($_COOKIE);exit;
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>
