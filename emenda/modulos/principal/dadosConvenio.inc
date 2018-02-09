<?php
if( $_SESSION['emenda']['tpopup'] != 'popup' ){
	include  APPRAIZ."includes/cabecalho.inc";
} else {
	echo '<script type="text/javascript" src="/includes/funcoes.js"></script>
		  <script type="text/javascript" src="/includes/prototype.js"></script>
		  <link rel="stylesheet" type="text/css" href="../includes/Estilo.css"/>
		  <link rel="stylesheet" type="text/css" href="../includes/listagem.css"/>';
}
print "<br/>";
//validaSessionPTA( $_SESSION['emenda']['federal'] );

$estadoAtual = pegarEstadoAtual( $_SESSION["emenda"]["ptrid"] );

$boConvenio = ($estadoAtual == CONVENIO_CANCELADO ? 'Sim' : 'N�o');

$ptrid = $_SESSION["emenda"]["ptrid"];

echo exibeInstituicaoBenefiada( $_SESSION["emenda"]["enbid"] );
print "<br/>";
montaAbasPTA( $abacod_tela, $url, '', $estadoAtual );

monta_titulo( 'Dados do Conv�nio', '');

echo cabecalhoPlanoTrabalho( $ptrid );

$sql = "SELECT
			ptr.ptrcod,
		    ptr.ptrnumconvenio,
		    ptr.ptrnumprocessoempenho,
		    enb.enbsituacaohabilita,
		    to_char(ptv.vigdatainicio, 'DD/MM/YYYY') as vigdatainicio,
		    to_char(ptp.pubdatapublicacao, 'DD/MM/YYYY') as pubdatapublicacao,
		    to_char(ptv.vigdatafim, 'DD/MM/YYYY') as vigdatafim,
		    b.bconome,
			cc.cocnu_agencia,
		    cc.cocnu_conta_corrente,
		    to_char(ptv.vigdatafim - now(), 'DD') as diasfim,
		    to_char(CAST(ptv.vigdatafim AS DATE) + 60, 'DD/MM/YYYY') as dataprestacao
		FROM
			emenda.planotrabalho ptr
		    inner join emenda.entidadebeneficiada enb on enb.enbid = ptr.enbid
		    inner join emenda.ptvigencia ptv on ptv.ptrid = ptr.ptrid
		    inner join emenda.ptminutaconvenio ptm on ptm.ptrid = ptr.ptrid and ptm.pmcstatus = 'A'
		    left join emenda.ptpublicacao ptp on ptp.pmcid = ptm.pmcid
		    left join emenda.contacorrente cc on cc.ptrid = ptr.ptrid
			left join emenda.banco b on b.bcoid = ptr.bcoid
		WHERE
			ptr.ptrid = $ptrid
		    and enb.enbstatus = 'A'
		    and ptr.ptrid NOT IN (SELECT tt.ptridpai FROM emenda.planotrabalho tt WHERE tt.ptridpai = ptr.ptrid and tt.ptrstatus = 'A')";
$arDados = $db->pegaLinha( $sql );

$arDados['ptrnumprocessoempenho'] = substr($arDados['ptrnumprocessoempenho'],0,5) . "." .
											substr($arDados['ptrnumprocessoempenho'],5,6) . "/" .
											substr($arDados['ptrnumprocessoempenho'],11,4) . "-" .
											substr($arDados['ptrnumprocessoempenho'],15,2);

if( $arDados['diasfim'] <= 60 ){
	$fimVigencia = "<div style='text-align: left; width: 50%; color: red;'>".$arDados['vigdatafim']."</div><div style='text-align: center; width: 50%; color: red;'>ATEN��O<br>
	Faltam ".$arDados['diasfim']." dias para o fim da vig�ncia do conv�nio.</div>";
} else {
	$fimVigencia = $arDados['vigdatafim'];
}
?>
<form name="formulario" id="formulario" method="post">
	<table class="tabela" align="center" border="0" cellpadding="5" cellspacing="1">
		<?if( !empty($arDados['ptrnumconvenio']) ){ ?>
		<tr>
			<td class="SubtituloDireita" style="width: 33%">N�mero do Conv�nio:</td>
			<td bgcolor="#F7F7F7"><?=$arDados['ptrnumconvenio']; ?></td>
			<td class="SubtituloDireita" style="width: 33%">N�mero do Processo:</td>
			<td bgcolor="#F7F7F7"><?=$arDados['ptrnumprocessoempenho']; ?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Situa��o de Habilita��o:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$arDados['enbsituacaohabilita']; ?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Dados Banc�rios:</td>
			<td colspan="4" bgcolor="#F7F7F7">
				<table class="tabela" align="center" border="0" cellpadding="5" cellspacing="1">
				<tr>
					<td class="SubtituloDireita" style="width: 20%">Banco:</td>
					<td style="80%" bgcolor="#F7F7F7"><?=$arDados['bconome']; ?></td>
				</tr>
				<tr>
					<td class="SubtituloDireita">Ag�ncia</td>
					<td bgcolor="#F7F7F7"><?=$arDados['cocnu_agencia']; ?></td>
				</tr>
				<tr>
					<td class="SubtituloDireita">Conta</td>
					<td bgcolor="#F7F7F7"><?=$arDados['cocnu_conta_corrente']; ?></td>
				</tr></table>
			</td>	
		</tr>
		<tr>
			<td class="SubtituloDireita">Objeto do Conv�nio:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?
			$sql = "SELECT
						obj.obcdsc
					FROM
						emenda.objetoconvenio obj
					    inner join emenda.objetominutaconvenio obm on obm.obcid = obj.obcid
					    inner join emenda.ptminutaconvenio ptm on ptm.pmcid = obm.pmcid and ptm.pmcstatus = 'A'
					WHERE
						ptm.ptrid = ".$ptrid;
			$arObjeto = $db->carregarColuna( $sql );
			$arObjeto = $arObjeto ? $arObjeto : array();
			echo implode( '<br>', $arObjeto );
			?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Data de Assinatura Conv�nio e/ou Termo Aditivo:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$arDados['vigdatainicio']; ?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Data da Publica��o no DOU:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$arDados['pubdatapublicacao']; ?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Data do Fim da vig�ncia:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$fimVigencia;?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Quantidade de dias para apresenta��o da Presta��o de Contas:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$arDados['diasfim'] + 60; ?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Data para apresenta��o da Presta��o de Contas:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$arDados['dataprestacao']; ?></td>
		</tr>
		<tr>
			<td class="SubtituloDireita">Conv�nio cancelado:</td>
			<td colspan="4" bgcolor="#F7F7F7"><?=$boConvenio; ?></td>
		</tr>
		<?} else { ?>
		<tr>
			<td style="text-align: center; color: red;">Para este plano de trabalho n�o existe conv�nio firmado at� o momento.</td>
		</tr>
		<?} ?>
	</table>
</form>