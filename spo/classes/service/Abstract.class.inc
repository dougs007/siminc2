<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Snapshot
 *
 * @author LindalbertoFilho
 */
abstract class Spo_Service_Abstract
{
    /**
     * Conjunto de dados que ser�o trabalhado na service.
     *
     * @var array
     */
    protected $dados = array();

    /**
     * Armazena as mensagens de retorno para o usu�rio.
     *
     * @var Simec_Helper_FlashMessage.
     */
    protected $flashMessage;

    /**
     * Seta os dados que ser�o usados na service.
     *
     * @param array $dados Dados tratados pela service.
     * @return \Simec_Service_Abstract
     */
    public function setDados(array $dados)
    {
        $this->dados = $dados;
        return $this;
    }

    /**
     * Retorna os dados usados na service.
     *
     * @return array
     */
    public function getDados()
    {
        return $this->dados;
    }

    /**
     *
     * @param Simec_Helper_FlashMessage $fm
     * @return \Spo_Service_Abstract
     * @deprecated As mensagens devem ser setadas no arquivo de controle e n�o dentro das services.
     */
    public function setFlashMessage(Simec_Helper_FlashMessage $fm)
    {
        $this->flashMessage = $fm;
        return $this;
    }

    /**
     *
     * @return Simec_Helper_FlashMessage
     */
    public function getFlashMessage()
    {
        return $this->flashMessage;
    }

    /**
     * Valida os dados carregados na service.
     * Para valida��es mais detalhadas, sobreescrever o m�todo.
     *
     * @throws Exception Lan�ada qdo os dados est�o vazios.
     */
    protected function validaDados()
    {
        if (empty($this->dados)) {
            throw new Exception('N�o existem dados carregados.');
        }
        return $this;
    }

    public function __get($name)
    {
        if (!array_key_exists($name, $this->dados)) {
            $nomeClasse = get_class($this);
            throw new Exception("Propriedade solicitada n�o existe ({$nomeClasse}::\${$name}).");
        }
        return $this->dados[$name];
    }

    public function __set($name, $value)
    {
        $this->dados[$name] = $value;
    }

    public function __isset($name)
    {
        return isset($this->dados[$name]);
    }
}
