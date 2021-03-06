<?

include_once("connector.php");
header("Content-Type: text/html; charset=utf-8");
ob_start();

function getErroSSD($erro) {
	$f1 = strpos($erro,"(");
	return substr($erro,($f1+1),11);
	
}

function erro(){
	global $db;
	$db->commit();
	$_SESSION = array();
	$_SESSION['MSG_AVISO'] = func_get_args();
	header( "Location: ". $_SERVER['PHP_SELF'] );
	exit();
}


$SSDWs = new SSDWsUser($tmpDir, $clientCert, $privateKey, $privateKeyPassword, $trustedCaChain);

if ($GLOBALS['USE_PRODUCTION_SERVICES']) {
	$SSDWs->useProductionSSDServices();
} else {
	$SSDWs->useHomologationSSDServices();
}

$cpfOrCnpj = str_replace(array(".","-"),array("",""), $_POST['usucpf']);
$resposta = $SSDWs->getUserInfoByCPFOrCNPJ($cpfOrCnpj);

/* Se o usu�rio n�o existe no SSD, verificar se ele existe no simec
 * caso existir, sincronizar com SSD
 */
define("PER_SIMEC", 154);
if(!$resposta->cpf) {
	$errossd = getErroSSD($resposta["erro"]);
	switch($errossd) {
		case "ErrorId=001":
			$cpfOrCnpj = str_replace(array(".","-"),array("",""), $_POST['usucpf']);
			$sql = "SELECT * FROM seguranca.usuario WHERE usucpf='".$cpfOrCnpj."'";
			$dadosusuario = $db->pegaLinha($sql);
			if($dadosusuario) {
				
				/*
				 * Exportando os dados do simec para o ssd (transparente para o usu�rio)
				 */
				$SSD_senha = @utf8_encode(base64_encode(md5_decrypt_senha( $dadosusuario['ususenha'], '' )));
				$SSD_tipo_pessoa = @utf8_encode("F");
				$SSD_nome = @utf8_encode($dadosusuario['usunome']);
				$SSD_cpf = @utf8_encode($cpfOrCnpj);
				$SSD_data_nascimento = @utf8_encode((($dadosusuario['usudatanascimento'])?$dadosusuario['usudatanascimento']:"0000-00-00"));
				$SSD_email = @utf8_encode($dadosusuario['usuemail']);
				$SSD_ddd_telefone = @utf8_encode($dadosusuario['usufoneddd']);
				$SSD_telefone = @utf8_encode($dadosusuario['usufonenum']);
				// Variavel para inserir os dados no SSD
				$userInfo = "$SSD_senha||$SSD_tipo_pessoa||$SSD_nome||$nome_mae||$SSD_cpf||$rg||$sigla_orgao_expedidor||$orgao_expedidor||$nis||" .
							"$SSD_data_nascimento||$codigo_municipio_naturalidade||$codigo_nacionalidade||$SSD_email||$email_alternativo||" .
							"$cep||$endereco||$sigla_uf_cep||$localidade||$bairro||$complemento||$endereco||$SSD_ddd_telefone||$SSD_telefone||" .
							"$ddd_telefone_alternativo||$telefone_alternativo||$ddd_celular||$celular||$instituicao_trabalho||$lotacao||ssd";
				// Inserindo usuario no SSD
				$respostanovousu = $SSDWs->signUpUser($userInfo);
				if($respostanovousu != "true") {
					switch($respostanovousu['erro']) {
						case @utf8_encode("SSD : A senha informada deve possuir no m�nimo 4 caracteres n�o num�ricos e 2 n�mericos."):
							// Se a autentica��o para o SIMEC estiver correta, enviar para mudan�a de senha (para o padr�o SSD)
							if (md5_decrypt_senha($dadosusuario['ususenha'],'') == $_POST['ususenha']) {
								$_SESSION['altsenhassd_cpf'] = $cpfOrCnpj;
								$_SESSION['altsenhassd_baselogin'] = $_POST['baselogin'];
								header("location: altsenhassd.php");
								exit;
							}
							
						default:
							session_unset();
							$_SESSION['MSG_AVISO'] = $respostanovousu['erro'];
							header('location: login.php');
							exit;
							
					}
				}
				/*
				 * Inserindo permiss�o ao novo usu�rio
				 */
				$permissionId = PER_SIMEC;
				// $responsibleForChangeCpfOrCnpj deve ser vazio
				$respostaperm = $SSDWs->includeUserPermissionByCPFOrCNPJ($cpfOrCnpj, $permissionId, $responsibleForChangeCpfOrCnpj);
				if($respostaperm != "true") {
					session_unset();
					$_SESSION['MSG_AVISO'] = $respostanovousu['erro'];
					header('location: login.php');
					exit;
				}
				
			}
			break;
			
		case "ErrorId=004":
			$permissionId = PER_SIMEC;
			$cpfOrCnpj = str_replace(array(".","-"),array("",""),$_POST["usucpf"]);
			// $responsibleForChangeCpfOrCnpj deve ser vazio
			$respostaperm = $SSDWs->includeUserPermissionByCPFOrCNPJ($cpfOrCnpj, $permissionId, $responsibleForChangeCpfOrCnpj);
			if($respostaperm != "true") {
				session_unset();
				$_SESSION['MSG_AVISO'] = $respostaperm['erro'];
				header('location: login.php');
				exit;
			}
			break;
	}
}
/* FIM
 * Se o usu�rio n�o existe no SSD, verificar se ele existe no simec
 * caso existir, sincronizar com SSD
 */




/*
 * Efetuando a autentica��o
 */
$SSDWs = new SSDWsAuth($tmpDir, $clientCert, $privateKey, $privateKeyPassword, $trustedCaChain);
if ($GLOBALS['USE_PRODUCTION_SERVICES']) {
	$SSDWs->useProductionSSDServices();
} else {
	$SSDWs->useHomologationSSDServices();
}

$cpfOrCnpj = base64_encode(str_replace(array(".","-"),array("",""), $_POST['usucpf']));
$password = base64_encode($_POST['ususenha']);
$respostaUsrSSD = $SSDWs->loginUserIntoSystemByCPFOrCNPJAndPassword($cpfOrCnpj, $password);
if($respostaUsrSSD instanceof stdClass) {
	/*
	 * Autentica��o com SSD realizada com sucesso
	 */
	
	if($respostaUsrSSD->identifier->field != "CPF" || $respostaUsrSSD->identifier->value != str_replace(array(".","-"),array("",""), $_POST['usucpf'])) {
		// 	Efetuando logout
		session_unset();
		$_SESSION['MSG_AVISO'] = "SSD : Problemas no identificador de autentica��o";
		header('location: login.php');
    	exit;
	}
	
	// quantidade limite de tentativas de acesso com senha inv�lida
	define( 'LIMITE_DE_TENTATIVAS', 4 );

	// lista de status de usu�rio
	define( 'STATUS_ATIVO', 'A' );
	define( 'STATUS_PENDENTE', 'P' );
	define( 'STATUS_BLOQUEADO', 'B' );

	// mensagens de alera do sistema
	$alerta = array(
		'cpf' => "O cpf informado n�o est� cadastrado.",
		'status_pendente' => "Sua conta est� pendente para aprova��o, aguarde a avalia��o dos administradores.",
		'status_bloqueado' => "Sua conta est� bloqueada, clique <a href='solicitar_ativacao_de_conta.php' title='solicitar ativa��o de conta'>aqui</a> para solicitar a ativa��o.",
		'senha' => "A senha informada n�o � v�lida. Tentativas restantes: %s",
		'tentativas' => "Voc� excedeu a quantidade de tentativas.",
		'permissao' => "Voc� n�o possui permiss�o de acesso em nenhum dos m�dulos.",
	);
	
	// carrega os dados da conta do usu�rio a partir do cpf informado
	$sql = sprintf(
		"SELECT 
			u.usucpf, 
			u.ususenha, 
			u.suscod, 
			u.usutentativas, 
			u.usunome, 
			u.usuemail 
		 FROM 
			seguranca.usuario u
		 WHERE 
			u.usucpf = '%s'",
		str_replace(array(".","-"),array("",""), $_POST['usucpf'])
	);

	$usuario = $db->pegaLinha( $sql );
	
	// verifica se o cpf existe
	if ( !$usuario['usucpf'] ) {
		erro( $alerta['cpf'] );
	}
	
	// Verifica o status do usu�rio
	switch ( $usuario['suscod'] ) {
		case STATUS_ATIVO:
			break;
		case STATUS_PENDENTE:
			erro( $alerta['status_pendente'] );
		case STATUS_BLOQUEADO:
		default:
			erro( $alerta['status_bloqueado'] );
	}
	
	// atribui��es requeridas para que a auditoria do sistema funcione
	$_SESSION['sisid'] = 4; # seleciona o sistema de seguran�a
	$_SESSION['usucpf'] = $usuario['usucpf'];
	$_SESSION['usucpforigem'] = $usuario['usucpf'];
	
	
	// carrega os dados do usu�rio para a sess�o
	unset( $usuario['ususenha'] );
	foreach ( $usuario as $attribute => $value ) {
		$_SESSION[$attribute] = $value;
	}
	$_SESSION['usucpforigem'] = $usuario['usucpf'];
	
	// verifica permiss�o de acesso aos m�dulos
	$sql = sprintf(
		"SELECT
		s.sisid, s.sisdiretorio, s.sisarquivo, s.sisdsc, s.sisurl, s.sisabrev, s.sisexercicio, s.paginainicial, p.pflnivel AS usunivel, us.susdataultacesso
		FROM seguranca.sistema s
		INNER JOIN seguranca.usuario_sistema us USING ( sisid )
		INNER JOIN seguranca.usuario u USING ( usucpf )
		INNER JOIN seguranca.perfilusuario pu USING ( usucpf )
		INNER JOIN seguranca.perfil p ON pu.pflcod = p.pflcod AND p.sisid = s.sisid
		WHERE
		us.suscod = 'A' AND
		u.usucpf = '%s' AND
		u.suscod = 'A' AND
		p.pflstatus = 'A'
		GROUP BY s.sisid, s.sisdiretorio,  s.sisarquivo, s.sisdsc, s.sisurl, s.sisabrev, s.sisexercicio, s.paginainicial, p.pflnivel, us.susdataultacesso
		ORDER BY us.susdataultacesso DESC
		LIMIT 1",
		$usuario['usucpf']
	);

	$sistema = $db->pegaLinha( $sql );
	if ( !$sistema['sisid'] ) {
		erro( $alerta['permissao'] );
	}
	// carrega os dados do m�dulo para a sess�o
	foreach ( $sistema as $attribute => $value ) {
		$_SESSION[$attribute] = $value;
	}
	
	// atribui o ano atual para o exerc�cio das tarefas
	$_SESSION['exercicio_atual'] = $db->pega_ano_atual();
	$_SESSION['exercicio'] = $db->pega_ano_atual();

	unset($_SESSION['superuser']);
	$_SESSION['superuser'] = $db->testa_superuser( $usuario['usucpf'] );

	// atualiza a data de �ltimo acesso no m�dulo selecionado
	$_SESSION['usuacesso'] = date( 'Y/m/d H:i:s' );
	$sql = sprintf(
		$sql = "UPDATE seguranca.usuario_sistema SET susdataultacesso = '%s' where usucpf = '%s' and sisid = %d",
		$_SESSION['usuacesso'],
		$usuario['usucpf'],
		$sistema['sisid']
	);
	$db->executar( $sql );
	
	// TO DO: verificar se h� mensagens na caixa de entrada (aprovar e implementar fluxo)
	/*	o sistema dever� disparar o processo autom�tico.
	Para tanto o sistema verfica se algume j� disparou o processo para o dia escolhido. se sim, n�o faz nada, se n�o ent�o atualiza a tabela e dispara o processo.
	*/
	$sql = "select ctrdata from controleprocesso where ctrdata=current_date";
	if  (! $db->pegaUm($sql) )//or $_SESSION['usucpf']=='')
	{
		// dispara os processos
		include APPRAIZ."includes/dispara_processo.inc";
	}

	$totmsg=0;
	unset($_SESSION['mostramsg']);
	$sql = "select count(msgid) as totmsg from mensagemusuario where usucpf = '".$_SESSION['usucpf']."' and msulida ='f' and msuexcluida='f'";
	$_SESSION['mostramsg']=$db->pegaUm($sql);

	/*
	 * O contador de tempo online na tela deve ser atualizado toda vez que o
	 * usu�rio carregar uma tela do sistema. Ele � utilizado pelo "estou vivo"
	 * de acordo com a constante MAXONLINETIME, definido no config.inc.
	 */
	$_SESSION["evHoraUltimoAcesso"] = time();
	
	// leva o usu�rio para a tela inicial do m�dulo selecionado
	$db->commit();

	if(!$_SESSION['login_demandas']){
		$header = sprintf(
			"Location: ../%s/%s.php?modulo=%s",
			$sistema['sisdiretorio'],
			$sistema['sisarquivo'],
			$sistema['paginainicial']
		);
	}
	else{
		$_SESSION['login_demandas'] = "";
		$header = sprintf(
			"Location: ../%s/%s.php?modulo=%s",
			'demandas',
			'demandas',
			'inicio&acao=C'
		);
	}
	
	header( $header );
	exit;
	
} else {
	// Efetuando logout
	session_unset();
	$_SESSION['MSG_AVISO'] = $respostaUsrSSD['erro'];
	header('location: login.php');
    exit;
}
?>