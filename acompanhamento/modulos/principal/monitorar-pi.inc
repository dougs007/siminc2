<?php
    include_once APPRAIZ . "monitora/classes/Pi_PlanoInterno.class.inc";

    $cAcompanhamento = new Acompanhamento_Controller_Acompanhamento();
    switch ($_REQUEST['req']) {
        case 'salvar':
            $cAcompanhamento->salvar($_REQUEST);
        die;
        case 'excluir':
            $cAcompanhamento->excluir($_REQUEST['acoid']);
        die;
        case 'ver-historico':
            $cAcompanhamento->recuperarHistorico($_REQUEST['acoid']);
        die;
        case 'carregarMedida':
            $mClassificacao = new Acompanhamento_Model_Classificacao($_REQUEST['claid']);
            $retorno['medida'] = $mClassificacao->clamedida;
            $retorno['select'] = $simec->select('medidas[]', 'Medidas a serem adotadas', null, (new Acompanhamento_Model_Medida())->recuperarSqlCombo(null, ['claid = ' . (int)$_REQUEST['claid']]));

            echo json_encode($retorno);
        die;
        case 'uploadAnexo':
            $file = new FilesSimec();
            if($file->setUpload($_REQUEST['arqdescricao'], '', false)){
                echo simec_json_encode(array(
                    'arqid' => $file->getIdArquivo(),
                    'arqnome' => $_FILES['file']['name'],
                    'arqdescricao' => $_REQUEST['arqdescricao']
                ));
            }else{
                echo simec_json_encode(array(
                    'error' => 1,
                    'errorMensage' => 'N�o foi poss�vel enviar o arquivo!'
                ));
            }
        die;
    }

    $mPlanoInterno = new Pi_PlanoInterno($_REQUEST['pliid']);
    $aPlanoInterno = current($mPlanoInterno->recuperarDados());

    $acoid = $_REQUEST['acoid'] ? $_REQUEST['acoid'] : $aPlanoInterno['acoid'];
    $mAcompanhamento = new Acompanhamento_Model_Acompanhamento($acoid);

    $listaDeAnexos = (new Acompanhamento_Model_AcompanhamentoArquivo())->buscarPorAcompanhamento($mAcompanhamento->acoid);

    include APPRAIZ . "includes/cabecalho.inc";
?>

<style>
    .no-margin-bottom .form-group{
        margin-bottom: 5px;
    }
</style>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-10">
        <h2><?php echo $titulo_modulo; ?></h2>
    </div>
</div>

<div class="wrapper wrapper-content animated fadeInRight">
    <div class="row">
        <?php if($aPlanoInterno['pliid']){ ?>

            <div class="col-md-12">

                <div class="ibox float-e-margins">
                    <div class="ibox-title">
                        <div class="row">
                            <div class="col-sm-12">
                                <h5>Informa��es do Projeto</h5>
                            </div>
                        </div>
                    </div>
                    <div class="ibox-content">
                        <div class="row form-horizontal">
                            <div class="col-sm-9 no-margin-bottom">
                                <?php
                                $qtdPrevista = $mPlanoInterno->recuperarQuantidadePrevista();
                                $ultimoHistorico = $mPlanoInterno->recuperarUltimoHistoricoAcompanhamento();

                                $simec->setPodeEditar(0);
                                if($ultimoHistorico){
                                    echo $simec->input('Monitorado', 'Monitorado em: ', "{$ultimoHistorico['hisdata']} por {$ultimoHistorico['usunome']}");
                                }
                                echo $simec->input('Quantidade', 'Quantidade', number_format($aPlanoInterno['picquantidade'], 2, ',', '.'));
                                echo $simec->input('Unidade', 'Unidade', $aPlanoInterno['pumnome']);
                                echo $simec->input('Produto', 'Produto', $aPlanoInterno['pprnome']);
                                echo $simec->input('Quantidade Prevista', 'Quantidade Prevista', number_format($qtdPrevista, 2, ',', '.'));
                                $simec->setLabelSize(3);
                                $simec->setPodeEditar(1);
                                ?>
                            </div>
                            <div class="col-sm-3">
                                <?php if(!count($aBeneficiarioDetalhe)){ ?>
                                    <ul class="list-group clear-list m-t">
                                        <li class="list-group-item fist-item">
                                            Previsto
                                            <span class="pull-right">R$ <?php echo number_format($aPlanoInterno['previsto'], 2, ',', '.'); ?></span>
                                        </li>
                                        <li class="list-group-item">
                                            Empenhado
                                            <span class="pull-right">R$ <?php echo number_format($aPlanoInterno['empenhado'], 2, ',', '.'); ?></span>
                                        </li>
                                        <li class="list-group-item">
                                            Liquidado
                                            <span class="pull-right">R$ <?php echo number_format($aPlanoInterno['liquidado'], 2, ',', '.'); ?></span>
                                        </li>
                                        <li class="list-group-item">
                                            Pago
                                            <span class="pull-right">R$ <?php echo number_format($aPlanoInterno['pago'], 2, ',', '.'); ?></span>
                                        </li>
                                    </ul>
                                <?php } ?>
                            </div>
                        </div>
                    </div>
                </div>

            </div>



            <form id="formulario" name="formulario" method="post" class="form-horizontal">
                <input type="hidden" name="req" id="req" value="salvar" />
                <input name="pliid" id="pliid" type="hidden" value="<?php echo $aPlanoInterno['pliid']; ?>">
                <input name="suoid" id="suoid" type="hidden" value="<?php echo $aPlanoInterno['suoid']; ?>">
                <input name="acoid" id="acoid" type="hidden" value="<?php echo $mAcompanhamento->acoid; ?>">

                <div class="col-md-8">
                    <div class="ibox float-e-margins">
                        <div class="ibox-title">
                            <h5>
                                Monitoramento do Projeto
                                <?php if($mAcompanhamento->acoid){ ?>
                                    <a style="margin-left: 10px;" class="fa fa-history detalhe-pi" title="Hist�rico de altera��es" href="?modulo=principal/monitorar-ppa&acao=A&req=ver-historico&acoid=<?php echo $mAcompanhamento->acoid; ?>"></a>
                                <?php } ?>
                            </h5>
                        </div>
                        <div class="ibox-content">
                            <?php
                                echo $simec->valor('acoquantidade', 'Executado', $mAcompanhamento->acoquantidade, ['required']);
                                echo $simec->textarea('acoanalise', 'An�lise Situacional', $mAcompanhamento->acoanalise);
                                echo $simec->select('claid', 'Classifica��o', $mAcompanhamento->claid, (new Acompanhamento_Model_Classificacao())->recuperarSqlCombo(null, ['tipid = ' . Acompanhamento_Model_Tipo::K_TIPO_PI]), ['required']);

                                $aMedidasSelecionadas = $mAcompanhamento->recuperarMedidas();
                                echo '<span id="span-medida" ' . (!count($aMedidasSelecionadas) ? 'style="display: none"' : '') . '>' . $simec->select('medidas[]', 'Medidas a serem adotadas', $aMedidasSelecionadas, (new Acompanhamento_Model_Medida())->recuperarSqlCombo(null, ['claid = ' . (int)$mAcompanhamento->claid])) . '</span>';

                                echo $simec->textarea('acoprovidencias', 'Detalhamento das provid�ncias a serem adotadas', $mAcompanhamento->acoprovidencias);
                            ?>

                            <div class="form-group">
                                <div class="text-center">
                                    <button class="btn btn-primary" type="button" id="btn-salvar"><i class="fa fa-check"></i>&nbsp;Salvar</button>
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
                                    <table id="table_anexos" cellpadding="5" border="0" width="98%" align="center" class="table table-striped table-hover table-bordered table-hover">
                                        <tr>
                                            <td style="text-align: left;"><b>Nome do arquivo</b></td>
                                            <td style="text-align: left;"><b>Descri��o</b></td>
                                            <td style="text-align: center;"><b>A��o</b></td>
                                        </tr>
                                        <?php 
                                            if($listaDeAnexos):
                                                foreach($listaDeAnexos as $anexo):
                                        ?>
                                            <tr style="height: 30px;" class="tr_anexos_<?php echo $anexo['arqid']; ?>" >
                                                <td style="text-align: left;"><a href="#" onclick="javascript:abrirArquivo('<?php echo $anexo['arqid']; ?>'); return false;" ><?php echo $anexo['arqnome']. '.'. $anexo['arqextensao']; ?></a></td>
                                                <td style="text-align: left;"><?php echo $anexo['arqdescricao']; ?></td>
                                                <td style="text-align: center;">
                                                    <input type="hidden" value="<?php echo $anexo['arqid']; ?>" name="listaAnexos[]">
                                                    <span class="glyphicon glyphicon-trash btnRemoverAnexos link" title="Excluir o arquivo <?php echo $anexo['arqnome']. '.'. $anexo['arqextensao']; ?>" data-anexos="<?php echo $anexo['arqid']; ?>" />
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
                                    <input type="button" id="btn_inserir_anexos" title="Inserir Anexos" value="Inserir Anexos" class="btn btn-info"/>
                                </div>
                            </div>

                        </div>
                    </div>
                </div>

            </form>
        <?php } ?>
    </div>
</div>

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

<div class="row">
    <div class="col-md-12">
        <div id="modal_upload" class="modal fade">
            <div class="modal_dialog_upload">
                <div class="modal-content">
                    <div class="modal-header">
                        <button class="close" aria-hidden="true" data-dismiss="modal" type="button">�</button>
                        <h4 class="modal-title">Anexar arquivos(Documentos)</h4>
                    </div>
                    <div class="modal-body">
                        <form class="dropzone" method="POST" enctype="multipart/form-data" action="acompanhamento.php?modulo=principal/monitorar-ppa&acao=A&acoid=<?php echo $mAcompanhamento->acoid; ?>&aba=1&req=uploadAnexo" id="formularioAnexo" name="formularioAnexo">
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
    $(function(){
        $('#claid').change(function(){
            $.ajax({
                url: '?modulo=principal/monitorar-ppa&acao=A&req=carregarMedida&claid=' + $(this).val(),
                dataType: 'json',
                success: function(retorno){
                    $('#span-medida').html(retorno.select);
                    if(retorno.medida == 't'){
                        $('#span-medida').show();
                    } else {
                        $('#span-medida').hide();
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
            window.location.href = '?modulo=principal/monitorar-ppa&acao=A&suoid=' + $(this).val();
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

            $('#formulario').submit();
        });
        
        $('#btn_inserir_anexos').click(function(){
            abrirModalUpload();
        });

        // Evento de terminar de carregar arquivos
        Dropzone.options.formularioAnexo = {
            init: function() {
                
                this.on("success", function(file, response){
                    var jsonResponse = $.parseJSON(response);
                    inserirNovoAnexo(jsonResponse);
                });

                this.on("queuecomplete", function(file){

                    // Armazena o objeto Dropzone para chamar m�todos
                    objFormularioAnexo = this;
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
                        objFormularioAnexo.removeAllFiles();
                        // fecha modal ap�s a sele��o
                        $('#modal_upload').modal('hide');
                    });
                });
            }
        };
        
        $('#table_anexos').on('click', '.btnRemoverAnexos', function(){
            var id = $(this).attr('data-anexos');
            $('.tr_anexos_'+ id).remove();
        });
    });
    
    function abrirModalUpload() {
        $('.modal_dialog_upload').show();
        $('#modal_upload').modal();
        $('#modal_upload .chosen-container').css('width', '100%');
    }

    function inserirNovoAnexo(json){
        var trHtml = '<tr style="height: 30px;" class="tr_anexos_'+ json.arqid +'" >'
            + '                    <td style="text-align: left;"><a href="#" onclick="javascript:abrirArquivo('+ json.arqid+ '); return false;" >'+ json.arqnome +'</a></td>'
            + '                    <td style="text-align: left;">'+ json.arqdescricao +'</td>'
            + '                    <td style="text-align: center;">'
            + '                         <input type="hidden" value="'+ json.arqid +'" name="listaAnexos[]">'
            + '                         <span class="glyphicon glyphicon-trash btnRemoverAnexos link" title="Excluir o arquivo '+ json.arqnome+ '" data-anexos="'+ json.arqid +'" >'
            + '                    </td>'
            + '                </tr>'
        ;
        $('#table_anexos').append(trHtml);
    }
</script>