<?php
#
# Initialisation
require_once "../controleurs/cadeaux_env.php";
$reprise = "editListe";
#
$DEBUG = 0;
#
switch ($DEBUG) {
case 1:
	echo "<pre>controleur: liste.php\n";
	print_r($_POST);
	exit;
}
#
$LEVEL = $_POST["LEVEL"];
if (isset($_POST["numDest"])) $numDest = $_POST["numDest"];
$numId = $_POST["numId"];
if (isset($_POST["numGroupe"])) $numGroupe = $_POST["numGroupe"];
$numLISTE = $_POST["numLISTE"];
$numCADEAU = $_POST["CADEAU"];
if (isset($_POST["titreListe"])) $titreListe = $_POST["titreListe"];
$ACTION = $_POST["ACTION"];
#
switch ($ACTION) {
case 'destUser':
case 'destGroupe':
	if ($numLISTE == 0) $ACTION = "newListe";
	else $ACTION = "editListe";
}
#
switch ($ACTION) {
case 'newListe':
	#
	$SQL1 = "INSERT INTO liste (NomListe,NumUtilisateur,NumGroupe) VALUES ('$titreListe', $numDest, $numGroupe)";
	WRITE($SQL1);
	#
	$numListe = control("val","SELECT NumListe FROM liste WHERE NumListe=LAST_INSERT_ID()");
	#
	$MSG = "Liste créée avec succès";
	break;

case 'editListe':
	$SQL1 = "UPDATE liste set NomListe='$titreListe', NumUtilisateur=$numDest, NumGroupe=$numGroupe WHERE NumListe=$numLISTE";
	WRITE($SQL1);
	$MSG = "Liste mise à jour";
	break;

case 'supprimListe':
	$SQL1 = "DELETE FROM liste WHERE NumListe=$numLISTE";
	WRITE($SQL1);
	$MSG = "Liste supprimée";
	$reprise = "rien";
	break;

case 'ajoutCadeau':
	$SQL1 = "INSERT INTO listecadeaux (NumListe,NumCadeau) VALUES ($numLISTE,$numCADEAU)";
	WRITE($SQL1);
	$MSG = "Cadeau ajouté";
	break;

case 'retirerCadeau':
	$SQL1 = "DELETE FROM listecadeaux WHERE NumListe=$numLISTE AND NumCadeau=$numCADEAU";
	WRITE($SQL1);
	$MSG = "Cadeau retiré";
	break;

case 'videListe':
	$SQL1 = "DELETE FROM listecadeaux WHERE NumListe=$numLISTE";
	WRITE($SQL1);
	$MSG = "Liste vide";
	break;

case 'achatCadeau':
	$SQL1 = "UPDATE listecadeaux set NumAcheteur=$numId WHERE NumListe=$numLISTE AND NumCadeau=$numCADEAU";
	WRITE($SQL1);
	$reprise = "voirListe";
	$MSG = "Cadeau acheté";
	break;

case 'abandonCadeau':
	$SQL1 = "UPDATE listecadeaux set NumAcheteur=0 WHERE NumListe=$numLISTE AND NumCadeau=$numCADEAU AND NumAcheteur=$numId";
	WRITE($SQL1);
	$reprise = "voirListe";
	$MSG = "A bandonadeau";
	break;
}
#
$DEBUG = 0;
switch ($DEBUG) {
case 0:
	$ONLOAD = "document.getElementById('redo').submit()";
	$VERIF = "";
	break;
default:
	$ONLOAD = "";
	$VERIF = "<pre>numListe = $numLISTE\n\n
	SQL1: $SQL1\n\n";
}
#
echo "<html>
<body OnLoad=\"$ONLOAD\">
$VERIF

<FORM id=redo action='../vue/index.php' method=POST>
<input type=hidden name=LEVEL value=$LEVEL>
<input type=hidden name=selLISTE value=$numLISTE>
<input type=hidden name=selACTION value='$reprise'>
<input type=hidden name=MSG value=\"$MSG\">
</FORM>
</body>
</html>";
?>