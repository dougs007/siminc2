<?php
    $acpid = $_REQUEST['acpid'];
    $acompanhamentopnc = new Acompanhamento_Model_Acompanhamentopnc($acpid);
    $listaIndicadorPnc = $acompanhamentopnc->buscarIndicadoresPnc();
    
    # Busca informa��es da Unidade e Subunidade pra exibir informa��es extras pra o usu�rio
    $subunidade = new Public_Model_SubUnidadeOrcamentaria($acompanhamentopnc->suoid);
    $unidadeOrcamentaria = new Public_Model_UnidadeOrcamentaria($subunidade->unoid);
    $exercicio = (int)$unidadeOrcamentaria->prsano;
    
    # Verificando se os indicadores do ano atual foi preenchido.
    $indicadoresPreenchidos = $acompanhamentopnc->verificarPreenchimentoIndicadoresAnoAtual();
?>

<table class="indicadores_table table table-bordered">
    <thead>
        <tr>
            <th>DESCRI��O DO INDICADOR</th>
            <?php for($ano = 2010; $ano <= ((int)$exercicio); $ano++): ?>
                <th><?php echo $ano; ?></th>
            <?php endfor; ?>
        </tr>
    </thead>
    <?php if($listaIndicadorPnc): ?>
    <tbody>
        <?php foreach($listaIndicadorPnc as $indicador): ?>
            <tr>
                <td><?php echo $indicador['ipncod']. ' - '. $indicador['ipndsc']; ?></td>
                <?php
                    for($ano = 2010; $ano <= ((int)$exercicio); $ano++):
                        $acompanhamentoIndicadorPnc = new Acompanhamento_Model_Indicadorpnc();
                        $acompanhamentoIndicadorPnc->acpid = $acompanhamentopnc->acpid;
                        $acompanhamentoIndicadorPnc->unocod = $unidadeOrcamentaria->unocod;
                        $acompanhamentoIndicadorPnc->suocod = $subunidade->suocod;
                        $acompanhamentoIndicadorPnc->ipncod = $indicador['ipncod'];
                        $acompanhamentoIndicadorPnc->prsano = $ano;
                        $acompanhamentoIndicadorPnc->buscarPorAcompanhamentoPncUnidadeIndicadorAno();
                ?>
                    <td>
                        <?php if(Acompanhamento_Controller_Acompanhamentopnc::verificarPermissaoEditar($acpid, $ano, $exercicio)): ?>
                            <?php if($acompanhamentoIndicadorPnc->idpid): ?>
                                <a href="#" class="editar_indicador link" data-idpid="<?php echo $acompanhamentoIndicadorPnc->idpid; ?>" title="Editar Indicador PNC">
                                    <?= !$acompanhamentoIndicadorPnc->idpquantidade? 0: $acompanhamentoIndicadorPnc->idpquantidade ?>
                                </a>
                            <?php else: ?>
                                <span class="editar_indicador fa fa-pencil link" data-idpid="" data-acpid="<?php echo $acpid; ?>" data-unocod="<?php echo $unidadeOrcamentaria->unocod; ?>" data-suocod="<?php echo $subunidade->suocod; ?>" data-ipncod="<?php echo trim($indicador['ipncod']); ?>" data-prsano="<?php echo $ano; ?>" title="Editar Indicador PNC"></span>
                            <?php endif; ?>
                        <?php else: ?>
                            <?php if($acompanhamentoIndicadorPnc->idpid): ?>
                                <?= !$acompanhamentoIndicadorPnc->idpquantidade? 0: $acompanhamentoIndicadorPnc->idpquantidade ?>
                            <?php else: ?>
                                <span class= "fa fa-pencil" title="Indicador PNC"></span>
                            <?php endif; ?>
                        <?php endif; ?>
                    </td>
                <?php endfor; ?>
            </tr>
        <?php endforeach; ?>
    </tbody>
    <?php else: ?>
        <tfoot>
            <tr>
                <td colspan="<?php echo($ano-2010); ?>">N�o existem indicadores cadastrados pra essa Meta PNC.</td>
            </tr>
        </tfoot>
    <?php endif; ?>
</table>

<?php echo '<input id="hid_indicadores_preenchidos" type="hidden" value="'.((int)$indicadoresPreenchidos). '" />'; ?>
