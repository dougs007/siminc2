<?php
/**
 * Popup de defini��o de respons�vel para a��o e PO.
 *
 * @package SiMEC
 * @subpackage planejamento-acompanhamento-orcamentario
 *
 * @version $Id: popupresponsavel.inc 89154 2014-10-24 20:12:21Z maykelbraz $
 */
?>
<?php if ('carregarUsuarios' == $_POST['requisicao']): ?>
<div class="col-md-12">
    <form class="form-horizontal" id="form-responsavel" method="POST" role="form">
        <input type="hidden" name="rldid" value="<?php echo $_POST['rldid']; ?>" />
        <input type="hidden" name="requisicao" value="salvarResponsavel" />
        <div class="form-group row">
            <label class="control-label col-md-2" for="usucpf">Respons�vel: </label>
            <div class="col-md-10">
                <?php
                $sql = <<<DML
SELECT usu.usucpf AS codigo,
       usu.usucpf || ' - ' || usu.usunome AS descricao
  FROM seguranca.perfilusuario pfu
    LEFT JOIN seguranca.usuario usu USING(usucpf)
  WHERE pfu.pflcod = %d
DML;
                $stmt = sprintf($sql, PFL_RELATORIO_TCU);
                inputCombo('novo_usucpf', $stmt, $_POST['usucpf'], 'usucpf');
                ?>
            </div>
        </div>
    </form>
</div>
<script type="text/javascript" lang="JavaScript">
$('#usucpf').chosen();
$('#usucpf_chosen').css('width', '100%');
</script>
<?php else: ?>
<div class="modal fade" id="modal-alterar-responsavel">
  <div class="modal-dialog" style="width:60%">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal">
            <span aria-hidden="true">&times;</span>
            <span class="sr-only">Fechar</span>
        </button>
        <h4 class="modal-title">Altera��o de Respons�vel</h4>
      </div>
      <div class="modal-body"></div>
      <div class="modal-footer">
        <button type="button" class="btn btn-danger" data-dismiss="modal">
            <span class="glyphicon glyphicon-remove"></span> Cancelar</button>
        <button type="button" class="btn btn-primary" id="salvar-responsavel">
            <span class="glyphicon glyphicon-ok"></span> Salvar
        </button>
      </div>
    </div>
  </div>
</div>
<?php endif;
