<?php
    $justificativa = (new Alteracao_Model_Justificativa())->recuperaJustificativa($_REQUEST['pedid']);
?>
<style>
    .size{
        font-size: 1.4em;
        color: #1AB394;
    }
</style>
<div class="row">
    <div class="col-lg-12">
        <div class="ibox float-e-margins">
            <div class="ibox-title">
                <h5>Essas Justificativas tem o objetivo de fornecer insumos para a rastreabilidade das Altera��es Or�ament�rias</h5>
            </div>
            <div class="ibox-content">
                <div class="row">
                    <form id="form-justificativa" name="form-justificativa" method="post" class="form-horizontal">
<!--                        <input type="hidden" name="pedid" id="pedid" value="<?= $_REQUEST['pedid']; ?>">-->
                        <input type="hidden" name="jstid" id="jstid" value="<?= $justificativa->jstid; ?>">
                        <div class="col-md-6">
                            <div class="ibox float-e-margins">
                                <div class="ibox-content">
                                    <?php
                                        $simec->setFormTipo(Simec_View_Helper::K_FORM_TIPO_VERTICAL);
                                        echo $simec->textarea(
                                            'jstnecessidade',
                                            'Necessidade de Altera��o <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_NECESSIDADE. '"></i>',
                                            $justificativa->jstnecessidade,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_NECESSIDADE,
                                                'cols' => 50,
                                                'rows' => 6,
                                                'required'
                                            ]
                                        );
                                        echo $simec->textarea(
                                            'jstfinanciamento',
                                            'Formas de financiamento de Cr�dito e adequa��o da proposta � meta fiscal e ao limite de gastos <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_FINANCIAMENTO. '"></i>',
                                            $justificativa->jstfinanciamento,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_FINANCIAMENTO,
                                                'cols' => 50,
                                                'rows' => 6
                                            ]
                                        );
                                        echo $simec->textarea(
                                            'jstmedida',
                                            'Medida Provis�ria <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_MEDIDA. '"></i>',
                                            $justificativa->jstmedida,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_MEDIDA,
                                                'cols' => 50,
                                                'rows' => 6
                                            ]
                                        );
                                    ?>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-6">
                            <div class="ibox float-e-margins">
                                <div class="ibox-content">
                                    <?php
                                        echo $simec->textarea('jstcausa',
                                            'Causa da Demanda <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_CAUSA. '"></i>',
                                            $justificativa->jstcausa,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_CAUSA,
                                                'cols' => 50,
                                                'rows' => 6,
                                                'required'
                                            ]
                                        );
                                        echo $simec->textarea('jstfontes',
                                            'Verifica��o das fontes, dos Identificadores de uso - Iduso e dos identificadores de Resultado Prim�rio - RP <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_FONTES. '"></i>',
                                            $justificativa->jstfontes,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_FONTES,
                                                'cols' => 50,
                                                'rows' => 6
                                            ]
                                        );
                                        echo $simec->textarea('jstlegislacao',
                                            'Legisla��o Espec�fica <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_LEGISLACAO. '"></i>',
                                            $justificativa->jstlegislacao,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_LEGISLACAO,
                                                'cols' => 50,
                                                'rows' => 6
                                            ]
                                        );
                                    ?>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-12">
                            <div class="ibox float-e-margins">
                                <div class="ibox-content">
                                    <?php
                                        echo $simec->textarea('jstoutros',
                                            'Outras Informa��es <i class="fa fa-info-circle size" title="'. Alteracao_Model_Justificativa::DESC_OUTROS. '"></i>',
                                            $justificativa->jstoutros,
                                            [
                                                'title' => Alteracao_Model_Justificativa::DESC_OUTROS,
                                                'cols' => 50,
                                                'rows' => 6
                                            ]
                                        );
                                    ?>
                                </div>
                            </div>
                        </div>
                    </form>
                    <?php if($podeEditar):  ?>
                        <div class="text-center">
                            <button class="btn btn-primary btn-buscar" type="button" id="salvar-justificativa">
                                <span class="glyphicon glyphicon-saved"></span> Salvar
                            </button>
                        </div>
                    <?php endif; ?>
                </div>
            </div>
        </div>
    </div>
</div>

<script>
    $(document).ready(function (){

        $('#salvar-justificativa').click(function () {

            var podeSalvar = validaRequired();

            if(podeSalvar == true){

                $.post('?modulo=principal/cadastro_alteracoes&acao=C&req=salvar_justificativa',
                    {
                        jstid: $('#jstid').val(),
                        pedid: $('#pedid').val(),
                        jstnecessidade: $('#jstnecessidade').val(),
                        jstcausa: $('#jstcausa').val(),
                        jstfinanciamento: $('#jstfinanciamento').val(),
                        jstfontes: $('#jstfontes').val(),
                        jstmedida: $('#jstmedida').val(),
                        jstlegislacao: $('#jstlegislacao').val(),
                        jstoutros: $('#jstoutros').val(),
                    },
                    function(retorno){
                        if (retorno){
                            swal({
                                title: "",
                                text: "Registro salvo com sucesso!",
                                type: "success",
                                confirmButtonText: 'Ok',
                                closeOnConfirm: true
                            })
                        }
                    }
                );
            }else{
                return false;
            }
        });

        function validaRequired(){

            var msg = '';

            if($('#jstnecessidade').val() == '' || $('#jstnecessidade').val() == null){
                msg += "<br>O preenchimento do campo \"Necessidade de Altera��o\" � obrigat�rio.";
            }
            if($('#jstcausa').val() == '' || $('#jstcausa').val() == null){
                msg += "<br>O preenchimento do campo \"Causa da Demanda\" � obrigat�rio.";
            }

            if(msg !== '') {
                alert(msg);
                return false;
            } else {
                return true;
            }
        }
    });
</script>