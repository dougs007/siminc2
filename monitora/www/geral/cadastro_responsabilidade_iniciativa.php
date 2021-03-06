<?php

include "config.inc";
header('Content-Type: text/html; charset=iso-8859-1');
include APPRAIZ."includes/classes_simec.inc";
include APPRAIZ."includes/funcoes.inc";

$db = new cls_banco();
$usucpf = $_REQUEST['usucpf'];
$pflcod = $_REQUEST['pflcod'];

/*
*** INICIO REGISTRO RESPONSABILIDADES ***
*/ 	

if(is_array($_POST['usuprogresp']) && @count($_POST['usuprogresp'])>0) {
	$txtmetasComCoordenador = "";
	$confirmarmetas = 0;
	$concluido = 0; // -1 erro, 0 nao concluido, 1 sucesso
	$metasConfirmados = $_REQUEST["metasConfirmados"];
	
	$sqlSelIniciativa	= "SELECT i.ictid, i.ictdsc FROM monitora.iniciativa i WHERE ictid = %s AND ictstatus = 'A' ";
	
	$sqlInsRpu = "INSERT INTO monitora.usuarioresponsabilidade (ictid, usucpf, rpustatus, rpudata_inc, pflcod, prsano) VALUES ('%s', '%s', '%s', '%s', '%s','".$_SESSION['exercicio']."')";

	$sqlUpdRpu = "UPDATE monitora.usuarioresponsabilidade SET rpustatus = 'I' WHERE ictid = '%s' AND pflcod = ".$pflcod." AND prsano = '{$_SESSION['exercicio']}'";

	$sqlUpdRpuUsu = "UPDATE monitora.usuarioresponsabilidade SET rpustatus = 'I' WHERE usucpf = '".$usucpf."' AND ictid IS NOT NULL AND pflcod = ".$pflcod." AND prsano = '{$_SESSION['exercicio']}'";
	
	// caso nao existam outros coordenadores de planejamento, registrar os itens selecionados
	if(!$confirmarmetas) {
		$sql = $sqlUpdRpuUsu;
		$db->executar($sql);
		foreach ($_POST['usuprogresp'] as $respcod) {
		   $sql = "";
		   if ($respcod>0){
		   $sql = vsprintf($sqlSelIniciativa, $respcod);
           $linha = $db->carregar($sql);
			if(is_array($linha) && count($linha)>=1) {
				foreach ($linha as $objetivo) {
					$ictid = $objetivo["ictid"]; 		
					$dados = array($ictid, $usucpf, 'A', date("Y-m-d H:i:s"), $pflcod); 						
					$sql = vsprintf($sqlInsRpu, $dados);
					$db->executar($sql);
				}
				
			}}
		}
		$concluido = 1;
	}

	if ($concluido>0) {
		$db->commit();
		?>
	<script>
	window.parent.opener.location.reload();self.close();
	</script>
		<?
		exit(0);
	}
}
/*
*** FIM REGISTRO RESPONSABILIDADES ***
*/
?>
<html>
<head>
<META http-equiv="Pragma" content="no-cache">
<title>Iniciativas</title>
<script language="JavaScript" src="/includes/funcoes.js"></script>
<link rel="stylesheet" type="text/css" href="/includes/Estilo.css">
<link rel='stylesheet' type='text/css' href='/includes/listagem.css'>

</head>
<body LEFTMARGIN="0" TOPMARGIN="5" bottommargin="5" MARGINWIDTH="0" MARGINHEIGHT="0" BGCOLOR="#ffffff">
<div align=center id="aguarde"><img src="/imagens/icon-aguarde.gif" border="0" align="absmiddle"> <font color=blue size="2">Aguarde! Carregando Dados...</font></div>
<?flush();?>
<DIV style="OVERFLOW:AUTO; WIDTH:496px; HEIGHT:350px; BORDER:2px SOLID #ECECEC; background-color: White;">
<table width="100%" align="center" border="0" cellspacing="0" cellpadding="2" class="listagem" id="tabela">
<script language="JavaScript">
document.getElementById('tabela').style.visibility = "hidden";
document.getElementById('tabela').style.display  = "none";
</script>
<form name="formulario">
<thead>
	<tr>
		<td valign="top" class="title" style="border-right: 1px solid #c0c0c0; border-bottom: 1px solid #c0c0c0; border-left: 1px solid #ffffff;" colspan="3"><strong>Selecione a(s) Iniciativa(s)</strong></td>
	</tr>
   	<tr bgcolor="<?=$cor?>">
		<th align="center">A��o</th>
		<th align="center">Objetivo Vinculado</th>
		<th align="center">Iniciativa</th>
	</tr>
</thead>
<?

	  $cabecalho = 'Selecione a(s) Iniciativa(s)';
	  $sql = "SELECT 
	  			i.ictid, 
	  			i.ictdsc, 
	  			o.objcod || ' - ' || objdsc AS objdsc
	  		  FROM 
	  		  	monitora.iniciativa i
	  		  INNER JOIN monitora.objetivoiniciativa oi ON oi.ictid = i.ictid
	  		  INNER JOIN monitora.objetivo o ON o.objid = oi.objid AND o.objstatus = 'A'
	  		  WHERE 
	  		  	ictstatus = 'A' AND 
	  		  	prgano = '".$_SESSION['exercicio']."' 
	  		  ORDER BY objdsc, ictdsc";
	 
	  $RS = @$db->carregar($sql);
	  $RS = !$RS ? array() : $RS;
	  $nlinhas = count($RS)-1;
	  for ($i=0; $i<=$nlinhas;$i++)
		 {
			foreach($RS[$i] as $k=>$v) ${$k}=$v;
			if (fmod($i,2) == 0) $cor = '#f4f4f4' ; else $cor='#e0e0e0';
	   ?>
	   		
		   		<tr bgcolor="<?=$cor?>">
					<td align="right">
						<input type="Checkbox" name="prgid" id="<?=$ictid?>" value="<?=$ictid?>" onclick="retorna(<?=$i?>);">
						<!--  
						<input type="Hidden" name="prgdsc" value="<?=$objcod.' - '.$ictdsc?>">
						-->
						<input type="Hidden" name="prgdsc" value="<?=$ictdsc?>">
					</td>
					<td align="justify" style=""><?=resumo($objdsc, 150)?></td>
					<td align="justify" valign="top"><?=$ictdsc?></td>
				</tr>
	   
	   <?}
?>
</table>
</form>
</div>
<form name="formassocia" style="margin:0px;" method="POST">
<input type="hidden" name="usucpf" value="<?=$usucpf?>">
<input type="hidden" name="pflcod" value="<?=$pflcod?>">
<select multiple size="8" name="usuprogresp[]" id="usuprogresp" style="width:500px;" class="CampoEstilo" onchange="moveto(this);">
<?
$sql = "SELECT DISTINCT 
		 i.ictid as codigo, 
		 i.ictdsc AS descricao 
		FROM 
		 monitora.usuarioresponsabilidade ur 
		 INNER JOIN monitora.iniciativa i ON ur.ictid=i.ictid
		 JOIN monitora.objetivoiniciativa oi ON oi.ictid = i.ictid
	  	 JOIN monitora.objetivo o ON o.objid = oi.objid
		WHERE 
		 ur.rpustatus='A' AND 
		 ur.usucpf='$usucpf' AND 
		 ur.pflcod=$pflcod AND 
		 ur.prsano='".$_SESSION['exercicio']."' 
		ORDER BY 2";

$RS = @$db->carregar($sql);

if(is_array($RS)) {
	$nlinhas = count($RS)-1;
	if ($nlinhas>=0) {
		for ($i=0; $i<=$nlinhas;$i++) {
			foreach($RS[$i] as $k=>$v) ${$k}=$v;
    		print " <option value=\"$codigo\">$descricao</option>";		
		}
	}
} else {
?>
	<option value="">Selecione a(s) Iniciativa(s).</option>
<?
}
?>
</select>
</form>
<table width="100%" align="center" border="0" cellspacing="0" cellpadding="2" class="listagem">
<tr bgcolor="#c0c0c0">
<td align="right" style="padding:3px;" colspan="3">
<input type="Button" name="ok" value="OK" onclick="selectAllOptions(campoSelect);document.formassocia.submit();" id="ok">
</td></tr>
</table>
<script language="JavaScript">
document.getElementById('aguarde').style.visibility = "hidden";
document.getElementById('aguarde').style.display  = "none";
document.getElementById('tabela').style.visibility = "visible";
document.getElementById('tabela').style.display  = "";


var campoSelect = document.getElementById("usuprogresp");


if (campoSelect.options[0].value != ''){
	for(var i=0; i<campoSelect.options.length; i++)
		{document.getElementById(campoSelect.options[i].value).checked = true;}
}



function retorna(objeto)
{

	tamanho = campoSelect.options.length;
	if (campoSelect.options[0].value=='') {tamanho--;}
	if (document.formulario.prgid[objeto].checked == true){
		campoSelect.options[tamanho] = new Option(document.formulario.prgdsc[objeto].value, document.formulario.prgid[objeto].value, false, false);
		sortSelect(campoSelect);
	}
	else {
		for(var i=0; i<=campoSelect.length-1; i++){
			if (document.formulario.prgid[objeto].value == campoSelect.options[i].value)
				{campoSelect.options[i] = null;}
			}
			if (!campoSelect.options[0]){campoSelect.options[0] = new Option('Selecione a(s) Iniciativa(s).', '', false, false);}
			sortSelect(campoSelect);
	}
}

function moveto(obj) {
	if (obj.options[0].value != '') {
		document.getElementById(obj.value).focus();}
}




</script>








