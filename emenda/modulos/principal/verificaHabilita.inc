<?php
require_once APPRAIZ . "includes/classes/Fnde_Webservice_Client.class.inc";
require_once APPRAIZ . "emenda/classes/LogErroWS.class.inc";
require_once APPRAIZ . "emenda/classes/Habilita.class.inc";


$_SESSION["emenda"]["ptrid"] = !empty( $_REQUEST["ptrid"] ) ? $_REQUEST["ptrid"] : $_SESSION["emenda"]["ptrid"];
$ptrid = $_SESSION["emenda"]["ptrid"];

if ( !$ptrid ){
	echo '<script>
			alert("A sess�o do Plano de Trabalho foi perdida!");
			window.location = "emenda.php?modulo=principal/analiseDadosPTA&acao=A";
		  </script>';
	die;
}

include_once APPRAIZ . 'includes/workflow.php';
if( $_SESSION['emenda']['tpopup'] != 'popup' ){
	include  APPRAIZ."includes/cabecalho.inc";
} else {
	echo '<script type="text/javascript" src="/includes/funcoes.js"></script>
		  <script type="text/javascript" src="/includes/prototype.js"></script>
		  <link rel="stylesheet" type="text/css" href="../includes/Estilo.css"/>
		  <link rel="stylesheet" type="text/css" href="../includes/listagem.css"/>';
}

print "<br/>";

$estadoAtual = pegarEstadoAtual( $_SESSION["emenda"]["ptrid"] );

echo exibeInstituicaoBenefiada( $_SESSION["emenda"]["enbid"] );
print "<br/>";
montaAbasPTA( $abacod_tela, $url, '', $estadoAtual );

// Cria o t�tulo da tela
//monta_titulo( 'Execu��o do PTA', "<img border='0' src='../imagens/obrig.gif' title='Indica campo obrigat�rio.' /> Indica os campos obrigat�rios");
monta_titulo( 'Consulta Habilita��o', "");

echo cabecalhoPlanoTrabalho($ptrid);
$obHabilita = new Habilita();
$cnpj = $obHabilita->pegaCnpj($ptrid);

$arPerfil = pegaPerfilArray( $_SESSION['usucpf'] );

if(  in_array( INSTITUICAO_BENEFICIADA, $arPerfil ) ) {
	$sql = "SELECT DISTINCT
			    count(ini.iniobras)
			FROM
				emenda.planotrabalho ptr
			    inner join emenda.entidadebeneficiada ent on ent.enbid = ptr.enbid
			    inner join emenda.ptiniciativa pti on pti.ptrid = ptr.ptrid
			    inner join emenda.iniciativa ini on ini.iniid = pti.iniid    
			WHERE
			    ptr.ptrstatus = 'A' 
			    AND ptr.ptrexercicio = 2010
			    and ini.iniobras = 'S'
			    and ptr.ptrid = $ptrid
			    AND ptr.ptrid NOT IN (SELECT tt.ptridpai FROM emenda.planotrabalho tt WHERE tt.ptridpai = ptr.ptrid and tt.ptrstatus = 'A')";
	if($db->pegaUm( $sql ) == 0){
		$html = '<tr>
					<td>Senhores dirigentes, \nInformamos que a efetiva��o do conv�nio dar-se-� mediante a apresenta��o da documenta��o de comprova��o de dominialidade.</td>
				</tr>';
	}
}
?>
<html>
<script src="../includes/prototype.js"></script>
<script type="text/javascript" src="js/emenda.js"></script>
<link rel="stylesheet" type="text/css" href="css/emenda.css"/>
<body>
	<table id="tblform" class="tabela" width="95%" bgcolor="#f5f5f5" cellspacing="1" cellpadding="2" align="center">
		<?=$html; ?>
		<tr>
			<td><a href="http://www.fnde.gov.br/index.php/ph-arquivos/category/5-2011?download=57%3Ares02213052011">
				Resolu��o n� 22 de 13 de maio de 2011 � Estabelece os documentos necess�rios � certifica��o da situa��o de regularidade para transfer�ncia de recursos e habilita��o de entidades. 
				</a></td>
		</tr>
		<tr>
			<td colspan="2" class="subtitulocentro">Situa��o Habilita��o</td>
		</tr>
		<tr>
			<td align="center"><?php echo $obHabilita->consultaHabilita($cnpj,true); ?></td>
		</tr>
	</table>
</body>
</html>