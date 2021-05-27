/* 
 * File:   Queen.cpp
 * Author: DPIUFV
 * 
 * Created on 26 de Abril de 2015, 16:55
 */

#include "Queen.h"

Queen::Queen(int VetorQueens[TAM]){
    for(int i = 0; i < TAM; i++){
        Queens[i] = VetorQueens[i];
    }
    this->VerificaQueens();
}

Queen::Queen(const Queen &orig) {
    for(int i = 0; i < TAM; i++){
        this->Queens[i] = orig.getPosicaoQueen(i);
        this->ataca[i] = orig.getAtacaQueen(i);
    }
    this->porcentagem = orig.porcentagem;
}

int Queen::getPosicaoQueen(int pos) const{
    if(pos >= 0 && pos <= 7){
        return (this->Queens[pos]);
    } else{
        cerr << "Erro.\nEoicao inesistente.\n";
    }
}

bool Queen::getAtacaQueen(int pos) const{
    if(pos >= 0 && pos <= 7){
        return (this->ataca[pos]);
    } else{
        cerr << "Erro.\nPoicao inesistente.\n";
    }
}

float Queen::getPorcentagemQueen() const{
    return (this->porcentagem);
}

void Queen::setPosicaoQueen(int coluna, int Queen){
    if(coluna >= 0 && coluna <= 7){
        this->Queens[coluna] = Queen;
    } else{
        cerr << "Erro.\nColuna inesistente.\n";
    }
}

void Queen::setAtacaQueen(int coluna, bool atacar){
    if(coluna >= 0 && coluna <= 7){
        this->ataca[coluna] = atacar;
    } else{
        cerr << "Erro.\nColuna inesistente.\n";
    }
}

void Queen::setPorcentagemQueen(float porc){
    this->porcentagem = porc;
}

void Queen::setQueen(int VetorQueens[], bool atacar[], float porc){
    for(int i = 0; i < TAM; i++){
        this->setPosicaoQueen(i, VetorQueens[i]);
        this->setAtacaQueen(i, atacar[i]);
    }
    this->setPorcentagemQueen(porc);
}

void Queen::VerificaQueens(){
    for(int i = 0; i < (TAM - 1); i++){
        for(int j = (i + 1); j < TAM; j++){
                if(this->getPosicaoQueen(i) > this->getPosicaoQueen(j)){
                    if(((this->getPosicaoQueen(i) - this->getPosicaoQueen(j)) == (i - j)) || ((this->getPosicaoQueen(i) - this->getPosicaoQueen(j)) == (j - i))){
                        this->setAtacaQueen(i, true);
                        this->setAtacaQueen(j, true);
                    }
                } else if(this->getPosicaoQueen(i) < this->getPosicaoQueen(j)){
                    if(((this->getPosicaoQueen(j) - this->getPosicaoQueen(i)) == (j - i)) || ((this->getPosicaoQueen(j) - this->getPosicaoQueen(i)) == (i - j))){
                        this->setAtacaQueen(i, true);
                        this->setAtacaQueen(j, true);
                    }
                } else{
                    cerr << "Erro.\nA duas Queens na mesma linha ou coluna.\n"; //Acusa um erro pois isso é uma restrição da classe.
                }
        }
    }
    int contQueen = 0;
    for(int i = 0; i < TAM; i++){
        if(!this->getAtacaQueen(i)){
            contQueen++;
        }
    }

    float Porcentagem = PORC * contQueen;
    this->setPorcentagemQueen(Porcentagem);
}

void Queen::IniciaQueen(){
    int aux;
    bool igual;
    for(int i = 0; i < TAM; i++){
        do{
            igual = false;
            aux = (rand() % TAM) + 1;
            for(int j = (i - 1); j >= 0; j--){
                if(aux == this->getPosicaoQueen(j)){
                    igual = true;
                }
            }
        } while(igual);
        this->setPosicaoQueen(i, aux);
    }
    this->VerificaQueens();
}

void Queen::crossover(const Queen &r, const Queen &r1){
    int i = 0;
    int auxRand1;
    auxRand1 = rand() % 7;
    while(i < (auxRand1)){
        this->setPosicaoQueen(i, r.getPosicaoQueen(i));
        i++;
    }
    while(i < TAM){
        this->setPosicaoQueen(i, r1.getPosicaoQueen(i));
        i++;
    }
    
    int vetorAux1[9];
    vetorAux1[0] = -10000; //Apenas para demostra que a posição 0 é descartada do vetor
    for(i = 1; i < 10; i++)
        vetorAux1[i] = 0;
    
    int vetorAux2[4];
    int vetorAux3[4];
    int contRepitido = 0;
    for(i = 0; i < TAM; i++){
        if(vetorAux1[this->getPosicaoQueen(i)] == 0){
            vetorAux1[this->getPosicaoQueen(i)] = getPosicaoQueen(i);
        } else if(vetorAux1[this->getPosicaoQueen(i)] != 0){
            vetorAux2[contRepitido] = i;
            vetorAux3[contRepitido++] = this->getPosicaoQueen(i);
        }
    }

    int seleciona;
    bool igual;
    int vetorAuxSeleciona[contRepitido];
    for(i = 0; i < contRepitido; i++){
        vetorAuxSeleciona[i] = -1;
    }
    int cont = 0, contRepitidoAux = contRepitido;
    while(contRepitido > 0){
        do{
            igual = false;
            seleciona = rand() % contRepitidoAux;
            vetorAuxSeleciona[cont] = seleciona;
            cont++;
            for(int j = 0; j < (cont -1); j++){
                if(seleciona == vetorAuxSeleciona[j]){
                    igual = true;
                    cont--;
                    break;
                }
            }
        } while(igual);
        for(i = 0; i < 9; i++){
            if(vetorAux1[i] == 0){
                this->setPosicaoQueen(vetorAux2[seleciona], i);
                vetorAux1[i] = vetorAux2[seleciona];
                break;
            }
        }
            contRepitido--;
    }

    int auxRand;
    auxRand = rand() & 100;
    if(auxRand <= 7){
        this->mutacao();
    } else {
        this->VerificaQueens();
    }

}

void Queen::mutacao(){
    int auxColuna1;
    int auxColuna2;

    do{
        auxColuna1 = rand() % TAM;
        auxColuna2 = rand() % TAM;
    } while(auxColuna1 == auxColuna2);
    
    int aux = this->getPosicaoQueen(auxColuna1);
    this->setPosicaoQueen(auxColuna1, this->getPosicaoQueen(auxColuna2));
    this->setPosicaoQueen(auxColuna2, aux);

    this->VerificaQueens();
}

void Queen::imprimeTabuleiro(){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if((this->getPosicaoQueen(j) - 1) == i){
                cout << "X ";
            } else{
                cout << "0 ";
            }
        }
        cout << "\n";
    }
}

Queen& Queen::operator=(const Queen &r){
    if(this != &r){
        for(int i = 0; i < TAM; i++){
            this->Queens[i] = r.getPosicaoQueen(i);
            this->ataca[i] = r.getAtacaQueen(i);
        }
        this->porcentagem = r.porcentagem;
    }
    return *this;
}

bool Queen::operator!=(const Queen &r){
    for(int i = 0; i < TAM; i++){
        if(this->Queens[i] != r.getPosicaoQueen(i)){
            return true;
        }
    }
    return false;
}

bool Queen::operator==(const Queen &r){
    for(int i = 0; i < TAM; i++){
        if(this->Queens[i] != r.getPosicaoQueen(i)){
            return false;
        }
    }
    return true;
}

bool Queen::operator>(const Queen &r){
    return (this->getPorcentagemQueen() >= r.getPorcentagemQueen());
}

ostream& operator<<(ostream &os , const Queen &r){
    os << "<";
    for(int i = 0; i < TAM; i++){
        //os << "(" << (char) (i + 65) << ", " << r.getPosicaoQueen(i) << ")";
        os << r.getPosicaoQueen(i);
        if(i < (TAM - 1))
            os << ", ";
    }
    os << "> ";
    return os;
}

Queen::~Queen() {

}

