<?php
	$titulo = "Delegar Compet�ncia"; //Monta o t�tulo da p�gina
	$schema = "seguranca"; //informa o schema
	$table = "delegacao_competencia"; //informa a tabela
	$hideWarning = true; //esconde os alertas, erros e informa��es de pk, fk, mapeamento de tabelas, etc.
	//$showPK = true; //exibe o campo de PK (readonly)
	//$showStatus = true; //exibe o combo de status (A,I e H)
	$arrOrdemColunas = array("usucpf_delegado","dcpdata_ini","dcpdata_fim"); //Ordena a exibi��o das colunas na tela, pode ser agrupado.
	/*
	$arrOrdemColunas = array(
							"Dados Pessoais" => array(
														"fdpcpf",
														"fdpnome",
														"fdpdatanascimento",
														"fdpnaturalidade",
														"eciid",
														"fdpconjuge"),
							"Contatos" => array(
													"fdptelefoneres",
													"fdpcelular"),
							"Endere�o" => array(
													"fdpcep",
													"fdpenderecoresidencial",
													"fdpbairro",
													"estuf",
													"muncod"), 
							"Filia��o" => array(
													"fdpnomepai",
													"fdpnomemae"), 
							"Dados Banc�rios" => array(
														"fdpbanco",
														"fdpnomebanco",
														"fdpagencia",
														"fdpcontacorrente")
						);
	*/
	//$ptsid = 8;
	
	$arrAttr["usucpf_delegado"] = array("obrigat�rio" => true);
							  
	//$arrAttr["muncod"] = array( "vinculo" => "estuf" );
	
	$arrAttr["usucpf"] = array( "mascara" => "###.###.###-##", //m�scara java script
								"validacao" => "validaCPF" ); //valida��o em PHP e JS (Obs: a fun��o em PHP e JS devem ter o nome da valida��o.)
	
	//$arrWhere = array("propostatiposubacao.frmid = 1","frmdsc like '%A%'"); //Array de filtros p/ a lista.
	
	/*
	 * Ex: $arrOrdemColunas = array( "Parte 1" => array(
	 * 													"coluna1",
	 * 													"coluna2",
	 * 													"coluna3") , 
	 * 								 "coluna4", 
	 * 								 "Parte 2" => array(
	 * 													"coluna5",
	 * 													"coluna6",
	 * 													"coluna7"));
	 */
	$arrPermission = array(
								"inserir", //Permite inserir registros na tabela
								"alterar", //Permite alterar registros da tabela
								"excluir", //Permite excluir registros da tabela
								"comentar_tabela", //Permite adicionar / editar coment�rios sobre a tabela
								"comentar_coluna", //Permite adicionar / editar coment�rios sobre a coluna da tabela
								"campo_descricao", //Permite informar qual o campo descritivo da tabela em casso de FK
								"campo_lista", //Permite definir quais os campos aparecer�o na lista dos registros da tabela
//								"inserir_tabela_apoio" //Permite inserir novas tabelas de apoio em seguranca.tblapoio e seguranca.tbasistema
								);

	include APPRAIZ .'/seguranca/modulos/sistema/tabelasApoio.inc';
?>