<?php
#######################################################################################
# File   : main.inc
# ~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Sécurise le développement grâce à 2 versions: DEV et PROD
# Paramètres de contexte
# -------------------------------------------------------------------------------------
#
#~~~~~~
# INIT
#~~~~~~~
$SN = $_SERVER["SCRIPT_NAME"];
$webHOST = $_SERVER['HTTP_HOST'];
include_once "env_vars.php";
#
#~~~~~~~~~~~~
# Parameters
#~~~~~~~~~~~~~
if (isset($_SERVER["HTTP_USER_AGENT"])) $UG = strtolower($_SERVER["HTTP_USER_AGENT"]);
else $UG = "BASH_mimic_script";
$UG_parts = explode(" ",$UG);
$c = count($UG_parts) - 1;
$key_arg = "";
$browser_type = explode(".",str_replace("/",".",$UG_parts[$c]));
$oldFirefoxMode = 0;
switch ($browser_type[0]) {
case "firefox":
	if ($browser_type[1] < 10) $oldFirefoxMode = 1;
}
$OS = "unknown";
if (stristr($UG,'windows')) {
    $OS = "Windows";
    if (stristr($UG,'trident') || stristr($UG,' msie ')) {
	$browser = "IE";
    }
}
else if (stristr($UG,'linux')) {
    $OS = "Linux";
}
if (stristr($UG,'gecko')) {
    if (stristr($UG,'firefox')) {
	$browser = "Firefox";
    }
    else if (stristr($UG,'opr/')) {
	$browser = "Opera";
    }
    else if (stristr($UG,'chrome')) {
	$browser = "Chrome";
    }
    else if (stristr($UG,'safari')) {
	$browser = "Safari";
    }
}
$steps = array(9,12,7,20,15,2,22,11,5,13);
$pcount = count($steps);
#
#~~~~~~~~~~~~~~~~~~~~
# Versions:
# ---------
# - php3: dev
# - php : production
#~~~~~~~~~~~~~~~~~~~~~
list($MYSCRIPT,$suffix) = explode(".", basename($SN));
$MYDIR = dirname($SN);
#
include "fetchArguments.php";
$c = strlen($key_arg);
include "variables.php";
#
#~~~~~~~~~~~~
# Script end
#~~~~~~~~~~~~~
?>
