<?
 /*
   Sistema Simec
   Setor respons�vel: SPO-MEC
   Desenvolvedor: Equipe Consultores Simec
   Analista: Gilberto Arruda Cerqueira Xavier, Cristiano Cabral (cristiano.cabral@gmail.com)
   Programador: Gilberto Arruda Cerqueira Xavier (e-mail: gacx@ig.com.br), Cristiano Cabral (cristiano.cabral@gmail.com)
   M�dulo:prn_gerenusu.inc
   Finalidade: permitir a constru��o de relatorio gerencial de usu�rio
    */
/*
session_cache_limiter('private_no_expire');
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-cache");
header("Pragma: no-cache");
session_start(); */

define('FPDF_FONTPATH','includes/fpdf/font/');
require(APPRAIZ.'includes/fpdf/fpdf.php');

class PDF extends FPDF
{
//Page header
function Header()
{
    global $title;
    global $title2;
    global $title3;
  //  global $i;
    global $res;

	// autor
	$this->SetAuthor('Sistema Integrado de Monitoramento do Minist�rio da Educa��o');
	$this->SetSubject('Relat�rio Gerencial de Usu�rios');
	$this->SetTitle($title2);
    //Logo
    $this->Image('/var/www/simec/www/imagens/logo_mec_br.jpg',40,20,525);
    $this->Image('/var/www/simec/www/imagens/top.jpg',40,43,525);
    $this->Image('/var/www/simec/www/imagens/livros_mec.jpg',190,380,200);
        $this->Ln(70);
    $this->SetFont('Arial','',8);
    if ($title <> "")  $this->Cell(0,15,$title,0,1,'C');
    if ($title2 <> "") $this->Cell(0,15,$title2.'   Exerc�cio:'.$_SESSION['exercicio'],0,1,'C');
    $this->Cell(0,15,$title3,0,1,'C');

 
}
function Prnlinha($j,$lin,$dado,$larg)
{
  global $lin;
  $linha = '';
  $piece = explode(" ", $dado);
      //$this->write(10,$dado);
  for ($n=0;$n < count($piece); $n++)
  {
    $linha = $linha.' '.$piece[$n];
    if (strlen($linha) >= $larg or $n==(count($piece)-1))
    {
       $this->Text($j+80,$lin,$linha);
       //$this->write(10,$linha);
       $lin=$lin+10;
       $linha = '';
    }

  }
 // return $lin+10;
}

function PrnWrite($tit,$dado,$y)
{
    $yy = $this->getY();
    if ($y == $yy) $dir=12; else $dir = 12;
    $this->setxy(40,$this->gety()+$dir);
    $this->SetFont('Arial','B',8);
    $this->write(12,$tit);
    $this->SetFont('Arial','',8);
    $this->SetLeftMargin(120);
    $y = $this->getY();
    $this->write(12,$dado);
    $y = $this->getY();
    return $y;
}


function DadosBasicos()
{

    global $res;
    global $resp;
    $this->SetFont('Arial','',8);
    $yp=$this->PrnWrite('CPF:',$res['codigo'],$yp);
    $yp=$this->PrnWrite('Nome / �rg�o:',$res['descricao'],$yp);
    $yp=$this->PrnWrite('Unidade:',$res['unidsc'],$yp);
    $yp=$this->PrnWrite('Responsabilidades:','',$yp);
    $linhas = count($_SESSION['LIN'][$res['codigo']]);
    for ($l=0;$l<$linhas;$l++)
    {
        $yp=$this->PrnWrite('',$_SESSION['LIN'][$res['codigo']][$l],$yp);
    }
    $yp=$this->PrnWrite('---------------------------','--------------------------------------------------------------------------------------',$yp);

}



// function Rotate
function Rotate($angle,$x=-1,$y=-1) {
                if($x==-1)
                        $x=$this->x;
                if($y==-1)
                        $y=$this->y;
                if($this->angle!=0)
                        $this->_out('Q');
                $this->angle=$angle;
                if($angle!=0) {
                        $angle*=M_PI/180;
                        $c=cos($angle);
                        $s=sin($angle);
                        $cx=$x*$this->k;
                        $cy=($this->h-$y)*$this->k;
                        $this->_out(sprintf('q %.5f %.5f %.5f %.5f %.2f %.2f cm 1 0 0 1 %.2f %.2f cm',$c,$s,-$s,$c,$cx,$cy,-$cx,-$cy));
                }
        }

// function RotatedText
        function RotatedText($x,$y,$txt,$angle) {
                //Text rotated around its origin
                $this->Rotate($angle,$x,$y);
                $this->Text($x,$y,$txt);
                $this->Rotate(0);
        }

//Page footer
function Footer()
{
    global $dat;
    global $title4;

    //Position at 1.5 cm from bottom
    $this->SetY(-55);
    $this->setX(40);
    $this->SetFont('Arial','I',6);
    $this->write(8,$title4);


    //Page number
   // $this->Cell(40);
    $this->SetY(-35);
    $this->setX(40);
    $this->Write(6,'Data: '.$dat);
    $this->setX(300);
    $this->Write(6,'P�gina '.$this->PageNo(),'',$this->getY()-12);
    //$this->Cell(0,10,'P�gina '.$this->PageNo().'/{nb}',0,0,'C');
}

//Simple table
function BasicTable($header,$data,$k)
{
    //Column widths
    global $w;
    global $cab;
    global $cab2;
    global $LINHA;

    //Data
    $this->SetFont('Times','',8);
    for($j=0;$j<=$LINHA;$j++)
    {
        for($i=0;$i<2;$i++){
          if (strlen($data[$j][0])> 30) $data[$j][0] = substr($data[$j][0],0,30);
          if (strlen($data[$j][1])> 120) $data[$j][1] = substr($data[$j][1],0,120).'...';
           $this->Cell($w[$i],12,$data[$j][$i],1,0,'L');}
       $this->Ln();
    }
}
}
  
//Instanciation of inherited class
$dat = $_SESSION['data'];
$title4 = $_SESSION['title'];

$pdf=new PDF('P','pt','A4');
$pdf->SetFont('Times','',6);
$pdf->Open();
$pdf->AliasNbPages();
// calcula as larguras de cada coluna


$title = 'SISTEMA INTEGRADO DE MONITORAMENTO DO MINIST�RIO DA EDUCA��O';

if (count($_SESSION['rsdados']) > 0)
{
  // solicitou dados b�sicos
  $title3 = 'Relat�rio Gerencial de Usu�rios';
  $pdf->AddPage();
  for ($i=0; $i<=count($_SESSION['rsdados'])-1;$i++)
  {
   $res = $_SESSION['rsdados'][$i];

   $pdf->DadosBasicos();
  }
}


$pdf->Output();
?>
