<?

 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br)
   M�dulo:dadosfisevo2.inc
   Finalidade: permitir a constru��o de relatorio gerencial acompanhamento fisico do plano de trabalho
*/
 
     if (! in_array($ptoid,$_SESSION['ptoid']))  $_SESSION['rspto'][] = $res;
         $_SESSION['ptoid'][]=$ptoid;
        
        if (! $inicio) $inicio='01/01/'.$_SESSION['exercicio'];
        if (! $fim) $fim='31/12/'.$_SESSION['exercicio'];
        $sql3= "select e.exprealizado, pt.ptosnsoma from execucaopto e left join planotrabalho pt on pt.ptoid=e.ptoid where e.ptoid=$ptoid order by e.refcod";
        $RSsoma= $this->record_set($sql3);
         $nlinhas3 = $this->conta_linhas($RSsoma);
         if ($nlinhas3 >= 0)
         {
           for ($n3=0;$n3<=$nlinhas3;$n3++)
           {
              $res3 = $this->carrega_registro($RSsoma,$n3);
              if(is_array($res3)) foreach($res3 as $k=>$v) ${$k}=$v;
              if ($ptosnsoma=='t')
              {
                $soma = $soma + $exprealizado;
              }
              else $soma = $exprealizado;
           }
         }
      $_SESSION['soma']['ptoid'][]=$ptoid;
      $_SESSION['soma']['soma'][]=$soma;


?>
       <tr>
          <td colspan=2><b>Tarefa</b></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Tipo:</td>
          <td><? 
            if ($ptotipo=='S') print 'Suba��o' ;
            else if ($ptotipo=='F') print 'Fase' ;
            else print 'Etapa';?></td>
        </tr>        
        <tr>
          <td align='right' class="subtitulodireita" width="20%">C�digo:</td>
          <td><?=$ptocod?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">T�tulo:</td>
          <td><?=$ptodsc?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Previs�o:</td>
          <td><?=$previsto?></td>
        </tr>
       <? if ($previsto > 0) {?>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Realizado at� o momento:</td>
          <td><?=$soma. '   (Correspondente a '.number_format(($soma/$previsto)*100,2,',','.').'%)'?></td>
        </tr>
        <?}?>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Per�odo:</td>
          <td><?=$inicio.' a '.$fim?></td>
        </tr>
        <tr>
          <td colspan=2><hr></td>
        </tr>
<?
//  acompanhamento f�sico
 $sql= "select e.ptoid, r.refdsc as refdsc2, e.exprealizado as exprealizado2, e.expobs as expobs2, to_char(e.expdata,'DD/MM/YYYY HH:MM') as pardata2, u.usunome ||' / '|| o.orgdsc as autor2, s.tpsdsc as tpsdsc2 from execucaopto e left join usuario u on u.usucpf=e.usucpf left join orgao o on o.orgcod = u.orgcod left join tiposituacao s on s.tpscod=e.tpscod left join referencia r on r.refcod=e.refcod where e.ptoid=".$ptoid;
     $RSpto2= $this->record_set($sql);
     $_SESSION['rspto2'][] = $this->carrega_tudo($RSpto2);
     $nlinhaspto2 = $this->conta_linhas($RSpto2);
     if ($nlinhaspto2 >= 0)
     {
     for ($n2=0;$n2<=$nlinhaspto2;$n2++)
     {
        $res = $this->carrega_registro($RSpto2,$n2);
        if(is_array($res)) foreach($res as $k=>$v) ${$k}=$v;
        ?>
       <tr>
          <td></td><td><b>Acompanhamento F�sico da Tarefa</b></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Refer�ncia:</td>
          <td><?=$refdsc2?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Lan�ado por:</td>
          <td><?=$autor2?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Lan�ado em:</td>
          <td><?=$pardata2?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Realizado:</td>
          <td><?=$exprealizado2?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Situa��o:</td>
          <td><?=$tpsdsc2?></td>
        </tr>
        <tr>
          <td align='right' class="subtitulodireita" width="20%">Observa��o:</td>
          <td><?=$expobs2?></td>
        </tr>
                <tr>
          <td colspan=2><hr></td>
        </tr>
      <?

     }
     }

?>
