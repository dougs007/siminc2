<?php

function getmicrotime()
{list($usec, $sec) = explode(" ", microtime());
 return ((float)$usec + (float)$sec);} 

date_default_timezone_set ('America/Sao_Paulo');

//$_REQUEST['baselogin'] = "simec_espelho_producao";

/* configura��es */
ini_set("memory_limit", "2048M");
set_time_limit(0);
/* FIM configura��es */

// carrega as fun��es gerais
include_once "config.inc";
include_once APPRAIZ . "includes/classes_simec.inc";
include_once APPRAIZ . "includes/funcoes.inc";

// CPF do administrador de sistemas
if(!$_SESSION['usucpf'])
$_SESSION['usucpforigem'] = '00000000191';
$arquivos = glob(APPRAIZ."arquivos/*");
echo 'Total de arquivos --> ' . count($arquivos) . '<br /><br />';
$total = 0;
foreach ($arquivos as $count => $filename) {
 	echo ($count+1) . " - $filename size " . filesize($filename) . "<br />";
    echo '<br />';

    $total += filesize($filename);
}

echo '<br /><br />';
echo 'Total ' . $total;
echo '<br /><br />FIM';

?>