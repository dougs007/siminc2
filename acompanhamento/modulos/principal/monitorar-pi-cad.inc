<?php

    include_once APPRAIZ . "monitora/classes/Pi_PlanoInterno.class.inc";

    $mPlanoInterno = new Pi_PlanoInterno($_REQUEST['pliid']);
    $planoAcao = current($mPlanoInterno->recuperarDados());
    
    $acoid = $_REQUEST['acoid'] ? $_REQUEST['acoid'] : $planoAcao['acoid'];
    $mAcompanhamento = new Acompanhamento_Model_Acompanhamento($acoid);

    $listaDeAnexos = (new Acompanhamento_Model_AcompanhamentoArquivo())->buscarPorAcompanhamento($mAcompanhamento->acoid);

    $listaPerfis = pegaPerfilGeral();
?>

<script src="../library/liquify/snap.svg.js"></script>
<script src="../library/liquify/liquid.meter.js"></script>

<style>
    .no-margin-bottom .form-group{
        margin-bottom: 5px;
    }
</style>

        <?php if($planoAcao['pliid']){ ?>

            <div class="col-md-12">

                <div class="ibox float-e-margins">
                    <div class="ibox-title">
                        <div class="row">
                            <div class="col-sm-12">
                                <h5>
                                    Informa��es do Projeto: 
                                    <?php
                                        if(!empty($planoAcao['plicod'])){
                                            echo '<span class="link" title="Exibir Espelho do PA" style="color: red; padding: 5px;" onclick="javascript: exibirEspelhoPi(\''. (int)$planoAcao['pliid']. '\')">(' . $planoAcao['plicod'] . ')</span>';
                                        }
                                    ?>
                                </h5>
                            </div>
                        </div>
                    </div>
                    <div class="ibox-content">
                        <div class="row form-horizontal">
                            <div class="col-md-4 no-margin-bottom">
                                <?php
                                $qtdPrevista = $mPlanoInterno->recuperarQuantidadePrevista();
                                $ultimoHistorico = $mPlanoInterno->recuperarUltimoHistoricoAcompanhamento();

                                $dadosGrafico = [];
                                if(count($planoAcao)){
                                    foreach ($planoAcao as $key => $valor) {
                                        if(in_array($key, ['previsto', 'autorizado', 'empenhado', 'liquidado', 'pago'])){
                                            $dadosGrafico[$key]['descricao'] = $key == 'autorizado' ? 'Provisionado' : ucfirst($key);
                                            $dadosGrafico[$key]['valor'] = $valor;
                                            $dadosGrafico[$key]['categoria'] = 'PI';
                                        }
                                    }
                                }

                                $simec->setPodeEditar(0);
                                $simec->setLabelSize(4);
                                if($ultimoHistorico){
                                    echo $simec->input('Monitorado', 'Monitorado em: ', "{$ultimoHistorico['hisdata']} por {$ultimoHistorico['usunome']}");
                                }
                                echo $simec->input('Quantidade', 'Quantidade', $planoAcao['picquantidade']);
                                echo $simec->input('Unidade', 'Unidade', $planoAcao['pumnome']);
                                echo $simec->input('Produto', 'Produto', $planoAcao['pprnome']);
                                echo $simec->input('Quantidadep', 'Quantidade prevista at� a data', $qtdPrevista);
                                $simec->setLabelSize(3);
                                $simec->setPodeEditar(1);
                                ?>
                            </div>
                            <?php
                                # Exibe o Gr�fico de Acompanhamento caso n�o seja Enquadramento N�o Or�ament�rio.
                                if($planoAcao['eqdcod'] !== Monitora_Model_PiEnquadramentoDespesa::EQDCOD_NAO_ORCAMENTARIA): ?>
                                    <div class="col-md-6">
                                        <h3 class="text-center">Acompanhamento do PA</h3>
                                        <?php
                                            $colors = "'#55BF3B', '#eeaaee', '#00BFFF', '#aaeeee', '#7798BF', '#DDDF0D', '#7CCD7C', '#DF5353', '#008000', '#CD0000', '#FF4500', '#ff0066', '#4B0082', '#808000', '#800000', '#2F4F4F', '#006400', '#FFA500'";
                                            $grafico = new Grafico(Grafico::K_TIPO_COLUNA, false);
                                            $grafico->setFormatoTooltip(Grafico::K_TOOLTIP_DECIMAL_0)
                                                ->setColors($colors)
                                                ->setHeight('200px')
                                                ->gerarGrafico($dadosGrafico);
                                        ?>
                                    </div>
                                    <div class="col-sm-2">
                                        <?php
                                            $percentual = $planoAcao['previsto'] ? $planoAcao['empenhado'] * 100 / $planoAcao['previsto'] : 0;
                                            $titulo_grafico = 'Percentual de Empenho';
                                        ?>
                                        <h3 class="text-center"><?= $titulo_grafico; ?></h3>
                                        <meter style="display: none;" max="1000" value="<?php echo $percentual; ?>" id="percentual-empenhado"></meter>
                                    </div>
                            <?php else: ?>
                                <div class="col-sm-2">
                                    <?php
                                        $percentual = $planoAcao['picquantidade'] ? $mAcompanhamento->acoquantidade * 100 / $planoAcao['picquantidade'] : 0;
                                        $titulo_grafico = 'Percentual de Execu��o';
                                    ?>
                                    <h3 class="text-center"><?= $titulo_grafico; ?></h3>
                                    <meter style="display: none;" max="1000" value="<?php echo $percentual; ?>" id="percentual-empenhado"></meter>
                                </div>
                            <?php endif; ?>
                        </div>
                    </div>
                </div>

            </div>



            <form id="formMonitorar" name="formMonitorar" method="post" class="form-horizontal">
                <input type="hidden" name="req" id="req" value="salvar" />
                <input name="pliid" id="pliid" type="hidden" value="<?php echo $planoAcao['pliid']; ?>">
                <input name="suoid" id="suoid" type="hidden" value="<?php echo $planoAcao['suoid']; ?>">
                <input name="acoid" id="acoid" type="hidden" value="<?php echo $mAcompanhamento->acoid; ?>">

                <div class="col-md-8">
                    <div class="ibox float-e-margins">
                        <div class="ibox-title">
                            <h5>
                                Monitoramento do Projeto
                                <?php if($mAcompanhamento->acoid){ ?>
                                    <a style="margin-left: 10px;" class="fa fa-history detalhe-pi" title="Hist�rico de altera��es" href="<?php echo $urlModulo; ?>&req=ver-historico&acoid=<?php echo $mAcompanhamento->acoid; ?>"></a>
                                <?php } ?>
                            </h5>
                        </div>
                        <div class="ibox-content">
                            <?php
                                # Caso o usu�rio logado esteja com perfil de consulta o formulario apresenta como somente leitura
                                if(in_array(PFL_CONSULTA, $listaPerfis)){
                                    $simec->setPodeEditar(0);
                                }
                                echo $simec->moedaInteiro('acoquantidade', 'Executado', $mAcompanhamento->acoquantidade, ['required']);
                                echo $simec->textarea('acoanalise', 'An�lise Situacional', $mAcompanhamento->acoanalise, ['rows'=>6]);
                                echo $simec->select('claid', 'Classifica��o', $mAcompanhamento->claid, (new Acompanhamento_Model_Classificacao())->recuperarSqlCombo(null, ['tipid = ' . Acompanhamento_Model_Tipo::K_TIPO_PI]));

                                $aMedidasSelecionadas = $mAcompanhamento->recuperarMedidas();
                                echo '<span class="span-medida" id="span-medida" ' . (!count($aMedidasSelecionadas) ? 'style="display: none"' : '') . '>' . $simec->select('medidas[]', 'Medidas a serem adotadas', $aMedidasSelecionadas, (new Acompanhamento_Model_Medida())->recuperarSqlCombo(null, ['claid = ' . (int)$mAcompanhamento->claid])) . '</span>';
                                echo '<span class="span-medida" ' . (!count($aMedidasSelecionadas) ? 'style="display: none"' : '') . '>' . $simec->textarea('acoprovidencias', 'Detalhamento das provid�ncias a serem adotadas', $mAcompanhamento->acoprovidencias, ['rows'=>6]) . '</span>';
                            ?>

                            <div class="form-group">
                                <div class="text-center">
                                    <?php
                                        # Caso o usu�rio logado n�o esteja com perfil de consulta ou o de consulta unidade o formulario exibe o bot�o de salvar
                                        if(!in_array(PFL_CONSULTA, $listaPerfis) && !(in_array(PFL_CONSULTA_UNIDADE, $listaPerfis))) { ?>
                                        <button class="btn btn-primary" type="button" id="btn-salvar"><i class="fa fa-check"></i>&nbsp;Salvar</button>
                                    <?php } ?>
                                    <a href="?modulo=inicio&acao=C" class="btn btn-warning" id="btn-voltar" type="button"><i class="fa fa-arrow-left"></i>&nbsp;Voltar</a>
                                    <?php if($mAcompanhamento->acoid){ ?>
    <!--                                        <a href="?modulo=apoio/acompanhamento_form&acao=A&req=excluir&acoid=--><?php //echo $mAcompanhamento->acoid; ?><!--" class="btn btn-danger link-excluir" id="btn-excluir" type="button"><i class="fa fa-close"></i>&nbsp;Excluir</a>-->
                                    <?php } ?>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="col-md-4">
                    <div class="ibox float-e-margins">
                        <div class="ibox-title">
                            <h5>Anexos</h5>
                        </div>
                        <div class="ibox-content">
                            <div class="form-group">
                                <div class="col-lg-12">
                                    <table id="table_anexos_acompanhamento" cellpadding="5" border="0" width="98%" align="center" class="table table-striped table-hover table-bordered table-hover">
                                        <tr>
                                            <td style="text-align: left;"><b>Nome do arquivo</b></td>
                                            <td style="text-align: left;"><b>Descri��o</b></td>
                                            <td style="text-align: center;"><b>A��o</b></td>
                                        </tr>
                                        <?php 
                                            if($listaDeAnexos):
                                                foreach($listaDeAnexos as $anexo):
                                        ?>
                                            <tr style="height: 30px;" class="tr_anexos_acompanhamento_<?php echo $anexo['arqid']; ?>" >
                                                <td style="text-align: left;"><a href="#" onclick="javascript:abrirArquivoAcompanhamento('<?php echo $anexo['arqid']; ?>'); return false;" ><?php echo $anexo['arqnome']. '.'. $anexo['arqextensao']; ?></a></td>
                                                <td style="text-align: left;"><?php echo $anexo['arqdescricao']; ?></td>
                                                <td style="text-align: center;">
                                                    <input type="hidden" value="<?php echo $anexo['arqid']; ?>" name="listaAnexos[]">
                                                    <span class="glyphicon glyphicon-trash btnRemoverAnexosAcompanhamento link" title="Excluir o arquivo <?php echo $anexo['arqnome']. '.'. $anexo['arqextensao']; ?>" data-anexos-acompanhamento="<?php echo $anexo['arqid']; ?>" />
                                                </td>
                                            </tr>
                                        <?php
                                                endforeach;
                                            endif;
                                        ?>
                                    </table>
                                </div>
                            </div>

                            <div class="form-group">
                                <div class="text-center">
                                    <?php
                                        # Caso o usu�rio logado n�o esteja com perfil de consulta o formulario exibe o bot�o de salvar
                                        if(!in_array(PFL_CONSULTA, $listaPerfis) && (!in_array(PFL_CONSULTA_UNIDADE, $listaPerfis))):
                                    ?>
                                        <input type="button" id="btn_inserir_anexos_acompanhamento" title="Inserir Anexos" value="Inserir Anexos" class="btn btn-info"/>
                                    <?php endif; ?>
                                </div>
                            </div>

                        </div>
                    </div>
                </div>

            </form>
        <?php } ?>

        <!-- Modal PI -->
        <div class="modal fade" id="detalhe-pi" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
            <div class="modal-dialog modal-lg" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                        <h4 class="modal-title" id="myModalLabel"></h4>
                    </div>
                    <div class="modal-body">

                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-danger" data-dismiss="modal">Fechar</button>
                    </div>
                </div>
            </div>
        </div>

        <!-- Modal de anexos -->
        <div class="row">
            <div class="col-md-12">
                <div id="modal_upload_acompanhamento" class="modal fade">
                    <div class="modal_dialog_upload_acompanhamento">
                        <div class="modal-content">
                            <div class="modal-header">
                                <button class="close" aria-hidden="true" data-dismiss="modal" type="button">�</button>
                                <h4 class="modal-title">Anexar arquivos(Documentos)</h4>
                            </div>
                            <div class="modal-body">
                                <form class="dropzone" method="POST" enctype="multipart/form-data" action="<?php echo $urlModulo; ?>&acoid=<?php echo $mAcompanhamento->acoid; ?>&aba=1&req=uploadAnexoAcompanhamento" id="formularioAnexoAcompanhamento" name="formularioAnexoAcompanhamento">
                                    <div class="form-group">
                                        <label for="arqdescricao" class="col-lg-2 control-label">Descri��o:</label>
                                        <div class="col-lg-10">
                                            <input type="text" value="" class="CampoEstilo normal form-control" placeholder="Insira a descri��o do arquivo." title="Descri��o" id="arqdescricao" name="arqdescricao" maxlength="255" size="2">
                                        </div>
                                    </div>
                                    <div class="fallback">
                                        <input name="file" type="file" multiple />
                                    </div>
                                </form>
                            </div>
                            <div class="modal-footer">
                                <button class="btn btn-default" data-dismiss="modal" type="button">Fechar</button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>

<script>
    urlModulo = '<?php echo $urlModulo; ?>';
    
    $(function(){
        $('#claid').change(function(){
            $.ajax({
                url: urlModulo+ '&req=carregarMedida&claid=' + $(this).val(),
                dataType: 'json',
                success: function(retorno){
                    $('#span-medida').html(retorno.select);
                    if(retorno.medida == 't'){
                        $('.span-medida').show();
                    } else {
                        $('.span-medida').hide();
                    }
                }
            });
        });

        $('.selecionar-meta').click(function(){
            if(!$('#suoid').val()){
                swal('', 'Por favor, escolha uma unidade.', 'warning');
                return false;
            }
        });

        $('#suoid').change(function(){
            window.location.href = urlModulo+ '&suoid=' + $(this).val();
        });

        $('.div-meta').mouseenter(function(){
            var cor = $(this).data('cor');
            $(this).removeClass(cor).addClass('blue-bg');
        });

        $('.div-meta').mouseleave(function(){
            var cor = $(this).data('cor');
            $(this).removeClass('blue-bg').addClass(cor);
        });

        $('.detalhe-pi').click(function(){
            var url = $(this).attr('href');
            var title = $(this).attr('title');
            $('#detalhe-pi .modal-body').load(url);
            $('#detalhe-pi .modal-title').html(title);
            $('#detalhe-pi').modal();
            return false;
        });

        $('#btn-salvar').click(function(){
            if($('#span-medida').css('display') != 'none' && !$('#medidas').val()){
                swal('', "O campo 'Medidas a serem adotadas' � de preenchimento obrigat�rio", 'warning');
                return false;
            }

            $('#formMonitorar').submit();
        });
        
        $('#btn_inserir_anexos_acompanhamento').click(function(){
            abrirModalUploadAcompanhamento();
        });

        // Evento de terminar de carregar arquivos
        Dropzone.options.formularioAnexoAcompanhamento = {
            init: function() {
                
                this.on("success", function(file, response){
                    var jsonResponse = $.parseJSON(response);
                    inserirNovoAnexoAcompanhamento(jsonResponse);
                });

                this.on("queuecomplete", function(file){

                    // Armazena o objeto Dropzone para chamar m�todos
                    objFormularioAnexoAcompanhamento = this;
                    // Chama mensagem de sucesso
                    swal({
                      title: "",
                      text: "Arquivos salvos com sucesso!",
                      timer: 2000,
                      showConfirmButton: false,
                      type: "success"
                    }, function(){
                        // Fecha o swal alert
                        swal.close();
                        // limpa campo de upload
                        objFormularioAnexoAcompanhamento.removeAllFiles();
                        // fecha modal ap�s a sele��o
                        $('#modal_upload_acompanhamento').modal('hide');
                    });
                });
            }
        };

        $('#table_anexos_acompanhamento').on('click', '.btnRemoverAnexosAcompanhamento', function(){
            var id = $(this).attr('data-anexos-acompanhamento');
            $('.tr_anexos_acompanhamento_'+ id).remove();
        });

        $('#percentual-empenhado').liquidMeter({
            shape: 'circle',
            color: '#0088cc',
            background: '#F9F9F9',
            fontSize: '24px',
            fontWeight: '600',
            stroke: '#F2F2F2',
            textColor: '#333',
            liquidOpacity: 0.9,
            liquidPalette: ['#333'],
            speed: 3000,
        });
    });
    
    function abrirModalUploadAcompanhamento() {
        $('.modal_dialog_upload_acompanhamento').show();
        $('#modal_upload_acompanhamento').modal();
        $('#modal_upload_acompanhamento .chosen-container').css('width', '100%');
    }

    function inserirNovoAnexoAcompanhamento(json) {
        var trHtml = '<tr style="height: 30px;" class="tr_anexos_acompanhamento_'+ json.arqid+ '" >'
            + '                    <td style="text-align: left;"><a href="#" onclick="javascript:abrirArquivoAcompanhamento('+ json.arqid+ '); return false;" >'+ json.arqnome+ '</a></td>'
            + '                    <td style="text-align: left;">'+ json.arqdescricao+ '</td>'
            + '                    <td style="text-align: center;">'
            + '                         <input type="hidden" value="'+ json.arqid+ '" name="listaAnexos[]">'
            + '                         <span class="glyphicon glyphicon-trash btnRemoverAnexosAcompanhamento link" title="Excluir o arquivo '+ json.arqnome+ '" data-anexos-acompanhamento="'+ json.arqid+ '" >'
            + '                    </td>'
            + '                </tr>'
        ;
        $('#table_anexos_acompanhamento').append(trHtml);
    }

    /**
     * Abre um arquivo cadastrado no sistema de comunicados.
     * @param {int} arqid O ID do arquivo no sistema.
     */
    function abrirArquivoAcompanhamento(arqid) {
        var uri = window.location.href;
        uri = uri.replace(/\?.+/g, '?modulo=principal/arquivo/visualizar&acao=A&download=S&arqid=' + arqid+ '&esquema=acompanhamento');
        window.location.href = uri;
    }

    /**
     * Exibe popup com Detalhes do pi. Tela de Espelho de PI.
     *
     * @returns VOID
     */
    function exibirEspelhoPi(pliid){
        window.open(
            '?modulo=inicio&acao=C&req=espelho-pi&pliid='+ pliid,
            'popup_espelho_pi',
            'width=780,height=1000,status=1,menubar=1,toolbar=0,scrollbars=1,resizable=1');
    }

</script>