<?php

    # Incluindo arquivo do M�dulo que possui a implementa��o da busca
    include_once APPRAIZ . "monitora/classes/Pi_PlanoInterno.class.inc";
    $modelPlanoInterno = new Pi_PlanoInterno();

    # Incluindo o arquivo da classe de relatorio
    include_once APPRAIZ . 'includes/relatorio-agrupador/tabela.php';

    # Busca SQL com filtros pra realizar a consulta
    $dto = (object)$_POST['filtro'];
    $dto->fundo = TRUE;
    $dto->exercicio = $_POST['filtro']['prsano'];
    $listaRelatorio = $modelPlanoInterno->listarRelatorioGeralPi($dto);

    # Colunas do relatorio
    $listaTodasColunas = montarColunasRelatorioPI();
    $listaColunasSelecionadas = $_POST['coluna'];
    $listaColunaFormatoMoeda = montarColunasFormatoMoeda();

    $relatorio = new relatorio_agrupador_tabela();
    $tabela = $relatorio->setListaTodasColunas($listaTodasColunas)
        ->setListaColunasSelecionadas($listaColunasSelecionadas)
        ->setListaColunaFormatoMoeda($listaColunaFormatoMoeda)
        ->setListaRelatorio($listaRelatorio)
        ->montarTabela()
        ->getTabela();

    # Gera o XLS do relat�rio
    if ($_REQUEST['req'] == 'xls') {
        echo $tabela;

        header('Content-Type: application/vnd.ms-excel');
        header('Expires: 0');
        header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
        header('Content-Disposition: attachment; filename="relatorio_gerencial_pi_fnc.xls"');
        die();
    }

    include APPRAIZ. "includes/cabecalho_bootstrap_v3_popup.inc";
?>

<div class="row" style="margin-top: 5px;">
    <div class="col-md-12">
        <div class="ibox float-e-margins">
            <div class="ibox-title">
                <h5>Relat�rio Geral de PI-FNC</h5>
            </div>
        </div>
        <div class="ibox-content">
            <div class="table-responsive" style="overflow-y: auto;">

                <?= $tabela ?>

            </div>
        </div>
    </div>
</div>