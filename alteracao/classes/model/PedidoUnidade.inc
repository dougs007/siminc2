<?php
/**
 * Classe de mapeamento da entidade alteracao.tipo
 *
 * @category Class PedidoUnidade de Alteracao Orcamentaria
 * @package  A1
 * @author   Douglasx <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 24-10-2018
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


/**
 * Alteracao_Model_PedidoUnidade
 *
 * @category Class PedidoUnidade de Alteracao Orcamentaria
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 24-10-2018
 * @link     no link
 */
class Alteracao_Model_PedidoUnidade extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'alteracao.pedido_unidade';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'peduniid',
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
        'peduniid' => null,
        'pedid'  => null,
        'suoid'  => null,
        'pedunistatus' => null,
    );

    /**
     * Consulta se o c�digo inserido existe e retorna a primeira coluna do primeiro registro.
     *
     * @return array
     */
    public function carregarPorPedido($pedid)
    {
        $sql = "SELECT suoid
                  FROM alteracao.pedido_unidade
                 WHERE pedid = ".$pedid."
                   and pedunistatus = 'A'";

        return $this->carregar($sql);
    }
    
    public function removerUnidades($pedid){
        $sql = "update alteracao.pedido_unidade set pedunistatus = 'I' where pedid = ".$pedid;
        $this->executar($sql);
    }

}
