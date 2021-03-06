<?php

require_once APPRAIZ . 'includes/php-excel/PHPExcel.php';

class Emendas_Controller_Importacao
{
    public function importar($arquivo)
    {
        $url = '?modulo=apoio/importar_emendas&acao=A';
        $modelImportacaoEmenda = new Emendas_Model_ImportacaoEmenda();
        try {
            if(!self::validarCarregamentoArquivo($arquivo['error'])){
                throw new Exception('N�o foi possivel fazer o upload do arquivo, verifique sua conex�o e tente novamente.');
            }
            
            if(!self::validarTipoArquivoXlsx($arquivo['type'])){
                throw new Exception('O arquivo da planilha precisa ser do tipo Planilha do Excel 2007(.xls).');
            }
            
            $arquivoDestino = self::copiarArquivoServidor($arquivo['tmp_name'], $arquivo['name']);
            if(!$arquivoDestino){
                throw new Exception('N�o foi poss�vel salvar o arquivo na pasta do Sistema.');
            }
            
            # Lista de emendas contida no arquivo da Planilha de importa��o
            $listaEmendasArquivo = self::listarEmendasArquivo($arquivoDestino);
            
            $modelImportacaoEmenda->setExercicio((int)$_SESSION['exercicio']);
            $modelImportacaoEmenda->setListaEmendasArquivo($listaEmendasArquivo);
            $modelImportacaoEmenda->importar();
            $modelImportacaoEmenda->commit();
            $_SESSION['mensagem_carregar'] = array('type' => 'success', 'text' => 'Opera��o realizada com sucesso');
        } catch (Exception $e){
            $modelImportacaoEmenda->rollback();
//            simec_redirecionar($url, 'error', $e->getMessage());
            $_SESSION['mensagem_carregar'] = array('type' => 'error', 'text' => $e->getMessage());
        }
        
        return $modelImportacaoEmenda->getListaEmendasArquivo();
    }
    
    /**
     * Lista os nomes das colunas do arquivo de planilha pra importa��o.
     * 
     * @return array
     */
    public static function listarColunasArquivoPlanilha() {
        $listaColunas = array(
            'Autor', 'Partido', 'Emenda', 'Esfera', '�rg�o', 'Unidade Or�ament�ria',
            'Programa', 'A��o', 'Localizador', 'Fonte', 'IDOC', 'IDUSO', 'GND',
            'Modalidade', 'Benefici�rio', 'Benefici�rio (nome)', 'Fun��o', 'Subfun��o',
            'LOA', 'Dota��o Atual', 'Autorizado', 'Valor Indicado (por Benefici�rio)',
            'Valor Priorizado (por Benefici�rio)'
        );
        
        return $listaColunas;
    }

    /**
     * Retorna uma lista de emendas contida no arquivo da Planilha de importa��o
     * 
     * @param string $arquivoDestino
     * @return array
     */
    public static function listarEmendasArquivo($arquivoDestino){
        $listaEmendas = array();
        $reader = PHPExcel_IOFactory::createReader('Excel2007');
        $reader->setReadDataOnly(true);
        $excel = $reader->load($arquivoDestino);
        $worksheet = $excel->getActiveSheet();

        $highestRow = $worksheet->getHighestRow();
        for($row = 2; $row <= $highestRow; ++$row) {
            # Retira codifica��o UTF8 dos textos importados
            $emenda = array_map('utf8_decode', array(
                'autor' => $worksheet->getCellByColumnAndRow(0, $row)->getValue(),
                'partido' => $worksheet->getCellByColumnAndRow(1, $row)->getValue(),
                'emenda' => $worksheet->getCellByColumnAndRow(2, $row)->getValue(),
                'esfera' => $worksheet->getCellByColumnAndRow(3, $row)->getValue(),
                'orgao' => $worksheet->getCellByColumnAndRow(4, $row)->getValue(),
                'unidadeOrcamentaria' => $worksheet->getCellByColumnAndRow(5, $row)->getValue(),
                'programa' => $worksheet->getCellByColumnAndRow(6, $row)->getValue(),
                'acao' => $worksheet->getCellByColumnAndRow(7, $row)->getValue(),
                'localizador' => $worksheet->getCellByColumnAndRow(8, $row)->getValue(),
                'fonte' => $worksheet->getCellByColumnAndRow(9, $row)->getValue(),
                'idoc' => $worksheet->getCellByColumnAndRow(10, $row)->getValue(),
                'iduso' => $worksheet->getCellByColumnAndRow(11, $row)->getValue(),
                'gnd' => $worksheet->getCellByColumnAndRow(12, $row)->getValue(),
                'modalidade' => $worksheet->getCellByColumnAndRow(13, $row)->getValue(),
                'beneficiario' => $worksheet->getCellByColumnAndRow(14, $row)->getValue(),
                'beneficiarioNome' => $worksheet->getCellByColumnAndRow(15, $row)->getValue(),
                'funcao' => $worksheet->getCellByColumnAndRow(16, $row)->getValue(),
                'subFuncao' => $worksheet->getCellByColumnAndRow(17, $row)->getValue(),
                'loa' => $worksheet->getCellByColumnAndRow(18, $row)->getValue(),
                'dotacaoAtual' => $worksheet->getCellByColumnAndRow(19, $row)->getValue(),
                'autorizado' => $worksheet->getCellByColumnAndRow(20, $row)->getValue(),
                'valorIndicado' => $worksheet->getCellByColumnAndRow(21, $row)->getValue(),
                'valorPriorizado' => $worksheet->getCellByColumnAndRow(22, $row)->getValue(),
            ));
            # Retira espa�os
            $listaEmendas[] = array_map('trim', $emenda);
        }

        return $listaEmendas;
    }
    
    /**
     * Copia o arquivo pra pasta de arquivos do sistema.
     * 
     * @param string $origem
     * @param string $nome
     * @return string
     */
    public static function copiarArquivoServidor($origem, $nome) {
        $extensao = substr($nome, strrpos($nome, '.'));
        $pastaDestino = APPRAIZ. 'arquivos/emendas';
        $arquivoDestino = $pastaDestino. '/planilha-importacao-'. date('YmdHis'). $extensao;
        if(!(is_dir($pastaDestino) && move_uploaded_file($origem, $arquivoDestino))){
            $arquivoDestino = NULL;
        }
        
        return $arquivoDestino;
    }
    
    /**
     * Verifica se o arquivo � do tipo Xlsx.
     * 
     * @param string $tipo
     * @return boolean
     */
    public static function validarTipoArquivoXlsx($tipo){
        $valido = FALSE;
        if($tipo == 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'){
            $valido = TRUE;
        }
        
        return $valido;
    }
    
    /**
     * Verifica se o arquivo � do tipo Xlsx.
     * 
     * @param string $status
     * @return boolean
     */
    public static function validarCarregamentoArquivo($status){
        $valido = FALSE;
        if($status == UPLOAD_ERR_OK){
            $valido = TRUE;
        }
        
        return $valido;
    }

}
