<?php
/**
 * Implementa a classe base de cria��o de a��es.
 * @version $Id: Acao.php 97549 2015-05-19 21:13:18Z maykelbraz $
 */

/**
 * Implementa��o base de todas as a��es da listagem. Faz o processamento de condi��es e par�metros adicionais
 * da a��o. Tamb�m faz o parse das a��es para o padr�o bootstrap e retorna a string HTML da a��o (dentro de uma TD).
 *
 * @todo Transformar a��es em singletons
 */
abstract class Simec_Listagem_Acao
{
    /**
     * Indica que o par�metro adicionado � um parametro extra e faz parte da linha de dados do banco.
     */
    const PARAM_EXTRA = 1;
    /**
     * Indica que o par�metro adicionado � um par�metro externo e seu valor � inserido diretamente na callback.
     */
    const PARAM_EXTERNO = 2;

    protected $icone;
    protected $titulo;
    protected $cor = 'default';
    protected $callbackJS;
    protected $dados;

    protected $condicoes = array();

    protected $parametrosExtra = array();
    protected $parametrosExternos = array();

    protected $partesID = array();

    /**
     * Lista de configura��o adicionais da a��o - estas configura��es s�o utilizadas na classe da a��o.
     * @var array
     */
    protected $config = array();

    public function __construct()
    {
        if (!isset($this->icone)) {
            throw new Exception('Esta a��o n�o tem um �cone definido para ela.');
        }
    }

    public function setTitulo($titulo)
    {
        if (!empty($titulo)) {
            $this->titulo = $titulo;
        }
        return $this;
    }

    public function setCallback($callback)
    {
        if (empty($callback)) {
            throw new Exception('A callback da a��o n�o pode ser vazia.');
        }
        $this->callbackJS = $callback;
        return $this;
    }

    public function setDados(array $dados)
    {
        $this->dados = $dados;
        return $this;
    }

    public function addCondicao(array $condicao)
    {
        $this->condicoes[] = $condicao;
        return $this;
    }

    public function addParams($tipo, $params)
    {
        switch ($tipo) {
            case self::PARAM_EXTRA:
                $tpParam = 'parametrosExtra';
                break;
            case self::PARAM_EXTERNO:
                $tpParam = 'parametrosExternos';
                break;
        }

        if (is_array($params)) {
            foreach ($params as $key => $param) {
                $this->{$tpParam}[$key] = $param;
            }
        } else {
            $this->{$tpParam}[$key] = $param;
        }
        return $this;
    }

    public function setPartesID($partesID)
    {
        if (!is_array($partesID) && !empty($partesID)) {
            $partesID = array($partesID);
        }

        foreach ($partesID as $parteID) {
            if (!key_exists($parteID, $this->dados)) {
                throw new Exception("A parte do ID '{$parteID}' n�o existe no conjunto de dados da listagem.");
            }

            $this->partesID[] = $parteID;
        }

        return $this;
    }

    /**
     * Armazena as configura��es adicionais de cada a��o.
     *
     * @param array $config Lista de configura��es especiais da a��o.
     * @return \Simec_Listagem_Acao
     */
    public function setConfig(array $config)
    {
        if (empty($config)) {
            return;
        }

        $this->config = $config;
        return $this;
    }

    /**
     * Retorna o HTML da a��o.
     * @return string
     */
    public function render()
    {
        if (empty($this->dados)) {
            trigger_error('N�o h� dados associados a esta a��o.', E_USER_ERROR);
        }

        if (empty($this->callbackJS)) {
            trigger_error('N�o h� uma callback JS associada a esta a��o.', E_USER_ERROR);
        }

        // -- A��o n�o atende condi��o de exibi��o
        if (!$this->exibirAcao()) {
            return '-';
        }

        return $this->renderAcao();
    }

    /**
     * @todo Criar um m�todo get icon para abstrair o span e poder formatar para todas as a��es.
     */
    protected function renderAcao()
    {
        $acao = <<<HTML
<a href="javascript:%s(%s);" title="%s">%s</a>
HTML;
        return sprintf(
            $acao,
            $this->callbackJS,
            $this->getCallbackParams(),
            $this->titulo,
            $this->renderGlyph()
        );
    }

    /**
     * Cria a lista de parametros que ser� utilizada na chamada da callback.
     * Existem 3 categorias de par�metros:<br />
     * <ul><li><b>id</b>: O primeiro par�metro � o id da linha. O valor do id da linha � o valor<br />
     * do primeiro campo da linha de dados;</li>
     * <li><b>par�metros extra</b>: Ao definir a a��o, o usu�rio pode indicar um conjunto de valores adicionais<br />
     * que devem ser passados para a callback. Eles vem logo depois do id.</li>
     * <li><b>par�metros externos</b>: Tamb�m na defini��o da fun��o, o usu�rio pode indicar um conjunto de valores<br />
     * externos (n�o inclusos no conjunto de dados da linha) que s�o inclusos na lista de par�metros log depois dos<br />
     * par�metros extra.</li></ul>
     *
     * @param bool $paramsComoArray Indica que os par�metros da callback devem ser retornados como um array.
     * @return string
     * @throws Exception Se algum par�metro que n�o existe nos dados da linha for informado na lista de par�metros extras, � gerada uma exce��o.
     * @todo Implementar passagem do nome do parametro como chave do array
     */
    protected function getCallbackParams($paramsComoArray = false)
    {
        $params = array();
        $params[] = "'" . current($this->dados) . "'"; // -- Informando o primeiro par�metro sempre como string

        // -- parametros extras
        foreach ($this->parametrosExtra as $param) {
            if (!key_exists($param, $this->dados)) {
                trigger_error("O par�metro '{$param}' n�o existe no conjunto de dados da listagem.", E_USER_ERROR);
            }
            $params[$param] = "'{$this->dados[$param]}'";
        }
        // -- parametros extras
        foreach ($this->parametrosExternos as $key => $param) {
            $params[$key] = "'{$param}'";
        }

        // -- Transformar a lista de par�metros em um array
        if ($paramsComoArray) {
            $params = '[' . implode(', ', $params) . ']';
            if (!is_null($parametroinicial)) {
                $params = "'{$parametroinicial}', {$params}";
            }
        } else {
            if (!is_null($parametroinicial)) {
                array_unshift($params, "'{$parametroinicial}'");
            }
            $params = implode(', ', $params);
        }

        return $params;
    }

    protected function getAcaoID()
    {
        if (empty($this->partesID)) {
            reset($this->dados);
            return current($this->dados);
        }

        $partes = array_intersect_key(
            $this->dados,
            array_combine(
                $this->partesID,
                array_fill(0, count($this->partesID), null)
            )
        );
        return implode('_', $partes);
    }

    public function __toString()
    {
        return $this->render();
    }

    protected function exibirAcao()
    {
        if (empty($this->condicoes)) {
            return true;
        }

        // -- Se houver uma entrada para a coluna no array de condicionais, as condi��es devem ser avaliadas
        foreach ($this->condicoes as &$condicao) {
            if (empty($condicao['op'])) {
                $condicao['op'] = 'igual';
            }
            $method = 'checa' . ucfirst($condicao['op']);
            // -- Se ao menos uma das condi��es falhar, a a��o n�o deve ser exibida
            if (!$this->$method($this->dados[$condicao['campo']], $condicao['valor'])) {
                return false;
            }
        }

        return true;
    }

    protected function checaIgual($val1, $val2)
    {
        return $val1 == $val2;
    }

    protected function checaDiferente($val1, $val2)
    {
        return $val1 != $val2;
    }

    protected function checaContido($val1, $val2)
    {
        return in_array($val1, $val2);
    }

    protected function renderGlyph()
    {
        $html = <<<HTML
<span class="btn btn-%s btn-sm glyphicon glyphicon-%s"></span>
HTML;
        return sprintf($html, $this->cor, $this->icone);
    }
}
