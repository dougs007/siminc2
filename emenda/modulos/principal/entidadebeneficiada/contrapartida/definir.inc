<?php
// topo
include_once APPEMENDA . 'modulos/principal/entidadebeneficiada/contrapartida/partialsControl/topo.inc';

switch ($_REQUEST["requisicao"]) {
	case 'pesquisa':
		$filtros = $obEntContra->geraFiltroContrapartida( $_REQUEST );
	break;
	case 'cadastra':
		$obEntContra->insereContrapartidaMinima( $_REQUEST );
	break;
	case 'modalidade':
		$resultado = $obEntContra->insereContrapartidaModalidade( $_REQUEST );
		if( $resultado ){
			$obEntContra->sucesso( "principal/entidadebeneficiada/contrapartida/definir" );
		} else {
			echo "<script>
						alert('Falha na opera��o');
						window.location.href = window.location;
				  </script>";
		}
	break;
}
monta_titulo( 'Contrapartida M�nima', '');

if( $_REQUEST['requisicao'] == 'mod' ){
	$arTipos = $obEntContra->carregaTipoEntidade( $_POST['resid'] );
} else {
	$arTipos = $obEntContra->carregaTipoEntidade();
}

include_once APPEMENDA.'modulos/principal/entidadebeneficiada/contrapartida/views/formDefault.inc';
?>