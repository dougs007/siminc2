<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:incluireuniao.inc
   Finalidade: permitir incluir evento de reuni�o
   */
$modulo=$_REQUEST['modulo'];
	//dbg('aqui',1);


function atualiza_participante($id, $usucpfs,$msgid )
	{
		global $db;
		$id = (integer) $id;
		if ( (!$id) or (! is_array($usucpfs)))
		{
			return;
		}
		$sql="select agrassunto as assunto, agrlocal as local,agrdata as data, agrhora as hora,agrduracao as duracao,  agrpauta as pauta, u2.ususexo as sexolancador,u2.usunome as nomelancador, u2.usufoneddd||'-'||u2.usufonenum as fonelancador, u2.usuemail as emaillancador from agenda_reuniao ar inner join seguranca.usuario u2 on u2.usucpf=ar.usucpf where agrid=$id";

		$res=$db->pegalinha($sql);
		if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
		
		$sql_remocao = "delete from agenda_reuniao_participante where usucpf is not null and agrid=".$id;
		$db->executar( $sql_remocao );
		foreach ( (array) $usucpfs as $usucpf )
		{
			if ($usucpf) {
				$sql_insercao = "insert into agenda_reuniao_participante (agrid, usucpf ) values ( " . $id . ",'" . $usucpf . "')";	
			$db->executar( $sql_insercao );
			// cria mensagem na caixa de mensagem do interessado
			$sql = "insert into mensagemusuario (msgid,usucpf) values ($msgid,'$usucpf')";
			$saida=$db->executar($sql);
			
			// envia email para o interessado
			
        $assunto = SIGLA_SISTEMA. '- Marca��o de reuni�o';
		$sexo = 'Prezado Sr.  ';
		if ($sexolancador=='F') $sexolanc='Sra. '; else $sexolanc='Sr. '; 
		$sql="select ususexo,usunome,usuemail from seguranca.usuario where usucpf='".$usucpf."'";
		$res=$db->pegalinha($sql);
		if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
		if ($ususexo == 'F') $sexo = 'Prezada Sra. ';
		
        $mensagem = $sexo. str_to_upper($usunome).chr(13)."Reportamos que foi marcada reuni�o com os seguintes dados:\n Assunto:$assunto \n Data/Hora:$data/$hora \n Dura��o prevista:$duracao \n Local:$local \n Pauta:$pauta. \n Qualquer d�vida favor consultar o sistema SIMEC ou entrar em contato com:\n $sexolanc $nomelancador (tel:$fonelancador) E-mail:$emaillancador";
        email($usunome, $usuemail, $assunto, $mensagem);
			}

		}

	}   


$campo=$_REQUEST['campo'];
if ($campo=='pe') $campo='pjeid';
if ($_REQUEST['id']) $id=$_REQUEST['id'];
$botao='Criar item na agenda';
$acao="cria_registro()";
if ($_REQUEST['agrid']) 
{
	// ent�o est� editando o registro
	$sql = "select ar.*, arp.* from agenda_reuniao ar inner join agenda_reuniao_processo arp on arp.agrid=ar.agrid where ar.agrid=".$_REQUEST['agrid'];
	$linha=$db->pegaLinha($sql);
	foreach($linha as $k=>$v) ${$k}=$v;
	$id=${$campo};
	$botao='Alterar item na agenda';
	$acao="altera_registro($agrid)";
}

if ($_REQUEST['act']=='incluir')
{
	// inclus�o de item na agenda
	$agrassunto= str_to_upper($_REQUEST['agrassunto']);
    $agrlocal=str_to_upper($_REQUEST['agrlocal']);
    $agrdata=$_REQUEST['agrdata'];
    $agrhora=$_REQUEST['agrhora'];
    $agrduracao= $_REQUEST['agrduracao'];
    $agrpauta = $_REQUEST['agrpauta'];
    $usucpf=$_SESSION['usucpf'];
    
    $sql = "insert into agenda_reuniao (agrassunto,agrlocal,agrdata,agrhora,agrduracao,agrpauta,usucpf) values ('$agrassunto','$agrlocal','$agrdata','$agrhora','$agrduracao','$agrpauta','$usucpf')";
    $saida = $db->executar($sql);
    $sql =  "select agrid from agenda_reuniao where oid = ".pg_last_oid($saida);
    $agrid = $db->pegaUm($sql);
    $sql="select usunome, usufoneddd||'-'||usufonenum as fone,usuemail from seguranca.usuario where usucpf='$usucpf'";
    $res=$db->pegaLinha($sql);

    foreach($res as $k=>$v) ${$k}=$v;

    // cria a mensagem
    $sql = "insert into mensagem (msgassunto,msgconteudo,usucpf,sisid) values ('Agendamento de reuni�o!',
    'Reportamos que foi marcada reuni�o com os seguintes dados:<br>Assunto: $agrassunto<br>Data/Hora: $agrdata/$agrhora<br>Dura��o prevista: $agrduracao<br>Local: $agrlocal<br>Pauta: $agrpauta<br>Qualquer d�vida favor consultar o sistema SIMEC ou entrar em contato com: $usunome ($fone) ou e-mail: $usuemail','$usucpf',".$_SESSION['sisid'].")";

	$saida=$db->executar($sql);
    $sql =  "Select msgid from mensagem where oid = ".pg_last_oid($saida);	
    $ultimomsgid=$db->pegaUm($sql);
    
     
       atualiza_participante($agrid, $_REQUEST['usucpf'],$ultimomsgid);
 
       // cria registro em agenda_processo
       $sql ="insert into agenda_reuniao_processo ($campo,agrid) values ($id,$agrid)";
      
       $saida = $db->executar($sql);       
       $db->commit();	
       $db->close();
       ?>
       <script>
           window.close();
           opener.location.reload();
       </script>
       <?
       exit();
       
}

if ($_REQUEST['act']=='alterar')
{
	// altera��oo de item na agenda
	  	$agrassunto= str_to_upper($_REQUEST['agrassunto']);
    $agrlocal=str_to_upper($_REQUEST['agrlocal']);
    $agrdata=$_REQUEST['agrdata'];
    $agrhora=$_REQUEST['agrhora'];
    $agrduracao= $_REQUEST['agrduracao'];
    $agrpauta = $_REQUEST['agrpauta'];
    $usucpf=$_SESSION['usucpf'];
    
    $sql = "update agenda_reuniao set agrassunto='$agrassunto',agrlocal='$agrlocal',agrdata='$agrdata',agrhora='$agrhora',agrduracao='$agrduracao',agrpauta='$agrpauta',usucpf='$usucpf' where agrid=".$_REQUEST['id2'];
    $saida = $db->executar($sql);
    $agrid = $_REQUEST['id2'];
    $sql="select usunome, usufoneddd||'-'||usufonenum as fone,usuemail from seguranca.usuario where usucpf='$usucpf'";
    $res=$db->pegaLinha($sql);
    foreach($res as $k=>$v) ${$k}=$v;

// cria a mensagem
    $sql = "insert into mensagem (msgassunto,msgconteudo,usucpf,sisid) values ('Altera��o de reuni�o agendada!',
    'Reportamos que foi alterada a reuni�o agendada com os novos dados:<br>Assunto: $agrassunto<br>Data/Hora: $agrdata/$agrhora<br>Dura��o prevista: $agrduracao<br>Local: $agrlocal<br>Pauta: $agrpauta<br>Qualquer d�vida favor consultar o sistema SIMEC ou entrar em contato com: $usunome ($fone) ou e-mail: $usuemail','".$_SESSION['usucpf']."',".$_SESSION['sisid'].")";
 
	$saida=$db->executar($sql);
    $sql =  "Select msgid from mensagem where oid = ".pg_last_oid($saida);	
    $ultimomsgid=$db->pegaUm($sql);
     
       atualiza_participante($agrid, $_REQUEST['usucpf'],$ultimomsgid);
       $db->commit();	
       $db->close();
       ?>
       <script>
           window.close();
           opener.location.reload();
       </script>
       <?
       exit();
       
}

if ($campo=='pjeid')
{
	$sql_usuario = "select distinct u.usucpf as codigo, u.usunome as descricao 
from seguranca.usuario u inner join seguranca.usuario_sistema us on us.usucpf=u.usucpf and us.suscod='A' and us.sisid=".$_SESSION['sisid']." inner join monitora.projeto_ator pa on u.usucpf=pa.usucpf and pa.peastatus='A' and pa.pjeid=$id where u.suscod='A' order by descricao";	
}

?>
<html>
<head>
<title>Marca��o de Reuni�o</title>
<link rel="stylesheet" type="text/css" href="../includes/Estilo.css">
<link rel='stylesheet' type='text/css' href='../includes/listagem.css'>
<script language="JavaScript" src="../includes/funcoes.js"></script>
<script language="JavaScript" src="../includes/calendario.js"></script>

</head>

<body bgcolor="#ffffff" leftmargin="0" rightmargin="0" topmargin="0" bottommargin="0" marginheight="0" marginwidth="0">
<form method="POST"  name="formulario">
<input type=hidden name="modulo" value="<?=$modulo?>">
<input type=hidden name="id" value="<?=$id?>">
<input type=hidden name="campo" value="<?=$_REQUEST['campo']?>">
<input type=hidden name="act" value="0">
<input type=hidden name="id2" value="<?=$agrid?>">
<br>
 <center>
    <table width='100%' align='center' border="0" cellspacing="1" cellpadding="3" align="center" style="border: 1px Solid Silver; background-color:#f5f5f5;">
     <tr>
	 <td colspan="2" align="Center" bgcolor="#dedede">Evento da Agenda</td>
	 </tr>
	 <tr>
        <td align="right" class="subtitulodireita">Assunto:</td> 
        <td><?=campo_texto('agrassunto','S','S','',70,100,'','');?></td>
     </tr>
	 <tr>
        <td align="right" class="subtitulodireita">Local:</td> 
        <td><?=campo_texto('agrlocal','S','S','',70,100,'','');?></td>
     </tr>
	 <tr>
        <td align="right" class="subtitulodireita">Data:</td> 
        <td><?=campo_data('agrdata', 'S','S','','S');?></td>
     </tr>     
     <tr>
        <td align="right" class="subtitulodireita">Hora:</td> 
        <td><?=campo_texto('agrhora', 'S','S','Entre com a hora hh:mm',5,5,"##:##",'');?></td>
     </tr> 
     <tr>
        <td align="right" class="subtitulodireita">Previs�o de dura��o(min):</td> 
        <td><?=campo_texto('agrduracao', 'S','S','Entre com a previs�o de dura��o em minutos',5,5,"###",'');?></td>
     </tr> 
   
	<tr>
        <td align='right' class="SubTituloDireita">Participantes:</td>
        <td>
        	<?
        	$sql_auxiliar = $_REQUEST[ 'agrid' ] ? "select distinct u.usucpf as codigo, u.usunome as descricao from agenda_reuniao_participante arp inner join seguranca.usuario u on arp.usucpf=u.usucpf  inner join agenda_reuniao ar on ar.agrid=arp.agrid inner join agenda_reuniao_processo ap on ap.agrid=ar.agrid and ap.$campo=$id where arp.usucpf=u.usucpf and arp.agrid=" . $_REQUEST[ 'agrid' ] . " order by descricao" : ''; 
        	$usucpf = $_REQUEST[ 'agrid' ] ? $db->carregar( $sql_auxiliar ) : ''; 
       		combo_popup( 'usucpf', $sql_usuario, 'Selecione o(s) Participante(s)', '360x460' )?>          </td>      
      </tr>                
     
     <tr align="center">
        <td colspan="2"><b>PAUTA</td> 
     </tr> 
     <?
     if ($_REQUEST['agrid'])
     {
     	// permitir incluir a ata da reuni�o
     	?>
     		<tr>
		<td class="SubTituloDireita">Arquivos vinculados � reuni�o:</td>
		<td>
			<? 	
				$sql=sql_vincula_arquivo('agenda_reuniao',$_REQUEST['agrid'],'agrid');
				//dbg($sql)   ;  
				popup_arquivo( 'arquivo_reuniao', $sql, 'agrid',$_REQUEST['agrid'], 1, 400, 400,'agenda_reuniao' );		
					
			?>
		</td>
	</tr>
     	<?
     }
     ?>
         
     <tr> 
        <td colspan=2><?=campo_textarea('agrpauta','N','S','','95%',13,'');?></td>
     </tr>
	 <tr>
	 <td colspan="2" align="right" class="subtitulodireita"><input type='button' class="botao" value='<?=$botao?>' onclick="<?=$acao?>">&nbsp;&nbsp;&nbsp;<input type='button' class="botao" value='Fechar' onclick="fechar_janela()"></td>
	 </tr>
  </table>
</form> 
<script>

   function popup_arquivo( acao, nome, width, height )
	{
		window.open( '../geral/popup_arquivo.php?acao=' + acao + '&nome=' + nome, '', "height=" + height +  ",width=" + width +  ",scrollbars=yes,top=50,left=200" );
	}
	
  function fechar_janela()
  {
    window.close();

  }
    function cria_registro()
  {
    prepara_formulario();
   	if (! validaBranco(document.formulario.agrassunto, 'Assunto')) return;
  	if (! validaBranco(document.formulario.agrlocal, 'Local')) return; 	
  	if (! validaBranco(document.formulario.agrdata, 'Data')) return;
  	if (! validaDataMaiorQueHoje(document.formulario.agrdata))
		{
			alert("Data n�o pode ser Anterior que Data atual.");
			document.formulario.agrdata.focus();
			return;
		}		  
  	
 	
  	if (!validaBranco(document.formulario.agrhora, 'Hora')) return; 
  	if (document.formulario.agrhora.value >'23:00')
		{
			alert("Hora inv�lida.");
			document.formulario.agrhora.focus();
			return;
		}   	
  	if (!validaBranco(document.formulario.agrduracao, 'Previs�o de dura��o')) return;

	if (!validaBranco(document.formulario.agrpauta, 'Pauta da reuni�o')) return tinyMCE.execCommand('mceFocus', true, 'agrpauta');
	document.formulario.act.value='incluir'	;
	document.formulario.submit();

  }
  
    function altera_registro(cod)
  {
    prepara_formulario();
   	if (!validaBranco(document.formulario.agrassunto, 'Assunto')) return;
  	if (!validaBranco(document.formulario.agrlocal, 'Local')) return; 	
  	if (!validaBranco(document.formulario.agrdata, 'Data')) return;
  	if (! validaDataMaiorQueHoje(document.formulario.agrdata))
		{
			alert("Data n�o pode ser Anterior que Data atual.");
			document.formulario.agrdata.focus();
			return;
		}
  	if (!validaBranco(document.formulario.agrhora, 'Hora')) return; 
  	if (document.formulario.agrhora.value >'23:00')
		{
			alert("Hora inv�lida.");
			document.formulario.agrhora.focus();
			return;
		}  	
  	if (!validaBranco(document.formulario.agrduracao, 'Previs�o de dura��o')) return;

	if (!validaBranco(document.formulario.agrpauta, 'Pauta da reuni�o')) return tinyMCE.execCommand('mceFocus', true, 'agrpauta');
	document.formulario.act.value='alterar'	;
	document.formulario.submit();

  }  

</script>
</body>
</html>
