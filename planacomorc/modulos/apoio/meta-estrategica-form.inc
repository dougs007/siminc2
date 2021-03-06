<?php

$cMetaEstrategica = new Planacomorc_Controller_MetaEstrategica();
$mMetaEstrategica = new Planacomorc_Model_MetaEstrategica($_REQUEST['meeid']);

switch ($_REQUEST['req']) {
    case 'salvar':
        $cMetaEstrategica->salvar($_REQUEST);
        break;
    case 'excluir':
        $cMetaEstrategica->excluir($_REQUEST['meeid']);
        break;
}

include APPRAIZ . "includes/cabecalho.inc";
?>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-10">
        <h2><?= $titulo_modulo; ?></h2>
    </div>
</div>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">
        <div class="col-md-12">
            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5>Meta Estratégica</h5>
                </div>
                <div class="ibox-content">
                    <form id="formulario" name="formulario" method="post" class="form-horizontal">
                        <input type="hidden" name="req" id="req" value="salvar" />
                        <input name="meeid" id="meeid" type="hidden" value="<?= $mMetaEstrategica->meeid; ?>">
                        <?= $simec->textarea('meenome', 'Nome', $mMetaEstrategica->meenome, ['required','maxlength' => 1000, 'cols' => 50, 'rows' => 6]); ?>
                        <div class="form-group">
                            <div class="text-center">
                                <button class="btn btn-primary" type="submit" id="btn-salvar"><i class="fa fa-check"></i>&nbsp;Salvar</button>
                                <a href="?modulo=apoio/meta-estrategica&acao=A" class="btn btn-warning" id="btn-voltar" type="button"><i class="fa fa-arrow-left"></i>&nbsp;Voltar</a>
                                <?php if($mMetaEstrategica->meeid){ ?>
                                    <a href="?modulo=apoio/meta-estrategica-form&acao=A&req=excluir&meeid=<?php echo $mMetaEstrategica->meeid; ?>" class="btn btn-danger link-excluir" id="btn-excluir" type="button"><i class="fa fa-close"></i>&nbsp;Excluir</a>
                                <?php } ?>
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>
