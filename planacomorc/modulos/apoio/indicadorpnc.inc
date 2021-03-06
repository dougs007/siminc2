<?php if($lista): ?>
    <div class="table-responsive">
        <table class="table table-striped table-bordered table-hover" >
            <thead>
            <tr class="text-center">
                <th width="10%">A��es</th>
                <th width="10%">C�digo</th>
                <th>Indicadores</th>
            </tr>
            </thead>
            <tbody>
            <?php foreach($lista as $dados){?>
                <tr>
                    <td class="text-center">
                        <a title="Alterar" class="editar-medida" href="?modulo=apoio/metapnc_form&acao=A&req=formulario-medida&ipnid=<?php echo $dados['ipnid']; ?>"><i class="fa fa-pencil"></i></a>
                        <?php if($podeEditar): ?>
                            <a title="excluir" name="req" value="excluir-medida" id="excluir-medida" href="?modulo=apoio/metapnc_form&acao=A&req=excluir-medida&mpnid=<?=$dados['mpnid'];?>&ipnid=<?=$dados['ipnid'];?>" style="margin-left: 5px;"><i class="fa fa-close"></i></a>
                        <?php endif; ?>
                    </td>
                    <td class="text-center"><?php echo $dados['ipncod']; ?></td>
                    <td><?php echo $dados['ipndsc']; ?></td>
                </tr>
            <?php } ?>
            </tbody>
        </table>
    </div>
<?php else: ?>
    <div class="alert alert-danger">Nenhum registro cadastrado</div>
<?php endif; ?>

<script>
    $(function(){
        $('.editar-medida').click(function(){
            jQuery("#div_formulario_medida").load(jQuery(this).attr('href'));
            return false;
        });

        $('.excluir-medida').click(function(){
            href = $(this).attr('href');
// alert(href);
            swal({
                    title: "Aten��o!",
                    text: "Deseja realmente excluir o registro?",
                    type: "warning",
                    showCancelButton: true,
                    confirmButtonColor: "#DD6B55",
                    confirmButtonText: "Sim, estou certo!",
                    closeOnConfirm: true
                },
                function(){
                    $.ajax({
                        url: href,
                        success: function (mpnid) {
                            $("#div_listagem_medida").load('?modulo=apoio/metapnc_form&acao=A&req=excluir-medida&ipnid='+ ipnid);
                        }
                    });
                });
            return false;
        });
    })
</script>
