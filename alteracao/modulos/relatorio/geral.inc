<?php

    $cabecalho = [
        'ID Pedido',
        'C�digo da UO',
        'Sigla da UO',
        'Nome da UO',
        'C�digo da Unidade',
        'Sigla da Unidade',
        'Nome da Unidade',
        'T�tulo',
        'Tipo',
        'Situa��o',
        'Janela',
        'Data de Cadastro',
        'Total Cancelado',
        'Total Suplementado',
        'Identificador do PI',
        'Funcional do PI',
        'C�digo PI',
        'T�tulo do PI',
        'Produto do PI',
        'Valor Custeio',
        'Valor Capital',
        'F�sico',
        'Suplementar Custeio',
        'Suplementar Capital',
        'Suplementar F�sico',
        'Cancelar Custeio',
        'Cancelar Capital',
        'Cancelar F�sico',
        'Suplementar por Excesso Custeio',
        'Suplementar por Excesso Capital',
        'Suplementar por Excesso F�sico',
        'Suplementar por Super�vit Custeio',
        'Suplementar por Super�vit Capital',
        'Suplementar por Super�vit F�sico',
        'Resultado Prov�vel Custeio',
        'Resultado Prov�vel Capital',
        'Resultado Prov�vel F�sico',
        'LOA Funcional',
        'LOA Categoria',
        'LOA GND',
        'LOA Modalidade de Aplica��o',
        'LOA Fonte',
        'LOA IDOC',
        'LOA IDUSO',
        'LOA RP',
        'LOA Suplementar',
        'LOA Cancelado',
        'LOA Suplementar por excesso',
        'LOA Suplementar por Super�vit',
        'Justificativa Necessidade de Altera��o',
        'Justificativa Causa da Demanda',
        'Justificativa formas de financiamento de Cr�dito e adequa��o da proposta � meta fiscal e ao limite de gastos',
        'Justificativa Verifica��o das fontes, dos Identificadores de uso - Iduso e dos identificadores de Resultado Prim�rio - RP',
        'Justificativa Medida Provis�ria',
        'Justificativa Legisla��o Espec�fica',
        'Justificativa Outras Informa��es'
    ];

    # Lista de colunas que ter�o formata��o de moeda.
    $listaColunaMoeda = array(
        'cancelado',
        'suplementado',
        
        'vlcusteio',
        'vlcapital',
        'vlfisico',
        'vlsuplementarcusteio',
        'vlsuplementarcapital',
        'vlsuplementarfisico',
        'vlcancelarcusteio',
        'vlcancelarcapital',
        'vlcancelarfisico',
        'vlsuplementarexcessocusteio',
        'vlsuplementarexcessocapital',
        'vlsuplementarexcessofisico',
        'vlsuplementarsuperavitcusteio',
        'vlsuplementarsuperavitcapital',
        'vlsuplementarsuperavitfisico',
        'vldotacaocusteio',
        'vldotacaocapital',
        'vldotacaofisico',
        
        'vlsuplementar',
        'vlcancelado',
        'vlsuplementarexcesso',
        'vlsuplementarsuperavit'
    );
    
    $listaPerfil = pegaPerfilGeral();
    $listaSubUnidadeUsuario = buscarSubUnidadeUsuario((object) array('usucpf' => $_SESSION['usucpf']));
    $parametro = array('pedano' => $_SESSION['exercicio']);
    if(in_array(PFL_SUBUNIDADE, $listaPerfil) && $listaSubUnidadeUsuario){
        if($listaSubUnidadeUsuario){
            $parametro['suocod'] = $listaSubUnidadeUsuario;
        }
    }
    $sql = montarSqlRelatorioGeralAlteracao((object) $parametro);
    $lista = $db->carregar($sql);
//ver($sql, $lista, d);
?>

<table width="100%" cellspacing="0">
    <thead>
        <tr>
            <?php foreach($cabecalho as $coluna){ ?>
                <th style="border: 1px #e5d9c5 solid; background-color: #f4f4f4"><?php echo $coluna; ?></th>
            <?php } ?>
        </tr>
    </thead>
    <?php if($lista): ?>
    <tbody>
        <?php foreach($lista as $dado){ ?>
            <tr>
                <?php foreach($dado as $coluna => $valor){ ?>
                    <td style="border: 1px #e5d9c5 solid;"><?php echo in_array($coluna, $listaColunaMoeda)? formata_valor($valor): $valor; ?></td>
                <?php } ?>
            </tr>
        <?php } ?>
    </tbody>
    <?php endif; ?>
</table>

<?php
    header( 'Content-Type: application/vnd.ms-excel' );
    header( 'Expires: 0' );
    header( 'Cache-Control: must-revalidate, post-check=0, pre-check=0' );
    header( 'Content-Disposition: attachment; filename="relatorio_geral_pedido_de_alteracao' . '.xls"' );
    die;
