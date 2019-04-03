<form id="formulario-diretriz" name="formulario" method="post" class="form-horizontal">
    <input type="hidden" name="req" id="req" value="salvar-diretriz-estrategica"/>
    <input name="dieid" id="dieid" type="hidden" value="<?= $mDiretrizEstrategica->dieid; ?>">
    <input name="obeid" id="obeid" type="hidden" value="<?= $_REQUEST['obeid']; ?>">

    <?php
        echo $simec->input('diecod', 'C�digo', $mDiretrizEstrategica->diecod, ['required', 'class' => 'upper-text', 'maxlength' => 4]);
        echo $simec->input('dienome', 'Nome', $mDiretrizEstrategica->dienome, ['required', 'maxlength' => 200]);
    ?>

    <div class="form-group">
        <div class="text-center">
            <button class="btn btn-success" id="btn-novo-diretriz" type="button">
                <i class="fa fa-plus"></i>&nbsp;Novo
            </button>
            <button class="btn btn-primary" id="btn-salvar-diretriz-estrategica" type="submit">
                <i class="fa fa-check"></i>&nbsp;Salvar
            </button>
        </div>
    </div>
</form>

<script type="text/javascript">
    $(function () {

        $('#formulario-diretriz').submit(function() {
            $.ajax({
                type: 'POST',
                dataType: 'json',
                url: '?modulo=apoio/objetivo_meta_diretriz_form&acao=A&req=salvar-diretriz-estrategica',
                data: {
                    obeid: $('#obeid').val(),
                    dieid: $('#dieid').val(),
                    diecod: $('#diecod').val().toUpperCase(),
                    dienome: $('#dienome').val(),
                }, success: function(){
                    $('#div_formulario_diretriz_estrategica').load('?modulo=apoio/objetivo_meta_diretriz_form&acao=A&req=formulario-diretriz-estrategica&dieid=' + $('#dieid').val());
                    $('#div_listagem_diretriz_estrategica').load('?modulo=apoio/objetivo_meta_diretriz_form&acao=A&req=listar-diretriz-estrategica&obeid=' + $('#obeid').val());
                }
            });

            // Retorna falso para n�o fazer submiss�o convencional(N�o ajax)
            return false;
        });

        // Limpa os campos para ser inserido novo registro
        $('#btn-novo-diretriz').click(function () {
            $('#dieid').val('');
            $('#diecod').val('');
            $('#dienome').val('');
        });

    });
</script>