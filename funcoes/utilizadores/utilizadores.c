int utilizadorExiste(char *username, Utilizadores **listaUtilizadores)
{
    Utilizadores *utilizador = *listaUtilizadores;

    while (utilizador != NULL)
    {
        if (strcmp(utilizador->user, username) == 0)
        {
            return 1;
        }

        utilizador = utilizador->proximo;
    }

    return 0;
}

int iniciarSessaoAdministrador(Utilizadores *listaUtilizadores, Utilizadores **utilizadorAdministrador)
{
    Utilizadores *utilizador = listaUtilizadores;
    *utilizadorAdministrador = NULL;

    char user[50], password[50];
    fflush(stdin);

    // Logica para preencher os dados do utilizador
    printf("Username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    while (utilizador != NULL)
    {
        if (strcmp(utilizador->user, user) == 0 && strcmp(utilizador->password, password) == 0)
        {
            if (utilizador->administrador == 1)
                *utilizadorAdministrador = utilizador;
            break;
        }

        utilizador = utilizador->proximo;
    }

    if (*utilizadorAdministrador != NULL)
        return 1;
    else
        return 0;
}

Utilizadores *iniciarSessao(Utilizadores *listaUtilizadores)
{
    Utilizadores *utilizador = NULL;
    do
    {
        system("cls");
        utilizador = listaUtilizadores;
        char user[50], password[50];
        fflush(stdin);
        printf("Username: ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0';

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        while (utilizador != NULL)
        {
            if (strcmp(utilizador->user, user) == 0 && strcmp(utilizador->password, password) == 0)
            {
                return utilizador;
            }

            utilizador = utilizador->proximo;
        }

        if (utilizador == NULL)
        {
            system("cls");
            printf("Utilizador ou password invalidos.\n\n");
        }
    } while (utilizador == NULL);

    return NULL;
}

void fecharSessaoAdministrador(Utilizadores **utilizadorAdministrador)
{
    *utilizadorAdministrador = NULL;
}

void criarUtilizador(Utilizadores **listaUtilizadores, Utilizadores *utilizadorAdministrador)
{
    FILE *arquivo = fopen("dados/utilizadores.bin", "ab+");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    Utilizadores *utilizador = (Utilizadores *)malloc(sizeof(Utilizadores));

    utilizador->proximo = NULL;
    utilizador->anterior = NULL;

    if (utilizador == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    fflush(stdin);

    // Logica para preencher os dados do utilizador
    printf("Nome do utilizador: ");
    fgets(utilizador->nome, sizeof(utilizador->nome), stdin);
    utilizador->nome[strcspn(utilizador->nome, "\n")] = '\0';

    do
    {
        if (utilizadorExiste(utilizador->user, listaUtilizadores))
            printf("\nEsse utilizador ja existe!\n");

        printf("Username: ");
        fgets(utilizador->user, sizeof(utilizador->user), stdin);
        utilizador->user[strcspn(utilizador->user, "\n")] = '\0';
    } while (utilizadorExiste(utilizador->user, listaUtilizadores));

    printf("Password: ");
    fgets(utilizador->password, sizeof(utilizador->password), stdin);
    utilizador->password[strcspn(utilizador->password, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &(utilizador->idade));
    getchar();

    if (utilizadorAdministrador != NULL)
    {
        if (utilizadorAdministrador->administrador == 1)
        {
            printf("O jogador e um administrador? (1 - Sim | 2 - Nao) ");
            scanf("%d", &(utilizador->administrador));
            getchar();
        }
    }
    else
    {
        utilizador->administrador = 0;
    }

    printf("Nacionalidade: ");
    fgets(utilizador->nacionalidade, sizeof(utilizador->nacionalidade), stdin);
    utilizador->nacionalidade[strcspn(utilizador->nacionalidade, "\n")] = '\0';

    printf("Localidade: ");
    fgets(utilizador->localidade, sizeof(utilizador->localidade), stdin);
    utilizador->localidade[strcspn(utilizador->localidade, "\n")] = '\0';

    strcpy(utilizador->dataUltimoJogo, "--/--/----");

    // Gravar o utilizador no ficheiro binario
    fwrite(utilizador, sizeof(Utilizadores), 1, arquivo);

    // Adicionar o novo utilizador à lista de utilizadores
    if (*listaUtilizadores == NULL)
    {
        *listaUtilizadores = utilizador;
    }
    else
    {
        Utilizadores *temp = *listaUtilizadores;

        while (temp->proximo != NULL)
            temp = temp->proximo;

        temp->proximo = utilizador;

        utilizador->anterior = temp;
    }

    printf("Utilizador criado com sucesso!\n");

    system("pause");
}

void removerUtilizador(char *username, Utilizadores **listaUtilizadores)
{
    Utilizadores *atual = *listaUtilizadores;
    Utilizadores *anterior = NULL;

    // Percorrer a lista ate encontrar o utilizador ou o fim da lista
    while (atual != NULL && strcmp(atual->user, username) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o utilizador foi encontrado
    if (atual != NULL)
    {
        // Atualizar os ponteiros para remover o utilizador da lista
        if (anterior != NULL)
            anterior->proximo = atual->proximo;
        else
            *listaUtilizadores = atual->proximo;

        // Libertar a memoria ocupada pelo utilizador removido
        free(atual);

        // Atualizar o ficheiro com a nova lista
        FILE *ficheiro = fopen("dados/utilizadores.bin", "wb");

        if (ficheiro == NULL)
        {
            printf("Erro ao abrir o ficheiro.\n");
            return;
        }

        atual = *listaUtilizadores;

        while (atual != NULL)
        {
            fwrite(atual, sizeof(Utilizadores), 1, ficheiro);
            atual = atual->proximo;
        }

        fclose(ficheiro);
    }
}

void listarUtilizadores(Utilizadores *listaUtilizadores)
{
    int opcao;
    system("cls");

    Utilizadores *temp = listaUtilizadores;

    while (temp != NULL)
    {
        printf("Nome: %s\n", temp->nome);
        printf("Username: %s\n", temp->user);
        printf("Idade: %d\n", temp->idade);
        printf("Nacionalidade: %s\n", temp->nacionalidade);
        printf("Localidade: %s\n", temp->localidade);
        printf("Administrador: %s\n", (temp->administrador == 1) ? "Sim" : "Nao");
        printf("Data do ultimo jogoe: %s\n", temp->dataUltimoJogo);
        printf("--------------------\n");

        temp = temp->proximo;
    }

    system("pause");
}

void carregarUtilizadores(Utilizadores **listaUtilizadores)
{
    FILE *arquivo = fopen("dados/utilizadores.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    Utilizadores utilizador;

    while (fread(&utilizador, sizeof(Utilizadores), 1, arquivo) == 1)
    {
        Utilizadores *novoUtilizador = (Utilizadores *)malloc(sizeof(Utilizadores));
        strcpy(novoUtilizador->user, utilizador.user);
        strcpy(novoUtilizador->password, utilizador.password);
        strcpy(novoUtilizador->nome, utilizador.nome);
        novoUtilizador->idade = utilizador.idade;
        strcpy(novoUtilizador->nacionalidade, utilizador.nacionalidade);
        strcpy(novoUtilizador->localidade, utilizador.localidade);
        strcpy(novoUtilizador->dataUltimoJogo, utilizador.dataUltimoJogo);
        novoUtilizador->administrador = utilizador.administrador;
        novoUtilizador->anterior = NULL;
        novoUtilizador->proximo = NULL;

        // Adicionar o novo utilizador à lista de utilizadores
        if (*listaUtilizadores == NULL)
        {
            *listaUtilizadores = novoUtilizador;
        }
        else
        {
            Utilizadores *temp = *listaUtilizadores;
            while (temp->proximo != NULL)
                temp = temp->proximo;

            temp->proximo = novoUtilizador;
            novoUtilizador->anterior = temp;
        }
    }

    fclose(arquivo);
}

void criarUtilizadorDireto(Utilizadores **listaUtilizadores, Utilizadores *utilizador) {
    FILE *arquivo = fopen("dados/utilizadores.bin", "ab+");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    if(utilizador == NULL) {
        printf("O utilizador é inválido.");
        return;
    }

    utilizador->proximo = NULL;
    utilizador->anterior = NULL;

    fflush(stdin);

    // Gravar o utilizador no ficheiro binario
    fwrite(utilizador, sizeof(Utilizadores), 1, arquivo);

    // Adicionar o novo utilizador à lista de utilizadores
    if (*listaUtilizadores == NULL)
    {
        *listaUtilizadores = utilizador;
    }
    else
    {
        Utilizadores *temp = *listaUtilizadores;

        while (temp->proximo != NULL)
            temp = temp->proximo;

        temp->proximo = utilizador;

        utilizador->anterior = temp;
    }

    printf("Utilizador admin criado com sucesso!\n");
}