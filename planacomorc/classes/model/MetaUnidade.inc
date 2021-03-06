<?php
/**
 * Classe de mapeamento da entidade planacomorc.meta_unidade
 *
 * @category Class
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 22-02-2019
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


/**
 * Planacomorc_Model_MetaUnidade
 *
 * @category Class
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU siminc2.cultura.gov.br
 * @version  Release: 
 * @link     no link
 */
class Planacomorc_Model_MetaUnidade extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'planacomorc.meta_unidade';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'meuid',
    );
    /**
     * Chaves estrangeiras.
     * @var array
     */
    protected $arChaveEstrangeira = array(
        'dimeid' => array('tabela' => 'planacomorc.dimensao_estrategica', 'pk' => 'dimeid'),
        'obeid'  => array('tabela' => 'planacomorc.objetivo_estrategico', 'pk' => 'obeid'),
        'meeid'  => array('tabela' => 'planacomorc.meta_estrategica',     'pk' => 'meeid'),
    );

    /**
     * Atributos
     * @var array
     * @access protected
     */
    protected $arAtributos = array(
        'meuid' => null,
        'dimeid' => null,
        'obeid' => null,
        'meeid' => null,
        'meunome' => null,
        'meuquantificavel' => null,
        'meuquantidade' => null,
        'meuprioritario' => null,
        'meucadastro' => null,
        'meustatus' => null,
    );

    /**
     * Retorna sql para buscar as Metas Unidades que est�o vinculadas � subunidade ou que n�o estejam vinculada a nenhuma subunidade.
     *
     * @param $suocod
     * @return string
     */
    public function recuperarSqlMeta($suocod)
    {

        $sql = "
            SELECT DISTINCT
                meu.meuid AS codigo,
                meu.meunome AS descricao
            FROM planacomorc.subunidade_meta_unidade AS smu
                LEFT JOIN planacomorc.meta_unidade AS meu ON meu.meuid = smu.meuid
                LEFT JOIN public.vw_subunidadeorcamentaria AS suo ON suo.suoid = smu.suoid
            WHERE
                meu.meustatus = 'A'
                AND suo.suocod = '".$suocod."'
            UNION ALL
            SELECT DISTINCT
                mun.meuid AS codigo,
                mun.meunome AS descricao
            FROM planacomorc.meta_unidade AS mun
                LEFT JOIN planacomorc.subunidade_meta_unidade AS sme ON mun.meuid = sme.meuid
            WHERE
                mun.meustatus = 'A'
                AND sme.suoid IS NULL
            ORDER BY
                descricao
        ";

        return $sql;
    }

    /**
     * Retorna o registro de Meta Unidade com os dados de Objetivo Estrat�gico, Dimens�o Estrat�gica e Meta Estrat�gica.
     *
     * @param $meuid
     * @return array|bool
     */
    public function recuperarPlanejamentoEstrategico($meuid)
    {
        $sql = "
            SELECT
                meu.meuid,
                meu.meunome,
                obj.obeid,
                obj.obenome,
                dime.dimeid,
                dime.dimenome,
                mee.meeid,
                mee.meenome
            FROM planacomorc.meta_unidade AS meu
                LEFT JOIN planacomorc.objetivo_estrategico AS obj ON obj.obeid = meu.obeid AND obj.obestatus = 'A'
                LEFT JOIN planacomorc.dimensao_estrategica AS dime ON dime.dimeid = meu.dimeid AND dime.dimestatus = 'A'
                LEFT JOIN planacomorc.meta_estrategica AS mee ON mee.meeid = meu.meeid AND mee.meestatus = 'A'
            WHERE
                meu.meuid = ". (int)$meuid."
                AND meu.meustatus = 'A'
        ";

        return $this->pegaLinha($sql);
    }

    /**
     *
     */
    public function recuperarInformacoes($exercicio = null)
    {
        $exercicio = $exercicio ? $exercicio : $_SESSION['exercicio'];

        $sql = "
            SELECT
                meu.meuid,
                meu.meunome,
                meu.meuquantificavel,
                meu.meuquantidade,
                obe.obeid,
                obe.obenome,
                dime.dimeid,
                dime.dimenome,
                mee.meeid,
                mee.meenome,
                CASE WHEN (SELECT count(1) FROM planacomorc.subunidade_meta_unidade smu WHERE smu.meuid = meu.meuid) = 0 THEN
                    TRUE
                WHEN (SELECT count(1) FROM planacomorc.subunidade_meta_unidade smu WHERE smu.meuid = meu.meuid) > 2 THEN
                    TRUE
                ELSE
                    FALSE
                END AS compartilhada,
                -- C�lculo para verificar quantidade anualizada: (valor previsto dividido por 4 e vezes o ano do monitoramento)
                meu.meuquantidade / 4 * ((to_char(now(), 'YYYY')::int % 4) + 1) meuquantidadeanualizada
            FROM planacomorc.meta_unidade meu
                LEFT JOIN planacomorc.objetivo_estrategico AS obe ON obe.obeid = meu.obeid
                LEFT JOIN planacomorc.dimensao_estrategica AS dime ON dime.dimeid = meu.dimeid
                LEFT JOIN planacomorc.meta_estrategica AS mee ON mee.meeid = meu.meeid
            WHERE
                meu.meustatus = 'A'
                AND meu.meuid = ". (int)$this->meuid. "
        ";

        return $this->pegaLinha($sql);
    }
}
