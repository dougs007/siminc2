<?php

$Enquadramento = (new Monitora_Model_PiEnquadramentoDespesa())->recuperarTodosRp( (object) array('exercicio' => $_SESSION['exercicio']));

include APPRAIZ . "includes/cabecalho.inc";
?>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-10">
        <h2><?php echo $titulo_modulo; ?></h2>
    </div>
</div>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">
        <div class="col-md-12">
            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5>Dados Gerais</h5>
                </div>
                <div class="ibox-content">
                    <a class="btn-small btn btn-success" href="?modulo=apoio/enquadramento_despesa_form&acao=A">
                        <span class="glyphicon glyphicon-plus"></span>
                        Novo
                    </a>
                    <div class="table-responsive">
                        <table class="table table-striped table-bordered table-hover dataTables" >
                            <thead>
                            <tr class="text-center">
                                <th width="5%">A��o</th>
                                <th>C�digo</th>
                                <th>Descri��o</th>
                                <th>Reduzido</th>
                                <th>Resultado Prim�rio</th>

                            </tr>
                            </thead>
                            <tbody>
                            <?php
                                if($Enquadramento):
                                    foreach($Enquadramento as $dados): ?>
                                        <tr>
                                            <td class="text-center">
                                                <a title="Alterar" href="planacomorc.php?modulo=apoio/enquadramento_despesa_form&acao=A&eqdid=<?php echo $dados['eqdid']; ?>"><i class="btn btn-primary btn-sm glyphicon glyphicon-pencil"></i></a>
                                            </td>
                                            <td class="text-center"><?php echo $dados['eqdcod']; ?></td>
                                            <td><?php echo $dados['eqddsc']; ?></td>
                                            <td class="text-center"><?php echo $dados['eqdstreduzido'] == 'S' ? 'Sim' : 'N�o'; ?></td>
                                            <td class="text-center"><?php echo $dados['lista_rp']; ?></td>
                                        </tr>
                                    <?php endforeach; ?>
                                <?php endif; ?>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
