<?php

$cProposta = new Proposta_Controller_Proposta();
$mProposta = new Proposta_Model_Proposta($_REQUEST['proid']);
switch ($_REQUEST['req']) {
    case 'salvar':
        $cProposta->salvar($_REQUEST);
        die;
    case 'excluir':
        $cProposta->excluir($_REQUEST['proid']);
        die;
    case 'carregar-funcional':
        echo $simec->select('ptrid', 'Funcional', null, (new Monitora_Model_Ptres())->recuperarSqlPorSubunidadeEEnquadramento($_REQUEST['suoid'], $_REQUEST['eqdid']), ['required']);
        die;
    case 'formulario-detalhe':
        $cProposta->montarFormularioDetalhes($_REQUEST['proid'], $_REQUEST['prdid']);
        die;
    case 'listar-detalhe':
        $cProposta->montarListagemDetalhes($mProposta->proid);
        die;
    case 'salvar-detalhe':
        $cPropostaDetalhe = new Proposta_Controller_PropostaDetalhe();
        $cPropostaDetalhe->salvar($_POST);
        die;
    case 'excluir-detalhe':
        $cPropostaDetalhe = new Proposta_Controller_PropostaDetalhe();
        echo $cPropostaDetalhe->excluir($_REQUEST['prdid']);
        die;
    case 'carregar-rp':
        $rp = (new Monitora_Model_PiEnquadramentoDespesa())->recuperarDescricaoRp($_REQUEST['eqdid']);
        echo '  <div class="form-group">
                    <label class="col-sm-3 control-label">RP: </label>
                    <div class="col-sm-9">
                      <p class="form-control-static">' . $rp . '</p>
                    </div>
                  </div>';
        die;
    case 'recuperar-dados-ptres':
        echo json_encode((new Monitora_Model_Ptres($_REQUEST['ptrid']))->recuperarProdutosPorPtres());
        die;
    case 'recuperar-valores-ptres':
        echo json_encode((new Proposta_Model_PrePlanoInterno())->recuperarValoresPorSubnidadeEPtres($_REQUEST['suoid'], $_REQUEST['ptrid']));
        die;
    case 'recuperar-subunidades-ptres':
        $subunidades = (new Monitora_Model_Ptres($_REQUEST['ptrid']))->recuperarSubunidades();
        echo '  <div class="form-group">
                    <label class="col-sm-3 control-label">Subunidades Vinculadas � Funcional: </label>
                    <div class="col-sm-9">
                      <p class="form-control-static">' . $subunidades . '</p>
                    </div>
                  </div>';
        die;
}

include APPRAIZ . "includes/cabecalho.inc";
?>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-10">
        <h2><?php echo $titulo_modulo; ?></h2>
    </div>
</div>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">
        <div class="col-md-6">
            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5>Dados Gerais</h5>
                </div>
                <div class="ibox-content">
                    <form id="formulario" name="formulario" method="post" class="form-horizontal">
                        <input type="hidden" name="req" id="req" value="salvar" />
                        <input name="proid" id="proid" type="hidden" value="<?php echo $mProposta->proid; ?>">
                        
                        <?php
                        echo $simec->select('suoid', 'SubUnidade', $mProposta->suoid, (new Public_Model_SubUnidadeOrcamentaria())->recuperarSqlCombo(), ['required']);
                        echo $simec->select('eqdid', 'Enquadramento da Despesa', $mProposta->eqdid, (new Monitora_Model_PiEnquadramentoDespesa())->recuperarSqlCombo(), ['required']);
                        echo '<span id="span-rp"></span>';
                        echo '<span id="span-funcional">' . $simec->select('ptrid', 'Funcional', $mProposta->ptrid, (new Monitora_Model_Ptres())->recuperarSqlPorSubunidadeEEnquadramento($mProposta->suoid, $mProposta->eqdid), ['required']) . '</span>';
                        echo '<span id="span-subunidades-ptres"></span>';
                        ?>

                        <div class="form-group ">
                            <label for="" class="col-sm-3 col-md-3 col-lg-3 control-label">Quantidades</label>
                            <div class="col-sm-9 col-md-9 col-lg-9 ">
                                <div class="table-responsive">
                                    <table class="table table-bordered table-hover" >
                                        <thead>
                                        <tr class="text-center">
                                            <th width="20%">N�vel</th>
                                            <th width="20%">Quantidade</th>
                                            <th width="20%">Unidade</th>
                                            <th>Produto</th>
                                        </tr>
                                        </thead>
                                        <tbody>
                                        <tr>
                                            <td>Localizador</td>
                                            <td>
                                                <input name="locquantidadeproposta" id="locquantidadeproposta" type="text" class="form-control valor " required="required">
                                            </td>
                                            <td id="unidade_acao"></td>
                                            <td id="produto_acao"></td>
                                        </tr>
                                        <tr>
                                            <td>PO</td>
                                            <td>
                                                <input name="proquantidade" id="proquantidade" type="text" value="<?php echo number_format($mProposta->proquantidade, 2, ',', '.'); ?>" class="form-control valor " required="required">
                                            </td>
                                            <td id="unidade_po"></td>
                                            <td id="produto_po"></td>
                                        </tr>
                                        </tbody>
                                    </table>
                                </div>

                            </div>
                            <div style="clear:both"></div>
                        </div>

                        <?php
                        echo $simec->valor('proquantidadeexpansao', 'Quantidade Expans�o PO', $mProposta->proquantidadeexpansao);

                        ?>

                        <div class="form-group ">
                            <label for="" class="col-sm-3 col-md-3 col-lg-3 control-label">Limites Pr�-PI</label>
                            <div class="col-sm-9 col-md-9 col-lg-9 ">
                                <div class="table-responsive">
                                    <table class="table table-bordered table-hover" >
                                        <thead>
                                        <tr class="text-center">
                                            <th width="20%">Limite</th>
                                            <th width="20%">Custeio</th>
                                            <th width="20%">Capital</th>
                                        </tr>
                                        </thead>
                                        <tbody>
                                        <tr>
                                            <td>Valor</td>
                                            <td id="limite_valor_custeio"></td>
                                            <td id="limite_valor_capital"></td>
                                        </tr>
                                        <tr>
                                            <td>Expans�o</td>
                                            <td id="limite_expansao_custeio"></td>
                                            <td id="limite_expansao_capital"></td>
                                        </tr>
                                        </tbody>
                                    </table>
                                </div>

                            </div>
                            <div style="clear:both"></div>
                        </div>

                        <?php
                        echo $simec->textarea('projustificativa', 'Justificativa', $mProposta->projustificativa, ['cols'=>60, 'rows'=>6]);
                        echo $simec->textarea('projustificativaexpansao', 'Justificativa Expans�o', $mProposta->projustificativaexpansao, ['cols'=>60, 'rows'=>6]);
                        ?>
                        
                        <div class="form-group">
                            <div class="text-center">
                                <button class="btn btn-primary" type="submit" id="btn-salvar"><i class="fa fa-check"></i>&nbsp;Salvar</button>
                                <a href="?modulo=principal/proposta&acao=A" class="btn btn-warning" id="btn-voltar" type="button"><i class="fa fa-arrow-left"></i>&nbsp;Voltar</a>
                                <?php if($mProposta->proid){ ?>
                                    <a href="?modulo=principal/proposta_form&acao=A&req=excluir&proid=<?php echo $mProposta->proid; ?>" class="btn btn-danger link-excluir" id="btn-excluir" type="button"><i class="fa fa-close"></i>&nbsp;Excluir</a>
                                <?php } ?>                                
                            </div>
                        </div>                        
                    </form>
                </div>
            </div>
        </div>

        <div class="col-md-5">
            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <h5>Dados Financeiros</h5>
                </div>
                <div class="ibox-content" id="">
                    <div id="div_formulario_detalhe">
                        <?php
                        if($mProposta->proid){
                            $cProposta->montarFormularioDetalhes($mProposta->proid);
                        }
                        ?>
                    </div>
                    <div id="div_listagem_detalhe">
                        <?php $cProposta->montarListagemDetalhes($mProposta->proid); ?>
                    </div>
                </div>
            </div>
        </div>

    </div>
</div>

<script>
    $(function(){
        $('#eqdid, #suoid').change(function(){
            $('#span-funcional').load('?modulo=principal/proposta_form&acao=A&req=carregar-funcional&eqdid=' + $('#eqdid').val() + '&suoid=' + $('#suoid').val());
        });

        $('#span-rp').load('?modulo=principal/proposta_form&acao=A&req=carregar-rp&eqdid=' + $('#eqdid').val());
        $('#eqdid').change(function(){
            $('#span-rp').load('?modulo=principal/proposta_form&acao=A&req=carregar-rp&eqdid=' + $('#eqdid').val());
        });

        carregarDadosPtres();
        $('body').on('change', '#ptrid', function(){
            carregarDadosPtres();
        });

        function carregarDadosPtres() {
            $.ajax({
                url: '?modulo=principal/proposta_form&acao=A&req=recuperar-dados-ptres&ptrid=' + $('#ptrid').val(),
                dataType: 'json',
                success: function(dados){
                    $('#unidade_acao').html(dados.unidade_acao);
                    $('#produto_acao').html(dados.produto_acao);
                    $('#unidade_po').html(dados.unidade_po);
                    $('#produto_po').html(dados.produto_po);
                    $('#locquantidadeproposta').val(number_format(parseFloat(dados.locquantidadeproposta), 2, ',', '.'));
                }
            });

            $.ajax({
                url: '?modulo=principal/proposta_form&acao=A&req=recuperar-valores-ptres&ptrid=' + $('#ptrid').val() + '&suoid=' + $('#suoid').val(),
                dataType: 'json',
                success: function(dados){
                    $('#limite_valor_custeio').html(number_format(parseFloat(dados.plivalorcusteio), 2, ',', '.'));
                    $('#limite_valor_capital').html(number_format(parseFloat(dados.plivalorcapital), 2, ',', '.'));
                    $('#limite_expansao_custeio').html(number_format(parseFloat(dados.plivalorcusteioadicional), 2, ',', '.'));
                    $('#limite_expansao_capital').html(number_format(parseFloat(dados.plivalorcapitaladicional), 2, ',', '.'));
                }
            });

            $('#span-subunidades-ptres').load('?modulo=principal/proposta_form&acao=A&req=recuperar-subunidades-ptres&ptrid=' + $('#ptrid').val());
        }
    })
</script>