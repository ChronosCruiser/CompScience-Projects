/** 
   GrafosAPI TP01
   grafosAPI.cpp

   Purpose: Criar um grafo a partir da leitura de uma arquivo e ser capaz de executar funções basicas como calcular o grau de um vértice, total de arestas
   e ser capaz de realizar a execução do algorítimo de Hierholzer no grafo criado.

   @author Gustavo Dutra, Reginaldo Filho, Tiago Fonseca.
   @version 1.0 02/25/17

 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matriz;
typedef vector<int> Coluna;

struct Grafo{
	Matriz matriz;
	int vertices = 0;
	int verticeInicial = 0;
};

Grafo getGrafo(Grafo grafo);
Grafo getDigrafo(Grafo grafo);
int calculaGrau(Grafo grafo);
int calculaGrau(Grafo grafo, int verticeAC);
void arestaExiste(Grafo grafo);
int totalArestas(Grafo grafo);
void hierholzer(Grafo grafo);
vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho, int arestas, int contador);


/** 
 */

int main(int argc, char** argv) {

    string linha;
	Grafo grafo;
	
	getline(cin, linha);
	cout << linha << endl;
	if (linha.find("0") != -1){
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
	try {
		getline(cin, linha);
		grafo.vertices = stoi(linha);
		getline(cin, linha);
		grafo.verticeInicial = stoi(linha);
		//int grafo[grafo.vertices][grafo.vertices] = {};	
	
		for(int x = 0; x < grafo.vertices; x++){
			Coluna coluna(grafo.vertices, 0);
			grafo.matriz.push_back(coluna);
		}
	
		getline(cin, linha);
		while(linha.compare(fim) != 0){
			cout << linha << endl;
			int origem = 0;
			int destino = 0;
			int peso = 0;
			origem = stoi(linha);
			destino = stoi(linha.substr(2));
			peso = stoi(linha.substr(4));
			//cout << origem << " " << destino << " " << peso << endl;
			grafo.matriz[origem][destino] = peso;
			grafo.matriz[destino][origem] = peso;
			fim = linha;
			getline(cin, linha);
		}
	
		for (int x = 0; x < grafo.vertices; x++){
			for (int y = 0; y < grafo.vertices; y++){
				cout << grafo.matriz[x][y];
			}
			cout << endl;
		}
	} catch(const std::invalid_argument& e){
		cout << "Invalid answer : " << linha << endl;
	}
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
	//int grafo[grafo.vertices][grafo.vertices] = {};	
	try {
		grafo.vertices = stoi(linha);
		for(int x = 0; x < grafo.vertices; x++){
			Coluna coluna(grafo.vertices, 0);
			grafo.matriz.push_back(coluna);
		}
	
		getline(cin, linha);
		while(linha.compare(fim) != 0){
			cout << linha << endl;
			int origem = 0;
			int destino = 0;
			int peso = 0;
			origem = stoi(linha);
			destino = stoi(linha.substr(2));
			peso = stoi(linha.substr(4));
			//cout << origem << " " << destino << " " << peso << endl;
			grafo.matriz[origem][destino] = peso;
			linha=fim;
			getline(cin, linha);
		}
	
		for (int x = 0; x < grafo.vertices; x++){
			for (int y = 0; y < grafo.vertices; y++){
				cout << grafo.matriz[x][y];
			}
			cout << endl;
		}
	} catch(const std::invalid_argument& e){
		cout << "Invalid answer : " << linha << endl;
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
	int grafoComplementar[grafo.vertices][grafo.vertices] = {};
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

/**
	Executa o algorítimo de Hierholzer em um grafo, em busca de um caminho euleriano. OBS: O vértice inicial é sempre o de menor 
	índice numérico.
	@param grafo Grafo onde o algorítimo irá contruir o caminho euleriano.
	
*/

void hierholzer(Grafo grafo){
	string resposta;
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
			contador++;
			caminho.push_back(y);
			grafo.matriz[x][y] = 0;
			grafo.matriz[y][x] = 0;
			caminho = hierholzer(&grafo, y, caminho, arestas, contador);
			vector<int>::iterator it = caminho.begin();
			do{
				string str = to_string(*it);
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
		contador++;
		caminho.push_back(y);
		grafo.matriz[x][y] = 0;
		grafo.matriz[y][x] = 0;
		caminho = hierholzer(&grafo, y, caminho, arestas, contador);
		vector<int>::iterator it = caminho.begin();
		do{
			string str = to_string(*it);
			resposta = resposta + "-" + str;
			it++;
		} while (it != caminho.end());
		
		resposta = resposta.substr(1, resposta.length());
		printf("%s \n", resposta.c_str());
	}
	
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafo.matriz[x][y];
		}
		cout << endl;
	}
}

/**
	 Vetor que representa e armazena o caminho euleriano encontrado em um grafo.
	 @param index Passagem de um grafo por endereço.
	 @param vertice Vértice onde a execução do void hierholzer se encontra.
	 @param caminho Caminho que está sendo construido por void hierfholzer.
	 @param arestas Número total de arestas do vértice a ser analizado.
	 @param contador Indicador da recurssão
*/

vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho, int arestas, int contador){
	
	Grafo& grafo = *index;
	int x = vertice, y=0;
	while (grafo.matriz[x][y] == 0){
		y++;
	}
	contador++;
	caminho.push_back(y);
	cout << y << endl;
	grafo.matriz[x][y] = 0;
	grafo.matriz[y][x] = 0;
	if(contador < arestas){
		caminho = hierholzer(&grafo, y, caminho, arestas, contador);
	}
	return caminho;
}
