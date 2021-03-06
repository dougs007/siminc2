<?
 /*
   Sistema Simec
   Setor responsável: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   Módulo:cadinddet.inc
   Finalidade: mostrar os atributos do indicador
   */

$modulo=$_REQUEST['modulo'] ;//
include APPRAIZ."includes/cabecalho.inc";

if ($_SESSION['prgid']) $_REQUEST['prgid'] = $_SESSION['prgid'];
if ($_REQUEST['prgid'])
  {
     // achar os atributo de programa que interessam
     $sql= "select prgdsc, prgcod from programa where prgstatus='A' and prgano = '".$_SESSION['exercicio']."' and prgid='".$_REQUEST['prgid']."'";
     $RS = $db->record_set($sql);
     $res = $db->carrega_registro($RS,0);

     $sql= "select ind.indnum, unm.unmdsc, bsg.bsgdsc,  per.perdsc, prgano, prgid, prgid, ind.inddsc, ind.inddscfonte,     ind.inddscformula, ind.indvlrano1,ind.indvlrano2, ind.indvlrano3, ind.indvlrano4, ind.indvlrano5, ind.indvlrano6, ind.indvlrreferencia, ind.indvlrfinalprg, ind.indsnapuracaoano1, ind.indsnapuracaoano2, ind.indsnapuracaoano3,ind.indsnapuracaoano4, ind.indsnapuracaoano5,ind.indsnapuracaoano6,ind.indsnapuracaoreferencia,ind.indsnapuracaofinalprg, ind.indvlrapurado,ind.indvlrfinalppa, ind.indvlrperiodo01,ind.indvlrperiodo02,ind.indvlrperiodo03,ind.indvlrperiodo04,ind.indvlrperiodo05,ind.indvlrperiodo06,ind.indvlrperiodo07,ind.indvlrperiodo08,ind.indvlrperiodo09,ind.indvlrperiodo10,ind.indvlrperiodo11,ind.indvlrperiodo12, ind.inddataapuracao,ind.indstatus,ind.indpbs from indicador ind left join unidademedida unm on ind.unmcod= unm.unmcod left join basegeografica bsg on ind.bsgcod = bsg.bsgcod left join periodicidade per on ind.percod = per.percod where ind.prgano = '".$_SESSION['exercicio']."'";
     
     if ($_POST['navega']) unset($_REQUEST['indnum']);

     if ($_REQUEST['indnum']) $sql = $sql. "  and ind.indnum='".$_REQUEST['indnum']."'";
     $sql = $sql . " and ind.prgid ='".$_REQUEST['prgid']."' order by ind.inddsc";

     $RS = $db->record_set($sql);
     $nlinhas = $db->conta_linhas($RS);

        // as linhas abaixo n�o permitem navegar para al�m dos limites
        controla_navegacao($nlinhas);

      // fim do controle de navega��o

     $res2 = $db->carrega_registro($RS,$_SESSION['registro']);
     // a linha abaixo transforma em vari�veis todos os campos do array
     if(is_array($res2)) foreach($res2 as $k=>$v) ${$k}=$v;
     

  }
 
?>
<title>Indicadores de Programas do Simec</title>
<br>
<?
 $db->cria_aba($abacod_tela,$url,'');
$titulo_modulo='Atributos do Indicador';
monta_titulo($titulo_modulo,'');
?>
    <div align="center">
    <table  width='95%' border="0" cellspacing="0" cellpadding="3" align="center" style="border: 1px Solid Silver; background-color:#f5f5f5;" align='center'>
  <tr align="center">
    <td width="95%"><strong>Indicadores de Programa -<?=$res['prgcod'].'--'.$res['prgdsc'].' ('.($nlinhas+1).')'?></strong></td>
     </tr>
</table>

   <form method="POST"  name="formulario">
   <input type=hidden name="modulo" value="<?=$modulo?>">
   <input type=hidden name="navega" value=0>
   <input type=hidden name="procura" value=0>
   <? // inclus�o do menu de setas de navega��o
   include APPRAIZ."includes/setas_navegacao.inc";
   ?> 
    <center>
<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center">
      <tr>
        <td align='right' class="SubTituloDireita">C�digo:</td>
        <td><?=campo_texto('indnum','N','','',5,4,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Descri��o:</td>
        <td><?=campo_texto('inddsc','N','','',100,100,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Unidade de medida:</td>
	       <td><?=campo_texto('unmdsc','N','','',100,100,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Base geogr�fica:</td>
        <td><?=campo_texto('bsgdsc','N','','',20,20,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Periodicidade:</td>
       <td><?=campo_texto('perdsc','N','','',20,20,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Descri��o da fonte:</td>
       <td><?=campo_texto('inddscfonte','N','','',40,40,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">F�rmula:</td>
       <td><?=campo_textarea('inddscformula','N','','',70,3,'');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Valores</td>
        <td colspan="2">
	    <table ><tr><td><b></b></td></tr>
	           <tr>
		      <td>
		         <table border = 1>
			    <tr>
			       <td>2006</td><td>2007</td><td>2008</td><td>2009</td><td>2010</td><td>2011</td><td>Valor de ref</td><td>Valor final</td>
			    </tr>
			    <tr>
			       <td><?=campo_texto('indvlrano1','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrano2','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrano3','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrano4','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrano5','N','','',5,5,'','');?></td>  
                   <td><?=campo_texto('indvlrano6','N','','',5,5,'','');?></td>   
                   <td><?=campo_texto('indvlrreferencia','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrfinalprg','N','','',5,5,'','');?></td>
			    </tr>
			 </table>
		      </td>
		   </tr>
            </table>
	</td>
      </tr>
      <tr>
     <tr>
        <td align='right' class="SubTituloDireita">Valores</td>
        <td colspan="2">
	    <table ><tr><td><b></b></td></tr>
	           <tr>
		      <td>
		         <table border = 1>
			    <tr>
			       <td>Valor apurado</td><td>Valor final PPA</td>
			    </tr>
			    <tr><td><?=campo_texto('indvlrapurado','N','','',5,5,'','');?></td>
    			    <td><?=campo_texto('indvlrfinalppa','N','','',5,5,'','');?></td>
			    </tr>
			 </table>
		      </td>
		   </tr>
            </table>
	</td>
      </tr>
      <!-- tr>
        <td align='right' class="SubTituloDireita">Valores no per�odo 01 a 06</td>
        <td colspan="2">
	    <table ><tr><td><b></b></td></tr>
	           <tr>
		      <td>
		         <table border = 1>
			    <tr>
			       <td>M�s 01</td><td>M�s 02</td><td>M�s 03</td><td>M�s 04</td><td>M�s 05</td><td>M�s 06</td>
			    </tr>
			    <tr>
			       <td><?=campo_texto('indvlrperiodo01','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo02','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo03','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo04','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo05','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo06','N','','',5,5,'','');?></td>
			    </tr>
			 </table>
		      </td>
		   </tr>
            </table>
	</td>
      </tr>
<?
  /*
 ind.,ind.indstatus,ind.indpbs 
   */
?>
    
      <tr>
        <td align='right' class="SubTituloDireita">Valores no per�odo 07 a 12</td>
        <td colspan="2">
	    <table ><tr><td><b></b></td></tr>
	           <tr>
		      <td>
		         <table border = 1>
			    <tr>
			       <td>M�s 07</td><td>M�s 08</td><td>M�s 09</td><td>M�s 10</td><td>M�s 11</td><td>M�s 12</td>
			    </tr>
			    <tr>
			       <td><?=campo_texto('indvlrperiodo07','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo08','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo09','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo10','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo11','N','','',5,5,'','');?></td>
                   <td><?=campo_texto('indvlrperiodo12','N','','',5,5,'','');?></td>
			    </tr>
			 </table>
		      </td>
		   </tr>
            </table>
	</td>
      </tr  -->
      <tr>
        <td align='right' class="SubTituloDireita">Data da apura��o:</td>
        <td><?=campo_data('inddataapuracao','N','','','S');?></td>
      </tr>
     <!--<tr>
        <td width="1%"></td>
        <td width="25%">PBS:</td>
        <td width="98%">
	<textarea rows="2" name="indpbs" cols="70"><?=$indpbs?></textarea></td>
	<td></td>
      </tr>-->
    </table> 
    </td>
    </tr>
    
  </table><center><? // inclusão do menu de setas de navegação
  
include APPRAIZ."includes/setas_navegacao.inc";?> 
    </center>
</div>
</form>
</td>
</tr>
</table>
<script>
 function VerRegistro(cod) {
	//alert (cod+1);
        document.formulario.navega.value = cod;
	document.formulario.submit();
    }
</script>
