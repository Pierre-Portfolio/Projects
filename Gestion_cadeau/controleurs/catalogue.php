<?php
#
# Initialisation
require_once "../controleurs/cadeaux_env.php";
#
$DEBUG = 0;
$ERR = $MSG = "";
$newACTION = "editCadeau";
#
switch ($DEBUG) {
case 1:
	echo "<pre>controleur: catalogue.php\n";
	print_r($_POST);
	exit;
}
#
$LEVEL = $_POST["LEVEL"];
$numCadeau = $_POST["numCADEAU"];
$nomCadeau = htmlspecialchars(trim($_POST["nomDuCadeau"]));
$lien = htmlspecialchars(trim($_POST["lien"]));
$descriptif = htmlspecialchars(stripslashes(trim($_POST["short"])));
#
switch ($_POST["ACTION"]) {
case 'newCadeau':
	$SQL1 = "INSERT INTO cadeau (NomCadeau, Descriptif, Lien) VALUES ('$nomCadeau', '$descriptif', '$lien')";
	WRITE($SQL1);
	#
	$numCadeau = control("val","SELECT NumCadeau FROM cadeau WHERE NumCadeau=LAST_INSERT_ID()");
	#
	$MSG = "Cadeau créé avec succès";
	break;

case 'editCadeau':
	$numCadeau = $_POST["numCADEAU"];
	$SQL1 = "UPDATE cadeau set NomCadeau='$nomCadeau', Descriptif='$descriptif', Lien= '$lien'";
	$SQL1 .= "WHERE NumCadeau=$numCadeau";
	WRITE($SQL1);
	$MSG = "Cadeau mis à jour";
	break;

case 'supprimeCadeau':
	$numCadeau = $_POST["numCADEAU"];
	$oldFile = sprintf("../cadeaux/img%07d.jpg", $numCadeau);
	if (file_exists($oldFile)) unlink($oldFile);
	$SQL1 = "DELETE FROM cadeau WHERE NumCadeau=$numCadeau";
	WRITE($SQL1);
	$SQL2 = "DELETE FROM listecadeaux WHERE NumCadeau=$numCadeau";
	WRITE($SQL2);
	$numCadeau = 0;
	$newACTION = "rien";
	$MSG = "Cadeau supprimé";
}
#
switch ($numCadeau) {
case 0:
	break;
default:
	#----------------------------------------
	# 1. Get file parameters (size & suffix)
	#-----------------------------------------
	$UPLOAD_FILE = "realFile";
	$nwFile = sprintf("img%07d.jpg", $numCadeau);
	#
	$fileName = $_FILES["$UPLOAD_FILE"]['name'];
	$fileTemp = $_FILES["$UPLOAD_FILE"]['tmp_name'];
	$fileType = basename($_FILES["$UPLOAD_FILE"]['type']);
	$fileSize = $_FILES["$UPLOAD_FILE"]['size'];
	#
	#-----------------------
	# 2. Taille du fichier
	#------------------------
	if ($fileSize > 300000) {
		$ERR = "Image trop large ($fileSize)<br>";
		break;
	}
	#
	#--------------------
	# 3. Type du fichier
	#---------------------
	switch ($fileType) {
	case "jpg":
	case "jpeg":
		$accept = 1;
		break;
	default:
		$accept = 0;
		$ERR = "Image pas du bon type ($fileType)<br>";
	}
	if ($accept == 0) break;
	#
	#----------------------
	# 4. Sauver le fichier
	#-----------------------
	$cheminComplet = "../cadeaux/".$nwFile;
	if ($DEBUG == 0) {
		move_uploaded_file($fileTemp, $cheminComplet) or die("crotte");
		chmod ($cheminComplet, 0644);  // octal;
	}
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
	$VERIF = "<pre>numCadeau = $numCadeau\n\n
SQL1: $SQL1\n\n
";
}
echo "<html>

<body OnLoad=\"$ONLOAD\">
$VERIF

<FORM id=redo action='../vue/index.php' method=POST>
<input type=hidden name=LEVEL value=$LEVEL>
<input type=hidden name=selCADEAU value=$numCadeau>
<input type=hidden name=selACTION value='$newACTION'>
<input type=hidden name=MSG value=\"$MSG\">
<input type=hidden name=ERR value=\"$ERR\">
</FORM>
</body>
</html>";
?>