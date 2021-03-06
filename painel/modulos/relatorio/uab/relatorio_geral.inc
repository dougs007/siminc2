<?php
// exibe consulta
if($_POST['relatorio']){
	include "geral_resultado.inc";
	exit;
}


include APPRAIZ . 'includes/cabecalho.inc';
include APPRAIZ . 'includes/Agrupador.php';

echo "<br>";
$db->cria_aba($abacod_tela,$url,'');
$titulo_modulo = "Relat�rio UAB";
monta_titulo( $titulo_modulo, 'Selecione os filtros e agrupadores desejados' );

?>
<script type="text/javascript">

	function uab_exibeRelatorioGeral() {
		var formulario = document.filtro;
		selectAllOptions( formulario.agrupador );
		
		if ( !formulario.agrupador.options.length ){
			alert( 'Favor selecionar ao menos um item para agrupar o resultado!' );
			return false;
		}
		
		selectAllOptions( document.getElementById('regiao') );
		selectAllOptions( document.getElementById('uf') );
		selectAllOptions( document.getElementById('municipio') );
		selectAllOptions( document.getElementById('idmantenedor') );
		selectAllOptions( document.getElementById('iesid') );
		selectAllOptions( document.getElementById('idcurso') );
		selectAllOptions( document.getElementById('tipocurso') );
		selectAllOptions( document.getElementById('polid') );
		
		formulario.target = 'resultadoUABGeral';
		var janela = window.open( '', 'resultadoUABGeral', 'width=800,height=600,status=1,menubar=1,toolbar=0,scrollbars=1,resizable=1' );
		janela.focus();
		formulario.submit();
	}
	
	/* Fun��o para substituir todos */
	function replaceAll(str, de, para){
	    var pos = str.indexOf(de);
	    while (pos > -1){
			str = str.replace(de, para);
			pos = str.indexOf(de);
		}
	    return (str);
	}
	/* Fun��o para adicionar linha nas tabelas */

			
				
	/**
	 * Alterar visibilidade de um bloco.
	 * 
	 * @param string indica o bloco a ser mostrado/escondido
	 * @return void
	 */
	function onOffBloco( bloco )
	{
		var div_on = document.getElementById( bloco + '_div_filtros_on' );
		var div_off = document.getElementById( bloco + '_div_filtros_off' );
		var img = document.getElementById( bloco + '_img' );
		var input = document.getElementById( bloco + '_flag' );
		if ( div_on.style.display == 'none' )
		{
			div_on.style.display = 'block';
			div_off.style.display = 'none';
			input.value = '0';
			img.src = '/imagens/menos.gif';
		}
		else
		{
			div_on.style.display = 'none';
			div_off.style.display = 'block';
			input.value = '1';
			img.src = '/imagens/mais.gif';
		}
	}
	
	/**
	 * Alterar visibilidade de um campo.
	 * 
	 * @param string indica o campo a ser mostrado/escondido
	 * @return void
	 */
	function onOffCampo( campo )
	{
		var div_on = document.getElementById( campo + '_campo_on' );
		var div_off = document.getElementById( campo + '_campo_off' );
		var input = document.getElementById( campo + '_campo_flag' );
		if ( div_on.style.display == 'none' )
		{
			div_on.style.display = 'block';
			div_off.style.display = 'none';
			input.value = '1';
		}
		else
		{
			div_on.style.display = 'none';
			div_off.style.display = 'block';
			input.value = '0';
		}
	}

</script>
<form action="" method="post" name="filtro">
<input type="hidden" name="relatorio" value="1">
<table class="tabela" align="center" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3">

		<tr>
			<td class="SubTituloDireita">Agrupadores</td>
			<td>
				<?php

					// In�cio dos agrupadores
					$agrupador = new Agrupador('filtro','');
					
					// Dados padr�o de destino (nulo)
					$destino = isset( $agrupador2 ) ? $agrupador2 : array();
					
					// Dados padr�o de origem
					$origem = array(
						'mantenedor' => array(
							'codigo'    => 'mantenedor',
							'descricao' => 'Mantenedor'
						),
						'polo' => array(
							'codigo'    => 'polo',
							'descricao' => 'Polo'
						),
						'tipocurso' => array(
							'codigo'    => 'tipocurso',
							'descricao' => 'Tipo Curso'
						),
						'nomecurso' => array(
							'codigo'    => 'nomecurso',
							'descricao' => 'Nome Curso'
						),
						'ies' => array(
							'codigo'    => 'ies',
							'descricao' => 'IES'
						),
						'uf' => array(
							'codigo'    => 'uf',
							'descricao' => 'UF'
						),
						'regiao' => array(
							'codigo'    => 'regiao',
							'descricao' => 'Regi�o'
						),	
						'municipio' => array(
							'codigo'    => 'municipio',
							'descricao' => 'Munic�pio'
						)
												
					);
					
					// exibe agrupador
					$agrupador->setOrigem( 'naoAgrupador', null, $origem );
					$agrupador->setDestino( 'agrupador', null, $destino );
					$agrupador->exibir();
				?>
			</td>
		</tr>
		</table>
		
	<table class="tabela" align="center" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3">
			<tr>
			<td class="SubTituloEsquerda" colspan="2">Filtros</td>
			</tr>
			<?php
				// Regi�o
				$stSql = " SELECT
								regcod AS codigo,
								regdescricao AS descricao
							FROM 
								territorios.regiao
							%s
							ORDER BY
								regdescricao ";
				$stSqlCarregados = "";
				mostrarComboPopup( 'Regi�es', 'regiao',  $stSql, $stSqlCarregados, 'Selecione a(s) Regi�es(s)' );

				// UF
				$stSql = " SELECT
								estuf AS codigo,
								estdescricao AS descricao
							FROM 
								territorios.estado
							ORDER BY
								estdescricao ";
				mostrarComboPopup( 'UF', 'uf',  $stSql, $stSqlCarregados, 'Selecione a(s) UF(s)' );

				// Munic�pio
				$stSql = "  SELECT
								tm.muncod AS codigo,
								tm.estuf || ' - ' || tm.mundescricao AS descricao
							FROM 
								territorios.municipio tm
							ORDER BY
								mundescricao ";
				mostrarComboPopup( 'Munic�pio', 'municipio',  $stSql, $stSqlCarregados, 'Selecione o(s) Munic�pio(s)' );

				// Mantenedor
				$stSql = "SELECT
								idmantenedor AS codigo,
								mantenedor AS descricao
							FROM 
								 painel.consultaofertas 
							GROUP BY 
								idmantenedor,
								mantenedor
							ORDER BY
								mantenedor";
				mostrarComboPopup( 'Mantenedor', 'idmantenedor',  $stSql, $stSqlCarregados, 'Selecione o(s) Mantenedor(es)' );

				// IES
				$stSql = "  SELECT
								iesid AS codigo,
								iesdsc AS descricao
							FROM 
								 painel.consultaofertas co 
							INNER JOIN 
								painel.ies ie ON ie.iesid = trim(co.idies)::integer
							GROUP BY 
								iesid,
								iesdsc
							ORDER BY
								iesdsc";
				mostrarComboPopup( 'IES', 'iesid',  $stSql, $stSqlCarregados, 'Selecione o(s) IES' );
				
				// Nome Curso
				$stSql = "SELECT
								idcurso AS codigo,
								nomecurso AS descricao
							FROM 
								 painel.consultaofertas 
							GROUP BY 
								idcurso,
								nomecurso
							ORDER BY
								nomecurso";
				mostrarComboPopup( 'Nome Curso', 'idcurso',  $stSql, $stSqlCarregados, 'Selecione o(s) Curso(s)' );
				
				// Tipo Curso
				$stSql = "SELECT
								tipocurso AS codigo,
								tipocurso AS descricao
							FROM 
								 painel.consultaofertas 
							GROUP BY 
								tipocurso
							ORDER BY
								tipocurso";
				mostrarComboPopup( 'Tipo Curso', 'tipocurso',  $stSql, $stSqlCarregados, 'Selecione o(s) Tipo(s) Curso(s)' );
				
				// Polo
				$stSql = "  SELECT
								polid AS codigo,
								poldsc AS descricao
							FROM 
								 painel.consultaofertas co 
							INNER JOIN 
								painel.polo pl ON pl.polid = trim(co.idpolo)::integer
							GROUP BY 
								polid,
								poldsc
							ORDER BY
								poldsc";
				mostrarComboPopup( 'Polo', 'polid',  $stSql, $stSqlCarregados, 'Selecione o(s) Polo(s)' );
				
				
			?>
		<tr>
			<td bgcolor="#CCCCCC"></td>
			<td bgcolor="#CCCCCC">
				<input type="button" value="Visualizar" onclick="uab_exibeRelatorioGeral();"/>
			</td>
		</tr>
	</table>
</form>