<div class="ibox-title">
    <h5>Descri��o</h5>
</div>
<div class="ibox-content">
    <?php
        echo $simec->input('plititulo', 'T�tulo', $dadosPI['plititulo'], ['maxlength' => 250, 'required']);
        echo $simec->textarea('plidsc', 'Descri��o / Finalidade', $dadosPI['plidsc'], ['rows' => 6, 'cols' => 60, 'required', 'maxlength' => 1000]);
        echo $simec->textarea('plirecursosnecessarios', 'Recursos Necess�rios', $dadosPI['plirecursosnecessarios'], ['rows' => 6, 'cols' => 60, 'maxlength' => 1000]);
    ?>
</div>