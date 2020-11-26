<?php
###########################################################################################
# File   : make_search.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Contributions à la base de données
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:make_search";
$key_comp = array(',,',"'",'"');
$key_replace = array(',','','');
#
$DEBUG = 0;
switch ($DEBUG) {
case 1:
    echo "<pre>";
    print_r($_POST);
    exit;
}
#
switch ($OP) {
case 'create':
    #$nwLABEL = str_replace("'","\'",utf8_decode(Secure3($LABEL)));
    $nwLABEL = str_replace("'","\'",Secure3($LABEL));
    $newKEYS = ",".stripAccents(Secure(str_replace($key_comp,$key_replace,$KEYS))).",";
    #$newLINK = utf8_decode($LINK);
    $newLINK = Secure($LINK);
    $active = 0;
    $VALUES = "$active,'$newCAT','$nwLABEL','$newKEYS','$newLINK'";
    $SQL1 = "INSERT INTO orsay_records (active,cat,titre,clefs,lien) VALUES ($VALUES)";
    if ($DEBUG > 0) {
	echo "<pre>\n$SQL1\n";print_r($_POST);exit;
    }
    WRITE($SQL1);
    $_POST["idx"] = control("val","SELECT idx FROM orsay_records WHERE idx=LAST_INSERT_ID()");
    break;

case 'update':
    #$nwLABEL = utf8_decode(Secure3($LABEL));
    $rawLABEL = Secure3($LABEL);
    $newKEYS = ",".stripAccents(Secure(str_replace($key_comp,$key_replace,$KEYS))).",";
    $newLINK = Secure($LINK);
    $SQL1 = "UPDATE orsay_records set cat=$newCAT";
    $QUERY = "SELECT titre,lien,cat,clefs FROM orsay_records WHERE idx=$idx";
    QUERY($QUERY);
    if ($MAX > 0) {
	$old_title = RESULT(0,0);
	$old_link = RESULT(0,1);
	$old_cat = RESULT(0,2);
	$old_keys = RESULT(0,3);
	if ($old_title != $rawLABEL) {
	    $nwLABEL = str_replace("'","\'",$rawLABEL);
	    $SQL1 .= ",titre='$nwLABEL'";
	}
	if ($old_link != $newLINK) {
	    $SQL1 .= ",lien='$newLINK'";
	}
	if ($old_keys != $newKEYS) {
	    $SQL1 .= ",clefs='$newKEYS'";
	}
	$SQL1 .= " WHERE idx=$idx";
	if ($DEBUG == 0) WRITE($SQL1);
    }
    if ($DEBUG > 0) {
	echo "<pre>DEBUG=$DEBUG\nmax=$MAX\n$QUERY\n$SQL1\n";print_r($_POST);exit;
    }
    break;
}
#
####################
# QUERY categories
####################
$QUERY = "SELECT cid,name FROM orsay_categories ORDER BY rank";
QUERY($QUERY);
$cat_max = $MAX;
if ($cat_max > 0) {
  for ($j=0;$j<$cat_max;$j++) {
    $CID[$j] = $cid = RESULT($j,0);
    #$CAT_NAME[$cid] = $CAT_TTL[$j] = utf8_encode(RESULT($j,1));
    $CAT_NAME[$cid] = $CAT_TTL[$j] = RESULT($j,1);
  }
}
#
#########################
# PREPARE RESULTS TABLE
#########################
$result_max = $idx_ref = $active = 0;
#
if (isset($_POST["idx"])) {
    $idx_ref = $_POST["idx"];
    $QUERY = "SELECT r.idx,r.titre,r.lien,c.name FROM orsay_records r, orsay_categories c WHERE r.cat=c.cid AND r.idx=$idx_ref";
    QUERY($QUERY);
    $result_max = $MAX;
}
#
if (!isset($_POST["new_record"])) $new_record = 0;
#
switch ($new_record) {
case 1:
    $newCAT0 = $_POST["search_cat0"];
    $newCAT1 = $CAT_NAME[$newCAT0];
    $newKEYS = stripAccents(rtrim($_POST["search_input0"]));
    break;

default:
    $newCAT0 = 0;
    $newCAT1 = $CAT_NAME[0];
    $newKEYS = "";
}
#
#################
# FRAME CONTENT
#################
echo "
<form id=admSearch TARGET=_self action='$SN' method=POST enctype='multipart/form-data'>
<input type=hidden name=innerREQ value=1>
<input type=hidden name=mode value='makeSearch'>
<input type=hidden name=OP id=OP value='create'>
<input type=hidden name=MENU id=MENU value='make_search'>
<input type=hidden name=idx id=idx_ref value=0>
<input type=hidden name=active id=set_active value=0>
<input type=hidden name=newCAT id=CAT0 value=$newCAT0>";
#
#############
# Page title
#############
echo "
  <div style='position:absolute;top:14px;left:100px;margin:0px;padding:1px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:4px 12px 4px 12px;text-align:center;
	background-color:$color14;font-size:16px;'>Sugg&eacute;rer un nouvel index de recherche</div>
  </div>";
#
################
# Champ ERREUR
################
$TOP = 51;
$TOP_ERR = 2 + $TOP;
$DELTA = 36;
$TOP0 = $DELTA + 1 + $TOP;
$TOP1 = $DELTA + $TOP0;
$TOP2 = $DELTA + $TOP1;
$TOP3 = $DELTA + $TOP2;
$TOP4 = $DELTA + $TOP3;
echo "
  <div id=errorFrame style='position:absolute;top:${TOP_ERR}px;left:98px;margin:0px;padding:2px;border:1px solid $color17;
    background-color:$color14;display:none;'>
    <div id=recordError class=blackArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color8;margin:0px;color:$color14;'></div>
  </div>";
#
############
# Category
############
echo "
  <div style='position:absolute;top:${TOP0}px;left:87px;margin:0px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white-space:nowrap;'>Cat&eacute;gorie</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=CAT1 id=CAT1 class=dBlueArial12B readonly value=\"$newCAT1\"
	    style='width:160px;padding:1px 3px 1px 3px;border:0px;'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"
	OnMouseOver=\"document.getElementById('cat_menu').style.top='300px';\"
	OnMouseOut=\"document.getElementById('cat_menu').style.top='0px';\"></div>
  </div>";
#
###############
# Champ LABEL
###############
echo "
  <div style='position:absolute;top:${TOP1}px;left:28px;margin:0px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white-space:nowrap;'>R&eacute;sultat &agrave; afficher</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=LABEL id=LABEL class=dBlueArial12B value=''
	    style='width:821px;padding:1px 3px 1px 3px;border:0px;' autocomplete='off'
	    OnMouseOver='this.focus();'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"
	    OnKeyPress=\"return down_syntax('LABEL','lock',event);\"
	    OnKeyUp=\"return up_syntax('LABEL','lock',event);\"></div>
  </div>";
#
##############
# Mots-clefs
##############
echo "
  <div style='position:absolute;top:${TOP2}px;left:16px;margin:0px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white-space:nowrap;'>Mots-clefs associ&eacute;s</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=KEYS id=KEYS class=dBlueArial12B value=\"$newKEYS\"
	    style='width:821px;padding:1px 3px 1px 3px;border:0px;' autocomplete='off'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"
	    OnKeyPress=\"return down_syntax('KEYS','lock',event);\"
	    OnKeyUp=\"return up_syntax('KEYS','lock',event);\"></div>
  </div>";
#
##############
# Champ LIEN
##############
echo "
  <div id=link_input style='position:absolute;top:${TOP3}px;left:36px;padding:2px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 8px 2px 8px;float:left;
	background-color:$color14;margin:0px;white_space:nowrap;'>Lien vers la page</div>

    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:2px 4px 2px 0px;float:left;
	background-color:$color14;margin:0px;'>
	<input type=text name=LINK id=LINK class=dBlueArial12B value=''
	    style='width:821px;padding:1px 3px 1px 3px;border:0px;' autocomplete='off'
	    OnFocus=\"document.getElementById('errorFrame').style.display = 'none';\"></div>
  </div>";
#
########################
# CREATE/UPDATE button
########################
echo "
  <div style='position:absolute;top:${TOP4}px;left:40px;width:601px;height:24px;margin:0px;padding:0px;text-align:right;'>
    <div id=manageRecord class='whiteArial12B mbutton'
      style='position:absolute;top:0px;left:391px;margin:0px;padding:4px 10px 4px 12px;background-color:$color5;
      border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;'
      OnClick='manage_event();'>soumettre un nouvel index</div>";
#
################
# Nouvel index
################
echo "
    <div id=clearData class='whiteArial12B mbutton'
      style='position:absolute;top:0px;left:155px;margin:0px;padding:4px 10px 4px 12px;background-color:$color5;
      border:2px solid $color14;color:$color14;border-radius:10px;-moz-border-radius:10px;white-space:nowrap;display:none;'
      OnClick='clear_data();'>nouvel index</div>
  </div>
</form>\n";
#
###########################
# Affichage des resultats
###########################
if ($result_max > 0) {
  $sel_idx = RESULT(0,0);
  #$label = utf8_encode(RESULT(0,1));
  $label = RESULT(0,1);
  $link = RESULT(0,2);
  #$cat = utf8_encode(RESULT(0,3));
  $cat = RESULT(0,3);
  echo "
  <div style='position:absolute;top:274px;left:20px;width:998px;height:110px;border:0px solid red;'>
    <div style='position:absolute;top:4px;left:16px;right:16px;bottom:4px;
      font-family:arial,Helvetica;font-size:12px;color:#606060;margin:0px;
      box-shadow:0px 0px 10px yellow;background-color:ivory;border-radius:16px;-moz-border-radius:16px;'>
      <div id=result_display style='position:absolute;top:60px;left:1px;right:1px;bottom:20px;margin:0px;border:0px;
	overflow:hidden'>
	<div style='position:relative;top:0px;left:0px;margin:0px;padding:0px;'>
	  <table border=0 cellspacing=2 cellpadding=0 style='margin:0px;width:100%;'>
	  <tr class=dBlueArial12B><td style='vertical-align:top;width:50px;'>
	    <div class=mbutton style='position:relative;top:0px;left:0px;margin:0px;padding:3px 0px 3px 0px;text-align:center;
	      background-color:$color6;' OnClick='edit_record($sel_idx);'>Editer</div></td>

	  <td style='width:140px;background-color:$color7;padding:2px 6px 2px 6px;text-align:center;'>$cat</td>
	  <td style='background-color:$color6;padding:2px 6px 2px 6px;'>
	  <div class=mbutton style='position:relative;top:0px;left:0px;margin:0px;padding:1px 2px 1px 6px;
	    background-color:$color6;' OnClick=\"file_link('$link')\">$label</div></td></tr>
	  </table>
	</div>
      </div>
    </div>

    <div class=rbanner_left style='border-color:transparent $color17 transparent transparent;'></div>
    <div class=rbanner_right style='border-color:transparent transparent transparent $color17;'></div>
    <div class=rbanner_text style='background-color:$color14;color:$color6;'>V&eacute;rifier le lien
    avant de quitter et &eacute;diter pour corriger si n&eacute;cessaire</div>
  </div>";
}
#
##################
# Menu Catégorie
##################
echo "
<div id=cat_menu style='position:absolute;top:0px;left:173px;margin-top:-210px;width:162px;height:129px;
  background-color:$color17;border:1px solid white;'
  OnMouseOver=\"this.style.top='300px'\" OnMouseOut=\"this.style.top='0px'\">
  <div style='position:absolute;top:1px;left:1px;right:1px;bottom:1px;background-color:white;'>
    <div class=whiteArial12B style='position:relative;margin:0px;padding:3px 2px 4px 2px;text-align:center;background-color:$color14;'>
    Modifier la cat&eacute;gorie</div>

    <div id=cat_scroll style='position:absolute;top:24px;left:2px;right:0px;bottom:3px;overflow:hidden;overflow-x:auto;'>
      <div style='position:absolute;top:0px;left:0px;right:13px;bottom:0px;margin:0px;padding:0px;'>";
#
for ($j=1;$j<$cat_max;$j++) {
  $cid = $CID[$j];
  $cat_label = addslashes($CAT_NAME[$cid]);
  echo "
    <div class='mbutton dBlueArial12B' style='position:relative;top:0px;margin:2px 0px 2px 0px;padding:2px 2px 2px 6px;
    background-color:$color6;' OnClick=\"choose_category($cid,'$cat_label');\">$CAT_NAME[$cid]</div>";
}
echo "
      </div>
    </div>
  </div>
</div>";
##############
# JavaScript
##############
echo "
<script language=JavaScript>
var cat_name0 = \"$CAT_NAME[0]\";
top.search_ref.value = '';
top.document.getElementById('new_record').value=0;

////////////////////
// CATEGORY CHANGE
////////////////////
function choose_category(cid,val) {
    document.getElementById('CAT0').value = cid;
    document.getElementById('CAT1').value = val;
    document.getElementById('cat_menu').style.top = '0px';
}
</script>";
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>