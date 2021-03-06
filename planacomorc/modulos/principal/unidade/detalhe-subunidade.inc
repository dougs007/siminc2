<?php
    $dado = count($dadosPi) ? current($dadosPi) : [];
    $urlBaseCadastro = $tipoPi == 'fnc'? 'planacomorc.php?modulo=principal/unidade/cadastro_pi_fnc&acao=A': 'planacomorc.php?modulo=principal/unidade/cadastro_pi&acao=A';
    $titulo = count($dado) ? $dado['unosigla'] . ' - ' . $dado['suonome'] . ' (' . $dado['suocod'] . ')' : "PA's da Unidade";
?>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">
        <div class="col-md-12">
            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5><?= $titulo; ?></h5>
                </div>
                <div class="ibox-content">

                    <div class="row">
                        <div class="tabs-container col-lg-12">
                            <ul class="nav nav-tabs">
                                <li class="active"><a data-toggle="tab" href="#tab-pa">Lista de PA</a></li>
                                <li><a data-toggle="tab" href="#tab-nao-orcamentaria">Lista de PA N�o Or�ament�rio</a></li>
                            </ul>
                            <div class="tab-content">
                                <div id="tab-pa" class="tab-pane active">
                                    <div class="panel-body">

                                        <div class="ibox-content">
                                            <?php if(count($dadosPi)): ?>
                                                <div class="table-responsive">
                                                    <table class="table table-striped table-bordered table-hover dataTables">
                                                        <thead>
                                                            <tr class="text-center">
                                                                <th>A��es</th>
                                                                <th>Id</th>
                                                                <th>C�digo</th>
                                                                <th>T�tulo</th>
                                                                <th>RP</th>
                                                                <th>Custeio</th>
                                                                <th>Capital</th>
                                                                <th>Provisionado</th>
                                                                <th>Empenhado</th>
                                                                <th>Liquidado</th>
                                                                <th>Pago</th>
                                                            </tr>
                                                        </thead>
                                                        <tbody>
                                                            <?php
                                                            $total['custeio'] = $total['capital'] = $total['empenhado'] = $total['pago'] = $total['liquidado'] = 0;
                                                            foreach($dadosPi as $dado):
                                                                $total['custeio'] += $dado['picvalorcusteio'];
                                                                $total['capital'] += $dado['picvalorcapital'];
                                                                $total['autorizado'] += $dado['autorizado'];
                                                                $total['empenhado'] += $dado['empenhado'];
                                                                $total['pago'] += $dado['pago'];
                                                                $total['liquidado'] += $dado['liquidado'];
                                                                ?>
                                                                <tr>
                                                                    <td class="text-center">
                                                                        <a href="<?php echo $urlBaseCadastro; ?>&pliid=<?php echo $dado['pliid']; ?>" class="btn btn-primary btn-sm glyphicon glyphicon-pencil"></a>
                                                                    </td>
                                                                    <td>
                                                                        <a href="#" title="Exibir detalhes do Plano Interno(Espelho)" class="a_espelho" data-pi="<?php echo $dado['pliid']; ?>" >
                                                                            <?php echo $dado['pliid']; ?>
                                                                        </a>
                                                                    </td>
                                                                    <td>
                                                                        <a href="#" title="Exibir detalhes do Plano Interno(Espelho)" class="a_espelho" data-pi="<?php echo $dado['pliid']; ?>" >
                                                                            <?php echo $dado['plicod']; ?>
                                                                        </a>
                                                                    </td>
                                                                    <td>
                                                                        <a href="#" title="Exibir detalhes do Plano Interno(Espelho)" class="a_espelho" data-pi="<?php echo $dado['pliid']; ?>" >
                                                                            <?php echo $dado['plititulo']; ?>
                                                                        </a>
                                                                    </td>
                                                                    <td class="text-center"><?php echo $dado['irpcod']; ?></td>
                                                                    <td class="text-right"><?php echo number_format($dado['picvalorcusteio'], 0, ',', '.'); ?></td>
                                                                    <td class="text-right"><?php echo number_format($dado['picvalorcapital'], 0, ',', '.'); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['autorizado'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['empenhado'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['liquidado'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['pago'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                </tr>
                                                            <?php endforeach; ?>
                                                        </tbody>
                                                        <tfoot>
                                                            <tr>
                                                                <th colspan="5">TOTAL</th>
                                                                <th class="text-right"><?php echo number_format($total['custeio'], 0, ',', '.'); ?></th>
                                                                <th class="text-right"><?php echo number_format($total['capital'], 0, ',', '.'); ?></th>
                                                                <th class="text-right"><?php echo marcarVermelhoValorSuperior($total['autorizado'], $total['custeio']+ $total['capital']); ?></th>
                                                                <th class="text-right"><?php echo marcarVermelhoValorSuperior($total['empenhado'], $total['custeio']+ $total['capital']); ?></th>
                                                                <th class="text-right"><?php echo marcarVermelhoValorSuperior($total['liquidado'], $total['custeio']+ $total['capital']); ?></th>
                                                                <th class="text-right"><?php echo marcarVermelhoValorSuperior($total['pago'], $total['custeio']+ $total['capital']); ?></th>
                                                            </tr>
                                                        </tfoot>
                                                    </table>
                                                </div>
                                            <?php else:
                                                echo '<div class="alert alert-danger">N�o h� PA vinculado a esta Unidade</div>';
                                            endif; ?>
                                        </div>
                                        <div class="ibox-title">
                                            <h5>PA's Delegados</h5>
                                        </div>
                                        <div class="ibox-content">
                                            <?php if(count($dadosDelegado)): ?>
                                                <div class="table-responsive">
                                                    <table class="table table-bordered table-hover " >
                                                        <thead>
                                                            <tr class="text-center">
                                                                <th>Id</th>
                                                                <th>C�digo</th>
                                                                <th>T�tulo</th>
                                                                <th>Custeio</th>
                                                                <th>Capital</th>
                                                                <th>Provisionado</th>
                                                                <th>Empenhado</th>
                                                                <th>Liquidado</th>
                                                                <th>Pago</th>
                                                            </tr>
                                                        </thead>
                                                        <tbody>
                                                            <?php foreach($dadosDelegado as $dado): ?>
                                                                <tr>
                                                                    <td><?php echo $dado['pliid']; ?></td>
                                                                    <td><?php echo $dado['plicod']; ?></td>
                                                                    <td><?php echo $dado['plititulo']; ?></td>
                                                                    <td class="text-right"><?php echo number_format2($dado['picvalorcusteio'], 0, ',', '.'); ?></td>
                                                                    <td class="text-right"><?php echo number_format2($dado['picvalorcapital'], 0, ',', '.'); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['autorizado'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['empenhado'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['liquidado'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                    <td class="text-right"><?php echo marcarVermelhoValorSuperior($dado['pago'], $dado['picvalorcusteio']+ $dado['picvalorcapital']); ?></td>
                                                                </tr>
                                                            <?php endforeach; ?>
                                                        </tbody>
                                                    </table>
                                                </div>
                                            <?php else: 
                                                echo '<div class="alert alert-danger">N�o h� PA delegado a esta Unidade</div>';
                                            endif;
                                            ?>
                                        </div>

                                    </div>
                                </div>

                                <div id="tab-nao-orcamentaria" class="tab-pane">
                                    <div class="panel-body">

                                        <div class="ibox-content">
                                            <?php if(count($dadosPiNaoOrcamentario)): ?>
                                                <div class="table-responsive">
                                                    <table class="table table-bordered table-striped table-hover dataTables">
                                                        <thead>
                                                            <tr class="text-center">
                                                                <th>A��es</th>
                                                                <th>Id</th>
                                                                <th>T�tulo</th>
                                                                <th>Quantidade</th>
                                                                <th>Produto</th>
                                                            </tr>
                                                        </thead>
                                                        <tbody>
                                                        <?php
                                                        $total['custeio'] = $total['capital'] = $total['empenhado'] = $total['pago'] = $total['liquidado'] = 0;
                                                        foreach($dadosPiNaoOrcamentario as $dado):
                                                            $total['custeio'] += $dado['picvalorcusteio'];
                                                            $total['capital'] += $dado['picvalorcapital'];
                                                            $total['autorizado'] += $dado['autorizado'];
                                                            $total['empenhado'] += $dado['empenhado'];
                                                            $total['pago'] += $dado['pago'];
                                                            $total['liquidado'] += $dado['liquidado'];
                                                            ?>
                                                            <tr>
                                                                <td class="text-center" width="5%">
                                                                    <a href="<?php echo $urlBaseCadastro; ?>&pliid=<?php echo $dado['pliid']; ?>" class="btn btn-primary btn-sm glyphicon glyphicon-pencil"></a>
                                                                </td>
                                                                <td>
                                                                    <a href="#" title="Exibir detalhes do Plano Interno(Espelho)" class="a_espelho" data-pi="<?php echo $dado['pliid']; ?>" >
                                                                        <?php echo $dado['pliid']; ?>
                                                                    </a>
                                                                </td>
                                                                <td>
                                                                    <a href="#" title="Exibir detalhes do Plano Interno(Espelho)" class="a_espelho" data-pi="<?php echo $dado['pliid']; ?>" >
                                                                        <?php echo $dado['plititulo']; ?>
                                                                    </a>
                                                                </td>
                                                                <td class="text-center"><?php echo $dado['picquantidade']; ?></td>
                                                                <td class="text-center"><?php echo $dado['pprnome']; ?></td>
                                                            </tr>
                                                        <?php endforeach; ?>
                                                        </tbody>
                                                    </table>
                                                </div>
                                            <?php else:
                                                echo '<div class="alert alert-danger">N�o h� PA N�o Or�ament�rio vinculado a esta Unidade</div>';
                                            endif; ?>
                                        </div>
                                        <div class="ibox-title">
                                            <h5>PA's Delegados</h5>
                                        </div>
                                        <div class="ibox-content">
                                            <?php if(count($dadosDelegadoNaoOrcamentario)): ?>
                                                <div class="table-responsive">
                                                    <table class="table table-bordered table-hover " >
                                                        <thead>
                                                        <tr class="text-center">
                                                            <th>Id</th>
                                                            <th>T�tulo</th>
                                                            <th class="text-center">Quantidade</th>
                                                            <th>Produto</th>
                                                        </tr>
                                                        </thead>
                                                        <tbody>
                                                        <?php foreach($dadosDelegadoNaoOrcamentario as $delegado): ?>
                                                            <tr>
                                                                <td><?= $delegado['pliid']; ?></td>
                                                                <td><?= $delegado['plititulo']; ?></td>
                                                                <td class="text-center"><?= $delegado['picquantidade']; ?></td>
                                                                <td><?= $delegado['pprnome']; ?></td>
                                                            </tr>
                                                        <?php endforeach; ?>
                                                        </tbody>
                                                    </table>
                                                </div>
                                            <?php else:
                                                echo '<div class="alert alert-danger">N�o h� PA N�o Or�ament�rio delegado a esta Unidade</div>';
                                            endif; ?>
                                        </div>

                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
<script>
    $(document).ready(function(){

        $('.dataTables').DataTable({
            searching: false,
            bPaginate: true,
            responsive: true,
            dom: '<"html5buttons"B>lTfgitp',
            "language": {
                "url": "/zimec/public/temas/simec/js/plugins/dataTables/Portuguese-Brasil.json"
            }
        });

    });
</script>