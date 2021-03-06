<?php

require_once APPRAIZ. 'proposta/classes/model/PrePlanoInterno.inc';

$listaSubUnidadeUsuario = buscarSubUnidadeUsuario((object) array('usucpf' => $_SESSION['usucpf']));
$listaPrePi = (new Proposta_Model_PrePlanoInterno)->recuperarListagem((object) array(
    'exercicio' => $_SESSION['exercicio'],
    'listaSubUnidadeUsuario' => $listaSubUnidadeUsuario
), $filtroprepi);

/**
 * Cabe�alho padr�o do sistema.
 * @see cabecalho.inc
 */
include APPRAIZ . "includes/cabecalho.inc";
?>

<div class="ibox float-e-margins">
    <div class="ibox-title">
        <h5>Listagem de Pr�-PI do m�dulo Proposta Or�ament�rias</h5>
    </div>
    <div class="ibox-content">

        <div class="table-responsive">
            <table class="table table-striped table-bordered table-hover dataTables-example" >
                <thead>
                <tr>
                    <th>A��es</th>
                    <th>Funcional</th>
                    <th>T�tulo</th>
                    <th>Unidade</th>
                    <th>Enq. Despesa</th>
                    <th>Situa��o</th>
                    <th>Qtd. F�sica</th>
                    <th>Vl. Custeio</th>
                    <th>Vl. Capital</th>
                    <th>Vl. Total</th>
                </tr>
                </thead>
                <tbody>
                    <?php
                    if($listaPrePi):
                        foreach($listaPrePi as $prepi): ?>
                            <tr>
                                <td>
                                    <?php if(!array_intersect($perfis, [PFL_CONSULTA, PFL_CONSULTA_UNIDADE])){ ?>
                                        <a href="planacomorc.php?modulo=principal/unidade/cadastro_pi&acao=A&replicarProposta=<?php echo $prepi['pliid']; ?>" title="Criar PI">
                                            <span class="btn btn-primary btn-sm fa fa-plus-circle"></span>
                                        </a>
                                    <?php } ?>
                                </td>
                                <td><?php echo $prepi['funcional']; ?></td>
                                <td><?php echo $prepi['plititulo']; ?></td>
                                <td><?php echo $prepi['subunidade']; ?></td>
                                <td><?php echo $prepi['eqddsc']; ?></td>
                                <td><?php echo $prepi['esddsc']; ?></td>
                                <td><?php echo $prepi['pliquantidade']; ?></td>
                                <td><?php echo number_format($prepi['plivalorcusteio'], 0, ',', '.'); ?></td>
                                <td><?php echo number_format($prepi['plivalorcapital'], 0, ',', '.'); ?></td>
                                <td><?php echo number_format(($prepi['plivalorcusteio']+ $prepi['plivalorcapital']), 0, ',', '.'); ?></td>
                            </tr>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </tbody>
            </table>
        </div>

    </div>
</div>

<script>
    $(document).ready(function(){
        $('.dataTables-example').DataTable({
            pageLength: 100,
            responsive: true,
            dom: '<"html5buttons"B>lTfgitp',
            "language": {
                "url": "/zimec/public/temas/simec/js/plugins/dataTables/Portuguese-Brasil.json"
            }
        });
    });

</script>
