int verificarResposta(Pergunta *pergunta, char *resposta)
{
    switch (pergunta->tipo)
    {
    case 1:
        // Pergunta de escolha multipla
        if (pergunta->opcaoCorreta == atoi(resposta))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case 2:
        // Pergunta de verdadeiro ou falso
        if (strcmp(resposta, pergunta->resposta) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    default:
        printf("Tipo de pergunta inválido.\n");
        return 0;
    }
}

void mostrarInformacaoJogadores(Jogadores jogadores[], int qntJogadores)
{
    int opcao;

    for (int i = 0; i < qntJogadores; i++)
    {
        printf("Jogador %d:\n", i + 1);
        printf("Nome: %s\n", jogadores[i].info->nome);
        printf("Numero de perguntas respondidas: %d\n", jogadores[i].numPerguntasRespondidas);
        printf("\n\n");
    }

    printf("1) Listar jogadores por nome | 2) Listar jogadores por idade\n> ");

    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            system("cls");
            listarJogadoresPorNome(jogadores, qntJogadores);
            system("pause");
            break;

        case 2:
            system("cls");
            // TODO: Listar por idade
            // listarJogadoresPorIdade(jogadores, qntJogadores);
            system("pause");
            break;
    }

}

int proximoJogador(int jogadorAtual, int qntJogadores)
{
    return (jogadorAtual + 1) % qntJogadores;
}

void apresentarPergunta(Pergunta *pergunta)
{
    switch (pergunta->tipo)
    {
    case 1:
        exibirPerguntaEscolhaMultipla(pergunta);
        break;
    case 2:
        exibirPerguntaVerdadeiroFalso(pergunta);
        break;
    default:
        printf("Tipo de pergunta inválido.\n");
    }
}

void guardarJogo(char *vencedor)
{
    FILE *ficheiro = fopen("dados/jogos.txt", "a");

    if (ficheiro == NULL)
    {
        printf("Falha ao abrir o ficheiro.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    char data_string[20];

    strftime(data_string, sizeof(data_string), "%d-%m-%Y", data_atual);
    fprintf(ficheiro, "Data: %s\n", data_string);
    fprintf(ficheiro, "Vencedor: %s\n\n", vencedor);
    //GUADAR OS USERS DOS JOGADORES COM AS PONTUACOES DE CADA UM
    //MOSTRAR A PONTUACAO TOTAL DO JOGO (SOMATORIO DAS PONTUACOES DE TODOS OS PLAYERS)

    fclose(ficheiro);
}

void mostrarJogos() //LIMITAR PARA O TOP10 DE PONTUACOES
{
    FILE *ficheiro = fopen("dados/jogos.txt", "r");

    if (ficheiro == NULL)
    {
        printf("Falha ao abrir o ficheiro.\n");
        return;
    }

    char linha[100];

    while (fgets(linha, sizeof(linha), ficheiro) != NULL)
    {
        printf("%s", linha);
    }

    fclose(ficheiro);
}

void iniciarJogo(Utilizadores *listaUtilizadores, Pergunta *listaPerguntas)
{
    int qntJogadores;
    char vencedor[50];

    system("cls");
    printf("Quantos jogadores vao jogar (2-4) --> ");
    scanf("%d", &qntJogadores);

    if (qntJogadores < 2 || qntJogadores > 4)
    {
        printf("Numero de jogadores invalidos.");
        return;
    }

    Utilizadores *utilizadores[4] = {NULL};

    for (int i = 0; i < qntJogadores; i++)
    {
        utilizadores[i] = iniciarSessao(listaUtilizadores);
    }

    Jogadores jogadores[4] = {NULL};

    for (int i = 0; i < qntJogadores; i++)
    {
        jogadores[i].info = utilizadores[i];
        jogadores[i].numPerguntasRespondidas = 0;
    }

    system("cls");

    int jogo = 1, jogadorAtual = 0;

    while (jogo)
    {
        system("cls");
        printf("Jogador atual: %s\n", jogadores[jogadorAtual].info->nome);
        printf("Numero de perguntas respondidas: %d\n", jogadores[jogadorAtual].numPerguntasRespondidas);
        printf("\n");

        Pergunta *perguntaAtual = obterPergunta(listaPerguntas);
        apresentarPergunta(perguntaAtual);

        char resposta[50];
        printf("Digite a resposta: ");
        fgets(resposta, sizeof(resposta), stdin);
        resposta[strcspn(resposta, "\n")] = '\0';

        if (verificarResposta(perguntaAtual, resposta))
        {
            printf("Resposta correta!\n");
            //ADICIONAR PONTOS
        }
        else
        {
            printf("Resposta incorreta!\n");

            jogadorAtual = proximoJogador(jogadorAtual, qntJogadores);
        }

        jogadores[jogadorAtual].numPerguntasRespondidas++;


        //FAZER A PARTE DE FINAL DO JOGO, OU SEJA, MOSTRAR AS PONTUAÇÕES SOMADAS DE CADA PLAYER E RALÇAR O VENCEDOR
        
    }

    system("cls");

    mostrarInformacaoJogadores(jogadores, qntJogadores);
    guardarJogo(vencedor);
}