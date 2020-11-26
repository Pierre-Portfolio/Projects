<?php
#
# Initialisation
require_once "../controleurs/cadeaux_env.php";
#
$DEBUG = 0;
#
switch ($DEBUG) {
case 1:
	echo "<pre>controleur: membre.php\n";
	print_r($_POST);
	exit;
}
#
# Validation des données
$ERR = $MSG = "";
$selINVIT = $_POST["selINVIT"];
$ACTION = $_POST["ACTION"];
$LEVEL = $_POST["LEVEL"];
#
$found = 0;
switch ($ACTION) {
case 'nonInvit':
    $SQL1 = "DELETE FROM invitation WHERE NumInvitation=$selINVIT";
    if ($DEBUG > 0) {
	echo "<pre>\n$SQL1\n";print_r($_POST);exit;
    }
    else WRITE($SQL1);
    $MSG = "Invitation refusée";
    break;

case 'ouiInvit':
    $QUERY = "SELECT NumGroupe,NumUtilisateur_inviter FROM invitation WHERE NumInvitation=$selINVIT";
    QUERY($QUERY);
    if ($MAX < 1) break;
    #
    $numGroupe = RESULT(0,0);
    $numUser = RESULT(0,1);
    $SQL1 = "INSERT INTO membre (NumGroupe,NumUtilisateur) VALUES ($numGroupe,$numUser)";
    #
    $SQL2 = "DELETE FROM invitation WHERE NumInvitation=$selINVIT";
    #
    if ($DEBUG == 0) {
	WRITE($SQL1);
	WRITE($SQL2);
	$MSG = "Invitation acceptée";
    }
    else {
	echo "<pre>DEBUG=$DEBUG\nmax=$MAX\n$QUERY\n$SQL1\n$SQL2\n";
	print_r($_POST);exit;
    }
    break;
}
#
$DEBUG = 0;
switch ($DEBUG) {
case 0:
    $ONLOAD = "document.getElementById('redo').submit()";
    break;
default:
    $ONLOAD = "";
}
#
echo "<html>

<body OnLoad=\"$ONLOAD\">

<FORM id=redo action='../vue/index.php' method=POST>
<input type=hidden name=LEVEL value=$LEVEL>
<input type=hidden name=selACTION value='rien'>
<input type=hidden name=MSG value=\"$MSG\">
</FORM>
</body>
</html>";
?>