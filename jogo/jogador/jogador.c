#include "jogador.h"
// Funcao de comparacao para ordenacao alfabética do nome
int compararPorNome(void *a, void *b)
{
    Jogadores *jogador1 = (Jogadores *)a;
    Jogadores *jogador2 = (Jogadores *)b;

    return strcmp(jogador1->info->nome, jogador2->info->nome);
}

void listarJogadoresPorNome(Jogadores jogadores[], int qntJogadores)
{
    //função qsort usada para ordenar o array de jogadores
    qsort(jogadores, qntJogadores, sizeof(Jogadores), (int (*)(const void *, const void *)) compararPorNome);

    printf("Lista de jogadores por ordem alfabética do nome:\n");
    for (int i = 0; i < qntJogadores; i++)
    {
        printf("%s\n", jogadores[i].info->nome);
    }
}