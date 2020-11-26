<?php
###########################################################################################
# File : adm_menu.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Affichage du menu d'administration
# -----------------------------------------------------------------------------------------
#
# Couleurs
$mouseOut = $color3;
$mouseOver = $color9;
$mouseOut2 = "#D4DCDD";
$mouseOver2 = "#FFFFFF";
$RESET_PASSWORD = 0;
#
$page .= "
<table style='border-collapse:collapse;' width=140px cellpadding=0 cellspacing=0>\n";
#
for ($j=0;$j<$main;$j++) {
	$action0 = $actn["$j,0"];
	$menu_class = "bar_item4";
	#
	if (in_array($MAIN_MENU[$j], array("Logout","Quitter"))) {
		$MOUSEOUT = $MENUCOLOR = "#EE2020";
		$MOUSEOVER = "#992000";
	}
	else {
		$menu_class = "bar_item4";
		$MOUSEOUT = $MENUCOLOR = $mouseOut;
		$MOUSEOVER = $mouseOver;
	}
	#
	if ($action0 == "blank") {
		$HEIGHT = $actn["$j,1"];
		$page .= "<tr><td style='border:0px;height:$HEIGHT;'></td></tr>";
	}
	else {
		$page .= "<tr><td style='border: 1px solid $color4;'>
		<div id=mreq class=$menu_class style='background-image: url($IMAGES/menu_button.png);color:$MENUCOLOR;'
			onMouseOver=\"this.style.color='$MOUSEOVER';this.style.fontSize='14px';\"
			onMouseOut=\"this.style.color='$MOUSEOUT';this.style.fontSize='13px';\"
			OnClick=\"$action0\">$MAIN_MENU[$j]</td></tr>\n\n";
	}
}
#
$page .= "<tr><td></td></tr>
</table>\n";
#
# End of script
?>
