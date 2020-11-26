<?php
#
# Creation de rien
if (! isset($numId)) $numId = 0;
$LOGIN = $nom = $prenom = $email = $mdp = $birth = "";
#
if (isset($_POST["FOCUS"])) {
    $FOCUS = $_POST["FOCUS"];
    $LOGIN = $_POST["LOGIN"];
    $nom   = $_POST["nom"];
    $prenom = $_POST["prenom"];
    $email = $_POST["email"];
    $birth = $_POST["birth"];
}
else $FOCUS = "login";
$DEBUG = 0;
switch ($DEBUG) {
case 1:
    echo "<pre>";
    print_r($_POST);
    exit;
}
#
if ($LEVEL == 100) {
    $QUERY = "SELECT NomUtilisateur,PrenomUtilisateur,Courriel FROM utilisateur";
    $QUERY .= " WHERE NumUtilisateur=$numId";
    QUERY($QUERY);
    #echo "<pre>max = $MAX\n$QUERY\n";exit;
    if ($MAX > 0) {
	$nom = RESULT(0,0);
	$prenom = RESULT(0,1);
	$email = RESULT(0,2);
	$LOGIN = $birth = "";
    }
}
#
echo "$HEADER

<body OnLoad=\"document.getElementById('$FOCUS').focus();\">

<nav class='navclass4'>
    <h2 class=bienvenue>Formulaire d'inscription</h2>
    <form id=REGISTER action='../controleurs/enregistrement.php' method='post'>
    <input type=hidden name='numId' value=$numId>
    <input type=hidden name='LEVEL' value=$LEVEL>

    <div class='test' style='top:50px;'>
	<p><input class=case type=text name=login id=login placeholder='Mon login'
	      style='text-transform:lowercase;' value='$LOGIN'
		OnKeyPress=\"return checkChar('next','nom',event);\"/></p>

	<p><input class=case type=text name=nom id=nom placeholder='Mon nom'
	      style='text-transform:uppercase;' value='$nom'
		OnKeyPress=\"return checkChar('next','prenom',event);\"/></p>

	<p><input class=case type=text name=prenom id=prenom placeholder='Mon pr&eacute;nom' value='$prenom'
		OnKeyPress=\"return checkChar('next','email',event);\"/></p>

	<p><input class=case type=text name=email id=email placeholder='Mon email' value='$email'
	      style='text-transform:lowercase;'
		OnKeyPress=\"return checkChar('next','mdp',event);\"/></p>

	<p><input class=case type=password name=mdp id=mdp placeholder='Mon mot de passe'
		OnKeyPress=\"return checkChar('next','naissance',event);\"/></p>

	<p><div class=date_pack>
	      <div class=date_label>Date de naissance</div>
	      <div class=date_input>
	      <input class='case date' type=date name=naissance id=naissance value='$birth'
		OnKeyPress=\"checkChar('submit','REGISTER',event);\"/></div>
	   </div>
	</p>
    </div>

    <input class='bouton1' type='submit' name='Valider' Value='Valider'/>
    </form>

    <FORM id=NEXT action='index.php' method='post'>
    <input type=hidden name=LEVEL id=LEVEL value=0>
    </FORM>
    <div class='bouton1 bouton3' OnClick=\"document.getElementById('NEXT').submit();\">Annuler</div>";
#
if (isset($_POST["ERR"])) {
    echo "
    <div class='erreur'>".$_POST["ERR"]."</div>";
}
echo "
</nav>

$BASIC

</body>
</html>";
?>