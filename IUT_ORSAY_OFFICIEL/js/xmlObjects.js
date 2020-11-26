//////////////////////
//###########################################################################################
//# File : xmlObjects.js(3)
//# ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//# Function:
//# ---------
//# Managing Javascript data for AJAX requests and other JavaScript utilities
//# -----------------------------------------------------------------------------------------
//#
/////////////////////////////////////////
// Protection against Right Mouse click
/////////////////////////////////////////
var allow_right_mouse = 0;
document.oncontextmenu=function() {
	if (allow_right_mouse == 1) return true;

	var protect = 'Utiliser le bouton droit de la souris est interdit\n\n';
	protect += '              Faites Control-v pour coller'
	alert(protect);
	return false;
}

var n = new Date();

//////////////////////
// XML -> JS -> HTML
//////////////////////
function getXMLHTTP() {
	var xhr=null;
	if (window.XMLHttpRequest) // Firefox et autres
		xhr = new XMLHttpRequest();
	else if(window.ActiveXObject) { // Internet Explorer
		try {
			xhr = new ActiveXObject("Msxml2.XMLHTTP");
		}
		catch (e) {
			try {
				xhr = new ActiveXObject("Microsoft.XMLHTTP");
			}
			catch (e1) {
				xhr = null;
			}
		}
	}
	else { // XMLHttpRequest non supporté par le navigateur
		alert("Your navigator does not work with XMLHTTPRequest...");
	}
	return xhr;
}

//////////////////////////////////////////////////
// On bloque le retour chariot, quoiqu'il arrive
//////////////////////////////////////////////////
function auto_search0(e) {
	var keyCode = ('which' in e) ? e.which : e.keyCode;
	switch (e.keyCode) {
	case 13:
		//alert ('Entry code: ' + keyCode);
		e.returnValue = false;
		return false;
	}
}

//////////////////////////////////////////////////////
// On analyse chaque caractère du nom commençant par
//////////////////////////////////////////////////////
var remember_format;
function auto_search(ACTION,format,e) {
	remember_format = format;

	switch (format) {
	case 'search':
	    var keyCode = ('which' in e) ? e.which : e.keyCode;
	    switch (keyCode) {
	    case 13:
		//alert ('Entry code: ' + keyCode);
		if (document.all) {
		    // IE
		    e.returnValue = false;
		}
		else if (document.getElementById) {
		    // NS7
		    e.stopPropagation();
		}
	    }
	}

	switch (format) {
	case 'search':
	case 'restart':
	    hide_mngt_menu();

	    // bloquer un espace en première position
	    if (searchElement.value == ' ') searchElement.value = '';

	    // si champ vide, aucune analyse
	    if (searchElement.value.length == 0) {
		search_results.innerHTML = '';
		return false;
	    }
	    break;

	case 'user':
	    // bloquer un espace en première position
	    if (document.getElementById('search_user1').value == ' ') document.getElementById('search_user1').value = '';
	}

	// on envoie le texte pour comparaison
	var params='action='+ACTION;
	params+='&format='+format;
	params+='&ajax=1';

	switch (format) {
	case 'search':
	case 'restart':
	    params+='&keywords='+encodeURIComponent(searchElement.value);
	    params+='&category='+searchCategory.value;
	    break;

	case 'user':
	    params+='&keywords='+encodeURIComponent(document.getElementById('search_user1').value);
	}
	n++;
	params+='&n='+n;

	var xhr_object = getXMLHTTP();
	xhr_object.open('POST',ajax, true);
	xhr_object.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
	xhr_object.send(params);

	// wait for the answer
	xhr_object.onreadystatechange = function() {
		if(xhr_object.readyState == 4 && xhr_object.status == 200) {
			var field = xhr_object.responseText.split('|');
			switch (format) {
			case 'search':
			case 'restart':
			    search_ref.value = searchElement.value;
			    search_results.innerHTML = field[1];
			    new PerfectScrollbar('#result_display');
			    break;

			case 'user':
			    document.getElementById('user_results').innerHTML = field[1];
			    new PerfectScrollbar('#users_display');
			    break;
			}
		}
	}
}

////////////////////////////////////////
// Admin EDIT of an auto-search result
////////////////////////////////////////
function admin_edit(val) {
	if (parseInt(level) > 3) return;

	document.getElementById('idx_edit').value = val;
	set_admin_menu(5);
}

//////////////////
// Login Control
//////////////////
function checkChar(field,e) {
	if (document.layers) {
		// NS4
		var keyCode = e.which;
		// alert ('Entry code: ' + keyCode);
		switch (keyCode) {
		case 13:
			// for textarea (not necessary for input)
			return false;
		}
		return true;
	}
	else if (document.all) {
		// IE5
		var keyCode = e.keyCode;
		// alert ('Entry code: ' + keyCode + ' field: ' + field);
		switch (e.keyCode) {
		case 13:
			e.returnValue = false;
			if (field == 'login') {
				document.getElementById('psw1').focus();
			}
			if (field == 'psw1') {
				submit_login();
			}
			return false;
		}
	}
	else if (document.getElementById) {
		// NS7
		var keyCode = document.getElementById ? e.keyCode : 0;
		// alert ('Entry code: ' + keyCode);

		switch (keyCode) {
		case 13:
			e.stopPropagation();
			if (field == 'login') {
				document.getElementById('psw1').focus();
			}
			if (field == 'psw1') {
				submit_login();
			}
		}
	}
}

////////////////
// Login Check
////////////////
var login,level = 9;
function submit_login() {
	var params='action=ADM_LOGIN';
	login = document.getElementById('login').value;
	params+='&LOGIN='+login;
	params+='&psw='+document.getElementById('psw1').value;
	n++;
	params+='&n='+n;

	var xhr_object = getXMLHTTP();
	xhr_object.open('POST',ajax, true);
	xhr_object.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
	xhr_object.send(params);

	// wait for the answer
	xhr_object.onreadystatechange = function() {
	    if(xhr_object.readyState == 4) {
		var field = xhr_object.responseText.split('|');
		switch (parseInt(field[0])) {
		case 1:
		    mode_login = 0;
		    level = field[3];
		    set_admin_menu(field[1]);
		    break;

		default:
		    switch (parseInt(field[1])) {
		    case 1:
			document.getElementById('login').value = '';
			document.getElementById('psw1').value = '';
			document.getElementById('psw1').focus();
			break;

		    default:
			document.getElementById('login').value = '';
			document.getElementById('psw1').value = '';
			document.getElementById('login').focus();
		    }
		    //alert('submit_login: menu KO');
		}
	    }
	}
	return false;
}

///////////////////
// Show Mngt Menu
///////////////////
function show_mngt_menu() {
	if (parseInt(force_new2day) == 1) set_admin_menu(1);
	else document.getElementById('mngt_frame').style.left = '100%';
	return false;
}

///////////////////
// Hide Mngt Menu
///////////////////
function hide_mngt_menu() {
	document.getElementById('mngt_frame').style.left = '0px';
	return false;
}

////////////////////
// Load Admin Menu
////////////////////
var remember_flag = 0;
function set_admin_menu(flag) {
	document.getElementById('form_FS0').submit();
	var params='action=MENU_SETUP';
	params+='&FLAG='+flag;
	params+='&LOGIN='+login;
	params+='&LEVEL='+level;
	n++;
	params+='&n='+n;

	var xhr_object = getXMLHTTP();
	xhr_object.open('POST',ajax, true);
	xhr_object.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
	xhr_object.send(params);

	// wait for the answer
	xhr_object.onreadystatechange = function() {
	    if(xhr_object.readyState == 4) {
		var field = xhr_object.responseText.split('|');
		switch (parseInt(field[0])) {
		case 1:
		    switch (parseInt(field[1])) {
		    case 0:
			document.getElementById('main_container').innerHTML = '';
			document.getElementById('mngt_frame').style.left = '100%';
			document.getElementById('swap_menu').style.top = '21px';

		    case 2:
		    case 3:
			document.getElementById('td_menu').innerHTML = field[2];
			break;

		    // Force password change when password = new2day
		    case 1:
			document.getElementById('mngt_frame').style.left = '100%';
			document.getElementById('swap_menu').style.top = '21px';
			document.getElementById('main_container').innerHTML = '';
			document.getElementById('mode_FS1').value='Passwd';
			document.getElementById('mode_OP').value='new2day';
			document.getElementById('form_FS1').submit();
			break;

		    // Special EDIT modes from result list
		    case 4:
			document.getElementById('new_record').value=1;
		    case 5:
			document.getElementById('td_menu').innerHTML = field[2];
			document.getElementById('mngt_frame').style.left = '100%';
			document.getElementById('mode_FS1').value='makeSearch';
			document.getElementById('mode_OP').value='makeSearch';
			document.getElementById('form_FS1').submit();
			break;

		    case 9:
			//////////////////
			// Disconnection
			//////////////////
			login_mode = 0;
			level = 8;
			document.getElementById('img_login').style.display='none';
			hide_mngt_menu();
			document.getElementById('swap_menu').style.top = '-100px';
			document.getElementById('td_menu').innerHTML = '';
		    }
		    //alert('Menu loaded via case: '+field[1]);
		    break;

		default:
		    alert('set_admin_menu: menu KO');
		}
	    }
	}
	return false;
}

////////////////
// Export link
////////////////
function file_link(file_name) {
    window.open(file_name, '_blank');
    return true;
}

///////////////
// Clear data
///////////////
function clear_data() {
    document.getElementById('clearData').style.display = 'none';
    document.getElementById('deleteRecord').style.display = 'none';
    document.getElementById('manageRecord').innerHTML = 'soumettre un nouvel index';
    document.getElementById('manageRecord').style.left = '391px';
    document.getElementById('OP').value = 'create';
    document.getElementById('idx_ref').value = 0;
    document.getElementById('LABEL').value = '';
    document.getElementById('KEYS').value = '';
    document.getElementById('LINK').value = '';
    document.getElementById('CAT0').value = 0;
    document.getElementById('CAT1').value = cat_name0;

    // Si nous sommes dans la page admin
    if (document.getElementById('officiel0')) {
	document.getElementById('officiel0').checked = 'true';
    }
    return false;
}

/////////////////////////////
// Editer un enregistrement
/////////////////////////////
var idx_ref = 0;
function edit_record(val) {
    idx_ref = val;
    var params='action=EDIT_RECORD';
    params+='&idx='+val;
    n++;
    params+='&n='+n;

    var xhr_object = getXMLHTTP();
    xhr_object.open('POST',ajax, true);
    xhr_object.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
    xhr_object.send(params);

    // wait for the answer
    xhr_object.onreadystatechange = function() {
	if(xhr_object.readyState == 4) {
	    var field = xhr_object.responseText.split('|');
	    switch (parseInt(field[0])) {
	    case 0:
		alert('ERROR: '+field[1]);
		break;
	    case 1:
		document.getElementById('clearData').style.display = 'inline';
		document.getElementById('manageRecord').innerHTML = 'modifier cet index';
		document.getElementById('manageRecord').style.left = '416px';
		document.getElementById('OP').value = 'update';
		document.getElementById('idx_ref').value = idx_ref;

		document.getElementById('LABEL').value = field[3];
		document.getElementById('CAT0').value = field[4];
		document.getElementById('CAT1').value = field[5];
		document.getElementById('KEYS').value = field[6];
		document.getElementById('LINK').value = field[7];

		// Quitter si page non-admin
		if (document.getElementById('set_active')) break;

		// Nous sommes dans la page admin
		document.getElementById('deleteRecord').style.display = 'inline';

		switch(parseInt(field[2])) {
		case 1:
		    document.getElementById('officiel1').checked = 'true';
		    break;

		default:
		    document.getElementById('officiel0').checked = 'true';
		}
		break;
	    }
	}
    }
    return false;
}

//////////////////////////////
// Validation check & submit
//////////////////////////////
function manage_event() {
    // Refuser si catégorie = 0 (Tout)
    if (document.getElementById('CAT0').value == 0) {
	document.getElementById('recordError').innerHTML = "La cat&eacute;gorie n'est pas d&eacute;finie";
	document.getElementById('errorFrame').style.display = 'inline';
	return false;
    }

    // Refuser champ résultat vide
    if (document.getElementById('LABEL').value.length < 6) {
	document.getElementById('recordError').innerHTML = 'Le champ r&eacute;sultat &agrave; afficher est vide';
	document.getElementById('errorFrame').style.display = 'inline';
	return false;
    }

    // Refuser l'absence de mot-clefs
    if (document.getElementById('KEYS').value.length < 2) {
	    document.getElementById('recordError').innerHTML = 'Aucun mot-clef disponible';
	    document.getElementById('errorFrame').style.display = 'inline';
	    return false;
    }

    // Refuser l'absence de lien
    if (document.getElementById('LINK').value.length < 4) {
	    document.getElementById('recordError').innerHTML = 'Le lien vers la page est vide';
	    document.getElementById('errorFrame').style.display = 'inline';
	    return false;
    }
    document.getElementById('admSearch').submit();
}

////////////////////////////////////
// Insert double quote in textarea
////////////////////////////////////
function insertAtCursor(insertZone, myValue, hideZone) {
    var myField = document.getElementById(insertZone), sel;

    // IE support
    if (document.selection) {
        myField.focus();
        sel = document.selection.createRange();
        sel.text = myValue;
    }
    // MOZILLA and others
    else if (myField.selectionStart || myField.selectionStart == '0') {
        var startPos = myField.selectionStart;
        var endPos = myField.selectionEnd;
        myField.value = myField.value.substring(0, startPos)
            + myValue
            + myField.value.substring(endPos, myField.value.length);
    } else {
        myField.value += myValue;
    }

    // Hide ALERT display
    switch (hideZone) {
    case 'none':
	break;

    default:
	document.getElementById(hideZone).style.display = 'none';
    }
}

///////////////////////////////
// Verify syntax On Key Press
///////////////////////////////
function down_syntax(sourceField,format,e) {
	var keyCode = ('which' in e) ? e.which : e.keyCode;
	var shift = e.shiftKey;

	var auto_like = 0, auto_set = 0;
	var lock = 0, cr_count = 0;

	switch (keyCode) {
	case 13:
		switch (format) {
		case 'lock':
		    lock = 1;
		    break;
		}
		switch (sourceField) {
		case 'topicTEXT':
		    cr_count = document.getElementById('short_text').value.match(/\s+/g).length;
		    if (parseInt(cr_count) > 1) lock = 1;
		    break;
		}
		if (parseInt(lock) == 1) {
		    if (document.all) e.returnValue = false;
		    else e.stopPropagation();
		    return false;
		}
		break;
	case 34:
		switch (sourceField) {
		case 'catSUBJECT':
		case 'dateTHEME':
		    document.getElementById('quoteSUBJECT').style.display = 'inline';
		    return false;

		case 'topicTEXT':
		    document.getElementById('quoteText').style.display = 'inline';
		    return false;
		}
		break;
	}
}

///////////////////////////////
// Verify syntax On Key Press
///////////////////////////////
function up_syntax(sourceField,format,e) {
	var keyCode = ('which' in e) ? e.which : e.keyCode;
	var shift = e.shiftKey;

	var auto_like = 0, auto_set = 0;
	var compREG = new RegExp();
	var lock = 0;

	//alert ('Entry code: ' + keyCode);
	switch (keyCode) {
	case 13:
		switch (format) {
		case 'lock':
		    lock = 1;
		    break;
		}

		switch (sourceField) {
		case 'topicTEXT':
		    cr_count = document.getElementById('short_text').value.match(/\s+/g).length;
		    if (parseInt(cr_count) > 1) lock = 1;
		    break;
		}

		if (parseInt(lock) == 1) {
		    e.stopPropagation();
		    return false;
		}
		break;

	case 51:
		switch (sourceField) {
		case 'catSUBJECT':
		case 'dateTHEME':
		    document.getElementById('quoteSUBJECT').style.display = 'inline';
		    return false;

		case 'topicTEXT':
		    document.getElementById('quoteText').style.display = 'inline';
		    return false;
		}
	}
	// var charCode = chr(keyCode);
	var charCode;
	if (keyCode>=65 && keyCode<=90 && shift) {
	    charCode = String.fromCharCode(keyCode);
	}
	if (keyCode>=65 && keyCode<=90 && !shift) {
	    charCode = String.fromCharCode(keyCode+32);
	}
	else charCode = String.fromCharCode(keyCode);
	//alert ('Char code: ' + charCode);
	//if (shift) alert ('Pass (upper) char: ' + keyCode + ' // ' + charCode);
	//else alert ('Pass (lower) char: ' + keyCode + ' // ' + charCode);
	var shunks =  new Array();
	switch (sourceField) {
	case 'dateTHEME':
		shunks = document.getElementById('dateTHEME').value.split('\"');
		if (shunks.length > 1) {
		    document.getElementById('dateTHEME').value = shunks[0];
		    document.getElementById('quoteSUBJECT').style.display = 'inline';
		    return false;
		}
		break;

	case 'catSUBJECT':
		shunks = document.getElementById('catSUBJECT').value.split('\"');
		if (shunks.length > 1) {
		    document.getElementById('catSUBJECT').value = shunks[0];
		    document.getElementById('quoteSUBJECT').style.display = 'inline';
		    return false;
		}
		break;

	case 'topicTEXT':
		shunks = document.getElementById('short_text').value.split('\"');
		if (shunks.length > 1) {
		    document.getElementById('short_text').value = shunks[0];
		    document.getElementById('quoteText').style.display = 'inline';
		    return false;
		}
	}
}