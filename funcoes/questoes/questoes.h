#ifndef QUESTOES_H
#define QUESTOES_H
    typedef struct pergunta
    {
        int numero, opcaoCorreta;
        char opcoes[4][50], resposta[50], pergunta[100];
        Serie serie;
        Tipo_Pergunta tipo;
        struct pergunta *proximo;
    } Pergunta;

    int verificarIndicePergunta(Pergunta* inicio, int indice);
    void guardarPerguntas(Pergunta** inicio);
    Pergunta* criarPerguntaEscolhaMultipla(char pergunta[], char opcoes[][50], int resposta, Serie *serie);
    Pergunta* criarPerguntaVerdadeiroFalso(char pergunta[], int resposta, Serie *serie);
    void adicionarPergunta(Pergunta** inicio, Pergunta* novaPergunta);
    void criarPergunta(Pergunta** inicio);
    void removerPergunta(Pergunta** inicio, int indice);
    void carregarPerguntas(Pergunta** listaPerguntas);
    void exibirPerguntaEscolhaMultipla(Pergunta* pergunta);
    void exibirPerguntaVerdadeiroFalso(Pergunta* pergunta);
    void exibirPerguntas(Pergunta* inicio);
    Pergunta* obterPergunta(Pergunta* listaPerguntas);

    #include "questoes.c"
#endif /* QUESTOES_H */