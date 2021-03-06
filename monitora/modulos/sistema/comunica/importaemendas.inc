<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Adonias Malosso
   Programador: Adonias Malosso (e-mail: malosso@gmail.com)
   M�dulo:importaemendas.inc
   Finalidade: permitir importar os dados da base de emendas da C�mara
   */
$modulo=$_REQUEST['modulo'] ;
include APPRAIZ."includes/cabecalho.inc";

if ($_REQUEST['__frmenviado'])
{
	$testaupload = (boolean)$_REQUEST["testaupload"];
	echo "<pre>";
	include SISRAIZ."/modulos/sistema/comunica/processaemendas.inc";
	echo "</pre>";
	exit;
}
?>
<br>
<?
$db->cria_aba($abacod_tela,$url,$parametros);
$titulo_modulo='Importa��o de Dados de Emendas';
monta_titulo($titulo_modulo,'');
$anoorigem=$_REQUEST['anoorigem'];
$anodestino=$_REQUEST['anodestino'];

?>
<link rel="stylesheet" type="text/css" href="../includes/Estilo.css">
<link rel='stylesheet' type='text/css' href='../includes/listagem.css'>
<script language="JavaScript" src="../includes/funcoes.js"></script>
<form method="POST" enctype="multipart/form-data" name="formulario">
<input type="hidden" name="modulo" value="<?=$modulo?>">
<input type="hidden" name="__frmenviado" value="0">
<table class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="1" align="center">
    <tr>
      <td colspan="2">
        <p>O recebimento de dados de Emendas dever� ocorrer uma vez ao ano, ap�s sua aprova��o no 
        Congresso Nacional.</p>
        <p>Ao pressionar o bot�o "Carregar dados", o sistema ir� ler o arquivo no formato CSV e fazer 
        uma migra��o seletiva de dados, incluindo os novos e alterando, se for o caso, os antigos.</p>
        <p>Para gerar o arquivo CSV de importa��o:
          <ul>
            <li>Acesse a base de Elabora��o do or�amento da uni�o - Aut�grafo; fornecida pela C�mara dos 
            Deputados.</li>
            <li>Execute a consulta Emendas - Aprovadas por Autor Todas.<li>
            <li>Exporte o resultado como CSV.</i>
            <li>Fa�a o upload do arquivo no formul�rio abaixo.</i>            
          </ul>
        </p>
      </td>
	</tr>
	<tr>
	  <td class="subTituloDireita" width="200">Arquivo:</td>
	  <td><input type="file" name="arqEmendas"/></td>
	</tr>
	<tr>
	  <td class="subTituloDireita" width="200">Somente testar o upload?<br/>(as mudan�as n�o ser�o aplicadas)</td>
	  <td><input type="checkbox" name="testaupload" value="1"></td>
	</tr>
	<tr>
	  <td colspan="2" align="center"><input type="button" class="botao" name="enviar" value="Enviar" onclick="frmEnviar()"></td>
	</tr>
</table>
</form> 
<script language="Javascript">
function frmEnviar	() {
	if( window.confirm( "Este processo pode sobrescrever dados existentes e levar algus minutos.\nConfirma a importa��o de dados de Emendas ?") ) {
		document.formulario.__frmenviado.value = 1;	
		document.formulario.submit();
	}
	else {
		return false;
	}
}
</script>