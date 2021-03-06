<?php
include_once APPRAIZ . "monitora/classes/Pi_PlanoInterno.class.inc";

$listaPerfis = pegaPerfilGeral();

$cAcompanhamento = new Acompanhamento_Controller_Acompanhamento();
switch ($_REQUEST['req']) {
    case 'salvar':
        $_REQUEST['url'] = '?modulo=principal/monitorar-planejamento-estrategico&acao=A';
        $cAcompanhamento->salvar($_REQUEST);
        die;
    case 'excluir':
        $cAcompanhamento->excluir($_REQUEST['acoid']);
        die;
    case 'detalhe-pi':
        $params = new stdClass();
        $params->tipo = 'meta-unidade';
        $params->meuid = $_REQUEST['meuid'];
        $params->suoid = $_REQUEST['suoid'];
        $cAcompanhamento->recuperarPiPorMetaESubunidade($params);
        die;
    case 'ver-historico':
        $cAcompanhamento->recuperarHistorico($_REQUEST['acoid']);
        die;
    case 'carregarMedida':
        $mClassificacao = new Acompanhamento_Model_Classificacao($_REQUEST['claid']);
        $retorno['medida'] = $mClassificacao->clamedida;
        $listaMedidas = $db->carregar((new Acompanhamento_Model_Medida())->recuperarSqlCombo(null, ['claid = ' . (int)$_REQUEST['claid']]));
        $listaMedidasUtf8 = array();
        if($listaMedidas){
            foreach ($listaMedidas as $medida){
                $listaMedidasUtf8[$medida['codigo']] = utf8_encode($medida['descricao']);
            }
        }
        $retorno['select'] = $simec->select('medidas[]', 'Medidas a serem adotadas', null, $listaMedidasUtf8);
        echo json_encode($retorno);
        die;
    case 'uploadAnexo':
        $_FILES['file']['name']   = utf8_decode($_FILES['file']['name']);
        $_REQUEST['arqdescricao'] = utf8_decode($_REQUEST['arqdescricao']);
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

$mAcompanhamento = new Acompanhamento_Model_Acompanhamento($_REQUEST['acoid']);

// Verificando qual a janela e se a janela permite editar ou n�o
$janid = $mAcompanhamento->janid ? $mAcompanhamento->janid : $_REQUEST['janid'];


if(!$janid){
    $janela = (new Acompanhamento_Model_Janela())->recuperarJanelaAtiva(Acompanhamento_Model_Tipo::K_TIPO_META_UNIDADE);
    $janid = $janela['janid'];
}

$mJanela = new Acompanhamento_Model_Janela($janid);

$podeEditar = in_array(PFL_CONSULTA, $listaPerfis)? 0:($mJanela->isAtual() == 't'?1 :0);

// Recuperando Meta Unidade Selecionada
$meuid = $mAcompanhamento->meuid ? $mAcompanhamento->meuid : $_REQUEST['meuid'];

// Recuperando SubUnidade
$suoid = $mAcompanhamento->suoid ? $mAcompanhamento->suoid : $_REQUEST['suoid'];

$listaDeAnexos = (new Acompanhamento_Model_AcompanhamentoArquivo())->buscarPorAcompanhamento($mAcompanhamento->acoid);

include APPRAIZ . "includes/cabecalho.inc";
?>
<script src="js/principal/acompanhamento.js?v=1"></script>

<script src="../library/liquify/snap.svg.js"></script>
<script src="../library/liquify/liquid.meter.js"></script>

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
        <div class="col-md-12">

            <div class="ibox float-e-margins">
                <div class="ibox-title">
                    <div class="row">
                        <div class="col-sm-2">
                            <h5>Metas Unidade</h5>
                        </div>
                        <div class="col-sm-10">
                            <div style="float: right;">
                                <div class="box-legenda">
                                    Legenda:
                                </div>
                                <div class="box-legenda red-bg">
                                    Pendente
                                </div>
                                <div class="box-legenda navy-bg">
                                    Preenchida
                                </div>
                                <div class="box-legenda blue-bg">
                                    Selecionada
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="ibox-content">
                    <div class="row form-horizontal">

                        <?php
                        $aMetas = $mAcompanhamento->recuperarMetasPlanejamentoEstrategico($suoid);
                        $aUnidades = (new Public_Model_SubUnidadeOrcamentaria())->recuperarPorUsuario();
                        $infoMeta = (new Planacomorc_Model_MetaUnidade($meuid))->recuperarInformacoes();
                        $dto = ['meuid' => $meuid, 'suoid' => $suoid];
                        $infoPI = (new Pi_PlanoInterno())->recuperarResumoPorMetaESubunidade((object)$dto);
                        $dadosGrafico = [];
                        if(count($infoPI)){
                            foreach ($infoPI as $key => $valor) {
                                if(in_array($key, ['previsto', 'provisionado', 'empenhado', 'liquidado', 'pago'])){
                                    $dadosGrafico[$key]['descricao'] = ucfirst($key);
                                    $dadosGrafico[$key]['valor'] = $valor;
//                                    $dadosGrafico[$key]['categoria'] = $infoMeta['mppcod'];
                                }
                            }
                        }
                        ?>

                        <div class="col-sm-6">
                            <?= $simec->select('suoid', 'Unidade', $suoid, $aUnidades, null, ['label-size' => 2]); ?>
                        </div>

                        <div class="clearfix"></div>

                        <?php foreach($aMetas as $meta){
                            $cor = $meta['acoid'] ? 'navy-bg' : 'red-bg';
                            $cor = $meuid == $meta['meuid'] ? 'blue-bg' : $cor;
                            $urlAcompanhamento = $meta['acoid'] ? "?modulo=principal/monitorar-planejamento-estrategico&acao=A&acoid={$meta['acoid']}" : "?modulo=principal/monitorar-planejamento-estrategico&acao=A&meuid={$meta['meuid']}&suoid={$suoid}";
                        ?>
                            <a class="selecionar-meta" href="<?= $urlAcompanhamento; ?>">
                                <div class="col-sm-4 col-md-3" title="<?= $meta['meuid'] . ' - ' . $meta['meunome']; ?>">
                                    <div data-cor="<?= $cor ?>" class="widget div-meta <?= $cor ?>">
                                        <div class="row">
                                            <div class="col-xs-12">
                                                <span><?= substr($meta['meunome'], 0, 50); ?>...</span>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </a>
                        <?php } ?>

                        <div class="clearfix"></div>

                        <?php if($meuid){ ?>
                            <hr />
                            <div class="col-md-5 no-margin-bottom">
                                <?php
                                $compartilhada =  $infoMeta['compartilhada'] == 't' ? ' <i style="font-size: 15px; color: #6892ff;" class="fa fa-handshake-o link" title="Meta Compartilhada com outras Subunidades."></i>' : '';

                                $simec->setPodeEditar(0);

                                $janinicio = Simec_Util::formatarData($mJanela->janinicio, 'dd/MM/YYYYY');
                                $janfim = Simec_Util::formatarData($mJanela->janfim, 'dd/MM/YYYYY');

                                echo $simec->input('Refer�ncia', 'Refer�ncia', "{$mJanela->jandsc} ({$janinicio} - {$janfim})");
                                echo $simec->input('Objetivo', 'Objetivo Estrat�gico', "{$infoMeta['obenome']}");
                                echo $simec->input('Dimensao', 'Dimensao Estrat�gica', "{$infoMeta['dimenome']}");
                                echo $simec->input('Meta', 'Meta Estrat�gica', "{$infoMeta['meunome']} {$compartilhada}");
                                echo $simec->input('Previsto', 'Quantidade Prevista', number_format($infoMeta['meuquantidade'], 2, ',', '.'));
                                if ($infoMeta['mppanualizavel'] == 't') {
                                    echo $simec->input('Previstoa', 'Previsto Anualizado', number_format($infoMeta['meuquantidadeanualizada'], 2, ',', '.'));
                                }
                                echo $simec->input('qtd_pis', "Planos de A��o (PA's)", '<a class="detalhe-pi" title="PA\'s Vinculados" href="?modulo=principal/monitorar-planejamento-estrategico&acao=A&req=detalhe-pi&meuid=' . $meuid . '&suoid=' . $suoid . '">' . number_format($infoPI['qtd'], 0, ',', '.') . '</a>');
                                $simec->setLabelSize(3);
                                $simec->setPodeEditar(1);
                                ?>

                            </div>
                            <div class="col-md-5">
                                <h3 class="text-center">PAs associados � Meta</h3>
                                <?php
                                $colors = "'#55BF3B', '#eeaaee', '#00BFFF', '#aaeeee', '#7798BF', '#DDDF0D', '#7CCD7C', '#DF5353', '#008000', '#CD0000', '#FF4500', '#ff0066', '#4B0082', '#808000', '#800000', '#2F4F4F', '#006400', '#FFA500'";
                                $grafico = new Grafico(Grafico::K_TIPO_COLUNA, false);
                                $grafico->setFormatoTooltip(Grafico::K_TOOLTIP_DECIMAL_0)
                                    ->setColors($colors)
                                    ->setHeight('250px')
                                    ->gerarGrafico($dadosGrafico);
                                ?>
                            </div>
                            <div class="col-sm-2">
                                <?php $percentual = $infoPI['previsto'] ? $infoPI['empenhado'] * 100 / $infoPI['previsto'] : 0; ?>
                                <h3 class="text-center">Percentual de Empenho</h3>
                                <meter style="display: none;" max="1000" value="<?php echo $percentual; ?>" id="percentual-empenhado"></meter>
                            </div>
                        <?php } ?>
                    </div>
                </div>
            </div>

        </div>

        <?php if($meuid){
            $simec->setPodeEditar($podeEditar);

            if($podeEditar){ ?>
                <form id="formulario" name="formulario" method="post" class="form-horizontal">
                <input type="hidden" name="req" id="req" value="salvar" />
                <input name="suoid" type="hidden" value="<?php echo $suoid; ?>">
                <input name="meuid" id="meuid" type="hidden" value="<?php echo $meuid; ?>">
                <input name="janid" id="janid" type="hidden" value="<?php echo $mJanela->janid; ?>">
                <input name="acoid" id="acoid" type="hidden" value="<?php echo $mAcompanhamento->acoid; ?>">
            <?php } ?>
            <div class="col-md-8">
                <div class="ibox float-e-margins">
                    <div class="ibox-title">
                        <h5>
                            Monitoramento da Meta
                            <?php if($mAcompanhamento->acoid){ ?>
                                <a style="margin-left: 10px;" class="fa fa-history detalhe-pi" title="Hist�rico de altera��es" href="?modulo=principal/monitorar-planejamento-estrategico&acao=A&req=ver-historico&acoid=<?php echo $mAcompanhamento->acoid; ?>"></a>
                            <?php } ?>
                        </h5>
                    </div>
                    <div class="ibox-content">

                        <div class="form-group ">
                            <label for="acoquantidade" class="col-sm-3 col-md-3 col-lg-3 control-label" title="Valor apurado para a meta considerando sua respectiva unidade de medida, cumulativo desde o in�cio do PPA.">Quantidade Alcan�ada: <span class="campo-obrigatorio" title="Campo obrigat�rio">*</span></label>
                            <div class="col-sm-3 col-md-3 col-lg-3 ">
                                <?php $acoquantidade = is_numeric($mAcompanhamento->acoquantidade) ? number_format($mAcompanhamento->acoquantidade, 2, ',', '.') : null; ?>
                                <?php if($podeEditar){ ?>
                                    <input name="acoquantidade" id="acoquantidade" type="text" class="form-control valor" value="<?php echo $acoquantidade; ?>" required="required" title="Valor apurado para a meta considerando sua respectiva unidade de medida, cumulativo desde o in�cio do PPA.">
                                <?php } else { ?>
                                    <p class="form-control-static" id="acoquantidade" title="Valor apurado para a meta considerando sua respectiva unidade de medida, cumulativo desde o in�cio do PPA.">
                                        <?php echo $acoquantidade; ?>
                                    </p>
                                <?php } ?>

                            </div>
                            <label for="acodata" class="col-sm-2 col-md-2 col-lg-2 control-label">Dt. Refer�ncia: <span class="campo-obrigatorio" title="Campo obrigat�rio">*</span></label>
                            <div class="col-sm-4 col-md-4 col-lg-4 <?php echo $podeEditar ? 'date' : '' ; ?>">
                                <div class="input-group">
                                    <?php if($podeEditar){ ?>
                                        <span class="input-group-addon"><span class="fa fa-calendar"></span></span>
                                        <input name="acodata" id="acodata" type="text" value="<?php echo Simec_Util::formatarData($mAcompanhamento->acodata, Zend_Date::DATES); ?>" class="datemask form-control" required="required">
                                    <?php } else { ?>
                                        <p class="form-control-static" id="acodata"><?php echo Simec_Util::formatarData($mAcompanhamento->acodata, Zend_Date::DATES); ?></p>
                                    <?php } ?>

                                </div>
                            </div>
                            <div style="clear:both"></div>
                        </div>

                        <?php
                        echo '<span title="Avalia��o da execu��o da meta, quantificando, sempre que poss�vel, o valor alcan�ado acumulado para o per�odo do Plano, destacando-se, em especial, o executado no ano corrente e a proje��o para o ano seguinte, o motivo da frustra��o ou da supera��o da expectativa, as necessidades existentes para que a meta seja atendida, e/ou outras informa��es pactuadas.">';
                        echo $simec->textarea('acoanalise', 'An�lise Situacional', $mAcompanhamento->acoanalise, ['title' => 'Avalia��o da execu��o da meta, quantificando, sempre que poss�vel, o valor alcan�ado acumulado para o per�odo do Plano, destacando-se, em especial, o executado no ano corrente e a proje��o para o ano seguinte, o motivo da frustra��o ou da supera��o da expectativa, as necessidades existentes para que a meta seja atendida, e/ou outras informa��es pactuadas.'
                            ,'rows'=>6]);
                        echo '</span>';

                        echo '<span title="Classifica��o da meta quanto ao seu andamento.">';
                        echo $simec->select('claid', 'Classifica��o da Meta', $mAcompanhamento->claid, (new Acompanhamento_Model_Classificacao())->recuperarSqlCombo(null, ['tipid = ' . Acompanhamento_Model_Tipo::K_TIPO_META_PPA]), ['title' => 'Classifica��o da meta quanto ao seu andamento.','required']);
                        echo '</span>';

                        $aMedidasSelecionadas = $mAcompanhamento->recuperarMedidas();
                        echo '<span class="span-medida" id="span-medida" ' . (!count($aMedidasSelecionadas) ? 'style="display: none"' : '') . '>' . $simec->select('medidas[]', 'Medidas a serem adotadas', $aMedidasSelecionadas, (new Acompanhamento_Model_Medida())->recuperarSqlCombo(null, ['claid = ' . (int)$mAcompanhamento->claid])) . '</span>';
                        echo '<span class="span-medida" ' . (!count($aMedidasSelecionadas) ? 'style="display: none"' : '') . '>' . $simec->textarea('acoprovidencias', 'Detalhamento das provid�ncias a serem adotadas', $mAcompanhamento->acoprovidencias, ['rows'=>6]) . '</span>';
                        ?>

                        <div class="form-group">
                            <div class="text-center">
                                <?php if($podeEditar){ ?>
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

                        <?php if($podeEditar){ ?>
                            <div class="form-group">
                                <div class="text-center">
                                    <input type="button" id="btn_inserir_anexos" title="Inserir Anexos" value="Inserir Anexos" class="btn btn-info"/>
                                </div>
                            </div>
                        <?php } ?>

                    </div>
                </div>
            </div>
            <?php if($podeEditar){ ?>
                </form>
            <?php } ?>
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
                        <form class="dropzone" method="POST" enctype="multipart/form-data" action="acompanhamento.php?modulo=principal/monitorar-planejamento-estrategico&acao=A&acoid=<?php echo $mAcompanhamento->acoid; ?>&aba=1&req=uploadAnexo" id="formularioAnexoMonitoramento" name="formularioAnexoMonitoramento">
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
                url: '?modulo=principal/monitorar-planejamento-estrategico&acao=A&req=carregarMedida&claid=' + $(this).val(),
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
            window.location.href = '?modulo=principal/monitorar-planejamento-estrategico&acao=A&suoid=' + $(this).val();
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
        Dropzone.options.formularioAnexoMonitoramento = {
            init: function() {

                this.on("success", function(file, response){
                    var jsonResponse = $.parseJSON(response);
                    inserirNovoAnexo(jsonResponse);
                });

                this.on("queuecomplete", function(file){

                    // Armazena o objeto Dropzone para chamar m�todos
                    formularioAnexoMonitoramento = this;
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
                        formularioAnexoMonitoramento.removeAllFiles();
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