<?php

include_once 'http/code.php';
include_once 'http.php';
include_once 'ssl.php';

/**
 * Classe principal que compoem o componente de comunica��o via SOAP.
 * 
 */
class SoapCurl_Client {
    
    /**
     * Conex�o com o provedor do servi�o
     * 
     * @var resource
     */
    public static $resource;
    
    /**
     * Protocolo de comunica��o
     * 
     * @var SoapCurl_Http
     */
    private $http;
    
    /**
     * Protocolo de seguran�a
     * 
     * @var SoapCurl_Ssl
     */
    private $ssl;
    
    /**
     * Lista de dados para serem enviados na requisi��o
     * 
     * @var array
     */
    private $listField;
    
    /**
     * Documento xml para envio na requisi��o
     * 
     * @var string
     */    
    private $xml;

    /**
     * Caminho fisico do arquivo para ser enviado na requisi��o
     * 
     * @var string
     */
    private $file;
    
    /**
     * Resposta da requisi��o
     * 
     * @var string
     */
    private $response;

    public static function getResource() {
        return self::$resource;
    }

    public function getHttp() {
        return $this->http;
    }

    public function getSsl() {
        return $this->ssl;
    }

    public function getListField() {
        return $this->listField;
    }

    public function getXml() {
        return $this->xml;
    }

    public function getFile() {
        return $this->file;
    }

    public function getResponse() {
        return $this->response;
    }

    public static function setResource($resource) {
        self::$resource = $resource;
        return self;
    }

    public function setHttp(SoapCurl_Http $http) {
        $this->http = $http;
        return $this;
    }

    public function setSsl(SoapCurl_Ssl $ssl) {
        $this->ssl = $ssl;
        return $this;
    }

    public function setListField($listField) {
        $this->listField = $listField;
        return $this;
    }

    public function setXml($xml) {
        $this->xml = $xml;
        return $this;
    }

    public function setFile($file) {
        $this->file = $file;
        return $this;
    }

    public function setResponse($response) {
        $this->response = $response;
        return $this;
    }

    /**
     * Manipula a comunica��o via SOAP.
     * 
     * @param SoapCurl_Http $http
     * @param SoapCurl_Ssl $ssl
     * @param array $listField
     * @param string $xml
     * @param string $file
     * @param string $response
     */
    public function __construct(SoapCurl_Http $http = NULL, SoapCurl_Ssl $ssl = NULL, $listField = NULL, $xml = NULL, $file = NULL, $response = NULL) {
        if(self::$resource){
            $this->close();
        }
        self::$resource = curl_init();
        $this->http = $http? $http: new SoapCurl_Http();
        $this->ssl = $ssl? $ssl: new SoapCurl_Ssl();
        $this->listField = $listField;
        $this->xml = $xml;
        $this->file = $file;
        $this->response = $response;
    }
    
    public function configureHttp(){
        $this->http->configureAll();
        return $this;
    }
    
    public function configureSsl(){
        $this->ssl->configureAll();
        return $this;
    }
    
    public function configureListField(){
        if($this->listField){
            curl_setopt(self::$resource, CURLOPT_POSTFIELDS, $this->listField);
        }
        return $this;
    }
    
    public function configureXml(){
        if($this->xml){
            curl_setopt(self::$resource, CURLOPT_POSTFIELDS, $this->xml);
        }
        return $this;
    }
    
    public function configureFile(){
        if($this->file){
            curl_setopt(self::$resource, CURLOPT_POSTFIELDS, $this->file);
        }
        return $this;
    }
    
    public function configureAll() {
        $this->configureSsl()
            ->configureHttp()
            ->configureListField()
            ->configureXml()
            ->configureFile();
        
        return $this;
    }
    
    /**
     * Faz requisi��o de forma segura configurando todos as op��es e encerrando a sess�o.
     * 
     * @return string
     */
    public function request(){
        # Configura op��es no modulo de conex�o
        $this->configureAll();
        
        # Executa a requisi��o ao servi�o
        $this->execute();
        
        # Busca informa��es sobre o c�digo de resposta da requisi��o
        $this->http->inform();

        # Em caso de n�o ter resposta, busca a mensagem do erro ocorrido
        if($this->http->getCode() != SoapCurl_Http_Code::OK){
            $this->exception();
        }

        # Encerra a sess�o da conex�o e encerra todos os recursos utilizados
        $this->close();
        
        return $this->response;
    }
    
    /**
     * Lan�a exce��o em caso de erro ao realizar requisi��o ou validar crit�rios do protocolo de seguran�a.
     * 
     * @throws Exception
     */
    public function exception(){
        # Exibe erro ocorrido no momento da requisi��o
        $this->ssl->warn();
        if($this->ssl->getError()){
            throw new Exception($this->ssl->getError());
        }
        
        # Exibe erro ocorrido durante o processamento da requisi��o
        throw new Exception($this->response, $this->http->getCode());
    }
    
    /**
     * Exibe o documento xml enviado no momento da requisi��o completo em um arquivo separado pra Baixar/fazer download.
     * 
     * @return VOID
     */    
    public function showXmlRequest(){
        echo $this->xml;
        header('Content-Type: application/xml; charset=utf-8');
        header('Expires: 0');
        header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
        header('Content-Disposition: attachment; filename="request.xml"');
        die;
    }
    
    /**
     * Exibe o documento xml de resposta completo em um arquivo separado pra Baixar/fazer download.
     * 
     * @return VOID
     */
    public function showXmlResponse() {
        echo $this->response;
        header('Content-Type: application/xml; charset=utf-8');
        header('Expires: 0');
        header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
        header('Content-Disposition: attachment; filename="response.xml"');
        die;
    }
    
    /**
     * Faz a requisi��o e retorna a resposta, mas os recursos usados pemanecem em aberto.
     * 
     * @return $this
     */
    public function execute(){
        $this->response = curl_exec(self::$resource);
        return $this;
    }
    
    /**
     * Encerra a sess�o da conex�o e encerra todos os recursos utilizados
     * 
     * @return $this
     */
    public function close(){
        curl_close(self::$resource);
        self::$resource = NULL;
        return $this;
    }
    
}
