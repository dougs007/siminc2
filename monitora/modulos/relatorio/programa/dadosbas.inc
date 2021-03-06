<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:dadosbas.inc
   Finalidade: permitir a constru��o de relatorio gerencial de programas em dados b�sicos
    */
    // primeira parte do relat�rio : dados b�sicos
    
    
    
    print '<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center"><tr><td><b>1. DADOS B�SICOS</b></td></tr></table>';
     $sql= 'select p.*,o.orgdsc,tp.tprnome from programa p left join orgao o on o.orgcod=p.orgcod left join tipoprograma tp on tp.tprcod=p.tprcod where p.prgid ='.$_SESSION['prgid'];
     $RSr = $db->record_set($sql);
     $res = $db->carrega_registro($RSr,0);
     if(is_array($res))
       foreach($res as $k=>$v) { ${$k}=$v; if (${$k}== '') ${$k} == 'Dado n�o informado pelo SIGPLAN';}

     ?>
     <table class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center">
      <tr>
        <td align='right' class="subtitulodireita" width="20%">C�digo:</td>
        <td><?=campo_texto('prgcod','N','S','',8,100,'','');?></td>
      </tr>
</form>
      <tr>
        <td align='right' class="SubTituloDireita">Org�o respons�vel:</td>
        <td><?=campo_texto('orgdsc','N','N','',100,100,'','');?></td>
      </tr>
      <?if ($unidsc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Unidade respons�vel:</td>
         <td><?=campo_texto('unidsc','N','N','',100,100,'','');?></td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Denomina��o:</td>
        <td><?=campo_texto('prgdsc','N','N','',100,100,'','');?></td>
      </tr>
      <?if ($prgdscproblema){?>
      <tr>
        <td align='right' class="SubTituloDireita">Problema:</td>
        <td><?=campo_textarea('prgdscproblema','N','N','',100,5,'');?></td>
      </tr>
      <?}?>
      <?if ($prgdscobjetivo){?>
      <tr>
        <td align='right' class="SubTituloDireita">Objetivo do Programa:</td>
        <td><?=campo_textarea('prgdscobjetivo','N','N','',100,5,'');?></td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">P�blico-Alvo:</td>
        <td><?=campo_texto('prgdscpublicoalvo','N','N','',100,100,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Justificativa:</td>
        <td><?=campo_textarea('prgdscjustificativa','N','N','',100,8,'');?></td>
      </tr>
      <?if ($prgdscobjetivoassoc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Objetivo setorial associado:</td>
        <td><?=campo_textarea('prgdscobjetivoassoc','N','N','',100,5,'');?></td>
      </tr>
      <?}?>
      <?if ($mobdsc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Desafio associado:</td>
        <td><?=campo_textarea('mobdsc','N','N','',100,5,'');?></td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Programa estruturante?</td>
        <td>
	<?
	   //if ($prgsnestruturante) {
	     // print '<input type="radio" value="1" name="prgsnestruturante" checked>Sim &nbsp;&nbsp; <input type="radio" name="prgsnestruturante" value="0" checked>Não';
	  // }
	  // else
	  // {
	     // print '<input type="radio" value="0" name="prgsnestruturante"> Sim &nbsp;&nbsp; <input type="radio" name="prgsnestruturante" value="1"  checked>Não';
	  // }
	  print 'Dado n�o informado pelo SIGPLAN';
	?>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Tipo:</td>
        <td><?=campo_texto('tprnome','N','N','',30,30,'','');?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Horizonte temporal:</td>
        <td>
	<?
	   if ($prgsntemporario=='f')    print 'Cont�nuo </td>';
	   else    print 'Tempor�rio </td>';
	?>
      </tr>
	<?
	   if ($prgsntemporario=='t'){?>
      <tr>
        <td align='right' class="SubTituloDireita">Data In�cio/T�rmino:</td>
        <td><?=campo_texto('prgmesinicio','N','N','',6,2,'','');?> /
	        <?=campo_texto('prganoinicio','N','N','',6,4,'','');?>
	<? if ($prgsntemporario=='t') {
	?>
	  <br>(Se tempor�rio) <?=campo_texto('prgmestermino','N','N','',6,2,'','');?> /
      <?=campo_texto('prganotermino','N','N','',6,4,'','');?>
	  <?}?>
	  </td>
      </tr>

       <tr>
        <td align='right' class="SubTituloDireita">Valor Global Estimado <br>do Programa (R$) (se tempor�rio)</td>
        <td>
	<? if ($prgsntemporario=='t') {
	?>
            <?=campo_texto('prgvlrprograma','N','N','',10,10,'','');?>
	  <?}?>
	  </td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Estrat�gia de implementa��o:</td>
        <td><?=campo_textarea('prgdscestrategia','N','N','',100,5,'');?></td>
    </td>
      </tr>
      <?if ($prgobs){?>
      <tr>
        <td align='right' class="SubTituloDireita">Observa��o:</td>
        <td><?=campo_textarea('prgobs','N','N','',100,5,'');?></td>
      </tr>
	  <?}?>
<?
   $sql = "select  distinct pfl.pflcod as codigo, pfl.pfldsc as descricao,pfl.pflsncumulativo,rpu.usucpf, rpu.prgid, usu.usunome || '('|| org.orgdsc ||')' as usuario from perfil pfl left join usuarioresponsabilidade rpu on rpu.pflcod = pfl.pflcod and rpu.prgid = ".$_SESSION['prgid']." and rpu.rpustatus='A' left join usuario usu on usu.usucpf=rpu.usucpf left join orgao org on org.orgcod = usu.orgcod where pfl.pflstatus='A' and pfl.pflresponsabilidade in ('P','X','D') order by pfl.pfldsc";
    $RS2 = $db->record_set($sql);
    $nlinhas = $db->conta_linhas($RS2);
    if ($nlinhas >= 0) {
        for ($i=0; $i<=$nlinhas;$i++){
            $res = $db->carrega_registro($RS2,$i);
            // a linha abaixo transforma em vari�veis todos os campos do array
            if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
	        $linha = "<tr><td align='right' class='SubTituloDireita'><b>".$descricao.":</b></td><td>".$usuario."</td></tr>";
            print $linha;

        }
     }

?>
    </table>
<?

