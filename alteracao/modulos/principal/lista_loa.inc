<?php
$req = '<span style="color: #ff0000">*</span>';
$linha = '<table id="tbListaLoa" class="table table-striped table-bordered table-hover" >
        <tr class="text-center">';
            if ($podeEditar):
                $linha .= '<th width="10%">A��o</th>';
            endif;
$linha .= '<th class="tdpliselid">Funcional'.$req.'</th>
            <th>Categoria'.$req.'</th>
            <th>GND'.$req.'</th>
            <th><span title="Modalidade de Aplica��o">Mod'.$req.'</span></th>
            <th>Fonte'.$req.'</th>
            <th>IDOC'.$req.'</th>
            <th>IDUSO'.$req.'</th>
            <th>RP'.$req.'</th>
            <th>Dota��o</th>
            <th>Cancelado</th>
            <th>Suplementar</th>
            <th>Suplementar por excesso</th>
            <th>Suplementar por Super�vit</th>
        </tr>';

            $loas = (new Alteracao_Model_RemanejamentoLoa())->recuperarTodosPorPedido($_REQUEST['pedid']);
            foreach($loas as $loa){
                if ($podeEditar):
                $linha .= '<tr class="text-center">
                              <td width="5% ">
                                  <a href="#" class="btnRemoverLoa" id="btnRemoverLoa" title="Excluir registro" rlid="'.$loa['rlid'].'"><i style="font-weight: 20px" class="fa fa-close"></i></a>&nbsp;&nbsp;&nbsp;
                                  <a href="#" class="btnSalvarLoa" id="btnSalvarLoa" title="Salvar registro" rlid="'.$loa['rlid'].'"><i class="fa fa-check"></i></a>
                              </td>';
                endif;
                $linha .= '<td class="combo" style="vertical-align: middle">';

                    if($podeEditar):
                        $linha .= '<input type="hidden" id="unicod'.$loa['rlid'].'" name="unicod" value="'.$loa['unicod'].'">';
                                $options = (new Alteracao_Model_RemanejamentoLoa())->recuperaFuncionalSelecionada($_REQUEST['pedid'], $_SESSION['exercicio']);
                        $linha .= montaListaLoa('ptrid',$options, $loa['ptrid'], $loa['rlid'], 'SelecionaPtrid(this, '.$loa['rlid'].');');
                    else:
                        $linha .= $loa['funcional'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo" style="vertical-align: middle">';
                    if($podeEditar):
                            $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboCategoria();
                    $linha .= montaListaLoa('ctecod', $options, $loa['ctecod'], $loa['rlid'], 'SelecionaDotacao('.$loa['rlid'].');');
                    else:
                        $linha .= $loa['ctecod'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo" style="vertical-align: middle">';
                    if($podeEditar):
                            $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboGND();
                    $linha .= montaListaLoa('gndcod', $options, $loa['gndcod'], $loa['rlid'], 'SelecionaDotacao('.$loa['rlid'].');');
                    else:
                        $linha .= $loa['gndcod'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo" style="vertical-align: middle">';
                    if($podeEditar):
                            $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboModalidade();
                    $linha .= montaListaLoa('mapcod', $options, $loa['mapcod'], $loa['rlid'], 'SelecionaDotacao('.$loa['rlid'].');', 'Modalidade de Aplica��o');
                    else:
                        $linha .= $loa['mapcod'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo" style="vertical-align: middle">';
                    if($podeEditar):
                        $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboFonte();
                        $linha .= montaListaLoa('fonid', $options, $loa['fonid'], $loa['rlid']);
                    else:
                        $linha .= $loa['foncod'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo" style="vertical-align: middle">';
                    if($podeEditar):
                        $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboIdoc();
                        $linha .= montaListaLoa('idoid', $options, $loa['idoid'], $loa['rlid']);
                    else:
                        $linha .= $loa['idocod'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo" style="vertical-align: middle">';
                    if($podeEditar):
                            $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboIduso();
                            $linha .= montaListaLoa('iduid', $options, $loa['iduid'], $loa['rlid']);
                    else:
                        $linha .= $loa['iducod'];
                    endif;
                $linha .= '</td>';
                $linha .= '<td class="combo">';
                if($podeEditar):
                    $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboRP();
                    $linha .= montaListaLoa('rpcod', $options, $loa['rpcod'], $loa['rlid']);
                else:
                    $linha .= $loa['rpcod'];
                endif;
                $linha .= '</td>';
                $linha .= '         <td class="combo" style="vertical-align: middle" id="vlDotacao'.$loa['rlid'].'">'.number_format($loa['vldotacao'],0,',','.').'</td>';
                $linha .=           '<td class="combo" style="vertical-align: middle">';
                                    if($podeEditar){
                                        $linha .= '<input type="text" id="vlCancelado'.$loa['rlid'].'" name="vlCancelado" rlid="'.$loa['rlid'].'" value="'.$loa['vlcancelado'].'" size="15" maxlength="15" class="form-control input_valor_remanejamento">';
                                    }else{
                                        $linha .= number_format($loa['vlcancelado'], 0, ',','.');
                                    }
                $linha .=           '</td>';
                $linha .= '         <td class="combo" style="vertical-align: middle">';
                                    if($podeEditar){
                                        $linha .= '<input type="text" id="vlSuplementar'.$loa['rlid'].'" name="vlSuplementar" rlid="'.$loa['rlid'].'" value="'.$loa['vlsuplementar'].'" size="15" maxlength="15" class="form-control input_valor_remanejamento">';
                                    }else{
                                        $linha .= number_format($loa['vlsuplementar'], 0, ',','.');
                                    }
                $linha .=           '</td>';
                $linha .=           '<td class="combo" style="vertical-align: middle">';
                                    if($podeEditar){
                                        $linha .= '<input type="text" id="vlSuplementarExcesso'.$loa['rlid'].'" name="vlSuplementarExcesso" rlid="'.$loa['rlid'].'" value="'.$loa['vlsuplementarexcesso'].'" size="15" maxlength="15" class="form-control input_valor_remanejamento">';
                                    }else{
                                        $linha .= number_format($loa['vlsuplementarexcesso'], 0, ',','.');
                                    }
                $linha .=           '</td>';
                $linha .=           '<td class="combo" style="vertical-align: middle">';
                                    if($podeEditar){
                                        $linha .= '<input type="text" id="vlSuplementarSuperavit'.$loa['rlid'].'" name="vlSuplementarSuperavit" rlid="'.$loa['rlid'].'" value="'.$loa['vlsuplementarsuperavit'].'" size="15" maxlength="15" class="form-control input_valor_remanejamento">';
                                    }else{
                                        $linha .= number_format($loa['vlsuplementarsuperavit'], 0, ',','.');
                                    }
                $linha .=           '</td>';
                $linha .= '     </tr>';
            }
$linha .= '</table>';
echo $linha;
        ?>
<script>
    $(function () {

        $('#btnloa').click(function () {
            $('#btnloa').attr('disabled', 'true');
            var tr = '<tr class="text-center">' +
                '        <th width="5% ">' +
                                 '<a href="#" class="btnRemoverLoa" id="btnRemoverLoa" title="Excluir registro" rlid=""><i style="font-weight: 20px" class="fa fa-close"></i></a>&nbsp;&nbsp;&nbsp;\n' +
                                 '<a href="#" class="btnSalvarLoa" id="btnSalvarLoa" title="Salvar registro" rlid=""><i class="fa fa-check"></i></a>' +
                         '</th>' +
                '        <th class="combo"> <input type="hidden" id="unicod" name="unicod">\n\
                             <?php $options = (new Alteracao_Model_RemanejamentoLoa())->recuperaFuncionalSelecionada($_REQUEST['pedid'], $_SESSION['exercicio']);
                                echo montaListaLoa('ptrid',$options, null, '', 'SelecionaPtrid(this, );');
                             ?> '+
                         '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboCategoria();
                               echo montaListaLoa('ctecod', $options, null, '',  'SelecionaDotacao();');
                           ?>'+
                        '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboGND();
                               echo montaListaLoa('gndcod', $options, null, '',  'SelecionaDotacao();');
                           ?>'+
                        '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboModalidade();
                               echo montaListaLoa('mapcod', $options, null, '',  'SelecionaDotacao();', 'Modalidade de Aplica��o');
                           ?>'+
                        '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboFonte();
                               echo montaListaLoa('fonid', $options);
                           ?>'+
                        '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboIdoc();
                               echo montaListaLoa('idoid', $options, '1');
                           ?>'+
                        '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboIduso();
                               echo montaListaLoa('iduid', $options, '6');
                           ?>'+
                        '</th>' +
                '        <th class="combo"><?php $options = (new Alteracao_Model_RemanejamentoLoa())->montaComboRP();
                               echo montaListaLoa('rpcod', $options);
                           ?>'+
                        '</th>' +
                '        <th id="vlDotacao" style="vertical-align: middle">-</th>' +
                '        <th><input type="text" id="vlSuplementar" name="vlSuplementar" rlid="" size="15" maxlength="15" class="form-control input_valor_remanejamento"></th>' +
                '        <th><input type="text" id="vlCancelado" name="vlCancelado" rlid="" size="15" maxlength="15" class="form-control input_valor_remanejamento"></th>' +
                '        <th><input type="text" id="vlSuplementarExcesso" name="vlSuplementarExcesso" rlid="" size="15" maxlength="15" class="form-control input_valor_remanejamento"></th>' +
                '        <th><input type="text" id="vlSuplementarSuperavit" name="vlSuplementarSuperavit" rlid="" size="15" maxlength="15" class="form-control input_valor_remanejamento"></th>' +
                '     </tr>';
            var tbody = $("#tbListaLoa > tbody");
            tbody.append(tr);
            $('.input_valor_remanejamento').keyup(function(){
                $(this).val(mascaraglobal('###.###.###.###', $(this).val()));
            }).keyup();   
            $(".btnSalvarLoa").click(function(){
                var rlid = $(this).attr('rlid');
                if(validaObrigatorio(rlid)) {
                    SalvarLoa(rlid);
                }
            });

            $(".chosen").chosen({
                placeholder_text_single: " "
            });

            $(".btnRemoverLoa").click(function(){
                var rlid = $(this).attr('rlid');
                swal({
                    title: "Cuidado!",
                    text: "Tem certeza que deseja excluir o registro ?",
                    type: "warning",
                    confirmButtonText: 'Sim',
                    cancelButtonText: 'N�o',
                    confirmButtonColor: "#DD6B55",
                    cancelButtonColor: "#DD6B55",
                    showCancelButton: true,
                    closeOnConfirm: true
                    },
                    function () {
                        if (rlid !== null && rlid !== '') {
                            RemoverLoa(rlid);
                        }else{
                            $(".div_remanejamento_loa").load('?modulo=principal/cadastro_alteracoes&acao=C&req=carrega_remanejamento_loa&pedid='+$("#pedid").val());
                        }
                    }
                );
            });

        });

        $(".chosen").chosen({
            placeholder_text_single: " "
        });

        $('.input_valor_remanejamento').keyup(function(){
            $(this).val(mascaraglobal('###.###.###.###', $(this).val()));
        }).keyup();

        $(".btnSalvarLoa").click(function(){
            var rlid = $(this).attr('rlid');

            if(validaObrigatorio(rlid)) {
                SalvarLoa(rlid);
            }
        });
        $(".btnRemoverLoa").click(function(){
            var rlid = $(this).attr('rlid');

            swal({
                    title: "Cuidado!",
                    text: "Tem certeza que deseja excluir o registro ?",
                    type: "warning",
                    confirmButtonText: 'Sim',
                    cancelButtonText: 'N�o',
                    confirmButtonColor: "#DD6B55",
                    cancelButtonColor: "#DD6B55",
                    showCancelButton: true,
                    closeOnConfirm: true
                },
                function(isConfirm){
                    if(isConfirm){
                        RemoverLoa(rlid);
                    }
                });

        });
    });

    function SalvarLoa(rlid){

        var ptrid = $("#ptrid"+rlid).val();
        var vlDotacao = acertaNumero($("#vlDotacao"+rlid).html());
        var vlSuplementar = acertaNumero($("#vlSuplementar"+rlid).val());
        var vlCancelado = acertaNumero($("#vlCancelado"+rlid).val());
        var vlSuplementarExcesso = acertaNumero($("#vlSuplementarExcesso"+rlid).val());
        var vlSuplementarSuperavit = acertaNumero($("#vlSuplementarSuperavit"+rlid).val());
        $.post('?modulo=principal/cadastro_alteracoes&acao=C&req=salvar_loa',
        {
            rlid: rlid,
            pedid: $("#pedid").val(),
            ptrid: $("#ptrid"+rlid).val(),
            ctecod: $("#ctecod"+rlid).val(),
            gndcod: $("#gndcod"+rlid).val(),
            mapcod: $("#mapcod"+rlid).val(),
            fonid: $("#fonid"+rlid).val(),
            idoid: $("#idoid"+rlid).val(),
            iduid: $("#iduid"+rlid).val(),
            rpcod: $("#rpcod"+rlid).val(),
            vlDotacao: vlDotacao,
            vlSuplementar: vlSuplementar,
            vlCancelado: vlCancelado,
            vlSuplementarExcesso: vlSuplementarExcesso,
            vlSuplementarSuperavit: vlSuplementarSuperavit
        },
            function(retorno){
                if (retorno){

                    swal({
                            title: "",
                            text: "Registro salvo com sucesso!",
                            type: "success",
                            confirmButtonText: 'Ok',
                            closeOnConfirm: true
                        },
                        function(){
                            $(".div_remanejamento_loa").load('?modulo=principal/cadastro_alteracoes&acao=C&req=carrega_remanejamento_loa&pedid='+$("#pedid").val());
                        })
                }else{
                    swal({
                        title: "",
                        text: "N�o foi poss�vel salvar o registro!",
                        type: "error"
                    })
                }
            }
        )
    }

    function RemoverLoa(rlid){
        $.post('?modulo=principal/cadastro_alteracoes&acao=C&req=remover_loa',
        {
            rlid: rlid
        },
            function(retorno){
                if (retorno){
                    $(".div_remanejamento_loa").load('?modulo=principal/cadastro_alteracoes&acao=C&req=carrega_remanejamento_loa&pedid='+$("#pedid").val());
                }
            }
        );        
    }

    function acertaNumero(num){
        if (num==''){
            num=0;
        }
        num = str_replace(['.', ','], ['', '.'],num);
        return num;
    }

    function validaObrigatorio(rlid) {

        var msg = '';

        if($('#ptrid'+rlid).val() == '' || $('#ptrid'+rlid).val() == null){
            msg += "O preenchimento do campo \"Funcional\" � obrigat�rio.\n";
        }
        if($('#ctecod'+rlid).val() == '' || $('#ctecod'+rlid).val() == null){
            msg += "O preenchimento do campo \"Categoria\" � obrigat�rio.\n";
        }
        if($('#gndcod'+rlid).val() == '' || $('#gndcod'+rlid).val() == null){
            msg += "O preenchimento do campo \"GND\" � obrigat�rio.\n";
        }
        if($('#mapcod'+rlid).val() == '' || $('#mapcod'+rlid).val() == null){
            msg += "O preenchimento do campo \"Modalidade\" � obrigat�rio.\n";
        }
        if($('#fonid'+rlid).val() == '' || $('#fonid'+rlid).val() == null){
            msg += "O preenchimento do campo \"Fonte\" � obrigat�rio.\n";
        }
        if($('#idoid'+rlid).val() == '' || $('#idoid'+rlid).val() == null){
            msg += "O preenchimento do campo \"IDOC\" � obrigat�rio.\n";
        }
        if($('#iduid'+rlid).val() == '' || $('#iduid'+rlid).val() == null){
            msg += "O preenchimento do campo \"IDUSO\" � obrigat�rio.\n";
        }
        if($('#rpcod'+rlid).val() == '' || $('#rpcod'+rlid).val() == null){
            msg += "O preenchimento do campo \"RP\" � obrigat�rio.\n";
        }

        if(msg !== '') {
            swal({
                title: "Aten��o!",
                text: msg,
                type: "warning"
            });
            return false;
        } else {
            return true;
        }

    }
    
    function SelecionaPtrid(ptrid, rlid){
        if (rlid==undefined){
            rlid='';
        }
        $.post('?modulo=principal/cadastro_alteracoes&acao=C&req=seleciona_dados_funcional',
        {
            ptrid: ptrid.value,
            pedid: $("#pedid").val()
        },
            function(dados){
                dados = JSON.parse(dados);
                if (dados){
                    $("#pliselid"+rlid).val(dados.pliselid);
                    $("#unicod"+rlid).val(dados.unicod);
                    $("#rpcod"+rlid).val(dados.irpcod);
                    $("#rpcod"+rlid).trigger('chosen:updated');
                    SelecionaDotacao(rlid);
                }
            }
        );         
    }
    
    function SelecionaDotacao(rlid){
        if (rlid==undefined){
            rlid='';
        }
        var unicod = $("#unicod"+rlid).val();
        var funcional = $("#ptrid"+rlid+" option:selected").text();
        var arrFuncional = funcional.split('.');
        var prgcod = arrFuncional[0];
        var acacod = arrFuncional[1];
        var loccod = arrFuncional[2];
        var objcod = arrFuncional[3];
        var plocod = arrFuncional[4];
        var gndcod = $("#gndcod"+rlid).val();
        var mapcod = $("#mapcod"+rlid).val();
        var categoria = $("#ctecod"+rlid).val();

        if (unicod && prgcod && acacod && loccod && plocod && mapcod && gndcod && categoria){
            var natureza = categoria.concat(gndcod,mapcod);
            $.post('?modulo=principal/cadastro_alteracoes&acao=C&req=seleciona_dotacao',
            {
                unicod: unicod,
                prgcod: prgcod,
                acacod: acacod,
                loccod: loccod,
                plocod: plocod,
                natureza: natureza
            },
                function(dados){
                    dados = JSON.parse(dados);
                    if (dados){
                        $("#vlDotacao"+rlid).html(dados);
                    }
                }
            );
        }
    }
</script>
<style>
    .combo > .chosen-container {
        font-size: 9px;        
    }
    .input_valor_remanejamento {
        font-size: 9px;
        width: 75px;
        padding: 0px;
    }
    .tdpliselid{
        width: 220px;
    }
</style>