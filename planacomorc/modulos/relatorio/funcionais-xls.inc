<?php

header( 'Content-Type: application/vnd.ms-excel' );
header( 'Expires: 0' );
header( 'Cache-Control: must-revalidate, post-check=0, pre-check=0' );
header( 'Content-Disposition: attachment; filename="relatorio_geral_pi' . '.xls"' );

# Colunas do relat�rio
$cabecalho = [
    'Unidade',
    'Subunidade',
    'PTRES',
    'Funcional',
    'Dota��o Custeio',
    'Planejado Custeio',
    'Dota��o Capital',
    'Planejado Capital',
    'Dota��o Total',
    'Planejado Total',
    'Provisionado',
    'Empenhado',
    'Liquidado',
    'Pago',
];

# Lista de colunas que ter�o formata��o de moeda.
$listaColunaMoeda = array(
    'ptrdotacao_capital',
    'ptrdotacao_custeio',
    'picvalorcapital',
    'picvalorcusteio',
    'provisionado',
    'empenhado',
    'liquidado',
    'pago',
);

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
        <?php if($listaFuncionais): ?>
            <tbody>
            <?php foreach($listaFuncionais as $dado): ?>
                <tr>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo $dado['unosigla']. ' (' . $dado['unocod'] . ')'; ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo $dado['suonome']. ' ('. $dado['suocod']. ')'; ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo $dado['ptres']; ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo $dado['funcional'] . ' - ' . $dado['acatitulo'] . ': ' . $dado['plodsc'] . ' (RP ' . $dado['irpcod'] . ')'; ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor($dado['ptrdotacao_custeio']); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor($dado['picvalorcusteio']); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor($dado['ptrdotacao_capital']); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor($dado['picvalorcapital']); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor(($dado['ptrdotacao_custeio'] + $dado['ptrdotacao_capital'])); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor(($dado['picvalorcusteio'] + $dado['picvalorcapital'])); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor(($dado['provisionado'])); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor(($dado['empenhado'])); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor(($dado['liquidado'])); ?>
                    </td>
                    <td style="border: 1px #e5d9c5 solid;">
                        <?php echo formata_valor(($dado['pago'])); ?>
                    </td>
                </tr>
            <?php endforeach; ?>
            </tbody>
        <?php endif; ?>
    </tbody>
</table>

<?php
die;
