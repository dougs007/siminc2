<?php

$aProponente = (new Emendas_Model_Proponente)->buscarTodos((object)array());

include APPRAIZ . "includes/cabecalho.inc";

?>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-12">
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
                    <a class="btn-small btn btn-success "href="?modulo=apoio/proponente_form&acao=A">
                        <span class="glyphicon glyphicon-plus"></span>
                        Novo
                    </a>

                    <div class="table-responsive">
                        <table class="table table-striped table-bordered table-hover dataTables" >
                            <thead>
                            <tr class="text-center">
                                <th width="5%">A��o</th>
                                <th>Tipo</th>
                                <th>Nome</th>
                                <th>CNPJ</th>
                                <th>Telefone</th>
                                <th>E-mail</th>
                            </tr>
                            </thead>
                            <tbody>
                            <?php foreach($aProponente as $dados){ ?>
                                <tr>
                                    <td class="text-center">
                                        <a title="Alterar" href="?modulo=apoio/proponente_form&acao=A&proid=<?php echo $dados['proid']; ?>"><i class="btn btn-primary btn-sm glyphicon glyphicon-pencil"></i></a>
                                    </td>
                                    <td><?php echo $dados['tipo']; ?></td>
                                    <td><?php echo $dados['pronome']; ?></td>
                                    <td><?php echo formatar_cnpj($dados['procnpj']); ?></td>
                                    <td class="maskTelefone"><?php echo formata_fone_fax($dados['protelefone']); ?></td>
                                    <td><?php echo $dados['proemail']; ?></td>
                                </tr>
                            <?php } ?>        
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

