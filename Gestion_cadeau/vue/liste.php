<?php
#
$selACTION = "rien";
$selLISTE = $selCADEAU = 0;
$NumDest = $numGroupe = 0;
$titreListe = $destNom = $NomGroupe = "";
#
$DEBUG = 0;
switch ($DEBUG) {
case 1:
	echo "<pre>";
	print_r($_POST);
	exit;
}
#
if (isset($_POST["selACTION"])) $selACTION = $_POST["selACTION"];
if (isset($_POST["selLISTE"])) $selLISTE = $_POST["selLISTE"];
if (isset($_POST["selCADEAU"])) $selCADEAU = $_POST["selCADEAU"];
#
if ($selLISTE > 0) {
    $QUERY = "SELECT NomListe,NumUtilisateur,NumGroupe FROM liste WHERE NumListe=$selLISTE";
    QUERY($QUERY);
    if ($MAX > 0) {
	$titreListe = RESULT(0,0);
	$NumDest = RESULT(0,1);
	$numGroupe = RESULT(0,2);
    }
}
#
if (isset($_POST["repeatDest"])) $NumDest = $_POST["repeatDest"];
if (isset($_POST["repeatGroupe"])) $numGroupe = $_POST["repeatGroupe"];
if (isset($_POST["repeatTitre"])) $titreListe = $_POST["repeatTitre"];
#
switch ($selACTION) {
case 'newListe':
case 'editListe':
    $ONLOAD = "document.getElementById('nomDeListe').focus()";
    break;
default:
    $ONLOAD = "";
}
#
$maListeUtilisateur = $numId;
#
# Liste utilisateur que je controle
$QUERY = "SELECT NumUtilisateur FROM utilisateur WHERE Superviseur=$numId AND Superviseur!=0";
QUERY($QUERY);
if ($MAX > 0) {
    for ($j=0;$j<$MAX;$j++) {
	$maListeUtilisateur .= ",".RESULT($j,0);
    }
}
#
# Liste des groupes dont je suis proprio ou membre (direct ou indirect)
#
$QUERY = "SELECT NumGroupe FROM membre WHERE NumUtilisateur IN ($maListeUtilisateur)";
QUERY($QUERY);
if ($MAX > 0) {
    $groupListe = $comma = "";
    for ($j=0;$j<$MAX;$j++) {
	$groupListe .= $comma . RESULT($j,0);
	$comma = ",";
    }
}
#
# Toutes listes qui me concernent (proprio ou membre)
#
$QUERY = "SELECT l.NumListe,l.NomListe,u.NumUtilisateur,u.PrenomUtilisateur,u.NomUtilisateur,g.NomGroupe,g.NumGroupe";
$QUERY .= " FROM liste l, utilisateur u, groupe g";
$QUERY .= " WHERE l.NumUtilisateur=u.NumUtilisateur AND l.NumGroupe=g.NumGroupe ORDER BY l.NomListe";
$SQL1 = $QUERY;
QUERY($QUERY);
$liste_max = $MAX;
if ($liste_max > 0) {
    for ($j=0;$j<$liste_max;$j++) {
	$numLISTE[$j] = RESULT($j,0);
	$nomLISTE[$j] = RESULT($j,1);
	$numDEST[$j] = RESULT($j,2);
	$fnameUSER[$j] = RESULT($j,3);
	$lnameUSER[$j] = RESULT($j,4);
	$nomGROUPE[$j] = RESULT($j,5);
	if ($numLISTE[$j] == $selLISTE) {
	      $titreListe = $nomLISTE[$j];
	      $PrenomUtilisateur = $fnameUSER[$j];
	      $NomUtilisateur = $lnameUSER[$j];
	      $NomGroupe = $nomGROUPE[$j];
	      $NumDest = $numDEST[$j];
	      $numGroupe = RESULT($j,6);
	}
    }
}
#
echo "$HEADER

<body OnLoad=\"$ONLOAD\">

<FORM id=LISTE action='../controleurs/liste.php' method='post'>
<input type=hidden name=LEVEL value=10>
<input type=hidden name=ACTION id=ACTION value='$selACTION'>
<input type=hidden name=numLISTE id=numLISTE value='$selLISTE'>
<input type=hidden name=numId id=numId value=$numId>
<input type=hidden name=CADEAU id=CADEAU value=0>\n";
#
# CONTENU
$n = 1;
#
switch ($selACTION) {
case 'editListe':
case 'addCadeau':
case 'delCadeau':
    $exclus = "0";
    $n = 0;
    echo "
    <div id=liste5 class='liste5'>
	<h2 class=group2>Contenu de cette liste</h2>
	<div class='inner_liste5'>";
	$QUERY = "SELECT c.NumCadeau,c.NomCadeau FROM cadeau c, listecadeaux lc WHERE c.NumCadeau=lc.NumCadeau";
	$QUERY .= " AND lc.NumListe=$selLISTE ORDER BY c.NomCadeau";
	QUERY($QUERY);
	if ($MAX > 0) {
	    for ($j=0;$j<$MAX;$j++) {
		$numCADEAU = RESULT($j,0);
		$nomCADEAU = RESULT($j,1);
		$exclus .= "," . $numCADEAU;
		$n++;
		echo "
		<div class='nom_liste3 over' OnClick=\"select_list_action(5,$numCADEAU)\">$nomCADEAU</div>";
		#
	    }
	}
    echo "
	</div>";
    if ($MAX > 0) {
	echo "
	<div class='list_bouton2 over'
		OnClick=\"select_list_action(12,$selCADEAU);\">Vider cette liste</div>";
    }
    echo "
    </div>

    <div id=liste6 class='liste6'>
	<h2 class=group3>Catalogue</h2>
	<div class='inner_liste3'>";
	$QUERY = "SELECT NumCadeau,NomCadeau FROM cadeau WHERE NumCadeau NOT IN ($exclus)";
	$QUERY .= " ORDER BY NomCadeau";
	QUERY($QUERY);
	if ($MAX > 0) {
	    for ($j=0;$j<$MAX;$j++) {
		$numCADEAU = RESULT($j,0);
		$nomCADEAU = RESULT($j,1);
		echo "
		<div class='nom_liste3 over' OnClick=\"select_list_action(6,$numCADEAU)\">$nomCADEAU</div>";
		#
	    }
	}
    echo "
	</div>
    </div>";
}
#
switch ($selACTION) {
case 'newListe':
case 'editListe':
case 'destUser':
case 'destGroupe':
case 'addCadeau':
case 'delCadeau':
    if ($numGroupe > 0) {
	    $NomGroupe = control("val","SELECT NomGroupe FROM groupe WHERE NumGroupe=$numGroupe");
    }
    if ($NumDest > 0) {
	    $QUERY = "SELECT PrenomUtilisateur,NomUtilisateur FROM utilisateur WHERE NumUtilisateur=$NumDest";
	    QUERY($QUERY);
	    if ($MAX > 0) {
		$destNom = RESULT(0,0)."&nbsp;".RESULT(0,1);
	    }
    }
    echo "
    <div class='liste2'>
    <h2 class=group2>Gestion des listes</h2>
    <table border=0 cellspacing=2 celladding=0>
    <tr class=cat_text>
    <td class=list_right>Liste</td>
    <td><input type=text class=case16 id=titreListe name=titreListe value='$titreListe'>
    </td></tr>

    <tr class=cat_text>
    <td class=list_right>B&eacute;n&eacute;ficiaire</td>
    <td><input type=text class=case16 readonly id=destNom name=destNom value='$destNom'
	placeholder='cliquer pour remplir' OnClick=\"select_list_action(3,0);\">
	<input type=hidden id=numDest name=numDest value=$NumDest>
    </td></tr>

    <tr class=cat_text>
    <td class=list_right>Groupe</td>
    <td><input type=text class=case16 readonly id=destGroupe name=destGroupe value='$NomGroupe'
	placeholder='cliquer pour remplir' OnClick=\"select_list_action(4,0);\">
	<input type=hidden id=numGroupe name=numGroupe value=$numGroupe>
    </td></tr>
    </table>
    
    <div class='list_bouton1 over' OnClick=\"select_list_action(1,0);\">Enregistrer</div>";
    #
    if ($n == 0) {
	echo "
	<div class='list_bouton1 over' style='left:257px;background-color:red;'
	    OnClick=\"select_list_action(9,0);\">Supprimer</div>";
    }
    echo "
    </div>";
}
#
switch ($selACTION) {
case 'destUser':
    echo "
    <div id=liste3 class='liste3'>
	<h2 class=group2>Choisir le b&eacute;n&eacuteficiaire</h2>
	<div class='inner_liste3'>";
    $QUERY = "SELECT NumUtilisateur,PrenomUtilisateur,NomUtilisateur FROM utilisateur WHERE NumUtilisateur=$numId OR Superviseur=$numId";
    $QUERY .= " ORDER BY NomUtilisateur,PrenomUtilisateur";
    QUERY($QUERY);
    if ($MAX > 0) {
	for ($j=0;$j<$MAX;$j++) {
	    $uid = RESULT($j,0);
	    $prenom = addslashes(RESULT($j,1));
	    $nom = addslashes(RESULT($j,2));
	    echo "
	    <div class='nom_liste3 over' OnClick=\"
		document.getElementById('numDest').value='$uid';
		document.getElementById('destNom').value='$prenom $nom';
		document.getElementById('liste3').style.display='none';\">$prenom&nbsp;$nom</div>";
	    #
	}
    }
    echo "
	</div>
    </div>";
}
#
switch ($selACTION) {
case 'destGroupe':
    echo "
    <div id=liste4 class='liste3'>
	<h2 class=group2>Choisir le groupe associ&eacute;</h2>
	<div class='inner_liste3'>";
    $QUERY = "SELECT NumGroupe,NomGroupe FROM groupe WHERE NumUtilisateur IN ($maListeUtilisateur)";
    $QUERY .= " ORDER BY NomGroupe";
    QUERY($QUERY);
    if ($MAX > 0) {
	for ($j=0;$j<$MAX;$j++) {
	    $numGROUP = RESULT($j,0);
	    $nomGROUP = addslashes(RESULT($j,1));
	    echo "
	    <div class='nom_liste3 over' OnClick=\"
		document.getElementById('numGroupe').value='$numGROUP';
		document.getElementById('destGroupe').value='$nomGROUP';
		document.getElementById('liste4').style.display='none';\">$nomGROUP</div>";
	    #
	}
    }
    echo "
	</div>
    </div>";
}
#
echo "
<div class='liste1'>
    <h2 class=group1>Listes de cadeaux</h2>
    <div class='inner_band1'>
	<div class=ttlLeft style='width:180px;'>Nom de la liste</div>

	<div class=ttlLeft>B&eacute;n&eacute;ficiaire</div>

	<div class=ttlLeft>Groupe</div>
    </div>
    <div class='inner_liste1' style=width:525px;'>
    <table border=0 cellspacing=2 cellpadding=0 style='margin-top:-12px;margin-left:-2px;'>";
#
if ($liste_max > 0) {
    $a = explode(",",$maListeUtilisateur);
    for ($j=0;$j<$liste_max;$j++) {
	$numListe = $numLISTE[$j];
	$nomListe = $nomLISTE[$j];
	$NumDest = $numDEST[$j];
	$proprio = $fnameUSER[$j]."&nbsp;".$lnameUSER[$j];
	if ($numListe == $selLISTE) $PROPRIO = $proprio;
	$NomGroupe = $nomGROUPE[$j];
	$item = "";
	$mode = 2;
	if ($NumDest == $numId) {
	    $item = "blue_item";
	}
	elseif (in_array($NumDest,$a)) {
	    $item = "orange_item";
	}
	else $mode = 13;
	echo "
	<tr><td style='height:22px;'>
	<div class='nom_liste1 over' OnClick=\"select_list_action($mode,$numListe)\">
	    <div class=list_item>$nomListe</div>
	    <div class='dest_item ".$item."'>$proprio</div>
	    <div class=group_item>$NomGroupe</div>
	</div></td></tr>";
    }
}
echo "
    </table>
    </div>
    
    <div class='cat_bouton1 over' style='left:360px;'
	OnClick=\"select_list_action(0,0);\">Cr&eacute;er une liste</div>
</div>";
#
switch ($selACTION) {
case 'addCadeau':
case 'delCadeau':
    $exclus = "0";
    $n = 0;
    echo "
    <div id=liste7 class='liste7'>
	<h2 class=group4>Cadeau s&eacute;lectionn&eacute;</h2>
	<div class='inner_liste5'>";
	$QUERY = "SELECT NomCadeau,Descriptif,Lien FROM cadeau WHERE NumCadeau=$selCADEAU";
	QUERY($QUERY);
	if ($MAX > 0) {
		$nomCADEAU = RESULT(0,0);
		$txtCADEAU = str_replace("\n","<br>",RESULT(0,1));
		$lienCADEAU = RESULT(0,2);
		$IMG = sprintf("../cadeaux/img%07d.jpg", $selCADEAU);
		#
		echo "<p><input class=case type=text readonly value='$nomCADEAU'>
		<div class=desc7>$txtCADEAU</div>
		<div class=frame7><IMG class=cat_image src='../cadeaux/$IMG'></div>
		<div class=link7>
		<a target=_blank href= '$lienCADEAU'>Lien vers le site marchand</a></div>";
	}
    echo "
	</div>";
    #
    if ($selACTION == "addCadeau") {
	echo "
	<div class='list_bouton2 over'
		OnClick=\"select_list_action(10,$selCADEAU);\">Ajouter ce cadeau dans la liste</div>";
    }
    else {
	echo "
	<div class='list_bouton2 over'
		OnClick=\"select_list_action(11,$selCADEAU);\">Retirer ce cadeau dans la liste</div>";
    }
    echo "
    <div class='list_bouton2 over' style='left:20px;'
		OnClick=\"document.getElementById('liste7').style.display='none';\">Masquer</div>
    </div>";
}
#
switch ($selACTION) {
case 'voirListe':
    $a = explode(",",$maListeUtilisateur);
    echo "
    <div id=liste8 class='liste8'>
	<h2 class=group2>Liste de $PROPRIO</h2>
	<div class='inner_liste5' style='padding:2px;'>
	<table border=0 cellspacing=0 cellpadding=0 style='margin:0px;'>";
	$QUERY = "SELECT c.NumCadeau,c.NomCadeau,lc.NumAcheteur FROM cadeau c, listecadeaux lc WHERE c.NumCadeau=lc.NumCadeau";
	$QUERY .= " AND lc.NumListe=$selLISTE ORDER BY c.NomCadeau";
	QUERY($QUERY);
	if ($MAX > 0) {
	    for ($j=0;$j<$MAX;$j++) {
		$numCADEAU = RESULT($j,0);
		$nomCADEAU = RESULT($j,1);
		$numAcheteur = RESULT($j,2);
		$item = "";
		$me = 0;
		if ($numAcheteur == $numId) {
		    $item = "background-color:blue;color:white;";
		    $me = 3;
		}
		elseif (in_array($numAcheteur,$a)) {
		    $item = "background-color:orange;";
		    $me = 2;
		}
		elseif ($numAcheteur > 0) $me = 1;
		echo "
		<tr><td class=cell8>
		<div class='nom_liste3 over' style='margin-top:1px;$item'>$nomCADEAU</div></td>
		<td>";
		#
		switch ($me) {
		case 2:
		case 3:
		    echo "<div class='bouton8 over' style='margin-top:-4px;'
		    OnClick=\"select_list_action(15,$numCADEAU)\">Abandon</div>";
		    break;
		case 1:
		    echo "&nbsp;";
		    break;
		default:
		    echo "<div class='bouton8 over' OnClick=\"select_list_action(14,$numCADEAU)\">Achat</div>";
		    break;
		}
		#
		echo "</td></tr>";
	    }
	}
    echo "</table>
	</div>
    </div>";
}
#
echo "
</form>

<FORM id=NEXT action='index.php' method='post'>
<input type=hidden name=LEVEL id=LEVEL value=10>
<input type=hidden name=selLISTE id=selLISTE value=$selLISTE>
<input type=hidden name=selCADEAU id=selCADEAU value=0>
<input type=hidden name=selACTION id=selACTION value='rien'>
<input type=hidden name=repeatTitre id=repeatTitre value=''>
<input type=hidden name=repeatDest id=repeatDest value=0>
<input type=hidden name=repeatGroupe id=repeatGroupe value=0>
</FORM>

$MEMBER

<script language=JavaScript1.2>
function select_list_action(action, val) {
    switch (parseInt(action)) {
    case 0:
	// Créer une liste
	document.getElementById('selLISTE').value=0;
	document.getElementById('selACTION').value='newListe';
	document.getElementById('NEXT').submit();
	break;
    case 1:
	// Soumettre la liste
	document.getElementById('LISTE').submit();
	break;
    case 2:
	// Editer une liste
	document.getElementById('selLISTE').value=val;
	document.getElementById('selACTION').value='editListe';
	document.getElementById('NEXT').submit();
	break;
    case 3:
	// Lister les bénéficiaires
	document.getElementById('repeatTitre').value=document.getElementById('titreListe').value;
	document.getElementById('repeatDest').value=document.getElementById('numDest').value;
	document.getElementById('repeatGroupe').value=document.getElementById('numGroupe').value;
	document.getElementById('selACTION').value='destUser';
	document.getElementById('NEXT').submit();
	break;
    case 4:
	// Lister les groupes
	document.getElementById('repeatTitre').value=document.getElementById('titreListe').value;
	document.getElementById('repeatDest').value=document.getElementById('numDest').value;
	document.getElementById('repeatGroupe').value=document.getElementById('numGroupe').value;
	document.getElementById('selACTION').value='destGroupe';
	document.getElementById('NEXT').submit();
	break;
    case 5:
	// Afficher descriptif cadeau avec bouton suppresion
	document.getElementById('selCADEAU').value=val;
	document.getElementById('selACTION').value='delCadeau';
	document.getElementById('NEXT').submit();
	break;
    case 6:
	// Afficher descriptif cadeau avec bouton ajouter
	document.getElementById('selCADEAU').value=val;
	document.getElementById('selACTION').value='addCadeau';
	document.getElementById('NEXT').submit();
	break;
    case 9:
	// Détruire une liste
	document.getElementById('ACTION').value='supprimListe';
	document.getElementById('LISTE').submit();
	break;
    case 10:
	// Ajoute cadeau dans la liste
	document.getElementById('CADEAU').value=val;
	document.getElementById('ACTION').value='ajoutCadeau';
	document.getElementById('LISTE').submit();
	break;
    case 11:
	// Retirer cadeau de la liste
	document.getElementById('CADEAU').value=val;
	document.getElementById('ACTION').value='retirerCadeau';
	document.getElementById('LISTE').submit();
	break;
    case 12:
	// Vider la liste
	document.getElementById('ACTION').value='videListe';
	document.getElementById('LISTE').submit();
	break;
    case 13:
	// Vider la liste
	document.getElementById('selLISTE').value=val;
	document.getElementById('selACTION').value='voirListe';
	document.getElementById('NEXT').submit();
	break;
    case 14:
	// Retirer cadeau de la liste
	document.getElementById('CADEAU').value=val;
	document.getElementById('ACTION').value='achatCadeau';
	document.getElementById('LISTE').submit();
	break;
    case 15:
	// Retirer cadeau de la liste
	document.getElementById('CADEAU').value=val;
	document.getElementById('ACTION').value='abandonCadeau';
	document.getElementById('LISTE').submit();
	break;
    }
}
</script>

</body>
</html>";
?>