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
     $sql= 'select p.*,o.orgdsc,tp.tprnome from programa p left join orgao o on o.orgcod=p.orgcod left join tipoprograma tp on tp.tprcod=p.tprcod where p.prgid ='.$programa;
     $RSprg = $db->record_set($sql);
     $_SESSION['rsdados'][] = $db->carrega_tudo($RSprg);
     $res = $db->carrega_registro($RSprg,0);
     if(is_array($res))
       foreach($res as $k=>$v) { ${$k}=$v; if (${$k}== '') ${$k} == 'Dado n�o informado pelo SIGPLAN';}

     ?>
     <table class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center">
      <tr>
        <td align='right' class="subtitulodireita" width="20%">C�digo:</td>
        <td><?=$prgcod?></td>
      </tr>
</form>
      <tr>
        <td align='right' class="SubTituloDireita">Org�o respons�vel:</td>
        <td><?=$orgdsc?></td>
      </tr>
      <?if ($unidsc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Unidade respons�vel:</td>
         <td><?=$unidsc?></td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Denomina��o:</td>
        <td><?=$prgdsc?></td>
      </tr>
      <?if ($prgdscproblema){?>
      <tr>
        <td align='right' class="SubTituloDireita">Problema:</td>
        <td><?=$prgdscproblema?></td>
      </tr>
      <?}?>
      <?if ($prgdscobjetivo){?>
      <tr>
        <td align='right' class="SubTituloDireita">Objetivo do Programa:</td>
        <td><?=$prgdscobjetivo?></td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">P�blico-Alvo:</td>
        <td><?=$prgdscpublicoalvo?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Justificativa:</td>
        <td><?=$prgdscjustificativa?></td>
      </tr>
      <?if ($prgdscobjetivoassoc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Objetivo setorial associado:</td>
        <td><?=$prgdscobjetivoassoc?></td>
      </tr>
      <?}?>
      <?if ($mobdsc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Desafio associado:</td>
        <td><?=$mobdsc?></td>
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
        <td><?=$tprnome?></td>
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
        <td><?=$prgmesinicio?> /
	        <?=$prganoinicio?>
	<? if ($prgsntemporario=='t') {
	?>
	  <br>(Se tempor�rio) <?=$prgmestermino?> /
      <?=$prganotermino?>
	  <?}?>
	  </td>
      </tr>

       <tr>
        <td align='right' class="SubTituloDireita">Valor Global Estimado <br>do Programa (R$) (se tempor�rio)</td>
        <td>
	<? if ($prgsntemporario=='t') {
	?>
            <?=$prgvlrprograma?>
	  <?}?>
	  </td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Estrat�gia de implementa��o:</td>
        <td><?=$prgdscestrategia?></td>
    </td>
      </tr>
      <?if ($prgobs){?>
      <tr>
        <td align='right' class="SubTituloDireita">Observa��o:</td>
        <td><?=$prgobs?></td>
      </tr>
	  <?}?>
<?

   $sql = "select distinct pfl.pflcod as codigo, pfl.pfldsc as descricao,pfl.pflsncumulativo,rpu.usucpf, rpu.prgid, usu.usunome || '('|| ee.entnome ||')' as usuario from seguranca.perfil pfl left join monitora.usuarioresponsabilidade rpu on rpu.pflcod = pfl.pflcod and rpu.prgid = ".$programa." and rpu.rpustatus='A' left join seguranca.usuario usu on usu.usucpf=rpu.usucpf left join entidade.entidade ee on ee.entid = usu.entid where pfl.pflstatus='A' and pfl.pflresponsabilidade in ('P','X') and pfl.sisid=".$_SESSION['sisid']."  order by pfl.pfldsc";
   
    $RS2 = $db->record_set($sql);
    $_SESSION['rsdadosresp'][] = $db->carrega_tudo($RS2);
    $nlinhas = $db->conta_linhas($RS2);
    if ($nlinhas >= 0) {
        for ($ii=0; $ii<=$nlinhas;$ii++){
            $res = $db->carrega_registro($RS2,$ii);
            // a linha abaixo transforma em vari�veis todos os campos do array
            if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
	        $linha = "<tr><td align='right' class='SubTituloDireita'><b>".$descricao.":</b></td><td>".$usuario."</td></tr>";
            print $linha;
        }
     }
    // print $sql;
   

?>
    </table>
<?

