<?php
/**
 * Classe de mapeamento da entidade emendas.beneficiario_historico
 *
 * @category Class
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 2018-08-23
 * @link     no link
 */


require_once APPRAIZ .'includes/classes/Modelo.class.inc';


/**
 * Emendas_Model_BeneficiarioObservacao
 *
 * @category Class
 * @package  A1
 * @author   DOUGLAS SANTANA FONTES <douglas.fontes@cultura.gov.br>
 * @license  GNU simec.mec.gov.br
 * @version  Release: 2018-08-23
 * @link     no link
 */
class Emendas_Model_BeneficiarioHistorico extends Modelo
{
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = 'emendas.beneficiario_historico';

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array(
        'behid',
    );
    /**
     * Chaves estrangeiras.
     * @var array
     */
    protected $arChaveEstrangeira = array(
        'usucpf' => array('tabela' => 'seguranca.usuario', 'pk' => 'usucpf'),
        'benid' => array('tabela' => 'emendas.beneficiario', 'pk' => 'benid'),
    );

    /**
     * Atributos
     * @var array
     * @access protected
     */
    protected $arAtributos = array(
        'behid' => null,
        'benid' => null,
        'usucpf' => null,
        'behdata' => null,
    );

    /**
     * Retorna lista com usu�rios que fizeram altera��es no cadastro de benefici�rio.
     *
     * @return mixed
     */
    public function recuperarHistorico($benid)
    {
        global $db;

        $sql = "SELECT
                    beh.behid,
                    to_char(beh.behdata, 'DD/MM/YYYY HH24:MI:SS') as behdata,
                    seg.usucpf,
                    seg.usunome,
                    seg.usuemail,
                    '(' || seg.usufoneddd || ') ' || seg.usufonenum as telefone
                FROM emendas.beneficiario_historico beh
                JOIN seguranca.usuario seg ON ( seg.usucpf = beh.usucpf )
                WHERE
                    beh.benid = '".$benid ."'
                ORDER BY
                    beh.behdata desc
        ";

        return $db->carregar($sql);
    }
    
    /**
     * Grava hist�rico de altera��o de um campo especifico do formul�rio.
     * 
     * @param string $campo
     * @param string $valorAnterior
     * @param string $valorNovo
     */
    public function gravarHistoricoCampo($campo, $valorAnterior, $valorNovo){
        $beneficiarioHistoricoAlteracao = new Emendas_Model_BeneficiarioHistoricoAlteracao();
        $beneficiarioHistoricoAlteracao->behid = $this->behid;
        $beneficiarioHistoricoAlteracao->bahcampo = $campo;
        $beneficiarioHistoricoAlteracao->bahanterior = $valorAnterior? $valorAnterior: 'Nenhuma';
        $beneficiarioHistoricoAlteracao->bahnovo = $valorNovo? $valorNovo: 'Nenhuma';
        $beneficiarioHistoricoAlteracao->salvar();
    }
    
    /**
     * Grava historico de altera��o da op��o SubUnidade
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoSubUnidade(array $post, Emendas_Model_Beneficiario $beneficiario){
        if($post['suoid'] != $beneficiario->suoid){
            $subunidadeAnterior = new Public_Model_SubUnidadeOrcamentaria($beneficiario->suoid);
            $subunidadeNova = new Public_Model_SubUnidadeOrcamentaria($post['suoid']);
            
            $this->gravarHistoricoCampo(
                'SubUnidade',
                $subunidadeAnterior->suocod. '-'. $subunidadeAnterior->suonome,
                $subunidadeNova->suocod. '-'. $subunidadeNova->suonome
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Proponente
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoProponente(array $post, Emendas_Model_Beneficiario $beneficiario){
        if($post['proid'] != $beneficiario->proid){
            $proponenteAnterior = new Emendas_Model_Proponente($beneficiario->proid);
            $proponenteNova = new Emendas_Model_Proponente($post['proid']);
            
            $this->gravarHistoricoCampo(
                'Proponente',
                formatar_cnpj($proponenteAnterior->procnpj). '-'. $proponenteAnterior->pronome,
                formatar_cnpj($proponenteNova->procnpj). '-'. $proponenteNova->pronome
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Localiza��o
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoLocalizacao(array $post, Emendas_Model_Beneficiario $beneficiario){
        if($post['esfid'] != $beneficiario->esfid){
            $localizacaoAnterior = new Territorios_Model_Esfera($beneficiario->esfid);
            $localizacaoNova = new Territorios_Model_Esfera($post['esfid']);

            $this->gravarHistoricoCampo(
                'Localiza��o',
                $localizacaoAnterior->esfdsc,
                $localizacaoNova->esfdsc
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Pa�s
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoPais(array $post, Emendas_Model_Beneficiario $beneficiario){
        $listaLocalizacaoBeneficiario = (new Emendas_Model_BeneficiarioLocalizacao())->recuperarPorBeneficiario($beneficiario->benid);
        $listaPaisBeneficiario = $listaLocalizacaoBeneficiario['paiid'];
        $listaPaisPost = retirarValorVazioArray($post['paiid']);
        if(
            array_diff($listaPaisPost, $listaPaisBeneficiario)
            ||
            array_diff($listaPaisBeneficiario, $listaPaisPost)
        ){
            $listaAnteriores = self::formatarListaPais($listaPaisBeneficiario);
            $listaNovas = self::formatarListaPais($listaPaisPost);
            $this->gravarHistoricoCampo(
                'Pa�s',
                join($listaAnteriores, '<br />'),
                join($listaNovas, '<br />')
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o UF
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoUf(array $post, Emendas_Model_Beneficiario $beneficiario){
        $listaLocalizacaoBeneficiario = (new Emendas_Model_BeneficiarioLocalizacao())->recuperarPorBeneficiario($beneficiario->benid);
        $listaUfBeneficiario = $listaLocalizacaoBeneficiario['estuf'];
        $listaUfPost = retirarValorVazioArray($post['estuf']);
        if(
            array_diff($listaUfPost, $listaUfBeneficiario)
            ||
            array_diff($listaUfBeneficiario, $listaUfPost)
        ){
            $listaAnteriores = self::formatarListaUf($listaUfBeneficiario);
            $listaNovas = self::formatarListaUf($listaUfPost);
            $this->gravarHistoricoCampo(
                'UF',
                join($listaAnteriores, '<br />'),
                join($listaNovas, '<br />')
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Munic�pio
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoMunicipio(array $post, Emendas_Model_Beneficiario $beneficiario){
        $listaLocalizacaoBeneficiario = (new Emendas_Model_BeneficiarioLocalizacao())->recuperarPorBeneficiario($beneficiario->benid);
        $listaMunicipioBeneficiario = $listaLocalizacaoBeneficiario['muncod'];
        $listaMunicipioPost = retirarValorVazioArray($post['muncod']);
        if(
            array_diff($listaMunicipioPost, $listaMunicipioBeneficiario)
            ||
            array_diff($listaMunicipioBeneficiario, $listaMunicipioPost)
        ){
            $listaAnteriores = self::formatarListaMunicipio($listaMunicipioBeneficiario);
            $listaNovas = self::formatarListaMunicipio($listaMunicipioPost);
            $this->gravarHistoricoCampo(
                'Munic�pio',
                join($listaAnteriores, '<br />'),
                join($listaNovas, '<br />')
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Delega��o(SubUnidade Delegada)
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoDelegacao(array $post, Emendas_Model_Beneficiario $beneficiario){
        $listaSubUnidadesDelegadasBeneficiario = $beneficiario->recuperarDelegacao();
        $listaSubUnidadesDelegadasPost = retirarValorVazioArray($post['delegacao']);
        if(
            array_diff($listaSubUnidadesDelegadasPost, $listaSubUnidadesDelegadasBeneficiario)
            ||
            array_diff($listaSubUnidadesDelegadasBeneficiario, $listaSubUnidadesDelegadasPost)
        ){
            $listaAnteriores = self::formatarListaSubunidade($listaSubUnidadesDelegadasBeneficiario);
            $listaNovas = self::formatarListaSubunidade($listaSubUnidadesDelegadasPost);
            $this->gravarHistoricoCampo(
                'Delega��o(Subunidade Delegada)',
                join($listaAnteriores, '<br />'),
                join($listaNovas, '<br />')
            );
        }
    }
    
    /**
     * Formata a lista de c�digos de Subunidade pra retornar uma lista com a 
     * descri��o contendo N�mero SIOP e nome da Subunidade pra ser exibido ao usu�rio.
     * 
     * @param array $listaCodigo
     * @return array
     */
    public static function formatarListaSubunidade($listaCodigo = array()){
        $listaDescricao = array();
        foreach($listaCodigo as $codigo){
            $subunidade = new Public_Model_SubUnidadeOrcamentaria($codigo);
            $listaDescricao[] = $subunidade->suocod. '-'. $subunidade->suonome;
        }
        
        return $listaDescricao;
    }
    
    /**
     * Formata a lista de c�digos de Pa�s pra retornar uma lista com a 
     * descri��o contendo nome do Pa�s pra ser exibido ao usu�rio.
     * 
     * @param array $listaCodigo
     * @return array
     */
    public static function formatarListaPais($listaCodigo = array()){
        $listaDescricao = array();
        foreach($listaCodigo as $codigo){
            $pais = new Territorios_Model_Pais($codigo);
            $listaDescricao[] = $pais->paidescricao;
        }
        
        return $listaDescricao;
    }
    
    /**
     * Formata a lista de c�digos de UF pra retornar uma lista com a 
     * descri��o contendo nome do UF pra ser exibido ao usu�rio.
     * 
     * @param array $listaCodigo
     * @return array
     */
    public static function formatarListaUf($listaCodigo = array()){
        $listaDescricao = array();
        foreach($listaCodigo as $codigo){
            $uf = new Territorios_Model_Estado($codigo);
            $listaDescricao[] = $uf->estuf. '-'. $uf->estdescricao;
        }
        
        return $listaDescricao;
    }
    
    /**
     * Formata a lista de c�digos de Munic�pio pra retornar uma lista com a 
     * descri��o contendo nome do Munic�pio pra ser exibido ao usu�rio.
     * 
     * @param array $listaCodigo
     * @return array
     */
    public static function formatarListaMunicipio($listaCodigo = array()){
        $listaDescricao = array();
        foreach($listaCodigo as $codigo){
            $municipio = new Territorios_Model_Municipio($codigo);
            $listaDescricao[] = $municipio->estuf. '-'. $municipio->mundescricao;
        }
        
        return $listaDescricao;
    }

    /**
     * Grava historico de altera��o da op��o N�mero do Processo
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoProcesso(array $post, Emendas_Model_Beneficiario $beneficiario){
        if($post['bennumeroprocesso'] != $beneficiario->bennumeroprocesso){
            $this->gravarHistoricoCampo(
                'N�mero do Processo',
                $beneficiario->bennumeroprocesso,
                $post['bennumeroprocesso']
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Data de In�cio da Vig�ncia
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoVigencia(array $post, Emendas_Model_Beneficiario $beneficiario){
        if($post['beninicio'] != formata_data($beneficiario->beninicio)){
            $this->gravarHistoricoCampo(
                'Data de In�cio da Vig�ncia',
                formata_data($beneficiario->beninicio),
                $post['beninicio']
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o Modalidade de Pactua��o
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoModalidade(array $post, Emendas_Model_Beneficiario $beneficiario){
        if($post['capid'] != $beneficiario->capid){
            $modalidadeAnterior = new Monitora_Model_CategoriaApropriacao($beneficiario->capid);
            $modalidadeNova = new Monitora_Model_CategoriaApropriacao($post['capid']);
            
            $this->gravarHistoricoCampo(
                'Modalidade de Pactua��o',
                $modalidadeAnterior->capdsc,
                $modalidadeNova->capdsc
            );
        }
    }
    
    /**
     * Grava historico de altera��o da op��o TED
     * 
     * @param array $post
     * @param Emendas_Model_Beneficiario $beneficiario
     */
    public function gravarHistoricoTed(array $post, Emendas_Model_Beneficiario $beneficiario){
        $tedAnterior = $beneficiario->bented == 't'?'Sim': 'N�o';
        $tedNovo = $post['bented']?'Sim': 'N�o';
        if($tedAnterior != $tedNovo){
            $this->gravarHistoricoCampo(
                'TED',
                $tedAnterior,
                $tedNovo
            );
        }
    }

}
