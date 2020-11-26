<?php
#######################################################################################
# File   : fetchMenuData.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# Récupère les paramètres du menu d'administration en fonction du LEVEL
#--------------------------------------------------------------------------------------
#
$activeDB = $TOOLADMIN;
$GLOBALS["SQL_SOURCE"] = "OSE:fetchMenuData";
$COMPARE = array("\\", 'é', 'è', 'ê', 'ë', 'à', 'â', 'ù', 'û', 'ô', 'Ã©', 'Ãš', 'ÃŽ', 'Ã«', 'Ãª', 'Ã');   
$REPLACE = array("", "&eacute;", "&egrave;", "&ecirc;", "&euml;", "&agrave;", "&acirc;", "&ugrave;", "&ucirc;", "&ocirc;", "&eacute;", "&egrave;", "&ocirc;", "&euml;", "&euml;", "&agrave;");
#
$QUERY = "SELECT name,action FROM orsay_menu WHERE level>=$LEVEL AND live='1' ORDER BY rank";
QUERY($QUERY);
$main = $MAX;
#
if ($main > 0) {
	for ($k=0;$k<$main;$k++) {
		#$MAIN_MENU[$k] = str_replace($COMPARE,$REPLACE,utf8_encode(RESULT($k,0)));
		$MAIN_MENU[$k] = RESULT($k,0);
		$ACTION = explode(";",str_replace(":",";",RESULT($k,1)));
		$actn["$k,0"] = "";
		$Z = count($ACTION);
		if ($Z > 0) {
			for ($z=0;$z<$Z;$z++) {
				switch($ACTION[$z]) {
				case 'showAdm':
					$actn["$k,0"] = "set_admin_menu(3);";
					break;

				case 'BLANK':
					$actn["$k,0"] = "blank";
					$z++;
					$actn["$k,1"] = $ACTION[$z];
					break;

				case 'OP':
					$z++;
					$op2 = "none";
					if ($z>=$Z) break;
					$rk = $ACTION[$z];
					break;

				case 'OP2':
					$z++;
					if ($z>=$Z) break;
					$op2 = $ACTION[$z];
					break;

				case 'showFrame1':
					$actn["$k,0"] .= "mode_FS1.value='$rk';";
					$actn["$k,0"] .= "mode_OP.value='$op2';";
					$actn["$k,0"] .= "FS1.submit();";
					break;

				case 'quit':
					$actn["$k,0"] = "document.getElementById('top').submit();return false;";
					break;

				case 'menuHide':
					$actn["$k,0"] = "hide_mngt_menu();return false;";
					break;

				case 'logout':
					$actn["$k,0"] = "set_admin_menu(9);return false;";
					break;
				}
			}
		}
	}
}
#
#### End of script ####
?>
