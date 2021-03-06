<?php

class Acompanhamento_Controller_Acompanhamentopnc
{
    public static function salvarIndicadorPnc($dados)
    {
        try {
            if($dados['idpid']){
                $acompanhamentoIndicadorPnc = new Acompanhamento_Model_Indicadorpnc($dados['idpid']);
                
                # Gravando hist�rico de altera��o do acompanhamento
                $acompanhamentoHistoricoIdicadorPnc = new Acompanhamento_Model_Historicoindicadorpnc();
                $acompanhamentoHistoricoIdicadorPnc->idpid = $acompanhamentoIndicadorPnc->idpid;
                $acompanhamentoHistoricoIdicadorPnc->usucpf = $_SESSION['usucpf'];
                $acompanhamentoHistoricoIdicadorPnc->hipdata = 'NOW()';
                $acompanhamentoHistoricoIdicadorPnc->hipquantidadeantigo = $acompanhamentoIndicadorPnc->idpquantidade;
                $acompanhamentoHistoricoIdicadorPnc->hipquantidadenovo = $dados['idpquantidade'];
                $acompanhamentoHistoricoIdicadorPnc->salvar();
            } else {
                $acompanhamentoIndicadorPnc = new Acompanhamento_Model_Indicadorpnc();
            }
            $acompanhamentoIndicadorPnc->popularDadosObjeto($dados);

            $acompanhamentoIndicadorPnc->idpquantidade = $acompanhamentoIndicadorPnc->idpquantidade? $acompanhamentoIndicadorPnc->idpquantidade: NULL;
            $acompanhamentoIndicadorPnc->idpdata = $acompanhamentoIndicadorPnc->idpdata? formata_data_sql($acompanhamentoIndicadorPnc->idpdata): NULL;
            $acompanhamentoIndicadorPnc->salvar(NULL, NULL, ['idpjustificativa']);
            $acompanhamentoIndicadorPnc->commit();

            return array(
                'success' => 'Opera��o realizada com sucesso!',
                'acpid' => $dados['acpid']
            );
        } catch (Exception $e){
            $acompanhamentoIndicadorPnc->rollback();
            return array(
                'error' => 'Ocorreu um erro ao executar opera��o!',
                'acpid' => $dados['acpid']
            );
        }
    }
    
    public static function enviar($dados)
    {
        try {
            $acompanhamentoPnc = new Acompanhamento_Model_Acompanhamentopnc((int)$dados['acpid']);
            $acompanhamentoPnc->acpenviado = TRUE;
            $acompanhamentoPnc->salvar();
            $acompanhamentoPnc->commit();

            return array(
                'success' => 'Opera��o realizada com sucesso!',
                'acpid' => $dados['acpid']
            );
        } catch (Exception $e){
            $acompanhamentoPnc->rollback();
            return array(
                'error' => 'Ocorreu um erro ao executar opera��o!',
                'acpid' => $dados['acpid']
            );
        }
    }
    
    public static function salvarAtividadePnc($dados)
    {
        try {
            if($dados['atvid']){
                $acompanhamentoAtividadePnc = new Acompanhamento_Model_Atividadepnc($dados['atvid']);
            } else {
                $acompanhamentoAtividadePnc = new Acompanhamento_Model_Atividadepnc();
            }
            $acompanhamentoAtividadePnc->popularDadosObjeto($dados);
            $acompanhamentoAtividadePnc->atvprodutoqtd = $acompanhamentoAtividadePnc->atvprodutoqtd? desformata_valor($acompanhamentoAtividadePnc->atvprodutoqtd): NULL;
            $acompanhamentoAtividadePnc->salvar(NULL, NULL, ['atvproduto', 'atvprodutoqtd', 'muncod']);
            $acompanhamentoAtividadePnc->commit();

            return array(
                'success' => 'Opera��o realizada com sucesso!',
                'acpid' => $dados['acpid']
            );
        } catch (Exception $e){
            $acompanhamentoAtividadePnc->rollback();
            return array(
                'error' => 'Ocorreu um erro ao executar opera��o!',
                'acpid' => $dados['acpid']
            );
        }
    }
    
    public static function excluirAtividadePnc($dados)
    {
        try {
            $acompanhamentoAtividadePnc = new Acompanhamento_Model_Atividadepnc($dados['atvid']);
            $acompanhamentoAtividadePnc->atvstatus = 'I';
            $acompanhamentoAtividadePnc->salvar(NULL, NULL, ['atvproduto', 'atvprodutoqtd', 'muncod']);
            $acompanhamentoAtividadePnc->commit();

            return array(
                'success' => 'Opera��o realizada com sucesso!',
                'acpid' => $acompanhamentoAtividadePnc->acpid
            );
        } catch (Exception $e){
            $acompanhamentoAtividadePnc->rollback();
            return array(
                'error' => 'Ocorreu um erro ao executar opera��o!',
                'acpid' => $dados['acpid']
            );
        }
    }
    
    public static function excluirAnexoPnc($dados)
    {
        try {
            $arquivo = new Public_Model_Arquivo($dados['arqid']);
            $arquivo->arqstatus = 'I';
            $arquivo->salvar(NULL, NULL, [
                'arqdescricao',
                'arqextensao',
                'arqtamanho',
                'arqdata',
                'arqhora',
                'arqstatus',
                'usucpf',
                'sisid']);
            $arquivo->commit();

            return array(
                'success' => 'Opera��o realizada com sucesso!',
                'acpid' => $dados['acpid']
            );
        } catch (Exception $e){
            $arquivo->rollback();
            return array(
                'error' => 'Ocorreu um erro ao executar opera��o!',
                'acpid' => $dados['acpid']
            );
        }
    }
    
    /**
     * Busca o acompanhamento de acordo com a Janela, Subunidade e Meta PNC
     * 
     * @param integer $suoid
     * @param integer $janid
     * @param integer $mpnid
     * @return object
     */
    public static function buscarAcompanhamentoJanelaSubunidadeMeta($suoid = NULL, $janid = NULL, $mpnid = NULL){
        $modelAcompanhamento = new Acompanhamento_Model_Acompanhamentopnc();
        $modelAcompanhamento->suoid = $suoid;
        $modelAcompanhamento->janid = $janid;
        $modelAcompanhamento->mpnid = $mpnid;
        $acompanhamento = $modelAcompanhamento->buscarPorJanelaSubunidadeMeta();
        return $acompanhamento;
    }

    /**
     * Verifica se o usu�rio logado tem permiss�o pra alterar os dados do acompanhamento da Meta PNC
     * 
     * @param integer $acpid
     * @param integer $ano Opcional
     * @param integer $exercicio Opcional
     * @return boolean
     */
    public static function verificarPermissaoEditar($acpid, $ano = NULL, $exercicio = NULL) {
        $resultado = FALSE;
        $acompanhamentopnc = new Acompanhamento_Model_Acompanhamentopnc($acpid);
        $janela = new Acompanhamento_Model_Janela($acompanhamentopnc->janid);
        $janelaAberta = $janela->isAtual() == 't'? TRUE: FALSE;
        $listaPerfis = pegaPerfilGeral();
        
        if($janelaAberta){
            if(
                # Verifica se o acompanhamento n�o est� enviado/conclu�do
                $acompanhamentopnc->acpenviado != 't'
                &&
                (
                    # Verifica se o perfil do usu�rio � Super Usu�rio, Administrador, PNC ou Unidade
                    in_array(PFL_SUPERUSUARIO, $listaPerfis)
                    || in_array(PFL_ADMINISTRADOR, $listaPerfis)
                    || in_array(PFL_PNC, $listaPerfis)
                )
            ){
                $resultado = TRUE;
            /*
             * Caso o perfil seja Unidade e o Ano n�o esteja preenchido o sistema libera edi��o.
             * Caso o perfil seja Unidade e o ano est� preenchido o sistema s� libera edi��o caso o ano seja igual ao ano do exercicio selecionado no m�dulo
             */
            } else if(in_array(PFL_UNIDADE, $listaPerfis) && (!$ano || ($ano == $exercicio))){
                $resultado = TRUE;
            }
        }
        
        return $resultado;
    }
}