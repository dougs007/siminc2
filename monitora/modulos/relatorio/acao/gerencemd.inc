<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:gerencaca.inc
   Finalidade: permitir a constru��o de relatorio gerencial de a��es
    */
$modulo=$_REQUEST['modulo'] ;//
unset($_SESSION['LINHA']);
unset($_SESSION['title']);
unset($_SESSION['TIT']);
unset($_SESSION['data']);
unset($_SESSION['LIN']);
$_SESSION['LIN']= array();
$_SESSION['TIT']=array();

if ($_REQUEST['relat']=='planilha')
{
	
	unset ($_REQUEST['relat']);
	if ($_REQUEST['planilha']=='3')
	{
    header('Content-type: application/xls');
    header('Content-Disposition: attachment; filename="planilha_simec.xls"');
	}
	else if ($_REQUEST['planilha']=='5')
	{
    header('Content-type: application/csv');
    header('Content-Disposition: attachment; filename="planilha_simec.csv"');		
	}
    for ($i=0;$i<count($_SESSION['cab']);$i++)
    {
	    if ($i<count($_SESSION['cab'])-1) print trim(($_SESSION['cab'][$i])). ' ' . "\t";
	    else print($_SESSION['cab'][$i]);
    }
    print chr(13);
//  if (count($_SESSION['conteudo'][0])>1) print count($_SESSION['conteudo'][0]);
   // else print_r ($_SESSION['conteudo'][10]);

    if (count($_SESSION['conteudo'][0])>1)
    {
    for ($i=0;$i<count($_SESSION['conteudo']);$i++)
    {
        foreach($_SESSION['conteudo'][$i] as $k=>$v)
        {
            ${$k}=$v;
            if ($v == 't') $v='1';
            else if ($v=='f') $v='0';
            if (! is_int($k) and $v <>'') 
            {
               if (is_numeric($v)) $v=number_format($v,2,',','.');//$v=formata_numero($v);
               print $v."\t";
            }
	     }
	     print chr(13);
     }	
   }
   else
   {
    for ($i=0;$i<count($_SESSION['conteudo']);$i++)
    {
        for ($j=0;$j<count($_SESSION['conteudo'][$i]);$j++)
        {
               
        foreach($_SESSION['conteudo'][$i][$j] as $k=>$v)
        {
            ${$k}=$v;
            if ($v == 't') $v='1';
            else if ($v=='f') $v='0';
            if (! is_int($k) and $v <>'') 
            {
               if (is_numeric($v)) $v=number_format($v,2,',','.');//$v=formata_numero($v);
               print $v."\t";
            }
	     }
	     print chr(13);
            }
     }   
   }   
	 exit();
}


if ($_REQUEST['relat']=='planilha_lista')
{
	unset ($_REQUEST['relat']);
	if ($_REQUEST['planilha']=='4')
	{
    header('Content-type: application/xls');
    header('Content-Disposition: attachment; filename="planilha_simec.xls"');
	}
	else if ($_REQUEST['planilha']=='6')
	{
    header('Content-type: application/csv');
    header('Content-Disposition: attachment; filename="planilha_simec.csv"');		
	}
    for ($i=1;$i<count($_SESSION['cab']);$i++)
    {
	    if ($i<count($_SESSION['cab'])-1) print trim(($_SESSION['cab'][$i])). ' ' . "\t";
	    else print($_SESSION['cab'][$i]);
    }
    print chr(13);
    if (count($_SESSION['conteudo'][0])>1)
    {
    for ($i=1;$i<count($_SESSION['conteudo']);$i++)
    {
        foreach($_SESSION['conteudo'][$i] as $k=>$v)
        {
        	if ($k<>'acao'){
            ${$k}=$v;
            if ($v == 't') $v='1';
            else if ($v=='f') $v='0';
            if (! is_int($k) and $v <>'') 
            {
               if (is_numeric($v)) $v=number_format($v,2,',','.');
               print $v."\t";
            }
        	}
	     }
	     print chr(13);
     }	
   }
	 exit();
}

if ($_REQUEST['relat']=='r')
{
  unset($sqlrel);
  include (APPRAIZ.$_SESSION['sisdiretorio']."/modulos/relatorio/acao/listageraca.inc");
}
include APPRAIZ."includes/cabecalho.inc";
?>
<br>
<div class="notprint">
<?
$db->cria_aba($abacod_tela,$url,$parametros);
$titulo_modulo='Relat�rio Gerencial de A��o';
monta_titulo($titulo_modulo,'');
?>
<div align="center">
<center>
<script language="JavaScript" src="../includes/calendario.js"></script>
<form method="POST"  name="formulario">
<input type='hidden' name="modulo" value="<?=$modulo?>">
<input type='hidden' name="relat" >
<input type='hidden' name="planilha" >

<center>
<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="1" align="center">
<tr><td colspan=2 align='center'><b>Escolha Listagem ou Dados Gerais. Se escolher Dados Gerais, marque pelo menos um dos dados. <br>Escolha os itens desejados (Filtros). <br>Pressione o bot�o "Gerar Relat�rio"</b></td></tr>
<tr><td colspan=2><hr></td></tr>
<tr valign='top'><td ><input type="radio" value="L" name="lista" onclick="mostra_div('L')"
<?if ($_REQUEST['lista']=='L') print '   checked'?>><b>Listagem</b></td><td><input type="radio" value="G" name="lista" onclick="mostra_div('D')" <?if ($_REQUEST['lista']=='G') print '   checked'?>><b>Dados gerais</b><br>
<div style='display:none' id='dadger'>
<input type='checkbox' name='dadobas' value='d' <?if ($_REQUEST['dadobas']) print '   checked'?>>Dados B�sicos
&nbsp;&nbsp;<input type='checkbox' name='avapar' value='avp' <?if ($_REQUEST['avapar']) print '   checked'?>>Avalia��o
&nbsp;&nbsp;<input type='checkbox' name='finevo' value='fin' <?if ($_REQUEST['finevo']) print '   checked'?>>Execu��o Financeira
<br><input type='checkbox' name='fisevo' value='fis' <?if ($_REQUEST['fisevo']) print '   checked'?>>Execu��o F�sica
&nbsp;&nbsp;<input type='checkbox' name='fisevotot' value='fistot' <?if ($_REQUEST['fisevotot']) print '   checked'?>>Execu��o F�sica (Totais)<br>
<input type='checkbox' name='plantrab' value='plant' <?if ($_REQUEST['plantrab']) print '   checked'?>>Plano de Trabalho
&nbsp;&nbsp;<input type='checkbox' name='respro' value='res' <?if ($_REQUEST['respro']) print '   checked'?>>Restri��es e Provid�ncias
<input type='checkbox' name='paralt' value='pag' <?if ($_REQUEST['paralt']) print '   checked'?>>Parecer da Alta Gest�o&nbsp;&nbsp;
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
      $prgid = $_REQUEST['prgid'];
	  $db->monta_combo("prgid",$sql,'S',"Todos os Programas",'atualizaComboAcao','');
	?></td>
</tr>
<?
	  if ($_REQUEST["prgid"]) {?>
<tr> <td align='right' class="SubTituloDireita">A��o:</td>
        <td>
        <?
        $acaid =$_REQUEST['acaid'];
        $sql = "select acaid as CODIGO,acacod ||'.'||unicod ||'.'||loccod||'-'||acadsc as DESCRICAO from acao where prgid=".$_REQUEST["prgid"]." order by acacod ";
	    $db->monta_combo("acaid",$sql,'S',"Todas as a��es",'','','',490);
	?></td>
</tr>
<?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Org�o:</td>
        <td >
	<?
   $orgcod =$_REQUEST["orgcod"];
    $sql = "select orgcod as CODIGO,orgdsc as DESCRICAO from orgao order by orgdsc ";
	  $db->monta_combo("orgcod",$sql,$habil,"Todos os �rg�os",'atualizaComboUnidade','');
	?><br> <input type="checkbox" name="exceto" value='1' title='Filtrar todos os �rg�os com exce��o do MEC'><b>Exceto o <?=$_SESSION['ittabrev']?></b></td>
      </tr>
	<?
	  if ($_REQUEST["orgcod"]) {
   $unicod =$_REQUEST['unicod'];
        ?>
      <tr bgcolor="#F2F2F2">
        <td align='right' class="SubTituloDireita">Unidade Or�ament�ria (UO):</td>
         <td >
         <?

$sql = "select unicod as CODIGO,unicod||' - '||unidsc as DESCRICAO from unidade where unistatus='A' and unitpocod='U' and orgcod ='".$_REQUEST["orgcod"]."' order by unidsc ";
$db->monta_combo("unicod",$sql,'S',"Todas as Unidades",'atualizaComboUnidade','');
?>
	</td>
      </tr>
<?}?>
	  <?
	      $org = substr($_SESSION['ittorgao'],0,2);
	  if ($unicod == $org.'101' and $orgcod==$_SESSION['ittorgao']) {?>
      <tr bgcolor="#F2F2F2">
        <td align = 'right' class="subtitulodireita">Unidade Gestora (UG):</td>
         <td >
	<?
	  $sql = "select ungcod as CODIGO,ungcod||' - '||ungdsc as DESCRICAO from unidadegestora where ungstatus='A' and unitpocod='U' and unicod ='".$unicod."' order by ungdsc ";
	  $db->monta_combo("ungcod",$sql,'S',"Todas as Unidades Gestoras",'','');
	   print obrigatorio();
	?>
	</td>
      </tr>

	  <?}
	?>
<tr><td align='right' class="SubTituloDireita">Somente C�digo (separe com ponto e v�rgula):</td>
    <td><?=campo_texto('acacodbusca','N','S','Entre com os c�digos separados por ponto e v�rgula.Exemplo:09hk;6336',100,100,'','');?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">T�tulo (ou parte):</td>
    <td><?=campo_texto('acadsc','N','S','Entre com uma parte do T�tulo (qualquer parte)',100,100,'','');?></td>
</tr>
<tr>
<td align='right' class="SubTituloDireita">Produto:</td>
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
    <td><?$sql = "select taccod as CODIGO,tacdsc as DESCRICAO from tipoacao where tacstatus='A' order by tacdsc ";
	  $db->monta_combo("taccod",$sql,'S',"Todos os Tipos",'','');
	?></td>
</tr>
<tr><td align='right' class="SubTituloDireita">Regi�o:</td>
    <td><?$sql = "select regcod as CODIGO,regdsc as DESCRICAO from regiao where regstatus='A' order by regdsc ";
	  $db->monta_combo("regcod",$sql,'S',"Todos as Regi�es",'','');
	?></td>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">RAP:</td>
    <td><input type='radio' value='f' name='cbrap'>N�o<input type='radio' value='t' name='cbrap'>Sim</td>
</tr>
<tr><td align='right' class="SubTituloDireita">Emenda:</td>
    <td><input type='radio' value='f' name='cbemenda'>N�o<input type='radio' value='t' name='cbemenda'>Sim</td>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">Data de fim do projeto:</td>
        <td>
		<?=campo_data('dataproj', 'N','S','','S');?> S� � testada para A��o tipo Projeto </td>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">Restri��es:</td>
    <td> <input type="radio" name="cbrp" value='N'>Ainda sem solu��o <input type="radio" name="cbrp" value='S'>Solucionadas  <input type="radio" name="cbrp" value='A'>Ambas</td>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td align='right' class="SubTituloDireita">Com Parecer da Alta Gest�o:</td>
    <td><input type="checkbox" name="cbpalt" value='REST'></td>
</tr>
</tr>
<tr><td colspan=2><hr></td></tr>
<tr><td></td><td><b>Avalia��o</b></td></tr>
<tr><td align='right' class="SubTituloDireita">Sem Avalia��o:</td>
    <td><input type="checkbox" name="cbsaval" value='saval'></td>
</tr>
<tr><td align="right" class="subtitulodireita">Situa��o da Avalia��o:</td>
<td>
<?    $sql = "select tpscod as CODIGO,tpsdsc as descricao from tiposituacao where tpsstatus='A' order by tpsdsc ";
	  $db->monta_combo("tpscodav",$sql,'S',"Todas as situa��es",'','');
	  ?>
</td></tr>
<tr><td align="right" class="subtitulodireita">Cor da avalia��o:</td>
<td><?
	$sql = "select corcod as CODIGO,corsignificado as desc , corimgav as imagem from cor where corstatus='A' order by corcod desc ";
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
<tr><td colspan=2><hr></td></tr>
<tr><td></td><td><b>Valida��o</b></td></tr>
<tr><td align='right' class="SubTituloDireita">N�o validado:</td>
    <td><input type="checkbox" name="cbsvalid" value='cbs'></td>
</tr>

<tr><td align='right' class="SubTituloDireita">Valida��o:</td>
    <td> <input type="radio" name="cbval" value='1'>Concord�ncia <input type="radio" name="cbval" value='2'>Pend�ncia  <input type="radio" name="cbval" value='3'>Discord�ncia</td>
</tr>


<tr><td colspan=2><hr></td></tr>
<tr><td align="right" class="subtitulodireita">Periodo:</td>
<td>In�cio <?=campo_data('dataini', 'N','S','','S');?> &nbsp;&nbsp;Fim <?=campo_data('datafim', 'N','S','','S');?> (Obs: O Per�odo s� � considerado para efeito de monitoramento)

</td></tr>

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
     include APPRAIZ.$_SESSION['sisdiretorio']."/modulos/relatorio/acao/montageraca.inc";
  else
     include APPRAIZ.$_SESSION['sisdiretorio']."/modulos/relatorio/acao/montadadosaca.inc";
}
?>

<script>
function validar_relatorio()
{
	if (!validaRadio(document.formulario.lista,'Listagem ou Dados Gerais')) return;
    // se existir data de fim do projeto, ent�o ela deve ser v�lida
    if (document.formulario.dataproj.value !='')
    {
       if (!validaData(document.formulario.dataproj))
       {
     	  alert("Data de fim do projeto inv�lida.");
		  document.formulario.dataproj.focus();
		  return;
       }
    }
	// se existir data de inicio, ent�o ela deve ser v�lida
    if (document.formulario.dataini.value !='')
    {
      if (!validaData(document.formulario.dataini))
      {
     	alert("Data de in�cio inv�lida.");
		document.formulario.dataini.focus();
		return;
      }
    }

    // se existir data de fim, ent�o ela deve ser v�lida
    if (document.formulario.datafim.value !='')
    {
      if (!validaData(document.formulario.datafim))
      {
     	alert("Data de fim inv�lida.");
		document.formulario.datafim.focus();
		return;
      }
     }
    // se n�o existir data de inicio, ent�o n�o pode existir data de fim
    if (document.formulario.dataini.value == '')
    {
      if (document.formulario.datafim.value != '')
      {
     	alert("Se existe data de fim, deve existir data de in�cio.");
		document.formulario.dataini.focus();
		return;
      }
    }
    // se existir data de inicio, ent�o tem que existir data de fim
    if (document.formulario.dataini.value !='')
    {
      if (document.formulario.datafim.value == '')
      {
     	alert("Se existe data de inicio, deve existir data de fim.");
		document.formulario.datafim.focus();
		return;
      }
    }
    
    // se n�o existir data de fim, ent�o n�o pode existir data de inicio
    if (document.formulario.datafim.value =='')
    {
      if (document.formulario.dataini.value != '')
      {
     	alert("Se existe tdata de fim, deve existir data de inicio.");
		document.formulario.dataini.focus();
		return;
      }
    }
    // a data fim tem que ser posterior a data inicio
     if (!validaDataMaior(document.formulario.dataini , document.formulario.datafim))
	  {
		alert("Data de Fim n�o pode ser Anterior que Data Inicio.");
		document.formulario.datafim.focus();
		return;
      }
    
    

	if (document.formulario.lista[1].checked)
    {
       if (! document.formulario.plantrab.checked && ! document.formulario.dadobas.checked && ! document.formulario.avapar.checked && ! document.formulario.finevo.checked && ! document.formulario.fisevo.checked && ! document.formulario.fisevotot.checked && ! document.formulario.respro.checked && ! document.formulario.paralt.checked ) {alert ('Preencher pelo menos um dos Dados Gerais'); return;}
       }
    document.formulario.relat.value='r';
   	document.formulario.submit();
}
function alterar_cad(cod,cod2)
{
   	location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=principal/acao/cadacao&acao=C&acaid="+cod+"&prgid="+cod2;

}

function imprime_rel(cod)
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
          if (cod == 1) {
           location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_geral1&acao=R";
          };
          if (cod== 2) {
           location.href = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_gerenaca&acao=R";
          }
          if (cod>2) {
          	if (cod ==3) document.formulario.relat.value='planilha';
          	if (cod ==4) document.formulario.relat.value='planilha_lista'; 
          	if (cod ==5) document.formulario.relat.value='planilha';
          	if (cod ==6) document.formulario.relat.value='planilha_lista';             	
          	document.formulario.planilha.value=cod;         	
                document.formulario.submit();
            }
       <?} else { ?>
          if (cod == 1) {
           e = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_geral1&acao=R";
          window.open(e, "relatorio","menubar=no,location=no,resizable=yes,scrollbars=yes,status=yes,width=600,height=400'");
        }
          if (cod== 2) {
           e = "<?=$_SESSION['sisdiretorio']?>.php?modulo=relatorio/prn_gerenaca&acao=R";
          window.open(e, "relatorio","menubar=no,location=no,resizable=yes,scrollbars=yes,status=yes,width=600,height=400'");
            }
          if (cod>2) {
          	if (cod ==3) document.formulario.relat.value='planilha';
          	if (cod ==4) document.formulario.relat.value='planilha_lista'; 
          	if (cod ==5) document.formulario.relat.value='planilha';
          	if (cod ==6) document.formulario.relat.value='planilha_lista';          	
          	document.formulario.planilha.value=cod;         	
                document.formulario.submit();
            }  
           

      <? } ?>
}
  function atualizaComboUnidade(cod)
  {
	 if (cod > 0) {document.formulario.submit()};
    }
  function atualizaComboAcao(cod)
  {
	 if (cod > 0) {document.formulario.submit()};
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

</script>