<?php

class Planacomorc_Controller_DiretrizEstrategica
{
    public function salvar($dados)
    {
        try {
            $mDiretriz = new Planacomorc_Model_DiretrizEstrategica($dados['dieid']);
            $mDiretriz->prsano = $_SESSION['exercicio'];
            $mDiretriz->diecadastro = 'NOW()';
            $mDiretriz->popularDadosObjeto($dados);
            $mDiretriz->salvar(null, null);
            $mDiretriz->commit();
            echo json_encode(array("return" => true));
        } catch (Exception $e) {
            $mDiretriz->rollback();
            echo json_encode(array("return" => false));
        }
    }

    public function excluir($dieid)
    {
        try {
            $mDiretriz = new Planacomorc_Model_DiretrizEstrategica($dieid);
            $mDiretriz->diestatus = 'I';
            $mDiretriz->salvar(null, null);
            $mDiretriz->commit();
            echo json_encode(array("return" => true));
        } catch (Exception $e) {
            $mDiretriz->rollback();
            echo json_encode(array("return" => false));
        }
    }

}