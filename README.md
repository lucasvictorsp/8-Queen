### **8-Queen**<br/>

O problema das *8-Rainhas* foi proposto em 1848 na revista *Schachzeitung* pelo enxadrista *Max Bezzel* e ao longo dos anos foi avaliado por diversos matemáticos. A primeira solução foi proposta em 1850 por *Francz Nauck* que também o generalizou para o Problema das *N-Rainhas*.<br/>
<br/>
O problema das *8-Rainhas* possui 92 soluções distintas, que podem ser obtidas a partir de um conjunto de 12 soluções únicas, aplicando operações de simetria no tabuleiro (Rotação e reflexão).<br/>
<br/>
O problema das *N-Rainhas* consiste em colocar em um tabuleiro de xadrez de tamanho *N x N* com *N-rainhas* de forma que elas **não** se atacam.<br/>
<br/>
Este trabalho propõem uma sulução para o problema das 8-Rainhas a partir de um **algoritmo genético**.<br/>
<br/>
O problema foi solucionado utilizando um vetor de inteiros de tamanho 8 onde as posições do vetor indicam a coluna de um tabuleiro e os inteiros (de 1 a 8) gravados em casa posição do vetor indicam a linha. A combinação desses dois fatores indica a posição exata em que uma rainha se encontra no tabuleiro.<br/>
<br/>
## Pseudocódigo do Algoritmo Genético:

*Entrada*: População (total de indivíduos)
	*Enquanto* não for solução
		**Para Cada** indivíduo da População
			**Se** indivíduo é a solução
				**returna** individuo
		*EscolhePais*(População);
		*GeraProximaGeração*(População)
*Saída*: um indivíduo que é a solução do problema, ou seja, que contém 8 rainhas em um tabuleiro das quais nenhumas se atacam.
<br/>

## Método Para Escoler os Pais:
- Aleatório;
- Roleta.
<br/>

## Método Para Gerar a Nova Geração:
- Apenas um filho;
- Gera dois filhos.

![alt text](https://github.com/lucasvictorsp/Peg-solitaire/blob/main/exemplos%20de%20tabuleiro.png)