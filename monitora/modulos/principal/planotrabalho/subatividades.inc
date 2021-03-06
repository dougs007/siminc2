<?php

// carrega as fun��es de integra��o
include "planotrabalho/unidade_atividade_funcoes.php";
// carrega as fun��es do m�dulo pde
include "planotrabalho/_constantes.php";
include "planotrabalho/_funcoes.php";
include "planotrabalho/_componentes.php";

// obt�m dados da atividade vinculada � a��o
$atividade = retornaTarefaUnidade( $_SESSION['monitora_var']['entid'], $_SESSION['exercicio'] );

$db->commit();
if ( $_REQUEST["atiid"] ) {
	$atividade = atividade_pegar( $_REQUEST["atiid"] );
} else {
	$_REQUEST["atiid"] = $atividade["atiid"];
	$atividade = atividade_pegar( $_REQUEST["atiid"] );
}

/*
 * Definir a permiss�o do usu�rio
 */
$permissao = true;
$permissao_formulario = 'S'; # S habilita e N desabilita o formul�rio


// ----- VERIFICA SE PROJETO EST� SELECIONADO
$_SESSION["projeto"] = $atividade["_atiprojeto"];
define( "PROJETO", $atividade["_atiprojeto"] );
projeto_verifica_selecionado( $atividade["atiid"] );

// ----- CABE�ALHO
include APPRAIZ . 'includes/cabecalho.inc';
print '<br/>';

$db->cria_aba( $abacod_tela, $url, '&atiid=' . $atividade['atiid'] );

//montar_titulo_projeto( $atividade['atidescricao'] );
monta_titulo("Plano de Trabalho",$atividade['atidescricao']);

extract( $atividade ); # mant�m o formul�rio preenchido
?>
<table class="tabela" bgcolor="#fbfbfb" cellspacing="0" cellpadding="10" align="center">
	<tr>
		<td>
			<? 
			echo montar_resumo_atividade( $atividade, $numeracao_relativa = true );
			
			$situacao = array(
				STATUS_NAO_INICIADO,
				STATUS_EM_ANDAMENTO,
				STATUS_SUSPENSO,
				STATUS_CANCELADO,
				STATUS_CONCLUIDO
			);
			$diretorio = $_SESSION["sisdiretorio"] . "/atividade";
			echo arvore( $atividade["atiid"], $profundidade, $situacao, null, $diretorio, $numeracao_relativa = true );
			?>
		</td>
	</tr>
</table>
<table class="tabela" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3" align="center">
    <tr style="background-color: #cccccc">	
		<td>
			<input type="hidden" name="atiid" value="<?php echo $_GET[atiid]; ?>">
		</td>
	</tr>		
</table>