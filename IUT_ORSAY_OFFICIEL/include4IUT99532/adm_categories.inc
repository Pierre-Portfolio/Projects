<?php
###########################################################################################
# File   : search_category.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Gestion des catégories
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:search_category";
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
    #$name = addslashes(utf8_decode($fr_name));
    $name = addslashes($fr_name);
    $rank = trim($rank);
    $VALUES  = "$cid, $activeButton, '$name', $rank";
    $SQL1  = "INSERT INTO orsay_categories (cid, active, name,rank) VALUES ($VALUES)";
    #echo "<pre>$SQL1\n";print_r($_POST);exit;
    WRITE($SQL1);
    #
    if ($rank < $cid) {
	$QUERY = "SELECT cid FROM orsay_categories WHERE cid!=$cid ORDER BY rank";
	QUERY($QUERY);
	$n = 0;
	for ($j=0;$j<$MAX;$j++) {
	    if ($n == intval($rank)) $n++;
	    $idx_menu = RESULT($j,0);
	    $SQL2 = "UPDATE orsay_categories set rank=$n WHERE cid=$idx_menu";
	    WRITE($SQL2);
	    $n++;	    
	}
    }
    break;

case 'update':
    #$name = utf8_decode($fr_name);
    $name = $fr_name;
    $QUERY  = "SELECT name, rank FROM orsay_categories";
    $QUERY .= " WHERE cid=$cid";
    QUERY($QUERY);
    if ($MAX > 0) {
	$old_name = RESULT(0,0);
	$old_rank = RESULT(0,1);
    }
    $SQL1  = "UPDATE orsay_categories set active=$activeButton";
    if ($old_name != $name) {
	$name = addslashes($name);
	$SQL1 .= ", name='$name'";
    }
    #
    $rearrange = 0;
    if ($old_rank != $rank) {
	$SQL1 .= ", rank=$rank";
	$rearrange = 1;
    }
    $SQL1 .= " WHERE cid=$prev_cid";
    #echo "<pre>$SQL1\n";print_r($_POST);exit;
    WRITE($SQL1);
    #
    if ($rearrange == 1) {
	$QUERY = "SELECT cid FROM orsay_categories WHERE cid!=$cid ORDER BY rank";
	QUERY($QUERY);
	$n = 0;
	for ($j=0;$j<$MAX;$j++) {
	    if ($n == intval($rank)) $n++;
	    $idx_menu = RESULT($j,0);
	    $SQL2 = "UPDATE orsay_categories set rank=$n WHERE cid=$idx_menu";
	    WRITE($SQL2);
	    $n++;	    
	}
    }
}
#
switch ($OP) {
case 'create':
case 'update':
    $page = "$OP:search_categories";
    $traceRecord = "$cid-$name";
    break;
default:
    $page = "read:search_categories";
    $traceRecord = "";
}
#
$COMPARE = "à,é,è,ù,ä,ë,ï,ö,ü";
$SUBSTITUTE = "&agrave;,&eacute;,&egrave;,&ugrave;,&auml;,&euml;,&iuml;,&ouml;,&uuml;";
#
# DATA à afficher
#~~~~~~~~~~~~~~~~~~
$QUERY  = "SELECT cid,name,active,rank";
$QUERY .= " FROM orsay_categories ORDER BY rank";
QUERY($QUERY);
$main_max = $MAX;
$separator = $SHORT_TAGS = "";
$top_cid = 0;
$MODE_SELECT = 1000;
#
if ($main_max > 0) {
  for ($j=0;$j<$main_max;$j++) {
    $CID[$j] = RESULT($j,0);
    $NAMES[$j] = RESULT($j,1);
    $ACTIVE_INDEX[$j] = RESULT($j,2);
    $RANK[$j] = RESULT($j,3);
    $SHORT_TAGS .= $separator . $NAMES[$j];
    $separator = "!";
  }
  $top_cid = control("next","SELECT max(cid) FROM orsay_categories");
}
#
##############
# FULL FRAME
##############
echo "
<head>
<link rel=stylesheet type='text/css' href='css/white-scrollbar.css'>
<script src='js/perfect-scrollbar.js'></script>
</head>

<FORM TARGET=_self name=cat_menu id=cat_menu action='$SN' method=POST>
<input type=hidden name=innerREQ value=1>
<input type=hidden name=mode value=cat>
<input type=hidden name=OP id=mode_OP value=none>
<input type=hidden name=cid id=cid value=$top_cid>

<div class=div_adm>";
#
#############
# Page title
#############
echo "
  <div style='position:absolute;top:14px;left:50px;margin:0px;padding:1px;border:1px solid white;'>
    <div class=whiteArial14B style='position:relative;top:0px;left:0px;padding:4px 12px 4px 12px;text-align:center;
	background-color:$color14;font-size:16px;'>Gestion des cat&eacute;gories</div>
  </div>";
#
#######################################
# SLIDING FRAME for LEFT menu display
#######################################
echo "
  <div style='position:absolute;top:60px;left:-14px;margin:24px;width:280px;bottom:30px;border:1px solid white;
	margin-top:0px;padding:0px;' OnMouseOver=\"new PerfectScrollbar('#result_display');\">
    <div style='position:absolute;top:1px;left:1px;right:1px;bottom:1px;margin:0px;padding:0px 0px 0px 3px;
	border:0px solid $color1;background-color:$color14;'>
      <div id=result_display style='position:absolute;top:3px;left:0px;right:1px;bottom:3px;margin:0px;padding:0px;
	overflow:hidden;overflow-y:auto;'>
	<div style='position:relative;top:0px;left:0px;margin:-8px 12px 0px 0px;padding:0px 0px 6px 1px;'>";
#
#################
# BUTTONS FRAME
#################
for ($j=0;$j<$main_max;$j++) {
	$cid = $CID[$j];
	#$label = utf8_encode($NAMES[$j]);
	$label = $NAMES[$j];
	$active = $ACTIVE_INDEX[$j];
	$rk = $RANK[$j];
	#
	$num = sprintf("%02d", $rk);
	if ($rk == 0) {
	  echo "
	  <div style='position:relative;top:2px;left:0px;margin-top:8px;width:60px;padding:0px;height:18px;'>
	    <div class=whiteArial12B style='position:absolute;top:0px;left:2px;margin:0px;padding:3px 3px 3px 3px;
		background-color:$color17;white-space:nowrap;color:white;cursor:none;'>$num</div>

	    <div class=whiteArial12B style='position:absolute;top:0px;left:26px;margin:0px;padding:3px 7px 3px 7px;
		background-color:#BB0000;white-space:nowrap;color:white;cursor:none;'>$label</div>
	  </div>";
	}
	else {
	  echo "
	  <div style='position:relative;top:2px;left:0px;margin-top:8px;width:60px;padding:0px;height:18px;'>
	    <input id=idx$j type=hidden value=$cid>
	    <input id=idx_active$j type=hidden value=$active>
	    <input id=idx_rank$j type=hidden value=$rk>
	    <input id=text$j type=hidden value=\"$label\">

	    <div class='whiteArial12B mbutton' style='position:absolute;top:0px;left:2px;margin:0px;padding:3px 3px 3px 3px;
		background-color:$color17;white-space:nowrap;color:white;'
		OnClick='edit_menu($j);return false;'>$num</div>

	    <div class='whiteArial12B mbutton' style='position:absolute;top:0px;left:26px;margin:0px;padding:3px 7px 3px 7px;
		background-color:black;white-space:nowrap;color:#CCCCFF;'
		OnClick='edit_menu($j);return false;'>$label</div>
	  </div>";
	}
}
echo "
	</div>
      </div>
    </div>
  </div>";
#
#################
# EDITING FRAME
#################
echo "
  <div style='position:absolute;top:60px;left:300px;margin:0px;width:270px;height:94px;padding:0px;border:1px solid white;'>
    <div style='position:absolute;top:1px;left:1px;right:1px;bottom:1px;padding:8px;background-color:$color14;'>
    <table border=0 cellspacing=0 cellpadding=0 style='margin:0px;'>
    <tr class=whiteArial12B>
    <td style='text-align:right;width:50px;'>Rang:</td>
    <td><input type=hidden id=prev_cid name=prev_cid value=$top_cid>
    <INPUT id=rank name=rank class=dBlueArial12B type=text value='$top_cid'
      style='margin:0px 0px 0px 3px;padding:1px 5px 1px 5px;text-align:right;width:30px;
	background-color:$color5;border:1px solid $color17;'
	OnMouseOver=\"document.getElementById('rank_frame').style.top = '500px';\"></td>

    <td style='text-align:right;width:60px;'>Visible:</td>
    <input type=hidden id=button_view name=activeButton value=1>
    <td><INPUT id=button_on name=viewButton class=dBlueArial12B type=radio value=1 checked
	style='margin:0px 0px 0px 3px;padding:1px 5px 1px 5px;'
	OnClick=\"document.getElementById('button_view').value = 1;\"></td>
    <td style='padding:2px 0px 2px 3px;width:20px;'>oui</td>
    <td><INPUT id=button_off name=viewButton class=dBlueArial12B type=radio value=0
	style='margin:0px 0px 0px 3px;padding:1px 5px 1px 5px;'
	OnClick=\"document.getElementById('button_view').value = 0;\"></td>
    <td style='padding:2px 0px 2px 3px;width:30px;'>non</td></tr>

    <tr><td colspan=7 style='height:8px'></td></tr>

    <tr class=whiteArial12B><td style='text-align:right;width:50px;'>Label:</td>
    <td colspan=6>
      <INPUT id=fr_name name=fr_name class=dBlueArial12B type=text value=''
	style='margin:0px 0px 0px 3px;padding:1px 5px 1px 5px;width:180px;
	    background-color:$color5;border:1px solid $color17;'></td>
    </tr>

    <tr class=dBlueArial12B><td colspan=9 style='text-align:right;'>
    <div style='position:relative;top:0px;left:0px;height:20px;margin:0px;padding:8px;'>
      <div id=new_item class='mbutton dBlueArial12B' style='position:absolute;right:-6px;margin:0px 20px 0px 0px;
	  padding:1px 8px 1px 8px;text-align:center;border-radius:10px;-moz-border-radius:10px;
	  border:2px solid $color7;background-color:$color5;'
	  OnClick=\"submit_menubackground-color);\">créer une rubrique</div>

      <div id=erase_item class='mbutton dBlueArial12B' style='position:absolute;left:5px;margin:0px 20px 0px 0px;
	  padding:1px 8px 1px 8px;text-align:center;border-radius:10px;-moz-border-radius:10px;
	  border:2px solid $color7;background-color:$color5;display:none;'
	  OnClick='refresh_edit_menu();'>nouvelle rubrique</div>

      <div id=update_item class='mbutton dBlueArial12B' style='position:absolute;right:10px;margin:0px;
	  padding:1px 8px 1px 8px;text-align:center;border-radius:10px;-moz-border-radius:10px;
	  border:2px solid $color7;background-color:$color5;display:none;'
	  OnClick=\"submit_menu('update');\">mettre &agrave; jour</div>
    </div></td></tr>
    </table>
    </div>
  </div>";
#
#############
# RANK MENU
#############
echo "
  <div id=rank_frame style='position:absolute;top:0px;margin-top:-431px;left:362px;width:56px;
    height:126px;padding:0px;border:1px solid white;background-color:$color17;'
	OnMouseOver=\"this.style.top = '500px';\"
	OnMouseOut=\"this.style.top = '0px';\">
    <div style='position:absolute;top:1px;left:1px;right:1px;bottom:1px;padding:8px;background-color:$color14;'>
      <div id=rank_display style='position:absolute;top:3px;left:0px;right:1px;bottom:3px;margin:0px;padding:0px;
	overflow:hidden;overflow-y:auto;'>
	<div style='position:relative;top:0px;left:0px;margin:-8px 12px 0px 0px;padding:5px 0px 0px 1px;'>";
#
for ($j=1;$j<=$top_cid;$j++) {
    if ($j < $top_cid) $BG = $color5;
    else $BG = $color17;
    #
    echo "
	  <div id=rk$j class='mbutton dBlueArial12B' style='position:relative;top:0px;left:0px;margin:4px 3px 2px 2px;
	    padding:1px 8px 1px 8px;text-align:right;border-radius:10px;-moz-border-radius:10px;
	  border:2px solid $color7;background-color:$BG;'
	  OnClick=\"set_rank($j);\">$j</div>";
}
echo "
	</div>
      </div>
    </div>
  </div>";
#
#####################
# End of FULL FRAME
#####################
echo "
</div>
</FORM>

<script language=JavaScript>
function edit_menu(val) {
    document.getElementById('cid').value = document.getElementById('idx'+val).value;
    document.getElementById('prev_cid').value = document.getElementById('idx'+val).value;
    document.getElementById('fr_name').value = document.getElementById('text'+val).value;
    document.getElementById('new_item').style.display = 'none';
    document.getElementById('update_item').style.display = 'inline';
    document.getElementById('erase_item').style.display = 'inline';
    set_rank(document.getElementById('idx_rank'+val).value);

    var button_val = document.getElementById('idx_active'+val).value;
    document.getElementById('button_view').value = button_val;
    if (parseInt(button_val) == 1) document.getElementById('button_on').checked = 'true';
    else document.getElementById('button_off').checked = 'true';
}

function refresh_edit_menu() {
    document.getElementById('cid').value = $top_cid;
    document.getElementById('prev_cid').value = $top_cid;
    set_rank($top_cid);
    document.getElementById('button_view').value = 1;
    document.getElementById('button_on').checked = 'true';
    document.getElementById('fr_name').value = '';
    document.getElementById('new_item').style.display = 'inline';
    document.getElementById('update_item').style.display = 'none';
    document.getElementById('erase_item').style.display = 'none';
}

function set_rank(val) {
    document.getElementById('rank').value = val;
    for (j=1;j<=$top_cid;j++) {
	if (parseInt(j) == parseInt(val)) {
	    document.getElementById('rk'+j).style.backgroundColor = '$color17';
	}
	else {
	    document.getElementById('rk'+j).style.backgroundColor = '$color5';
	}
    }
    document.getElementById('rank_frame').style.top = '0px';
}

function submit_menu(val) {
    if (document.getElementById('fr_name').value.length < 3) {
	alert('Label vide');
	return false;
    }
    document.getElementById('mode_OP').value = val;
    document.getElementById('cat_menu').submit();
}

if ($LEVEL == 0) allow_right_mouse = 1;

new PerfectScrollbar('#rank_display');
</script>";
?>