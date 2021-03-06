<?php
/**
 * Classe de mapeamento da entidade public.identifuso
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
 * Public_Model_Identifuso
 *
 * @category Class
 * @package  A1
 * @author    <>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 
 * @link     no link
 */
class Public_Model_IdentifUso extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'public.identifuso';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'iduid',
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
        'iduid' => null,
        'iducod' => null,
        'idudsc' => null,
        'idustatus' => null,
    );

    /**
     * Consulta se o c�digo inserido existe e retorna a primeira coluna do primeiro registro.
     *
     * @return array
     */
    public function carregarPorCodigo()
    {
        $sql = "SELECT
                    iducod,
                    idudsc
                FROM
                    public.identifuso
                WHERE
                    idustatus = 'A'
                    AND iducod = '". $this->iducod ."'
                    AND iduid <> '". (int)$this->iduid ."'";
                
        return $this->pegaLinha($sql);
    }
}