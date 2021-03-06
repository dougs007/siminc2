<?php
/**
 * Classe de mapeamento da entidade emendas.beneficiario_historico_alteracao
 *
 * @category Class
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 2018-08-24
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


/**
 * Emendas_Model_BeneficiarioHistoricoAlteracao
 *
 * @category Class
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 2018-08-24
 * @link     no link
 */
class Emendas_Model_BeneficiarioHistoricoAlteracao extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'emendas.beneficiario_historico_alteracao';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'bahid',
    );
    /**
     * Chaves estrangeiras.
     * @var array
     */
    protected $arChaveEstrangeira = array(
        'behid' => array('tabela' => 'seguranca.beneficiario_historico', 'pk' => 'behid'),
    );

    /**
     * Atributos
     * @var array
     * @access protected
     */
    protected $arAtributos = array(
        'bahid' => null,
        'behid' => null,
        'bahcampo' => null,
        'bahanterior' => null,
        'bahnovo' => null,
    );

    /**
     * Retorna todas as altera��es que o usu�rio fez no cadastro de benefici�rio.
     *
     * @param $benid
     * @return array|string
     */
    public function recuperarAlteracoes($benid)
    {
        global $db;

        $sql = "SELECT
                    alt.behid,
                    alt.bahcampo,
                    alt.bahanterior,
                    alt.bahnovo
                FROM emendas.beneficiario_historico_alteracao AS alt
                JOIN emendas.beneficiario_historico AS his ON (alt.behid = his.behid)
                WHERE
                    his.benid = '". $benid ."'
                ORDER BY
                    alt.behid DESC
	    ";

        return $db->carregar($sql);
    }

}
