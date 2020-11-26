<?php
#
echo "$HEADER

<body>

<FORM id=MEMBRE action='../controleurs/membre.php' method='post'>
<input type=hidden name=LEVEL value=0>
<input type=hidden name=ACTION id=ACTION value='rien'>
<input type=hidden name=selINVIT id=selINVIT value=0>
</FORM>\n";
#
$QUERY = "SELECT g.NomGroupe,u.PrenomUtilisateur,u.NomUtilisateur,i.NumInvitation FROM groupe g, utilisateur u, invitation i";
$QUERY .= " WHERE i.NumGroupe=g.NumGroupe AND i.NumUtilisateur=u.NumUtilisateur ORDER BY i.NumInvitation";
QUERY($QUERY);
if ($MAX > 0) {
    echo "
<div class='membre1'>
    <h2 class=group1>INVITATION</h2>
    <div class='inner_band1'>
	<div class=ttlLeft style='width:200px;'>Vous &ecirc;tes invit&eacute; par</div>

	<div class=ttlLeft style='width:320px;'>&agrave; rejoindre le groupe</div>
    </div>
    <div class='inner_liste1' style='bottom:10px;'>
    <table border=0 cellspacing=2 cellpadding=0 style='margin-top:-12px;margin-left:-2px;'>";
    for ($j=0;$j<$MAX;$j++) {
	$groupe = RESULT($j,0);
	$nom = RESULT($j,1)."&nbsp;".RESULT($j,2);
	$numInvit = RESULT($j,3);
	echo "
	<tr><td style='height:23px;'>
	<div class='nom_liste1 over'>
	    <div class=list_item style='width:250px;'>$nom</div>
	    <div class=group_item style='left:260px;width:240px;'>$groupe</div>
	</div></td>

	<td><div class='bouton8 over' style='top:11px;left:-4px;'
	    OnClick=\"select_action(1,$numInvit);\">Accepter</div></td>

	<td><div class='bouton8 over' style='top:11px;background-color:red;'
	    OnClick=\"select_action(0,$numInvit);\">Refuser</div></td>
	</tr>";
    }
echo "
    </table>
    </div>
</div>";
}

if (isset($_POST["welcome"])) {
    echo "
    <div class='welcome'>
	<h2 class=bienvenue>Bonjour <span style='color:yellow;'>$prenom</span> !</h2>
    <br>
    <h2 class=black>Bienvenue dans ton espace de No&euml;l</h2>";
}
else {
    echo "
    <div class='fantome'>";
    if (isset($_POST["MSG"])) {
	echo "
	<div class='erreur info'>".$_POST["MSG"]."</div>";
    }
    echo "
    </div>";
}
#
echo "
<FORM id=NEXT action='index.php' method='post'>
<input type=hidden name=LEVEL id=LEVEL value=99>
</FORM>

</div>
$MEMBER

<script language=JavaScript1.2>
function select_action(action, val) {
    document.getElementById('selINVIT').value=val;

    switch (parseInt(action)) {
    case 0:
	// Refuse l'invitation
	document.getElementById('ACTION').value='nonInvit';
	document.getElementById('MEMBRE').submit();
	break;
    case 1:
	// Accepter l'invitation
	document.getElementById('ACTION').value='ouiInvit';
	document.getElementById('MEMBRE').submit();
	break;
    }
}
</script>

</body>
</html>";
?>