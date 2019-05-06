<div class="div-grupo-estrategico">
    <div class="ibox-title">
        <h5>Planejamento Estrat�gico </h5>
    </div>
    <div class="ibox-content">
        <?php echo $simec->select('obeid', 'Objetivo Estrat�gico', $dadosPI['obeid'], (new Planacomorc_Model_ObjetivoEstrategico())->recuperarSqlCombo(['obecod', 'obenome'], null, 'obecod')); ?>
        <div class="div_meeid">
            <?php echo $simec->select('meeid', 'Meta Estrat�gica', $dadosPI['meeid'], (new Planacomorc_Model_MetaEstrategica())->recuperarSqlCombo(['meecod', 'meenome'], null, 'meecod')); ?>
        </div>
        <div class="div_dieid">
            <?php echo $simec->select('dieid', 'Diretriz Estrat�gica', $dadosPI['dieid'], (new Planacomorc_Model_DiretrizEstrategica())->recuperarSqlCombo(['diecod', 'dienome'], null, 'diecod')); ?>
        </div>
    </div>
</div>