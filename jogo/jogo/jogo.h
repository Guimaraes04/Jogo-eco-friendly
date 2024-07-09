#ifndef JOGO_H
#define JOGO_H
    int verificarResposta(Pergunta *pergunta, char *resposta);
    void mostrarInformacaoJogadores(Jogadores jogadores[], int qntJogadores);
    int proximoJogador(int jogadorAtual, int qntJogadores);
    void apresentarPergunta(Pergunta *pergunta);
    void guardarJogo(char *vencedor);
    void mostrarJogos();
    void iniciarJogo(Utilizadores *listaUtilizadores, Pergunta *listaPerguntas);
    #include "jogo.c"
#endif /* JOGO_H */