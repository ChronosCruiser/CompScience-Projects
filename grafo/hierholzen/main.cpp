/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Gustavo Dutra
 *
 * Created on 25 de Fevereiro de 2017, 18:16
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
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

fstream arquivo;
/*
* local test
*/

string fullpath = "home//tornado//Documents//Grafos TP01//usb.in";
/**/
Grafo getGrafo(Grafo grafo);
Grafo getDigrafo(Grafo grafo);
int calculaGrau(Grafo grafo);
void arestaExiste(Grafo grafo);
void totalArestas(Grafo grafo);
void hierholzer(Grafo grafo);
vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho);
/*
 * 
 */
int main(int argc, char** argv) {
	
    string linha;
	Grafo grafo;
	//cout << "Digite o nome do arquivo:";
	//getline(cin, name);
	cout << fullpath << endl;
	arquivo.open("C:\\0.txt");
	if ( !arquivo.is_open()) {                 
      	cout <<" Failed to open" << endl;
   	}
   	else {
      cout <<"Opened OK" << endl;
   	}
	
	getline(arquivo, linha);
	cout << linha << endl;
	if (linha.find("0") != -1){
		grafo = getGrafo(grafo);
	}else{
		grafo = getDigrafo(grafo);
	}
	hierholzer(grafo);
	//calculaGrau(grafo, grafo.vertices);
	//arestaExiste(grafo, grafo.vertices);
	//totalArestas(grafo);
    arquivo.close();
	return 0;
}

Grafo getGrafo(Grafo grafo){
	
	string linha;
	try {
		getline(arquivo, linha);
		grafo.vertices = stoi(linha);
		getline(arquivo, linha);
		grafo.verticeInicial = stoi(linha);
		//int grafo[grafo.vertices][grafo.vertices] = {};	
	
		for(int x = 0; x < grafo.vertices; x++){
			Coluna coluna(grafo.vertices, 0);
			grafo.matriz.push_back(coluna);
		}
	
		while(arquivo.eof() == false){
			getline(arquivo, linha);
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

Grafo getDigrafo(Grafo grafo){
    string linha;
	getline(arquivo, linha);
	//int grafo[grafo.vertices][grafo.vertices] = {};	
	try {
		grafo.vertices = stoi(linha);
		for(int x = 0; x < grafo.vertices; x++){
			Coluna coluna(grafo.vertices, 0);
			grafo.matriz.push_back(coluna);
		}
	
		while(arquivo.eof() == false){
			getline(arquivo, linha);
			cout << linha << endl;
			int origem = 0;
			int destino = 0;
			int peso = 0;
			origem = stoi(linha);
			destino = stoi(linha.substr(2));
			peso = stoi(linha.substr(4));
			//cout << origem << " " << destino << " " << peso << endl;
			grafo.matriz[origem][destino] = peso;
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

int calculaGrau(Grafo grafo, int verticeAC){
	int escolhido = verticeAC;
	int grau = 0;
	//cout << "Digite o nodo a ter o grau calculado:";
	//cin >> escolhido;
	if (-1 < escolhido < grafo.vertices){
		for (int x = 0; x < grafo.vertices; x++){
			if (grafo.matriz[x][escolhido] > 0){
				grau++;
			}
		}
	}
	return grau;
}

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

void totalArestas(Grafo grafo){
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
	cout << "Matriz grafoComplementar: " << endl; 
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafoComplementar[x][y];
		}
		cout << endl;
	}
	cout << "Numero de arestas total: " << aresta << endl;
	cout << "Grafo completo =" << completo << endl;
}

void hierholzer(Grafo grafo){
	bool impar = false;
	
	vector<int> caminho;
	for (int x = 0; x < grafo.vertices; x++){
		if (calculaGrau(grafo, x)%2 == 1){
			impar = true;
		}
	}
	if (impar == true){
		cout << "grafo não euleriano!" << endl;
	}else{
		caminho.push_back(grafo.verticeInicial);
		int x = grafo.verticeInicial, y=0;
		while (grafo.matriz[x][y] == 0){
			y++;
		}
		caminho.push_back(y);
		grafo.matriz[x][y] = 0;
		grafo.matriz[y][x] = 0;
		
		caminho = hierholzer(&grafo, y, caminho);
		
		vector<int>::iterator it = caminho.begin();
		do{
			cout << "-" << *it;
			it++;
		}while (it != caminho.end());
		cout << endl;
	}
	
	for (int x = 0; x < grafo.vertices; x++){
		for (int y = 0; y < grafo.vertices; y++){
			cout << grafo.matriz[x][y];
		}
		cout << endl;
	}
}

vector<int> hierholzer(Grafo* index, int vertice, vector<int> caminho){
	
	Grafo& grafo = *index;
	int x = vertice, y=0;
	while (grafo.matriz[x][y] == 0){
		y++;
	}
	caminho.push_back(y);
	grafo.matriz[x][y] = 0;
	grafo.matriz[y][x] = 0;
	if(y != grafo.verticeInicial){
		caminho = hierholzer(&grafo, y, caminho);
	}
	return caminho;
}