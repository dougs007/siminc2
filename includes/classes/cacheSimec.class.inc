<?php
/* In�cio - Cache em arquivo
	include_once APPRAIZ.'includes/classes/cacheSimec.class.inc';
	Utiliza��o de Cache
	$cache = new cache("nomedoarquivo");

	Exclus�o de Cache
	$cache = new cache(false);
	$cache->apagarCache("nomedoarquivo");
   Fim - Cache em arquivo*/

/*
 * Classe Cache
 * Classe para fazer cache em arquivo
 * @author Juliano Meinen
 * @since 28/11/2011
 */
class Cache {

	public  $diretorio; 
	public  $arrInfo = array();
	public  $nomeCache = false;
	private $extensao = "html";
	private $diretorioEspecial = null;
	
	
	public function __construct($nomeCache,$extensao = null,$diretorio = null)
	{
		//return false; //Remover essa linha para funcionar.
		if($extensao){
			$this->extensao = $extensao;
		}
		
		if($diretorio){
			$this->diretorioEspecial = $diretorio;
		}
		
		if($nomeCache){
			$this->nomeCache = $nomeCache;
			if( !$this->recuperarCache() ){
				register_shutdown_function(array($this,criarCache));
			}
		}
	}
	
	/**
	 * M�todo para cria��o do chache.
	 * @access public
	 * @author Juliano Meinen
	 * @since 28/11/2011
	 * @version 0.1
	 */
	public function criarCache()
	{
		
		$string = $this->nomeCache;
		
		if(!$this->diretorio){ //Verifica se n�o existe diretorio para o cache
			$this->diretorio = APPRAIZ."arquivos/".$_SESSION['sisdiretorio'];
		}
		
		$cacheFile = md5($string); //Nome do arquivo que armazenar� o conte�do.
		$cacheConteudo = ob_get_contents(); //Obt�m o conte�do
		if(!is_dir($this->diretorio)){//Verifica se n�o existe o diret�rio para grava��o do cache
			mkdir($this->diretorio, 0777); //Cria o diret�rio para armazenamento do cache com permiss�o para escrita
		}
		if(!is_dir($this->diretorio."/cache")){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			mkdir($this->diretorio."/cache", 0777); //Cria o diret�rio para armazenamento do cache com permiss�o para escrita
		}
		
		if(!is_dir($this->diretorio."/cache/".substr($cacheFile,0,2))){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			mkdir($this->diretorio."/cache/".substr($cacheFile,0,2), 0777); //Cria o diret�rio para armazenamento do cache com permiss�o para escrita
		}
		
		if($this->diretorioEspecial && !is_dir($this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial)){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			mkdir($this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial, 0777); //Cria o diret�rio para armazenamento do cache com permiss�o para escrita
		}
		
		if($this->diretorioEspecial){
			/*
			if(is_file($this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial."/$cacheFile.".$this->extensao)){
				dbg("J� existem um cache com esse nome!");
				return false;
			}
			*/
			$cacheArquivo = fopen($this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial."/$cacheFile.".$this->extensao, "w+"); //Cria um arquivo para armazenar o conte�do
		}else{
			/*
			if(is_file($this->diretorio."/cache/".substr($cacheFile,0,2)."/".$cacheFile.".".$this->extensao)){
				dbg("J� existem um cache com esse nome!");
				return false;
			}
			*/
			$cacheArquivo = fopen($this->diretorio."/cache/".substr($cacheFile,0,2)."/".$cacheFile.".".$this->extensao, "w+"); //Cria um arquivo para armazenar o conte�do
		}
 
		fwrite($cacheArquivo, $cacheConteudo); // Escreve o conte�do no arquivo criado
		fclose($cacheArquivo); //Fechar o arquivo
	}
	
	public function recuperarCache()
	{
				
		$string = $this->nomeCache;
		
		$cacheFile = md5($string); //Nome do arquivo que armazenar� o conte�do.
		
		if(!$this->diretorio){ //Verifica se n�o existe diretorio para o cache
			$this->diretorio = APPRAIZ."arquivos/".$_SESSION['sisdiretorio'];
		}
		
		if($this->diretorioEspecial){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			$local = $this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial."/$cacheFile.".$this->extensao;
		}else{
			$local = $this->diretorio."/cache/".substr($cacheFile,0,2)."/".$cacheFile.".".$this->extensao;	
		}
		
		
		if(is_file($local)){
			$this->tratarRodape($cacheFile);
			ob_clean();
			if($this->extensao != "html"){
				header('Content-type: application/'.$this->extensao);
				header('Content-Disposition: attachment; filename="downloaded.'.$this->extensao.'"');
				readfile($local);
			}else{
				include($local);
			}
			
			$this->arrInfo[] = "A p�gina est� utilizando cache.";
			exit;
		}else{
			$this->arrInfo[] = "A p�gina n�o est� utilizando cache.";
			return false;
		}
	}
	
	/**
	 * M�todo para atualizar os dados do rodap� do SIMEC
	 * @access private
	 * @author Juliano Meinen
	 * @since 29/11/2011
	 * @version 0.1
	 */
	private function tratarRodape($cacheFile)
	{
		echo "<!-- cache de sistema -->";
		
		if($this->diretorioEspecial){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			$local = $this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial."/$cacheFile.".$this->extensao;
		}else{
			$local = $this->diretorio."/cache/".substr($cacheFile,0,2)."/$cacheFile.".$this->extensao;
		}
		
		if(is_file($local)) {
			
			$cacheArquivo = file ($local);
			
			$html = implode ('',$cacheArquivo);
			$pos_inicial_cab = 0;
			$pos_final_cab = strpos($html,"class=\"tbl_conteudo");
			if($pos_final_cab){
				$html = substr($html,$pos_final_cab + 331,strlen($html));
				global $db;
				include(APPRAIZ."includes/cabecalho.inc");
				echo "<br />";
			}
	
			$pos_inicial = strpos($html,"<table class=\"rodape\"");
			$pos_final = strpos($html,"<div id=\"avisochat");
			
			if($pos_inicial && $pos_final){
				$antigoHtml = substr($html,$pos_inicial,$pos_final);
				$novoHtml = substr($html,0,$pos_inicial);
				$novoHtml.= substr($html,$pos_final,strlen($html));
				echo $novoHtml;
				$cache_sistema = "C";
				global $Tinicio;
				include(APPRAIZ."includes/rodape.inc");
				exit;
			}
		
		}
		
	}
	
	public function apagarCache($nomeDoArquivo)
	{
		//return false; //Remover essa linha para funcionar.
		
		$cacheFile = md5($nomeDoArquivo); //Nome do arquivo que armazenar� o conte�do.
		
		if(!$this->diretorio){ //Verifica se n�o existe diretorio para o cache
			$this->diretorio = APPRAIZ."arquivos/".$_SESSION['sisdiretorio'];
		}
		
		if($this->diretorioEspecial){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			$local = $this->diretorio."/cache/".substr($cacheFile,0,2)."/".$this->diretorioEspecial."/$cacheFile.".$this->extensao;
		}else{
			$local = $this->diretorio."/cache/".substr($cacheFile,0,2)."/$cacheFile.".$this->extensao;
		}

		if(file_exists($local) && is_writable($local)){
			if(unlink($local)){
				$this->arrInfo[] = "Arquivo de cache exclu�do com sucesso.";
				return true;
			}else{
				$this->arrInfo[] = "N�o foi poss�vel excluir o arquivo de cache.";
				return false;
			}
		}else{
			$this->arrInfo[] = "Arquivo de cache inexistente. $nomeDoArquivo / $cacheFile";
			return true;
		}
	}
	
	public function apagarTodoCache($diretorio = false)
	{
		if(!$this->diretorio){ //Verifica se n�o existe diretorio para o cache
			$this->diretorio = APPRAIZ."arquivos/".$_SESSION['sisdiretorio'];
		}
		
		if($this->diretorioEspecial){//Verifica se n�o existe o diret�rio 'cache' para grava��o dos arquivos
			$local = $this->diretorio."/cache/".$this->diretorioEspecial;
		}else{
			$local = $this->diretorio."/cache";
		}
		
		$ponteiro  = opendir($local);
		while ($nome_itens = readdir($ponteiro)) {
		    if($nome_itens!= "." && $nome_itens != ".."){
		    	if(is_file($local."/$nome_itens")){
			    	$itens[] = $nome_itens;
			    	@chmod($local."/$nome_itens", 0666);
			    	@unlink($local."/$nome_itens");
			    	echo "$nome_itens <br />";
		    	}
			if($diretorio){
		    		if(is_dir($local."/$nome_itens")){
		    			echo "Diret�rio: ".$nome_itens."<br />";
		    			$ponteiro2  = opendir($local."/$nome_itens");
			    		while ($nome_itens2 = readdir($ponteiro2)) {
						    if($nome_itens2!= "." && $nome_itens2 != ".."){
						    	if(is_file($local."/$nome_itens/$nome_itens2")){
							    	$itens[] = $nome_itens2;
							    	@chmod($local."/$nome_itens/$nome_itens2", 0666);
							    	@unlink($local."/$nome_itens/$nome_itens2");
							    	echo " - $nome_itens2 <br />";
						    	}
						    }
			    		}
		    		}
		    	}
		    }
		}
		if(!$itens){
			die("N�o existe cache!");
		}else{
			die("Cache exclu�do! ".count($itens)." arquivo(s).");
		}
				
	}
	
	public function extensao($extensao)
	{
		$this->extensao = $extensao;
	}

}