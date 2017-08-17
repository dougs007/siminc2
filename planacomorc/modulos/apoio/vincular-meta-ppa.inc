<?php

switch ($_REQUEST['req']){
    case 'salvar':
        $cMetaPpa = new Spo_Controller_SubUnidadeMetaPpa();
        $cMetaPpa->salvar($_REQUEST);
        die;
}

$aMetaPpa = (new Public_Model_MetaPpa())->recuperarTodos('*', ["prsano = '2018'", "mppstatus = 'A'"], 'mppcod');
$aSubUnidadeOrcamentaria = simec_preparar_array((new Public_Model_SubUnidadeOrcamentaria())->recuperarTodos("suoid as codigo, unosigla || ' - ' || suonome as descricao", ["prsano = '2018'", "suostatus = 'A'"], 'descricao'));
$aVinculos = (new Spo_Model_SubUnidadeMetaPpa())->recuperarPorExercicio($_SESSION['exercicio']);

/**
 * Cabe�alho padr�o do simec.
 * @see cabecalho.inc
 */
include APPRAIZ . "includes/cabecalho.inc";

?>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-10">
        <h2>V�ncular Metas PPA com Sub-Unidade Or�ament�ria</h2>
    </div>
</div>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">
        <div class="col-md-12">
            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5>Metas PPA</h5>
                </div>
                <div class="ibox-content">
                    <form id="formulario" name="formulario" method="post" class="form-horizontal">
                        <input type="hidden" name="req" id="req" value="salvar" />

                        <div class="table-responsive">
                            <table class="table table-striped table-bordered table-hover dataTables" >
                                <thead>
                                <tr>
                                    <th width="50%">Meta PPA</th>
                                    <th>Sub-Unidade</th>
                                </tr>
                                </thead>
                                <tbody>
                                <?php foreach($aMetaPpa as $dados){ ?>
                                    <tr>
                                        <td><?php echo $dados['mppcod'] . ' - ' . $dados['mppnome']; ?></td>
                                        <td>
                                            <?php
                                            $vinculados = !empty($aVinculos[$dados['mppid']]) ?  $aVinculos[$dados['mppid']]: [];
                                            echo $simec->select("vinculos[{$dados['mppid']}][]", null, $vinculados, $aSubUnidadeOrcamentaria, null, ['input-size'=>12]);
                                            ?>
                                        </td>
                                    </tr>
                                <?php } ?>
                                </tbody>
                            </table>
                        </div>
                        <div class="form-group">
                            <div class="text-center">
                                <input type="submit" class="btn btn-primary" name="btg" value="Salvar" />
                                <a href="planacomorc.php?modulo=principal/unidade/listapimanter&acao=A" class="btn btn-warning" id="btnVoltar" type="button">Voltar</a>
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>