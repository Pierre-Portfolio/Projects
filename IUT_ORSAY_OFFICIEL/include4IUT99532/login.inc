<?php
#######################################################################################
# File: login.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Login page
#######################################################################################
#
#############################
# PREPARE PRE-SELECTED PAGE
#############################
$LOGIN_LOGO = "$IMAGES/icones-humaines_2.png";
$LOGO_SIZE  = "width:84p;height:42px";
#
$BG_COLOR = "#0489B1";
$TEXT_COLOR = "darkblue";
#
$PAGE_2_DISP = "
  <div id=login_div style='position:absolute;top:50%;left:50%;width:314px;height:114px;background-color:$BG_COLOR;border:2px solid $TEXT_COLOR;
    padding:6px 12px 0px 12px; margin:-120px 0px 0px -172px;border-radius:10px;-moz-border-radius:10px;
    opacity: 0.8;_filter: alpha(opacity=80);'>
    <table border=0 cellspacing=1 cellpadding=2>
    <tr style='font-family:arial,Helvetica;font-size:18px;font-weight:bold;color:$TEXT_COLOR;white-space:nowrap;'>
    <td style='width:104px;text-align:center;'><img style='border:0px;margin:0px;$LOGO_SIZE;' src='$LOGIN_LOGO'></td>
    <td style='text-align:center;padding:0px 0px 8px 0px;'>Administrateur</td></tr>

    <tr style='font-family:arial,Helvetica;font-size:14px;font-weight:bold;color:#000099;white-space:nowrap;'>
    <td style='text-align:right;padding:2px 5px 2px 0px;'><SPAN id=login_name>Indentifiant</SPAN></td>
    <td><input type=text id=login class=loginField value=''
	OnKeyPress=\"dummy=checkChar('login',event);\"
	OnMouseOver='this.focus();'></td></tr>

    <tr style='font-family:arial,Helvetica;font-size:14px;font-weight:bold;color:#000099;white-space:nowrap;'>
    <td style='text-align:right;padding:2px 5px 2px 0px;'><SPAN id=login_psw>Mot de passe</SPAN></td>
    <td><input type=password id=psw1 class=loginField value=''
	OnKeyPress=\"dummy=checkChar('psw1',event);\"
	OnMouseOver=\"if (document.getElementById('login').value.length > 2) this.focus();\"></td></tr>
    </table>
  </div>

  <div id=razMsg style='position:absolute;top:-50%;left:50%;width:314px;height:88px;background-color:$color14;
    border:1px solid $color5;padding:6px 12px 0px 12px; margin:-114px 0px 0px -171px;'>
    <div class=whiteArial14B style='position:absolute;top:2px;left:2px;right:2px;bottom:2px;background-color:$color17;
	text-align:center;padding:8px 16px 0px 16px;'>Voulez-vous recevoir un message de r&eacute;cup&eacute;ration ?
	<div style='position:relative;margin:2px 20px 0px 0px;height:30px;'>
	    <div style='position:relative;float:right;margin:10px;padding:2px;border:1px solid white;background-color:$color17;'>
	      <div class=mbutton style='position:relative;padding:1px 20px 1px 20px;background-color:$color14;'
	      OnClick='hide_raz_message();'>non</div>
	    </div>
	    <div style='position:relative;float:right;margin:10px 40px 0px 0px;padding:2px;border:1px solid white;background-color:$color17;'>
	      <div class=mbutton style='position:relative;padding:1px 20px 1px 20px;background-color:$color14;'
	      OnClick='send_raz_message();'>oui</div>
	    </div>
	</div>
    </div>
  </div>

  <div id=wait style='position:absolute;top:-50%;left:50%;width:314px;height:46px;background-color:$color17;
    border:1px solid $color5;padding:6px 12px 0px 12px; margin:-88px 0px 0px -171px;'>
    <div class=whiteArial14B style='position:absolute;top:2px;left:2px;right:2px;bottom:2px;background-color:$color14;
	text-align:center;padding:8px 16px 0px 16px;font-size:24px;'>Veuillez patienter, s.v.p.
    </div>
  </div>";
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>
