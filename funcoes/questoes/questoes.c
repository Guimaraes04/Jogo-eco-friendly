int verificarIndicePergunta(Pergunta *inicio, int indice)
{
    Pergunta *temp = inicio;

    while (temp != NULL)
    {
        if (temp->numero == indice)
        {
            return 1; // O indice da pergunta existe na lista
        }
        temp = temp->proximo;
    }

    return 0; // O indice da pergunta nao existe na lista
}

void guardarPerguntas(Pergunta **inicio)
{
    FILE *arquivo = fopen("dados/questoes.bin", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Pergunta *temp = *inicio;

    while (temp != NULL)
    {
        fwrite(temp, sizeof(Pergunta), 1, arquivo);
        temp = temp->proximo;
    }

    fclose(arquivo);
}

Pergunta *criarPerguntaEscolhaMultipla(char pergunta[], char opcoes[][50], int resposta, Serie *serie)
{
    Pergunta *novaPergunta = (Pergunta *)malloc(sizeof(Pergunta));
    
    novaPergunta->tipo = 1;
    strcpy(novaPergunta->pergunta, pergunta);
    for (int i = 0; i < 4; i++)
    {
        strcpy(novaPergunta->opcoes[i], opcoes[i]);
    }
    novaPergunta->opcaoCorreta = resposta;
    novaPergunta->proximo = NULL;
    novaPergunta->serie = *serie;

    return novaPergunta;
}

Pergunta *criarPerguntaVerdadeiroFalso(char pergunta[], int resposta, Serie *serie)
{
    Pergunta *novaPergunta = (Pergunta *)malloc(sizeof(Pergunta));

    novaPergunta->tipo = 2;
    strcpy(novaPergunta->pergunta, pergunta);
    novaPergunta->opcaoCorreta = resposta;
    novaPergunta->proximo = NULL;
    novaPergunta->serie = *serie;

    return novaPergunta;
}

void adicionarPergunta(Pergunta **inicio, Pergunta *novaPergunta)
{
    if (*inicio == NULL)
    {
        *inicio = novaPergunta;
    }
    else
    {
        Pergunta *temp = *inicio;
        while (temp->proximo != NULL)
        {
            temp = temp->proximo;
        }
        temp->proximo = novaPergunta;
    }
}

void criarPergunta(Pergunta **inicio)
{
    Pergunta *novaPergunta = (Pergunta *)malloc(sizeof(Pergunta));
    int numeroSerie;

    fflush(stdin);

    // Pedir a pergunta
    printf("Digite a pergunta: ");
    fgets(novaPergunta->pergunta, sizeof(novaPergunta->pergunta), stdin);

    // Remover o caractere de nova linha no final da pergunta
    novaPergunta->pergunta[strcspn(novaPergunta->pergunta, "\n")] = '\0';

    // Pedir o tipo de pergunta
    int tipo;
    printf("Selecione o tipo de pergunta:\n");
    printf("1 - Escolha Multipla\n");
    printf("2 - Verdadeiro/Falso\n");

    printf("Digite o numero correspondente ao tipo: ");
    scanf("%d", &tipo);
    getchar(); // Limpar o caractere de nova linha do buffer

    novaPergunta->tipo = tipo;

    switch (tipo)
    {
        case 1:
        {
            // Pergunta de escolha multipla
            printf("Digite as opcoes de resposta (separadas por ponto-e-virgula):\n");
            for (int i = 0; i < 4; i++)
            {
                printf("Opcao %d: ", i + 1);
                fgets(novaPergunta->opcoes[i], sizeof(novaPergunta->opcoes[i]), stdin);
                // Remover o caractere de nova linha no final da opcao
                novaPergunta->opcoes[i][strcspn(novaPergunta->opcoes[i], "\n")] = '\0';
            }

            // Pedir a opcao correta
            printf("Digite o numero da opcao correta (1-4): ");
            scanf("%d", &novaPergunta->opcaoCorreta);
            getchar(); // Limpar o caractere de nova linha do buffer
            
            printf("Qual é a serie? (1, 3)");
            scanf("%d", &numeroSerie);
            // TODO: Fazer verificação para ver se a serie existe e para ver se está cheia

            break;
        }
        case 2:
        {
            // Pergunta verdadeiro/falso
            printf("Digite a resposta correta (V/F): ");
            scanf("%c", &novaPergunta->opcaoCorreta);
            getchar(); // Limpar o caractere de nova linha do buffer

            printf("Qual é a serie? (2, 4)");
            scanf("%d", &numeroSerie);
            // TODO: Fazer verificação para ver se a serie existe e para ver se está cheia

            break;
        }
        default:
            printf("Tipo de pergunta inválido.\n");
            free(novaPergunta);
            return;
    }

    novaPergunta->serie = obterSerie(numeroSerie);
    novaPergunta->proximo = NULL;

    adicionarPergunta(inicio, novaPergunta);

    Pergunta *temp = *inicio;
    int numero = 0;

    while (temp->proximo != NULL)
    {
        numero++;
        temp = temp->proximo;
    }

    novaPergunta->numero = numero;

    guardarPerguntas(inicio);

    printf("\n\nPergunta adicionada com sucesso!\n");

    system("pause");
}

void removerPergunta(Pergunta **inicio, int indice)
{
    if (*inicio == NULL)
    {
        return;
    }

    if (indice == 0)
    {
        Pergunta *temp = *inicio;
        *inicio = (*inicio)->proximo;
        free(temp);
    }
    else
    {
        Pergunta *anterior = *inicio;
        Pergunta *atual = (*inicio)->proximo;
        int i = 1;
        while (atual != NULL && i < indice)
        {
            anterior = anterior->proximo;
            atual = atual->proximo;
            i++;
        }
        if (atual != NULL)
        {
            anterior->proximo = atual->proximo;
            free(atual);
        }
    }

    guardarPerguntas(inicio);
}

void carregarPerguntas(Pergunta **listaPerguntas)
{
    FILE *arquivo = fopen("dados/questoes.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Pergunta temp;
    int numero = 0;

    while (fread(&temp, sizeof(Pergunta), 1, arquivo) == 1)
    {
        Pergunta *novaPergunta = (Pergunta *)malloc(sizeof(Pergunta));
        novaPergunta->tipo = temp.tipo;
        strcpy(novaPergunta->pergunta, temp.pergunta);
        switch (temp.tipo)
        {
        case 1:
            novaPergunta->opcaoCorreta = temp.opcaoCorreta;
            for (int i = 0; i < 4; i++)
            {
                strcpy(novaPergunta->opcoes[i], temp.opcoes[i]);
            }
            break;
        case 2:
            novaPergunta->opcaoCorreta = temp.opcaoCorreta;
            break;
        case 3:
            strcpy(novaPergunta->resposta, temp.resposta);
            break;
        }
        novaPergunta->proximo = NULL;
        novaPergunta->numero = numero;
        adicionarPergunta(listaPerguntas, novaPergunta);
        numero++;
    }

    fclose(arquivo);
}

void exibirPerguntaEscolhaMultipla(Pergunta *pergunta)
{
    printf("Pergunta: %s\n", pergunta->pergunta);
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, pergunta->opcoes[i]);
    }
    // printf("Resposta: %d\n", pergunta->opcaoCorreta);
}

void exibirPerguntaVerdadeiroFalso(Pergunta *pergunta)
{
    printf("Pergunta: %s\n", pergunta->pergunta);
    // printf("Resposta: %s\n", pergunta->opcaoCorreta ? "Verdadeira" : "Falsa");
}

void exibirPerguntas(Pergunta *inicio)
{
    Pergunta *temp = inicio;
    int indice = 1;
    while (temp != NULL)
    {
        printf("Pergunta %d:\n", temp->numero);
        switch (temp->tipo)
        {
        case 1:
            exibirPerguntaEscolhaMultipla(temp);
            break;
        case 2:
            exibirPerguntaVerdadeiroFalso(temp);
            break;
        }
        
        printf("\n");
        temp = temp->proximo;
        indice++;
    }

    system("pause");
}

Pergunta *obterPergunta(Pergunta *listaPerguntas)
{
    Pergunta *perguntaAtual = listaPerguntas;

    int i = 0;

    while (perguntaAtual != NULL)
    {
        i++;
        perguntaAtual = perguntaAtual->proximo;
    }

    perguntaAtual = listaPerguntas;

    int indice = rand() % i;

    while (perguntaAtual != NULL)
    {
        if (perguntaAtual->numero == indice)
            return perguntaAtual;

        perguntaAtual = perguntaAtual->proximo;
    }

    return NULL;
}