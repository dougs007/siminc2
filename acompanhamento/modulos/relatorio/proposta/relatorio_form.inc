<input type="hidden" name="req" id="req" value=""/>
<div class="ibox-title">
    <h5>Relat�rio Geral de Proposta</h5><br>
</div>
<div class="ibox-content">
    <?php
    $stSql = "SELECT prsano AS codigo, prsano AS descricao FROM proposta.proposta WHERE prostatus = 'A' ORDER BY 1;";
    $preenchidos = null;
    if (!$_REQUEST['filtro']['prsano']) {
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
    // Dados padr�o de origem
    $origem = array(array('codigo' => 'locquantidadeproposta', 'descricao' => 'Quantidade Localizador'),
                    array('codigo' => 'proquantidade', 'descricao' => 'Quantidade PO'),
                    array('codigo' => 'proquantidadeexpansao', 'descricao' => 'Quantidade Expans�o PO'),
                    array('codigo' => 'projustificativa', 'descricao' => 'Justificativa'),
                    array('codigo' => 'projustificativaexpansao', 'descricao' => 'Justificativa Expans�o'),
                    array('codigo' => 'prdvalor', 'descricao' => 'Valor'),
                    array('codigo' => 'prdvalorexpansao', 'descricao' => 'Valor Expans�o'),
                    array('codigo' => 'suonome', 'descricao' => 'Subunidade'),
                    array('codigo' => 'eqddsc', 'descricao' => 'Enquadramento da Despesa'),
                    array('codigo' => 'irpcod', 'descricao' => 'RP'),
                    array('codigo' => 'funcional', 'descricao' => 'Funcional'),
                    array('codigo' => 'acatitulo', 'descricao' => 'A��o'),
                    array('codigo' => 'plodsc', 'descricao' => 'PO'),
                    array('codigo' => 'ndpid', 'descricao' => 'Natureza de Despesa'),
                    array('codigo' => 'iducod', 'descricao' => 'IDUSO'),
                    array('codigo' => 'foncod', 'descricao' => 'Fonte'),
                    array('codigo' => 'idoid', 'descricao' => 'IDOC'),
                    array('codigo' => 'proid', 'descricao' => 'ID Proposta'),
                    array('codigo' => 'prsano', 'descricao' => 'Ano'),
    );
    // exibe agrupador
    $agrupador->setOrigem('naoColuna', null, $origem);
    $agrupador->setDestino('coluna', null, $destino);
    $agrupador->exibir();
    $stSql = "  SELECT DISTINCT suo.suoid AS codigo,
                       suo.suonome AS descricao,
                       suo.prsano
                  FROM public.vw_subunidadeorcamentaria suo
                 WHERE suo.prsano='".$_REQUEST['filtro']['prsano']."' AND suo.suostatus = 'A'
                 ORDER BY 3,2";
    echo $simec->select("filtro[suoid][]", 'Unidade', $suoid, $stSql, null, ['input-size' => 9, 'label-size' => 2]);
    $stSql = "  SELECT DISTINCT eqd.eqdid AS codigo,
                       eqd.eqddsc AS descricao
                  FROM monitora.pi_enquadramentodespesa eqd
                 WHERE eqd.eqdano='".$_REQUEST['filtro']['prsano']."'
                   and eqdstatus = 'A'
                 ORDER BY 2,1";

    echo $simec->select("filtro[eqdid][]", 'Enquadramento', null, $stSql, null, ['input-size' => 9, 'label-size' => 2]);    
    $stSql = "  SELECT DISTINCT irp.irpcod AS codigo,
                       irp.irpcod || ' - ' || irp.irpdsc AS descricao
                  FROM public.identresultprimario irp
                 WHERE irp.irpstatus = 'A'
                 ORDER BY 2,1";

    echo $simec->select("filtro[irpcod][]", 'RP', null, $stSql, null, ['input-size' => 9, 'label-size' => 2]);    
    $stSql = "  SELECT DISTINCT tpd.tpdid AS codigo,
                       tpd.tpdcod || ' - ' || tpd.tpdnome AS descricao 
                  FROM proposta.tipodetalhamento tpd
                 WHERE tpd.tpdstatus = 'A'
                 ORDER BY 2,1";

    echo $simec->select("filtro[tpdid][]", 'Tipo de Detalhamento', null, $stSql, null, ['input-size' => 9, 'label-size' => 2]);    
    ?>    
    <div class="text-center">
        <a class="btn-success btn btn-md" href="javascript:exibeRelatorioGeral('exibir');"><i class="fa fa-eye"></i> Visualizar</a>
        <a class="btn btn-primary btn-buscar" href="javascript:exibeRelatorioGeral('xls');"><i class="fa fa-file-excel-o"></i> Exportar XLS</a>
    </div>
</div>