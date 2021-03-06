<?php
/**
 * Classe de mapeamento da entidade planacomorc.historico_pi
 *
 * @category Class
 * @package  A1
 * @author   RAFAEL FREITAS CARNEIRO <rafael.carneiro@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 06-07-2018
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


class Planacomorc_Model_ImportaDadosSiop extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = '';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        '',
    );
    /**
     * Chaves estrangeiras.
     * @var array
     */
    protected $arChaveEstrangeira = array(
        '',
        '',
    );

    /**
     * Atributos
     * @var array
     * @access protected
     */
    protected $arAtributos = array();
    
    public function excluirWsExecucaoOrcamentaria($exercicio){
        $sql = "DELETE FROM wssof.ws_execucaoorcamentariadto WHERE anoexercicio = ". (int)$exercicio;
        $this->executar($sql);
    }
    
    public function excluirWsExecucaoOrcamentariaPorOrgao($preFixoCodigoOrgao){
        $sql = "DELETE FROM wssof.ws_execucaoorcamentariadto WHERE anoexercicio::NUMERIC >= 2019 AND unidadeorcamentaria ILIKE '". (int)$preFixoCodigoOrgao. "%'";
        $this->executar($sql);
    }
    
    public function excluirSiopExecucao($exercicio){
        $sql = "DELETE FROM spo.siopexecucao WHERE exercicio = '". (int)$exercicio. "'";
        $this->executar($sql);
    }
    
    public function inserirSiopExecucao($exercicio){
        $sql = "
            INSERT INTO spo.siopexecucao(
                exercicio,
                esfcod,
                unicod,
                funcod,
                sfucod,
                prgcod,
                acacod,
                loccod,
                plocod,
                ptres,
                plicod,
                natcod,
                gndcod,
                vlrdotacaoinicial,
                vlrdotacaoatual,
                vlrempenhado,
                vlrliquidado,
                vlrpago,
                vlrautorizado
            )
            SELECT
                exo.anoexercicio AS exercicio,
                exo.esfera AS esfcod,
                exo.unidadeorcamentaria AS unicod,
                exo.funcao AS funcod,
                exo.subfuncao AS sfucod,
                exo.programa AS prgcod,
                exo.acao AS acacod,
                exo.localizador AS loccod,
                exo.planoorcamentario AS plocod,
                exo.numeroptres AS ptres,
                SUBSTRING(exo.planointerno, 1, 11) AS plicod,
                natureza AS natcod,
                gruponaturezadespesa AS gndcod,
                CASE WHEN exo.dotacaoinicial <> '' THEN
                    exo.dotacaoinicial::NUMERIC
                ELSE
                    0
                END AS vlrdotacaoinicial,
                CASE WHEN exo.dotatual <> '' THEN
                    exo.dotatual::NUMERIC
                ELSE
                    0
                END AS vlrdotacaoatual,
                exo.empliquidado::NUMERIC + exo.empenhadoaliquidar::NUMERIC AS vlrempenhado,
                exo.empliquidado::NUMERIC - exo.executadoporinscricaoderap::NUMERIC AS vlrliquidado,
                exo.pago::NUMERIC AS vlrpago,
                exo.autorizado::NUMERIC AS vlrautorizado
            FROM wssof.ws_execucaoorcamentariadto exo
            WHERE
                anoexercicio = '". (int)$exercicio. "'";

        $this->executar($sql);
    }
    
    public function buscarDotacoesFuncionaisSIOP($exercicio){
        $sql = "
            SELECT
                exe.unidadeorcamentaria,
                exe.funcao,
                exe.subfuncao,
                exe.programa,
                exe.acao,
                exe.localizador,
                exe.planoorcamentario,
                exe.categoriaeconomica,
                exe.unidadeorcamentaria || '.' || exe.funcao || '.' || exe.subfuncao || '.' || exe.programa || '.' || exe.acao || '.' || exe.localizador || '.' || exe.planoorcamentario AS funcional,
                SUM(exe.dotacaoinicial::numeric) AS dotacaoinicial,
                SUM(exe.dotatual::numeric) AS dotatual,
                SUM(exe.dotinicialsiafi::numeric) AS dotinicialsiafi,
                SUM(exe.dotacaoantecipada::numeric) AS dotacaoantecipada
            FROM wssof.ws_execucaoorcamentariadto AS exe
            WHERE
                exe.anoexercicio = '". (int)$exercicio. "'
                AND exe.anoreferencia = '". (int)$exercicio. "'
            GROUP BY
                exe.unidadeorcamentaria,
                exe.funcao,
                exe.subfuncao,
                exe.programa,
                exe.acao,
                exe.localizador,
                exe.planoorcamentario,
                exe.categoriaeconomica
            ORDER BY
                exe.unidadeorcamentaria,
                exe.programa,
                exe.acao,
                exe.localizador,
                exe.planoorcamentario,
                exe.categoriaeconomica
        ";

        $dados = $this->carregar($sql);
        return $dados ? $dados : [];        
    }
    
    public function buscarLimitesFuncionaisSubunidades($exercicio){
        $sql = "
            SELECT
                ptr.unicod,
                suo.unocod,
                suo.unosigla,
                suo.unonome,
                suo.suocod,
                suo.suosigla,
                suo.suonome,
                psu.suoid,
                psu.psuid,
                ptr.ptrid,
                ptr.funcional AS funcionalptres,
                ptr.unicod || '.' || ptr.funcod || '.' || ptr.sfucod || '.' || ptr.prgcod || '.' || ptr.acacod || '.' || ptr.loccod || '.' || ptr.plocod  AS funcional,
                COALESCE(psu.ptrdotacaocapital, 0) AS ptrdotacaocapital,
                COALESCE(psu.ptrdotacaocusteio, 0) AS ptrdotacaocusteio
            FROM spo.ptressubunidade AS psu
                JOIN monitora.vw_ptres AS ptr ON ptr.ptrid = psu.ptrid
                JOIN public.vw_subunidadeorcamentaria AS suo ON suo.suoid = psu.suoid
            WHERE
                ptr.ptrano = '". (int)$exercicio. "'
                AND ptr.irpcod != '6'
            ORDER BY
                ptr.unicod,
                funcional
        ";

        $dados = $this->carregar($sql);
        return $dados ? $dados : [];        
    }
    
    public function buscarPaComProvisionadoMaiorPrevisto($exercicio){
        $sql = "
            SELECT
                pli.plicod,
                pli.pliid,
                pli.suocod,
                pli.suosigla,
                pli.plititulo,
                pli.unocod,
                pli.unosigla,
                pli.funcional,
                pli.previsto::numeric,
                pli.autorizado::numeric,
                pli.empenhado::numeric,
                pli.liquidado::numeric,
                pli.pago::numeric pago
            FROM monitora.vw_planointerno pli
                JOIN monitora.vw_ptres ptr ON pli.ptrid = ptr.ptrid
            WHERE
                pli.pliano = '$exercicio'
                AND pli.autorizado > pli.previsto
                AND ptr.irpcod <> '6'
            ORDER BY
                pli.unosigla,
                pli.suosigla,
                pli.funcional
        ";

        $dados = $this->carregar($sql);
        return $dados ? $dados : [];        
    }
    
    public function buscarFuncionaisSemValorPlanejado($exercicio){
        $sql = "
            SELECT
                ptr.ptrid,
                ptr.ptres,
                ptr.funcional,
                CASE WHEN (
                    SELECT
                        COUNT(ptressubunidade.ptrid)
                    FROM spo.ptressubunidade
                    WHERE
                        ptressubunidade.ptrid = ptr.ptrid
                ) = 1 THEN
			suo.suocod || ' - ' || suo.suonome || '(' || suo.unosigla || ')'
		ELSE
                    'V�rias'
		END AS subunidade,
		COALESCE(sec.empenhado, 0.00) AS empenhado,
		COALESCE(sec.liquidado, 0.00) AS liquidado,
		COALESCE(sec.pago, 0.00) as pago
            FROM public.vw_subunidadeorcamentaria suo
                JOIN spo.ptressubunidade psu on psu.suoid = suo.suoid
                JOIN monitora.vw_ptres ptr on ptr.ptrid = psu.ptrid AND ptr.ptrano = suo.prsano
                JOIN(
                    SELECT
                        siopexecucao.ptres,
                        SUM(COALESCE(siopexecucao.vlrautorizado, 0.00))::NUMERIC AS provisionado,
                        SUM(COALESCE(siopexecucao.vlrempenhado, 0.00))::NUMERIC AS empenhado,
                        SUM(COALESCE(siopexecucao.vlrliquidado, 0.00))::NUMERIC AS liquidado,
                        SUM(COALESCE(siopexecucao.vlrpago, 0.00))::NUMERIC AS pago
                    FROM spo.siopexecucao
                        LEFT JOIN monitora.pi_planointerno ON(
                            siopexecucao.plicod = pi_planointerno.plicod
                            AND pi_planointerno.pliano = '". (int)$exercicio. "'
                            AND pi_planointerno.plistatus = 'A'
			)
                    WHERE
                        pi_planointerno.ungcod IS NULL
                        AND siopexecucao.exercicio = '". (int)$exercicio. "'
                    GROUP BY
                        siopexecucao.ptres
		) sec ON(ptr.ptres = sec.ptres)
            WHERE
                suo.prsano = '". (int)$exercicio. "'
                AND suo.unofundo = FALSE
                AND suo.suostatus = 'A'
		AND ptr.irpcod <> '6'
		AND (empenhado > 0 OR liquidado > 0 OR pago > 0)
            GROUP BY
		ptr.ptrid,
		ptr.ptres,
		ptr.funcional,
                subunidade,
		sec.empenhado,
		sec.liquidado,
		sec.pago
            ORDER BY
                ptr.funcional,
		ptr.ptres,
		subunidade
        ";

        $listaResultado = $this->carregar($sql);
        return $listaResultado? $listaResultado: [];        
    }
    
    public function buscarListaEmailsSuperUsuarios(){
        $sql = "
            SELECT DISTINCT
                usu.usucpf,
                usu.usunome,
                usu.usuemail
            FROM seguranca.perfilusuario pu
                JOIN seguranca.usuario usu ON(
                    usu.usucpf = pu.usucpf
                    AND usu.suscod = 'A'
                )
                JOIN seguranca.usuario_sistema us ON(
                    us.usucpf = usu.usucpf
                    AND us.suscod = 'A'
                    AND us.sisid = ". (int)SISID_PLANEJAMENTO. "
                )
            WHERE
                pu.pflcod IN (". (int)PFL_ADMINISTRADOR. ", ". (int)PFL_SUPERUSUARIO. ")
            ORDER BY
                usuemail
        ";
//echo $sql;
        return $this->carregar($sql);        
    }

    public function atualizarDotacoesIniciaisFuncionais($exercicio){
        $sql = "
            UPDATE monitora.ptres SET
                ptrdotacaoinicialcapital = x.ptrdotacaoinicialcapital,
                ptrdotacaoinicialcusteio = x.ptrdotacaoinicialcusteio
            FROM (
                SELECT
                    SUM(
                        CASE WHEN exe.categoriaeconomica = '4' THEN
                            exe.dotacaoinicial::NUMERIC
                        ELSE
                            0
                        END
                    ) AS ptrdotacaoinicialcapital,
                    SUM(
                        CASE WHEN exe.categoriaeconomica = '3' THEN
                            exe.dotacaoinicial::NUMERIC
                        ELSE
                            0
                        END
                    ) AS ptrdotacaoinicialcusteio,
                    ptres.ptrid
                FROM wssof.ws_execucaoorcamentariadto exe,
                    monitora.vw_ptres ptres
                WHERE
                    exe.anoexercicio::INTEGER = ptres.ptrano::INTEGER
                    AND exe.unidadeorcamentaria = ptres.unicod
                    AND exe.funcao = ptres.funcod
                    AND exe.subfuncao = ptres.sfucod
                    AND exe.programa = ptres.prgcod
                    AND exe.acao = ptres.acacod
                    AND exe.localizador = ptres.loccod
                    AND exe.planoorcamentario = ptres.plocod
                GROUP BY
                    ptres.ptrid
            ) AS x
            WHERE
                monitora.ptres.ptrano = '". (int)$exercicio. "'
                AND monitora.ptres.ptrid = x.ptrid
        ";
        $this->executar($sql);
    }
}

