Serie* criar_serie(int numero_da_serie, int numero_de_perguntas, Tipo_Pergunta tipo) {
    Serie* nova_serie = (Serie*)malloc(sizeof(Serie));

    nova_serie->numero_da_serie = numero_da_serie;
    nova_serie->numero_de_perguntas = numero_de_perguntas;
    nova_serie->tipo = tipo;
    nova_serie->anterior = NULL;
    nova_serie->proximo = NULL;

    return nova_serie;
}

void guardarSeries(Serie *listaSeries) {
    FILE *arquivo = fopen("dados/series.bin", "wb+");

    if (arquivo == NULL) {
        printf("Erro ao abrir ficheiro.\n");
        return;
    }

    Serie *temp = listaSeries;

    while (temp != NULL) {
        fwrite(temp, sizeof(Serie), 1, arquivo);
        temp = temp->proximo;
    }

    fclose(arquivo);
}

void adicionar_serie(Serie** inicio, Serie* nova_serie) {
    if (*inicio == NULL) {
        *inicio = nova_serie;
    } else {
        Serie* temp = *inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = nova_serie;
        nova_serie->anterior = temp;
    }

    guardarSeries(*inicio);
}

void remover_serie(Serie** inicio, int numero_da_serie) {
    Serie* temp = *inicio;
    
    while (temp != NULL && temp->numero_da_serie != numero_da_serie) {
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("A serie com numero %d não foi encontrada.\n", numero_da_serie);
        return;
    }

    if (temp->anterior != NULL) {
        temp->anterior->proximo = temp->proximo;
    } else {
        *inicio = temp->proximo;
    }

    if (temp->proximo != NULL) {
        temp->proximo->anterior = temp->anterior;
    }

    free(temp);
    printf("A serie com numero %d foi removida.\n", numero_da_serie);
}

void criar_series_iniciais(Serie** inicio) {
    Serie* serie1 = criar_serie(1, 8, ESCOLHA_MULTIPLA);
    Serie* serie2 = criar_serie(2, 7, VERDADEIRO_FALSO);
    Serie* serie3 = criar_serie(3, 6, ESCOLHA_MULTIPLA);
    Serie* serie4 = criar_serie(4, 5, VERDADEIRO_FALSO);

    adicionar_serie(inicio, serie1);
    adicionar_serie(inicio, serie2);
    adicionar_serie(inicio, serie3);
    adicionar_serie(inicio, serie4);
}

void listar_series(Serie* inicio) {
    Serie* temp = inicio;

    while (temp != NULL) {
        printf("Serie %d: %d perguntas, Tipo: %s\n",
               temp->numero_da_serie,
               temp->numero_de_perguntas,
               temp->tipo == VERDADEIRO_FALSO ? "Verdadeiro/Falso" : "Escolha Multipla");
        temp = temp->proximo;
    }
}

Serie obterSerie(int numero) {
    Serie serie;

    FILE *arquivo = fopen("dados/series.bin", "rb+");

    if (arquivo == NULL) {
        printf("Erro ao abrir ficheiro.\n");
        return serie;
    }

    while (fread(&serie, sizeof(Serie), 1, arquivo) == 1) {
        if (serie.numero_da_serie == numero) {
            fclose(arquivo);
            return serie;
        }
    }

    fclose(arquivo);
    return serie;
}

void carregarSeries(Serie **listaSeries) {
    FILE *arquivo = fopen("dados/series.bin", "rb+");

    if (arquivo == NULL) {
        printf("Erro ao abrir ficheiro.\n");
        return;
    }

    Serie *serie;

    while (fread(&serie, sizeof(Serie), 1, arquivo) == 1) {
        Serie *novaSerie = (Serie *)malloc(sizeof(Serie));

        novaSerie->numero_da_serie = serie->numero_da_serie;
        novaSerie->numero_de_perguntas = serie->numero_de_perguntas;
        novaSerie->tipo = serie->tipo;
        novaSerie->anterior = NULL;
        novaSerie->proximo = NULL;

        if (*listaSeries == NULL)
        {
            *listaSeries = novaSerie;
        }
        else
        {
            Serie *temp = *listaSeries;
            while (temp->proximo != NULL)
                temp = temp->proximo;

            temp->proximo = novaSerie;
            novaSerie->anterior = temp;
        }

    }

    fclose(arquivo);
}