<?php

$listaHistorico = (new Planacomorc_Model_HistoricoPi())->recuperarListagem($_REQUEST['pliid']);

?>

<div class="row">
    <div class="col-md-12">
        <div class="ibox float-e-margins">
            <div class="table-responsive">
                <?php if ($listaHistorico) { ?>
                    <table class="table table-bordered table-hover">
                        <thead>
                        <tr class="text-center">
                            <th>Data</th>
                            <th>Usu�rio</th>
                            <th>E-mail</th>
                            <th>Telefone</th>
                            <th>C�digo Anterior</th>
                            <th>C�digo Novo</th>
                        </tr>
                        </thead>
                        <tbody>
                        <?php foreach ($listaHistorico as $dados) : ?>
                            <tr>
                                <td><?= $dados['hisdata'] ?></td>
                                <td><?= $dados['usunome'] ?></td>
                                <td><?= $dados['usuemail'] ?></td>
                                <td><?= $dados['telefone'] ?></td>
                                <td><?= $dados['hpidscantigo'] ?></td>
                                <td><?= $dados['hpidscnovo'] ?></td>
                            </tr>
                        <?php endforeach; ?>
                        </tbody>
                    </table>
                <?php } else { ?>
                    <div class="alert alert-danger">N�o h� Hist�rico de altera��es nesse PA</div>
                <?php } ?>
            </div>
        </div>
    </div>
</div>