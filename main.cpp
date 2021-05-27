/* 
 * File:   main.cpp
 * Author: Lucas Victor
 *
 * Created on 26 de Abril de 2015, 14:44
 */

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "Queen.h"
#include "Lista.h"

using namespace std;

int vetorInicializador[TAM] = {-1};
//bool vetorAtaca[TAM] = {false, false, false, false, false, false, false, false};
/*
 * 
 */

#define POPULACAO 10
#define QuantPais 5

void EscolhePaisAleatorio(Queen []);

void EscolhePaisRoleta(Queen []);

void EscolhePaisMaisAdapitados(Queen []);

void ProximaGeracao(Queen []);

void ProximaGeracaoFihlosGemeos(Queen []);

void AlgoGenetico(Queen [], char );

void IniciaPopolacao(Queen []);

void menu(Queen []);

int main(int argc, char** argv) {
    srand((unsigned) time(NULL)); //gera valores para a função hand atravez do tempo(hora).

    Queen pop[POPULACAO];
    menu(pop);

    return 0;
}

void EscolhePaisAleatorio(Queen pop[]){
    int auxRand;
    for(int i = 0; i < QuantPais; i++){
        auxRand = rand() % POPULACAO;
        pop[i] = pop[auxRand];
    }
}

void EscolhePaisRoleta(Queen pop[]){
    Lista<Queen> vetorPorc;

    float somaPorcentagem = 0;
    for(int i = 0; i < POPULACAO; i++){
        vetorPorc.insereOrdenado(pop[i]);
        somaPorcentagem += pop[i].getPorcentagemQueen();
    }

    int somaPorcentagemInt;
    somaPorcentagemInt = somaPorcentagem;
    Queen popOrdenada [POPULACAO];
    Lista<Queen>::RefLComp p;
    int k = 0;
    while(!vetorPorc.EstaVazia()){
        p = vetorPorc.primeiro();
        popOrdenada[k] = vetorPorc.recupera(p);
        vetorPorc.remove(p);
        k++;
    }

    int auxRand;
    float auxSomaPorcentagemLista;
    Queen aux1;
    for(int i = 0; i < QuantPais; i++){
        auxSomaPorcentagemLista = 0;
        auxRand = rand() % somaPorcentagemInt;
        for(int j = 0; j < POPULACAO; j++){
            auxSomaPorcentagemLista += popOrdenada[j].getPorcentagemQueen();
            if(auxRand <= auxSomaPorcentagemLista){
                pop[i] = popOrdenada[j];
                break;
            }
        }
    }
}

void EscolhePaisMaisAdapitados(Queen pop[]){
    Lista<Queen> vetorPorc;

    for(int i = 0; i < POPULACAO; i++){
        vetorPorc.insereOrdenado(pop[i]);
    }

    Lista<Queen>::RefLComp p = vetorPorc.ultimo();
    for(int i = 0; i < QuantPais; i++){
        pop[i] = vetorPorc.recupera(p);
        p = vetorPorc.anterior(p);
    }
}

void ProximaGeracao(Queen pais[]){
    Queen filhos[POPULACAO];
    int auxRand1, auxRand2;
    for(int i = 0; i < POPULACAO; i++){
        do{
            auxRand1 = rand() % QuantPais;
            auxRand2 = rand() % QuantPais;
        } while(auxRand1 == auxRand2);

        filhos[i].crossover(pais[auxRand1], pais[auxRand2]);
    }
    for(int i = 0; i < POPULACAO; i++){
        pais[i] = filhos[i]; 
    }
}

void ProximaGeracaoFilhosGemeos(Queen pais[]){
    Queen filhos[POPULACAO];
    int auxRand1, auxRand2;
    for(int i = 0; i < POPULACAO; i+= 2){
        do{
            auxRand1 = rand() % QuantPais;
            auxRand2 = rand() % QuantPais;
        } while(auxRand1 == auxRand2);

        filhos[i].crossover(pais[auxRand1], pais[auxRand2]);
        filhos[i + 1].crossover(pais[auxRand2], pais[auxRand1]);
    }
    for(int i = 0; i < POPULACAO; i++){
        pais[i] = filhos[i]; 
    }
}

void AlgoGenetico(Queen pop[], char op){
    int contInteracao = 0;
    bool solucao = false;

    while(true){
        for(int i = 0; i < POPULACAO; i++){
            if(pop[i].getPorcentagemQueen() == 100){
                cout << pop[i] << endl;
                cout << "Numero de intecacoes: " << contInteracao << endl;
                solucao = true;
                break;
//                exit(1);
            }
        }

        if(solucao){
            break;
        }

        if(op == '1'){
            EscolhePaisAleatorio(pop);
            ProximaGeracao(pop);
            contInteracao++;
        //} else if(op == '2'){
        //    //cout << "OOOOOOPA" << endl;
        //    EscolhePaisRoleta(pop);
        //    ProximaGeracao(pop);
        //    contInteracao++;
        } else if(op == '2'){ //else if(op == '3'){
            EscolhePaisMaisAdapitados(pop);
            ProximaGeracao(pop);
            contInteracao++;
        } else if(op == '3'){
            EscolhePaisAleatorio(pop);
            ProximaGeracaoFilhosGemeos(pop);
            contInteracao++;
        //} else if(op == '5'){
        //    EscolhePaisRoleta(pop);
        //    ProximaGeracaoFilhosGemeos(pop);
        //    contInteracao++;
        } else{
            EscolhePaisMaisAdapitados(pop);
            ProximaGeracaoFilhosGemeos(pop);
            contInteracao++;
        }   
    }
}

void IniciaPopolacao(Queen pop[]){
    for(int i = 0; i < POPULACAO; i++){
        pop[i].IniciaQueen();
    }
}

void menu(Queen pop[]){
    clock_t time1, time2, time_diff;
    Queen auxImprime;
    bool desenha = false;
    char op;

    while(true){
                cout << "1-Selecao dos pais de forma totalmente aleatoria e gera 1 individuo por par de Rainhas.\n"
                //"2-Selecao dos pais por Roleta e gera 1 individuo por par de Rainhas.\n"
                "2-Selacao dos por Truncamento e gera 1 individuo por par de Rainhas.\n"
                "3-Selecao dos pais de forma totalmente aleatoria e gera 2 individuo por par de Rainhas.\n"
                //"5-Selecao dos pais por Roleta e gera 2 individuo por par de Rainhas.\n"
                "4-Selacao dos por Truncamento e gera 2 individuo por par de Rainhas.\n"
                "5-Sair.\n"
                "Escolha uma Opicao por favor: ";
        cin >> op;
        switch(op){
            case '1':
            case '2':
            case '3':
            case '4':
            {
                time1 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (antes de iniciar o calculo).
                IniciaPopolacao(pop);
                AlgoGenetico(pop, op);
                time2 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (depois de calcular o calculo).
                time_diff = time2 - time1; //obtem a diferenca entre os tempos antes e depois em ms.
                cout << "Tempo de execução do Algoritmo Genetico: " << time_diff << " ms\n\n" << endl;

                while(true){
                    cout << "Deseja desenhar o tabuleiro em tela(s ou S = sim e n ou N: nao):\n"
                            "X = Rainha.\n"
                            "O = Espaco vazio(Sem pacas).\n";
                    cin >> op;
                    switch(op){
                        case 's':
                        case 'S':
                        {
                            for(int i = 0; i < POPULACAO; i++){
                                if(pop[i].getPorcentagemQueen() == 100){
                                    auxImprime = pop[i];
                                }
                            }
                            auxImprime.imprimeTabuleiro();
                            desenha = true;
                            break;
                        }
                        case 'n':
                        case 'N':
                        {
                            desenha = true;
                            break;
                        }
                        default:
                        {
                            cout << "Opcao invalida.\n";
                        }
                    }
                    if(desenha){
                        break;
                    }
                }
                break;
            }
            //case '7':
            case '5':
            {
                exit(0);
                break;
            }
            default:
            {
                cout << "Opcao invalida.\n";
            }
        }
        cout << "\n\n\n=======================================================================================\n\n";
    }

}
