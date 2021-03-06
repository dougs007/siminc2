<?php
/**
 * A��o de download relacionada a um item da listagem.
 *
 * @version $Id: Download.php 103403 2015-10-06 21:10:22Z maykelbraz $
 * @filesource
 */

/**
 * A��o de download relacionada a um item da listagem.
 *
 * Cria��o a��es de dois tipo, a primeira � uma a��o normal, como as demais a��es da listagem.<br />
 * O segundo � uma a��o avan�ada, que possibilita o download de extens�es diferentes. Neste<br />
 * segundo caso, � aberta uma janela para o usu�rio selecionar o tipo de extens�o que ele<br />
 * precisa.<br />
 * Exemplo de utiliza��o do modo avan�ado:<pre>
 * $listagem = new Simec_Listagem();
 * ...
 * $configAcao = array('func' => 'nomeCallback', 'formatos' => array('xls', 'pdf'));
 * $listagem->addAcao('download', $configAcao);
 * ...
 * $listagem->render();</pre>
 * A assinatura do callback js deve suportar como primeiro par�metro um array e uma string como o segundo.<br />
 * O primeiro par�metro � um array com todos os par�metros informados durante a configura��o do m�doto, normalmente,<br />
 * � apena o ID da linha. O segundo par�metro � o tipo de arquivo selecionado pelo usu�rio.
 *
 * @package Simec\View\Listagem\Acao
 * @see Simec_Listagem
 * @see Simec_Listagem_Acao
 */
class Simec_Listagem_Acao_Download extends Simec_Listagem_Acao
{
    protected $icone = 'download-alt';
    protected $titulo = 'Download do arquivo';

    /**
     * Renderiza o �cone de a��o.
     *
     * Se Simec_Listagem_Acao_Download::$config['formatos'] for preenchido, a renderiza��o � feita<br />
     * utilizando o formato avan�ado da a��o. Veja a forma de utilizar o modo avan�ado na documenta��o desta<br />
     * classe.<br />
     * Se Simec_Listagem_Acao_Download::$config['formatos'] n�o for preenchido, a rederiza��o � feita<br />
     * da mesma forma que as demais a��es b�sicas.
     *
     * @return string
     */
    protected function renderAcao()
    {
        // -- A��o b�sica
        if (!isset($this->config['formatos'])) {
            return parent::renderAcao();
        }

        // -- A��o avan�ada
        $acao = <<<HTML
<a href="#" class="multi-download" data-cb="%s" data-types="%s" data-params="%s">%s</a>
HTML;
        return sprintf(
            $acao,
            $this->callbackJS,
            str_replace('"', "'", simec_json_encode($this->config['formatos'])),
            $this->getCallbackParams(true),
            $this->renderGlyph()
        );
    }
}
