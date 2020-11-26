<?php
#
$selACTION = "rien";
$selGROUP = 0;
$nomDuGroupe = "";
#
if (isset($_POST["selACTION"])) $selACTION = $_POST["selACTION"];
if (isset($_POST["selGROUP"])) $selGROUP = $_POST["selGROUP"];
#
$DEBUG = 0;
#
switch($DEBUG) {
case 1:
    echo "<pre>";
    print_r($_POST);
    exit;
}
#
switch ($selACTION) {
case 'newGroup':
case 'editGroup':
    $ONLOAD = "document.getElementById('nomDuGroupe').focus()";
    break;
case 'inviteMembre':
    $ONLOAD = "document.getElementById('nom2').focus()";
    break;
default:
    $ONLOAD = "";
}
#
echo "$HEADER

<body OnLoad=\"$ONLOAD\">

<FORM id=GROUPE action='../controleurs/groupe.php' method='post'>
<input type=hidden name=LEVEL value=8>
<input type=hidden name=numId value=$numId>
<input type=hidden name=ACTION id=ACTION value='$selACTION'>
<input type=hidden name=selUSER id=selUSER value='0'>
<input type=hidden name=numGROUP id=numGROUP value='$selGROUP'>\n";
#
$FIELDS = "g.NumGroupe, g.NomGroupe, g.NumUtilisateur";
$QUERY = "SELECT $FIELDS FROM groupe g, membre m WHERE g.NumGroupe=m.NumGroupe AND m.NumUtilisateur=$numId";
$QUERY .= " ORDER BY g.NomGroupe";
QUERY($QUERY);
$groupe_max = $MAX;
if ($groupe_max > 0) {
    for ($j=0;$j<$groupe_max;$j++) {
	$numGROUP[$j] = RESULT($j,0);
	$nomGROUP[$j] = RESULT($j,1);
	$PROPRIO[$j] = RESULT($j,2);
	if ($numGROUP[$j] == $selGROUP) $nomDuGroupe = $nomGROUP[$j];
    }
}

switch ($selACTION) {
case 'newGroup':
case 'editGroup':
case 'inviteMembre':
case 'ajoutGroupe':
    echo "
    <div class='container-groupe2'>
	<div class='groupe2'>
	<h2 class=group2>Nommage des groupes</h2>
	<input type=text class=case style='width:280px;' id=nomDuGroupe name=nomDuGroupe
	    placeholder='Nouveau nom de groupe' value='$nomDuGroupe'>
    
	<div class='bouton4 over' OnClick=\"select_action(1,0);\">Enregistrer</div>";
    #
    echo "
	<div class='bouton4 over' style='left:184px;background-color:red;'
	    OnClick=\"select_action(10,0);\">Supprimer</div>";
    #
    echo "
	</div>";

	switch ($selACTION) {
	case 'inviteMembre':
	    $QUERY = "SELECT NumUtilisateur_inviter FROM invitation WHERE NumGroupe=$selGROUP";
	    QUERY($QUERY);
	    $invites = "0";
	    if ($MAX > 0) {
		for ($j=0;$j<$MAX;$j++) {
		    $numUser = RESULT($j,0);
		    $invites .= "," . $numUser;
		    $INVITES[$numUser] = 1;
		}
	    }
	    echo "
	    <div id=groupe4 class='groupe4'>
		<h2 class=group2>S&eacute;lectionner un destinataire</h2>
		<div class='inner_liste5' style='height:112px;'>";
		    $QUERY = "SELECT NumUtilisateur,PrenomUtilisateur,NomUtilisateur,Superviseur ";
		    $QUERY .= "FROM utilisateur u WHERE u.NumUtilisateur!=$numId AND u.Superviseur in (0,$numId) AND Courriel!=''";
		    $QUERY .= " AND u.NumUtilisateur NOT IN ($invites) ORDER BY NomUtilisateur,PrenomUtilisateur";
		    QUERY($QUERY);
		    if ($MAX > 0) {
			for ($j=0;$j<$MAX;$j++) {
			    $uid = RESULT($j,0);
			    $prenom = RESULT($j,1);
			    $nom = RESULT($j,2);
			    $proprio = RESULT($j,3);
			    if ($proprio > 0) $BG = "style='background-color:#ffa000;'";
			    else $BG = "";
			    echo "
			    <div class='nom_liste3 over' $BG OnClick=\"select_action(4,$uid);\">$prenom&nbsp;$nom</div>";
			    #
			}
		    }
		    echo "
		</div>

		<div class='test2'>
		    <h2 class=group2 style='font-size:18px;'>ou ajouter un membre ext&eacute;rieur</h2>
		    <p><input class=case type=text name=nom2 id=nom2 placeholder='Son nom'
			style='text-transform:uppercase;' value=''
			OnKeyPress=\"return checkChar('next','prenom2',event);\"/></p>

		    <p><input class=case type=text name=prenom2 id=prenom2 placeholder='Son pr&eacute;nom' value=''
			OnKeyPress=\"return checkChar('next','courriel',event);\"/></p>

		    <p><input class=case type=text name=courriel id=courriel placeholder='Son email' value=''
			style='text-transform:lowercase;'/></p>
		</div>

		<div class='commande_groupe1 over' style='left:78px;'
		    OnClick=\"select_action(5,0);\">Ajouter un nouveau membre</div>
	    </div>";
	}
    echo "
    </div>";
}
echo "
</FORM>
    
<div class='groupe1'>
    <h2 class=group1>Groupes</h2>
    <div class='inner_groupe1'>";
#
if ($groupe_max == 0) {
    echo "
    <div class='contenu_vide1'>Aucune appartenance &agrave; un groupe</div>";
}
else  {
    for ($j=0;$j<$groupe_max;$j++) {
	$numGroupe = $numGROUP[$j];
	$nomGroupe = $nomGROUP[$j];
	$proprio = $PROPRIO[$j];
	#
	if ($proprio == $numId) {
	    $CLASS = "contenu_proprio";
	    $mode = 2;
	}
	else {
	    $CLASS =  "contenu_membre";
	    $mode = 9;
	}
	echo "
	<div class='$CLASS over' OnClick=\"select_action($mode,$numGroupe);\">$nomGroupe</div>";
    }
}
echo "
    </div>

    <div class='commande_groupe1 over' OnClick=\"select_action(0,0);\">
	Cr&eacute;er un nouveau groupe</div>
</div>\n";
#
switch ($selACTION) {
case 'editGroup':
case 'inviteMembre':
case 'voirGroupe':
case 'ajoutGroupe':
    $QUERY = "SELECT NumUtilisateur_inviter FROM invitation WHERE NumGroupe=$selGROUP";
    QUERY($QUERY);
    $invites = "0";
    if ($MAX > 0) {
	for ($j=0;$j<$MAX;$j++) {
	    $numUser = RESULT($j,0);
	    $invites .= "," . $numUser;
	    $INVITES[$numUser] = 1;
	}
    }
    echo "
    <div class='groupe3'>
	<h2 class=group3>Membres</h2>
	<div class='inner_groupe1'>";
	$QUERY = "SELECT DISTINCT u.NumUtilisateur,u.PrenomUtilisateur, u.NomUtilisateur FROM utilisateur u, membre m ";
	$QUERY .= " WHERE (u.NumUtilisateur=m.NumUtilisateur AND m.NumGroupe=$selGROUP) OR u.NumUtilisateur IN ($invites)";
	$QUERY .= " ORDER BY u.NomUtilisateur, u.PrenomUtilisateur";
	QUERY($QUERY);
	if ($MAX > 0) {
	    for ($j=0;$j<$MAX;$j++) {
		$uUser = RESULT($j,0);
		$uPrenom = RESULT($j,1);
		$uNom = RESULT($j,2);
		if (isset($INVITES[$uUser])) $BG = "background-color:#ffa000;";
		else $BG = "";
		echo "
		<div class=contenu_membre style='text-align:left;$BG'>$uPrenom $uNom</div>";
	    }
	}
	echo "
	</div>";

    switch ($selACTION) {
    case 'editGroup':
    case 'inviteMembre':
	echo "
	<div class='commande_groupe1 over' style='left:32px;'
	     OnClick=\"select_action(3,0);\">Inviter un nouveau membre</div>";
    }
    echo "
    </div>";
}
#
echo "
<FORM id=NEXT action='index.php' method=POST>
<input type=hidden name=LEVEL id=LEVEL value=8>
<input type=hidden name=selGROUP id=selGROUP value=$selGROUP>
<input type=hidden name=selACTION id=selACTION value='rien'>
</FORM>

<div class='fantome'>";
if (isset($_POST["MSG"]) && strlen($_POST["MSG"]) > 3) {
	echo "
	<div class='erreur info'>".$_POST["MSG"]."</div>";
}
echo "
</div>";
#
# Menu principal
#
echo "
$MEMBER

<script language=JavaScript1.2>
function select_action(action, val) {
    //alert('select_groupe');

    switch (parseInt(action)) {
    case 0:
	document.getElementById('selGROUP').value=0;
	document.getElementById('selACTION').value='newGroup';
	document.getElementById('NEXT').submit();
	break;
    case 1:
	document.getElementById('GROUPE').submit();
	break;
    case 2:
	document.getElementById('selGROUP').value=val;
	document.getElementById('selACTION').value='editGroup';
	document.getElementById('NEXT').submit();
	break;
    case 3:
	document.getElementById('selACTION').value='inviteMembre';
	document.getElementById('NEXT').submit();
	break;
    case 4:
	document.getElementById('selUSER').value=val;
	document.getElementById('ACTION').value='emailMembre';
	document.getElementById('GROUPE').submit();
	break;
    case 5:
	document.getElementById('ACTION').value='ajoutMembre';
	document.getElementById('GROUPE').submit();
	break;
    case 9:
	document.getElementById('selGROUP').value=val;
	document.getElementById('selACTION').value='voirGroupe';
	document.getElementById('NEXT').submit();
	break;
    case 10:
	document.getElementById('ACTION').value='supprimeGroupe';
	document.getElementById('GROUPE').submit();
	break;
    case 9:
    }
}
</script>
</body>
</html>";
?>