<?php
/**
 * Dados da a��o para justificativa.
 * @version $Id: inicio.inc 89632 2014-11-04 12:59:02Z maykelbraz $
 */

// -- Identificador do relat�rio de gest�o
$rlgid = $_REQUEST['rlgid'];

if (!$dados['rldid']) {
    echo <<<HTML
<div class="alert alert-danger col-lg-6 col-lg-offset-3" role="alert">
    Antes de visualizar o formul�rio de justificativas, � necess�rio cadastrar uma a��o.
</div>
HTML;
    return;
}

// -- Template de dados da a��o
$dados['exercicio'] = $_SESSION['exercicio'];
$quadroAcao = preencheTemplate(
    file_get_contents(dirname(__FILE__) . '/../acao/html-pdf.php'),
    $dados
);

// -- CSS de formata��o do quadro da a��o
echo file_get_contents(dirname(__FILE__) . '/../css-relatorio.php');
?>
<div class="col-lg-12 row">
    <?php if (empty($dados['docid'])): ?>
    <div class="col-lg-12">
    <?php else: ?>
    <div class="col-lg-11">
    <?php endif; ?>
        <div class="col-lg-10 col-lg-offset-1">
            <?php echo $quadroAcao; ?>
        </div>
    </div>
    <?php if (!empty($dados['docid'])): ?>
    <div class="col-lg-1"><?php wf_desenhaBarraNavegacao($dados['docid'], array()); ?></div>
    <?php endif; ?>
    <br style="clear:both" />
    <br />
    <br />
    <div class="col-lg-12">
        <div class="page-header">
            <h4>Justificativas</h4>
        </div>
        <div class="well">
    <?php
    $questionario = carregarQuestionarioTcu($dados['rldid']);

    /**
     * Question�rio do TCU.
     * @see questionario.inc
     */
    require_once(dirname(__FILE__) . '/../questionario.inc');
    ?>
        </div>
    </div>
</div>