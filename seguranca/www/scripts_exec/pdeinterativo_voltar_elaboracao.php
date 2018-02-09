<?php

function getmicrotime()
{list($usec, $sec) = explode(" ", microtime());
 return ((float)$usec + (float)$sec);} 

date_default_timezone_set ('America/Sao_Paulo');

$_REQUEST['baselogin'] = "simec_espelho_producao";

/* configura��es */
ini_set("memory_limit", "2048M");
set_time_limit(0);
/* FIM configura��es */

// carrega as fun��es gerais
include_once "config.inc";
include_once APPRAIZ . "includes/classes_simec.inc";
include_once APPRAIZ . "includes/funcoes.inc";
include_once APPRAIZ . "includes/workflow.php";
error_reporting(-1);


// CPF do administrador de sistemas
if(!$_SESSION['usucpf'])
$_SESSION['usucpforigem'] = '00000000191';

if($_SERVER['HTTP_HOST']=='simec.mec.gov.br') {
	$servidor_bd = '';
	$porta_bd = '5432';
	$nome_bd = '';
	$usuario_db = '';
	$senha_bd = '';
}


// abre conex�o com o servidor de banco de dados
$db = new cls_banco();


$sql = "select d.* from pdeinterativo.pdinterativo p
inner join workflow.documento d on d.docid = p.docid
where pdicodinep in 
(
'11002123',
'11002999',
'11016329',
'11017899',
'11046260',
'11047631',
'13028685',
'13054929',
'13067966',
'13082990',
'13132229',
'15002500',
'15005208',
'15055264',
'15055477',
'15055833',
'15055850',
'15086518',
'15098273',
'15098885',
'15104060',
'15111423',
'15113973',
'15120139',
'15137606',
'15204200',
'15562140',
'15643336',
'17005353',
'17006503',
'17018404',
'17029864',
'17051002',
'17053064',
'21009163',
'21030790',
'21077258',
'21081069',
'21081565',
'21097690',
'21108048',
'21108277',
'21196011',
'21227829',
'21233403',
'21236143',
'21249989',
'21262810',
'21330417',
'21349614',
'21351414',
'22011170',
'22021922',
'22037900',
'22064605',
'22064842',
'22120335',
'23000562',
'23006676',
'23008989',
'23009012',
'23014601',
'23038632',
'23048204',
'23061391',
'23061685',
'23061774',
'23063068',
'23063173',
'23084065',
'23091061',
'23095148',
'23100559',
'23124423',
'23130075',
'23133562',
'23163992',
'23180471',
'23216409',
'23216492',
'23232528',
'23242264',
'23247290',
'24001910',
'24002224',
'24002232',
'24002283',
'24017957',
'24019852',
'24044504',
'24046949',
'24050296',
'24052280',
'24052426',
'24052876',
'24053309',
'24055484',
'24055522',
'24056170',
'24056197',
'24058289',
'24058416',
'24062502',
'24062847',
'24098205',
'24248207',
'24294314',
'25083414',
'25086618',
'25090364',
'25091220',
'25100092',
'25115820',
'26017512',
'26026775',
'26027160',
'26028751',
'26036207',
'26050331',
'26057514',
'26059878',
'26060124',
'26076519',
'26076799',
'26080710',
'26081032',
'26091224',
'26102382',
'26103435',
'26108020',
'26109018',
'26109310',
'26113546',
'26114607',
'26119897',
'26120771',
'26129086',
'26139049',
'26143801',
'26151855',
'26152428',
'26166593',
'26171783',
'26424711',
'27000770',
'27000915',
'27000931',
'27001407',
'27004481',
'27006573',
'27006980',
'27009297',
'27009645',
'27011577',
'27012670',
'27012697',
'27013030',
'27013405',
'27015920',
'27016650',
'27017117',
'27017184',
'27017320',
'27017354',
'27017362',
'27018326',
'27018440',
'27018660',
'27018679',
'27019063',
'27019080',
'27020967',
'27021122',
'27028380',
'27030725',
'27032280',
'27036332',
'27036499',
'27037681',
'27038599',
'27039331',
'27039463',
'27040046',
'27046303',
'27216888',
'27221040',
'27221725',
'27224333',
'27226018',
'28005201',
'28006275',
'28006305',
'28006720',
'28007131',
'28007816',
'28009576',
'28011341',
'28013476',
'28014731',
'28015371',
'28015959',
'28016459',
'28017854',
'28017862',
'28020464',
'28020472',
'28022459',
'28023730',
'28031725',
'28032942',
'28033302',
'28070402',
'28072413',
'29000084',
'29000289',
'29001960',
'29007720',
'29007763',
'29008298',
'29008395',
'29013704',
'29015170',
'29017343',
'29026113',
'29026636',
'29031826',
'29038898',
'29040043',
'29045134',
'29046890',
'29048800',
'29053137',
'29054133',
'29060540',
'29060672',
'29063671',
'29063825',
'29064228',
'29064937',
'29065291',
'29066140',
'29066921',
'29071917',
'29073073',
'29084610',
'29088097',
'29089018',
'29098955',
'29110823',
'29117577',
'29118530',
'29123550',
'29124468',
'29126118',
'29126533',
'29129389',
'29137969',
'29145066',
'29150558',
'29152968',
'29153425',
'29154227',
'29156009',
'29157471',
'29157641',
'29159741',
'29161576',
'29166470',
'29176441',
'29176867',
'29176905',
'29194113',
'29201012',
'29201047',
'29201136',
'29201691',
'29202639',
'29205395',
'29220971',
'29221374',
'29226503',
'29226848',
'29233054',
'29237041',
'29240387',
'29247900',
'29256810',
'29267838',
'29279283',
'29280060',
'29280540',
'29281180',
'29296595',
'29301769',
'29305802',
'29314216',
'29314763',
'29326850',
'29357152',
'29372178',
'29390761',
'29391407',
'29391741',
'29392462',
'29393744',
'29404100',
'29407583',
'29409829',
'29412030',
'29414008',
'29414164',
'29417805',
'29419239',
'29419476',
'29422558',
'29426570',
'29429978',
'29441200',
'29444306',
'29444578',
'29827620',
'31015644',
'31238945',
'31340146',
'32036400',
'32039166',
'32039590',
'33036780',
'33052379',
'33054185',
'33055785',
'33059799',
'33064148',
'33073970',
'33076014',
'33076146',
'33080585',
'33083444',
'33091447',
'33151288',
'33154520',
'33439605',
'35277393',
'35277861',
'35417440',
'41009231',
'41018168',
'41049098',
'41107969',
'41118960',
'41123956',
'41132947',
'41134770',
'41143035',
'41143302',
'41365887',
'42024749',
'42128714',
'42140420',
'42143411',
'43038786',
'43060382',
'43087604',
'43092993',
'43152350',
'50009915',
'50015591',
'51004399',
'51036940',
'51037009',
'51037327',
'51045559',
'51063239',
'51086182',
'51089033',
'51090031',
'52020940',
'52033600',
'52036529',
'52037215',
'52038793',
'52065227',
'53000870',
'53006917',
'53012186'
)

and pdistatus = 'A'";

$lista = $db->carregar($sql);

if($lista[0]) {
	foreach($lista as $l) {
		$docid = $l['docid'];
		$aedid = 1260;
		$dados = array();
		$result = wf_alterarEstado( $docid, $aedid, $cmddsc = 'Tramita��o feita em lote', $dados);
		echo "r.".$result."<br>";
	
	}
}
echo "fim";
?>