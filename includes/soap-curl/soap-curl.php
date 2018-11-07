<?php

include_once 'soap-curl-http.php';
include_once 'soap-curl-ssl.php';

/**
 * Classe principal que compoem o componente de comunica��o via SOAP.
 * 
 */
class soapCurl {
    
    /**
     * Conex�o com o provedor do servi�o
     * 
     * @var resource
     */
    public static $resource;
    
    /**
     * Protocolo de comunica��o
     * 
     * @var soapCurlHttp
     */
    private $http;
    
    /**
     * Protocolo de seguran�a
     * 
     * @var soapCurlSsl
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

    public function setHttp(soapCurlHttp $http) {
        $this->http = $http;
        return $this;
    }

    public function setSsl(soapCurlSsl $ssl) {
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
     * @param soapCurlHttp $http
     * @param soapCurlSsl $ssl
     * @param array $listField
     * @param string $xml
     * @param string $file
     * @param string $response
     */
    public function __construct(soapCurlHttp $http = NULL, soapCurlSsl $ssl = NULL, $listField = NULL, $xml = NULL, $file = NULL, $response = NULL) {
        self::$resource = $resource? $resource: curl_init();
        $this->http = $http;
        $this->ssl = $ssl;
        $this->listField = $listField;
        $this->xml = $xml;
        $this->file = $file;
        $this->response = $response;
    }
    
    public function configureHttp(){
        $this->http->configureAll(self::$resource);
        return $this;
    }
    
    public function configureSsl(){
        $this->ssl->configureAll(self::$resource);
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
    
    /**
     * Faz requisi��o de forma segura configurando todos as op��es e encerrando a sess�o.
     * 
     * @return string
     */
    public function request(){
        $this->configureHttp()
            ->configureSsl()
            ->configureListField()
            ->configureXml()
            ->configureFile()
            ->execute()
            ->close();
        return $this->response;
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
        return $this;
    }

    /**
     * Ao descarregar o objeto da m�moria encerra a sess�o e os recursos
     *
     * @return VOID
     */
    public function __destruct(){
        $this->close();
    }
    
}
