<?php
    $mItens = (new Planacomorc_Model_ManutencaoItem)->recuperarLista();
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
                    <a class="btn-small btn btn-success" href="?modulo=apoio/item-manutencao-form&acao=A">
                        <span class="glyphicon glyphicon-plus"></span>
                        Novo
                    </a>
                    <div class="table-responsive">
                        <table class="table table-striped table-bordered table-hover dataTables">
                            <thead>
                            <tr class="text-center">
                                <th>A��o</th>
                                <th>Nome</th>
                                <th>Descri��o</th>
                                <th>Enquadramento</th>
                            </tr>
                            </thead>
                            <tbody>
							<?php if ($mItens):
								foreach ($mItens as $item): ?>
                                    <tr>
                                        <td class="text-center">
                                            <a title="Alterar" href="planacomorc.php?modulo=apoio/item-manutencao-form&acao=A&maiid=<?= $item['codigo']; ?>"><i class="btn btn-primary btn-sm glyphicon glyphicon-pencil"></i></a>
                                        </td>
                                        <td><?= $item['nome']; ?></td>
                                        <td><?= $item['descricao']; ?></td>
                                        <td><?= $item['enquadramento']; ?></td>
                                    </tr>
								<?php endforeach;
							    endif;
                            ?>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
