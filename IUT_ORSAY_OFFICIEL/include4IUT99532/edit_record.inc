<?php
###########################################################################################
# File   : edit_record.inc(3)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function:
# ---------
# Editer un enregistrement
# -----------------------------------------------------------------------------------------
#
$GLOBALS["SQL_SOURCE"] = "OSE:edit_record";
#
##################
# PREPARE RESULT
###################
$QUERY = "SELECT r.active,r.titre,r.lien,r.clefs,r.cat,c.name FROM orsay_records r, orsay_categories c WHERE idx=$idx AND r.cat=c.cid";
QUERY($QUERY);
if ($MAX > 0) {
    $active = RESULT(0,0);
    #$title = utf8_encode(RESULT(0,1));
    $title = RESULT(0,1);
    $link = RESULT(0,2);
    $field1 = RESULT(0,3);
    $field2 = RESULT(0,4);
    $temp = RESULT(0,3);
    $lg = strlen($temp) - 2;
    $keys = substr($temp,1,$lg);
    $cat = RESULT(0,4);
    #$catName = utf8_encode(RESULT(0,5));
    $catName = RESULT(0,5);
    $response = "1|$idx|$active|$title|$cat|$catName|$keys|$link|0";
}
else $response = "0|$QUERY";
#
#~~~~~~~~~~~~~~~
# End of script
#~~~~~~~~~~~~~~~~
?>