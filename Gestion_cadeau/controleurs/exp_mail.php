<?php
#
#~~~~~~
# Init
#~~~~~~~
$FROM_FILE = "../controleurs/support3.txt";
#
$GLOBALS["SQL_SOURCE"] = "exp_mail";
$page = "email";
#
/*
$QUERY = "SELECT uid,email,fname FROM users WHERE login='$LOGIN'";
QUERY($QUERY);
if ($MAX > 0) {
	$uid = RESULT(0,0);
	$email = RESULT(0,1);
	$fname = RESULT(0,2);
}
*/
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Data for generating access key
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
$section = "A,B,C,D,E,F,G,R,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,0,1,2,3,4,5,6,7,8,9";
$alpha = explode(",", "$section,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,-,_");
$lg = count($alpha) - 1;
$size = 40;
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~
# Generate new access key
#~~~~~~~~~~~~~~~~~~~~~~~~~~~
$key = "";
$mimick_rank = rand(0,9);
$target_rank = 26 + $mimick_rank;
for ($c=0;$c<$size;$c++) {
	$rank = rand(0,$lg);
	switch ($c) {
	case 1:
		$mimick_val = $alpha[$rank];
		$key .= $mimick_val;
		break;

	case 2:
		$key .= $mimick_rank;
		break;

	case $target_rank:
		$key .= $mimick_val;
		break;
	default:
		$key .= $alpha[$rank];
	}
}
#
#~~~~~~~~~~~~~~
# Message link
#~~~~~~~~~~~~~~~
$masterSN = dirname(dirname($_SERVER["SCRIPT_NAME"]))."/vue/index.php";
$url = "https://".$_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$masterSN;
$clef_MdP = $url."?k!".$key."!";
#
#~~~~~~~~~~~~~~~~
# Sauver la clef
#~~~~~~~~~~~~~~~~~
if (isset($numInvit)) {
	WRITE("UPDATE invitation set clef='$key' WHERE NumInvitation=$numInvit");
}
#
#~~~~~~~~~~~~
# Build mail
#~~~~~~~~~~~~~
switch ($numMessage) {
case 0:
$PRENOM = utf8_decode($prenom);
$Subject = "P&P Gift: invitation à vous inscrire sur notre site de Noël";
$SUCCESS = utf8_encode("Compte créé et invitation envoyée à") . $prenom;
#
#$Subject = utf8_encode("P&P Gift: invitation à vous inscrire sur notre site de Noël");
$MESSAGE = "<!DOCTYPE HTML>
<html lang='fr_FR'>
<head>
<title>Invitation P&P Gift</title>
<meta http-equiv='content-type' content='text/html; charset=utf8'>
</head>

<style>
a:link {
  text-decoration: none;
  font-weight: bold;
  color: #336699;
  font-size:18px;
}
a:visited {
  text-decoration: none;
  font-weight: bold;
  color: #6699CC;
  font-size:18px;
}
a:hover, a:active {
  font-weight: bold;
  color: #000033;
  font-style: italic;
  text-decoration: none;
  font-size:18px;
}
.redArial14B {
	font-family: Arial,Helvetica;
	font-size: 14px;
	font-weight: bold;
	color: red;
}
.dBlueArial12B {
	font-family: Arial,Helvetica;
	font-size: 12px;
	font-weight: bold;
	color: darkblue;
}
</style>

<body id=mailBody style='font-family:arial,helvetica;font-size:12px;color:darkblue;'>
<p class=dBlueArial12B>Bonjour $PRENOM,</p>
<p>Ceci est un message automatique vous permettant de vous inscrire sur notre site
<a href='".$clef_MdP."'>P&amp;P_Gift</a> développé dans le cadre d'un exercice informatique
réel par des élèves de l'Université Paris-Sud.</p>

<p><b>Fini le casse-tête de Noël !</b> Plus d'achats en double ni de cadeaux qui déplaisent.
Ce site convivial et intuitif vous permettra de créer en ligne des listes de cadeaux
à partager avec vos amis, vos collègues ou encore votre famille.
Les plus petits sans compte &laquo;courriel&raquo; ne sont pas oubliés. Ils peuvent disposer
d'un compte géré par leurs parents.</p>

<p>Pour découvrir le site, il vous suffit de cliquer sur le lien ci-apr&egrave;s pour finaliser votre inscription :
&nbsp;<a href='".$clef_MdP.">P&amp;P_Gift</a><br>
<p class=redArial14B>Attention, la clef associée au lien ci-dessus est &agrave; usage unique.</p>

<p class=dBlueArial12B>Bien cordialement,<br>
Les deux Pierre.</p>
<p>&nbsp;</p></body></html>\n";
break;

case 1:
$PRENOM = utf8_decode($prenom);
$Subject = "P&P Gift: invitation à rejoindre le groupe $GROUPE";
$SUCCESS = utf8_encode("Invitation simple envoyée à ") . $prenom;
#
$MESSAGE = "<!DOCTYPE HTML>
<html lang='fr_FR'>
<head>
<title>Invitation P&P Gift</title>
<meta http-equiv='content-type' content='text/html; charset=utf8'>
</head>

<style>
a:link {
  text-decoration: none;
  font-weight: bold;
  color: #336699;
  font-size:18px;
}
a:visited {
  text-decoration: none;
  font-weight: bold;
  color: #6699CC;
  font-size:18px;
}
a:hover, a:active {
  font-weight: bold;
  color: #000033;
  font-style: italic;
  text-decoration: none;
  font-size:18px;
}
.redArial14B {
	font-family: Arial,Helvetica;
	font-size: 14px;
	font-weight: bold;
	color: red;
}
.dBlueArial12B {
	font-family: Arial,Helvetica;
	font-size: 12px;
	font-weight: bold;
	color: darkblue;
}
</style>

<body id=mailBody style='font-family:arial,helvetica;font-size:12px;color:darkblue;'>
<p class=dBlueArial12B>Bonjour $PRENOM,</p>
<p>Ce message automatique vous signale, que vous êtes invité(e) à rejoindre le groupe <b>&laquo;$GROUPE&raquo;</b>
sur votre site de Noël: <a href='".$url."'>P&amp;P_Gift</a>.</p>

<p class=dBlueArial12B>Bien cordialement,<br>
Les deux Pierre.</p>
<p>&nbsp;</p></body></html>\n";
break;
}

$ref_char = substr($key,1,1);
$target = 26 + substr($key,2,1);
$dup_char = substr($key,$target,1);
$DEBUG = 0;
if ($DEBUG > 0) {
	#~~~~~~~~~~~~~~~
	# Debug display
	#~~~~~~~~~~~~~~~~
	echo "<pre>";
	echo "From = $email\n";
	echo "Subj = $Subject\n";
	echo "</pre>";
	##$MESSAGE = str_replace("<br>","\n",$MESSAGE);
	echo "$MESSAGE\n";
	exit;
}
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Inclusion des classes de PHPMailer
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
require "../controleurs/class.phpmailer.php";
require "../controleurs/class.smtp.php";
#
#~~~~~~~~~~~~~~
# Send message
#~~~~~~~~~~~~~~~
if (file_exists($FROM_FILE)) {
	$fp = fopen($FROM_FILE,"r");
	#
	while (!feof($fp)) {
		$line = rtrim(fgets($fp, 500));
		if (stristr($line, "=")) {
			list($ope_param, $ope_val) = explode("=", $line);
			switch ($ope_param) {
			case "name":
				$FromName = $ope_val;
				break;
			case "sendmail":
				$sendmail = $ope_val;
				break;
			case "mdp":
				$supportMdp = $ope_val;
				break;
			case "response":
				$noreply = $ope_val;
				break;
			case "smtp":
				$smtp_account = $ope_val;
				break;
			}
		}
	}
	fclose($fp);
	#
	/*
	echo "<pre>FromName:$FromName\n";
	echo "sendmail:$sendmail\n";
	echo "supportMdp:$supportMdp\n";
	echo "smtp:$smtp_account\n";
	exit;
	*/
	#
	$mail = new PHPMailer;
	#
	switch ($smtp_account) {
	case "gmail":
		$mail->FromName = "$FromName";
		#$mail->CharSet="UTF-8";
		$mail->From = $sendmail;
		$mail->AddReplyTo($noreply, 'NE PAS REPONDRE');
		$mail->isSMTP();
		$mail->Host = 'smtp.gmail.com';
		$mail->Port = 465;
		$mail->SMTPAuth = true;
		$mail->SMTPSecure = 'tls';
		$mail->Username = $sendmail;
		$mail->Password = $supportMdp;
		break;

	case "office365":
		$mail->FromName = "$FromName";
		$mail->CharSet="UTF-8";
		$mail->From = $sendmail;
		$mail->AddReplyTo($noreply, 'NE PAS REPONDRE');
		$mail->isSMTP();
		$mail->Host = 'smtp.office365.com';
		$mail->Port = 587;
		$mail->SMTPAuth = true;
		$mail->SMTPSecure = 'tls';
		$mail->Username = $sendmail;
		$mail->Password = $supportMdp;
		break;

	case "mailfr":
		$mail->FromName = "$FromName";
		$mail->From = $sendmail;
		$mail->AddReplyTo($noreply, 'NE PAS REPONDRE');
		$mail->isSMTP();
		$mail->Host = 'smtp.mail.fr';
		$mail->Port = 587;
		$mail->SMTPAuth = true;
		$mail->SMTPSecure = 'tls';
		$mail->Username = $sendmail;
		$mail->Password = $supportMdp;
		break;

	default:
		$MSG = "Erreur: le serveur du compte d'envoi n'est pas d&eacute;fini";
		exit;
	}
	$mail->addAddress("$email");
	$mail->isHTML(true);
	$mail->Subject = $Subject;
	$mail->Body = "$MESSAGE";
	if ($mail->send()) {
		$MSG = $SUCCESS;
	}
	else {
		$MSG = utf8_encode("Echec de l'envoi a $prenom avec erreur: ") . $mail->ErrorInfo;
	}
}
else {
	$MSG = "Erreur: le compte d'envoi n'est pas configuré";
}
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>
