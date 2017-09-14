
    /**
     * Formata a tela para n�o exibir Unidade, quantidade e cronograma f�sico quando o usu�rio
     * selecionar "N�o se aplica" ou op��es de mesmo sentido.
     * 
     * @returns VOID
     */
    function formatarTelaProdutoNaoAplica(codigo){
        if(codigo == intProdNaoAplica){
            $('.div_unidade_medida').hide('slow');
            $('#pumid').val('').trigger("chosen:updated");
            $('.div_quantidade_produto').hide('slow');
            $('#picquantidade').val('');
            // Oculta as colunas e campos do Cronograma F�sico
            $('.td_cronograma_fisico').hide('slow');
            // Apaga os dados do cronograma F�sico
            $('.input_fisico').val('');
        } else {
            $('.div_unidade_medida').show();
            $('.div_quantidade_produto').show();
            // Exibe as colunas e campos do Cronograma F�sico
            $('.td_cronograma_fisico').show();
        }
    }

    /**
     * Atualiza o Titulo do PI conforme a op��o selecionada em Manuten��o Item.
     * 
     * @returns VOID
     */
    function atualizarTitulo(){
        var titulo = $('#maiid :checked').text();
        if(titulo != ''){
            $('#plititulo').val(titulo);
        }
    }
    
    /**
     * Atualiza a descri��o do PI conforme a op��o selecionada em Manuten��o Subitem.
     * 
     * @returns VOID
     */
    function atualizarDescricao(){
        var descricao = $('#masid :checked').text();
        if(descricao != ''){
            $('#plidsc').val(descricao);
        }
    }

   /**
    * Valida informa��es de valores do Projeto(Capital e Custeio), Fisicos,
    * Or�ament�rios e Financeiros e caso estejam com inconformidades mudam a cor pra vermelho.
    *
    * @returns VOID
    */
    function mudarCorValoresProjetosFisicoOrcamentarioFinanceiro(){
        mudarCorCronogramaFisico();
        mudarCorCronogramaOrcamentarioCusteio();
        mudarCorCronogramaOrcamentarioCapital();
        mudarCorCronogramaFinanceiroCusteio();
        mudarCorCronogramaFinanceiroCapital();
    }

    /**
     * Retira cor dos elementos marcados pela valida��o do formul�rio quando a valida��o for satisfeita(Quando o elemento for preenchido).
     *
     * @returns VOID
     */
    function initTirarCorValidacao(){
        var listaiten = definirCamposObrigatorios();
        listaiten.push('mpnid', 'ipnid');

        $.each(listaiten , function(i , id){
            $('#formulario').on('change', '#' + id, function(){
                tirarCorVermelha(id);
            });
        });
    }

    /**
     * Tira a Cor Vermelha da valida��o do label do elemento e da tag pai do elemento.
     *
     * @param string id
     * @returns VOID
     */
    function tirarCorVermelha(id){
        $item = $('#' + id);
        $($item).parent().parent().removeClass('has-error');
        $('label[for="'+ $item.attr('id') +'"]').removeClass('has-error');
    }

    /**
     * Exibe orienta��es ao usu�rio para preencher corretamente o Cronograma.
     *
     * @returns VOID
     */
    function avisarCronogramaFisico(){
        if(!validarCronogramaFisicoInferiorQuantidade()){
            alert('<p style="text-align: justify;">&nbsp; &nbsp; N�o ser� poss�vel salvar o formul�rio com a soma de todos os valores preenchidos nos meses do cronograma f�sico superior ao valor informado na Quantidade do Produto do PI.<br />&nbsp; &nbsp; <span style="color: #ff0000;">Por favor, diminua os valores informados na coluna do cronograma f�sico ou aumente a Quantidade no Produto do PI.</span></p>');
        }
    }

    /**
     * Exibe orienta��es ao usu�rio para preencher corretamente o Cronograma.
     *
     * @returns VOID
     */
    function avisarCronogramaOrcamentarioSuperiorCusteio(){
        if(!validarCronogramaOrcamentarioSuperiorValorProjetoCusteio()){
            alert('<p style="text-align: justify;">&nbsp; &nbsp; N�o ser� poss�vel salvar o formul�rio com a soma de todos os valores de CUSTEIO preenchidos nos meses do cronograma or�ament�rio superior ao valor informado no campo de CUSTEIO do Valor do Projeto.<br />&nbsp; &nbsp; <span style="color: #ff0000;">Por favor, diminua os valores informados nos campos de CUSTEIO do cronograma or�ament�rio ou aumente o valor de CUSTEIO do Valor do Projeto.</span></p>');
        }
    }
    
   /**
    * Valida se o valor preenchido no cronograma or�ament�rio � inferior ou igual ao valor declarado em custeio para o valor do projeto.
    * 
    * @return boolean
    */
    function validarCronogramaOrcamentarioSuperiorValorProjetoCusteio(){
        var resultado = false;
        var valorCusteio = textToFloat($('#picvalorcusteio').val());
        var valorTotalCusteioCronograma = buscarTotalCusteioCronogramaOrcamentario();
        
        if(valorTotalCusteioCronograma <= valorCusteio){
            resultado = true;
        }
        
        return resultado;
    }
    
    /**
     * Exibe orienta��es ao usu�rio para preencher corretamente o Cronograma.
     *
     * @returns VOID
     */
    function avisarCronogramaOrcamentarioSuperiorCapital(){
        if(!validarCronogramaOrcamentarioSuperiorValorProjetoCapital()){
            alert('<p style="text-align: justify;">&nbsp; &nbsp; N�o ser� poss�vel salvar o formul�rio com a soma de todos os valores de CAPITAL preenchidos nos meses do cronograma or�ament�rio superior ao valor informado no campo de CAPITAL do Valor do Projeto.<br />&nbsp; &nbsp; <span style="color: #ff0000;">Por favor, diminua os valores informados nos campos de CAPITAL do cronograma or�ament�rio ou aumente o valor de CAPITAL do Valor do Projeto.</span></p>');
        }
    }
    
   /**
    * Valida se o valor preenchido no cronograma or�ament�rio � inferior ou igual ao valor declarado em custeio para o valor do projeto.
    * 
    * @return boolean
    */
    function validarCronogramaOrcamentarioSuperiorValorProjetoCapital(){
        var resultado = false;
        var valorCapital = textToFloat($('#picvalorcapital').val());
        var valorTotalCapitalCronograma = buscarTotalCapitalCronogramaOrcamentario();
        
        if(valorTotalCapitalCronograma <= valorCapital){
            resultado = true;
        }
        
        return resultado;
    }
    
    /**
     * Exibe orienta��es ao usu�rio para preencher corretamente o Cronograma.
     *
     * @returns VOID
     */
    function avisarCronogramaFinanceiroSuperiorCapital(){
        if(!validarCronogramaFinanceiroSuperiorValorProjetoCapital()){
            alert('<p style="text-align: justify;">&nbsp; &nbsp; N�o ser� poss�vel salvar o formul�rio com a soma de todos os valores de CAPITAL preenchidos nos meses do cronograma financeiro superior ao valor informado no campo de CAPITAL do Valor do Projeto.<br />&nbsp; &nbsp; <span style="color: #ff0000;">Por favor, diminua os valores informados nos campos de CAPITAL do cronograma financeiro ou aumente o valor de CAPITAL do Valor do Projeto.</span></p>');
        }
    }
    
   /**
    * Valida se o valor preenchido no cronograma or�ament�rio � inferior ou igual ao valor declarado em custeio para o valor do projeto.
    * 
    * @return boolean
    */
    function validarCronogramaFinanceiroSuperiorValorProjetoCapital(){
        var resultado = false;
        var valorCapital = textToFloat($('#picvalorcapital').val());
        var valorTotalCapitalCronograma = buscarTotalCapitalCronogramaFinanceiro();
        
        if(valorTotalCapitalCronograma <= valorCapital){
            resultado = true;
        }
        
        return resultado;
    }
    
    /**
     * Exibe orienta��es ao usu�rio para preencher corretamente o Cronograma.
     *
     * @returns VOID
     */
    function avisarCronogramaFinanceiroSuperiorCusteio(){
        if(!validarCronogramaFinanceiroSuperiorValorProjetoCusteio()){
            alert('<p style="text-align: justify;">&nbsp; &nbsp; N�o ser� poss�vel salvar o formul�rio com a soma de todos os valores de CUSTEIO preenchidos nos meses do cronograma financeiro superior ao valor informado no campo de CUSTEIO do Valor do Projeto.<br />&nbsp; &nbsp; <span style="color: #ff0000;">Por favor, diminua os valores informados nos campos de CUSTEIO do cronograma financeiro ou aumente o valor de CUSTEIO do Valor do Projeto.</span></p>');
        }
    }
    
   /**
    * Valida se o valor preenchido no cronograma or�ament�rio � inferior ou igual ao valor declarado em custeio para o valor do projeto.
    * 
    * @return boolean
    */
    function validarCronogramaFinanceiroSuperiorValorProjetoCusteio(){
        var resultado = false;
        var valorCusteio = textToFloat($('#picvalorcusteio').val());
        var valorTotalCusteioCronograma = buscarTotalCusteioCronogramaFinanceiro();
        
        if(valorTotalCusteioCronograma <= valorCusteio){
            resultado = true;
        }
        
        return resultado;
    }

    /**
     * Muda a cor dos valores do cronograma F�sico se o valor exceder o valor do projeto.
     *
     * @returns VOID
     */
    function mudarCorCronogramaFisico(){
        if(validarCronogramaFisicoInferiorQuantidade()){
            $('input.input_fisico').removeClass('validateRedText');
            $('#td_total_fisico').removeClass('validateRedText');
        } else {
            $('input.input_fisico').addClass('validateRedText');
            $('#td_total_fisico').addClass('validateRedText');
        }
    }

    /**
     * Muda a cor dos valores das colunas de Custeio do cronograma or�ament�rio se o valor exceder o valor do projeto.
     *
     * @returns VOID
     */
    function mudarCorCronogramaOrcamentarioCusteio(){
        if(validarCronogramaOrcamentarioInferiorValorProjetoCusteio()){
            $('.input_orcamentario.custeio').removeClass('validateRedText');
            $('#td_total_orcamentario_custeio').removeClass('validateRedText');
        } else {
            $('.input_orcamentario.custeio').addClass('validateRedText');
            $('#td_total_orcamentario_custeio').addClass('validateRedText');
        }
    }
    
    /**
     * Muda a cor dos valores das colunas de Capital do cronograma or�ament�rio se o valor exceder o valor do projeto.
     *
     * @returns VOID
     */
    function mudarCorCronogramaOrcamentarioCapital(){
        if(validarCronogramaOrcamentarioInferiorValorProjetoCapital()){
            $('.input_orcamentario.capital').removeClass('validateRedText');
            $('#td_total_orcamentario_capital').removeClass('validateRedText');
        } else {
            $('.input_orcamentario.capital').addClass('validateRedText');
            $('#td_total_orcamentario_capital').addClass('validateRedText');
        }
    }

    /**
     * Muda a cor dos valores do cronograma financeiro se o valor exceder o valor do projeto.
     *
     * @returns VOID
     */
    function mudarCorCronogramaFinanceiroCusteio(){
        if(validarCronogramaFinanceiroInferiorValorProjetoCusteio()){
            $('.input_financeiro.custeio').removeClass('validateRedText');
            $('#td_total_financeiro_custeio').removeClass('validateRedText');
        } else {
            $('.input_financeiro.custeio').addClass('validateRedText');
            $('#td_total_financeiro_custeio').addClass('validateRedText');
        }
    }
    
    /**
     * Muda a cor dos valores do cronograma financeiro se o valor exceder o valor do projeto.
     *
     * @returns VOID
     */
    function mudarCorCronogramaFinanceiroCapital(){
        if(validarCronogramaFinanceiroInferiorValorProjetoCapital()){
            $('.input_financeiro.capital').removeClass('validateRedText');
            $('#td_total_financeiro_capital').removeClass('validateRedText');
        } else {
            $('.input_financeiro.capital').addClass('validateRedText');
            $('#td_total_financeiro_capital').addClass('validateRedText');
        }
    }

    /**
     * Verifica se o cronograma est� preenchido.
     *
     * @returns Boolean
     */
    function validarCronogramaFisicoPreenchido(){
        var valido = false;
        var totalFisico = buscarTotalCronogramaFisico();

        if(totalFisico > 0){
            valido = true;
        }

        return valido;
    }

    /**
     * Verifica se o cronograma est� preenchido com valores superiores a Quantidade do Produto do PI.
     *
     * @returns Boolean
     */
    function validarCronogramaFisicoInferiorQuantidade(){
        var valido = false;
        var quantidade = textToFloat($('#picquantidade').val());
        var totalFisico = buscarTotalCronogramaFisico();
        if(totalFisico <= quantidade){
            valido = true;
        }

        return valido;
    }

    /**
     * Verifica se a coluna de custeio do cronograma est� preenchido com valores inferiores ao valor do projeto.
     *
     * @returns Boolean
     */
    function validarCronogramaOrcamentarioInferiorValorProjetoCusteio(){
        var valido = false;
        var valorDoProjeto = textToFloat($('#picvalorcusteio').val());
        var valorTotalOrcamentario = buscarTotalCusteioCronogramaOrcamentario();

        if(valorTotalOrcamentario <= valorDoProjeto){
            valido = true;
        }

        return valido;
    }
    
    /**
     * Verifica se a coluna de capital do cronograma est� preenchido com valores inferiores ao valor do projeto.
     *
     * @returns Boolean
     */
    function validarCronogramaOrcamentarioInferiorValorProjetoCapital(){
        var valido = false;
        var valorDoProjeto = textToFloat($('#picvalorcapital').val());
        var valorTotalOrcamentario = buscarTotalCapitalCronogramaOrcamentario();

        if(valorTotalOrcamentario <= valorDoProjeto){
            valido = true;
        }

        return valido;
    }

    /**
     * Verifica se a coluna de custeio do cronograma est� preenchido com valores inferiores ao valor do projeto.
     *
     * @returns Boolean
     */
    function validarCronogramaFinanceiroInferiorValorProjetoCusteio(){
        var valido = false;
        var valorDoProjeto = textToFloat($('#picvalorcusteio').val());
        var valorTotalFinanceiro = buscarTotalCusteioCronogramaFinanceiro();

        if(valorTotalFinanceiro <= valorDoProjeto){
            valido = true;
        }

        return valido;
    }
    
    /**
     * Verifica se a coluna de capital do cronograma est� preenchido com valores inferiores ao valor do projeto.
     *
     * @returns Boolean
     */
    function validarCronogramaFinanceiroInferiorValorProjetoCapital(){
        var valido = false;
        var valorDoProjeto = textToFloat($('#picvalorcapital').val());
        var valorTotalFinanceiro = buscarTotalCapitalCronogramaFinanceiro();

        if(valorTotalFinanceiro <= valorDoProjeto){
            valido = true;
        }

        return valido;
    }

    /**
     * Verifica se o cronograma est� preenchido.
     *
     * @returns Boolean
     */
    function validarCronogramaOrcamentarioPreenchido(){
        var valido = false;
        var custeio = buscarTotalCusteioCronogramaOrcamentario();
        var capital = buscarTotalCapitalCronogramaOrcamentario();
        
        valorTotalOrcamentario = custeio + capital;

        if(valorTotalOrcamentario > 0){
            valido = true;
        }

        return valido;
    }

    /**
     * Verifica se o cronograma est� preenchido.
     *
     * @returns Boolean
     */
    function validarCronogramaFinanceiroPreenchido(){
        var valido = false;
        var custeio = buscarTotalCusteioCronogramaFinanceiro();
        var capital = buscarTotalCapitalCronogramaFinanceiro();
        
        valorTotalFinanceiro = custeio + capital;

        if(valorTotalFinanceiro > 0){
            valido = true;
        }

        return valido;
    }

    /**
     * Busca o total informado de todos os meses no cronograma f�sico.
     *
     * @returns float
     */
    function buscarTotalCronogramaFisico(){
        var totalFisico = 0;
        $('input.input_fisico').each(function(data, key){
            var valorMesFisico = textToFloat($(this).val());
            totalFisico += valorMesFisico;
        });

        return totalFisico;
    }

    /**
     * Busca o total de custeio informado de todos os meses no cronograma orcamentario.
     *
     * @returns float
     */
    function buscarTotalCusteioCronogramaOrcamentario(){
        var totalOrcamentario = 0;
        $('input.input_orcamentario.custeio').each(function(data, key){
            var valorMesOrcamento = textToFloat($(this).val());
            totalOrcamentario += valorMesOrcamento;
        });

        return totalOrcamentario;
    }
    
    /**
     * Busca o total de capital informado de todos os meses no cronograma orcamentario.
     *
     * @returns float
     */
    function buscarTotalCapitalCronogramaOrcamentario(){
        var totalOrcamentario = 0;
        $('input.input_orcamentario.capital').each(function(data, key){
            var valorMesOrcamento = textToFloat($(this).val());
            totalOrcamentario += valorMesOrcamento;
        });

        return totalOrcamentario;
    }

    /**
     * Busca o total de custeio informado de todos os meses no cronograma financeiro.
     *
     * @returns float
     */
    function buscarTotalCusteioCronogramaFinanceiro(){
        var totalFinanceiro = 0;
        $('input.input_financeiro.custeio').each(function(data, key){
            var valorMesFinanceiro = textToFloat($(this).val());
            totalFinanceiro += valorMesFinanceiro;
        });

        return totalFinanceiro;
    }
    
    /**
     * Busca o total de capital informado de todos os meses no cronograma financeiro.
     *
     * @returns float
     */
    function buscarTotalCapitalCronogramaFinanceiro(){
        var totalFinanceiro = 0;
        $('input.input_financeiro.capital').each(function(data, key){
            var valorMesFinanceiro = textToFloat($(this).val());
            totalFinanceiro += valorMesFinanceiro;
        });

        return totalFinanceiro;
    }

    /**
     * Calcula e exibi na tela o valor disponivel na Sub-Unidade.
     *
     * @returns VOID
     */
    function atualizarValorLimiteDisponivelUnidade() {
        var valorBaseLimiteDisponivelUnidade = textToFloat($('#VlrSUDisponivel').val());
        var valorBaseProjeto = buscarValorBaseDoProjeto();
        var valorProjeto = buscarValorDoProjeto();

        if(valorProjeto < valorBaseProjeto){
            valorDiferenca = (valorBaseProjeto - valorProjeto);
        } else {
            valorDiferenca = (valorProjeto - valorBaseProjeto);
        }

        var fltValorLimiteDisponivelUnidade = (valorBaseLimiteDisponivelUnidade - valorDiferenca);
        $('#td_disponivel_sub_unidade').html(number_format(fltValorLimiteDisponivelUnidade.toFixed(2), 2, ',', '.'));
    }

    /**
     * Calcula e exibi na tela o valor disponivel na funcional de custeio.
     *
     * @returns VOID
     */
    function atualizarValorLimiteDisponivelFuncionalCusteio() {
        var valorBaseLimiteDisponivel = textToFloat($('#VlrFuncionalDisponivelCusteio').val());
        var valorBaseLimiteProjetoCusteio = textToFloat($('#vlrPiCusteio').val());
        var valorProjetoCusteio = textToFloat($('#picvalorcusteio').val());

        if(valorProjetoCusteio < valorBaseLimiteProjetoCusteio){
            valorCusteio = (valorBaseLimiteProjetoCusteio - valorProjetoCusteio);
        } else {
            valorCusteio = (valorProjetoCusteio - valorBaseLimiteProjetoCusteio);
        }
        var fltValorLimiteDisponivelFuncional = (valorBaseLimiteDisponivel - valorCusteio);
        $('#td_disponivel_funcional_custeio').html(number_format(fltValorLimiteDisponivelFuncional.toFixed(2), 2, ',', '.'));
    }

    /**
     * Calcula e exibi na tela o valor disponivel na funcional de capital.
     *
     * @returns VOID
     */
    function atualizarValorLimiteDisponivelFuncionalCapital() {
        var valorBaseLimiteDisponivel = textToFloat($('#VlrFuncionalDisponivelCapital').val());
        var valorBaseLimiteProjetoCapital = textToFloat($('#vlrPiCapital').val());
        var valorProjetoCapital = textToFloat($('#picvalorcapital').val());

        if(valorProjetoCapital < valorBaseLimiteProjetoCapital){
            valorCapital = (valorBaseLimiteProjetoCapital - valorProjetoCapital);
        } else {
            valorCapital = (valorProjetoCapital - valorBaseLimiteProjetoCapital);
        }
        var fltValorLimiteDisponivelFuncional = (valorBaseLimiteDisponivel - valorCapital);
        $('#td_disponivel_funcional_capital').html(number_format(fltValorLimiteDisponivelFuncional.toFixed(2), 2, ',', '.'));
    }

    /**
     * Calcula e exibi na tela o valor detalhado da funcional.
     *
     * @returns VOID
     */
    function atualizarValorDetalhado() {
        var fltValorBaseDoProjeto = buscarValorBaseDoProjeto();
        var fltValorDoProjeto = buscarValorDoProjeto();
        var fltValorDetalhado = textToFloat($('#piDetalhado').val());
        
        var fltValorDetalhadoAtual = (fltValorDetalhado - fltValorBaseDoProjeto) + fltValorDoProjeto;
        $('#td_pi_detalhado').html(number_format(fltValorDetalhadoAtual.toFixed(2), 2, ',', '.'));
    }

    /**
     * Calcula e exibi na tela o valor n�o detalhado da funcional.
     *
     * @returns VOID
     */
    function atualizarValorNaoDetalhado() {
        var fltValorBaseDoProjeto = buscarValorBaseDoProjeto();
        var fltValorDoProjeto = buscarValorDoProjeto();
        var fltValorBaseNaoDetalhado = textToFloat($('#piNaoDetalhado').val());
        
        var fltValorNaoDetalhadoAtual = (fltValorBaseNaoDetalhado - (fltValorDoProjeto - fltValorBaseDoProjeto));
        $('#td_pi_nao_detalhado').html(number_format(fltValorNaoDetalhadoAtual.toFixed(2), 2, ',', '.'));
    }

    /**
     * Calcula o valor da funcional.
     *
     * @returns VOID
     */
    function atualizarValorDoProjeto() {
        var valorCusteio = textToFloat($('#picvalorcusteio').val());
        var valorCapital = textToFloat($('#picvalorcapital').val());
        var total = valorCusteio + valorCapital;
        $('#td_valor_projeto').html(number_format(total.toFixed(2), 2, ',', '.'));
    }

    /**
     * Exibe o valor total do cronograma F�sico na tela.
     *
     * @returns VOID
     */
    function atualizarTotalFisico() {
        var total = buscarTotalCronogramaFisico();
        $('#td_total_fisico').html( total.toFixed(0) );
    }

    /**
     * Exibe o valor total do cronograma Or�ament�rio na tela.
     *
     * @returns VOID
     */
    function atualizarTotalOrcamentario() {
        var custeio = buscarTotalCusteioCronogramaOrcamentario();
        var capital = buscarTotalCapitalCronogramaOrcamentario();
        $('#td_total_orcamentario_custeio').html('R$ '+ number_format(custeio.toFixed(2), 2, ',', '.'));
        $('#td_total_orcamentario_capital').html('R$ '+ number_format(capital.toFixed(2), 2, ',', '.'));
    }

    /**
     * Exibe o valor total do cronograma Financeiro na tela.
     *
     * @returns VOID
     */
    function atualizarTotalFinanceiro() {
        var custeio = buscarTotalCusteioCronogramaFinanceiro();
        var capital = buscarTotalCapitalCronogramaFinanceiro();
        $('#td_total_financeiro_custeio').html('R$ '+ number_format(custeio.toFixed(2), 2, ',', '.'));
        $('#td_total_financeiro_capital').html('R$ '+ number_format(capital.toFixed(2), 2, ',', '.'));
    }

    /**
     * Soma o valor de capital e custeio e retorna o valor total do projeto.
     *
     * @returns float Valor do projeto
     */
    function buscarValorDoProjeto(){
        var valorCusteio = textToFloat($('#picvalorcusteio').val());
        var valorCapital = textToFloat($('#picvalorcapital').val());
        var valorDoProjeto = valorCusteio + valorCapital;

        return valorDoProjeto;
    }

    /**
     * Soma o valor de capital e custeio e retorna o valor base total do projeto.
     *
     * @returns float Valor do projeto
     */
    function buscarValorBaseDoProjeto(){
        var valorCusteio = textToFloat($('#vlrPiCusteio').val());
        var valorCapital = textToFloat($('#vlrPiCapital').val());
        var valorBaseDoProjeto = valorCusteio + valorCapital;

        return valorBaseDoProjeto;
    }

    /**
     * Soma o valor de capital e custeio e retorna o valor total disponivel.
     * @todo considerar valor inicial base pra dimininuir antes de somar ao valor disponivel custeio e capita.
     * @returns float Valor
     */
    function buscarValorDisponivelFuncional(){
        var valorCusteio = textToFloat($('#td_disponivel_funcional_custeio').text());
        var valorCapital = textToFloat($('#td_disponivel_funcional_capital').text());
        var disponivelFuncional = valorCusteio + valorCapital;

        return disponivelFuncional;
    }

    /**
     * Soma o valor de capital e custeio e retorna o valor total disponivel.
     *
     * @returns float Valor
     */
    function buscarValorAutorizadoFuncional(){
        var valorCusteio = textToFloat($('#td_autorizado_funcional_custeio').text());
        var valorCapital = textToFloat($('#td_autorizado_funcional_capital').text());
        var autorizadoFuncional = valorCusteio + valorCapital;

        return autorizadoFuncional;
    }

    function atualizarSaldoFuncional(){
        // Saldo Autorizado
        dotacaoAtualPO = $('tr[id^=ptres_] td:nth-child(3)').eq(0).text();
        var vlrAutorizadoCusteioCapitalProvisorio = textToFloat(dotacaoAtualPO) / 2;

        $('#td_autorizado_funcional_custeio').text(number_format(vlrAutorizadoCusteioCapitalProvisorio.toFixed(2), 2, ',', '.'));
        $('#td_autorizado_funcional_capital').text(number_format(vlrAutorizadoCusteioCapitalProvisorio.toFixed(2), 2, ',', '.'));

        // Saldo Dispon�vel
        var textNaoDetalhado = $('tr[id^=ptres_] td:nth-child(5)').eq(0).text();
        var vlrNaoDetalhadoCusteioCapitalProvisorio = textToFloat(textNaoDetalhado) / 2;

        var valorDisponivelCusteio = vlrNaoDetalhadoCusteioCapitalProvisorio;
        var valorDisponivelCapital = vlrNaoDetalhadoCusteioCapitalProvisorio;

        $('#td_disponivel_funcional_custeio').text(number_format(valorDisponivelCusteio.toFixed(2), 2, ',', '.'));
        $('#td_disponivel_funcional_capital').text(number_format(valorDisponivelCapital.toFixed(2), 2, ',', '.'));
    }
    
    function carregarSaldoFuncional(){
        // Saldo Autorizado
        dotacaoAtualPO = $('tr[id^=ptres_] td:nth-child(3)').eq(0).text();
        var vlrAutorizadoCusteioCapitalProvisorio = textToFloat(dotacaoAtualPO) / 2;

        $('#td_autorizado_funcional_custeio').text(number_format(vlrAutorizadoCusteioCapitalProvisorio.toFixed(2), 2, ',', '.'));
        $('#td_autorizado_funcional_capital').text(number_format(vlrAutorizadoCusteioCapitalProvisorio.toFixed(2), 2, ',', '.'));

        // Saldo Dispon�vel
        var textNaoDetalhado = $('tr[id^=ptres_] td:nth-child(5)').eq(0).text();
        var vlrNaoDetalhadoCusteioCapitalProvisorio = textToFloat(textNaoDetalhado) / 2;
        
        var valorDisponivelCusteio = vlrNaoDetalhadoCusteioCapitalProvisorio;
        var valorDisponivelCapital = vlrNaoDetalhadoCusteioCapitalProvisorio;

        $('#td_disponivel_funcional_custeio').text(number_format(valorDisponivelCusteio.toFixed(2), 2, ',', '.'));
        $('#td_disponivel_funcional_capital').text(number_format(valorDisponivelCapital.toFixed(2), 2, ',', '.'));
        $('#VlrFuncionalDisponivelCapital').val(number_format(valorDisponivelCusteio.toFixed(2), 2, ',', '.'));
        $('#VlrFuncionalDisponivelCusteio').val(number_format(valorDisponivelCapital.toFixed(2), 2, ',', '.'));
    }

    /**
     * Muda a cor do valor de projeto capital e custeio quando o valor disponvel
     * da sub-unidade ou funcional for ultrapassado.
     *
     * @returns VOID
     */
    function mudarCorValorProjeto(){
        var disponivelUnidade = textToFloat($('#td_disponivel_sub_unidade').text());
        var disponivelFuncional = buscarValorDisponivelFuncional();
        var valorDoProjeto = buscarValorDoProjeto();

        if(valorDoProjeto > disponivelUnidade || valorDoProjeto > disponivelFuncional){
            $('#picvalorcusteio').addClass('validateRedText');
            $('#picvalorcapital').addClass('validateRedText');
            $('#td_valor_projeto').addClass('validateRedText');
        } else {
            $('#picvalorcusteio').removeClass('validateRedText');
            $('#picvalorcapital').removeClass('validateRedText');
            $('#td_valor_projeto').removeClass('validateRedText');
        }
    }

   /**
    * Transforma o valor de texto pra flutuante pra efetuar opera��es matematicas.
    *
    * @param string text
    * @return float numero
    */
    function textToFloat(text){
        var numero = 0;
        text = replaceAll(text, '.', '');
        text = replaceAll(text, ',', '.');
        if(parseFloat(text) > 0){
            numero = parseFloat(text);
        }

        return numero;
    }

    /**
     * Controla as op��es do formulario conforme a op��o de tipo de localiza��o selecionada.
     *
     * @param int esfid C�digo da esfera preenchido pelo usu�rio
     * @return VOID
     */
    function controlarTipoLocalizacao(esfid){
        $('#btn_selecionar_localizacao').hide();
        $('#btn_selecionar_localizacao_estadual').hide();
        $('#btn_selecionar_localizacao_exterior').hide();
        $('#table_localizacao tr').hide();
        $('#table_localizacao_estadual tr').hide();
        $('#table_localizacao_exterior tr').hide();

        switch (esfid) {
            // Verifica se a esfera � Estadual/DF.
            case intEsfidEstadualDF:
                $('#table_localizacao_estadual tr').show('slow');
                $('#btn_selecionar_localizacao_estadual').show('slow');

                $('#table_localizacao tr').not('tr.tr_head').remove();
                $('#table_localizacao_exterior tr').not('tr.tr_head').remove();
            break;
            // Verifica se a esfera � Exterior.
            case intEsfidExterior:
                $('#table_localizacao_exterior tr').show('slow');
                $('#btn_selecionar_localizacao_exterior').show('slow');
                $('#table_localizacao tr').not('tr.tr_head').remove();
                $('#table_localizacao_estadual tr').not('tr.tr_head').remove();
            break;
            // Verifica se a esfera � Federal.
            case intEsfidFederalBrasil:
                $('#btn_selecionar_localizacao').hide('slow');
                $('#table_localizacao tr').hide('slow');
                $('#table_localizacao tr').not('tr.tr_head').remove();
                $('#table_localizacao_estadual tr').not('tr.tr_head').remove();
                $('#table_localizacao_exterior tr').not('tr.tr_head').remove();
            break;
            // Verifica se a esfera � Municipal.
            case intEsfidMunicipal:
                $('#table_localizacao tr').show('slow');
                $('#btn_selecionar_localizacao').show('slow');
                $('#table_localizacao_estadual tr').not('tr.tr_head').remove();
                $('#table_localizacao_exterior tr').not('tr.tr_head').remove();
            break;
        }
    }
    
    /**
     * Verifica se o formul�rio � reduzido ou completo.
     * 
     * @returns boolean retorna true se o formul�rio for reduzido.
     */
    function verificarFormularioReduzido(){
        var resultado = false;
        if($.inArray($('#eqdid').val(), listaEqdReduzido) >= 0){
            resultado = true;
        }
        
        return resultado;
    }
    
    /**
     * Verifica se o formul�rio � N�o Or�ament�rio.
     * 
     * @returns boolean retorna true se o formul�rio for N�o Or�ament�rio.
     */
    function verificarFormularioNaoOrcamentario(){
        var resultado = false;
        if($('#eqdid').val() == intEnqNaoOrcamentario){
            resultado = true;
        }
        
        return resultado;
    }

    function abrirModalResponsaveis() {
        // Verifica se o modal ter� que carregar a tela.
        if($('#modal_responsaveis .modal-body p').size() <= 1){
            $.post('planacomorc.php?modulo=principal/unidade/pi-responsaveis&acao=A&ungcod='+ $("#ungcod").val(),
                function(response) {
                    $('#modal_responsaveis .modal-body p').html(response);
                    $('.modal_dialog_responsaveis').show();
                    $('#modal_responsaveis').modal();
                    $('#modal_responsaveis .chosen-select').chosen();
                    $('#modal_responsaveis .chosen-container').css('width', '100%');
            });
        } else {
            $('#formulario_responsaveis input[name=ungcod]').val($("#ungcod").val());
            $('#modal_responsaveis').modal();
            $('#btnPopupResponsaveisPesquisar').click();
        }
    }

    function abrirModalLocalizacao() {
        // Verifica se o modal ter� que carregar a tela.
        if($('#modal_localizacao .modal-body p').size() <= 1){
            $.post('planacomorc.php?modulo=principal/unidade/pi-localizacao&acao=A', function(response) {
                    $('#modal_localizacao .modal-body p').html(response);
                    $('.modal_dialog_localizacao').show();
                    $('#modal_localizacao').modal();
                    $('#modal_localizacao .chosen-select').chosen();
                    $('#modal_localizacao .chosen-container').css('width', '100%');
            });
        } else {
            $('#modal_localizacao').modal();
            $('#btnPopupLocalizacaoPesquisar').click();
        }
    }

    function abrirModalLocalizacaoEstadual() {
        // Verifica se o modal ter� que carregar a tela.
        if($('#modal_localizacao_estadual .modal-body p').size() <= 1){
            $.post('planacomorc.php?modulo=principal/unidade/pi-localizacao-estadual&acao=A', function(response) {
                    $('#modal_localizacao_estadual .modal-body p').html(response);
                    $('.modal_dialog_localizacao_estadual').show();
                    $('#modal_localizacao_estadual').modal();
                    $('#modal_localizacao_estadual .chosen-select').chosen();
                    $('#modal_localizacao_estadual .chosen-container').css('width', '100%');
            });
        } else {
            $('#modal_localizacao_estadual').modal();
            $('#btnPopupLocalizacaoEstadualPesquisar').click();
        }
    }

    function abrirModalLocalizacaoExterior() {
        // Verifica se o modal ter� que carregar a tela.
        if($('#modal_localizacao_exterior .modal-body p').size() <= 1){
            $.post('planacomorc.php?modulo=principal/unidade/pi-localizacao-exterior&acao=A', function(response) {
                    $('#modal_localizacao_exterior .modal-body p').html(response);
                    $('.modal_dialog_localizacao_exterior').show();
                    $('#modal_localizacao_exterior').modal();
                    $('#modal_localizacao_exterior .chosen-select').chosen();
                    $('#modal_localizacao_exterior .chosen-container').css('width', '100%');
            });
        } else {
            $('#modal_localizacao_exterior').modal();
            $('#btnPopupLocalizacaoExteriorPesquisar').click();
        }
    }

    function abrirModalUpload() {
        $('.modal_dialog_upload').show();
        $('#modal_upload').modal();
        $('#modal_upload .chosen-container').css('width', '100%');
    }

    function inserirNovoAnexo(json){
        var trHtml = '<tr style="height: 30px;" class="tr_anexos_'+ json.arqid +'" >'
            + '                    <td style="text-align: left;"><a href="#" onclick="javascript:abrirArquivo('+ json.arqid+ '); return false;" >'+ json.arqnome +'</a></td>'
            + '                    <td style="text-align: left;">'+ json.arqdescricao +'</td>'
            + '                    <td style="text-align: center;">'
            + '                         <input type="hidden" value="'+ json.arqid +'" name="listaAnexos[]">'
            + '                         <span class="glyphicon glyphicon-trash btnRemoverAnexos link" title="Excluir o arquivo '+ json.arqnome+ '" data-anexos="'+ json.arqid +'" >'
            + '                    </td>'
            + '                </tr>'
        ;
        $('#table_anexos').append(trHtml);
    }

   /**
    * Controla a��es para quando o bot�o edital estiver marcado ou desmarcado.
    */
    function controlarEdital(opcao){
        if(opcao == true){
            $('#div_edital').show('slow');
        } else {
            $('#div_edital').hide('slow');
        }
    }

    /**
     * Controla a exibi��o do formulario se o enquadramento for finalistico.
     *
     * @param integer codigo C�digo selecionado pelo usu�rio.
     * @returns VOID
     */
    function mudarFormularioFinalistico(codigo){
        // Se o c�digo for Finalistico, o sistema exibe as op��es PNC.
        if(codigo == intEnqFinalistico){
            // Exibe as op��es Meta PNC e Indicador PNC.
            $('.grupo_pnc').show('slow');
        } else {
            // Oculta e apaga as op��es Meta PNC e Indicador PNC.
            $('.grupo_pnc').hide('slow');
            // Apaga as op��es selecionadas.
            $('#mpnid').val('').trigger("chosen:updated");
            $('#ipnid').val('').trigger("chosen:updated");
        }
    }
    
    /**
     * Controla a exibi��o do formulario se o enquadramento for n�o or�ament�rio.
     *
     * @param integer codigo C�digo selecionado pelo usu�rio.
     * @returns VOID
     */
    function mudarFormularioNaoOrcamentario(codigo){
        // Se o c�digo for N�o Or�ament�rio, o sistema n�o exibe as op��es PTRES(Funcional), Valor do Projeto, Cronograma Or�ament�rio e Financeiro.
        if(codigo == intEnqNaoOrcamentario){
            // Oculta a op��es PTRES(Funcional).
            $('.div_ptres').hide('slow');
            // Oculta o quadro de Custeio e Capital com a op��o de Valor do Projeto.
            $('.div_custeio_capital').hide('slow');
            // Oculta as colunas e campos do Cronograma Or�ament�rio.
            $('.td_cronograma_orcamentario').hide('slow');
            // Oculta as colunas e campos do Cronograma Financeiro.
            $('.td_cronograma_financeiro').hide('slow');
        } else {
            // Exibe a op��es PTRES(Funcional).
            $('.div_ptres').show('slow');
            // Exibe o quadro de Custeio e Capital com a op��o de Valor do Projeto.
            $('.div_custeio_capital').show('slow');
            // Exibe as colunas e campos do Cronograma Or�ament�rio.
            $('.td_cronograma_orcamentario').show('slow');
            // Exibe as colunas e campos do Cronograma Financeiro.
            $('.td_cronograma_financeiro').show('slow');
        }
    }

    /**
     * Carrega novo conte�do para o select de Suba��es via requisi��o ajax.
     */
    function carregarUG(unicod) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarComboUG=ok&unicod=' + unicod, function(response) {
            $('#ungcod').remove('slow');
            $('.div_ungcod').html(response);
            $(".chosen-select").chosen();
        });
    }

    /**
     * Carrega novo conte�do para o select de Metas PPA via requisi��o ajax.
     */
    function carregarMetasPPA(oppid, mppid, suocod) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarMetasPPA=ok&oppid=' + oppid + '&suocod=' + suocod, function(response) {
            $('#mppid').remove();
            $('.div_mppid').html(response);
            $(".chosen-select").chosen();
        });
    }

    /**
     * Carrega limites da Sub-Unidade via requisi��o ajax.
     */
    function carregarLimitesUnidade(codigo) {
        $.ajax({
            url: '?modulo=principal/unidade/cadastro_pi&acao=A&carregarLimitesUnidade=ok',
            type: "post",
            data: {'ungcod': codigo},
            dataType: 'json',
            success: function(data){
                $('#td_autorizado_sub_unidade').text(data.autorizado);
                var fltDisponivelUnidade = textToFloat(data.disponivel);
                var fltBaseProjeto = buscarValorBaseDoProjeto();
                var fltDisponivel = (fltDisponivelUnidade - fltBaseProjeto) + buscarValorDoProjeto();
                $('#td_disponivel_sub_unidade').text(number_format(fltDisponivel.toFixed(2), 2, ',', '.'));
                $('#VlrSUDisponivel').val(number_format(fltDisponivel.toFixed(2), 2, ',', '.'));
                
                mudarCorValorProjeto();
            }
        });
    }

    /**
     * Carrega novo conte�do para o select de metas PNC via requisi��o ajax.
     */
    function carregarMetaPNC(codigo) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarMetaPNC=ok&suocod=' + codigo, function(response) {
            $('#mpnid').remove();
            $('.div_mpnid').html(response);
            $(".chosen-select").chosen();
        });
    }

    /**
     * Carrega novo conte�do para o select de Indicadores PNC via requisi��o ajax.
     */
    function carregarIndicadorPNC(codigo) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarIndicadorPNC=ok&mpnid=' + codigo, function(response) {
            $('#ipnid').remove();
            $('.div_ipnid').html(response);
            $(".chosen-select").chosen();
        });
    }

    /**
     * Carrega novo conte�do para o select de Segmento Cultural via requisi��o ajax.
     */
    function carregarSegmentoCultural(codigo) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarSegmentoCultural=ok&mdeid=' + codigo, function(response) {
            $('#neeid').remove();
            $('.div_neeid').html(response);
            $(".chosen-select").chosen();
        });
    }

    /**
     * Carrega novo conte�do para o select de Manuten��o Item via requisi��o ajax.
     */
    function carregarManutencaoItem(codigo) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarManutencaoItem=ok&eqdid=' + codigo + '&maiid=' + intMaiid, function(response) {
            $('#maiid').remove();
            $('#masid option').not('option[value=""]').remove();
            $('#masid').val('').trigger("chosen:updated");
            $('.div_maiid').html(response);
            formatarTelaEnquadramentoComManutencaoItem();
        });
    }
    
    /**
     * Se existir itens de manuten��o exibe as op��es de manuten��o item e sub-item e bloqueia os campos de titulo e descri��o.
     * 
     * @returns VOID
     */
    function exibirOpcoesItemManutencao(){
        if($('#maiid option').not('option[value=""]').size() > 0){
            $('.grupo_manutencao').show('slow');
            // Desabilita a op��o de modificar os campos de T�tulo e Descri��o.
            $('[name=plititulo]').attr('readonly', 'readonly');
            $('[name=plidsc]').attr('readonly', 'readonly');
        } else {
            $('.grupo_manutencao').hide('slow');
            // Habilita a op��o de modificar os campos de T�tulo e Descri��o.
            $('[name=plititulo]').removeAttr('readonly');
            $('[name=plidsc]').removeAttr('readonly');
        }
    }
    
    function formatarTelaEnquadramentoComManutencaoItem(){
        // Verifica se o usu�rio j� estiver preenchido o enquadramento(Caso de formul�rio de cadastro de novo PI).
        if($('#eqdid').val() != ""){
            
            // Se for formul�rio reduzido
            if(verificarFormularioReduzido() > 0){

                // Se existir itens de manuten��o exibe as op��es de manuten��o item e sub-item e bloqueia os campos de titulo e descri��o.
                exibirOpcoesItemManutencao();
                
                // Oculta os campos de metas PPA e PNC
                $('.div_metas_ppa_pnc').hide('slow');
                $('#oppid').val('').trigger("chosen:updated");
                $('#mppid').val('').trigger("chosen:updated");
                $('#ippid').val('').trigger("chosen:updated");
                $('#mpnid').val('').trigger("chosen:updated");
                $('#ipnid').val('').trigger("chosen:updated");
                // Oculta os campos do Produto do PI
                $('.div_produto_pi').hide('slow');
                $('#pprid').val('').trigger("chosen:updated");
                $('#pumid').val('').trigger("chosen:updated");
                $('#picquantidade').val('');
                // Oculta as colunas e campos do Cronograma F�sico
                $('.td_cronograma_fisico').hide('slow');
                // Apaga os dados do cronograma F�sico
                $('.input_fisico').val('');
            } else {
                // Se existir itens de manuten��o exibe as op��es de manuten��o item e sub-item e bloqueia os campos de titulo e descri��o.
                exibirOpcoesItemManutencao();
                
                // Exibe os campos de metas PPA e PNC
                $('.div_metas_ppa_pnc').show('slow');
                // Exibe os campos do Produto do PI
                $('.div_produto_pi').show('slow');
                // Exibe as colunas e campos do Cronograma F�sico
                $('.td_cronograma_fisico').show('slow');
            }
        }
    }

    /**
     * Carrega novo conte�do para o select de Manuten��o SubItem via requisi��o ajax.
     */
    function carregarManutencaoSubItem(codigo) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarManutencaoSubItem=ok&maiid=' + codigo, function(response) {
            $('#masid').remove();
            $('.div_masid').html(response);
            $(".chosen-select").chosen();
        });
    }

    /**
     * Carrega novo conte�do para o select de Metas PPA via requisi��o ajax.
     */
    function carregarIniciativaPPA(codigo) {
        $.post('?modulo=principal/unidade/cadastro_pi&acao=A&carregarIniciativaPPA=ok&oppid=' + codigo, function(response) {
            $('#ippid').remove();
            $('.div_ippid').html(response);
            $(".chosen-select").chosen();
        });
    }

    function Trim(str)
    {
        return str.replace(/^\s+|\s+$/g, "");
    }

    //coloca tabindex no campo valor
    function tabindexcampo() {
        var x = document.getElementsByTagName("input");
        var y = 1;
        for (i = 0; i < x.length; i++) {
            if (x[i].type == "text") {
                if (x[i].name.substr(0, 8) == 'plivalor') {
                    x[i].tabIndex = y;
                    y++;
                }
            }
        }
    }

    /**
     * Verifica se o valor do cronograma F�sico � igual ao informado no Produto do PI.
     * 
     * @returns {Boolean}
     */
    function validarCronogramaFisicoIgualQuantidade(){
        var resultado = false;
        var qtdCronograma = buscarTotalCronogramaFisico();
        var qtdProdutoPi = textToFloat($('#picquantidade').val());
        
        if(qtdCronograma == qtdProdutoPi){
            resultado = true;
        }
        
        return resultado;
    }
    
    /**
     * Verifica se o valor do cronograma Orcamentario � igual ao informado no valor do projeto.
     * 
     * @returns {Boolean}
     */
    function validarCronogramaOrcamentarioCusteioIgualValorProjeto(){
        var resultado = false;
        var vlrCronograma = buscarTotalCusteioCronogramaOrcamentario();
        var vlorProjeto = textToFloat($('#picvalorcusteio').val());
        
        if(vlrCronograma == vlorProjeto){
            resultado = true;
        }
        
        return resultado;
    }
    
    /**
     * Verifica se o valor do cronograma Orcamentario � igual ao informado no valor do projeto.
     * 
     * @returns {Boolean}
     */
    function validarCronogramaOrcamentarioCapitalIgualValorProjeto(){
        var resultado = false;
        var vlrCronograma = buscarTotalCapitalCronogramaOrcamentario();
        var vlorProjeto = textToFloat($('#picvalorcapital').val());
        
        if(vlrCronograma == vlorProjeto){
            resultado = true;
        }
        
        return resultado;
    }

    /**
     * Verifica se o valor do cronograma Financeiro � igual ao informado no valor do projeto.
     * 
     * @returns {Boolean}
     */
    function validarCronogramaFinanceiroCusteioIgualValorProjeto(){
        var resultado = false;
        var vlrCronograma = buscarTotalCusteioCronogramaFinanceiro();
        var vlorProjeto = textToFloat($('#picvalorcusteio').val());
        
        if(vlrCronograma == vlorProjeto){
            resultado = true;
        }
        
        return resultado;
    }

    /**
     * Verifica se o valor do cronograma Financeiro � igual ao informado no valor do projeto.
     * 
     * @returns {Boolean}
     */
    function validarCronogramaFinanceiroCapitalIgualValorProjeto(){
        var resultado = false;
        var vlrCronograma = buscarTotalCapitalCronogramaFinanceiro()
        var vlorProjeto = textToFloat($('#picvalorcapital').val());
        
        if(vlrCronograma == vlorProjeto){
            resultado = true;
        }
        
        return resultado;
    }

    /* Fun��o para subustituir todos */
    function replaceAll(str, de, para) {
        var pos = str.indexOf(de);
        while (pos > -1) {
            str = str.replace(de, para);
            pos = str.indexOf(de);
        }
        return (str);
    }

    function abrir_lista() {
        // Verifica se o modal ter� que recarregar a tela.
        if($('#modal-ptres .modal-body p').size() <= 1){
            $.post('planacomorc.php?modulo=principal/unidade/popupptres&acao=A&obrigatorio=n&unicod='+ $("#unicod").val()+ '&ungcod='+ $("#ungcod").val()+ '&no_ptrid='+ $('input[name=ptrid]').val(), function(response) {
                $('#modal-ptres .modal-body p').html(response);
                $('.modal-dialog-ptres').show();
                $('#modal-ptres').modal();
                $('#modal-ptres .chosen-select').chosen();
                $('#modal-ptres .chosen-container').css('width', '100%');
            });
        } else {
            $('#formularioPopup input[name=unicod]').val($("#unicod").val());
            $('#modal-ptres').modal();
            $('#btnPopupPtresPesquisar').click();
        }
    }

    function visualizarRegistro(ptrid) {
        $('#modal-confirm .modal-body p').empty();
        url = 'planacomorc.php?modulo=principal/unidade/popupptres&acao=A&detalhe=ok&ptrid=' + ptrid;
        $.post(url, function(html) {
            $('#modal-confirm .modal-body p').html(html);
            $('#modal-confirm .modal-title').html('Detalhamento PTRES');
            $('#modal-confirm .btn-primary').remove();
            $('#modal-confirm .btn-default').html('Fechar');
            $('.modal-dialog').show();
            $('#modal-confirm').modal();
        });
    }

