<?php
###########################################################################################
# File   : NewPass.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Changement du Password.
# -----------------------------------------------------------------------------------------
#
#~~~~~~
# Init
#~~~~~~~
$GLOBALS["SQL_SOURCE"] = "OSE:NewPass";
#
switch ($OP) {
case "new2day":
    $psw0 = "new2day";
    $_SESSION["new2day"] = 1;
    break;


case "success":
    ###########################################
    # Successful status for changing password
    ###########################################
    echo "
    <div style='position:absolute;top:0px;left:0px;margin:0px;width:100%;height:100%;background-color:#000080;'>
	<div style='position:absolute;top:25%;left:10%;width:400px;height:62px;margin:0px;border:1px solid white;'>
	    <div class=whiteArial14B style='position:absolute;top:2px;left:2px;bottom:2px;right:2px;
		font-size:18px;margin:0px;padding:8px 16px 8px 16px;text-align:center;
		background-color:$color14;'>Changement du mot de passe effectu&eacute;<br>
		avec succ&egrave;s
	    </div>
	</div>
    </div>
    </body></html>\n";
    exit;

    default:
    if (!isset($psw0)) $psw0 = "";
}
#
$success = 0;
if (!isset($passSEL)) $passSEL = "new";
if (!isset($psw1)) $psw1 = "";
if (!isset($psw2)) $psw2 = "";
#
$DEBUG = 0;
switch ($DEBUG) {
case 1:
    echo "
    <div style='position:absolute;top:10px;left:600px;padding:0px 20px 0px 12px;
    background-color:lemonchiffon;border:2px solid black;'>
    <pre>passSEL=$passSEL\nLOGIN: $LOGIN\nOP: $OP\n\n";
    print_r($_POST);
    echo "\n</div>";
}

switch (trim($passSEL)) {
case "save":
    switch (1) {
    default:
	#if (!isset($mode) || $mode != "Passwd") break;
	if ($psw1 == "new2day") {
		#$passSEL = "new2day";
		$warning = "<SPAN style='color: $tcolor3;'>new2day</SPAN> est un mot r&eacute;serv&eacute;&nbsp; Recommencez, S.V.P.";
		break;
	}

	#################
	## Test egalite
	#################
	if ($psw1 != $psw2) {
		$warning = "<SPAN style='color: $tcolor3;'>In&eacute;galit&eacute; entre nouvelles valeurs!</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	##################
	## Test longueur
	##################
	if (strlen($psw1) < 8) {
		$warning = "<SPAN style='color: $tcolor3;'>Longueur insuffisante!</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	if ($psw1 == $psw0) {
		$warning = "<SPAN style='color: $tcolor3;'>Mot de passe identique!</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	###################
	## Test minuscule
	###################
	$lg = strlen($psw1);
	$found = 1;
	if (strtoupper($psw1) == $psw1) $found = 0;
	if ($found == 0) {
		$warning = "<SPAN style='color: $tcolor3;'>Aucune minuscule d&eacute;tect&eacute;e !</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	###################
	## Test majuscule
	###################
	$found = 1;
	if (strtolower($psw1) == $psw1) $found = 0;
	if ($found == 0) {
		$warning = "<SPAN style='color: $tcolor3;'>Aucune MAJUSCULE d&eacute;tect&eacute;e !</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	#################
	## Test chiffre
	#################
	$found = 0;
	$chiffres = explode(","," ,0,1,2,3,4,5,6,7,8,9");
	for ($j=0;$j<$lg;$j++) {
	    $char = substr($psw1,$j,1);
	    if (in_array($char,$chiffres)) {
		$found = 1;
		break;
	    }
	}
	if ($found == 0) {
		$warning = "<SPAN style='color: $tcolor3;'>Aucun chiffre d&eacute;tect&eacute; !</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	########################
	## Test chars speciaux
	########################
	$found = 0;
	$speciaux = explode("|"," |,|.|;|:|/|?|-|_|!");
	for ($j=0;$j<$lg;$j++) {
	    $char = substr($psw1,$j,1);
	    if (in_array($char,$speciaux)) {
		$found = 1;
		break;
	    }
	}
	if ($found == 0) {
		$warning = "<SPAN style='color: $tcolor3;'>Aucun caract&egrave;re sp&eacute;cial d&eacute;tect&eacute; !</SPAN> &nbsp; Recommencez, S.V.P.";
		break;
	}

	$pswcheck = control("val","select passwd from $IDENTIFIER_TABLE where uid='$uid'");
	if (password_verify($psw0,$pswcheck) == $pswcheck) {
		$pass = password_hash($psw1, PASSWORD_DEFAULT);
		$now = date("Y/m/d H:i:s");
		$today = date("Y/m/d");
		$REQ = "UPDATE $IDENTIFIER_TABLE set passwd='$pass',laccess='$now',chgpass='$today' where uid='$uid'";
		WRITE("$REQ");
		$success = 1;
		if ($psw0 == "new2day") $OP = "refreshMENU";
	}
	else {
		$warning = "<SPAN style='color: $tcolor3;'>Ancien mot de passe incorrect!</SPAN> &nbsp; Recommencez, S.V.P.";
		$focusOLD = 1;
	}
    }

case "new2day":
case "new":
	if (isset($focusOLD) && $focusOLD == 1 && ! in_array($OP, array("new2day","refreshMENU"))) $pswFOCUS = "psw0";
	else $pswFOCUS = "psw1";
	echo "\n<script language='JavaScript1.2'>
	<!--
	function checkChar(field,e) {
		if (document.all) {
			// IE5
			var keyCode = e.keyCode;
			// alert ('Entry code: ' + keyCode + ' field: ' + field);
			switch (e.keyCode) {
			case 13:
				if (field == 'psw1') {
					document.getElementById('psw2').focus();
					e.returnValue = false;
					return false;
				}
				if (field == 'psw0') {
					document.getElementById('psw1').focus();
					e.returnValue = false;
					return false;
				}
				submit_password();
				return false;
			}
		}
		else if (document.getElementById) {
			// NS7
			var keyCode = document.getElementById ? e.keyCode : 0;
			// alert ('Entry code: ' + keyCode);

			switch (keyCode) {
			case 13:
				if (field == 'psw1') {
					e.stopPropagation();
					document.getElementById('psw2').focus();
					return false;
				}
				if (field == 'psw0') {
					e.stopPropagation();
					document.getElementById('psw1').focus();
					return false;
				}
				submit_password();
			}
		}
	}
	//-->
	</script>\n\n";

	echo "<div style='position:absolute;top:0px;left:0px;margin:0px;width:100%;height:100%;
	background-color:#000080;'>";
#
#########################
## DEBUG
#########################
	switch ($DEBUG) {
	case 0:
	    break;
	default:
	    echo "
	    <div style='position:absolute;top:10px;left:600px;padding:0px 20px 0px 12px;
	    background-color:lemonchiffon;border:2px solid black;'>
	    <pre>passSEL=$passSEL\nLOGIN: $LOGIN\nOP: $OP\n\n";
	    print_r($_POST);
	    echo "\n</div>";
	}
#
##############
## FIN DEBUG
##############
	if ($success == 1) {
	    unset($_SESSION["new2day"]);
	    if ($OP == "refreshMENU") {
		echo "<script language=JavaScript>top.force_new2day=0;top.set_admin_menu(0);</script>\n";
		exit;
	    }
	    #
	    echo "
	    <div style='position:absolute;top:25%;left:10%;width:400px;height:62px;margin:0px;
		border:1px solid white;'>
	    <div class=whiteArial14B style='position:absolute;top:2px;left:2px;bottom:2px;right:2px;
		font-size:18px;margin:0px;padding:8px 16px 8px 16px;text-align:center;
		background-color:$color14;'>Changement du mot de passe effectu&eacute;<br>
		avec succ&egrave;s</div></div>\n";
	    exit;
	}

	echo "
	<div style='position:absolute;top:20%;left:10%;width:400px;height:214px;margin:0px;border:1px solid white;'>
	<div style='position:absolute;top:2px;left:2px;bottom:2px;right:2px;margin:0px;background-color:$color14;'>";

	if (isset($warning) && $warning != "") {
	    echo "
	    <div style='position:absolute;top:-54px;left:-40px;margin:0px;right:-40px;'>
	    <div style='position:absolute;top:0px;left:0px;right:0px;height:33px;border:1px solid white;'>
	    <div class=whiteArial12B style='padding:4px 6px 6px 6px;font-size:16px;text-align:center;background-color:$color1;
	      margin:2px;'>$warning</div></div></div>\n";
	}
	elseif ($psw0 == "new2day") {
	    echo "
	    <div style='position:absolute;top:-84px;left:-40px;margin:0px;right:-40px;'>
	    <div style='position:absolute;top:0px;left:0px;right:0px;height:71px;border:1px solid white;'>
	    <div class=whiteArial12B style='padding:4px 6px 6px 6px;font-size:16px;text-align:center;background-color:$color14;
	      margin:2px;'>Par mesure de s&eacute;curit&eacute; vous ne pouvez pas conserver<br>
		&laquo; <SPAN style='color: $color8;'>new2day</SPAN> &raquo; comme mot de passe permanent.<br>
		<SPAN style='color: $color8;'>Veuillez en changer, S.V.P.</div></div></div>\n";
	}
	elseif ($passSEL == "new") {
	    echo "
	    <div style='position:absolute;top:-54px;left:0px;margin:0px;width:100%;'>
	    <div style='position:absolute;top:0px;left:56px;right:56px;height:33px;border:1px solid white;'>
	    <div class=whiteArial14B style='padding:4px 6px 6px 6px;font-size:16px;text-align:center;background-color:$color14;
	      margin:2px;'>Changement du mot de passe</div></div></div>\n";
	}

	echo "
	<div class=whiteArial12b style='position:relative;top:0px;left:0px;height:98px;margin:0px;padding:6px;
	  border:0px solid $color5;'>
	R&egrave;gles pour le mot de passe:<UL style='font-weight:normal;'>
	<LI>8 caract&egrave;res minimum</LI>
	<LI>Au moins une minuscule</LI>
	<LI>Au moins une majuscule</LI>
	<LI>Au moins un caract&egrave;re sp&eacute;cial dans la liste entre crochets:
	      <br>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
	      &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
	      [<SPAN class=whiteArial14B> , . ; : / ? - _ ! </SPAN>]</LI></div>
	<table border=0 cellpadding=0 cellspacing=0 style='margin-left:60px;'>
	<FORM name=form1 id=form1 action='$SN' method=POST>
	<input type=hidden name=uid value='$uid'>
	<input type=hidden name=passSEL value=save>\n";

	if ($passSEL == "new2day" or $psw0 == "new2day") {
		echo "<input type=hidden name=psw0 value='new2day'>\n";
	}
	else {
		echo "<tr><td class=whiteArial12b
			style='text-align:right;padding:0px 0px 0px 20px;white-space:nowrap;'>Ancien mot de passe:</td>
		<td style='padding:3px 10px 3px 6px;'>
		<input class=dBlueArial11B type=password name=psw0 id=psw0 maxLength=15 size=15 value='$psw0'
			style='border:1px solid $color6;padding:1px 3px 1px 3px;color:$tcolor3;'
			OnKeyPress=\"checkChar('psw0',event);\"></td></tr>\n\n";
	}

	echo "<tr class=whiteArial12b><td style='text-align:right;padding:0px 0px 0px 4px;white-space:nowrap;'>Nouveau mot de passe:</td>
	<td style='padding:3px 10px 3px 6px;'>
	<input class=dBlueArial11B type=password name=psw1 id=psw1 maxLength=15 size=15 value='$psw1'
			style='border:1px solid $color6;padding:1px 3px 1px 3px;'
			OnKeyPress=\"checkChar('psw1',event);\"></td></tr>

	<tr class=whiteArial12b><td style='text-align:right;padding:0px 0px 0px 20px;'>Confirmation:</td>
	<td style='padding:3px 10px 3px 6px;'>
	<input class=dBlueArial11B type=password name=psw2 id=psw2 maxLength=15 size=15 value='$psw2'
			style='border:1px solid $color6;padding:1px 3px 1px 3px;'
		OnKeyPress=\"checkChar('psw2',event);\"></td></tr>

  	<tr><td></td><td>
	<div class=varButtonBlue11B style='width:60px;height:13px;padding:1px 8px 1px 8px;margin:6px 0px 0px 26px;
			border:2px solid $color17;background-color:$color5;color:$tcolor1;'
		OnClick='submit_password();'>Valider</div></td></tr>\n";

	$post_count=count($_POST);
	$post_data=array_keys($_POST);
	for ($i=0;$i<$post_count;$i++) {
		switch ($post_data[$i]) {
		case 'LOGIN':
		case 'uid':
		case 'psw0':
		case 'psw1':
		case 'psw2':
		case 'cookieSET':
		case 'passSEL':
		case 'submit':
			break;
		default:
			$temp = $post_data[$i];
			$$temp = $_POST["$temp"];
			echo "\t<input type=hidden name=$temp id=$temp value='$$temp'>\n";
			break;
		}
		$debug = 0;
		if ($debug == 3) {
			echo "<PRE>";
			print_r($_POST);
			echo "</PRE>";
		}
	}

	echo "</FORM>
	</table>
	<script language='JavaScript1.2'>
	<!--
	function submit_password() {
	    if (document.getElementById('OP').value == 'new2day') document.getElementById('OP').value='refreshMENU';
	    document.getElementById('mode').value='Passwd';
	    document.getElementById('form1').submit();
	}
	document.getElementById('$pswFOCUS').focus();
	//-->
	</script>
	</div>
	</div>
	</div>\n\n";
	exit;
	break;
}
?>
