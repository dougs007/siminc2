<?php

$plicod = "";
$plicod = $_REQUEST['pi'] ? $_REQUEST['pi'] : null;

monta_titulo( 'Dados da Revis�o', 'Plano Interno: ' . $plicod );

// Busca as informa��es da �ltima revis�o
if ( !empty( $plicod ) ){
	
	$sql = "";
	$sql = "SELECT
				su.usunome as nome,
				su.usufoneddd || ' ' || su.usufonenum as telefone, 
				to_char(mp.piodata, 'DD/MM/YYYY �s HH24:MI') as data,
				mp.pioobs as obs
			FROM
				monitora.planointernoobservacao mp
			INNER JOIN
				seguranca.usuario su ON mp.usucpf = su.usucpf  
			WHERE 
				plicod = '{$plicod}'";
	
	$dados = "";
	$dados = $db->carregar($sql);
	
}

?>
<html>
	<head>
		<title> Simec - Sistema Integrado de Monitoramento do Minist�rio da Educa��o </title>
		<script language="JavaScript" src="../includes/funcoes.js"></script>
		<link rel="stylesheet" type="text/css" href="../includes/Estilo.css">
		<link rel='stylesheet' type='text/css' href='../includes/listagem.css'>
	</head>
	<body>
		<table class="tabela" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3"	align="center">
			<?php 
				$cabecalho = array("Registrado Por", "Telefone", "Data de Inclus�o", "Observa��o");
				$db->monta_lista( $sql, $cabecalho, 100, 30, 'N', 'center', '' );
			?>
		</table>
		<table class="tabela" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3"	align="center">
			<tr bgcolor="#C0C0C0">
				<td>
					<input style="cursor:pointer;" type="button" value="Fechar" onclick="self.close();"/>
				</td>
			</tr>
		</table>
	</body>
</html>