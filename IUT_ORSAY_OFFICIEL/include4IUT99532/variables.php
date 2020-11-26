<?php
#######################################################################################
# File   : variables.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Paramètres fonctionnels
# -------------------------------------------------------------------------------------
#
# Constantes
$IMAGES = "./images";
$menuWIDTH = 146;
$TOOL_LABEL = "OSE";
$ICON_TYPE = "x-icon";
$ICON_IMAGE = "$IMAGES/eye_icon.ico";
$pageHeader = "Orsay Search Engine";
$COOKIE_NAME = "orsay_login";
$toolDIR = dirname($SN);
$xmlObjects = "./js/xmlObjects.js";
$IDENTIFIER_TABLE = "orsay_login";
#
$TOOLDB    = "iutorsay";
$TOOLADMIN    = "iutorsay";
$USERS_DB   = $connu = $TOOLDB;
#
# Variables POST
$post_count=count($_POST);
if ($post_count > 0) {
	$post_data=array_keys($_POST);
	for ($i=0;$i<$post_count;$i++) {
		$temp = $post_data[$i];
		$$temp = $_POST["$temp"];
	}
}
#
# Tables des couleurs du site
include_once "colors.default";
#
# Type de LOGIN
$LOGIN_BY_COOKIE = 1;
#
# Récupération du Cookie
include_once "HostVariables.inc";
#
# Librairie d'accès à MySQL
$php_full_version = explode('.',phpversion());
$php_version = $php_full_version[0];

switch ($php_version) {
case '7':
case 7:
        include_once "mySqliUtilities.php";
        break;

default:
        include_once "mySqlUtilities.inc";
}
#
# Javascript à activer en fin de chargement de la page
$OnLoad = "";
if (isset($OP)) {
	switch ($OP) {
	case 'search':
		$OnLoad = "document.getElementById('search_input').focus();";
		break;
	}
}
#
# Connexion à la DB
$GLOBALS["SQL_SOURCE"] = "OSE:variables";
$GLOBALS["db"] = connect2("$TOOLDB");
?>
