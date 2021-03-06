<?php
/**
 * Rotina que controla o acesso �s p�ginas do m�dulo.
 *
 * Carrega as bibliotecas padr�es do sistema e executa tarefas de inicializa��o.
 *
 * @package Simec\Core
 * @author Cristiano Cabral <cristiano.cabral@gmail.com>
 * @since 25/08/2008
 */

date_default_timezone_set ('America/Sao_Paulo');

/**
 * Obt�m o tempo com precis�o de microsegundos. Essa informa��o � utilizada para
 * calcular o tempo de execu��o da p�gina.
 *
 * @return float
 * @see /includes/rodape.inc
 */
function getmicrotime(){
	list( $usec, $sec ) = explode( ' ', microtime() );
	return (float) $usec + (float) $sec;
}

// obt�m o tempo inicial da execu��o
$Tinicio = getmicrotime();

// controle o cache do navegador
header( "Cache-Control: no-store, no-cache, must-revalidate" );
header( "Cache-Control: post-check=0, pre-check=0", false );
header( "Cache-control: private, no-cache" );
header( "Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT" );
header( "Pragma: no-cache" );

// carrega as fun��es gerais
include_once "config.inc";
include "verificasistema.inc";
include_once APPRAIZ . "includes/funcoes.inc";
include_once APPRAIZ . "includes/classes_simec.inc";
include_once APPRAIZ . "includes/connection/adapter-connection.php";

initAutoload();

include_once APPRAIZ . "includes/controla_requisicao_upload.php";

// abre conex�o com o servidor de banco de dados
$db = new cls_banco();

//Emula outro usu�rio
if ( $_POST['usucpf_simu'] && ( $_SESSION['superuser'] || $db->testa_uma() || $_SESSION['usuuma'] ) )
{
	unset($_SESSION['testa_superuser']);
	unset($_SESSION['acl']);

	$_SESSION['usucpf'] = $_POST['usucpf_simu'];
}

/**
 * Fecha todas as conex�es com base de dados.
 *
 * @see Simec\Core\Db\cls_banco
 * @see Simec\Db\connection
 */
function fechaDb()
{
    global $db;
    $db->close();
    connection::getInstance()->close();
}

simec_magic_quotes();
register_shutdown_function('fechaDb');

//Verifica permiss�es de acesso ao m�dulo requisitado via URL
include APPRAIZ . 'includes/testa_acesso.inc';
?>