<?php

include_once APPRAIZ. 'monitora/classes/Pi_PlanoInterno.class.inc';

$cabecalho = [
    'ID Planejamento', 'Situa��o', 'C�digo', 'C�digo da UO', 'UO', 'C�digo da Unidade', 'Unidade', 'Unidade Delegada', 'Unidade Delegada', 'Enquadramento', 'RP - Resultado Prim�rio',
    'Item de Manuten��o', 'Subitem de Manuten��o', 'C�digo do Programa', 'Programa', 'C�digo do Objetivo', 'Objetivo', 'C�digo da Iniciativa', 'Iniciativa', 'C�digo da A��o', 'A��o', 'C�digo do Localizador',
    'Localizador', 'C�digo do PO', 'Plano Or�ament�rio', 'PTRES', '�rea', 'Meta PNC', 'Meta', 'T�tulo', 'Descri��o', 'Segmento Cultural', 'Tipo de Instrumento / Modalidade de Pactua��o',
    'Emenda parlamentar', 'Forma de execu��o - Edital', 'Localiza��o da a��o', 'Pa�s', 'Unidade Federativa', 'Munic�pio',
    'Meta da Unidade', 'Objetivo Estrat�gico', 'Dimens�o Estrat�gica', 'Meta Estrat�gica', 'Quantidade da Meta Unidade', 'Priorit�rio',
    'Respons�vel', 'TED', 'Edital', 'Previs�o Edital',
    'Conv�nio', 'SNIIC', 'Processo', 'PRONAC', 'Produto', 'Unidade de Medida', 'Quantidade', 'Valor Total', 'Valor Total Custeio', 'Valor Total Capital',

    'Cronograma F�sico<br />Capital Janeiro', 'Cronograma F�sico<br />Capital Fevereivo', 'Cronograma F�sico<br />Capital Mar�o', 'Cronograma F�sico<br />Capital Abril',
    'Cronograma F�sico<br />Capital Maio', 'Cronograma F�sico<br />Capital Junho', 'Cronograma F�sico<br />Capital Julho', 'Cronograma F�sico<br />Capital Agosto',
    'Cronograma F�sico<br />Capital Setembro', 'Cronograma F�sico<br />Capital Outubro', 'Cronograma F�sico<br />Capital Novembro', 'Cronograma F�sico<br />Capital Dezembro',

    'Cronograma Financeiro<br />Capital Janeiro', 'Cronograma Financeiro<br />Capital Fevereivo', 'Cronograma Financeiro<br />Capital Mar�o', 'Cronograma Financeiro<br />Capital Abril',
    'Cronograma Financeiro<br />Capital Maio', 'Cronograma Financeiro<br />Capital Junho', 'Cronograma Financeiro<br />Capital Julho', 'Cronograma Financeiro<br />Capital Agosto',
    'Cronograma Financeiro<br />Capital Setembro', 'Cronograma Financeiro<br />Capital Outubro', 'Cronograma Financeiro<br />Capital Novembro', 'Cronograma Financeiro<br />Capital Dezembro',

    'Cronograma Financeiro<br />Custeio Janeiro', 'Cronograma Financeiro<br />Custeio Fevereivo', 'Cronograma Financeiro<br />Custeio Mar�o', 'Cronograma Financeiro<br />Custeio Abril',
    'Cronograma Financeiro<br />Custeio Maio', 'Cronograma Financeiro<br />Custeio Junho', 'Cronograma Financeiro<br />Custeio Julho', 'Cronograma Financeiro<br />Custeio Agosto',
    'Cronograma Financeiro<br />Custeio Setembro', 'Cronograma Financeiro<br />Custeio Outubro', 'Cronograma Financeiro<br />Custeio Novembro', 'Cronograma Financeiro<br />Custeio Dezembro',

    'Cronograma Or�ament�rio<br />Capital Janeiro', 'Cronograma Or�ament�rio<br />Capital Fevereivo', 'Cronograma Or�ament�rio<br />Capital Mar�o', 'Cronograma Or�ament�rio<br />Capital Abril',
    'Cronograma Or�ament�rio<br />Capital Maio', 'Cronograma Or�ament�rio<br />Capital Junho', 'Cronograma Or�ament�rio<br />Capital Julho', 'Cronograma Or�ament�rio<br />Capital Agosto',
    'Cronograma Or�ament�rio<br />Capital Setembro', 'Cronograma Or�ament�rio<br />Capital Outubro', 'Cronograma Or�ament�rio<br />Capital Novembro', 'Cronograma Or�ament�rio<br />Capital Dezembro',

    'Cronograma Or�ament�rio<br />Custeio Janeiro', 'Cronograma Or�ament�rio<br />Custeio Fevereivo', 'Cronograma Or�ament�rio<br />Custeio Mar�o', 'Cronograma Or�ament�rio<br />Custeio Abril',
    'Cronograma Or�ament�rio<br />Custeio Maio', 'Cronograma Or�ament�rio<br />Custeio Junho', 'Cronograma Or�ament�rio<br />Custeio Julho', 'Cronograma Or�ament�rio<br />Custeio Agosto',
    'Cronograma Or�ament�rio<br />Custeio Setembro', 'Cronograma Or�ament�rio<br />Custeio Outubro', 'Cronograma Or�ament�rio<br />Custeio Novembro', 'Cronograma Or�ament�rio<br />Custeio Dezembro',

    'Valor Provisionado', 'Valor Empenhado', 'Valor Liquidado', 'Valor Pago',
    
    'Executado', 'An�lise Situacional', 'Classifica��o', 'Medidas a serem adotadas', 'Detalhamento das provid�ncias a serem adotadas'
];

# Lista de colunas que ter�o formata��o de moeda.
$listaColunaMoeda = array(
    'valortotal',
    'picvalorcusteio',
    'picvalorcapital',
    'fin_capital_1',
    'fin_capital_2',
    'fin_capital_3',
    'fin_capital_4',
    'fin_capital_5',
    'fin_capital_6',
    'fin_capital_7',
    'fin_capital_8',
    'fin_capital_9',
    'fin_capital_10',
    'fin_capital_11',
    'fin_capital_12',
    'fin_custeio_1',
    'fin_custeio_2',
    'fin_custeio_3',
    'fin_custeio_4',
    'fin_custeio_5',
    'fin_custeio_6',
    'fin_custeio_7',
    'fin_custeio_8',
    'fin_custeio_9',
    'fin_custeio_10',
    'fin_custeio_11',
    'fin_custeio_12',
    'orc_capital_1',
    'orc_capital_2',
    'orc_capital_3',
    'orc_capital_4',
    'orc_capital_5',
    'orc_capital_6',
    'orc_capital_7',
    'orc_capital_8',
    'orc_capital_9',
    'orc_capital_10',
    'orc_capital_11',
    'orc_capital_12',
    'orc_custeio_1',
    'orc_custeio_2',
    'orc_custeio_3',
    'orc_custeio_4',
    'orc_custeio_5',
    'orc_custeio_6',
    'orc_custeio_7',
    'orc_custeio_8',
    'orc_custeio_9',
    'orc_custeio_10',
    'orc_custeio_11',
    'orc_custeio_12',
    'vlrautorizado',
    'vlrempenhado',
    'vlrliquidado',
    'vlrpago'
);

# Verifica se o usu�rio tem vinculo de Sub-Unidades no seu Perfil
$listaSubunidade = buscarSubUnidadeUsuario((object)array('usucpf' => $_SESSION['usucpf']));

$dto = (object) array(
    'exercicio' => $_SESSION['exercicio'],
    'listaSubunidade' => $listaSubunidade
);
# Filtro do FNC
if($_REQUEST['fundo'] === 't'){
    $dto->fundo = TRUE;
}
else if($_REQUEST['fundo'] === 'f'){
    $dto->fundo = FALSE;
}
$dados = (new Pi_PlanoInterno())->listarRelatorioGeralPi($dto);

?>

<table width="100%" cellspacing="0">
    <thead>
        <tr>
            <?php foreach($cabecalho as $coluna){ ?>
                <th style="border: 1px #e5d9c5 solid; background-color: #f4f4f4"><?php echo $coluna; ?></th>
            <?php } ?>
        </tr>
    </thead>
    <tbody>
        <?php foreach($dados as $dado){ ?>
            <tr>
                <?php foreach($dado as $coluna => $valor){ ?>
                    <td style="border: 1px #e5d9c5 solid;"><?php echo in_array($coluna, $listaColunaMoeda)? formata_valor($valor): $valor; ?></td>
                <?php } ?>
            </tr>
        <?php } ?>
    </tbody>
</table>

<?php

header( 'Content-Type: application/vnd.ms-excel' );
header( 'Expires: 0' );
header( 'Cache-Control: must-revalidate, post-check=0, pre-check=0' );
header( 'Content-Disposition: attachment; filename="relatorio_geral_pi' .($_REQUEST['fundo'] === 't'? '_fnc': NULL). '.xls"' );
die;
