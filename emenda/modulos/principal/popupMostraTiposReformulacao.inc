<?php
	$arRegistro = pegaTipoReformulacao( $_GET['ptrid'] );
	monta_titulo('', 'Lista de Reformula��o');
	$cabecalho = array("Codigo","Descri��o Reformula��o");
	$db->monta_lista_array($arRegistro, $cabecalho, 20, 4, 'N','Center');
	
	echo '<table width="95%" cellSpacing="1" cellPadding="3" align="center">
				<tr>
					<td style="text-align: center">
						<input type="button" name="fechar" value="Fechar" onclick="javascript: window.close();">
					</td>
				</tr>
			</table>';
?>
<script type="text/javascript" src="/includes/funcoes.js"></script>
<script type="text/javascript" src="/includes/prototype.js"></script>
<link rel="stylesheet" type="text/css" href="../includes/Estilo.css"/>
<link rel="stylesheet" type="text/css" href="../includes/listagem.css"/>