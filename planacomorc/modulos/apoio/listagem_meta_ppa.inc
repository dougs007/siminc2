<table class="table table-striped table-bordered table-hover dataTablesPg5" >
    <thead>
    <tr class="text-center">
        <th width="10%">A��es</th>
        <th>C�digo</th>
        <th>Meta</th>
        <th>Quantificavel</th>
        <th>Quantidade</th>
    </tr>
    </thead>
    <tbody>
    <?php foreach($mMetappa as $dados){ ?>
        <tr>
            <td class="text-center">
                <a title="Alterar" href="javascript:alterarCamposMeta(<?= $dados['mppid'] ?>,'<?= $_REQUEST['oppid'] ?>');"><i class="fa fa-pencil"></i></a>
            </td>
            <td><?php echo $dados['mppcod']; ?></td>
            <td><?php echo $dados['mppnome']; ?></td>
            <td><?php echo $dados['mppquantificavel'] == 't'? 'Sim': 'N�o'; ?></td>
            <td><?php echo $dados['mppquantidade']; ?></td>
        </tr>
    <?php } ?>
    </tbody>
</table>