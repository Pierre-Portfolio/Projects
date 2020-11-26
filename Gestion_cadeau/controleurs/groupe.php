<?php
#
# Initialisation
require_once "../controleurs/cadeaux_env.php";
$newACTION = "editGroup";
#
$DEBUG = 0;
#
switch ($DEBUG) {
case 1:
	echo "<pre>controleur: groupe.php\n";
	print_r($_POST);
	exit;
}
#
$LEVEL = $_POST["LEVEL"];
$numId = $_POST["numId"];
$numGroupe = $_POST["numGROUP"];
$nomGroupe = $_POST["nomDuGroupe"];
#
switch ($_POST["ACTION"]) {
case 'newGroup':
	#
	$SQL1 = "INSERT INTO groupe (NomGroupe, NumUtilisateur) VALUES ('$nomGroupe', $numId)";
	WRITE($SQL1);
	#
	$numGroupe = control("val","SELECT NumGroupe FROM groupe WHERE NumGroupe=LAST_INSERT_ID()");
	$SQL2 = "INSERT INTO membre (NumGroupe, NumUtilisateur) VALUES ($numGroupe, $numId)";
	WRITE($SQL2);
	#
	$MSG = "Groupe créé avec succès";
	break;

case 'editGroup':
	$SQL1 = "UPDATE groupe set NomGroupe='$nomGroupe' WHERE NumGroupe=$numGroupe";
	WRITE($SQL1);
	$MSG = "Groupe mis à jour";
	break;

case 'supprimeGroupe':
	$SQL1 = "DELETE FROM groupe WHERE NumGroupe=$numGroupe";
	WRITE($SQL1);
	$SQL2 = "DELETE FROM membre WHERE NumGroupe=$numGroupe";
	WRITE($SQL2);
	$SQL3 = "DELETE FROM invitation WHERE NumGroupe=$numGroupe";
	WRITE($SQL3);
	$MSG = "Groupe supprimé";
	$newACTION = "rien";
	break;

case 'ajoutMembre':
	$nom = strtoupper(htmlspecialchars(stripslashes(trim($_POST["nom2"]))));
	$prenom = htmlspecialchars(stripslashes(trim($_POST["prenom2"])));
	$email = strtolower(htmlspecialchars(stripslashes(trim($_POST["courriel"]))));
	$lg = strlen($prenom);
	if ($lg < 1) {
	    $ERR = "Le prénom est vide";
	    break;
	}
	if (stristr($prenom, "-")) {
	    $chacun = explode("-", $prenom);
	    $lg = count($chacun);
	    $prenom = "";
	    $tiret = "";
	    for ($j=0;$j<$lg;$j++) {
		$prenom .= $tiret.ucwords($chacun[$j]);
		$tiret = "-";
	    }
	}
	$FIELDS = "NomUtilisateur,PrenomUtilisateur,DateNaissance,Courriel,Login,MotDePasse,Superviseur";
	$VALUES = "'$nom','$prenom','','$email','','#0',$numId";
	#
	$SQL1 = "INSERT INTO utilisateur ($FIELDS) VALUES ($VALUES)";
	if ($DEBUG > 0) {
	    echo "<pre>\n$SQL1\n";print_r($_POST);exit;
	}
	else WRITE($SQL1);
	#
	$selUSER = control("val","SELECT NumUtilisateur FROM utilisateur WHERE NumUtilisateur=LAST_INSERT_ID()");
	$FIELDS = "NumGroupe,NumUtilisateur,NumUtilisateur_inviter";
	$SQL1 = "INSERT INTO invitation ($FIELDS) VALUES ($numGroupe,$numId,$selUSER)";
	WRITE($SQL1);
	#
	$numMessage = 0;
	$numInvit = control("val","SELECT NumInvitation FROM invitation WHERE NumInvitation=LAST_INSERT_ID()");
	#
	include_once "../controleurs/exp_mail.php";
	break;

case 'emailMembre':
	$selUSER = $_POST["selUSER"];
	$FIELDS = "NumGroupe,NumUtilisateur,NumUtilisateur_inviter";
	$SQL1 = "INSERT INTO invitation ($FIELDS) VALUES ($numGroupe,$numId,$selUSER)";
	if ($DEBUG == 0) WRITE($SQL1);
	else {
	    echo "<pre>$SQL1\n";exit;
	}
	$QUERY = "SELECT PrenomUtilisateur,Courriel FROM utilisateur WHERE NumUtilisateur=$selUSER";
	QUERY($QUERY);
	if ($MAX > 0) {
	    $prenom = RESULT(0,0);
	    $email = RESULT(0,1);
	}
	$GROUPE = control("val","SELECT NomGroupe FROM groupe WHERE NumGroupe=$numGroupe");
	$numMessage = 1;
	include_once "../controleurs/exp_mail.php";
#
$DEBUG = 0;
#
switch ($DEBUG) {
case 1:
	echo "<pre>apres envoi message: groupe.php\n";
	print_r($_POST);
	exit;
}
	break;
}
#
echo "<html>
<body OnLoad=\"document.getElementById('redo').submit()\">
<FORM id=redo action='../vue/index.php' method=POST>
<input type=hidden name=LEVEL value=$LEVEL>
<input type=hidden name=selGROUP value=$numGroupe>
<input type=hidden name=selACTION value='$newACTION'>
<input type=hidden name=MSG value=\"$MSG\">
</FORM>
</body>
</html>";
?>