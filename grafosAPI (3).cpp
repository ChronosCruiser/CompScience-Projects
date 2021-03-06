/** 
   GrafosAPI TP01
   grafosAPI.cpp

   Purpose: Criar um grafo a partir da leitura de uma arquivo e ser capaz de executar funções basicas 
   como calcular o grau de um vértice, total de arestas
   e ser capaz de realizar a execução do algorítimo de Hierholzer no grafo criado.

   @authors Gustavo Dutra, Reginaldo Filho, Tiago Fonseca.
   @version 1.3.276 02/25/17

 */
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include <limits.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <iterator>
#include <map>

using namespace std;

#define INFINITO -1

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

struct Aresta{
	int comeco;
	int fim;
	int peso;
};

bool ordenador (Aresta a,Aresta b) { return (a.peso < b.peso); }

struct Grafo{
	Matriz matriz;
	int vertices;
	vector<int> listaPeso;
};

Grafo getGrafo(Grafo grafo);
Grafo getDigrafo(Grafo grafo);
int calculaGrau(Grafo grafo);
int calculaGrau(Grafo grafo, int verticeAC);
void arestaExiste(Grafo grafo);
int totalArestas(Grafo grafo);
int grafoVazio(Grafo* grafo, int verticeInicial);
//void hierholzer(Grafo grafo, int verticeInicial);
//vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho, int verticeInicial);
Grafo primAGM(Grafo grafo, int verticeInicial=0);
//void dijkstraReverso(Grafo agm, int verticeInicial);
int minDistance(int dist[], bool sptSet[], int V);
void printPath(int parent[], int j);
int printSolution(int dist[], int V, int parent[], int src);
void dijkstra(Grafo agm, int src);

/** 
 */

int main(int argc, char** argv) {
    string linha;
    int isGrafo;
    int verticeInicial;
	Grafo grafo;
	grafo.vertices = 0;
	getline(cin, linha);
	std::istringstream(linha) >> isGrafo;
	if (isGrafo == 0){
		getline(cin, linha);
		std::istringstream(linha) >> grafo.vertices;
		getline(cin, linha);
		std::istringstream(linha) >> verticeInicial;
		grafo = getGrafo(grafo);
	}else{
		getline(cin, linha);
		std::istringstream(linha) >> grafo.vertices;
		getline(cin, linha);
		std::istringstream(linha) >> verticeInicial;
		grafo = getDigrafo(grafo);
	}
	//hierholzer(grafo, verticeInicial);
	//calculaGrau(grafo);
	//arestaExiste(grafo, grafo.vertices);
	//totalArestas(grafo);
	Grafo agm;
	agm = primAGM(grafo);
	dijkstra(agm, verticeInicial);
	return 0;
}

/**
	Retorna um grafo preenchido após realizar a leitura de arquivo.
	@param grafo Grafo vazio a ser preenchido pelo método.
	@return Grafo preenchido após a leitura do arquivo.
*/

Grafo getGrafo(Grafo grafo){
 	string linha, fim;
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
		grafo.listaPeso.push_back(peso);
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
	sort(grafo.listaPeso.begin(), grafo.listaPeso.end());
	return grafo;
}

/**
	Retorna um digrafo preenchido após realizar a leitura de arquivo.
	@param grafo Digrafo vazio a ser preenchido pelo método.
	@return Digrafo preenchido após a leitura do arquivo.
*/

Grafo getDigrafo(Grafo grafo){

	string linha, fim; 	
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

int grafoVazio(Grafo* index, int verticeInicial){
	int resp;
	Grafo& grafo = *index;
	for (int i = 0; i < grafo.vertices; i++){
		for(int j = 0; j < grafo.vertices; j++){
			if(grafo.matriz[i][j] == 1){
				verticeInicial = i;
				return 1;
			} else resp = 0;
		}
	}
	return resp;
}

/**
	Executa o algorítimo de Hierholzer em um grafo, em busca de um caminho euleriano. OBS: O vértice inicial é sempre o de menor 
	índice numérico.
	@param grafo Grafo onde o algorítimo irá contruir o caminho euleriano.
	


void hierholzer(Grafo grafo, int verticeInicial){
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
		caminho = hierholzer(&grafo, y, caminho, verticeInicial);
		//cout << "end 1 " << endl;
		while (grafoVazio(&grafo) != 0) {
			cout << verticeInicial << endl;
			vector<int>::iterator pos = caminho.begin();
			while(*pos != verticeInicial){
				pos++;
			}
			circuito.push_back(verticeInicial);
			int xcircuito = verticeInicial, ycircuito=0;
			while (grafo.matriz[xcircuito][ycircuito] == 0){
				ycircuito++;
			}
			circuito.push_back(ycircuito);
			grafo.matriz[xcircuito][ycircuito] = 0;
			grafo.matriz[ycircuito][xcircuito] = 0;
			circuito = hierholzer(&grafo, ycircuito, circuito, verticeInicial);
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
		caminho.push_back(verticeInicial);
		int x = verticeInicial, y=0;
		while (grafo.matriz[x][y] == 0){
			y++;
		}
		caminho.push_back(y);
		grafo.matriz[x][y] = 0;
		grafo.matriz[y][x] = 0;
		caminho = hierholzer(&grafo, y, caminho, verticeInicial);
		//cout << "end 1 " << endl;
		while (grafoVazio(&grafo) != 0) {
			//cout << grafo.verticeInicial << endl;
			vector<int>::iterator pos = caminho.begin();
			while(*pos != verticeInicial){
				pos++;
			}
			circuito.push_back(verticeInicial);
			int xcircuito = verticeInicial, ycircuito=0;
			while (grafo.matriz[xcircuito][ycircuito] == 0){
				ycircuito++;
			}
			circuito.push_back(ycircuito);
			grafo.matriz[xcircuito][ycircuito] = 0;
			grafo.matriz[ycircuito][xcircuito] = 0;
			circuito = hierholzer(&grafo, ycircuito, circuito, verticeInicial);
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

/**
	 Vetor que representa e armazena o caminho euleriano encontrado em um grafo.
	 @param index Passagem de um grafo por endereço.
	 @param vertice Vértice onde a execução do void hierholzer se encontra.
	 @param caminho Caminho que está sendo construido por void hierfholzer.
	 @param arestas Número total de arestas do vértice a ser analizado.
	 @param contador Indicador da recurssão


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
/*
void kruskal (Grafo grafo){
	bool flag1, flag2, flag3;
	Grafo agm;
	Aresta tmp;
	vector<vector<int>> floresta;
	vector<Aresta> lista;
	for( int i = 0; i < grafo.vertices; i++){
		for( int j = i+1; j < grafo.vertices; j++){
			if( grafo.matriz[i][j] != 0){
				tmp.comeco = i;
				tmp.fim = j;
				tmp.peso = grafo.matriz[i][j];
				lista.push_back(tmp);
			}
		}
	}
	sort(lista.begin(), lista.end(), ordenador);
	floresta.push_back(lista[0].comeco);
	floresta[0].push_back(lista[0].fim);
	lista.erase(lista.begin());
	while(!lista.empty()){
		//primeiro caso se nao existirem vertices na arvore criar uma nova arvore
		//segundo caso se existir um vertice mas o outro nao está ainda na arvore
		//quando um vertice esta em uma arvore e o outro esta em outra
		//
		vector<int>::iterator it = floresta.begin();
		do {
			int vertice = *it;
			if(vertice != lista[0].comeco && vertice != lista[0].fim){
				flag1=true;
				flag2=false;
				flag3=false;
			}
			it++;
		} while (it != floresta.end());
	}
}*/

Grafo primAGM(Grafo grafo, int verticeInicial){
	Grafo agm;
	vector<int> arvore;
	int maiorAresta = 0;
	Aresta tmp;
	//gerar matriz 0
	agm.vertices = grafo.vertices;
	//cout << agm.vertices << endl;
	for(int x = 0; x < agm.vertices; x++){
		Coluna coluna(agm.vertices, 0);
		agm.matriz.push_back(coluna);
	}
	
	bool flag1;
	vector<Aresta> lista;
	for( int i = 0; i < grafo.vertices; i++){
		if( grafo.matriz[verticeInicial][i] != 0){
			tmp.comeco = verticeInicial;
			tmp.fim = i;
			tmp.peso = grafo.matriz[i][verticeInicial];
			
			lista.push_back(tmp);
		}
	}
	sort(lista.begin(), lista.end(), ordenador);
	arvore.push_back(verticeInicial);
	
	while(arvore.size() != agm.vertices){
		flag1 = false;
		vector<int>::iterator it = arvore.begin();
		do {
			int vertice = *it;

			if(vertice == lista[0].fim){
				flag1=true;
			}
			it++;
		} while((it != arvore.end()));
		
		if(flag1 == false){
			arvore.push_back(lista[0].fim);
			agm.matriz[lista[0].comeco][lista[0].fim] = lista[0].peso;
			agm.matriz[lista[0].fim][lista[0].comeco]= lista[0].peso;

			if(lista[0].peso > maiorAresta){
				maiorAresta = lista[0].peso;
			}

			for( int i = 0; i < agm.vertices; i++){
				if( grafo.matriz[lista[0].fim][i] != 0){
					tmp.comeco = lista[0].fim;
					tmp.fim = i;
					tmp.peso = grafo.matriz[i][lista[0].fim];
					lista.push_back(tmp);
				}
			}
		}
		lista.erase(lista.begin());
		sort(lista.begin(), lista.end(), ordenador);

	}
	cout << maiorAresta << endl;
	return agm;
}
/*
void dijkstraReverso(Grafo agm, int verticeInicial){
	int maior= 0;
	int proximo;
	map<int, int> distancias;
	map<int, vector<int>> caminhos;
	vector<int> visitados;
	visitados.push_back(verticeInicial);
	distancias.insert(pair<int,int>(verticeInicial, 0));
	caminhos.insert(pair<int,vector<int>>(verticeInicial, {verticeInicial}));
	
	for(int i = 0; i < agm.vertices; i++){
		if(agm.matriz[i][verticeInicial] != 0){
			if( (agm.matriz[i][verticeInicial] > maior) || (maior == 0) ){
				maior = agm.matriz[i][verticeInicial];
				proximo = i;
			}
			distancias.insert(pair<int,int>(i,agm.matriz[i][verticeInicial]));
			caminhos.insert(pair<int,vector<int>>(i, {verticeInicial,i}));
		}
	}
	visitados.push_back(proximo);
	for(int i = 0; i < agm.vertices; i++){
		if(distancias[proximo]+agm.matriz[i][proximo] > distancias[i]){
			distancias.erase(i);
			distancias.insert(pair<int,int>(i,distancias[proximo]+agm.matriz][proximo]));
		}
	}
}
*/

int minDistance(int dist[], bool sptSet[], int V)
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}

// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j]==-1)
        return;
 
    printPath(parent, parent[j]);
 
    printf("-%d", j);
}
 
// A utility function to print the constructed distance
// array
int printSolution(int dist[], int V, int parent[], int src)
{
    int maior = 0;
    int chave;
    for (int i = 1; i < V; i++)
    {
    	if(dist[i] > maior){
    		maior = dist[i];
    		chave = i;
    	}
    }
    printf("%d", src);
    printPath(parent, chave);
    cout << endl;
    printf("%d\n", maior);
}
  
// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(Grafo agm, int src)
{
    int dist[agm.vertices];  // The output array. dist[i] will hold
                  // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[agm.vertices];
 
    // Parent array to store shortest path tree
    int parent[agm.vertices];
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < agm.vertices; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < agm.vertices-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet, agm.vertices);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < agm.vertices; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && agm.matriz[u][v] &&
                dist[u] + agm.matriz[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + agm.matriz[u][v];
            }
    }
 
    // print the constructed distance array
    printSolution(dist, agm.vertices, parent, src);
}