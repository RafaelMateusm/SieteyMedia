#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <locale.h>
#include<time.h>
using namespace std;
const int TAM = 10;
typedef int tCartasPorAparecer [TAM];
int menu();
bool juego(int opcion);
float modoA(ifstream &file, int numCartas);
float modoBhumano(ifstream &file, int numCartas);
float modoBmaquina(ifstream &file, int numCartas, float puntosHumano);
int determinaGanador(float puntosHumano, float puntosMaquina);
bool quedanCartas(const tCartasPorAparecer cartas);
float modoChumano(ifstream &file, tCartasPorAparecer cartas);
bool esProbablePasarse(float machineScore,const tCartasPorAparecer cartas);
float modoCmaquina(ifstream &file, tCartasPorAparecer cartas, float puntosHumano);

int main()
{
	int opcion = 0;
	do
	{
		opcion = menu();   //muestra las opciones del juego
		juego(opcion);
	} while (opcion != 4);

	//system("pause");

	return 0;
}

int menu()              // opciones del juego
{
	setlocale(LC_CTYPE, "Spanish");
	int opcion;
	cout << "Bienvenido al juego de las Siete y Media" << endl;
	cout << "Elija una opci�n:" << endl;
	cout << "1 - A" << endl;
	cout << "2 - B" << endl;
	cout << "3 - C" << endl;
	cout << "4 - SALIR" << endl;
	cin >> opcion;
	cout << endl;
	return opcion;
}
bool juego(int opcion)             //funci�n juego
{
	bool archivoAbierto2 = false;
	int numCartas;
	float puntosHumano = 0, puntosMaquina = 0;
	ifstream archivoAbierto;
	string nombremazo;
	tCartasPorAparecer cartas = {4,4,4,4,4,4,4,4,4,4};
	if (opcion == 4)
	{
		return 0;

	}
	while ((archivoAbierto.is_open() == false) && ((opcion == 1) || (opcion == 2) || (opcion ==3)))
	{
		cout << "Introduce el nombre del mazo: ";
		cin >> nombremazo;
		archivoAbierto.open(nombremazo);              // abre el archivo de texto
	}
	if (archivoAbierto.is_open() && ((opcion == 1) || (opcion == 2) || (opcion == 3)))
	{
		// saca un n�mero aleatorio
		archivoAbierto2 = true;
		srand(time(NULL));
		numCartas = rand();
		numCartas = 3 + rand() % (6 - 3);
		cout << "N�mero aleatorio: " << numCartas << endl;
		cout << " " << endl;
		cout << "Player turn!" << endl;
		if (opcion == 1)
		{
			puntosHumano = modoA(archivoAbierto, numCartas);            // llama a la funci�n modoA
			if (puntosHumano > 7.5)
			{
				cout << "Ha ganado la m�quina :(" << endl;
			}
			else
			{
				cout << "Es el turno de la m�quina" << endl;
				puntosMaquina = modoA(archivoAbierto, numCartas);            // llama a la funci�n modoA para el turno de la m�quina
				if (puntosMaquina > 7.5)
				{
					cout << "��ERES EL GANADOR!!" << endl;
				}
				else
				{
					determinaGanador(puntosHumano, puntosMaquina); // llama a la funci�n determinaGanador para poder determinar el ganador
				}
			}
		}
		if (opcion == 2)
		{
			puntosHumano = modoBhumano(archivoAbierto, numCartas);     // llama a la funci�n modoBhumano
			if (puntosHumano > 7.5)
			{
				cout << "Ha ganado la m�quina :( " << endl;
			}
			else
			{
				cout << "Es el turno de la m�quina" << endl;
				puntosMaquina = modoBmaquina(archivoAbierto, numCartas, puntosHumano);   // llama la funci�n modoBm�quina
				if (puntosMaquina > 7.5)
				{
					cout << "��ERES EL GANADOR!!" << endl;
				}
				else
				{
					determinaGanador(puntosHumano, puntosMaquina);        // llama a la funci�n determinaGanador
				}
			}
		}
		if (opcion == 3)
		{
			puntosHumano = modoChumano(archivoAbierto, cartas);
			if (puntosHumano > 7.5)
			{
				cout << "Ha ganado la maquina :(" << endl;
			}
			else
			{
				cout << "Es el turno de la maquina" << endl;
				puntosMaquina = modoCmaquina(archivoAbierto, cartas, puntosHumano);
				if (puntosMaquina > 7.5)
				{
					cout << "ERES EL GANADOR!! :)" << endl;
				}
				else
				{
					determinaGanador(puntosHumano, puntosMaquina);
				}
			}
			for(int i = 0; i < 10; i++){
				cout << "Carta: " << cartas[i];
			}
		}
	}
	cout << endl;
	archivoAbierto.close();
	return archivoAbierto2;
}


/*Permite a cualquiera de los dos jugadores realizar su turno del modo A en una partida.
Recibe el archivo con el mazo y el número de cartas que hay que robar
y devuelvo los puntos obtenidos tras robar ese n�mero de cartas.*/
float modoA(ifstream & archivoAbierto, int numCartas)
{
	int contador = 1;
	double score = 0;
	bool sehapasado = false;
	int carta;
	while ((contador <= numCartas) && (sehapasado == false))
	{
		archivoAbierto >> carta;
		contador += 1;
		if (carta == 10 || carta == 11 || carta == 12)
		{
			score += 0.5;
		}
		else {
			score += carta;
		}
		cout << carta << endl;
		cout << "Puntuaci�n: " << score << endl;
		if (score > 7.5)
		{
			sehapasado = true;
		}
	}
	return score;
}


/*Permite realizar el turno del jugador humano en el modo B.
Recibe el archivo con el mazo y el n�mero m�ximo de cartas que puede robar,
y devuelve los puntos obtenidos.*/
float modoBhumano(ifstream &archivoAbierto, int numCartas)
{
	int contador = 1, carta;
	double score = 0;
	string plantarse;
	bool sehapasado = false, stop = false;
	while ((contador <= numCartas) && (sehapasado == false) && (stop == false))
	{
		archivoAbierto >> carta;
		contador += 1;
		if ((carta == 10) || (carta == 11) || (carta == 12))
		{
			score += 0.5;
		}
		else
		{
			score += carta;
		}
		cout << carta << endl;
		cout << "Puntuaci�n: " << score << endl;
		if (score > 7.5)
		{
			sehapasado = true;
		}
		else
		{
			cout << "Desea plantarse??? " << endl;
			cin >> plantarse;
			if (plantarse == "si")
			{
				stop = true;
			}
		}
	}
	return score;
}


/*Permite realizar el turno del jugador m�quina en el modo B.
Recibe el archivo con el mazo, el n�mero m�ximo de cartas que puede robar
y la puntuación obtenida por el jugador humano,
y devuelve los puntos obtenidos.*/
float modoBmaquina(ifstream &archivoAbierto, int numCartas, float puntosHumano)
{
	int contador = 1;
	int carta;
	double score = 0;
	bool sehapasado = false, stop = false;
	while ((contador <= numCartas) && (sehapasado == false) && (stop == false))
	{
		archivoAbierto >> carta;
		contador += 1;
		if ((carta == 10) || (carta == 11) || (carta == 12))
		{
			score += 0.5;
		}
		else
		{
			score += carta;
		}
		cout << carta << endl;
		cout << "Puntuaci�n: " << score << endl;
		if (score > 7.5)
		{
			sehapasado = true;
		}
		else
		{
			if (score > puntosHumano)
			{
				stop = true;
			}
		}
	}
	return score;
}

/*Recibe los puntos obtenidos por el jugador humano y por la m�quina,
y devuelve un valor que indica qui�n gana.*/
int determinaGanador(float puntosHumano, float puntosMaquina)
{
	int ganador;
	if (puntosHumano > puntosMaquina)
	{
		ganador = 1;
		cout << "��ERES EL GANADOR!!" << endl;
	}
	if (puntosHumano < puntosMaquina) {
		ganador = 2;
		cout << "Ha ganado la m�quina :(" << endl;
	}
	else
	{
		//saca el n�mero aleatorio
		srand(time(NULL));
		ganador = rand();
		ganador = 1 + rand() % (3 - 1);
		if (ganador == 1) {
			cout << "��ERES EL GANADOR!!" << endl;
		}
		else {
			cout << "Ha ganado la m�quina :(" << endl;
		}
	}
	return ganador;
}

//Nos permite saber si quedan cartas en dicha posición del array tCartasPorAparecer cartas

bool quedanCartas(const tCartasPorAparecer cartas)
{
	int total = 0;
	for(int i = 0; i < 10; i++){
		total+=cartas[i];
	}
	if(total > 0){
			return true;
	}else{
		return false;
	}
}


/*Permite realizar el turno del jugador humano en el modo C. Recibe el archivo
con el mazo y una variable cartas que indica cuántas cartas de cada tipo quedan,
y devuelve los puntos obtenidos y actualiza cartas de acuerdo con las cartas
que haya robado el humano. */
float modoChumano(ifstream &archivoAbierto, tCartasPorAparecer cartas)
{
	double puntuacion = 0;
	//typedef enum {uno=1,dos=2,tres=3,cuatro=4,cinco=5,seis=6,siete=7,diez=10,once=11,doce=12} tCartas;
	int micarta;
	int carta;
	bool quedancartas = quedanCartas(cartas);
	bool sehapasado = false;
	bool stop = false;
	string plantarse;
	while((quedancartas == true) && (sehapasado == false) && (stop == false)){
		archivoAbierto >> micarta;
		switch(micarta){

			case 1:
			carta = 0;
			break;

			case 2:
			carta = 1;
			break;

			case 3:
			carta = 2;
			break;

			case 4:
			carta = 3;
			break;

			case 5:
			carta = 4;
			break;

			case 6:
			carta = 5;
			break;

			case 7:
			carta = 6;
			break;

			case 10:
			carta = 7;
			break;

			case 11:
			carta = 8;
			break;

			case 12:
			carta = 9;
			break;
		}
		if((micarta > 7)){
			puntuacion+=0.5;
			cartas[carta]--;
		}else{
				puntuacion+=micarta;
				cartas[carta]--;
		}
		cout << "La carta es: " << micarta << endl;
		cout << "La puntuación es: " << puntuacion << endl;
		if(puntuacion > 7.5){
			sehapasado = true;
		}else{
			if(quedancartas == true){
				cout << "Desea plantarse??? " << endl;
				cin >> plantarse;
				if (plantarse == "si")
				{
					stop = true;
				}
			}
		}
	}
	return puntuacion;
}

/*Determina si la probabilidad que tiene la máquina de pasarse si robara una carta
más es mayor que 0.5. Recibe la puntuación actual de la máquina y una variable cartas
que indica cuántas cartas de cada tipo quedan, y devuelve true si la probabilidad
de pasarse si roba una carta más supera 0.5 y false en caso contrario.*/
bool esProbablePasarse(float machineScore,const tCartasPorAparecer cartas)
{
	int cartasMalas = 0, total = 0;
	double diferencia = (7.5 - machineScore);
	double estimacion = 0;
	bool pasarse = false;
	for(int i = 0; i < 10; i++){
		total+=cartas[i];
		if((i < 7) && (diferencia < (i+1))){
			cartasMalas+=cartas[i];
		}
		if((i >=7) && (diferencia < 0.5)){
			cartasMalas+=cartas[i];
		}
	}
	estimacion = (double) cartasMalas / total;
	cout << estimacion;
	if(estimacion > 0.5){
		pasarse = true;
	}else{
		pasarse = false;
	}
	return pasarse;
}

/*Permite realizar el turno del jugador máquina en el modo C. Recibe el archivo
con el mazo, una variable cartas que indica cuántas cartas de cada tipo quedan
y la puntuación obtenida por el jugador humano, y devuelve los puntos obtenidos y
actualiza cartas de acuerdo con las cartas que haya robado la máquina. */
float modoCmaquina(ifstream &archivoAbierto, tCartasPorAparecer cartas, float puntosHumano)
{
	bool stop = false;
	bool sehapasado2 = false;
	bool quedarcartas = quedanCartas(cartas);
	int micarta;
	double puntuacion = 0;
	int carta;
	while((quedarcartas == true) && (sehapasado2 == false) && (stop == false)){
		archivoAbierto >> micarta;
		switch(micarta){

			case 1:
			carta = 0;
			break;

			case 2:
			carta = 1;
			break;

			case 3:
			carta = 2;
			break;

			case 4:
			carta = 3;
			break;

			case 5:
			carta = 4;
			break;

			case 6:
			carta = 5;
			break;

			case 7:
			carta = 6;
			break;

			case 10:
			carta = 7;
			break;

			case 11:
			carta = 8;
			break;

			case 12:
			carta = 9;
			break;
		}
		if((micarta > 7)){
			puntuacion+=0.5;
			cartas[carta]--;
		}else{
				puntuacion+=micarta;
				cartas[carta]--;
		}
		cout << "La carta es: " << micarta << endl;
		cout << "La puntuación es: " << puntuacion << endl;
		if(puntuacion > 7.5){
			sehapasado2 = true;
		}else{
			if(quedarcartas == true){
				if(((puntuacion == 7.5) || (puntuacion > puntosHumano) || (puntuacion == puntosHumano)) && (esProbablePasarse(puntuacion,cartas))){
					stop = true;
				}
			}
		}
	}
	return puntuacion;
}
