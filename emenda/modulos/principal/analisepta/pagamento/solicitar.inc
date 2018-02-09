<?php
// topo
include_once APPEMENDA . 'modulos/principal/analisepta/pagamento/partialsControl/topo.inc';
require_once APPRAIZ . "emenda/classes/WSEmpenho.class.inc";
require_once APPRAIZ . "emenda/classes/ExecucaoFinanceira.class.inc";
require_once APPRAIZ . "emenda/classes/Habilita.class.inc";

unset( $_SESSION['emenda']['msgErro'] );
$_SESSION['emenda']['msgErro'] = array();

$boReformulacao = pegaPaiPTA( $_SESSION["emenda"]["ptridAnalise"] );
$boReformulacao = ( !empty($boReformulacao) ? true : false );

$estadoAtual = pegarEstadoAtual( $_SESSION["emenda"]["ptridAnalise"] );

montaAbasAnalise( $abacod_tela, $url, '' , $estadoAtual, $boReformulacao);
// Cria o t�tulo da tela
monta_titulo( 'Pagamento', "<img border='0' src='../imagens/obrig.gif' title='Indica campo obrigat�rio.' /> Indica os campos obrigat�rios");

echo cabecalhoPlanoTrabalho($ptrid, true);
montaVisualizarPTA( $_SESSION["emenda"]["ptridAnalise"], false, $boReformulacao );

$arRrefid = verificaTiposReformulacao( $ptrid, 'codigo' );	

$arrPerfil = pegaPerfilArray( $_SESSION['usucpf'] );

if ( ($estadoAtual != EM_LIBERACAO_RECURSO && $estadoAtual != EM_LIBERACAO_RECURSO_REFORMULACAO) && ( !in_array( PAGAMENTO, $arrPerfil) || in_array(SUPER_USUARIO, $arrPerfil) ) ) {
	$boDisabled = 'disabled="disabled"';
}
$boPendencia = false;
$label = 'N� Empenho Original';
if( !$boReformulacao ){
	$federal = buscaEmendaDescentraliza( $ptrid );
	
	$label = 'N� Empenho Original';
	if( $federal == 'S' ) $label = 'Nota de Cr�dito';
}
$obHabilita = new Habilita();
$cnpjHabilita = $obHabilita->pegaCnpj($ptrid);

$sql = "SELECT distinct em.empnumeroprocesso||'&nbsp;' as processo, em.empcodigoptres||'&nbsp;' as ptres, em.empcodigopi,
			to_char(pa.pagdatapagamento, 'DD/MM/YYYY') as datapagamento, pa.parnumseqob||'&nbsp;' as ordembancaria, pa.pagsituacaopagamento,
			p.pobvalorpagamento, p.pobpercentualpag
			FROM par.subacaoemendapta sep
			inner join par.subacaodetalhe sd on sd.sbdid = sep.sbdid
			inner join par.subacao s on s.sbaid = sd.sbaid
			inner join par.pagamentosubacao p on p.sbaid = s.sbaid and pobstatus = 'A' -- se tiver nesta tabela teve empenho
			inner join par.pagamento pa on pa.pagid = p.pagid and pa.pagstatus = 'A'
			inner join par.empenho em on em.empid = pa.empid and empstatus = 'A'
			inner join emenda.ptemendadetalheentidade ped on ped.ptrid = sep.ptrid
			inner join emenda.v_emendadetalheentidade ved on ved.edeid = ped.edeid
		WHERE
			sep.ptrid = $ptrid
			and sep.sepstatus = 'A'
			and ved.edestatus = 'A'";

$arrDadosPagPar = $db->carregar( $sql );
$arrDadosPagPar = $arrDadosPagPar ? $arrDadosPagPar : array();


if($arrDadosPagPar[0]){
	echo '<table id="tblform" class="tabela" width="95%" bgcolor="#f5f5f5" cellspacing="1" cellpadding="2" align="center">
				<tr>
					<th colspan="2" class="subtitulocentro">Pagamento PAR</th>
				</tr>
				<tr>
					<th class="subtitulocentro" colspan="2" style="color: red;">Este plano de trabalho foi realizado o pagamento como transfer�ncia direta no sistema PAR.</th>
				</tr>
				<tr>
					<th colspan="2" class="subtitulocentro">Dados do Pagamento PAR</th>
				</tr>
			</table>';
	$cabecalho = array('N�mero do Processo', 'N�mero do PTRES', 'N�mero do PI', 'Data Pagamento', 'N� Ordem banc�ria', 'Situa��o', 'Valor', '% Empenhado');
	$db->monta_lista_array($arrDadosPagPar, $cabecalho, 5000, 20, 'S', 'center', '');
} else {

	$arDadosPag = $obPagamento->selectParaPagamento();
	
	$arMSG = array();
	$arMSGExiste = array();
	$arrPendencia = array();
	foreach ($arDadosPag as $v) {
		$arMSG = array();
		if( empty($v['enbcnpj']) ) 				 
	//		if( !in_array( 'enbcnpj', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">N� do cnpj da entidade n�o foi encontrado vinculado ao PTA!</span>' );
				array_push( $arMSGExiste, 'enbcnpj' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['cocseq_conta']) )
	//		if( !in_array( 'cocseq_conta', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">N� sequencial da conta corrente n�o encontrado!</span>' );
				array_push( $arMSGExiste, 'cocseq_conta' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['ptrnumprocessoempenho']) ) 
	//		if( !in_array( 'ptrnumprocessoempenho', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">N� processo empenho n�o encontrado (aba informa��es gerais)!</span>' );
				array_push( $arMSGExiste, 'ptrnumprocessoempenho' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['ptranoconvenio']) )
	//		if( !in_array( 'ptranoconvenio', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">Ano do conv�nio n�o cadastrado!</span>' );
				array_push( $arMSGExiste, 'ptranoconvenio' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['ptrnumconvenio']) )
	//		if( !in_array( 'ptrnumconvenio', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">N� do conv�nio n�o cadastrado!</span>' );
	//			array_push( $arMSGExiste, 'ptrnumconvenio' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['pmcnumconveniosiafi']) ) 	 
	//		if( !in_array( 'pmcnumconveniosiafi', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">N� do conv�nio SIAF n�o cadastrado (� necess�rio importar o conv�nio)!</span>' );
	//			array_push( $arMSGExiste, 'pmcnumconveniosiafi' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['exfvalor']) ) 			 
	//		if( !in_array( 'exfvalor', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">Valor do pagamento n�o informado (aba informa��es gerais)!</span>' );
	//			array_push( $arMSGExiste, 'exfvalor' );
				$arrPendencia[$v['exfid']] = $arMSG;
	//		}
		if( empty($v['pubdatapublicacao']) && ( !in_array(APOSTILAMENTO, $arRrefid) ) ) 	 
	//		if( !in_array( 'pubdatapublicacao', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">Data de publica��o n�o cadastrada (aba DOU)!</span>' );
	//			array_push( $arMSGExiste, 'pubdatapublicacao' );
				$arrPendencia[$v['exfid']] = $arMSG;
			//}
		if( empty($v['exfnumempenhooriginal']) ) 
			//if( !in_array( 'exfnumempenhooriginal', $arMSGExiste ) ){
				array_push( $arMSG, '<span style="color: red; font-weight: bold;">N� do empenho original n�o cadastrado (Empenho n�o efetivado)!</span>' );
				//array_push( $arMSGExiste, 'exfnumempenhooriginal' );
				$arrPendencia[$v['exfid']] = $arMSG;
			//}
	}
	
	//if( !empty( $arMSG ) || $obHabilita->consultaHabilitaEntidade($cnpjHabilita, true) != 3  ) $boPendencia = true;
	
	$arDados = $obPagamento->carregaDadosEmpenhoPagamento();
	include_once APPEMENDA.'modulos/principal/analisepta/pagamento/views/formDefault.inc';
	include_once APPEMENDA.'modulos/principal/analisepta/pagamento/views/partialsViews/listaSolicitacaoPagamento.inc';
	
	/*foreach ($arParcela as $key => $v) {
		$boSolicitacao = ( $v['orbnumsolicitacao'] ? true : false );
		$numparcela = sizeof($arParcelaPaga);
		if( !$boSolicitacao ){
		echo "<script>
			$('boalterou').value = 'false';
			
			var valorPag = 'valorigual_'+{$v['exfid']};
			var parcela = {$numparcela};
			
			//verifica se o valor da parcela e menor que o valor total do pagamento
			if($(valorPag).value == '1'){
				carregarParcela( '{$v['orbmesparcela']}', '{$v['orbanoparcela']}', '{$v['orbvalorparcela']}', '{$v['orbid']}', '{$v['exfid']}', '', '{$boDisabled}', parcela );
			}
			</script>";
		}
	}*/
}
?>