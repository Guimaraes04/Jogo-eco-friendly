#ifndef UTILIZADORES_H
#define UTILIZADORES_H

typedef struct utilizadores
{
    char user[50];
    char password[50];
    char nome[50];
    int idade;
    int administrador;
    char nacionalidade[50];
    char localidade[50];
    char dataUltimoJogo[50];
    struct utilizadores *anterior;
    struct utilizadores *proximo;
} Utilizadores;

int utilizadorExiste(char *username, Utilizadores **listaUtilizadores);
int iniciarSessaoAdministrador(Utilizadores *listaUtilizadores, Utilizadores **utilizadorAdministrador);
void fecharSessaoAdministrador(Utilizadores **utilizadorAdministrador);
void criarUtilizador(Utilizadores **listaUtilizadores, Utilizadores *utilizadorAdministrador);
void removerUtilizador(char *username, Utilizadores **listaUtilizadores);
void listarUtilizadores(Utilizadores *listaUtilizadores);
void carregarUtilizadores(Utilizadores **listaUtilizadores);
void criarUtilizadorDireto(Utilizadores **listautilizadores, Utilizadores *utilizador);

#include "utilizadores.c"
#endif /* UTILIZADORES_H */