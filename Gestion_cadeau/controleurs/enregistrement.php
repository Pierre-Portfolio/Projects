<?php
#
# Initialisation
require_once "../controleurs/cadeaux_env.php";
#
$DEBUG = 0;
#
switch ($DEBUG) {
case 1:
	echo "<pre>on arrive dans enregistrement.php\n";
	print_r($_POST);
	exit;
}
#
# Validation des données
$OP = "err";
$ERR = "";
#
switch (1) {
case 1:
    $LEVEL = $_POST["LEVEL"];
    #
    $alpha = "abcdefghijklmnopqrstuvwxyz";
    $chiffres = "0123456789";
    #
    $numId = $_POST["numId"];
    $LOGIN = strtolower(htmlspecialchars(stripslashes(trim($_POST["login"]))));
    $nom = strtoupper(htmlspecialchars(stripslashes(trim($_POST["nom"]))));
    $prenom = htmlspecialchars(stripslashes(trim($_POST["prenom"])));
    $email = strtolower(htmlspecialchars(stripslashes(trim($_POST["email"]))));
    $naissance = $_POST["naissance"];
    $mdp = $_POST["mdp"];
    $LEVEL = $_POST["LEVEL"];
    #
    ## Login
    $FOCUS = "login";
    $lg = strlen($LOGIN);
    if ($lg < 3) {
	$ERR = "Le login est trop court";
	break;
    }
    $ok = 1;
    for ($j=0;$j<$lg;$j++) {
	if (! stristr($alpha.$chiffres, substr($LOGIN,$j,1))) {
	    $ok = 0;
	    break;
	}
    }
    if ($ok == 0) {
	$ERR = "Ce login est invalide";
	break;
    }
    #
    $exist = control("val","SELECT NumUtilisateur FROM utilisateur WHERE Login='$LOGIN' AND NumUtilisateur!=$numId");
    if ($exist > 0) {
	$ERR = "Ce login existe déjà";
	break;    
    }
    #
    ## Nom de famille
    $FOCUS = "nom";
    $lg = strlen($nom);
    if ($lg < 1) {
	$ERR = "Le nom de famille manque";
	break;
    }
    if ($lg < 2) {
	$ERR = "Le nom de famille est trop court";
	break;
    }
    #
    ## Prénom
    $FOCUS = "prenom";
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
    #
    ## Email
    $FOCUS = "email";
    if (strlen($email) > 50) {
	$ERR = "L'adresse email est trop longue";
	break;
    }
    if (strlen($email) < 5) {
	$ERR = "L'adresse email est invalide";
	break;
    }
    # Caractères non autorisés dans un nom de domaine .eu :
    $nonASCII='ďđēĕėęěĝğġģĥħĩīĭįıĵķĺļľŀłńņňŉŋōŏőoeŕŗřśŝsťŧ';
    $nonASCII.='ďđēĕėęěĝğġģĥħĩīĭįıĵķĺļľŀłńņňŉŋōŏőoeŕŗřśŝsťŧ';
    $nonASCII.='ũūŭůűųŵŷźżztșțΐάέήίΰαβγδεζηθικλμνξοπρςστυφ';
    $nonASCII.='χψωϊϋόύώабвгдежзийклмнопрстуфхцчшщъыьэюяt';
    $nonASCII.='ἀἁἂἃἄἅἆἇἐἑἒἓἔἕἠἡἢἣἤἥἦἧἰἱἲἳἴἵἶἷὀὁὂὃὄὅὐὑὒὓὔ';
    $nonASCII.='ὕὖὗὠὡὢὣὤὥὦὧὰάὲέὴήὶίὸόὺύὼώᾀᾁᾂᾃᾄᾅᾆᾇᾐᾑᾒᾓᾔᾕᾖᾗ';
    $nonASCII.='ᾠᾡᾢᾣᾤᾥᾦᾧᾰᾱᾲᾳᾴᾶᾷῂῃῄῆῇῐῑῒΐῖῗῠῡῢΰῤῥῦῧῲῳῴῶῷ';
    #
/*
    $syntaxe="#^[[:alnum:][:punct:]]{1,64}@[[:alnum:]-.$nonASCII]{2,253}\.[[:alpha:].]{2,6}$#";
    if(! preg_match($syntaxe,$email)) {
	$ERR = "Adresse email invalide";
    }
*/
    #
    $exist = control("val","SELECT NumUtilisateur FROM utilisateur WHERE Courriel='$email' AND NumUtilisateur!=$numId");
    if ($exist > 0 && $LEVEL < 97) {
	$ERR = "Cette adresse email existe déjà";
	break;    
    }
    #
    ## Mot de passe
    #
    if ($LEVEL != 97) {
	$FOCUS = "mdp";
	if (strlen($mdp) < 1) {
	    $ERR = "Le mot de passe est vide";
	    break;
	}
	if (strlen($mdp) < 2) {
	    $ERR = "Le mot de passe est trop court";
	    break;
	}
	$hashed_password = password_hash($_POST["mdp"],PASSWORD_DEFAULT);
    }
    #
    ## Date de naissance
    #
    $FOCUS = "naissance";
    if (strlen($naissance) < 10) {
	$ERR = "La date de naissance est incomplète";
	break;
    }
    #
    if ($LEVEL == 1) $OP = "create";
    else $OP = "update";
}
#
$found = 0;
switch ($OP) {
case 'create':
    $nom = addslashes($nom);
    $prenom = addslashes($prenom);
    #
    $FIELDS = "NomUtilisateur,PrenomUtilisateur,DateNaissance,Courriel,Login,MotDePasse";
    $VALUES = "'$nom','$prenom','$naissance','$email','$LOGIN','$hashed_password'";
    #
    $SQL1 = "INSERT INTO utilisateur ($FIELDS) VALUES ($VALUES)";
    if ($DEBUG > 0) {
	echo "<pre>\n$SQL1\n";print_r($_POST);exit;
    }
    WRITE($SQL1);
    $numId = control("val","SELECT NumUtilisateur FROM utilisateur WHERE NumUtilisateur=LAST_INSERT_ID()");
    break;

case 'update':
    $FIELDS = "NomUtilisateur,PrenomUtilisateur,Login,Courriel,DateNaissance,MotDePasse";
    $QUERY = "SELECT $FIELDS FROM utilisateur WHERE NumUtilisateur=$numId";
    QUERY($QUERY);
    if ($MAX > 0) {
	$old_nom = RESULT(0,0);
	$old_prenom = RESULT(0,1);
	$old_LOGIN = RESULT(0,2);
	$old_email = RESULT(0,3);
	$old_birth = RESULT(0,4);
	$old_mdp = RESULT(0,4);
    }
    #
    $comma = ",";
    $SQL1 = "UPDATE utilisateur set Superviseur=0";
    #
    if ($old_LOGIN != $LOGIN) {
	$SQL1 .= ",Login='$LOGIN'";
	$comma = ",";
	$found = 1;
    }
    if ($old_nom != $nom) {
	$nom = addslashes($nom);
	$SQL1 .= $comma."NomUtilisateur='$nom'";
	$comma = ",";
	$found = 1;
    }
    if ($old_prenom != $prenom) {
	$prenom = addslashes($prenom);
	$SQL1 .= $comma."PrenomUtilisateur='$prenom'";
	$comma = ",";
	$found = 1;
    }
    if ($old_email != $email) {
	$SQL1 .= $comma."Courriel='$email'";
	$comma = ",";
	$found = 1;
    }
    if ($old_birth != $naissance) {
	$SQL1 .= ",DateNaissance='$naissance'";
	$comma = ",";
	$found = 1;
    }
    if (strlen($_POST["mdp"]) > 2) {
	$SQL1 .= ",MotDePasse='$hashed_password'";
	$comma = ",";
	$found = 1;
    }
    #
    if ($found == 0) {
	$OP = "err";
	$ERR = "Aucun changement";
	break;
    }
    $SQL1 .= " WHERE NumUtilisateur=$numId";
    $DEBUG = 0;
    if ($DEBUG == 0) WRITE($SQL1);
    else {
	echo "<pre>DEBUG=$DEBUG\nmax=$MAX\n$QUERY\n$SQL1\n";
	print_r($_POST);exit;
    }
    if ($LEVEL > 99) {
	$SQL2 = "UPDATE invitation set clef='' WHERE NumUtilisateur_inviter=$numId";
	break;
    }
    if ($LEVEL > 96) {
	$ONLOAD = "document.getElementById('redo').submit()";
	echo "
	<html>

	<body OnLoad=\"$ONLOAD\">
	<form id=redo action='../vue/index.php' method='post'>
	<input type=hidden name=LEVEL value=$LEVEL>
	<input type=hidden name=MSG value='Mise à jour des données réussie'>
	</form>
	</body>
	</html>";
	exit;
    }
    break;

case 'raz':
    $psw =  password_hash("new2day", PASSWORD_DEFAULT);
    #$SQL1 = "UPDATE utilisateur set passwd='$psw' WHERE uid=$UID";
    #WRITE($SQL1);
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
if ($OP == "err") {
    echo "
    <html>

    <body OnLoad=\"$ONLOAD\">
    <form id=redo action='../vue/index.php' method='post'>
    <input type=hidden name=LEVEL value='$LEVEL'>
    <input type=hidden name=FOCUS value='$FOCUS'>
    <input type=hidden name=ERR value=\"$ERR\">
    <input type=hidden name=LOGIN value='$LOGIN'>
    <input type=hidden name=nom value='$nom'>
    <input type=hidden name=prenom value='$prenom'>
    <input type=hidden name=email value='$email'>
    <input type=hidden name=birth value='$naissance'>
    </form>
</body>
    </html>";
    exit;
}
#
include "set_cookie.php";
#
?>