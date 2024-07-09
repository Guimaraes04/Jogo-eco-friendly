void abrirMenu()
{
    int menu, menuAdmin, menuAdminPerguntas, menuAdminJogadores, menuAdminJogo, menuAdminSeries, tipo;

    /**
     *
     * Utilizadores
     *
     */
    Utilizadores *listaUtilizadores = NULL, *utilizadorAdministrador = NULL;
    carregarUtilizadores(&listaUtilizadores);

    /**
     *
     * Séries
     *
     */
    Serie *listaSeries = NULL;
    carregarSeries(&listaSeries);

    /**
     *
     * Perguntas
     *
     */
    Pergunta *listaPerguntas = NULL;
    carregarPerguntas(&listaPerguntas);

    /**
     *
     * Criar Administrador
     *
     */
    Utilizadores *administrador = NULL;
    administrador = (Utilizadores *)malloc(sizeof(Utilizadores));

    strcpy(administrador->user, "admin");
    strcpy(administrador->nome, "Administrador");
    strcpy(administrador->password, "admin");
    administrador->idade = 0;
    strcpy(administrador->nacionalidade, "N/A");
    strcpy(administrador->localidade, "N/A");
    administrador->administrador = 1;
    strcpy(administrador->dataUltimoJogo, "N/A");

    if (!utilizadorExiste("admin", &listaUtilizadores))
    {
        criarUtilizadorDireto(&listaUtilizadores, administrador);
    } else {
        free(administrador);
    }

    do
    {
        system("cls");
        printf("------------------------ MENU ------------------------\n\n");
        printf("1) > Jogar\n");
        printf("2) > Entrar como administrador\n");
        printf("0) > Sair");
        printf("\n\n--> ");
        scanf("%d", &menu);

        system("cls");

        switch (menu)
        {
        case 1:
            iniciarJogo(listaUtilizadores, listaPerguntas);

            break;

        case 2:
            if (!iniciarSessaoAdministrador(listaUtilizadores, &utilizadorAdministrador))
            {
                system("cls");
                printf("Esse utilizador ou password nao estao corretos ou o utilizador nao e um administrador.\n\n");
                system("pause");
                break;
            }

            do
            {
                system("cls");
                printf("------------------------ MENU ------------------------\n\n");
                printf("1) > Jogadores\n");
                printf("2) > Séries\n");
                printf("3) > Perguntas\n");
                printf("4) > Jogo\n");
                printf("0) > Sair");
                printf("\n\n--> ");
                scanf("%d", &menuAdmin);

                switch (menuAdmin)
                {
                case 1:
                    do
                    {
                        system("cls");
                        printf("------------------------ MENU ------------------------\n\n");
                        printf("1) > Criar jogador\n");
                        printf("2) > Remover jogador\n");
                        printf("3) > Listar jogador\n");
                        printf("0) > Sair");
                        printf("\n\n--> ");
                        scanf("%d", &menuAdminJogadores);

                        switch (menuAdminJogadores)
                        {
                        case 1:
                            criarUtilizador(&listaUtilizadores, utilizadorAdministrador);
                            break;

                        case 2:
                            system("cls");
                            fflush(stdin);
                            char username[35];
                            printf("Username a remover --> ");
                            fgets(username, sizeof(username), stdin);
                            username[strcspn(username, "\n")] = '\0';
                            removerUtilizador(username, &listaUtilizadores);
                            break;

                        case 3:
                            listarUtilizadores(listaUtilizadores);
                            break;
                        }
                    } while (menuAdminJogadores != 0);
                    break;

                case 2:
                    do
                    {
                        system("cls");
                        printf("------------------------ MENU ------------------------\n\n");
                        printf("2) > Listar séries\n");
                        printf("0) > Sair");
                        printf("\n\n--> ");
                        scanf("%d", &menuAdminSeries);
                    }
                    while (menuAdminSeries != 0);

                    break;

                case 3:
                    do
                    {
                        system("cls");
                        printf("------------------------ MENU ------------------------\n\n");
                        printf("1) > Criar pergunta\n");
                        printf("2) > Remover pergunta\n");
                        printf("3) > Listar perguntas\n");
                        printf("0) > Sair");
                        printf("\n\n--> ");
                        scanf("%d", &menuAdminPerguntas);

                        switch (menuAdminPerguntas)
                        {
                        case 1:
                            criarPergunta(&listaPerguntas);
                            break;

                        case 2:
                            system("cls");
                            fflush(stdin);
                            int pergunta;
                            printf("Numero da pergunta a remover --> ");
                            scanf("%d", &pergunta);

                            if (!verificarIndicePergunta(listaPerguntas, pergunta))
                            {
                                printf("Essa pergunta nao existe!\n");
                                system("pause");
                                break;
                            }

                            removerPergunta(&listaPerguntas, pergunta);
                            break;

                        case 3:
                            exibirPerguntas(listaPerguntas);
                            break;
                        }
                    } while (menuAdminPerguntas != 0);
                    break;

                case 4:
                    mostrarJogos();
                    system("pause");
                    break;

                case 0:
                    fecharSessaoAdministrador(&utilizadorAdministrador);
                    break;
                }
            } while (menuAdmin != 0);
            break;

        case 0:

            break;

        default:
            break;
        }
    } while (menu != 0);

    while (listaUtilizadores != NULL)
    {
        Utilizadores *temp = listaUtilizadores;
        listaUtilizadores = listaUtilizadores->proximo;
        free(temp);
    }

    while (listaPerguntas != NULL)
    {
        Pergunta *temp = listaPerguntas;
        listaPerguntas = listaPerguntas->proximo;
        free(temp);
    }
}