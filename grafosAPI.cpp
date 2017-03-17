/** 
   GrafosAPI TP01
   grafosAPI.cpp

   Purpose: Criar um grafo a partir da leitura de uma arquivo e ser capaz de executar funções basicas 
   como calcular o grau de um vértice, total de arestas
   e ser capaz de realizar a execução do algorítimo de Hierholzer no grafo criado.

   @authors Gustavo Dutra, Reginaldo Filho, Tiago Fonseca.
   @version 1.3.276 02/25/17

 */
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <iterator>

using namespace std;

typedef vector<vector<int> > Matriz;
typedef vector<int> Coluna;

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

struct Grafo{
	Matriz matriz;
	int vertices;
	int verticeInicial;
};

Grafo getGrafo(Grafo grafo);
Grafo getDigrafo(Grafo grafo);
int calculaGrau(Grafo grafo);
int calculaGrau(Grafo grafo, int verticeAC);
void arestaExiste(Grafo grafo);
int totalArestas(Grafo grafo);
int grafoVazio(Grafo* grafo);
void hierholzer(Grafo grafo);
vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho, int verticeInicial);


/** 
 */

int main(int argc, char** argv) {
    string linha;
    int isGrafo;
	Grafo grafo;
	grafo.vertices = 0;
	grafo.verticeInicial = 0;
	getline(cin, linha);
	std::istringstream(linha) >> isGrafo;
	
	if (isGrafo == 0){
		grafo = getGrafo(grafo);
	}else{
		grafo = getDigrafo(grafo);
	}
	hierholzer(grafo);
	//calculaGrau(grafo);
	//arestaExiste(grafo, grafo.vertices);
	//totalArestas(grafo);
	return 0;
}

/**
	Retorna um grafo preenchido após realizar a leitura de arquivo.
	@param grafo Grafo vazio a ser preenchido pelo método.
	@return Grafo preenchido após a leitura do arquivo.
*/

Grafo getGrafo(Grafo grafo){
	
	string linha, fim;
	getline(cin, linha);
	std::istringstream(linha) >> grafo.vertices;
	getline(cin, linha);
	std::istringstream(linha) >> grafo.verticeInicial;
	//int grafo[grafo.vertices][grafo.vertices] = {};	
	//cout << grafo.vertices << " Numero de nodos." << endl;
	//cout << grafo.verticeInicial << " Nodo de comeco." << endl; 
	for(int x = 0; x < grafo.vertices; x++){
		Coluna coluna(grafo.vertices, 0);
		grafo.matriz.push_back(coluna);
	}

	getline(cin, linha);
	while(linha.compare(fim) != 0){
		//cout << linha << endl;
		string line;
		int origem = 0;
		int destino = 0;
		int peso = 0;
		//cout << linha << endl;
		std::vector<std::string> spt = split(linha, ',');
		std::istringstream(spt[0]) >> origem;
		std::istringstream(spt[1]) >> destino;
		std::istringstream(spt[2]) >> peso;
		//std::istringstream(linha.substr(4)) >> peso;
		//cout << origem << " " << destino << " " << peso << endl;
		grafo.matriz[origem][destino] = peso;
		grafo.matriz[destino][origem] = peso;
		fim = linha;
		getline(cin, linha);
	}
	/*
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafo.matriz[x][y];
		}
		cout << endl;
	}
	*/
	
	return grafo;
}

/**
	Retorna um digrafo preenchido após realizar a leitura de arquivo.
	@param grafo Digrafo vazio a ser preenchido pelo método.
	@return Digrafo preenchido após a leitura do arquivo.
*/

Grafo getDigrafo(Grafo grafo){

	string linha, fim;
	getline(cin, linha);
	std::istringstream(linha) >> grafo.vertices;
	getline(cin, linha);
	std::istringstream(linha) >> grafo.verticeInicial; 	
	for(int x = 0; x < grafo.vertices; x++){
		cout << "aqui" << endl;
		Coluna coluna(grafo.vertices, 0);
		grafo.matriz.push_back(coluna);
	}
	
	getline(cin, linha);
	while(linha.compare(fim) != 0){
		//cout << linha << endl;
		int origem = 0;
		int destino = 0;
		int peso = 0;
		std::istringstream(linha) >> origem;
		std::istringstream(linha.substr(2)) >> destino;
		std::istringstream(linha.substr(4)) >> peso;
		//cout << origem << " " << destino << " " << peso << endl;
		grafo.matriz[origem][destino] = peso;
		fim = linha;
		getline(cin, linha);
	}
	
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafo.matriz[x][y];
		}
		cout << endl;
	}	
	return grafo;
}

/**
	Calcula o grau de um vética especifico de um grafo ou digrafo.
	@param grafo Grafo de onde se encontra o vértice.
	@return grau Grau do vétice escolhido.
*/

int calculaGrau(Grafo grafo){
	int escolhido;
	cout << "Digite o nodo a ter o grau calculado:";
	cin >> escolhido;
	int grau = calculaGrau(grafo,escolhido);
	return grau;
}

/**
	Calcula o grau de um vética especifico de um grafo ou digrafo.
	@param grafo Grafo de onde se encontra o vértice.
	@param int verticeAC vértice a ser calculado o grau.
	@return grau Grau do vétice escolhido.
*/
int calculaGrau(Grafo grafo, int verticeAC){
	int escolhido = verticeAC;
	int grau = 0;
	if (-1 < escolhido < grafo.vertices){
		for (int x = 0; x < grafo.vertices; x++){
			if (grafo.matriz[x][escolhido] > 0){
				grau++;
			}
		}
	}
	return grau;
}

/**
	Verifica a existência de uma aresta no grafo.
	@param grafo Grafo que será analisado.
*/

void arestaExiste(Grafo grafo){
	int nodo1, nodo2;
	cout << "Digite o primeiro nodo a ser verificado: ";
	cin >> nodo1;
	cout << "Digite o segundo nodo a ser verificado: ";
	cin >> nodo2;
	if ((-1 < nodo1 < grafo.vertices) && (-1 < nodo2 < grafo.vertices)){
		if (grafo.matriz[nodo1][nodo2] > 0){
			cout << "A aresta existe" << endl;
		} else {
			cout << "A aresta não existe" << endl;
		}
	}
}

/**
	Calcula o número total de arestas do grafo.
	@param grafo Grafo que será analisado.
	@return aresta Total de arestas do grafo.
*/

int totalArestas(Grafo grafo){
	bool completo = true;
	int aresta = 0;
	int grafoComplementar[grafo.vertices][grafo.vertices];
	for(int x = 0; x < grafo.vertices; x++){
		for(int y = x; y < grafo.vertices; y++){
			if (grafo.matriz[x][y] > 0){
				aresta++;
			}else if ( x!=y ){
				completo = false;
				grafoComplementar[x][y] = 1;
				grafoComplementar[y][x] = 1;
			}
		}
	}
	//cout << "Matriz grafoComplementar: " << endl; 
	/*
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafoComplementar[x][y];
		}
		cout << endl;
	}
	*/
	return aresta;
}

/*
* Funcao que verifica se nossa matriz esta vazia ou ainda tem espaco para percorrer.
* @param Grafo* index;
* @return int resp;
**/
int grafoVazio(Grafo* index){
	int resp;
	Grafo& grafo = *index;
	for (int i = 0; i < grafo.vertices; i++){
		for(int j = 0; j < grafo.vertices; j++){
			if(grafo.matriz[i][j] == 1){
				grafo.verticeInicial = i;
				return 1;
			} else resp = 0;
		}
	}
	return resp;
}

/**
	Executa o algorítimo de Hierholzer em um grafo, em busca de um caminho euleriano. OBS: O vértice inicial é sempre o de menor 
	índice numérico.
	@param grafo Grafo onde o algorítimo irá construir o caminho euleriano.
	
*/

void hierholzer(Grafo grafo){
	string resposta;
	int pos;
	vector<int> circuito;
	bool impar = false;
	int unicursal = 0;
	int contador = 0;
	int verticesImpar[2];
	int arestas = totalArestas(grafo);
	vector<int> caminho;
	for (int x = 0; x < grafo.vertices; x++){
		if (calculaGrau(grafo, x)%2 == 1){
			impar = true;
			unicursal++;
			if(unicursal < 3){
				verticesImpar[unicursal-1] = x;
			}
		}
	}

	if (impar == true){
		if (unicursal == 2){
			caminho.push_back(verticesImpar[1]);
			int x = verticesImpar[1], y = 0;
			while (grafo.matriz[x][y] == 0){
			y++;
		}
		caminho.push_back(y);
		grafo.matriz[x][y] = 0;
		grafo.matriz[y][x] = 0;
		caminho = hierholzer(&grafo, y, caminho, grafo.verticeInicial);
		//cout << "end 1 " << endl;
		while (grafoVazio(&grafo) != 0) {
			cout << grafo.verticeInicial << endl;
			vector<int>::iterator pos = caminho.begin();
			while(*pos != grafo.verticeInicial){
				pos++;
			}
			circuito.push_back(grafo.verticeInicial);
			int xcircuito = grafo.verticeInicial, ycircuito=0;
			while (grafo.matriz[xcircuito][ycircuito] == 0){
				ycircuito++;
			}
			circuito.push_back(ycircuito);
			grafo.matriz[xcircuito][ycircuito] = 0;
			grafo.matriz[ycircuito][xcircuito] = 0;
			circuito = hierholzer(&grafo, ycircuito, circuito, grafo.verticeInicial);
			vector<int>::iterator it = circuito.begin();
			do {
				//cout << *it << "-";
				it++;
			} while (it != circuito.end());
		//	cout << endl;
			caminho.insert(pos, circuito.begin(), circuito.end()-1);
		}
			vector<int>::iterator it = caminho.begin();
			do{
				string str = toString(*it);
				resposta = resposta + "-" + str;
				it++;
			} while (it != caminho.end());
			resposta = resposta.substr(1, resposta.length());
			printf("%s \n", resposta.c_str());
		} 
		else cout << "grafo não euleriano!" << endl;
	} 
	
	else {
		caminho.push_back(grafo.verticeInicial);
		int x = grafo.verticeInicial, y=0;
		while (grafo.matriz[x][y] == 0){
			y++;
		}
		caminho.push_back(y);
		grafo.matriz[x][y] = 0;
		grafo.matriz[y][x] = 0;
		caminho = hierholzer(&grafo, y, caminho, grafo.verticeInicial);
		//cout << "end 1 " << endl;
		while (grafoVazio(&grafo) != 0) {
			//cout << grafo.verticeInicial << endl;
			vector<int>::iterator pos = caminho.begin();
			while(*pos != grafo.verticeInicial){
				pos++;
			}
			circuito.push_back(grafo.verticeInicial);
			int xcircuito = grafo.verticeInicial, ycircuito=0;
			while (grafo.matriz[xcircuito][ycircuito] == 0){
				ycircuito++;
			}
			circuito.push_back(ycircuito);
			grafo.matriz[xcircuito][ycircuito] = 0;
			grafo.matriz[ycircuito][xcircuito] = 0;
			circuito = hierholzer(&grafo, ycircuito, circuito, grafo.verticeInicial);
			vector<int>::iterator it = circuito.begin();
			do {
				//cout << *it << "-";
				it++;
			} while (it != circuito.end());
		//	cout << endl;
			caminho.insert(pos, circuito.begin(), circuito.end()-1);
		}

		vector<int>::iterator it = caminho.begin();
		do {
			string str = toString(*it);
			resposta = resposta + "-" + str;
			it++;
		} while (it != caminho.end());
		
		resposta = resposta.substr(1, resposta.length());
		//cout << "Caminho encontrado: " << endl;
		printf("%s \n", resposta.c_str());
		//cout << resposta << endl;
	}
	/*
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafo.matriz[x][y];
		}
		cout << endl;
	}
	*/	
}

/**
	 Vetor que representa e armazena o caminho euleriano encontrado em um grafo.
	 @param index Passagem de um grafo por endereço.
	 @param vertice Vértice onde a execução do void hierholzer se encontra.
	 @param caminho Caminho que está sendo construido por void hierfholzer.
	 @param arestas Número total de arestas do vértice a ser analizado.
	 @param contador Indicador da recurssão
*/

vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho, int verticeInicial){
	
	Grafo& grafo = *index;
	int x = vertice, y=0;
	//cout << x << endl;
	while (grafo.matriz[x][y] == 0){
		y++;
	}
	caminho.push_back(y);
	grafo.matriz[x][y] = 0;
	grafo.matriz[y][x] = 0;
	if(verticeInicial != y){
		caminho = hierholzer(&grafo, y, caminho, verticeInicial);
	}
	return caminho;
}