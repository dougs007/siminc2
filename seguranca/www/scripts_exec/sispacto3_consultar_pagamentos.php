<?php

header( 'Content-Type: text/html; charset=ISO-8859-1' );
//header( 'Content-Type: text/html; charset=UTF-8' );

define( 'BASE_PATH_SIMEC', realpath( dirname( __FILE__ ) . '/../../../' ) );

set_time_limit( 0 );
error_reporting( E_ALL ^ E_NOTICE );

ini_set( 'soap.wsdl_cache_enabled', '0' );
ini_set( 'soap.wsdl_cache_ttl', 0 );
ini_set( 'default_socket_timeout', '99999999' );

$_REQUEST['baselogin']  = "simec_espelho_producao";//simec_desenvolvimento

// carrega as fun��es gerais
require_once BASE_PATH_SIMEC . "/global/config.inc";
require_once APPRAIZ . "includes/classes_simec.inc";
require_once APPRAIZ . "includes/funcoes.inc";
require_once APPRAIZ . "includes/workflow.php";
require_once APPRAIZ . "www/sispacto3/_funcoes.php";
require_once APPRAIZ . "www/sispacto3/_constantes.php";
require_once APPRAIZ . 'includes/phpmailer/class.phpmailer.php';
require_once APPRAIZ . 'includes/phpmailer/class.smtp.php';

$opcoes = Array(
                'exceptions'	=> 0,
                'trace'			=> true,
                //'encoding'		=> 'UTF-8',
                'encoding'		=> 'ISO-8859-1',
                'cache_wsdl'    => WSDL_CACHE_NONE
);

$soapClient = new SoapClient( WSDL_CAMINHO, $opcoes );

libxml_use_internal_errors( true );
    
// CPF do administrador de sistemas
if(!$_SESSION['usucpf']) {
	$_SESSION['usucpforigem'] = '00000000191';
	$_SESSION['usucpf'] = '00000000191';
}

function getmicrotime() {list($usec, $sec) = explode(" ", microtime()); return ((float)$usec + (float)$sec);}

$microtime = getmicrotime();
    
ini_set("memory_limit", "2048M");

// abre conex��o com o servidor de banco de dados
$db = new cls_banco();

if(!$_REQUEST['numeroDiasProcessamento']) $numeroDiasProcessamento = 30;
else $numeroDiasProcessamento = $_REQUEST['numeroDiasProcessamento'];

for($i=1;$i<=$numeroDiasProcessamento;$i++) {
	$datasel[] = "to_char(NOW(),'YYYY-mm-dd')::date - interval '".$i." day' as data".$i;
}

$datas = $db->pegaLinha("select ".implode(",",$datasel));

for($i=$numeroDiasProcessamento;$i>=1;$i--) {
	$arxml['situacoes']['autenticacao'] 		= array('sistema' => SISTEMA_SGB, 'login' => USUARIO_SGB,'senha' => SENHA_SGB);
	$arxml['situacoes']['programa'] 			= PROGRAMA_SGB;
	$arxml['situacoes']['dataDasAlteracoes'] 	= formata_data($datas['data'.$i]);
	
	$consultarSituacaoDePagamentos_obj = $soapClient->consultarSituacaoDePagamentos( $arxml );
	
	if($consultarSituacaoDePagamentos_obj->situacoes->pagamentos->pagamento) {
		foreach($consultarSituacaoDePagamentos_obj->situacoes->pagamentos->pagamento as $pgs) {
			
			$pboid = $pgs->id;
			
			if(count($pgs->situacoes->situacao)>1) {
				$pg = end($pgs->situacoes->situacao);
			} else {
				$pg = $pgs->situacoes->situacao;
			}
			
			if($pg->codigo==SGB_AUTORIZADA || $pg->codigo==SGB_HOMOLOGADA || $pg->codigo==SGB_PREAPROVADA || $pg->codigo==SGB_ENVIADOAOSIGEF) {
				$docid = $db->pegaUm("SELECT p.docid FROM sispacto3.pagamentobolsista p 
									  INNER JOIN workflow.documento d ON d.docid = p.docid 
									  WHERE pboid='".$pboid."' AND d.esdid='".ESD_PAGAMENTO_AG_AUTORIZACAO_SGB."'");
				if($docid) {
					echo "Pagamento #".$pboid." (".$pg->data.") foi enviado para Aguardando pagamento<br>";
					$result = wf_alterarEstado( $docid, AED_AUTORIZARSGB_PAGAMENTO, $cmddsc = '', array());
				} else {
					echo "Pagamento #".$pboid." (".$pg->data.") N�O foi enviado para Aguardando pagamento<br>";
				}
			}
			
			if($pg->codigo==SGB_ENVIADOBANCO) {
				$docid = $db->pegaUm("SELECT p.docid FROM sispacto3.pagamentobolsista p 
									  INNER JOIN workflow.documento d ON d.docid = p.docid 
									  WHERE pboid='".$pboid."' AND d.esdid='".ESD_PAGAMENTO_AGUARDANDO_PAGAMENTO."'");
				if($docid) {
					echo "Pagamento #".$pboid." (".$pg->data.") foi enviado para Enviado ao Banco<br>";
					$result = wf_alterarEstado( $docid, AED_ENVIARBANCO_PAGAMENTO, $cmddsc = '', array());
				} else {
					echo "Pagamento #".$pboid." (".$pg->data.") N�O foi enviado para Enviado ao Banco<br>";
				}
			}
			
				
			if($pg->codigo==SGB_CREDITADA || $pg->codigo==SGB_SACADA) {
				
				$pagamentobolsista = $db->pegaLinha("SELECT d.docid, d.esdid FROM sispacto3.pagamentobolsista p 
												  INNER JOIN workflow.documento d ON d.docid = p.docid 
												  WHERE pboid='".$pboid."'");
				
				$docid 		  = $pagamentobolsista['docid'];
				$esdid_origem = $pagamentobolsista['esdid'];
				
				if($esdid_origem) {
					$sql = "SELECT aedid FROM workflow.acaoestadodoc WHERE esdidorigem='".$esdid_origem."' and esdiddestino='".ESD_PAGAMENTO_EFETIVADO."'";
					$aedid = $db->pegaUm($sql);
				}
				
				
				if($docid && $aedid) {
					echo "Pagamento #".$pboid." (".$pg->data.") foi enviado para Pagamento Efetivado<br>";
					$result = wf_alterarEstado( $docid, $aedid, $cmddsc = '', array());
				}

			}
		}
	}
	
	inserirDadosLog(array('logrequest'=>$soapClient->__getLastRequest(),'logresponse'=>$soapClient->__getLastResponse(),'logservico'=>'consultarSituacaoDePagamentos'));
	
}

$sql = "UPDATE seguranca.agendamentoscripts SET agstempoexecucao='".round((getmicrotime() - $microtime),2)."' WHERE agsfile='sispacto3_consultar_pagamentos.php'";
$db->executar($sql);
$db->commit();


$db->close();
	
if($_SESSION['usucpf'] == '00000000191') {
	
	unset($_SESSION['usucpf']);
	unset($_SESSION['usucpforigem']);
	
}


echo "fim";


?>