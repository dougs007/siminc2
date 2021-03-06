<?php

$tipoRelatorio = $_REQUEST['tipo_relatorio'] ? $_REQUEST['tipo_relatorio'] : array();
$norelatorio = '';

$listaSubUnidades = buscarSuoidUsuario((object) array(
    'exercicio' => ($_REQUEST['filtro']['prsano']? $_REQUEST['filtro']['prsano']: $_SESSION['exercicio']),
    'usucpf' => $_SESSION['usucpf']
));

if(isset($_REQUEST['req'])){
    switch ($_REQUEST['req']) {
        case 'exibir':
            include $_REQUEST['tipo_relatorio']."/relatorio.inc";
            include APPRAIZ. 'includes/rodape_bootstrap_v3.inc';
        die;
        case 'xls':
            include $_REQUEST['tipo_relatorio']."/relatorio.inc";
            die;
        case 'carregar-combo-subunidade':
            $where = $_REQUEST['unoid']? "\n AND suo.unoid IN(". join($_REQUEST['unoid'], ','). ")": NULL;
            $stSql = "
                SELECT DISTINCT
                    suo.suoid AS codigo,
                    suo.suocod || ' - ' || suo.suonome AS descricao
                FROM public.vw_subunidadeorcamentaria suo
                WHERE
                    suo.suostatus = 'A'
                    AND suo.prsano = '". $_REQUEST['prsano']. "'
                    $where
                ORDER BY
                    descricao
            ";
            echo $simec->select(
                'filtro[suoid][]',
                'Subunidade',
                NULL,
                $stSql,
                NULL,
                ['input-size' => 9, 'label-size' => 2]
            );
            die();
        case 'carregar-combo-acao':
            $where = $_REQUEST['unoid']? "\n AND suo.unoid IN(". join($_REQUEST['unoid'], ','). ")": NULL;
            $where .= $_REQUEST['suoid']? "\n AND suo.suoid IN(". join($_REQUEST['suoid'], ','). ")": NULL;
            $stSql = "
                SELECT DISTINCT
                    acao.acaid AS codigo,
                    prgcod || ' - ' || acacod || ' - ' || acaobjetivocod || ' - ' || loccod || ' - ' || acatitulo AS descricao
                FROM monitora.acao acao
                    JOIN public.vw_subunidadeorcamentaria suo ON(
                        suostatus = 'A'
                        AND acao.unicod = suo.unocod
                        AND suo.prsano = prgano
                    )
                WHERE
                    acastatus = 'A'
                    AND prgano = '". $_REQUEST['prsano']. "'
                    $where
                ORDER BY
                    descricao
            ";
            echo $simec->select(
                'filtro[acaid][]',
                'A��o',
                NULL,
                $stSql,
                NULL,
                ['input-size' => 9, 'label-size' => 2]
            );
            die();
        case 'carregar-combo-funcional':
            $where = $_REQUEST['unoid']? "\n AND suo.unoid IN(". join($_REQUEST['unoid'], ','). ")": NULL;
            $where .= $_REQUEST['suoid']? "\n AND suo.suoid IN(". join($_REQUEST['suoid'], ','). ")": NULL;
            $where .= $_REQUEST['acaid']? "\n AND ptr.acaid IN(". join($_REQUEST['acaid'], ','). ")": NULL;
            $stSql = "
                SELECT DISTINCT
                    ptr.ptrid codigo,
                    coalesce(ptr.prgcod, '') || ' - ' || coalesce(ptr.acacod, '') || ' - ' || coalesce(ptr.loccod, '') || ' - ' || coalesce(ptr.acaobjetivocod, '') || ' - ' || coalesce(ptr.plocod, '') || ' - ' || ptr.acatitulo || ' - ' || ptr.plodsc descricao
                FROM monitora.vw_ptres ptr
                    JOIN public.vw_subunidadeorcamentaria suo ON(
                        suostatus = 'A'
                        AND ptr.unicod = suo.unocod
                        AND suo.prsano = ptr.ptrano
                    )
                WHERE
                    ptr.ptrstatus = 'A'
                    AND ptr.ptrano = '". $_REQUEST['prsano']. "'
                    $where
                ORDER BY
                    descricao
            ";
            echo $simec->select(
                'filtro[ptrid][]',
                'Funcional',
                NULL,
                $stSql,
                NULL,
                ['input-size' => 9, 'label-size' => 2]
            );
            die();
        case 'salvar-relatorio':
            $cConsultaRelatorio = new Acompanhamento_Controller_ConsultaRelatorio();
            $cConsultaRelatorio->salvar($_REQUEST);
            die;
        case 'excluir-relatorio':
            $cConsultaRelatorio = new Acompanhamento_Controller_ConsultaRelatorio();
            $cConsultaRelatorio->excluirRelatorio($_REQUEST['crid']);
            die;              
        case 'seleciona-relatorio':
            $cConsultaRelatorio = new Acompanhamento_Controller_ConsultaRelatorio();
            $retConsultaRelatorio = $cConsultaRelatorio->consultarRelatorio($_REQUEST['crid']);
            $tipoRelatorio = $_REQUEST['tipo_relatorio'];
            $crid = $_REQUEST['crid'];
            $norelatorio = $retConsultaRelatorio['consulta'];          
    }
}

if ($_REQUEST['crid']){
    $cConsultaRelatorio = new Acompanhamento_Controller_ConsultaRelatorio();
    $retConsultaRelatorio = $cConsultaRelatorio->consultarRelatorio($_REQUEST['crid']);
    $tipoRelatorio = $retConsultaRelatorio['consulta']['tprel'];
    $crid = $_REQUEST['crid'];
    $norelatorio = $retConsultaRelatorio['consulta']['norelatorio'];    
    foreach($retConsultaRelatorio['valores'] as $key=>$value){
        $$key = $value;
    }
}

include APPRAIZ . 'includes/AgrupadorBootstrap.php';

/**
 * Cabe�alho padr�o do sistema.
 */
include APPRAIZ . "includes/cabecalho.inc";
?>

<script language="javascript" type="text/javascript" src="../includes/agrupadorBootstrap.js"></script>

<div class="row wrapper border-bottom white-bg page-heading">
    <div class="col-lg-12">
        <h2><?php echo $titulo_modulo; ?></h2>
    </div>
</div>

<form action="" method="post" name="filtro" class="form-horizontal">
    <div class="wrapper wrapper-content animated fadeInRight">
        <div class="row">
            <div class="col-md-12">
                <div class="ibox float-e-margins">
                    <div class="ibox-title">
                        <h5 style="margin: 8px 0 7px;">Relat�rio:</h5>
                            <?php
                                $preenchidos = $tipoRelatorio? $tipoRelatorio: array();
                                $base = array(
                                    'proposta' => 'Relat�rio de Propostas',
                                    'emendas'=> 'Relat�rio de Benefici�rios/Emenda',
                                    'pre-pi' => 'Relat�rio de Pr�-PA',
                                    'pi' => 'Relat�rio de PA',
                                    'pi-fnc' => 'Relat�rio de PA do FNC',
                                    'funcional' => 'Relat�rio de Funcionais',
                                );
                                echo $simec->select('tipo_relatorio', '', $preenchidos, $base);
                            ?>
                    </div>
                </div>
            </div>
        </div>

        <div class="row">
            <div class="col-md-12">
                <div class="ibox float-e-margins">
                    <div class="ibox-title">
                        <h5 style="margin: 8px 0 7px;">Consultas Salvas:</h5>
                            <input type="hidden" id='norelatorio' name='norelatorio' value="<?php echo $norelatorio;?>">
                            <?php
                                $preenchidos = $_REQUEST['crid']? $_REQUEST['crid']: array();
                                $sql = "select crid as codigo, norelatorio as descricao from acompanhamento.consulta_relatorio";
                                echo $simec->select('crid', '', $preenchidos, $sql);
                            ?>
                    </div>
                </div>
            </div>
        </div>
        
        <div class="row">
            <div class="col-md-12">
                <div class="ibox float-e-margins div_form_rel">

                    <?php
                        switch ($tipoRelatorio) {
                            case 'emendas':
                                include_once APPRAIZ. 'acompanhamento/modulos/relatorio/emendas/relatorio_form.inc';
                            break;
                            case 'proposta':
                                include_once APPRAIZ. 'acompanhamento/modulos/relatorio/proposta/relatorio_form.inc';
                            break;
                            case 'pre-pi':
                                include_once APPRAIZ. 'acompanhamento/modulos/relatorio/pre-pi/relatorio_form.inc';
                            break;
                            case 'funcional':
                                include_once APPRAIZ. 'acompanhamento/modulos/relatorio/funcional/relatorio_form.inc';
                            break;
                            case 'pi-fnc':
                                include_once APPRAIZ. 'acompanhamento/modulos/relatorio/pi-fnc/relatorio_form.inc';
                            break;
                            case 'pi':
                                include_once APPRAIZ. 'acompanhamento/modulos/relatorio/pi/relatorio_form.inc';
                            break;
                        }
                    ?>

                </div>
            </div>        
        </div>
        <div class='ibox-content'>
            <div class="text-center">
                <a class="btn-success btn btn-md" href="javascript:exibeRelatorioGeral('exibir');"><i class="fa fa-eye"></i> Visualizar</a>
                <a class="btn btn-primary btn-buscar" href="javascript:exibeRelatorioGeral('xls');"><i class="fa fa-file-excel-o"></i> Exportar XLS</a>
                <a class="btn btn-warning btn-buscar" href="javascript:salvarConsulta();"><i class="fa fa-check"></i> Salvar Consulta</a>
                <?php if ($_REQUEST['crid']){?>
                    <a class="btn btn-danger btn-buscar" href="javascript:excluirConsulta();"><i class="fa fa-check"></i> Excluir Consulta</a>
                <?php } ?>
            </div>                
        </div>

    </div>
</form>

<script>

    $(document).ready(function(){

        $("#tipo_relatorio").change(function(){
            document.filtro.target = "";
            $("#req").val("");
            $("#crid").val('');
            $("#norelatorio").val('');
            document.filtro.submit();
        });

        $("#crid").change(function(){
            document.filtro.action = '?modulo=relatorio/relatorio_principal_form&acao=A';
            document.filtro.target = "";
            if ($(this).val()!=''){
                $("#req").val("seleciona-relatorio");
            }else{
                $("#req").val("");
            }
            document.filtro.submit();

        });
        
        $("#filtro-prsano").change(function(){
            document.filtro.target = "";
            $("#req").val("");
            document.filtro.submit();
        });
  
        $('.div_form_rel').on('change', '[name="filtro[unoid][]"]', function(){
            carregarComboSubunidade();
            carregarComboAcao();
            carregarComboFuncional();
        });
        
        $('.div_form_rel').on('change', '[name="filtro[suoid][]"]', function(){
            carregarComboAcao();
            carregarComboFuncional();
        });
        
        $('.div_form_rel').on('change', '[name="filtro[acaid][]"]', function(){
            carregarComboFuncional();
        });

        $('.div_form_rel').on('change', '[name="filtro[suoid][]"]', function(){
            carregarComboAcao();
        });

    });
    
    function exibeRelatorioGeral(tipo) {
        
        if (document.filtro.coluna.length==0){
            swal('Aten��o!', 'Selecione pelo menos uma coluna para exibir o relat�rio!', 'warning');
            return;
        }
        var formulario = document.filtro;

        selectAllOptions(formulario.agrupador);
        selectAllOptions(formulario.naoAgrupador);
        selectAllOptions(formulario.coluna);
        selectAllOptions(formulario.naoColuna);
        var largura = $(window).width();
        $("#req").val(tipo);
        if (tipo == 'xls') {
            formulario.action = '?modulo=relatorio/relatorio_principal_form&acao=A';
        } else if (tipo == 'exibir') {
            formulario.action = '?modulo=relatorio/relatorio_principal_form&acao=A';
            window.open('', 'relatorio', 'width='+largura+',height=750,status=1,menubar=1,toolbar=0,scrollbars=yes,resizable=1');
            formulario.target = 'relatorio';

        }

        formulario.submit();
    }

    /**
     * Carrega novo conte�do para a op��es de Sub-Unidade via requisi��o ajax.
     * 
     * @return VOID
     */
    function carregarComboSubunidade() {
        $.ajax({
            dataType: "html",
            url: '?modulo=relatorio/relatorio_principal_form&acao=A',
            data: {
                req: 'carregar-combo-subunidade',
                prsano: $('[name="filtro[prsano]"]').val(),
                unoid: $('[name="filtro[unoid][]"]').val()
            },
            success: function(response) {
                $('.div_suoid').remove('slow');
                $('.div_suoid').html(response);
                $(".chosen-select").chosen();
            }
        });
    }

    /**
     * Carrega novo conte�do para a op��es de A��es via requisi��o ajax.
     *
     * @return VOID
     */
    function carregarComboAcao() {
        $.ajax({
            dataType: "html",
            url: '?modulo=relatorio/relatorio_principal_form&acao=A',
            data: {
                req: 'carregar-combo-acao',
                prsano: $('[name="filtro[prsano]"]').val(),
                unoid: $('[name="filtro[unoid][]"]').val(),
                suoid: $('[name="filtro[suoid][]"]').val()
            },
            success: function(response) {
                $('.div_acaid').empty();
                $('.div_acaid').html(response);
                $(".chosen-select").chosen();
            }
        });
    }
    
    /**
     * Carrega novo conte�do para a op��es de Funcionais via requisi��o ajax.
     * 
     * @return VOID
     */
    function carregarComboFuncional() {
        $.ajax({
            dataType: "html",
            url: '?modulo=relatorio/relatorio_principal_form&acao=A',
            data: {
                req: 'carregar-combo-funcional',
                prsano: $('[name="filtro[prsano]"]').val(),
                unoid: $('[name="filtro[unoid][]"]').val(),
                suoid: $('[name="filtro[suoid][]"]').val(),
                acaid: $('[name="filtro[acaid][]"]').val()
            },
            success: function(response) {
                $('.div_ptrid').remove('slow');
                $('.div_ptrid').html(response);
                $(".chosen-select").chosen();
            }
        });
    }

    function salvarConsulta(){
        var formulario = document.filtro;
        document.filtro.target = "";
        selectAllOptions(formulario.coluna);
        $("#req").val("salvar-relatorio");
        if ($("#norelatorio").val()==''){
            swal({
                title: $("#tipo_relatorio option:selected").text(),
                text: "Digite o nome da consulta",
                type: "input",
                showCancelButton: true,
                closeOnConfirm: false,
                confirmButtonText: 'Confirmar',
                cancelButtonText: 'Cancelar',
                animation: "slide-from-top",
                inputPlaceholder: ""
              },
              function(inputValue){
                if (inputValue === false) return false;

                if (inputValue === "") {
                  swal.showInputError("Favor digitar o nome da consulta!");
                  return false;
                }
                $("#norelatorio").val(inputValue);
                formulario.action = '?modulo=relatorio/relatorio_principal_form&acao=A';
                formulario.submit();
              });
        }else{
            formulario.action = '?modulo=relatorio/relatorio_principal_form&acao=A';
            formulario.submit();              
        }

    }

    function excluirConsulta(){
        var formulario = document.filtro;
        $("#req").val("excluir-relatorio");
        swal({
            title: $("#tipo_relatorio option:selected").text(),
            text: "Deseja Realmente Excluir essa consulta?",
            icon: "warning",
            showCancelButton: true,
            closeOnConfirm: true,
            confirmButtonText: 'Confirmar',
            cancelButtonText: 'Cancelar',
            animation: "slide-from-top"
        },function(isConfirm){
                if (isConfirm){
                    formulario.action = '?modulo=relatorio/relatorio_principal_form&acao=A';
                    formulario.submit();
                }else{
                    return false;    
                }
        });

    }

</script>
