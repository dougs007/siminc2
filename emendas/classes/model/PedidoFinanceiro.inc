<?php
/**
 * Classe de mapeamento da entidade emendas.autortipo
 *
 * @category Class
 * @package  A1
 * @author   RAFAEL FREITAS CARNEIRO <rafael.carneiro@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 07-02-2019
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


/**
 * Emendas_Model_PedidoFinanceiro
 *
 * @category Class
 * @package  A1
 * @author    <>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 
 * @link     no link
 */
class Emendas_Model_PedidoFinanceiro extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'emendas.pedido_financeiro';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'pefid',
    );
    /**
     * Chaves estrangeiras.
     * @var array
     */
    protected $arChaveEstrangeira = array(        
    );

    /**
     * Atributos
     * @var array
     * @access protected
     */
    protected $arAtributos = array(
        'pefid' => null,
        'benid' => null, 
        'dtcadastro' => null,
        'usucpf' => null,
        'vlcusteiopedido' => null,
        'vlcapitalpedido' => null,
        'nroanoreferencia' => null,
        'nromesreferencia' => null,
        'vinid' => null,
    );
    
    Public Function recuperaPedidoFinanceiroPorBenidPorPeriodo($benid){
        $sql = "select pf.pefid,
                       pf.benid,
                       pf.dtcadastro,
                       pf.usucpf,
                       pf.vlcusteiopedido,
                       pf.vlcapitalpedido,
                       pf.nroanoreferencia,
                       pf.nromesreferencia,
                       pf.vinid,
                       v.vindsc
                  from emendas.pedido_financeiro pf
                  left join emendas.vinculacao v
                    on pf.vinid = v.vinid
                 where pf.benid = ".$benid."
                   and pf.nroanoreferencia = date_part('year', CURRENT_DATE)
                   and pf.nromesreferencia = date_part('month', CURRENT_DATE)";
        return (object)$this->pegaLinha($sql);
    }
    
    Public Function verificaPedidoFinanceiroAnoMes($benid, $ano, $mes){
        $sql = "select coalesce(pefid,0) as pefid
                  from emendas.pedido_financeiro
                 where nroanoreferencia = ".$ano."
                   and nromesreferencia = ".$mes."
                   and benid = ".$benid;
        return $this->pegaUm($sql);
    }

    Public Function recuperaPedidoFinanceiroPorBenid($benid){
        $sql = "
            SELECT
                pf.pefid,
                pf.benid,
                to_char(pf.dtcadastro,'DD/MM/YYYY') AS dtcadastro,
                pf.usucpf,
                pf.vlcusteiopedido,
                pf.vlcapitalpedido,
                pf.nroanoreferencia,
                pf.nromesreferencia,
                pf.vinid,
                u.usunome,
                u.usuemail,
                '(' || u.usufoneddd ||') '|| u.usufonenum AS telefone,
                v.vindsc
            FROM emendas.pedido_financeiro AS pf
            JOIN seguranca.usuario AS u
                    ON pf.usucpf = u.usucpf
            LEFT JOIN emendas.vinculacao v ON pf.vinid = v.vinid
            WHERE
                pf.benid = ".$benid;
        return (object)$this->carregar($sql);
    }
}
