<html>
<head>
	<title><?php echo NOME_SISTEMA; ?></title>
	<script type="text/javascript" src="../includes/prototype.js"></script>
    <link rel="stylesheet" type="text/css" href="../includes/Estilo.css"/>
    <link rel="stylesheet" type="text/css" href="../includes/listagem.css"/>
</head>
<body>
	<table class="tabela" align="center" cellspacing="1" cellpadding="4" >
		<tr>
			<td style="text-align: center;">				
				<b>Minist�rio da Educa��o</b> <br/>
				FUNDO NACIONAL DE DESENVOLVIMENTO DA EDUCA��O <br/>
				<?php echo NOME_SISTEMA; ?>
			</td>
		</tr>
	</table>		
	<br/>
	<table class="tabela" align="center" cellspacing="1" cellpadding="4" >
		<tr>
			<td>
				Para realizar a impress�o corretamente, favor configurar o seu browser conforme as instru��es abaixo.
			</td>
		</tr>
		<tr>
			<th><b>Configura��o para impress�o</b></th>
		</tr>
		<tr>
			<td> Configurar a p�gina removendo os dados de cabe�alho e rodap�.<br/><br/>
				<b>No browser Internet Explorer:</b><br/>
				<font style="color: red;"> Acessar no menu <b>Arquivo (File)</b> a op��o <b>Configurar P�gina (Page Setup)</b>.<br/>
				Na op��o cabe�alho e rodap� altere as sele��es de todas as op��es para <b>"-Vazio-"</b>.<br/>
				Ap�s a conclus�o clique no bot�o <b>OK</b>. </font><br/><br/>
				
				<b>No browser Mozilla Firefox:</b><br/>
				<font style="color: red;"> Acessar no menu <b>Arquivo (File)</b> a op��o <b>Configurar P�gina (Page Setup)</b> e clique na aba <b>Margens</b>.<br/>
				Na op��o cabe�alho e rodap� altere as sele��es de todas as op��es para <b>"--em branco--"</b>.<br/>
				Ap�s a conclus�o clique no bot�o <b>OK</b>. </font><br/><br/>				
				Ap�s estes procedimentos o seu browser estar� configurado para as impress�es necess�rias. </td>
		</tr>
	</table>
	<br/>		
	<table  align="center" cellspacing="1" cellpadding="4" >
		<tr style="text-align: center;">
			<td><input type="button" name="btnRelatorio" id="btnRelatorio" value="Ir para Impress�o" onclick="imprimir(<?=$_REQUEST['parametro']; ?>,'<?=$_REQUEST['tipo']; ?>');">
				<input type="button" name="btnFechar" id="btnFechar" value="Fechar" onclick="window.close();">
			</td>
		</tr>
	</table>		
</body>
<script type="text/javascript">
function imprimir(parametro, tipo){
	if( tipo == 'minuta' ){
		var janela = window.open( 'emenda.php?modulo=principal/popImprimeMinutaPTA&acao=A&tipo=M&ptrid='+parametro, 'relatorio', 'width=450,height=400,status=0,menubar=1,toolbar=0,scrollbars=1,resizable=0' );
		janela.focus();
	} else if(tipo == 'M'){
		var janela = window.open( 'emenda.php?modulo=principal/popImprimeMinutaPTA&acao=A&tipo=M&pmcid='+parametro, 'relatorio', 'width=450,height=400,status=0,menubar=1,toolbar=0,scrollbars=1,resizable=0' );
		janela.focus();
	}else if( tipo == 'T' ){
		var janela = window.open( 'emenda.php?modulo=principal/popImprimeMinutaPTA&acao=A&tipo=T&refid='+parametro, 'relatorio', 'width=450,height=400,status=0,menubar=1,toolbar=0,scrollbars=1,resizable=0' );
		janela.focus();
	}else{
		var janela = window.open("emenda.php?modulo=principal/ptaConsolidado&acao=A&ptrid=" + parametro,"relatorio", "scrollbars=yes,height=600,width=800");
		janela.focus();
	}
}
</script>
</html>