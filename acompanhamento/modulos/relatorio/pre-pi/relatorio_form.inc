<input type="hidden" name="req" id="req" value=""/>
<div class="ibox-title">
    <h5>Relat�rio Geral de Pr�-PA</h5><br>
</div>
<div class="ibox-content">
    <?php
        $stSql = "SELECT DISTINCT prsano AS codigo, prsano AS descricao FROM proposta.preplanointerno WHERE plistatus = 'A' ORDER BY 1";

    $preenchidos = null;
    if(!$_REQUEST['filtro']['prsano']) {
        $_REQUEST['filtro']['prsano'] = $preenchidos = $_SESSION['exercicio'];
    } else {
        $preenchidos = $_REQUEST['filtro']['prsano'];
    }
    echo $simec->select('filtro[prsano]', 'Exerc�cio', $preenchidos, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
    ?>
    <label class="col-sm-2 col-md-2 col-lg-2 control-label">Colunas</label>
    <?php
    unset($agrupador, $destino, $origem);
    // In�cio das colunas
    $agrupador = new AgrupadorBootstrap('filtro', '');
    // Dados padr�o de destino (nulo)
    $destino = isset($agrupador2) ? $agrupador2 : array();

    # Dados das colunas do Relat�rio
    $arrColunas = montarColunasRelatorioPrePI();
    if ($retConsultaRelatorio['colunas']){
        foreach($arrColunas as $arrColuna){
            foreach($retConsultaRelatorio['colunas'] as $coluna){
                if ($coluna['dscampo']==$arrColuna['codigo']){
                    $destino[] = $arrColuna;
                }
            }
        }
        foreach($arrColunas as $arrColuna){
            $achou=false;
            foreach($retConsultaRelatorio['colunas'] as $coluna){
                if ($coluna['dscampo']==$arrColuna['codigo']){
                    $achou=true;
                }
            }
            if (!$achou){
                $origem[] = $arrColuna;
            }
        }        
    }else{
        $destino = isset($agrupador2) ? $agrupador2 : array();
        $origem = $arrColunas;
    }
    // exibe agrupador
    $agrupador->setOrigem('naoColuna', null, $origem);
    $agrupador->setDestino('coluna', null, $destino);
    $agrupador->exibir();
    $stSql = "
        SELECT DISTINCT
            suo.suoid AS codigo,
            suo.suocod || ' - ' || suo.suonome AS descricao,
            suo.prsano
        FROM public.vw_subunidadeorcamentaria suo
        WHERE
	        suo.prsano = '".$_REQUEST['filtro']['prsano']."'
	        AND suo.suostatus = 'A'";
        if (count($listaSubUnidades)>0){
            $stSql .= " AND suo.suoid in (".implode(',', $listaSubUnidades).")";
        }        
        $stSql .= " ORDER BY
                descricao
        ";
        
        if (count($listaSubUnidades)>0){
            $suoid = $listaSubUnidades;
            echo $simec->select("filtro[suoid][]", 'Subunidade', $suoid, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
        }else{
            echo $simec->select("filtro[suoid][]", 'Subunidade', $suoid, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
        }
    
    $stSql = "
        SELECT DISTINCT
            eqd.eqdid AS codigo,
            eqd.eqddsc AS descricao
        FROM monitora.pi_enquadramentodespesa eqd
        WHERE eqd.eqdano='".$_REQUEST['filtro']['prsano']."'
            AND eqdstatus = 'A'
        ORDER BY
            2,1
    ";
    echo $simec->select("filtro[eqdid][]", 'Enquadramento', $eqdid, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
    
    $stSql = "
        SELECT DISTINCT
            irp.irpcod AS codigo,
            irp.irpcod || ' - ' || irp.irpdsc AS descricao
        FROM public.identresultprimario irp
        WHERE
            irp.irpstatus = 'A'
        ORDER BY
            2,1
    ";
    echo $simec->select("filtro[irpcod][]", 'RP', $irpcod, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
    
    $stSql = "
        SELECT DISTINCT
            esdid AS codigo,
            esddsc AS descricao
        FROM workflow.estadodocumento
        WHERE
            tpdid = ".TPDID_PROPOSTA."
        ORDER BY
            1
    ";
    echo $simec->select("filtro[esdid][]", 'Situa��o', $esdid, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
    ?>
</div>