<?php
/**
 * Classe de mapeamento da entidade proposta.proposta
 *
 * @category Class
 * @package  A1
 * @author   ORION TELES DE MESQUITA <teste@teste.com.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 13-04-2018
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


/**
 * Proposta_Model_Proposta
 *
 * @category Class
 * @package  A1
 * @author    <>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 
 * @link     no link
 */
class Proposta_Model_Proposta extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'proposta.proposta';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'proid',
    );
    /**
     * Chaves estrangeiras.
     * @var array
     */
    protected $arChaveEstrangeira = array(
        'ptrid' => array('tabela' => 'ptres', 'pk' => 'ptrid'),
        'eqdid' => array('tabela' => 'pi_enquadramentodespesa', 'pk' => 'eqdid'),
        'suoid' => array('tabela' => 'subunidadeorcamentaria', 'pk' => 'suoid'),
    );

    /**
     * Atributos
     * @var array
     * @access protected
     */
    protected $arAtributos = array(
        'proid' => null,
        'suoid' => null,
        'eqdid' => null,
        'ptrid' => null,
        'proquantidade' => null,
        'proquantidadeexpansao' => null,
        'projustificativa' => null,
        'projustificativaexpansao' => null,
        'prostatus' => null,
        'prsano' => null,
    );


    public function recuperarListagem()
    {
        $sql = "select pro.proid, ptr.funcional, ptr.acatitulo, ptr.plodsc, eqd.eqddsc, suo.unosigla || ' - ' || suo.suonome subunidade,  pro.proquantidade, pro.proquantidadeexpansao, 
                        sum(prd.prdvalor) prdvalor, sum(prd.prdvalorexpansao) prdvalorexpansao
                from proposta.proposta pro
                    inner join monitora.vw_ptres ptr on pro.ptrid = ptr.ptrid
                    inner join public.vw_subunidadeorcamentaria suo on suo.suoid = pro.suoid
                    inner join monitora.pi_enquadramentodespesa eqd on eqd.eqdid = pro.eqdid
                    left join proposta.propostadetalhe prd on prd.proid = pro.proid
                where pro.prsano = '{$_SESSION['exercicio']}'
                and prostatus = 'A'
                group by pro.proid, ptr.funcional, ptr.acatitulo, ptr.plodsc, eqd.eqddsc, subunidade,  pro.proquantidade, pro.proquantidadeexpansao";

        return $this->carregar($sql);
    }

    public function recuperarDadosProposta($exercicio, $momento, $unoid = null)
    {
        /********************************************************************************************************************************************************
         *                                                                                                                                                       *
         *  DOCUMENTA��O DO SIOP PARA MONTAGEM DOS DADOS: https://www1.siop.planejamento.gov.br/siopdoc/doku.php/webservices:manual-wsquantitativo#propostadto   *
         *                                                                                                                                                       *
         ********************************************************************************************************************************************************/

        $where = $unoid ? " AND uno.unoid IN('". join($unoid, "','"). "') ": '' ;

//        $sql = "SELECT  distinct pro.proid, pro.prodtcadastro, tdp.tdpid, tdp.tpdcodigo, pro.proidentificadoracao, uno.unocod, aca.acacod, loc.loccod, prg.prgcod, a.codigoesfera, a.codigofuncao, a.codigosubfuncao,
//                        pro.proqtdpo, pro.proqtdexpansao, plf.plfvalor, plf.plfvalorexpansao, a.identificadorunico identificadorunicoacao, po.planoorcamentario ,plo.plocod, po.identificadorunico identificadorunicopo,
//                        plf.iducod, ido.idocod, ndp.ndpcod, plf.foncod, eqd.eqdcodigorp, pro.projustificativa, pro.projustificativaexp
//                FROM planointerno.propostaloa pro
//                        INNER JOIN planointerno.ppamomentounidade AS pmu ON pmu.pmuid = pro.pmuid AND pmu.prsano = '$exercicio'
//                        INNER JOIN planointerno.momento AS mom ON mom.momid = pmu.momid
//                        INNER JOIN planointerno.subunidadeorcamentaria AS suo ON suo.suoid = pmu.suoid
//                        INNER JOIN planointerno.unidadeorcamentaria AS uno ON uno.unoid = suo.unoid
//                        INNER JOIN planointerno.vw_funcional_2016 AS vwf ON vwf.pmuid = pmu.pmuid
//                        INNER JOIN planointerno.ppaacao aca ON aca.acaid = vwf.acaid
//                        INNER JOIN planointerno.ppalocalizador loc ON loc.locid = vwf.locid
//                        INNER JOIN planointerno.ppaprograma prg ON prg.prgid = vwf.prgid
//                        INNER JOIN planointerno.ppaplanoorcamentario plo ON plo.ploid = pmu.ploid
//                        LEFT JOIN planointerno.produtopo prp ON prp.prpid = plo.prpid
//                        LEFT JOIN planointerno.unidademedidapo upo ON upo.upoid = plo.upoid
//                        inner JOIN planointerno.enquadramentodespesa eqd ON eqd.eqdid = pro.eqdid
//                        inner JOIN planointerno.tipodetalhamentoploa tdp ON tdp.tdpid = eqd.tdpid
//                        left JOIN planointerno.propostaloafinanceiro plf ON plf.proid = pro.proid AND plf.plfstatus = 'A'
//                        INNER JOIN idoc ido ON ido.idoid = plf.idoid
//                        INNER JOIN naturezadespesa ndp ON ndp.ndpid = plf.ndpid
//                        inner join wssof.ws_acoesdto a on a.exercicio = '$exercicio' and a.codigomomento = '$momento' and a.codigoorgao = uno.unocod and a.codigoacao = aca.acacod and a.codigoprograma = prg.prgcod
//                        left join wssof.ws_planosorcamentariosdto po on po.identificadorunicoacao = a.identificadorunico and po.exercicio = '$exercicio' and po.planoorcamentario = plo.plocod
//                WHERE pmu.momid = (select momid from planointerno.momento where prsano = '{$exercicio}' and momstatus = 'A' order by momid limit 1)
//                AND  pro.prostatus = 'A'
//                $where
//                and eqd.eqdcodigorp in ('2', '3')
//                ";

        $sql = "select  distinct a.identificadorunico identificadorunicoacao, 0 tpdcodigo, a.codigoesfera, aca.unicod, aca.prgcod, a.codigofuncao, a.codigosubfuncao, aca.acaid, aca.acacod, aca.loccod, 
                        ptr.plocod, ndp.ndpcod, prd.foncod, prd.iducod, idoc.idocod, prdvalor, pro.proquantidade, po.identificadorunico identificadorunicopo,
                        pro.projustificativa, pro.proquantidadeexpansao, pro.projustificativaexpansao, prd.prdvalorexpansao
                from proposta.proposta pro
                        inner join proposta.propostadetalhe prd on prd.proid = pro.proid
                        inner join public.naturezadespesa ndp on ndp.ndpid = prd.ndpid
                        inner join public.idoc on idoc.idoid = prd.idoid
                        inner join monitora.ptres ptr on ptr.ptrid = pro.ptrid
                        inner join monitora.acao aca on aca.acaid = ptr.acaid
                        inner join wssof.ws_acoesdto a on a.exercicio = pro.prsano::int  and a.codigomomento = $momento and a.codigoorgao = aca.unicod and a.codigoacao = aca.acacod and a.codigoprograma = aca.prgcod
                        left join wssof.ws_planosorcamentariosdto po on po.identificadorunicoacao = a.identificadorunico and po.exercicio = pro.prsano::int and po.planoorcamentario = ptr.plocod
                where pro.prsano = '$exercicio'
                and pro.prostatus = 'A'";

        $dados = $this->carregar($sql);

        $aEnvioWS = [];
        foreach ($dados as $dado) {
            $agrupador = $dado['tpdcodigo'] . '_' . $dado['unicod'] . '_' . $dado['acacod'] . '_' . $dado['loccod'] . '_' . $dado['prgcod'] . '_' . $dado['identificadorunico'];
//            $aEnvio[$agrupador][] = $dado;

            // C�lculos auxiliares
            $aEnvio[$agrupador]['valorFisico'] += $dado['prdvalor'];
            $aEnvio[$agrupador]['quantidadeFisico'][$dado['proid']] = 0;
            $aEnvio[$agrupador]['quantidadeFisicoPo'][$dado['plocod']][$dado['proid']] = $dado['proquantidade'];
            $aEnvio[$agrupador]['expansaoFisicaSolicitada'][$dado['proid']] = 0;
            $aEnvio[$agrupador]['expansaoFisicaSolicitadaPo'][$dado['plocod']][$dado['proid']] = $dado['proquantidadeexpansao'];
            $aEnvio[$agrupador]['justificativa'][$dado['proid']] = $dado['projustificativa'];
            $aEnvio[$agrupador]['propostas'][] = $dado['proid'];

            // @TODO Verificar se pode passar a justificativa. Por enquanto n�o est� passando
            if($dado['proquantidadeexpansao']){
                $aEnvio[$agrupador]['justificativaExpansaoSolicitada'][$dado['proid']] = $dado['projustificativaexpansao'];
            }

            // fix para limpar idOC cadastrados errados
            $idOCvalidos = array('0001', '0002', '0003', '0004', '0005', '9999');
            if (!in_array($dado['idocod'], $idOCvalidos)) {
                $dado['idocod'] = '9999';
            }

            // Montando no loop o array de FinanceiroDTO
            $aEnvio[$agrupador]['FinanceiroDTO'][] = [
                'idUso'                          => $dado['iducod'],
                'idOC'                           => $dado['idocod'],
                'naturezaDespesa'                => $dado['ndpcod'],
                'fonte'                          => $dado['foncod'],
                'resultadoPrimarioLei'           => $dado['eqdcodigorp'],
                'resultadoPrimarioAtual'         => $dado['eqdcodigorp'], // aceita nulo
                'identificadorPlanoOrcamentario' => $dado['identificadorunicopo'],
                'valor'                          => number_format($dado['prdvalor'], 0, '', ''),
                'expansaoSolicitada'             => ($dado['prdvalorexpansao'] > 0 ? $dado['prdvalorexpansao'] : null),
            ];

            // Montando no loop o array de FinanceiroDTO
            $aEnvio[$agrupador]['MetaPlanoOrcamentarioDTO'][$dado['plocod']] = [
                'identificadorUnicoPlanoOrcamentario' => $dado['identificadorunicopo'],
                'quantidadeFisico' => array_sum($aEnvio[$agrupador]['quantidadeFisicoPo'][$dado['plocod']]),
                'expansaoFisicaSolicitada' => ($aEnvio[$agrupador]['expansaoFisicaSolicitadaPo'][$dado['plocod']] > 0 ? array_sum($aEnvio[$agrupador]['expansaoFisicaSolicitadaPo'][$dado['plocod']]) : null),
                'expansaoFisicaConcedida' => null
            ];

            // Motagem do Array de PropostaDTO
            $aEnvioWS[$agrupador] = [
                'exercicio'                       => $exercicio,
                'codigoEsfera'                    => $dado['codigoesfera'],
                'codigoOrgao'                     => $dado['unicod'],
                'codigoFuncao'                    => $dado['codigofuncao'],
                'codigoSubFuncao'                 => $dado['codigosubfuncao'],
                'codigoPrograma'                  => $dado['prgcod'],
                'codigoAcao'                      => $dado['acacod'],
                'codigoTipoInclusaoAcao'          => '1',                                                       // Valores v�lidos: 1 - PLOA, 2 - Emenda, 4 - PPA, 5 - Cr�dito Especial, 6 - Cr�dito Extraordin�rio
                'codigoLocalizador'               => $dado['loccod'],
                'codigoTipoInclusaoLocalizador'   => '1',                                                       // Valores v�lidos: 1 - PLOA, 2 - Emenda, 4 - PPA, 5 - Cr�dito Especial, 6 - Cr�dito Extraordin�rio
                'codigoMomento'                   => $momento,                                                  // S�o os momentos (etapas) do processo no SIOP: 1000 (UO), 2000 (OS), 5000 (PLOA) e 8000 (LOA).
                'codigoTipoDetalhamento'          => $dado['tpdcodigo'],
                'quantidadeFisico'                => array_sum($aEnvio[$agrupador]['quantidadeFisico']),        // aceita nulo
                'valorFisico'                     => $aEnvio[$agrupador]['valorFisico'],                        // aceita nulo
                'financeiros'                     => $aEnvio[$agrupador]['FinanceiroDTO'],                        // lista de FinanceiroDTO
                // 'receitas'                        => null,                                                   // aceita nulo e lista de ReceitaDTO ?????????????????????????????
                'metaPlanoOrcamentario'           => array_values($aEnvio[$agrupador]['MetaPlanoOrcamentarioDTO']),
                'justificativa'                   => substr($dado['projustificativa'], 0, 4999),   // aceita nulo
                'identificadorUnicoAcao'          => $dado['identificadorunicoacao'],                             // aceita nulo ?????????????????????????????
                'expansaoFisicaSolicitada'        => array_sum($aEnvio[$agrupador]['expansaoFisicaSolicitada']),
                'justificativaExpansaoSolicitada' => ($aEnvio[$agrupador]['justificativaExpansaoSolicitada'] ? implode('. ', $aEnvio[$agrupador]['justificativaExpansaoSolicitada']) : null),
                'tdpid'                           => $dado['tdpid'],
                'propostas'                       => array_unique($aEnvio[$agrupador]['propostas'])
            ];
        }

        return $aEnvioWS;
    }

    public function gerarPlanilhaImportacao($momento = 2000, $unoid = null)
    {
        require_once APPRAIZ . 'includes/php-excel/PHPExcel.php';
        $exercicio = $_SESSION['exercicio'];

        $aEnvioWS = simec_utf8_encode_recursive($this->recuperarDadosProposta($exercicio, $momento, $unoid));
        
        $PHPExcel = new PHPExcel();

        // Criando Planilha "Financeiro"
        $planilhaFinanceiro = $PHPExcel->getActiveSheet();
        $planilhaFinanceiro->setTitle("Financeiro");

        // Criando Planilha "F�sico Localizador"
        $planilhaFisicoLocalizador = $PHPExcel->createSheet();
        $planilhaFisicoLocalizador->setTitle(utf8_encode("F�sico Localizador"));

        // Criando Planilha "F�sico PO"
        $planilhaFisicoPo = $PHPExcel->createSheet();
        $planilhaFisicoPo->setTitle(utf8_encode("F�sico PO"));


        $aPadrao = [
            'Momento'=>'codigoMomento',
            'Tipo de detalhamento'=>'codigoTipoDetalhamento',
            'Esfera'=>'codigoEsfera',
            'Unidade'=>'codigoOrgao',
            'SubUO'=>'',
            'Programa'=>'codigoPrograma',
            'Fun��o'=>'codigoFuncao',
            'SubFun��o'=>'codigoSubFuncao',
            'A��o'=>'codigoAcao',
            'Localizador'=>'codigoLocalizador',
        ];

        $aFinanceiro = ['PO'=>'PO', 'Natureza'=>'naturezaDespesa', 'Fonte'=>'fonte', 'Iduso'=>'idUso', 'Idoc'=>'idOC', 'Valor financeiro'=>'valor'];
        $aLocalizador = ['F�sico'=>'valorFisico', 'Justificativa'=>'justificativa'];
        $aPo = ['PO'=>'PO', 'F�sico PO'=>'quantidadeFisico'];

        // Criando cabe�alhos
        $coluna = 0;
        foreach($aPadrao as $titulo => $campo){
            $planilhaFinanceiro->setCellValueByColumnAndRow($coluna,1,utf8_encode($titulo));
            $planilhaFisicoLocalizador->setCellValueByColumnAndRow($coluna,1,utf8_encode($titulo));
            $planilhaFisicoPo->setCellValueByColumnAndRow($coluna,1,utf8_encode($titulo));
            $coluna++;
        }
        // Cabe�alho Planilha "Financeiro"
        $coluna = 10;
        foreach($aFinanceiro as $titulo => $campo){
            $planilhaFinanceiro->setCellValueByColumnAndRow($coluna++,1,utf8_encode($titulo));
        }

        // Cabe�alho Planilha "F�sico Localizador"
        $coluna = 10;
        foreach($aLocalizador as $titulo => $campo){
            $planilhaFisicoLocalizador->setCellValueByColumnAndRow($coluna++,1,utf8_encode($titulo));
        }
        // Cabe�alho Planilha "F�sico PO"
        $coluna = 10;
        foreach($aPo as $titulo => $campo){
            $planilhaFisicoPo->setCellValueByColumnAndRow($coluna++,1,utf8_encode($titulo));
        }

        $aPoSiop = $this->carregar("select * from wssof.ws_planosorcamentariosdto where exercicio = '{$exercicio}' and codigomomento = {$momento}");
        $aPoSiopCodigo = [];
        foreach($aPoSiop as $po){
            $aPoSiopCodigo[$po['identificadorunico']] = $po['planoorcamentario'];
        }

        $linhaFinanceiro = $linhaLocalizador = $linhaPo = 2;
        foreach($aEnvioWS as $chave => $dadosPloa){

            // Dados da Planilha "Financeiro"
            foreach($dadosPloa['financeiros'] as $aCampo){
                $coluna = 0;
                foreach($aPadrao as $campo){
                    $dado = $campo == 'codigoMomento' ? utf8_encode('�rg�o Setorial') : $dadosPloa[$campo];
                    $planilhaFinanceiro->setCellValueExplicitByColumnAndRow($coluna++,$linhaFinanceiro,$dado);
                }
                foreach($aFinanceiro as $campo){
                    $dado = $campo == 'PO' ? $aPoSiopCodigo[$aCampo['identificadorPlanoOrcamentario']] : $aCampo[$campo];
                    $planilhaFinanceiro->setCellValueExplicitByColumnAndRow($coluna++,$linhaFinanceiro,$dado);
                }
                $linhaFinanceiro++;
            }

            // Dados da Planilha "F�sico Localizador"
            $coluna = 0;
            foreach(($aPadrao+$aLocalizador) as $campo){
                $dado = $campo == 'codigoMomento' ? utf8_encode('�rg�o Setorial') : $dadosPloa[$campo];
                $planilhaFisicoLocalizador->setCellValueExplicitByColumnAndRow($coluna++,$linhaLocalizador,$dado);
            }

            $linhaLocalizador++;

            // Dados da Planilha "F�sico PO"
            foreach($dadosPloa['metaPlanoOrcamentario'] as $aCampo){
                $coluna = 0;
                foreach($aPadrao as $campo){
                    $dado = $campo == 'codigoMomento' ? utf8_encode('�rg�o Setorial') : $dadosPloa[$campo];
                    $planilhaFisicoPo->setCellValueExplicitByColumnAndRow($coluna++,$linhaPo,$dado);
                }
                foreach($aPo as $campo){
                    $dado = $campo == 'PO' ? $aPoSiopCodigo[$aCampo['identificadorUnicoPlanoOrcamentario']] : $aCampo[$campo];
                    $planilhaFisicoPo->setCellValueExplicitByColumnAndRow($coluna++,$linhaPo,$dado);
                }
                $linhaPo++;
            }
        }

        // Indica��o da cria��o do ficheiro
        $objWriter = PHPExcel_IOFactory::createWriter($PHPExcel, 'Excel5');

        // Encaminhar o ficheiro resultante para abrir no browser ou fazer download
        header('Content-Type: application/vnd.ms-excel');
        header('Content-Disposition: attachment;filename="PlanilhaImportacao.xls"');
        header('Cache-Control: max-age=0');
        $objWriter->save('php://output');
    }

}//end Class
?>