<?php

$modelSubunidade = new Public_Model_SubUnidadeOrcamentaria();
$modelUo = new Public_Model_UnidadeOrcamentaria();

switch($_REQUEST['req']){
    case 'salvar-limite-rp':
        # Exclui(Exclus�o l�gica) o registro de limite atual
        $modelSubunidaderplimite = new Proposta_Model_Subunidaderplimite();
        $modelSubunidaderplimite->suoid = $_REQUEST['suoid'];
        $modelSubunidaderplimite->irpcod = $_REQUEST['irpcod'];
        $modelSubunidaderplimite->buscarPorSuoidIrpcod();
        if($modelSubunidaderplimite->srlid){
            $modelSubunidaderplimite->srlstatus = 'I';
            $modelSubunidaderplimite->salvar();
        }
        
        # Salva o novo limite pra unidade
        $modelSubunidaderplimite = new Proposta_Model_Subunidaderplimite();
        $modelSubunidaderplimite->popularDadosObjeto($_REQUEST);
        $resultado = $modelSubunidaderplimite->salvar();
        if($resultado){
            $modelSubunidaderplimite->commit();
            echo json_encode(array(
                'msg' => utf8_encode('Opera��o realizada com sucesso!'),
                'irpcod' => $modelSubunidaderplimite->irpcod,
                'suoid' => $modelSubunidaderplimite->suoid
            ));
        } else {
            echo json_encode(array('msg' => utf8_encode('Erro ao salvar!')));
        }
    die;
    case 'salvar-limite-rp-fnc':
        $unoid = $_REQUEST['unoid'];
        $suoid = $_REQUEST['suoid'];
        $irpcod = $_REQUEST['irpcod'];
        
        $listaSubunidadeFnc = (new Public_Model_SubUnidadeOrcamentaria)->recuperarTodos('*', ['unoid = ' . (int)$unoid, "suostatus = 'A'"]);
        foreach($listaSubunidadeFnc as $contador => $subUnidade){
            # Exclui(Exclus�o l�gica) o registro de limite atual
            $modelSubunidaderplimite = new Proposta_Model_Subunidaderplimite();
            $modelSubunidaderplimite->suoid = $subUnidade['suoid'];
            $modelSubunidaderplimite->irpcod = $irpcod;
            $modelSubunidaderplimite->buscarPorSuoidIrpcod();
            if($modelSubunidaderplimite->srlid){
                $modelSubunidaderplimite->srlstatus = 'I';
                $modelSubunidaderplimite->salvar();
            }

            # Salva o novo limite pra unidade
            $modelSubunidaderplimite = new Proposta_Model_Subunidaderplimite();
            $modelSubunidaderplimite->popularDadosObjeto($_REQUEST);
            $modelSubunidaderplimite->suoid = $subUnidade['suoid'];
            $resultado = $modelSubunidaderplimite->salvar();
        }

        if($resultado){
            $modelSubunidaderplimite->commit();
            echo json_encode(array(
                'msg' => utf8_encode('Opera��o realizada com sucesso!'),
                'irpcod' => $irpcod,
                'unoid' => $unoid,
                'suoid' => $suoid
            ));
        } else {
            echo json_encode(array('msg' => utf8_encode('Erro ao salvar!')));
        }
    die;
}

$filtros = array(
    "suo.prsano = '". (int)$_SESSION['exercicio']. "'",
    'suo.unofundo = FALSE',
);

$listaSubunidadeTotais = $modelSubunidade->buscarPropostaTotaisLimites((object)array(
    'exercicio' => $_SESSION['exercicio'],
    'fundo' => FALSE
));

$listaUoFnc = $modelUo->buscarPropostaTotaisLimitesFnc((object)array(
    'exercicio' => $_SESSION['exercicio'],
    'fundo' => FALSE,
    'unocod' => UNOCOD_FNC
));
$UofncComTotais = current($listaUoFnc);

$listaSubunidadeFncTotais = $modelSubunidade->buscarPropostaTotaisLimites((object)array(
    'exercicio' => $_SESSION['exercicio'],
    'fundo' => TRUE
));
$subUnidadeFncComTotais = current($listaSubunidadeFncTotais);
//ver($subUnidadeFncComTotais, d);
/**
 * Cabe�alho padr�o do sistema.
 * @see cabecalho.inc
 */
include APPRAIZ . "includes/cabecalho.inc";
?>

<style>
    .title-disponivel{
        cursor: help;
    }

    .linha_subunidade, .linha_fnc {
        background-color: rgba(241, 246, 215, 0.3) !important;
        font-weight: bold;
    }
</style>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-10">
        <h2><?php echo $titulo_modulo; ?></h2>
    </div>
</div>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">

        <div class="col-md-12">

            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5>&nbsp;</h5>
                </div>
                <div class="ibox-content">
                    <div class="table-responsive">
                        <table class="table table-bordered table-hover" >
                            <thead>
                            <tr class="text-center">
                                <th style="border-right: 1px black solid;">
                                    <i class="fa fa-plus detalhar-todos link"></i>&nbsp;&nbsp;Unidade
                                </th>
                                <th width="10%" style="border-right: 1px black solid;">Total Pr�-PI</th>
                                <th width="10%" style="border-right: 1px black solid;">Limite RP</th>
                            </tr>
                            </thead>
                            <?php if($listaSubunidadeTotais): ?>
                                <?php
                                    $listaRpTotaisPrePi = $modelSubunidade->buscarPropostaRpTotaisLimitesFnc((object)array(
                                        'exercicio' => $_SESSION['exercicio'],
                                        'suoid' => $subUnidadeFncComTotais['suoid']));
                                ?>
                                <tbody>
                                    <tr class="linha_fnc" style="background-color: #ffe6e1 !important;">
                                        <td style="border-right: 1px black solid;">
                                            <i class="fa fa-plus detalhar-linha-fnc link" data-unoid="<?php echo $UofncComTotais['unoid']; ?>"></i>&nbsp;&nbsp;
                                            <span class="detalhe-fnc" data-unoid="<?php echo $UofncComTotais['unoid']; ?>">
                                                <?php echo $UofncComTotais['unosigla'] . ' - ' . $UofncComTotais['unonome'] . ' (' . $UofncComTotais['unocod'] . ')'; ?>
                                            </span>
                                        </td>
                                        <td style="border-right: 1px black solid;" class="text-right">
                                            <?php echo number_format($UofncComTotais['total_pre_pi'], 0, ',', '.'); ?>
                                        </td>
                                        <td id='total_<?php echo $subUnidadeFncComTotais['suoid']; ?>' style="border-right: 1px black solid;" class="text-right">
                                            <?php echo number_format($UofncComTotais['total_limite_rp'], 0, ',', '.'); ?>
                                        </td>
                                    </tr>
                                    <?php foreach($listaRpTotaisPrePi as $Rp): ?>
                                        <tr class="tr_<?php echo $UofncComTotais['unoid']; ?> tr_detalhe" style="display: none;">
                                            <td style="padding-left: 30px; border-right: 1px black solid;" >
                                                <span>
                                                    <?php echo '(RP '. $Rp['irpcod']. ') - '. $Rp['irpdsc']; ?>
                                                </span>
                                            </td>
                                            <td style="border-right: 1px black solid;" class="text-right">
                                                <?php echo number_format($Rp['total_pre_pi'], 0, ',', '.'); ?>
                                            </td>
                                            <td class="text-right" style="border-right: 1px black solid;">
                                                <input name="limites[]" type="text" class="input_valor salvar-limite-rp-fnc" value="<?php echo number_format($Rp['total_limite_rp'], 0, '.', ''); ?>" data-unoid="<?php echo $UofncComTotais['unoid']; ?>" data-suoid="<?php echo $subUnidadeFncComTotais['suoid']; ?>" data-irpcod="<?php echo $Rp['irpcod']; ?>" >
                                            </td>
                                        </tr>
                                    <?php endforeach; ?>
                                    <?php foreach($listaSubunidadeTotais as $subunidade): ?>
                                        <?php
                                            $listaRpTotaisPrePi = $modelSubunidade->buscarPropostaRpTotaisLimites((object)array(
                                                'exercicio' => $_SESSION['exercicio'],
                                                'suoid' => $subunidade['suoid']));
                                        ?>
                                        <tr class="linha_subunidade">
                                            <td style="border-right: 1px black solid;">
                                                <i class="fa fa-plus detalhar-linha link" data-suoid="<?php echo $subunidade['suoid']; ?>"></i>&nbsp;&nbsp;
                                                <span class="detalhe-subunidade" data-suoid="<?php echo $subunidade['suoid']; ?>">
                                                    <?php echo $subunidade['unosigla']. ' - '. $subunidade['suonome']. ' (' . $subunidade['suocod']. ')'; ?>
                                                </span>
                                            </td>
                                            <td style="border-right: 1px black solid;" class="text-right">
                                                <?php echo number_format($subunidade['total_pre_pi'], 0, ',', '.'); ?>
                                            </td>
                                            <td id='total_<?php echo $subunidade['suoid']; ?>' style="border-right: 1px black solid;" class="text-right">
                                                <?php echo number_format($subunidade['total_limite_rp'], 0, ',', '.'); ?>
                                            </td>
                                        </tr>
                                        <?php foreach($listaRpTotaisPrePi as $Rp): ?>
                                            <tr class="tr_<?php echo $subunidade['suoid']; ?> tr_detalhe" style="display: none;">
                                                <td style="padding-left: 30px; border-right: 1px black solid;" >
                                                    <span>
                                                        <?php echo '(RP '. $Rp['irpcod']. ') - '. $Rp['irpdsc']; ?>
                                                    </span>
                                                </td>
                                                <td style="border-right: 1px black solid;" class="text-right">
                                                    <?php echo number_format($Rp['total_pre_pi'], 0, ',', '.'); ?>
                                                </td>
                                                <td class="text-right" style="border-right: 1px black solid;">
                                                    <input name="limites[]" type="text" class="input_valor salvar-limite-rp" value="<?php echo number_format($Rp['total_limite_rp'], 0, '.', ''); ?>" data-suoid="<?php echo $subunidade['suoid']; ?>" data-irpcod="<?php echo $Rp['irpcod']; ?>" >
                                                </td>
                                            </tr>
                                        <?php endforeach; ?>
                                    <?php endforeach; ?>
                                </tbody>
                            <?php endif; ?>
                        </table>
                    </div>

                </div>
            </div>
        </div>
    </div>
</div>

<script>
    $(document).ready(function(){

        $('.input_valor').keyup(function(){
            $(this).val(mascaraglobal('###.###.###.###', $(this).val()));
        }).keyup();

        $('.detalhar-linha').click(function(){

            var suoid = $(this).data('suoid');

            if($(this).hasClass('fa-minus')){
                $(this).removeClass('fa-minus').addClass('fa-plus');
                $('.tr_' + suoid).hide();
            } else {
                $(this).removeClass('fa-plus').addClass('fa-minus');
                $('.tr_' + suoid).show('slow');
            }
        });
        
        $('.detalhar-linha-fnc').click(function(){

            var unoid = $(this).data('unoid');

            if($(this).hasClass('fa-minus')){
                $(this).removeClass('fa-minus').addClass('fa-plus');
                $('.tr_' + unoid).hide();
            } else {
                $(this).removeClass('fa-plus').addClass('fa-minus');
                $('.tr_' + unoid).show('slow');
            }
        });

        $('.detalhar-todos').click(function(){

            if($(this).hasClass('fa-minus')){
                $(this).removeClass('fa-minus').addClass('fa-plus');
                $('.detalhar-linha').removeClass('fa-minus').addClass('fa-plus');
                $('.tr_detalhe').hide();
            } else {
                $(this).removeClass('fa-plus').addClass('fa-minus');
                $('.detalhar-linha').removeClass('fa-plus').addClass('fa-minus');
                $('.tr_detalhe').show('slow');
            }
        });

        $('.salvar-limite-rp').change(function(){
            var srllimite = $(this).val()? str_replace(['.'], [''], $(this).val()): 0;
            var suoid = $(this).data('suoid');
            var irpcod = $(this).data('irpcod');

            $.ajax({
                url: '?modulo=configuracao/limite-subunidade-rp&acao=A&req=salvar-limite-rp',
                type: 'POST',
                data: {
                    'suoid': suoid,
                    'irpcod': irpcod,
                    'srllimite': srllimite
                },
                dataType: 'json',
                success: function(dataResponse){
                    limiteTotal = calcularLimiteTotalUnidade(parseInt(dataResponse.suoid));
                    $("#total_"+ dataResponse.suoid).html(number_format(limiteTotal.toFixed(0), 0, ',', '.'));
                }
            });
        });
        
        $('.salvar-limite-rp-fnc').change(function(){
            var srllimite = $(this).val()? str_replace(['.'], [''], $(this).val()): 0;
            var unoid = $(this).data('unoid');
            var suoid = $(this).data('suoid');
            var irpcod = $(this).data('irpcod');

            $.ajax({
                url: '?modulo=configuracao/limite-subunidade-rp&acao=A&req=salvar-limite-rp-fnc',
                type: 'POST',
                data: {
                    'unoid': unoid,
                    'suoid': suoid,
                    'irpcod': irpcod,
                    'srllimite': srllimite
                },
                dataType: 'json',
                success: function(dataResponse){
                    limiteTotal = calcularLimiteTotalFnc(parseInt(dataResponse.suoid));
                    $("#total_"+ dataResponse.suoid).html(number_format(limiteTotal.toFixed(0), 0, ',', '.'));
                }
            });
        });

    });

    function calcularLimiteTotalUnidade(suoid){
        limiteTotal = parseInt(0);
        
        $(".salvar-limite-rp").each(function(){
            if($(this).data("suoid") === suoid){
                var limiteRp = $(this).val()? str_replace('.', '', $(this).val()): 0;
                limiteTotal += parseInt(limiteRp);
            }
        });
        
        return limiteTotal;
    }
    
    function calcularLimiteTotalFnc(suoid){
        limiteTotal = parseInt(0);
        
        $(".salvar-limite-rp-fnc").each(function(){
            if($(this).data("suoid") === suoid){
                var limiteRp = $(this).val()? str_replace('.', '', $(this).val()): 0;
                limiteTotal += parseInt(limiteRp);
            }
        });
        
        return limiteTotal;
    }

</script>
