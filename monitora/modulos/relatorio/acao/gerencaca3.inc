<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier, Cristiano Cabral (cristiano.cabral@gmail.com)
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br), Cristiano Cabral (cristiano.cabral@gmail.com)
   M�dulo:grencaca.inc
   Finalidade: permitir a constru��o de relatorio gerenciais de a��o
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
     include "monitora/modulos//relatorio/acao/listageraca.inc";
}

include APPRAIZ."includes/cabecalho.inc";
?>
<br><script language="JavaScript" src="includes/calendario.js"></script>
<?
$db->cria_aba($abacod_tela,$url,$parametros);
$titulo_modulo='Relat�rio Gerencial de A��o';
monta_titulo($titulo_modulo,'');
?>
<div align="center">
<center>

<form method="POST"  name="formulario">
<input type='hidden' name="modulo" value="<?=$modulo?>">
<input type='hidden' name="relat" >

<center>
<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="1" align="center">
<tr><td colspan=2 align='center'><b>Escolha abaixo os itens desejados e pressione o bot�o "Gerar Relat�rio"</b></td></tr>

<tr> <td align='right' class="SubTituloDireita">Programa:</td>
        <td>	<?$sql = "select prgcod as CODIGO,prgcod || '--' ||prgdsc as DESCRICAO from programa where prgano='".$_SESSION['exercicio']."'order by prgcod ";
	  $db->monta_combo("prgcod",$sql,'S',"Todos os Programas",'','');
	?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">T�tulo (ou parte):</td>
    <td><?=campo_texto('acadsc','N','S','',100,100,'','');?></td>
</tr>
<tr> <td align='right' class="SubTituloDireita">Org�o respons�vel:</td>
        <td><?$sql = "select orgcod as CODIGO,orgdsc as DESCRICAO from orgao order by orgdsc ";
	  $db->monta_combo("orgcod",$sql,'S',"Todos os �rg�os",'','');
	?></td>
</tr>
<tr> <td align='right' class="SubTituloDireita">Unidade respons�vel:</td>
        <td>	<?$sql = "select distinct unicod as CODIGO,unicod || '--' || unidsc as DESCRICAO from unidade order by unicod ";
	  $db->monta_combo("unicod",$sql,'S',"Todos as Unidades",'','');
	?></td>
</tr>
<tr> <td align='right' class="SubTituloDireita">Produto:</td>
        <td>	<?$sql = "select procod as CODIGO,prodsc as DESCRICAO from produto where prostatus='A' order by prodsc ";
	  $db->monta_combo("procod",$sql,'S',"Todos os Produtos",'','');
	?></td>
</tr>
<tr> <td align='right' class="SubTituloDireita">Unidade de Medida:</td>
        <td>	<?$sql = "select unmcod as CODIGO,unmdsc as DESCRICAO from unidademedida where unmstatus='A' order by unmdsc ";
	  $db->monta_combo("unmcod",$sql,'S',"Todas as Unidades",'','');
	?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">Tipo:</td>
    <td><?$sql = "select taccod as CODIGO,tacdsc as DESCRICAO from tipoacao order by tacdsc ";
	  $db->monta_combo("taccod",$sql,'S',"Todos os Tipos",'','');
	?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">Regi�o:</td>
    <td><?$sql = "select regcod as CODIGO,regdsc as DESCRICAO from regiao where regstatus='A' order by regdsc ";
	  $db->monta_combo("regcod",$sql,'S',"Todos as Regi�es",'','');
	?></td>
</tr>

<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">� a��o de RAP:</td>
    <td><input type='radio' value='f' name='cb2'>N�o<input type='radio' value='t' name='cb2'>Sim</td>
</tr>
<tr><td align='right' class="SubTituloDireita">Com Restri��es:</td>
    <td><input type="checkbox" name="cb1" value='REST'></td>
</tr>
<tr><td align='right' class="SubTituloDireita">Data de fim do projeto:</td>
        <td>
		<?=campo_data('dataproj', 'N','S','','S');?> S� � testada para A��o tipo Projeto </td>
</tr>

<tr><td colspan=2><hr></td></tr>
<tr><td></td><td><b>Avalia��o</b></td></tr>
<tr><td align="right" class="subtitulodireita">Situa��o da avalia��o:</td>
<td>
<? $sql = "select tpscod as CODIGO,tpsdsc as descricao from tiposituacao where tpsstatus='A' order by tpsdsc ";
  $db->monta_combo("tpscodav",$sql,'S',"Todas as situa��es",'','');
?>
</td></tr>
<tr><td align="right" class="subtitulodireita">Cor da avalia��o:</td>
<td><?
	$sql = "select corcod as CODIGO,corsignificado as desc , corimgav as imagem from cor where corstatus='A' order by cordsc ";
	$RSradio = $db->record_set($sql);
	$nlinhasradio = $db->conta_linhas($RSradio);
	for ($j=0; $j<=$nlinhasradio;$j++)
	{
	    $res2 =  $db->carrega_registro($RSradio,$j);
	    if(is_array($res2)) foreach($res2 as $k=>$v) ${$k}=$v;
        print "<input type='radio' value='".$codigo."' name='corcodav'  title='".$desc."'>";
	    print "<img src='../imagens/".trim($imagem)."' title='".$desc."'>";
   }
?>
</td></tr>

<tr><td></td><td><b>Parecer</b></td></tr>
<tr><td align="right" class="subtitulodireita">Situa��o do parecer:</td>
<td>
<?    $sql = "select tpscod as CODIGO,tpsdsc as descricao from tiposituacao where tpsstatus='A' order by tpsdsc ";
	  $db->monta_combo("tpscodpar",$sql,'S',"Todas as situa��es",'','');
	  ?>
</td></tr>
<tr><td align="right" class="subtitulodireita">Cor do parecer:</td>
<td><?
	$sql = "select corcod as CODIGO,corsignificado as desc , corimgpar as imagem from cor where corstatus='A' order by cordsc ";
	$RSradio = $db->record_set($sql);
	$nlinhasradio = $db->conta_linhas($RSradio);
	for ($j=0; $j<=$nlinhasradio;$j++)
	{
	    $res2 =  $db->carrega_registro($RSradio,$j);
	    if(is_array($res2)) foreach($res2 as $k=>$v) ${$k}=$v;
        print "<input type='radio' value='".$codigo."' name='corcodpar'  title='".$desc."'>";
	    print "<img src='../imagens/".trim($imagem)."' title='".$desc."'>";
   }
?>


<tr bgcolor="#CCCCCC">
   <td></td>   <td align='center'><input type="button" name="btrelat" value="Gerar Relat�rio" onclick="validar_relatorio()" class="botao"></td>

</tr>
</table>
</center>
</div>
</form>
<?

if ($sqlrel){
  print $sqlrel;
  $RS = $db->record_set($sqlrel);

    $_SESSION['LINHA'] = $db->conta_linhas($RS);
    $_SESSION['title'] = $tit;
    $_SESSION['TIT'][0][0] = 'C�digo ';
    $_SESSION['TIT'][0][1] = 'T�tulo';
    $_SESSION['data']= date('(h:m) d/m/Y');
    $_SESSION['LIN'] = array();
    print '<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center"><tr><td><b>'.$titul. '</b></td><td>';
    if ($_SESSION['LINHA'] >=0) print '<input type="button" class="botao" name="btrelat" value ="Imprimir" align="left" onclick="imprime_rel()">';
    print '</td></tr></table>';

    
    $cabecalho = array('A��o','C�digo ','T�tulo');
    $db->monta_lista($sqlrel,$cabecalho,100,20,'','','');
    //

    if ($_SESSION['LINHA'] >= 0) {
        for ($i=0; $i<=$_SESSION['LINHA'];$i++){
            $res = $db->carrega_registro($RS,$i);
            // a linha abaixo transforma em vari�veis todos os campos do array
            if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
 	       $_SESSION['LIN'][$i][0] = $codigo;
		   $_SESSION['LIN'][$i][1] = $descricao;
        }
     }
}
?>

<script>
function validar_relatorio()
{
    document.formulario.relat.value='r';
   	document.formulario.submit();
}
function alterar_cad(cod,prg)
{
   	location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=principal/acao/cadacao&acao=C&acaid="+cod+"&prgid="+prg;
}
function imprime_rel()
{
    <?
       $browser = get_browser();
       $saiu = false;
       if (is_array($browser)){
       foreach ($browser as $name => $value) {
           if ($value == 'IE') {
           $saiu = true;
          }
       }}
       if ($saiu){?>
           location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_geral1&acao=R";
       <?} else { ?>
           e = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_geral1&acao=R";
          window.open(e, "relatorio","menubar=no,location=no,resizable=yes,scrollbars=yes,status=yes,width=600,height=400'");

      <? } ?>
}

</script>
