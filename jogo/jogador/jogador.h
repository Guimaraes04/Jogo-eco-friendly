#ifndef JOGADOR_H
#define JOGADOR_H
typedef struct jogador
{
    Utilizadores *info;
    int numPerguntasRespondidas;
    int pontuacao;
} Jogadores;

int compararPorNome(void *a, void *b);
void listarJogadoresPorNome(Jogadores jogadores[], int qntJogadores);

#include "jogador.c"
#endif /* JOGADOR_H */