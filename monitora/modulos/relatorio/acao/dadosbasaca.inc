<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:dadosbasaca.inc
   Finalidade: permitir a constru��o de relatorio gerencial de a��o em dados b�sicos
    */
    // primeira parte do relat�rio : dados b�sicos
    print '<table  class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center"><tr><td><b>DADOS B�SICOS</b></td></tr></table>';
     $sql= 'select a.*,fu.fundsc, sfu.sfudsc, unm.unmdsc, o.orgdsc, fis.fisqtdeprevistoano as meta, pro.prodsc, p.prgcod,p.prgdsc, u.unidsc, ta.tacdsc from acao a left join ppafuncao fu on fu.funcod=a.funcod left join ppasubfuncao sfu on sfu.sfucod=a.sfucod left join programa p on p.prgid = a.prgid left join dadofisico fis on a.acaid=fis.acaid left join unidademedida unm on unm.unmcod=a.unmcod left join produto pro on pro.procod=a.procod left join unidade u on u.unicod=a.unicod left join orgao o on u.orgcod = o.orgcod left join tipoacao ta on ta.taccod=a.taccod where a.acaid ='.$acaoid;

     $RSprg = $db->record_set($sql);
     $_SESSION['rsdados'][] = $db->carrega_tudo($RSprg);
     $res = $db->carrega_registro($RSprg,0);
     if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;

     ?>
     <table class="tabela" bgcolor="#f5f5f5" cellSpacing="1" cellPadding="3" align="center">
      <tr>
        <td align='right' class="subtitulodireita" width="20%">Programa C�digo:</td>
        <td><?=$prgcod?></td>
      </tr>
      <tr>
        <td align='right' class="subtitulodireita" width="20%">Programa T�tulo:</td>
        <td><?=$prgdsc?></td>
      </tr>
      <tr>
        <td align='right' class="subtitulodireita" width="20%">A��o C�digo:</td>
        <td><?=$acacod.'.'.$unicod.'.'.$loccod?></td>
      </tr>
      <tr>
        <td align='right' class="subtitulodireita" width="20%">A��o T�tulo:</td>
        <td><?=$acadsc?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Org�o Respons�vel:</td>
        <td><?=$orgdsc?></td>
      </tr>
      <?if ($unidsc){?>
      <tr>
        <td align='right' class="SubTituloDireita">Unidade respons�vel:</td>
         <td><?=$unidsc?></td>
      </tr>
      <?}?>
      <?  if ($fundsc) {?>
      <tr>
        <td align='right' class="SubTituloDireita">Fun��o:</td>
        <td><?=$fundsc?></td>
      </tr>
      <?}?>
      <? if ($sfudsc) {?>
      <tr>
        <td align='right' class="SubTituloDireita">Subfun��o:</td>
        <td><?=$sfudsc?></td>
      </tr>
      <?}?>
      <?if ($acafinalidade){?>
      <tr>
        <td align='right' class="SubTituloDireita">Finalidade:</td>
        <td><?=$acafinalidade?></td>
      </tr>
      <?}?>
      <?if ($acadescricao){?>
      <tr>
        <td align='right' class="SubTituloDireita">Descri��o:</td>
        <td><?=$acadescricao?></td>
      </tr>
      <?}?>

      <?if ($acasnrap=='t'){?>
      <tr>
        <td align='right' class="SubTituloDireita">Situa��o:</td>
        <td>RAP</td>
      </tr>
      <?}?>
      <?if ($acasnemenda=='t'){?>
      <tr>
        <td align='right' class="SubTituloDireita">Emenda:</td>
        <td>Sim</td>
      </tr>
      <?}?>
      <?if ($procod){?>
      <tr>
        <td align='right' class="SubTituloDireita">Produto:</td>
        <td><?=$prodsc?></td>
      </tr>
      <?}?>
      <tr>
        <td align='right' class="SubTituloDireita">Meta:</td>
        <td><?=$meta?></td>
      </tr>
      <tr>
        <td align='right' class="SubTituloDireita">Unidade de Medida:</td>
        <td><?=$unmdsc?></td>
      </tr>

      <? if ($acadscproduto) {?>
      <tr>
        <td align='right' class="SubTituloDireita">Especifica��o do Produto:</td>
        <td><?=$acadscproduto;?></td>
      </tr>
      <?}?>
   <?
    if ($acasnoutrasfontes =='t') {?>
        <tr>
        <td align='right' class="SubTituloDireita">Quanto ao Or�amento:</td>
        <td><input type="hidden" name="taccod" value='3'>N�o or�ament�ria</td>
      </tr>
   <? } else {?>
        <tr>
           <td align='right' class="SubTituloDireita">Quanto ao Or�amento:</td>
           <td><input type="hidden" name="taccod" value='3'>Or�ament�ria</td>
        </tr>
        <tr>
           <td align='right' class="SubTituloDireita">Tipo de Or�amento:</td>
           <td>
	    <?
	         if ($acasnfiscalseguridade=='t') print 'Fiscal&nbsp;&nbsp;&nbsp;&nbsp;';
  	         if ($acasnfiscalseguridade=='f') print 'Seguridade&nbsp;&nbsp;&nbsp;&nbsp;';
  	         if ($acasninvestatais=='t') print 'Investimentos Estatais&nbsp;&nbsp;&nbsp;&nbsp;';
	    ?>
          </td>
      </tr>
      <tr>
	     <td align='right' class="SubTituloDireita">Tipo de a��o:</td>
         <td><input type="hidden" name="tacdsc" ><?=$tacdsc?></td>
      </tr>
            <?if ($taccod==1){?>
        <tr>
	      <td align='right' class="SubTituloDireita">Evolu��o da Situa��o F�sica:</td>
          <td>
             <table border=1>
                <tr>
                   <td width='33%'>Total</td>
                   <td width='33%'>Realizado at� <?=strval($_SESSION['exercicio'])-1?></td>
                   <td width='33%'>Previsto em <?=$_SESSION['exercicio']?></td>
                </tr>
                <tr>
                   <td width='33%'><?=$acaqtdcustototal?></td>
                   <td width='33%'><?=$acaqtdateanoanterior?></td>
                   <td width='33%'><?=$acaqtdprevistoanocorrente?></td>
                </tr>
             </table>
          </td>
         </tr>
        <tr>
	      <td align='right' class="SubTituloDireita">Evolu��o da Situa��o Financeira:</td>
          <td>
             <table border=1>
                <tr>
                   <td width='33%'>Total</td>
                   <td width='33%'>Realizado at� <?=strval($_SESSION['exercicio'])-1?></td>
                   <td width='33%'>Previsto em <?=$_SESSION['exercicio']?></td>
                </tr>
                <tr>
                   <td width='33%'><?=number_format($acavlrcustototal,2,',','.')?></td>
                   <td width='33%'><?=number_format($acavlrcustoateanoanterior,2,',','.')?></td>
                   <td width='33%'><?=number_format($acavlrprevistoanocorrente,2,',','.')?></td>
                </tr>
             </table>
          </td>
         </tr>
        <tr>
	      <td align='right' class="SubTituloDireita">Justificativa da Repercuss�o Financeira sobre o Custeio da Uni�o:</td>
          <td>
             <?=$acarepercfinanceira;?>
          </td>
         </tr>
        <tr>
	      <td align='right' class="SubTituloDireita">Valor Estimado da Repercuss�o Financeira (R$/ano):</td>
          <td>
             <?=number_format($acavlrrepercfinanceira,2,',','.')?>
          </td>
         </tr>
        <tr>
	      <td align='right' class="SubTituloDireita">Dura��o do Projeto:</td>
          <td>
             <table border=1>
                <tr>
                   <td width='50%'>In�cio</td>
                   <td width='50%'>T�rmino</td>
                </tr>
                <tr>
                   <td width='50%'><?=$acamesinicio.'/'.$acaanoinicio?></td>
                   <td width='50%'><?=$acamestermino.'/'.$acaanotermino?></td>
                </tr>
             </table>
          </td>
         </tr>
      <?}?>
            <? if ($esfcod) {?>
        <tr>
	      <td align='right' class="SubTituloDireita">Esfera:</td>
          <td>
             <?=$esfdsc;?>
          </td>
         </tr>
       <?}?>
       <tr>
	     <td align='right' class="SubTituloDireita">Forma de Implementa��o:</td>
         <td><input type="hidden" name="tacdsc" >
         <?
            if ($acasnmedireta=='t') print 'Direta<br>';
            if ($acasnmedesc=='t')   print 'Descentralizada<br>';
		    if ($acasnmelincred=='t') print 'Linha de Cr�dito<br>';
         ?>
         </td>
      </tr>
       <? if ($acadetalhamento) {?>
      <tr>
        <td align='right' class="SubTituloDireita">Detalhamento da Implementa��o:</td>
        <td><?=$acadetalhamento;?></td>
      </tr>
      <?}?>

      <?}?>
      <?
    if ($acabaselegal ) {?>
      <tr>
        <td align='right' class="SubTituloDireita">Base legal:</td>
        <td><?=$acabaselegal;?></td>
	</td>
      </tr>
     <?}?>


      <? if ($acahistorico) {?>
     <tr>
        <td align='right' class="SubTituloDireita">Hist�rico da a��o:</td>
       <td><?=$acahistorico;?></td>
      </tr>
     <?}?>

<?

   $sql = "select distinct pfl.pflcod as codigo, pfl.pfldsc as descricao,pfl.pflsncumulativo,rpu.usucpf, rpu.acaid, usu.usunome || '('|| org.orgdsc ||')' as usuario from perfil pfl left join usuarioresponsabilidade rpu on rpu.pflcod = pfl.pflcod and rpu.acaid = ".$acaoid." and rpu.rpustatus='A' left join usuario usu on usu.usucpf=rpu.usucpf left join orgao org on org.orgcod = usu.orgcod where pfl.pflstatus='A' and pfl.pflresponsabilidade in ('A','X') order by pfl.pfldsc";
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

?>
    </table>
<?

