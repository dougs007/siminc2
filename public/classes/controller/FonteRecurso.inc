<?php

class Public_Controller_FonteRecurso
{
    public function salvar($dados)
    {
        $url = '?modulo=apoio/fonte_form&acao=A';

        try {
            $mdfonte = new Public_Model_FonteRecurso($dados['fonid']);
            $mdfonte->popularDadosObjeto($dados);
            $mdfonte->salvar(null,null);
            $mdfonte->commit();
            simec_redirecionar($url . '&fonid=' . $mdfonte->fonid, 'success');
        } catch (Exception $e){
            $mdfonte->rollback();
            simec_redirecionar($url, 'error');
        }
    } //end salvar()

    public function excluir($fonid)
    {
        $url = '?modulo=apoio/fonte&acao=A';
        try {
            $mdfonte = new Public_Model_FonteRecurso($fonid);
            $mdfonte->fonstatus = 'I';
            $mdfonte->salvar();
            $mdfonte->commit();
            simec_redirecionar($url, 'success');
        } catch (Exception $e){
            $mdfonte->rollback();
            simec_redirecionar($url, 'error');
        }
    } //end salvar()


    /**
     * Valida se o c�digo da Fonte pode ser alterado ou inserido.
     *
     * @return string|array
     */
    function validaFonte()
    {
        $resposta = array();

        # Verifica se o c�digo inserido est� sendo usado.
        $mFonte = new Public_Model_FonteRecurso();
        $mFonte->foncod = $_REQUEST['foncod'];
        $mFonte->fonid = $_REQUEST['fonid'];
        $verifica = $mFonte->carregarPorCodigo();
        if (!empty($verifica)) {
            $resposta['title'] = NULL;
            $resposta['text'] = 'O c�digo da Fonte ' . $mFonte->foncod . ' j� est� sendo usado!';
            $resposta['type'] = 'error';
        } else {
            $resposta['type'] = 'success';
        }
        return simec_json_encode($resposta);
    }
}
