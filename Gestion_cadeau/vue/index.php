<?php
#
$DEBUG = 0;
$numId = 0;
#if (isset($_POST["DEBUG"])) $DEBUG = $_POST["DEBUG"];
#
switch ($DEBUG) {
case 1:
	echo "<pre>DEBUG index.php:\n";
	print_r($_POST);
	exit;
}
#
# Initialisation
require_once "../controleurs/cadeaux_env.php";
#
$LEVEL = 0;
#
# Présence du COOKIE = connecté
if (isset($_COOKIE[$COOKIE_NAME])) {
	list ($numId,$TimeToRefresh,$TimeOut) = explode('_',$_COOKIE[$COOKIE_NAME]);
	$FIELDS = "NomUtilisateur,PrenomUtilisateur,Login,Courriel,DateNaissance";
	$QUERY = "SELECT $FIELDS FROM utilisateur WHERE NumUtilisateur=$numId";
	QUERY($QUERY);
	if ($MAX > 0) {
		$nom = RESULT(0,0);
		$prenom = RESULT(0,1);
		$LOGIN = RESULT(0,2);
		$email = RESULT(0,3);
		$birth = RESULT(0,4);
		$LEVEL = 5;
	}
}
#
if (isset($_POST["LEVEL"]) && $_POST["LEVEL"] > $LEVEL) $LEVEL = intval($_POST["LEVEL"]);
#
# Présence d'une invitation
$lg = strlen($_SERVER["QUERY_STRING"]);
switch($lg) {
case 43:
	if (substr($_SERVER["QUERY_STRING"],0,1) != "k") break;
	#	
	# On vérifie dans la table des invitations
	$tag = explode("!",htmlspecialchars(stripslashes(trim($_SERVER["QUERY_STRING"]))));
	if (strlen($tag[1]) != 40) break;
	#
	$TAG = $tag[1];
	$QUERY = "SELECT NumUtilisateur_inviter FROM invitation WHERE clef='$TAG'";
	QUERY($QUERY);
	if ($MAX > 0) {
		$numId = RESULT(0,0);
		$LEVEL = 100;
	}
}
#
# HEADERS
#
require_once "headers.php";
#
# SELECTEUR DE FONCTIONS
#
switch ($LEVEL) {
case 100:
	# Demande d'inscription sur invitation
	require_once "inscription.php";
	break;
case 99:
	# Information
	require_once "contact1.php";
	break;
case 98:
	# Changer le mot de passe
	require_once "change_mdp.php";
	break;
case 97:
	# Modifier mes données
	require_once "identity.php";
	break;
case 96:
	# Modifier mes données
	require_once "filiation.php";
	break;
case 10:
	# Membre connecté
	require_once "liste.php";
	break;
case 9:
	# Membre connecté
	require_once "catalogue.php";
	break;
case 8:
	# Membre connecté
	require_once "groupe.php";
	break;
case 5:
	# Membre connecté
	require_once "membre.php";
	break;
case 1:
	# Demande d'inscription depuis la page de login
	require_once "inscription.php";
	break;
default:
	# Page de login
	require_once "login.php";
}
?>
