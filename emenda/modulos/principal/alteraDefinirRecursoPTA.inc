<?

verificaPermissao();

// Inclui o script para altera��o de um PTA existente
if( $_REQUEST['tipo'] ){
	$tipo = 'popup';
	$_SESSION['emenda']['tpopup'] = $tipo;
} else {
	$tipo = 'alteracao';
	unset($_SESSION['emenda']['tpopup']);
}

include "recursosPTA.inc";

?>