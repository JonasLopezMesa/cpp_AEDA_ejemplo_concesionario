#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int Actual = 0, Total;
const int S = 100;

struct tseg {
	char *modelo; 
	char *numSerie; 
	double precio; 
	char *numContrato; 
	double impContrato;
};

struct tconces {
	char *nombre; 
	char *direccion; 
	char *codigo;
	int max;
	int sact;
	tseg *contrato;
};

void registrarConcesionario(tconces *concesionario);
bool registrarSeguro(tconces *concesionario, int pos);
double recompraCoche(tconces *concesionario, char *numSerie, double precio, int meses);
int buscarConcesionario(tconces *concesionario, char *codigo);
void mostrarConcesionarios(tconces *concesionario);
void menu(tconces *concesionario);
void contar(tconces *concesionario);

int main () {
	tconces *concesionario;
	
	cout << "Antes de empezar, introduzca el número de concesionarios Totales" << endl;
	cin >> Total;
	
	concesionario = new tconces[Total];
	
	
	
	menu(concesionario);
	
}

void registrarConcesionario(tconces *concesionario){
	
  	if(Actual < Total){
		
  		cout << "introduzca el nombre del concesionario, pulsa enter para finalizar." << endl;
		concesionario[Actual].nombre = new char[S];
		cin >> concesionario[Actual].nombre;
		//cin.getline(concesionario[Actual].direccion, S,'\n');
		
		cout << "introduzca la dirección del concesionario, pulsa enter para finalizar." << endl;
		concesionario[Actual].direccion = new char[S];
		cin >> concesionario[Actual].direccion;
		
		cout << "introduzca el código del concesionario" << endl;
		concesionario[Actual].codigo = new char[S];
		cin >> concesionario[Actual].codigo;
		//cin.getline(concesionario[Actual].codigo, S, '\n');
		
		cout << "introduzca el número de seguros como máximo máximos que tendrá este concesionario" << endl;
		cin >> concesionario[Actual].max;
		
		concesionario[Actual].sact = 0;
		concesionario[Actual].contrato = new tseg[concesionario[Actual].max];	// para el vector de contrato, reserva el numero 											
																				//máximo de contratos que se acaban de introducir.
		
		Actual++;
		
	}
	
	else cout << "has pasado el límite de concesionarios" << endl;
	
}


bool registrarSeguro(tconces *concesionario, int pos){
	int a;
	//pos es el lugar donde esta el concesionario, (pos < Actual).
	// antes de entrar a la funcion hay que pedir pos.
	if(pos < Actual)
		if (concesionario[pos].sact < concesionario[pos].max){
			//pedir los datos del seguro.
			//hay que llevar otro contador de huecos libres.
			
			a = concesionario[pos].sact;
			cout << "introduzca el modelo, pulse enter para finalizar." << endl;
			concesionario[pos].contrato[a].modelo = new char[S];
			cin >> concesionario[pos].contrato[a].modelo;
			//cin.getline(concesionario[pos].contrato[a].modelo, S, '\n');
			
			cout << "introduzca el número de serie, pulse enter para finalizar." << endl;
			concesionario[pos].contrato[a].numSerie = new char[S];
			cin >> concesionario[pos].contrato[a].numSerie;
			//cin.getline(concesionario[pos].contrato[a].numSerie, S, '\n');
			
			cout << "introduzca el precio" << endl;
			cin >> concesionario[pos].contrato[a].precio;
			
			cout << "introduzca el número del contrato, pulse enter para finalizar." << endl;
			concesionario[pos].contrato[a].numContrato = new char[S];
			cin >> concesionario[pos].contrato[a].numContrato;
			//cin.getline(concesionario[pos].contrato[a].numContrato, S, '\n');
			
			cout << "introduzca el importe del contrato" << endl;
			cin >> concesionario[pos].contrato[a].impContrato;
			
			
			concesionario[pos].sact++;
			return(true);
		}
  	
		else cout << " te has pasado del total " << endl;
	return(false);
  	
}


double recompraCoche(tconces *concesionario, char *numSerie, double precio, int meses){
	
	int u = 0;
	int aa, bb;
	int a, b;
	double r;
	
	for (a = 0; a < Actual; a++) {
		for (b = 0; b < concesionario[a].sact; b++) {
			if (strcmp(numSerie, concesionario[a].contrato[b].numSerie) == 0) {
				aa = a;
				bb = b;
				a = Actual;
				b = concesionario[a].sact;
				
				if (meses < 6) {
					r = concesionario[aa].contrato[bb].precio;						
				}
				if (meses >= 6 && meses <= 12) {
					r = (concesionario[aa].contrato[bb].precio * 0.85);
				}
				if (meses >= 12 && meses <= 18) {
					r = (concesionario[aa].contrato[bb].precio * 0.60);
				}
				if (meses > 18) {
					r = 0;
				}
				
				u = 1;
			}
		}
	}
	if (u == 0) {
		cout << "No existe el numero de Serie indicado " << endl;
	}
	

	
	return r;
	
}


int buscarConcesionario(tconces *concesionario, char *codigo){
	int pos = -1;
	int i;
	for (i = 0; i < Actual; i++) {
		if (strcmp(concesionario[i].codigo, codigo) == 0) {
			pos = i;
		}
	}
	return(pos);
}


void mostrarConcesionarios(tconces *concesionario){
	int a = 0;
	int b = 0;
	
	cout << "..........CONCESIONARIOS.........." << endl;
	for (a = 0; a < Actual; a++) {
		cout << "Nombre del Conces.			" << concesionario[a].nombre << endl;
		cout << "Dirección del Conces.		" << concesionario[a].direccion << endl;
		cout << "Código del Conces.			" << concesionario[a].codigo << endl;
	}
	cout << "..............SEGUROS............." << endl;
	for (a = 0; a < Actual; a++) {
		cout << "Seguros del concesionario:" << concesionario[a].nombre << endl;
		for (b = 0; b < concesionario[a].sact; b++) {
			cout << "Seguro nº:                 " << b << endl;
			cout << "Modelo                     " << concesionario[a].contrato[b].modelo << endl;
			cout << "Número de Serie            " << concesionario[a].contrato[b].numSerie << endl;
			cout << "Precio	                    " << concesionario[a].contrato[b].precio << endl;
			cout << "Número de Contrato         " << concesionario[a].contrato[b].numContrato << endl;
			cout << "Importe del Contrato       " << concesionario[a].contrato[b].impContrato << endl;
		}
	}
	
	
}

void contar(tconces *concesionario){
	
	int a = 0;
	int cuenta = 0;
	
	for (a = 0; a < Actual; a++) {
			
			
			cuenta = (concesionario[a].sact + cuenta);
			
	}
	
	cout << "El número de seguros es:" << cuenta << endl;
	
}
	

void menu(tconces *concesionario){

	int bus;
	bool h;
	char codigo[S];
	double m;
	char numSerie[S];
	double precio;
	int meses;
	int pos;
	int a = 0;
	int op;
	while(a == 0){
		cout << "MENÚ" << endl;
		cout << "Selecciona la opcion que desees:" << endl;
		cout << "1 ===> Registrar un Concesionario" << endl;
		cout << "2 ===> Registrar un Seguro" << endl;
		cout << "3 ===> Mostrar los Datos de Todos los concesionarios" << endl;
		cout << "4 ===> Calcular el Precio de Recompra" << endl;
		cout << "5 ===> Buscar un Concesionario" << endl;
		cout << "6 ===> Salir" << endl;
		cout << "7 ===> Contar los concesionarios" << endl;
		cin >> op;	
		switch(op){
			case 1: registrarConcesionario(concesionario); 
					break;
			case 2: cout << "primero introduce la posición donde estará el seguro que quieres registrar" << endl;
					cin >> pos;
					h = registrarSeguro(concesionario, pos); 
					if (h == 1) {
						cout << "se pudo registrar con éxito" << endl;
					}
					if (h == 0) {
						cout << "no se pudo registrar con éxito" << endl;
					}
					break;
			case 3: mostrarConcesionarios(concesionario); 
					break;
			case 4: cout << "Introduzca el Número de serie del que quiere calcular el precio de recompra:" << endl;
					cin >> numSerie;
					//cin.getline(numSerie, S, '\n');
					cout << "Introduzca los meses transcurridos desde la compra:" << endl;
					cin >> meses;
					m = recompraCoche(concesionario, numSerie, precio, meses);
					cout << "El precio de Recompra será: " << m << endl;
					break;
				
			case 5: cout << "Introduce el código del concesionario que quieras buscar:" << endl; 
					cin >> codigo;
					bus = buscarConcesionario(concesionario, codigo);
					if (bus == -1) {
						cout << "El concesionario no está registrado" << endl;
					}
					if (bus != -1) {
						cout << "el concesionario se encuentra en la posición: " << bus << endl;
					}
					break;
			case 6: cout << "adios!!!" << endl;
					a = 1;
					break;
			case 7: contar(concesionario);
					break;	
			default: cout << "ERROR vuelva a escribir una opcion correcta" << endl;
				menu(concesionario);
				
		}
	}
	
}

