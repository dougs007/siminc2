<h2 style="color: #1AB394">4. Natureza da Receita
    <?php if ($podeEditarAlteracao === TRUE): ?>
        <a href="#" id="btnRemanejamentoLoa" title="Editar">
            <span class="btn btn-primary btn-sm glyphicon glyphicon-pencil"></span>
        </a>
    <?php endif; ?>
</h2>
<div class="tabs-container tabs">
    <ul class="nav nav-tabs prodTabs">
        <li class="active " style="list-style-type: none;">
            <a class="tab-tipo" data-toggle="tab" id="tp_interno" href="#tab-tabela-natureza">Tabela</a>
        </li>
        <li class=" " style="list-style-type: none;">
            <a class="tab-tipo" data-toggle="tab" id="tp_externo" href="#tab-grafico-natureza">Gr�fico</a>
        </li>
    </ul>
    <div class="tab-content">
        <div id="tab-tabela-natureza" class="tab-pane active">
            <table class="table table-striped table-bordered table-hover dataTables">
                <thead>
                    <tr class="text-center">
                        <th>Natureza da Receita</th>
                        <th>Fonte</th>
                        <th>Dota��o Inicial</th>
                        <th>Outros Acr�scimos</th>
                        <th>Outras Redu��es</th>
                        <th>Acr�scimo Redu��o</th>
                        <th>Saldo</th>
                    </tr>
                </thead>
                <tbody>
                        <tr>
                            <td>''</td>
                            <td>''</td>
                            <td>''</td>
                            <td>''</td>
                            <td>''</td>
                            <td>''</td>
                            <td>''</td>
                        </tr>
                </tbody>
            </table>
        </div>

        <div id="tab-grafico-natureza" class="tab-pane">

        </div>
    </div>
</div>