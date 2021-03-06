<div class="ibox-title">
    <h5>Identifica��o</h5>
</div>
<div class="ibox-content">
    
    <div class="form-group">
        <div class="col-md-3 text-right">
            <label class="control-label" for="unicod">Unidade: <span title="Campo obrigat�rio" class="link campo-obrigatorio">*</span></label>
        </div>
        <div class="col-lg-9">
            <?php
            $obrigatorias = UNIDADES_OBRIGATORIAS;
            // -- Se a requisi��o tiver um scpid, quer dizer que a tela foi aberta para homologar uma
            // -- solicita��o de PI, ou para ver uma transa��o executada anteriormente. Nos dois casos,
            // -- o filtro de UOs deve exibir (ao menos) a UO escolhida no momento da cria��o da transa��o,
            // -- portanto, n�o deve filtrar pela UO do usu�rio que a est� visualizando.
            // ******* Ao carregar a listagem de PTRES, sempre filtrar pela UO selecionada, independentemente do Perfil ; *****

            $wherePerfilUO = $filtroPerfilUG = '';
            if(in_array(PFL_SUBUNIDADE, $perfis)){
                $sql = "
                    SELECT DISTINCT
                        suo.suoid,
                        suo.suocod,
                        suo.unoid,
                        suo.unocod,
                        suo.unofundo
                    FROM planacomorc.usuarioresponsabilidade ur
                        JOIN public.vw_subunidadeorcamentaria suo ON suo.suocod = ur.ungcod
                    WHERE
                        suo.suostatus = 'A'
                        AND usucpf = '{$_SESSION['usucpf']}'
                        AND ur.pflcod = '" . PFL_SUBUNIDADE . "'
                        AND suo.prsano = '{$_SESSION['exercicio']}'
                        AND rpustatus = 'A'
                        AND unofundo IS FALSE
                    ORDER BY
                        suo.unocod
                ";

                $dadosUsuario = $db->carregar($sql);

                $unidadeUsuario = [];
                if($dadosUsuario){
                    foreach ($dadosUsuario as $dadoUsuario){
                        $unidadeUsuario['unidades'][$dadoUsuario['unocod']] = $dadoUsuario['unocod'];
                        $unidadeUsuario['subunidades'][$dadoUsuario['unocod']] = $dadoUsuario['unocod'];

                        # Agrupando por FNC
                        $unidadeUsuario['unocod'][$dadoUsuario['unofundo']][$dadoUsuario['unocod']] = $dadoUsuario['unocod'];
                        $unidadeUsuario['suocod'][$dadoUsuario['unofundo']][$dadoUsuario['suocod']] = $dadoUsuario['suocod'];
                    }
                }
                
                $wherePerfilUO  = " AND unocod IN('" . ($unidadeUsuario['unidades']? implode("', '", $unidadeUsuario['unidades']): 0) . "')";

                if(empty($dadosPI['unicod'])){
                    $dadosPI['unicod'] = (1 == count($unidadeUsuario['unocod']['f'])) ? current($unidadeUsuario['unocod']['f']) : '';
                }
                if(empty($dadosPI['ungcod'])){
                    $dadosPI['ungcod'] = (1 == count($unidadeUsuario['suocod']['f'])) ? current($unidadeUsuario['suocod']['f']) : '';
                }
            }

            $sql = "
                SELECT DISTINCT
                    suo.unocod AS codigo,
                    CASE WHEN suo.unocod = '". (int)UNICOD_MC. "' THEN
                        '". (int)UNICOD_MC. " - MINSTERIO DA CIDADANIA - ADMINISTRA��O DIRETA'
                    ELSE
                        suo.unocod || ' - ' || suo.unonome
                    END AS descricao
                FROM public.vw_subunidadeorcamentaria suo
                WHERE
                    suo.prsano = '{$_SESSION['exercicio']}'
                    AND suo.suostatus = 'A'
                    AND suo.unofundo = FALSE
                    $wherePerfilUO
                ORDER BY
                    descricao
            ";

            $editavelUg = ($dadosPI['unicod'] && $dadosPI['pliid']) ? 'N' : 'S';
            $db->monta_combo('unicod', $sql, $editavelUg, 'Selecione', null, null, null, null, 'N', 'unicod', null, (isset($dadosPI['unicod']) ? $dadosPI['unicod'] : null), null, 'class="form-control chosen-select" style="width=100%;"', null, null);
            ?>
        </div>
    </div>
    
    <div class="form-group">
        <div class="col-md-3 text-right">
            <label class="control-label" for="ungcod">SubUnidade: <span title="Campo obrigat�rio" class="link campo-obrigatorio">*</span></label>
        </div>
        <div class="col-lg-9 div_ungcod">
            <?php
            $ungcod = $dadosPI['ungcod'];
            carregarComboUG($dadosPI['unicod'], $editavelUg);
            ?>
        </div>
    </div>
    
    <div class="form-group">
        <div class="col-md-3 text-right">
            <label class="control-label" for="picted">Delega��o:</label>
        </div>
        <div class="col-md-1">
            <input type="checkbox" name="radioDelegacao" id="radioDelegacao" value="t" class="js-switch" <?php echo count($listaSubUnidadesDelegadas) ? 'checked="checked"' : ''; ?> />
        </div>
        <div class="col-md-7" id="div_unidades_delegadas" style="margin-left: 15px;">
            <?php
            $aSubUnidadeOrcamentaria = simec_preparar_array((new Public_Model_SubUnidadeOrcamentaria())->recuperarTodos("suoid as codigo, unosigla || ' - ' || suonome as descricao", ["prsano = '{$_SESSION['exercicio']}'", "suostatus = 'A'"], 'descricao'));
            echo $simec->select("delegacao[]", '', $listaSubUnidadesDelegadas, $aSubUnidadeOrcamentaria);
            ?>
        </div>
    </div>
    
    <?php
        $checked = $dadosPI['eqdid']? $dadosPI['eqdid']: $codigoEnquadramentoNaoOrcamentario;
        echo $simec->select("eqdid", 'Enquadramento da Despesa', $checked, (new Monitora_Model_PiEnquadramentoDespesa())->recuperarSqlCombo('eqdid, eqddsc', null, 'eqddsc'), ['required']);
    ?>
    
    <div class="form-group grupo_manutencao" style="display: none;">
        <div class="col-md-3 text-right">
            <label class="control-label" for="maiid">Item: <span title="Campo obrigat�rio" class="link campo-obrigatorio">*</span></label>
        </div>
        <div class="col-lg-9 div_maiid">
            <?php carregarManutencaoItem($dadosPI['eqdid'], $dadosPI['maiid']); ?>
        </div>
    </div>
    
    <div class="form-group grupo_manutencao" style="display: none;">
        <div class="col-md-3 text-right">
            <label class="control-label" for="masid">SubItem: <span title="Campo obrigat�rio" class="link campo-obrigatorio">*</span></label>
        </div>
        <div class="col-lg-9 div_masid">
            <?php carregarManutencaoSubItem($dadosPI['maiid'], $dadosPI['masid']); ?>
        </div>
    </div>

</div>
