<?php
	
class ContatosObra extends Modelo{
	
    /**
     * Nome da tabela especificada
     * @var string
     * @access protected
     */
    protected $stNomeTabela = "obras2.contatos_obra";	

    /**
     * Chave primaria.
     * @var array
     * @access protected
     */
    protected $arChavePrimaria = array( "cobid" );

    /**
     * Atributos
     * @var array
     * @access protected
     */    
    protected $arAtributos     = array(
									  	'cobid' => null, 
									  	'entid' => null, 
									  	'tpcid' => null, 
									  	'obrid' => null, 
									  	'cobstatus' => null, 
									  	'cobdtinclusao' => null, 
									  );

    /**
     * Retorna os usu�rios referentes ao prefeito e prefeitura da obra
     */
    public function getContatosPrefeitura()
    {
    }

    /**
     * Retorna os usu�rios referentes ao secret�rio e secretaria da obra
     */
    public function getContatosSecreteria()
    {
    }

    /**
     * Retorna os usu�rios referentes aos respons�veis do FNDE pela bra
     */
    public function getContatosFNDE()
    {
    }

    /**
     * Retorna os usu�rios referentes aos Gestores MI e Fiscais MI da obra
     */
    public function getContatosEmpresaMi(){

    }

    /**
     * Retorna os usu�rios referentes aos Gestores e Fiscais da obra
     */
    public function getContatos($obrid)
    {
        $obra = new Obras($obrid);
        $sql = "select
                    u.*
                from obras2.usuarioresponsabilidade ur
                    inner join seguranca.usuario u on u.usucpf = ur.usucpf
                    inner join seguranca.usuario_sistema us on us.usucpf = u.usucpf and sisid = 147 and us.susstatus = 'A' and us.suscod = 'A'
                    left join obras2.empreendimento e on e.empid = {$obra->empid}
                where
                    ur.rpustatus = 'A' AND
                    u.suscod = 'A' AND
                    us.suscod = 'A' AND
                    --u.usustatus = 'A' AND
                    ( (ur.empid = {$obra->empid}) or (ur.pflcod IN (946) and ur.entid = e.entidunidade) )";

        return $this->carregar($sql);
    }
}