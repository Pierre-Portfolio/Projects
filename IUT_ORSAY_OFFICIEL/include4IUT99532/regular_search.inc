<?php
###########################################################################################
# File   : regular_search.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Gestion de la base de données
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:regular_search";
$QWANT1 = "https://www.qwant.com/?q=";
$QWANT2 = "&t=web";
$ECOSIA = "https://www.ecosia.org/search?q=";
$GOOGLE = "https://www.google.fr/search?q=";
$DDG1 = "https://duckduckgo.com/?q=";
$DDG2 = "&t=hh&ia=web";
#
$DEBUG = 0;
switch ($DEBUG) {
case 1:
    echo "<pre>";
    print_r($_POST);
    exit;
}
#
$response = "";
if (!isset($_POST["ajax"])) {
    $keywords = clean_str(Secure($_POST["keywords"]));
}
else {
    #$keywords = utf8_decode(clean_str(Secure(urldecode($_POST["keywords"]))));
    $keywords = clean_str(Secure(urldecode($_POST["keywords"])));
    $response = "$keywords|";
}
#
$lg = strlen($keywords);
$rank = 0;
$ignore = "0"; # pour les recherches multiples
#
if (intval($category) == 0) $CATEGORY = "";
else $CATEGORY = " AND cat=$category";
$SQL0 = "SELECT idx,titre,lien FROM orsay_records WHERE active=1$CATEGORY AND (";
$SQL9 = ") ORDER BY titre LIMIT 60";

$words = explode(" ",$keywords);
$main_count = $count = count($words);
switch ($count) {
case 1:
	$QUERY = $SQL0 . "clefs LIKE '%,${keywords}%,%'" . $SQL9;
	QUERY($QUERY);
	if ($MAX > 0) {
	    for ($j=0;$j<$MAX;$j++) {
		$IDX[$rank] = $idx = RESULT($j,0);
		#$LABEL[$rank] = utf8_encode(RESULT($j,1));
		$LABEL[$rank] = RESULT($j,1);
		$LINK[$rank] = RESULT($j,2);
		$ignore .= "," . $idx;
		$rank++;
	    }
	}
	break;

default:
	#######################
	# Champs prioritaires
	#######################
	$count--;
	$word0 = $words[$count];
	$QUERY = $SQL0 . "clefs LIKE '%,${word0}%,%'";
	for ($j=0;$j<$count;$j++) {
	      $word0 = $words[$j];
	      $QUERY .= " AND clefs LIKE '%,${word0},%'";
	}
	$QUERY .= $SQL9;
	QUERY($QUERY);
	if ($MAX > 0) {
	    for ($j=0;$j<$MAX;$j++) {
		$IDX[$rank] = $idx = RESULT($j,0);
		#$LABEL[$rank] = utf8_encode(RESULT($j,1));
		$LABEL[$rank] = RESULT($j,1);
		$LINK[$rank] = RESULT($j,2);
		$ignore .= "," . $idx;
		$rank++;
	    }
	}
	break;
}
#
$CONTENT = "";
#
if ($rank > 0) {
    $tag = "Cliquer sur une ligne de r&eacute;sultat pour ouvrir la page associ&eacute;e";
    $VERTICAL = "bottom:20px";
    #
    for ($j=0;$j<$rank;$j++) {
	$ridx = $IDX[$j];
	$link = $LINK[$j];
	$CONTENT .= "
	<tr class=dBlueArial12B>";
	if ($LEVEL < 4) {
	    $CONTENT .= "<td style='padding:2px;width:50px;'>
	    <div class=mbutton style='position:relative;top:0px;left:0px;margin:0px;padding:2px;
	    background-color:$color7;text-align:center;' OnClick='admin_edit($ridx);'>Editer</div></td>
	    <td style='padding:2px 6px 2px 0px;'>";
	    
	}
	else $CONTENT .= "<td style='padding:2px 6px 2px 6px;'>";
	$CONTENT .= "
	<div class=mbutton style='position:relative;top:0px;left:0px;margin:0px;padding:2px 2px 2px 6px;
	    background-color:$color6;' OnClick=\"file_link('$link')\">$LABEL[$j]</div></td></tr>";
    }
}
else {
    #$tag = "Votre recherche est vide<br><SPAN style='color:black;'>$QUERY</SPAN>";
    $tag = "Votre recherche est vide";
    $VERTICAL = "height:160px";
}
#$tag = "($category) ".$QUERY;
#
###########################
# Affichage des resultats
###########################
$qwant = $QWANT1 . urlencode($keywords) . $QWANT2;
$ecosia = $ECOSIA . urlencode($keywords);
$google = $GOOGLE . urlencode($keywords);
$ddg = $DDG1 . urlencode($keywords) . $DDG2;
#
$response .= "
<div style='position:absolute;top:20px;left:50%;width:900px;margin-left:-450px;$VERTICAL;border:0px solid red;
  opacity: 0.84;_filter: alpha(opacity=84);'
  OnMouseOver=\"new PerfectScrollbar('#result_display');\">
  <div style='position:absolute;top:4px;left:16px;right:16px;bottom:4px;
    font-family:arial,Helvetica;font-size:12px;color:#606060;margin:0px;
    box-shadow:0px 0px 10px yellow;background-color:ivory;border-radius:16px;-moz-border-radius:16px;'>
    <div id=result_display style='position:absolute;top:60px;left:1px;right:1px;bottom:86px;margin:0px;border:0px;
	overflow:hidden;overflow-y:auto;border:0px solid blue;'>
      <div style='position:relative;top:0px;left:0px;margin:0px 10px 0px 0px;padding:0px;'>
	<table border=0 cellspacing=2 cellpadding=0 style='margin:0px;width:100%;'>$CONTENT</table>
      </div>
    </div>

    <div class=dBlueArial12B style='position:absolute;top:100%;left:12px;right:12px;height:52px;margin:0px;border:0px;
	margin-top:-80px;padding:10px 0px 0px 12px;background-color:$color7;border-radius:14px;-moz-border-radius:14px;'>
	Si vous n'&ecirc;tes pas satisfait par ce r&eacute;sultat, vous pouvez:\n";

if ($main_count > 1) {
    $response .= "
	<div class='whiteArial12B mbutton'
	  style='position:absolute;top:5px;left:357px;margin:0px;padding:2px 10px 2px 12px;background-color:$color5;
	  border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick='set_admin_menu(4);'>sugg&eacute;rer un nouvel index</div>\n";
}

$response .= "
	<div class='whiteArial12B mbutton'
	  style='position:absolute;top:5px;left:561px;margin:0px;padding:2px 10px 2px 12px;background-color:$color5;
	  border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick=\"file_link('$qwant')\">lancer cette recherche sur Qwant</div>

	<div class='whiteArial12B mbutton'
	  style='position:absolute;top:35px;left:20px;margin:0px;padding:2px 10px 2px 12px;background-color:$color5;
	  border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick=\"file_link('$ddg')\">lancer cette recherche sur DuckDuckGo</div>

	<div class='whiteArial12B mbutton'
	  style='position:absolute;top:35px;left:307px;margin:0px;padding:2px 10px 2px 12px;background-color:$color5;
	  border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick=\"file_link('$google')\">lancer cette recherche sur Google</div>

	<div class='whiteArial12B mbutton'
	  style='position:absolute;top:35px;left:560px;margin:0px;padding:2px 10px 2px 12px;background-color:$color5;
	  border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick=\"file_link('$ecosia')\">lancer cette recherche sur Ecosia</div>
    </div>
  </div>

  <div class=rbanner_left style='border-color:transparent $color17 transparent transparent;'></div>
  <div class=rbanner_right style='border-color:transparent transparent transparent $color17;'></div>
  <div class=rbanner_text style='background-color:$color14;color:$color6;'>$tag</div>
</div>";
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>