<?
require_once( APPRAIZ . "includes/cabecalho.inc" );
//$objProjeto = new Projeto();
$pjeid = $_SESSION['pjeid'];
$objProjeto = new projetoPT();
$objProjeto = $objProjeto->getProjetoPeloId( $pjeid );


if( @$_REQUEST['correcao'] == 1 )
{
	$objTarefa = new TarefaPT();
	$objTarefa->reparaTarefas( $objProjeto );
	AbstractEntity::updateAllChangedEntities();
	$db->commit();
	dbg( 'A Corre��o Foi Efetivada!' );
}


function projetoaberto()
 {
 	 global $db;
	 
 	// verifica se o projeto esta aberto para ser acompanhado,	//
 	// ou seja, se ele nao esta concluido, cancelado etc.		//
 	
	
	$sql = ' SELECT ' .
				'tpscod' .
			' FROM ' .
				'monitora.projetoespecial' .
			' WHERE ' .
				'pjeid' . ' = ' . $_SESSION['pjeid'];
	$sit=$db->pegaUm($sql);
	if ($sit=='11' or $sit=='10')
	{
		// se o projeto estiver Fase de planejamento ou Fase de Execu��o ent�o pode acompanhar
		return true;
	}
	else
	{
		return false;
	}
}



print '<br/>';
$db->cria_aba($abacod_tela,$url,'');
$titulo_modulo='Estruturar o Plano de Trabalho do Projeto Especial <img src="../imagens/grupo.gif" title="Ver equipe do projeto" onclick="mostra_equipe()">  ';
monta_titulo($titulo_modulo,'');

$arrTarefasPrincipais = $objProjeto->getArrTarefasDoProjeto();
?>

	<!--  comeco da lista tarefas do projeto -->
	
		<!--[if !IE]>-->
			<LINK REL="StyleSheet" HREF='../../includes/JsLibrary/css/tabelaTarefaNotIE.css' />
		<!--<![endif]-->
		<!--[if IE]>-->
			<LINK REL="StyleSheet" HREF='../../includes/JsLibrary/css/tabelaTarefaIE.css' />
		<!--<![endif]-->
		
		<script type="text/javascript" src="../../includes/JsLibrary/_start.js"></script>
		<script type="text/javascript" src="../../includes/JsBusiness/listaTarefas.js"></script>
	<body>
		<div id="EditarTarefa">
			<center>
				<table  class="tabela" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3" align="center" style="color:#808080;">
					<tr>
						<td align='right' class="SubTituloDireita">Projeto :</td>
						<td><b> <?= $objProjeto->getCodigo() ?> &nbsp;-&nbsp; <?= $objProjeto->getNome() ?> </b></td>
					</tr>
					<tr>
						<td align='right' class="SubTituloDireita">Per�odo do Projeto:</td>
						<td>
							<b> <?= $objProjeto->getDataInicio() ?> &nbsp; - &nbsp; <?= $objProjeto->getDataFim() ?></b>
						</td>
					</tr>  
					<tr>
						<td align="right"  class="SubTituloDireita">
							GR�FICO DE GANTT
						</td>
						<td>
							<input type="button" class='botao' 
							value='Ver Gr�fico' title='Ver Gr�fico.' 
							onclick="exibe_grafico( 'Projeto' , <?= $objProjeto->getId() ?> )">
							<select id="profunidadeNivel">
								<option value="1" > Apenas N�vel 1 </option>
								<option value="2" > At� N�vel 2 </option>
								<option value="3" > At� N�vel 3 </option>
								<option value="4" > At� N�vel 4 </option>
								<option value="1000" > Todos os N�veis </option>
							</select>     
						</td>
					</tr>
					<? if ( $objProjeto->getProjetoAberto()): ?>
						<tr >
							<td   class="SubTituloDireita">
								<input type="submit" value="Inserir Tarefa" 
								onclick="insertElement( this , 0, <?= $objProjeto->getId() ?>, 'TarefaPT' , function(){ window.location.reload() } )" />
							</td>
						</tr>
					<? endif ?>
				</table>
			</center>
		</div>
		<center>
			<div id="listaTarefas" >
				<table border="0" class="tabelaTarefas">
					<thead>
						<tr>
							<th class="tarefaMais">
								Codigo
							</th>
							<th class="tarefaOrdem">
								Op��es
							</th>
							<th class="tarefaNome">
								Titulo
							</th>
							<th class="tarefaDescricao">
								Descri&ccedil;&atilde;o
							</th>
							<th class="tarefaInicio">
								In&iacute;cio
							</th>
							<th class="tarefaTermino">
								T&eacute;rmino
							</th>
							<th class="tarefaAprovada">
								Fec.
							</th>
							<th class="tarefaTipo">
								Predecessora
							</th>
							<th style="width: 13px;">
							</th>
						</tr>
					</thead>
					<tbody>
					</tbody>
				</table>
			</div>
			<div id="conteudoTarefas">
			<?php
			if ( sizeof( $arrTarefasPrincipais) > 0 ) 
			{
				geraTabelaTarefas( $arrTarefasPrincipais );
			}
			?>
			</div>
		</center>
	</body>
	<script>
		if( !IE )
		{
			finishing();
		}
		else
		{
			setTimeout( finishing , 1000 );
		}
	</script>
</html>
