<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:gerencprg.inc
   Finalidade: permitir a constru��o de relatorio gerencial de programas
    */
$modulo=$_REQUEST['modulo'] ;//
unset($_SESSION['LINHA']);
unset($_SESSION['title']);
unset($_SESSION['TIT']);
unset($_SESSION['data']);
unset($_SESSION['LIN']);
$_SESSION['LIN']= array();
$_SESSION['TIT']=array();

if ($_REQUEST['relat']=='r')
{
  unset($sqlrel);
  //if ($_REQUEST['lista']=='L')
     include APPRAIZ.$_SESSION['sisdiretorio']."/modulos/relatorio/programa/listagerprg.inc";
}

include APPRAIZ."includes/cabecalho.inc";
?>
<br>
<div class="notprint">
<?
$db->cria_aba($abacod_tela,$url,$parametros);
$titulo_modulo='Relat�rio Gerencial de Programas';
monta_titulo($titulo_modulo,'');
?>
<div align="center">
<center>
<script language="JavaScript" src="../includes/calendario.js"></script>
<form method="POST"  name="formulario">
<input type='hidden' name="modulo" value="<?=$modulo?>">
<input type='hidden' name="relat" >

<center>

<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="1" align="center">
<tr><td colspan=2 align='center'><b>Escolha Listagem ou Dados Gerais. Se escolher Dados Gerais, marque pelo menos um dos dados. <br>Escolha os itens desejados (Filtros). <br>Pressione o bot�o "Gerar Relat�rio"</b></td></tr>
<tr><td colspan=2><hr></td></tr>
<tr valign='top'><td ><input type="radio" value="L" name="lista" onclick="mostra_div('L')" <?if ($_REQUEST['lista']=='L') print '   checked'?>><b>Listagem</b></td><td><input type="radio" value="G" name="lista" onclick="mostra_div('D')" <?if ($_REQUEST['lista']=='G') print '   checked'?>><b>Dados gerais</b><br>
<div style='display:none' id='dadger'>
<input type='checkbox' name='dadobas' value='d'>Dados B�sicos &nbsp;&nbsp;<input type='checkbox' name='avapar' value='avp'>Avalia��o e Parecer&nbsp;&nbsp;<input type='checkbox' name='finevo' value='fin'>Execu��o Financeira<br><input type='checkbox' name='respro' value='res'>Restri��es e Provid�ncias&nbsp;&nbsp;<input type='checkbox' name='paralt' value='pag'>Parecer da Alta Gest�o&nbsp;&nbsp;
</div>
<?
if ($_REQUEST['lista']=='G')
{
  ?>
<script>
   document.getElementById("dadger").style.visibility = "visible";
   document.getElementById("dadger").style.display = "";
</script>
<?}?>
</td></tr>
<tr><td colspan=2><hr></td></tr>
<tr> <td align='right' class="SubTituloDireita">Programa:</td>
        <td>	<?$sql = "select prgid as CODIGO,prgcod ||'-'||prgdsc as DESCRICAO from programa where prgano='".$_SESSION['exercicio']."' order by prgcod ";
	  $db->monta_combo("prgid",$sql,'S',"Todos os Programas",'','');
	?></td>
</tr>
<tr> <td align='right' class="SubTituloDireita">Org�o respons�vel:</td>
        <td>	<?$sql = "select distinct orgcod as CODIGO,orgdsc as DESCRICAO from orgao where organo = '".$_SESSION['exercicio']."' and  orgstatus='A' order by orgdsc ";
	  $db->monta_combo("orgcod",$sql,'S',"Todos os �rg�os",'','');
	?><br> <input type="checkbox" name="exceto" value='1' title='Filtrar todos os �rg�os com exce��o do MEC'><b>Exceto o <?=$_SESSION['ittabrev']?></b></td>
</tr>
<tr><td align='right' class="SubTituloDireita">T�tulo (ou parte):</td>
    <td><?=campo_texto('prgdsc','N','S','',100,100,'','');?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">Tipo:</td>
    <td><?$sql = "select tprcod as CODIGO,tprnome as DESCRICAO from tipoprograma order by tprnome ";
	  $db->monta_combo("tprcod",$sql,'S',"Todos os Tipos",'','');
	?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">Horizonte temporal:</td>
    <td><input type="radio" value="f" name="prgsntemporario"> Cont�nuo &nbsp;&nbsp; <input type="radio" name="prgsntemporario" value="t">Tempor�rio</td>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">Restri��es:</td>
    <td> <input type="radio" name="cbrp" value='N'>Ainda sem solu��o  <input type="radio" name="cbrp" value='S'>Solucionadas  <input type="radio" name="cbrp" value='A'>Ambas</td>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">Com Parecer da Alta Gest�o:</td>
    <td><input type="checkbox" name="cbpalt" value='REST'></td>
</tr>
</tr>


<tr bgcolor="#CCCCCC">
   <td></td>   <td align='center'><input type="button" name="btrelat" value="Gerar Relat�rio" onclick="validar_relatorio()" class="botao"></td>
</tr>
</table>
</center>
</div>
</form>
</div>
<?

if ($sqlrel){
//print $sqlrel;
  if ($_REQUEST['lista']=='L')
     include APPRAIZ.$_SESSION['sisdiretorio']."/modulos/relatorio/programa/montagerprg.inc";
  else
     include APPRAIZ.$_SESSION['sisdiretorio']."/modulos/relatorio/programa/montadadosprg.inc";
}
?>

<script>
function validar_relatorio()
{
	if (!validaRadio(document.formulario.lista,'Listagem ou Dados Gerais')) return;
	if (document.formulario.lista[1].checked)
    {
       if (! document.formulario.dadobas.checked && ! document.formulario.avapar.checked && ! document.formulario.finevo.checked && ! document.formulario.respro.checked && ! document.formulario.paralt.checked ) {alert ('Preencher pelo menos um dos Dados Gerais'); return;}
       }

    document.formulario.relat.value='r';
   	document.formulario.submit();
}
function alterar_cad(cod)
{
   	location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=principal/programa/cadprograma&acao=C&prgid="+cod;

}
function monitorar_cad(cod)
{
   	location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/programa/relmonitoraprg&acao=R&prgid="+cod;

}

  function mostra_div(cod)
  {
    if (cod == 'L')
    {
	document.getElementById("dadger").style.visibility = "hidden";
	document.getElementById("dadger").style.display = "none";
     }
    if (cod == 'D')
    {
		document.getElementById("dadger").style.visibility = "visible";
		document.getElementById("dadger").style.display = "";
     }
  }
  
function imprime_rel(cod)
{
    <?
       $browser = get_browser();
       $saiu = false;
       foreach ($browser as $name => $value) {
           if ($value == 'IE') {
           $saiu = true;
          }
       }
       if ($saiu){?>
          if (cod == 1) {
           location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_geral1&acao=R";
          };
          if (cod== 2) {
           location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_gerenprg&acao=R";
          }
       <?} else { ?>
          if (cod == 1) {
           e = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_geral1&acao=R";
          window.open(e, "relatorio","menubar=no,location=no,resizable=yes,scrollbars=yes,status=yes,width=600,height=400'");
        }
          if (cod== 2) {
           e = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_gerenprg&acao=R";
          window.open(e, "relatorio","menubar=no,location=no,resizable=yes,scrollbars=yes,status=yes,width=600,height=400'");
            }

      <? } ?>
}

</script>
