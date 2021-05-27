/* 
 * File:   Queen.h
 * Author: DPIUFV
 *
 * Created on 26 de Abril de 2015, 16:55
 */

#include <iostream>
#include <cstdlib>
#include <string>

using std::ostream;
using std::cerr;
using std::cout;


/*#ifndef ERRORAINHA_H
#define	ERRORAINHA_H

class ErroRainha {
    private:
        char msg[100];
    public:
        ErroLista(const char *s) {
            strcpy(msg, s);
        }

        char *what() {
            return msg;
        }
};

#endif//*/

#ifndef QUEEN_H
#define	QUEEN_H

#define TAM 8 //Define número de rainhas e tamanho do tabuleiro (numero de linahs e colunas).
#define PORC 12.5
class Queen {
    public:
        //Construtores
        Queen(){ } //Construtor default
        Queen(int []); //Construtor criado para inicializar um individuo com tabuleiro especificos que o usurio queira digitar.
        Queen(const Queen& orig); //Constrtor de Copiar, apesar de não estar trabalhando com alocação de memória dinâmica, ou seja, não  teria.
                                    //problema em usar o construtor que o proprio comppilador gera foi criado o proprio compilador da classe.

        //funcoes:
            //gets:
        int getPosicaoQueen(int ) const;   //Retorna a posição(linha e coluna) de uma rainha no tabuleiro.
        bool getAtacaQueen(int ) const;    //Retorna(verdadeiro ou falso) se uma dada rainha em uma posição(linha coluna) ataca ou/é atacada.
        float getPorcentagemQueen() const; // Retorna o quão bom um individio é pra reproduzir, ou seja, a porcentagem de rainahs se não se atacam.

            //sets
        void setQueen(int [], bool [], float );
        void setPosicaoQueen(int , int );
        void setAtacaQueen(int , bool );
        void setPorcentagemQueen(float );

            //Funcões criadas na classe(apenas para encapsular) mais é Especificas para o Algoritmo Genético:
        void VerificaQueens(); //Verifica de as 8-Queen em um tabuleiro se atacam umas as outras, e delimitando o quão um individuo é bom
                                //apartir desde quesito.
        void IniciaQueen(); //Inicializa de forma randomica um tabuleiro(individuo) com 8 Queens.
        void crossover(const Queen & , const Queen & ); //Faz o cruzameto de Dois individuos, gerando 2 individuos com caracterisca dos seus pais.
        void mutacao(); //Troca 2 Queens de posição no tabuleiro, ou seja, faz uma variação de um individuo em relação aos seus pais(essa função
                        //é chamada dentro da função crossover para cria variabalidade nos individuos).
        void imprimeTabuleiro();

            //sobrecarga dos operadors:
        Queen& operator=(const Queen & );
        bool operator!=(const Queen & );
        bool operator==(const Queen & );
        bool operator>(const Queen & );
        friend ostream& operator<<(ostream & , const Queen& );

        virtual ~Queen(); //Como não há dentro da classe rainha nenhuma alocação dinâmica de memoria  não há a necessidade de criar um destritor
                           //podendo ele ser virtual.

    private:
        int Queens[TAM];  //Vetor que simboliza o tabuleiro com as 8 Queens, tal que a posição do vetor mais 1 corresponde as colunas onde as Queens
                         //estão no tabuleiro e os numeros guardados dentro de cada posição do vetor corresponde a linha.
        bool ataca[TAM]; //Vetor boleano que guarda Verdadeiro caso uma rainha ataca e/ou é ataca por uma outra Queen, como por definição(restrição) da
                       //classe duas Queens não podem estar em uma mesma coluna, tomamos que a posição do vetor mais 1 indicando que o valor boeano
                       //guardado nela corresponde a rainha qu esta na mesma coluna do vetor rainhas.
        float porcentagem; //Variavel real que guarda o quão bom um individuo é bom para reproduzir.
};

#endif	/* Queen_H */