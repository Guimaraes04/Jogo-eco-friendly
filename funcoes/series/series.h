#ifndef SERIES_H
#define SERIES_H

typedef enum tipo_de_pergunta {
    VERDADEIRO_FALSO,
    ESCOLHA_MULTIPLA
} Tipo_Pergunta;

typedef struct serie {
    int numero_da_serie, numero_de_perguntas;
    Tipo_Pergunta tipo;
    int pontuacao_resposta;
    struct serie *anterior;
    struct serie *proximo;
} Serie;

void carregarSeries(Serie **listaSeries);
Serie obterSerie(int numero_da_serie);
#include "series.c"
#endif //SERIES_H
