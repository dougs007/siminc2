<!--  
// � necess�rio que a tela que chamou esta, informe os parametros abaixo:
// 'nomecampo': � o nome do campo da tabela que ser� utilizado para recupera o texto que ser� exibido na tela
// 'nometabela': � o nome da tabela que ser� recuperado o texto
// 'nomeid': � o nome da coluna da tabela que ser� a chave da busca.
// 'id': � o identificador do registro que ser� recuperado.

// Esta p�gina � chamada pela /principal/documentosAnalisePTA.inc para exibir os documentos extras da emenda.
-->

<form id="formulario" name="formulario" method="post" >

<table width="100%" class="tabela" align="center">
    <tr>
        <td>
			<?php
				// Recupera o texto do documento
				
				$sql = "SELECT ".$_REQUEST["nomecampo"]."
						FROM ".$_REQUEST["nometabela"]."
						WHERE ".$_REQUEST["nomeid"]." = ".$_REQUEST["id"];
				
				$texto = $db->pegaUm($sql);

			?> 
			<div id="conteudo" style="font-weight:normal;vertical-align:top; FONT: 8pt Arial,verdana">
				<?=html_entity_decode($texto)?>
			</div>
        </td>
    </tr>
</table>
    
</form>
</body>