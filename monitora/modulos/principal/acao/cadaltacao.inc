<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:cadacao.inc
   Finalidade: permitir o controle do cadastro de acao
   */

$modulo=$_REQUEST['modulo'] ;//

if ($_REQUEST['acaid']) 
    $sql= "select a.*, b.prgdsc from acao a, programa b where a.acaid = ".$_REQUEST['acaid'].' and a.prgcod=b.prgcod and a.prgano = b.prgano ';
 
else
  if ($_POST['procura']) $sql= "select a.* from acao a, programa b where a.prgano = '".$_SESSION['exercicio']."' and a.acacod='".strtoupper($_POST['procura'])."' and a.prgcod=b.prgcod and a.prgano = b.prgano   order by a.acacod";


$RS = $db->record_set($sql);
$nlinhas = $db->conta_linhas($RS);

if ($nlinhas >= 0) {

   // as linhas abaixo n�o permitem navegar para al�m dos limites
controla_navegacao($nlinhas);

// fim do controle de navega��o

$res =  $db->carrega_registro($RS,$_POST['registro']);

// a linha abaixo transforma em vari�veis todos os campos do array
if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
	// encontrar o desafio (macro-objetivo)
    $sql= "select prodsc from produto where procod='".$procod."'";
    $res = $db->recuperar($sql);
    if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
        // encontrar descri��o da unidade de medida
    $sql= "select unmdsc from unidademedida where unmcod='".$unmcod."'";
    $res = $db->recuperar($sql);
    if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
        // encontrar descri��o do tipo de a��o          
    $sql= "select tacdsc from tipoacao where taccod='".$taccod."'";
    $res = $db->recuperar($sql);
    if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;   
        // encontrar a fun��o          
    $sql= "select fundsc from ppafuncao where funcod='".$funcod."'";
    $res = $db->recuperar($sql);
    if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;   
        // encontrar a subfun��o          
    $sql= "select sfudsc from ppasubfuncao where sfucod='".$sfucod."'";
    $res = $db->recuperar($sql);
    if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v; 
    
 } else 
 { 
   ?>
<script>
    alert('C�digo da A��o inexistente');
    history.back();
</script>

   <? flush();
  
   exit();
 }
        	
?>
<head>
<title>Cadastro de A��es do Simec</title>
</head>

<body>

<? // inclus�o do menu
include "includes/menu2.inc";?>

<div align="center">
<table  width='75%' border="0" cellspacing="0" cellpadding="3" align="center" style="border: 1px Solid Silver; background-color:#f5f5f5;" align='center'>
  <tr align="center">
    <td width="100%"><strong>Cadastro de A��es</strong>
    &nbsp&nbsp&nbsp<span  title='Indica campo obrigat�rio'><img src="../imagens/obrig.gif"  align="middle"></span>...<a href="javascript:janela('ajuda_usuario.htm',700,500)"><img border="0" src="../imagens/help.gif"  alt='Ajuda desta p�gina' title='Ajuda desta p�gina'></a></td>
  </tr>
</table>

<table  align='center'  width='75%' border="0" cellspacing="0" cellpadding="3" align="center" style="border: 1px Solid Silver; background-color:#f5f5f5;">
  <tr>
    <td width="100%"><font color=red><strong><? print $_SESSION['msgsistema']; $_SESSION['msgsistema'] = '' ?></strong></font></td>
  </tr>
</table>
<form method="POST"  name="formulario">
<input type=hidden name="modulo" value="<?=$modulo?>">
<input type=hidden name="orgao" value=0>
<input type=hidden name="registro" value=<?=$_POST['registro'];?>>
<input type=hidden name="navega" value=0>
<input type=hidden name="procura" value=0>
<input type=hidden name="avalia" value=0>

<? // inclus�o do menu de setas de navega��o
include "includes/setas_navegacao.inc";?> 

    <center>
    <table><tr><td><strong>Programa -   
    <input type="text" name="prgcod" size="5" value='<?=$prgcod?>'>
	<img border="0" src="../imagens/busca.gif"  alt='Procura programa' title='Procura programa' onclick="ProcuraPrograma(this.form)">
    <?='  '.$prgdsc?> 
    
    </strong></td></tr></table>
    <table width='75%' align='center' border="0" cellspacing="0" cellpadding="3" align="center" style="border: 1px Solid Silver; background-color:#f5f5f5;">
      <tr>
        <td></td>
        <td width="25%">C�digo:</td>
        <td width="98%"><input type="text" name="acacod" size="5" value='<?=$acacod?>'>
	<?print $prgcod.'-'.$unicod.'('.$loccod.')'?>
	<img border="0" src="../imagens/busca.gif"  alt='Procura a��o' title='Procura a��o' onclick="ProcuraAcao(this.form)"> 	
      </tr>
      <tr>
        <td></td>
        <td width="25%">T�tulo:</td>
        <td width="98%">
	<textarea rows="2" name="acadsc" cols="50"><?=$acadsc?></textarea></td>
      </tr>
      <tr>
        <td></td>
        <td width="25%">Org�o Or�ament�rio Respons�vel:</td>
        <td width="98%">
	<?
	  $sql = "select orgcod as CODIGO,orgdsc as DESCRICAO from orgao order by orgdsc ";
	  $db->monta_combo("orgcod",$sql,"Selecione o �rg�o respons�vel",'');
	?>
	</td>
      </tr>
      <tr>
        <td></td>
        <td width="25%">Unidade Or�ament�ria Respons�vel:</td>
         <td width="98%">
	<?
	  //if ($orgcod) {
	  $sql = "select unicod as CODIGO,unidsc as DESCRICAO from unidade order by unidsc";
	  //where orgcod ='".$orgcod."' order by unidsc ";
	  $db->monta_combo('unicod',$sql,'Selecione a Unidade','');
	  //}
	?>
	</td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Fun��o:</td>
 	<td width="98%"><input type="text" name="fundsc" size="60" value='<?=$fundsc?>'></td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Subfun��o:</td>
	<td width="98%"><input type="text" name="sfudsc" size="60" value='<?=$sfudsc?>'></td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Finalidade:</td>
	<td width="98%"><textarea rows="2" name="acafinalidade" cols="50"><?=$acafinalidade?></textarea></td>
      </tr>
      <tr>
        <td></td>
        <td width="25%">Descri��o:</td>
        <td width="98%">
	<textarea rows="2" name="acadescricao" cols="50"><?=$acadescricao?></textarea></td>
      </tr>
       <tr>
        <td></td>
        <td width="25%">Produto (Bem ou Servi�o):</td>
        <td width="98%">	<?
	  $sql = "select procod as CODIGO,prodsc as DESCRICAO from produto order by prodsc";	  
	  $db->monta_combo('procod',$sql,'Selecione o produto','');
	  //}
	?></td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Unidade de Medida:</td>
	<td width="98%"><input type="text" name="unmdsc" size="60" value='<?=$unmdsc?>'></td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Especifica��o do Produto:</td>
        <td width="98%"><input type="text" name="acadscproduto" size="60" value='<?=$acadscproduto?>'></td>
      </tr>
  <?
    if (! $acasnoutrasfontes) {?>
        <tr>
        <td width="1%"></td>
        <td width="25%">Tipo de a��o:</td>
        <td width="98%"><input type="hidden" name="taccod" value='3'>N�o or�ament�ria</td>
      </tr>
   <? } else {?>
      <tr>
        <td width="1%"></td>
	 <td width="25%">Tipo de a��o:</td>
        <td width="98%">
	  <table>
	    <tr>
	      <td valign="top"><strong>Or�ament�ria</strong>
	         <table><tr><td> <?=$tacdsc?></td></tr></table>
	      </td>
	      <td valign="top"><strong>Forma de Implementa��o</strong>
                 <table><tr><td> <? 
		 if ($acasnmedireta) 
		 print 'Direta';
		  if ($acasnmedesc) 
		 print '<br>Descentralizada';
		  if ($acasnmelincred) 
		 print '<br>Linha de Cr�dito';
		 $tacdsc?></td></tr></table>
	      </td>
	    </tr>
	  </table>


	</td>

      </tr>
      <?}?>
      <tr>
        <td width="1%"></td>
        <td width="25%">Detalhamento da forma de implementa��o:</td>
        <td width="98%"><textarea rows="2" name="prgdscobjetivoassoc" cols="50"><?=$prgdscobjetivoassoc?></textarea></td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Tipo de Or�amento:</td>
        <td width="98%">
	<? 
	  if ($acasnfiscalseguridade) print 'Fiscal&nbsp;&nbsp;&nbsp;&nbsp;';
  	  if (! $acasnfiscalseguridade) print 'Seguridade&nbsp;&nbsp;&nbsp;&nbsp;';
  	  if ($acasninvestatais) print 'Investimentos Estatais&nbsp;&nbsp;&nbsp;&nbsp;';
	?></td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Base legal:</td>
        <td width="98%"><input type="text" name="acabaselegal" size="60" value='<?=$acabaselegal?>'>
	</td>
      </tr>

      <tr>
        <td width="1%"></td>
        <td width="25%">Unidade Responsavel:</td>
        <td width="98%">
           <input type="text" name="acaunidaderesp" size="60" value='<?=$acaunidresp?>'>
	</td>
      </tr>
     <tr>
        <td></td>
        <td width="25%">Hist�rico da a��o:</td>
        <td width="98%">
	<textarea rows="2" name="acahistorico" cols="50"><?=$acahistorico?></textarea></td>
      </tr>
      <tr>
        <td></td>
        <td width="25%">Data In�cio/T�rmino</td>
        <td width="98%"><input type="text" name="acamesinicio" size="2" value='<?=$acamesinicio?>'>
	<input type="text" name="acaanoinicio" size="4" value='<?=$acaanoinicio?>'>
	<? //if ($prgsntemporario) {
	?>
	  <br><input type="text" name="acamestermino" size="2" value='<?=$acamestermino?>'>
	  <input type="text" name="acaanotermino" size="4" value='<?=$acaanotermino?>'>
	  <?//}?>

	  </td>
      </tr>

       <tr>
        <td></td>
        <td width="25%">Valor Realizado at� <br>o Ano anterior(R$)</td>
        <td width="98%">
	<?//if ($prgsntemporario) {
	?>
            <input type="text" name="acavlrcustoateanoanterior" size="10" value='<?=$acavlrcustoateanoanterior?>'>
	  <?//}?>

	  </td>
      </tr>
      <tr>
        <td width="1%"></td>
        <td width="25%">Estrat�gia de implementa��o:</td>
        <td width="98%">
	<textarea rows="2" name="prgdscestrategia" cols="50"><?=$prgdscestrategia?></textarea>
        </td>
      </tr>
    </table>
    <table>
    <tr><td><input type='button' value='Avaliar' name='btavalia' onclick="AvaliaAcao('1')">
    </center>

<? // inclus�o do menu de setas de navega��o
include "includes/setas_navegacao.inc";?> 
</form>
<script>
    function VerRegistro(cod) {
	//alert (cod+1);
        document.formulario.navega.value = cod;
	document.formulario.submit();
    }
    function AvaliaAcao(cod) {
      
	document.formulario.avalia.value = cod;
	document.formulario.submit();
    }
    function ProcuraAcao(form) {
	document.formulario.procura.value = document.formulario.acacod.value;
	document.formulario.submit();
    }
    function ProcuraPrograma(form) {
	document.formulario.submit();
    }
</script>
</body>
</html>