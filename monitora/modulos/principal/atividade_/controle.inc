<?php

// carrega as fun��es do m�dulo pde
include APPRAIZ . "pde/www/_constantes.php";
include APPRAIZ . "pde/www/_funcoes.php";
include APPRAIZ . "pde/www/_componentes.php";

$atividade = atividade_pegar( $_REQUEST['atiid'] );
if ( !$atividade ) {
	redirecionar( 'principal/atividade_/arvore', 'A' );
}

$parametros = array(
	'aba' => $_REQUEST['aba'], # mant�m a aba ativada
	'atiid' => $_REQUEST['atiid'] 
);

// impede que usu�rio sem permiss�o acione eventos
if ( $_REQUEST['evento'] && !atividade_verificar_responsabilidade( $_REQUEST['atiid'], $_SESSION['usucpf'] ) ) {
	redirecionar( $_REQUEST['modulo'], $_REQUEST['acao'], $parametros );
}

switch( $_REQUEST['evento'] ){

	case 'cadastrar_controle':
		$sql = sprintf(
			"insert into pde.observacaoatividade ( obsdescricao, obsmedida, atiid, usucpf ) values ( '%s', '%s', %d, '%s' )",
			$_REQUEST['obsdescricao'],
			$_REQUEST['obsmedida'],
			$_REQUEST['atiid'],
			$_SESSION['usucpf']
		);
		if ( !$db->executar( $sql ) ) {
			$db->rollback();
		} else {
			$db->commit();
		}
		redirecionar( $_REQUEST['modulo'], $_REQUEST['acao'], $parametros );
		break;

	case 'excluir_controle':
		$sql = sprintf(
			"update pde.observacaoatividade set obsstatus = 'I' where obsid = %d",
			$_REQUEST['obsid']
		);
		if( !$db->executar( $sql ) ){
			$db->rollback();
		} else {
			$db->commit();
		}
		redirecionar( $_REQUEST['modulo'], $_REQUEST['acao'], $parametros );
		break;

	case 'controlar_solucao':
		if ( $_REQUEST['obssolucao'] == 't' ) {
			$sql = sprintf(
				"update pde.observacaoatividade set
					obssolucao = true,
					obsdatasolucao = '%s',
					obsmedida = '%s',
					usucpfsolucao = '%s'
				where obsid = %d",
				formata_data_sql( date( 'd/m/Y' ) ),
				$_REQUEST['obsmedida'],
				$_SESSION['usucpf'],
				$_REQUEST['obsid']
			);
		} else {
			$sql = sprintf(
				"update pde.observacaoatividade set
					obssolucao = false,
					obsdatasolucao = null,
					obsmedida = '%s',
					usucpfsolucao = null
					where obsid = %d",
				$_REQUEST['obsmedida'],
				$_REQUEST['obsid']
			);
		}
		if( !$db->executar( $sql ) ){
			$db->rollback();
		} else {
			$db->commit();
		}
		redirecionar( $_REQUEST['modulo'], $_REQUEST['acao'], $parametros );
		break;

	default:
		break;

}

$permissao = atividade_verificar_responsabilidade( $atividade['atiid'], $_SESSION['usucpf'] );
$permissao_formulario = $permissao ? 'S' : 'N'; # S habilita e N desabilita o formul�rio

// VERIFICA SE PROJETO EST� SELECIONADO
projeto_verifica_selecionado();

// CABE�ALHO
include APPRAIZ . 'includes/cabecalho.inc';
print '<br/>';
$db->cria_aba( $abacod_tela, $url, '&atiid=' . $atividade['atiid']  );
montar_titulo_projeto( $atividade['atidescricao'] );

extract( $atividade ); # mant�m o formul�rio preenchido
?>
<!-- habilita o tiny -->
<script language="javascript" type="text/javascript" src="../includes/tiny_mce.js"></script>
<script language="JavaScript">
//Editor de textos
tinyMCE.init({
	theme : "advanced",
	mode: "specific_textareas",
	editor_selector : "text_editor_simple",
	plugins : "table,save,advhr,advimage,advlink,emotions,iespell,insertdatetime,preview,zoom,flash,searchreplace,print,contextmenu,paste,directionality,fullscreen",
	theme_advanced_buttons1 : "undo,redo,separator,link,bold,italic,underline,forecolor,backcolor,separator,justifyleft,justifycenter,justifyright, justifyfull, separator, outdent,indent, separator, bullist",
	theme_advanced_buttons2 : "",
	theme_advanced_buttons3 : "",
	theme_advanced_toolbar_location : "top",
	theme_advanced_toolbar_align : "left",
	extended_valid_elements : "a[name|href|target|title|onclick],img[class|src|border=0|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name],hr[class|width|size|noshade],font[face|size|color|style],span[class|align|style]",
	language : "pt_br",
	width : "450px",
	entity_encoding : "raw"
	});
</script>

<script language="javascript" type="text/javascript">
	
	function cadastrar_controle(){
		if ( validar_formulario_controle() ) {
			document.controle.submit();
		}
	}
	
	function validar_formulario_controle(){
		var validacao = true;
		var mensagem = 'Os seguintes campos n�o foram preenchidos:';
		if ( tinyMCE.getContent('obsdescricao') == '' ) {
			mensagem += '\nConte�do';
			validacao = false;
		}
		if ( !validacao ) {
			alert( mensagem );
		}
		return validacao;
	}
	
	function excluirControle( controle ){
		if ( confirm( 'Deseja excluir o controle?' ) ) {
			window.location = '?modulo=<?= $_REQUEST['modulo'] ?>&acao=<?= $_REQUEST['acao'] ?>&atiid=<?= $_REQUEST['atiid'] ?>&aba=<?= $_REQUEST['aba'] ?>&evento=excluir_controle&obsid='+ controle;
		}
	}

	function filtrar_restricoes( filtro ){
		if ( filtro ) {
			window.location = '?modulo=<?= $_REQUEST['modulo'] ?>&acao=<?= $_REQUEST['acao'] ?>&atiid=<?= $_REQUEST['atiid'] ?>&aba=<?= $_REQUEST['aba'] ?>';
		} else {
			window.location = '?modulo=<?= $_REQUEST['modulo'] ?>&acao=<?= $_REQUEST['acao'] ?>&atiid=<?= $_REQUEST['atiid'] ?>&aba=<?= $_REQUEST['aba'] ?>&filtro=1';
		}
	}

	function enviar_email( cpf ){
		var nome_janela = 'janela_enviar_emai_' + cpf;
		window.open(
			'/geral/envia_email.php?cpf=' + cpf,
			nome_janela,
			'width=650,height=557,scrollbars=yes,scrolling=yes,resizebled=yes'
		);
	}

</script>

<script language="javascript" type="text/javascript">
	
	function ltrim( value ){
		var re = /\s*((\S+\s*)*)/;
		return value.replace(re, "$1");
	}
	
	function rtrim( value ){
		var re = /((\s*\S+)*)\s*/;
		return value.replace(re, "$1");
	}
	
	function trim( value ){
		return ltrim(rtrim(value));
	}
</script>
<table class="tabela" bgcolor="#fbfbfb" cellspacing="0" cellpadding="10" align="center">
	<tr>
		<td>
			<?= montar_resumo_atividade( $atividade ) ?>
			<!-- NOVO CONTROLE -->
			<?php if( $permissao ): ?>
				<form method="post" name="controle">
					<input type="hidden" name="evento" value="cadastrar_controle"/>
					<table class="tabela" bgcolor="#f5f5f5" cellspacing="1" cellpadding="3" style="width: 100%;">
						<tr>
							<td align='right' class="SubTituloDireita" style="vertical-align:top; width:25%;">Restri��o:</td>
							<td>
								<textarea name="obsdescricao" id="obsdescricao" rows="10" cols="70" class="text_editor_simple"><?= $obsdescricao ?></textarea>
							</td>
						</tr>
						<tr>
							<td align='right' class="SubTituloDireita" style="vertical-align:top; width:25%;">Provid�ncia:</td>
							<td><?= campo_textarea( 'obsmedida', 'N', 'S', '', 70, 2, 250 ); ?></td>
						</tr>
						<tr style="background-color: #cccccc">
							<td align='right' style="vertical-align:top; width:25%">&nbsp;</td>
							<td><input type="button" name="botao" value="Salvar" onclick="cadastrar_controle();"/></td>
						</tr>
					</table>
				</form>
			<?php endif; ?>
			<!-- LISTA DE RESTRI��ES -->
			<?php
				$filtro = $_REQUEST['filtro'] ? ' and o.obssolucao = false ' : '';
				$sql = sprintf(
					"select
						o.obsid, o.obsdata, o.obsdescricao,
						o.obssolucao, o.obsdatasolucao, o.obsmedida,
						autor.usucpf as cpfautor, autor.usunome as nomeautor, autor.usufoneddd as dddautor, autor.usufonenum as telefoneautor, unidadeautor.unidsc as unidadeautor,
						responsavel.usucpf as cpfresponsavel, responsavel.usunome as nomeresponsavel, responsavel.usufoneddd as dddresponsavel, responsavel.usufonenum as telefoneresponsavel, unidaderesponsavel.unidsc as unidaderesponsavel
					from pde.observacaoatividade o
					left join seguranca.usuario autor on
						autor.usucpf = o.usucpf
					left join public.unidade unidadeautor on
						unidadeautor.unicod = autor.unicod
					left join seguranca.usuario responsavel on
						responsavel.usucpf = o.usucpfsolucao
					left join public.unidade unidaderesponsavel on
						unidaderesponsavel.unicod = responsavel.unicod
					where
						o.atiid = %d and o.obsstatus = 'A' %s
					order by o.obsdata desc",
					$_REQUEST['atiid'],
					$filtro
				);
				$restricoes = $db->carregar( $sql );
			?>
			<?php if( is_array( $restricoes ) ): ?>
				<label onclick="filtrar_restricoes( <?= $_REQUEST['filtro'] ?> );">
					<input type="checkbox" name="filtro" value="1" class="normal" <?= $_REQUEST['filtro'] ? 'checked="checked"' : '' ?>/>
					Exibir apenas as restri��es <b>n�o superadas</b>.
				</label>
				<?php foreach( $restricoes as $restricao ): ?>
				<form method="post" id="formulario_<?= $restricao['obsid'] ?>">
					<input type="hidden" name="evento" value="controlar_solucao"/>
					<input type="hidden" name="obsid" value="<?= $restricao['obsid'] ?>"/>
					<table id="<?= $restricao['obsid'] ?>" class='tabela' bgcolor="#f5f5f5" style="width:100%; margin-top: 15px;<?= $restricao['obssolucao'] == 't' ? 'color:#454545;' : '' ?>" cellpadding="3">
						<tbody>
							<tr style="background-color: #cccccc">
								<td align='right' style="vertical-align:top; width:25%">&nbsp;</td>
								<td align='left' style="vertical-align:top;">
									<b>Restri��o</b>
									<?php if( $restricao['obssolucao'] != 't' ): ?><img src="../imagens/restricao.png" border="0" align="absmiddle" style="margin: 0 3px 0 3px;"/><?php endif; ?>
								</td>
							</tr>
							<tr>
								<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Descri��o:</td>
								<td>
									<?= $restricao['obsdescricao'] ?>
								</td>
							</tr>
							<tr>
								<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Data:</td>
								<td><?= formata_data( $restricao['obsdata'] ); ?></td>
							</tr>
							<tr>
								<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Autor:</td>
								<td>
									<div>
										<img onclick="enviar_email( '<?= $restricao['cpfautor'] ?>' );" title="enviar e-mail" src="../imagens/email.gif" align="absmiddle" style="border:0; cursor:pointer;"/>
										<?= $restricao['nomeautor'] ?>
									</div>
									<div style="color:#959595;"><?= $restricao['unidadeautor'] ?> - Tel: (<?= $restricao['dddautor'] ?>) <?= $restricao['telefoneautor'] ?></div>
								</td>
							</tr>
							<tr>
								<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Restri��o superada?</td>
								<td>
									<?php if( $permissao ): ?>
										<label title="indica que a restri��o est� superada">
											<input type="radio" name="obssolucao" value="t" <?= $restricao['obssolucao'] == 't' ? 'checked="checked"' : '' ?>/>
											Sim
										</label>
										&nbsp;&nbsp;
										<label title="indica que a restri��o n�o est� superada">
											<input type="radio" name="obssolucao" value="f" <?= $restricao['obssolucao'] == 'f' ? 'checked="checked"' : '' ?>/>
											N�o
										</label>
									<?php else: ?>
										<?= $restricao['obssolucao'] == 't' ? 'Sim' : 'N�o' ?>
									<?php endif; ?>
								</td>
							</tr>
							<tr>
								<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Provid�ncia:</td>
								<td>
								<?php
								
								$obsmedida = $restricao["obsmedida"];
								echo campo_textarea( 'obsmedida', 'N', 'S', '', 70, 2, 250 );
								
								?>
								</td>
							</tr>
							
							<?php if( $restricao['obssolucao'] == 't' ): ?>
								<tr id="titulo_providencia_<?= $restricao['obsid'] ?>" style="background-color: #cccccc;">
									<td align='right' style="vertical-align:top; width:25%">&nbsp;</td>
									<td align='left' style="vertical-align:top;"><b>Supera��o</b></td>
								</tr>
								<tr id="datasuperacao_<?= $restricao['obsid'] ?>">
									<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Data:</td>
									<td><?= formata_data( $restricao['obsdatasolucao'] ) ?></td>
								</tr>
								<tr id="responsavel_<?= $restricao['obsid'] ?>">
									<td class="SubTituloDireita" style="vertical-align:top; width:25%;">Autor:</td>
									<td>
										<div>
											<img onclick="enviar_email( '<?= $restricao['cpfresponsavel'] ?>' );" title="enviar e-mail" src="../imagens/email.gif" align="absmiddle" style="border:0; cursor:pointer;"/>
											<?= $restricao['nomeresponsavel'] ?>
										</div>
										<div style="color:#959595;"><?= $restricao['unidaderesponsavel'] ?> - Tel: (<?= $restricao['dddresponsavel'] ?>) <?= $restricao['telefoneresponsavel'] ?></div>
									</td>
								</tr>
							<?php endif; ?>
							
							<?php if( $permissao ): ?>
								<tr style="background-color: #cccccc">
									<td align='right' style="vertical-align:top; width:25%">&nbsp;</td>
									<td>
										<input type="submit" name="botao" value="Salvar"/>
										<input type="button" name="botao" value="Excluir" onclick="excluirControle( <?= $restricao['obsid'] ?> );" />
									</td>
								</tr>
							<?php endif; ?>
						</tbody>
					</table>
				</form>
				<?php endforeach; ?>
			<?php else: ?>
				<table class='tabela' style="width:100%;" cellpadding="3">
					<tbody>
						<td style="text-align:center;padding:15px;background-color:#f5f5f5;">
							A atividade n�o possui restri��es.
						</td>
					</tbody>
				</table>
			<?php endif; ?>
		</td>
	</tr>
</table>