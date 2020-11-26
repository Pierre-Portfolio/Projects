<?php
###########################################################################################
# File   : users_utility.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Editer un utilisateur
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:users_utility";
#
##################
# PREPARE RESULT
###################
switch ($format) {
case "edit":
    $QUERY = "SELECT login,level,fname,lname,email FROM orsay_login WHERE uid=$user_id";
    QUERY($QUERY);
    if ($MAX > 0) {
	$user_login = RESULT(0,0);
	$role = RESULT(0,1);
	#$fname = utf8_encode(RESULT(0,2));
	#$lname = utf8_encode(RESULT(0,3));
	#$email = utf8_encode(RESULT(0,4));
	$fname = RESULT(0,2);
	$lname = RESULT(0,3);
	$email = RESULT(0,4);
	$response = "1|$user_id|$user_login|$fname|$lname|$email|$role|0";
    }
    else $response = "0|$QUERY";
    break;

default:
    $words = explode(" ",$keywords);
    #
    $SQL0 = "SELECT uid,login,level,fname,lname,email,laccess FROM orsay_login ";
    $SQL9 = " ORDER BY lname,fname";
    #
    $main_count = $count = count($words);
    switch ($count) {
    case 1:
	$QUERY = $SQL0 . "WHERE fname LIKE '${keywords}%' OR lname LIKE '${keywords}%'" . $SQL9;
	break;

    default:
	$word0 = $words[0];
	$word1 = $words[1];
	$QUERY = $SQL0 . "WHERE (fname = '$word0' AND lname LIKE '${word1}%')";
	$QUERY .= " OR (lname = '$word0' AND fname LIKE '${word1}%')" . $SQL9;
    }
    #
    #########################################
    # Juste renvoyer la $QUERY à "user.inc"
    #########################################
    if ($format == "list") break;
    #
    ##############################################
    # Construire le tableau pour la requête AJAX
    ##############################################
    $role_codes = array(0,1,2,3,9);
    $role_names = array("webmaster","design","admin","clerk","normal");
    $role_max = count($role_codes);
    #
    for ($j=0;$j<$role_max;$j++) {
	$code = $role_codes[$j];
	$roleNames[$code] = $role_names[$j];
    }
    $width_login = 70;
    $width_first = 150;
    $width_last = 150;
    $width_laccess = 118;
    $width_button = 66;
    $BG1 = "steelblue";
    $BG1 = $color7;
    $BG2 = $color5;
    #
    QUERY($QUERY);
    $result_max = $MAX;
    if ($MAX > 0) {
	$response = "1|
	<table border=0 cellspacing=2 cellpadding=0 style='margin:0px;width:100%;'>";
	for ($j=0;$j<$result_max;$j++) {
	    $sel_uid = RESULT($j,0);
	    $sel_login = RESULT($j,1);
	    $role = RESULT($j,2);
	    #$fname = utf8_encode(RESULT($j,3));
	    #$lname = utf8_encode(RESULT($j,4));
	    $fname = RESULT($j,3);
	    $lname = RESULT($j,4);
	    $email = RESULT($j,5);
	    $laccess = RESULT($j,6);
	    #
	    $response .= "
	    <tr class=dBlueArial12B><td style='width:${width_login}px;padding:2px;text-align:center;
	      background-color:$BG1;'>$sel_login</td>
	    <td style='vertical-align:top;width:${width_first}px;padding:2px 0px 2px 6px;white-space:nowrap;
	      background-color:$BG1;'>$fname</td>
	    <td style='vertical-align:top;width:${width_last}px;padding:2px 0px 2px 6px;white-space:nowrap;
	      background-color:$BG1;'>$lname</td>
	    <td style='vertical-align:top;width:${width_laccess}px;padding:2px 0px 2px 6px;white-space:nowrap;
	      background-color:$BG1;'>$laccess</td>
	    <td rowspan=2>";
	    #
	    if ($uid != $sel_uid && $LEVEL <= $role) {
		$response .= "
		<div class='whiteArial12B mbutton'
		style='position:relative;top:0px;left:0px;margin:2px;padding:1px 8px 1px 8px;background-color:$color5;text-align:center;
		border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
		OnClick=\"edit_user($sel_uid);\">&eacute;diter</div>";
	    }
	    #
	    $response .= "</td></tr>

	    <tr class=dBlueArial12B><td style='width:${width_login}px;padding:2px;text-align:center;
	      background-color:$BG2;'>$roleNames[$role]</td>
	    <td colspan=3 style='vertical-align:top;width:${width_first}px;padding:2px 0px 2px 6px;white-space:nowrap;
	      background-color:$BG2;'>$email</td></tr>";
	}
	$response .= "</table>|0";
    }
    else $response = "0|<table border=0 cellspacing=2 cellpadding=0 style='margin:2px;width:516px;background:$color7;'>
	<tr class=dBlueArial12B><td style='text-align:center;padding:4px;'>V&eacute;rifiez la syntaxe de votre recherche</td></tr>
	</table>|0";
}
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>