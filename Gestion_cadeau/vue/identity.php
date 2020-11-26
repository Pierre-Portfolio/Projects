<?php
#
# Creation de rien
if (! isset($numId)) $numId = 0;
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
    echo "<pre>
    pass 4:
    LEVEL: $LEVEL
    LOGIN: $LOGIN
    nom: $nom
    prenom: $prenom
    mail: $email
    date: $birth\n";
    exit;
}
#
echo "$HEADER

<body OnLoad=\"document.getElementById('$FOCUS').focus();\">

<nav class='navclass4'>
    <h2 class=bienvenue>Modifier mes donn&eacute;es</h2>
    <form id=REGISTER action='../controleurs/enregistrement.php' method='post'>
    <input type=hidden name='numId' value=$numId>
    <input type=hidden name='LEVEL' value=$LEVEL>
    <input type=hidden name='mdp' value=0>

    <div class='test' style='top:70px;'>
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

$MEMBER

</body>
</html>";
?>