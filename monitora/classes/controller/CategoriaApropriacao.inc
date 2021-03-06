<?php

class Monitora_Controller_CategoriaApropriacao
{
    public function salvar($dados)
    {
        $url = '?modulo=apoio/modalidade-pactuacao&acao=A';

        try {
            $mCategoriaApropriacao = new Monitora_Model_CategoriaApropriacao($dados['capid']);
            $mCategoriaApropriacao->popularDadosObjeto($dados);
            $mCategoriaApropriacao->capano = $mCategoriaApropriacao->capano ? $mCategoriaApropriacao->capano : $_SESSION['exercicio'];

            $mCategoriaApropriacao->salvar(null, null, ['capcod', 'capdsc', 'capano', 'capstatus', 'capsiconv', ]);
            $mCategoriaApropriacao->commit();
            simec_redirecionar($url . '&capid=' . $mCategoriaApropriacao->capid, 'success');
        } catch (Exception $e){
            $mCategoriaApropriacao->rollback();
            simec_redirecionar($url, 'error');
        }
    } //end salvar()

    public function excluir($capid)
    {
        $url = '?modulo=apoio/modalidade-pactuacao&acao=A';

        try {
            $mCategoriaApropriacao = new Monitora_Model_CategoriaApropriacao($capid);

            if($mCategoriaApropriacao->existeVinculo()){
                $mensagem = 'O registro n�o pode ser exclu�do pois possui v�nculo com algum PI.';
                $url = '?modulo=apoio/modalidade-pactuacao-form&acao=A&capid=' . $mCategoriaApropriacao->capid;
                simec_redirecionar($url, 'error', $mensagem);
            }

            $mCategoriaApropriacao->capstatus = 'I';
            $mCategoriaApropriacao->salvar();
            $mCategoriaApropriacao->commit();
            simec_redirecionar($url, 'success');
        } catch (Exception $e){
            $mCategoriaApropriacao->rollback();
            simec_redirecionar($url, 'error');
        }
    } //end salvar()
}