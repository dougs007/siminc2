<?php
// carrega a p�gina solicitada pelo usu�rio
$sql = sprintf( "select u.usuchaveativacao from seguranca.usuario u where u.usucpf = '%s'", $_SESSION['usucpf'] );

if (isset($_SESSION['chave']))
{
    $chave = $_SESSION['chave'];
}
else
{
    $chave = $db->pegaUm( $sql );
    $_SESSION['chave'] = $chave;
}

if ( $chave == 'f' )
{
    // leva o usu�rio para o formul�rio de troca de senha
    if ( $_SESSION['sisid'] == 147 ) { //obras 2
        include APPRAIZ . $_SESSION['sisdiretorio'] . "/modulos/sistema2/usuario2/altsenha.inc";
    }
    else {
        include APPRAIZ . $_SESSION['sisdiretorio'] . "/modulos/sistema/usuario/altsenha.inc";
    }
    include APPRAIZ . "includes/rodape.inc";
}
else if ( $_REQUEST['modulo'] )
{
    // leva o usu�rio para a p�gina solicitada, se ela existir
    $file = realpath(APPRAIZ . $_SESSION['sisdiretorio'] . "/modulos/" . $_REQUEST['modulo'] . ".inc");

    if (file_exists( $file )) {
        include APPRAIZ . $_SESSION['sisdiretorio'] . "/modulos/" . $_REQUEST['modulo'] . ".inc";
    }

    include APPRAIZ . "includes/rodape.inc";
}
else
{
    header( "Location: ../login.php" );
}
?>