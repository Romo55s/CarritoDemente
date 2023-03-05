/* Proyecto laberinto el carrito demente
	Integrantes: Jose Antonio, Andrea Candelario, Angel Ramirez, Luis Humberto 
*/

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

using namespace std;

/*
LEFT = 0x25
RIGTH = 0x27
UP = 0x28
DOWN = 0x26
*/

const char pared = '#';
const char espacio = ' ';
const int mapaAlto1 = 14;
const int mapaAncho1 = 30;
const int mapaAlto2 = 17;
const int mapaAncho2 = 27;
const int mapaAlto3 = 24;
const int mapaAncho3 = 34;

void menu(char);
void OcultaCursorChafa();
void mostrarMapa1();
void mostrarMapa2();
void mostrarMapa3();
int movCarritoChafa(char,int,int,int,int);
int movCarritoChafa2(char,int,int,int,int);
int movCarritoChafa3(char,int,int,int,int);
void gotoxy(int, int);
void TimerC ();
void registro();
bool checarMap1(int,int,int,int);
bool checarMap2(int,int,int,int);
bool checarMap3(int,int,int,int);
bool AjustarVentana(int Ancho, int Alto);
void registro(char);
void Color(int Background, int Text);
void portada();
void tablaPunt(char tablaN[][10],char tablaP[][10]);
void mostrarTabla(char tablaN[][10],char tablaP[][10]);
void llenarTabla(char tablaN[][10],char tablaP[][10]);

int contP= -1; // para que el primer usuario sea 0
char opcion;
int puntos=0;
// 41, 13
char nombre[10];
char tablaN[10][10];
char tablaP[2][10];
char mapa1[mapaAlto1][mapaAncho1 + 1] =
{
    "######################## #####",
	"############  #      ### #####",
	"###########  ####### ###    ##",
	"#        ## ##    ## ###### ##",
	"# # # ## ##    ## ## #      ##",
	"### # ##  # ### # #    #### ##",
    "#   #  #    ### # # ####### ##",
    "### ###########         ######",
    "#   #### ##############     ##",
    "# # ###  ###     ########## ##",
    "### ### #### ########     # ##",
    "    ###         # ### ### # ##",
    "###     #######       ###   ##",
    "##############################",
};

char mapa2[mapaAlto2][mapaAncho2 + 1] =
{
	"######################### #",
	"#       #  ###          # #",
	"## ######      ######## # #",
	"##    ### #####         # #",
	"## ## ### ## ## ######### #",
	"## ##        #          # #",
    "## ###### ## # ###### ##  #",
    "##        ## # ##     #  ##",
    "####  ###  #    # #####   #",
    "#### ############    ## # #",
    "#       #####        ## ###",
    "## ########## #########   #",
    "#    #  # #    #     #### #",
    "#         #            ## #",
    "######### ############ ## #",
    "#                #        #",
    "# #########################",
};

char mapa3[mapaAlto3][mapaAncho3 + 1] =
{
"############################## ###",
"#               #      #     #   #",
"### ######    ###     #  ### ### #",
"#        # ##   ####### #  # #   #",
"# ######## #### ####### #  # #  ##",
"#      #   #  # #       # #  ##  #",
"###### #   #  ### ########  ##  ##",
"#      #   ## # #     ###  ##  ###",
"# #######     # ##### # #  #  ####",
"# ######## #### #     # #        #",
"#        #  ##  # ##### # ########",
"######## ## #  #      # #   #    #",
"#      # #  # ####### # #   #    #",
"# #####  # #        # # #   #### #",
"#     # ##  # ## #  # ## #  #    #",
"### # #   # #  # ## #  # ####    #",
"### # ### # ## # ##  # #     #####",
"# # # #   # ## #   # # #     #   #",
"# # # # ###  # # ##  # #######   #",
"#   # #   # ## # ## ## #         #",
"  ##  ### # #  # ## ## #  ####   #",
"# ##      #   #   #    #     #   #",
"##################################",
};

// Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
enum Colors { 
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LGREY = 7,
	DGREY = 8,
	LBLUE = 9,
	LGREEN = 10,
	LCYAN = 11,
	LRED = 12,
	LMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

int main()
{
	AjustarVentana(100,23);  // Para pantalla de resolución 
	char carritoCh = '*';
	portada();
	registro(carritoCh);
	return 0;
}

//funcion para el registro
void registro(char carritoCh)
{
	int opc=0;
	int a=0;
	char b;
	do
	{
		tablaPunt(tablaN,tablaP);
		system("cls");
		Color(BLACK, WHITE);
		gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#REGISTRO#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
		gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
		gotoxy(41,5);printf("Su nombre: ");
		scanf("%s",nombre);
		gotoxy(41,6);printf("Continuar ... 4");
		gotoxy(41,7);printf("Salir ....... 0");
		gotoxy(41,8);printf("Introdusca una opcion: ");
		scanf("%d",&opc);
		contP ++;
		puntos=0;
		switch(opc)
		{
			case 4:menu(carritoCh);break;
			default: gotoxy(40,10);printf("Coloque una opcion valida!\n");break;
		}
		system("pause");
	}while(opc != 0);
}

void menu(char carritoCh)
{
	int resp;
	int xO= 11;
	int yO= 11;
	int pO= 13;
	int lO= 12;
	do
	{
		system("cls");
		gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#MENU#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
		gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
		gotoxy(38,5);printf("-level 1 .................. 1");
		gotoxy(38,6);printf("-level 2 .................. 2");
		gotoxy(38,7);printf("-level 3 .................. 3");
		gotoxy(38,8);printf("-Listado de Puntuacion .... 4");
		gotoxy(38,9);printf("-Agregar otro usuario ..... 5");
		gotoxy(38,10);printf("-Salir .................... 6");
		gotoxy(38,11);printf("Que nivel escoges? ");
		scanf("%d",&resp);
		Sleep(500);
		system("cls");
		switch(resp)
		{
			case 1:
			mostrarMapa1();
			puntos = movCarritoChafa(carritoCh,xO,yO,pO,lO);
			break;
			
			case 2:
			mostrarMapa2();
			puntos = movCarritoChafa2(carritoCh,xO,yO,pO,lO);
			break;
			
			case 3:
			mostrarMapa3();
			puntos = movCarritoChafa3(carritoCh,xO,yO,pO,lO);
			break;
			
			case 4:
			tablaPunt(tablaN,tablaP);
			break;
			
			case 5:
			registro(carritoCh);
			break;
			
			case 6: break;
		}
		
	}while(resp != 6);
}

//funcion para imprimir el mapa1
void mostrarMapa1()
{
    for (int Y = 0; Y < mapaAlto1; Y++)
	{
    	/*gotoxy(40,Y+5);*/printf("%s\n", mapa1[Y]);
    	Sleep(100);
    }
    printf("\n");
}

//funcion para imprimir el mapa2
void mostrarMapa2()
{
	for (int Y = 0; Y < mapaAlto2; Y++)
	{
    	printf("%s\n", mapa2[Y]);
    	Sleep(100);
    }
    printf("\n");
}

//funcion para imprimir el mapa2
void mostrarMapa3()
{
	for (int Y = 0; Y < mapaAlto3; Y++)
	{
    	printf("%s\n", mapa3[Y]);
    	Sleep(100);
    }
    printf("\n");
}

// funcion echa de varias funciones para que el laberinto funcione correctamente en el mapa 1
int movCarritoChafa(char carritoCh,int xO,int yO, int pO, int lO)
{
	int x=1, y=11;
	int finalX=24;
	int finalY=0;
	int m=0;
	int m2=0;
	char vida1= '^';
	char vida2= '^';
	int matRand[30][27];
	int contador=0;
	int contVid=2;
	int contPunt=0;
	int contObs=0;
	Color(BLACK, WHITE);
	Color(BLACK, CYAN);
	gotoxy(x,y); printf("%c",carritoCh);
	Color(BLACK, WHITE);
	gotoxy(50,1);printf("%c %c",vida1,vida2);
	gotoxy(60,1);printf("Puntuacion: %d",puntos);
	gotoxy(38,0);printf("Timer");
	gotoxy(38,3);printf("Tu tiempo limite es 1:00:00");
	while(carritoCh != '@')
	{
		for(int s=0; s <= 90; s++) // es el for es para el cronometro
		{
			Color(BLACK, WHITE);
			gotoxy(60,0);printf("Obstaculos vencidos: %d",contObs);
			gotoxy(47,0);printf("Vidas: %d",contVid);
			//vidas(carritoCh,x,y,xO,yO,pO,lO);
			gotoxy(38,1);printf("%d:%d:%d",m2,m,s);
			Sleep(16);// velocidad del timer y carrito
			if(s == 60)
			{
				m++;
				s=0;
			}
			if(m == 60)
			{
				m2++;
				m=0;
			}
			if(m2 == 1 && m == 0)
			{
				Color(BLACK, WHITE);
				gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GAME OVER#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
				gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
				system("cls");
				gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
				gotoxy(38,6);printf("- Tus puntos ganados fueron: %d",contPunt);
				gotoxy(38,7);printf("- El tiempo que hiciste: %d:%d:%d",m2,m,s);
				gotoxy(38,8);printf("- Se te acabo el tiempo campeon!\n");
				gotoxy(38,9);system("pause");
				menu(carritoCh);
			}
			//opcion=getch();
			if(GetAsyncKeyState(0x25) && mapa1[y][x-1] == espacio)
			{
					gotoxy(x,y);printf(" ");
					x--;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x27) && mapa1[y][x+1] == espacio)
			{
					gotoxy(x,y);printf(" ");
					x++;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x28) && mapa1[y+1][x] == espacio)
			{
					gotoxy(x,y);printf(" ");
					y++;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x26) && mapa1[y-1][x] == espacio)
			{
					gotoxy(x,y);printf(" ");
					y--;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(x == finalX && y == finalY) // condicion para que se acabe el nivel del laberinto
			{
				if(m <= 30) // condicion para validar en cuanto tiempo termino el laberinto
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 350;
					gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("- Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("- El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,9);system("pause");
					menu(carritoCh);
				}
				if(m > 30 && m <= 60)
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 150;
					gotoxy(38,5);printf("Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
				if(m2 == 1 && m <= 30)
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 50;
					gotoxy(38,5);printf("Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
			}
			for(int r1=0; r1 < 30; r1++)
			{
				if(x == matRand[0][r1] && y == matRand[1][r1] && vida1 != ' ')
				{
					gotoxy(50,1);printf(" ");
					vida1 = ' ';
					matRand[0][r1] = 500;
					matRand[1][r1] = 400;
					contVid--;
					contObs++;
				}
			
			
				else if(vida1 == ' ' && x == matRand[0][r1] && y == matRand[1][r1])
				{
					gotoxy(51,1);printf("  ");
					vida2 = ' ';
					matRand[0][r1] = 500; // Esto sirve para que no corra el riesgo de que se repita la coordenada (Aqui corremos el riesgo de que se vuelva a repetir la coordenada y que no funcione correctamente)
					matRand[1][r1] = 400;
					contVid--;
					contObs++;
					
					if(m <= 30 || m > 30 || m2 == 1) // condicion para decirle en cuanto tiempo perdio
					{
						Color(BLACK, WHITE);
						system("cls");
						gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GAME OVER#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
						gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
						gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
						gotoxy(38,6);printf("- El tiempo que hiciste: %d:%d:%d",m2,m,s);
						gotoxy(38,7);printf("- Perdiste todas tus vidas\n");
						gotoxy(38,8);system("pause");
						menu(carritoCh);
					}
				}
			
				/*else if(vida2 == ' ' &&  x == matRand[0][r1] && y == matRand[1][r1])
				{
					gotoxy(52,1);printf(" ");
					gotoxy(52,1);printf("FF");
				}*/	
			
				if(x == xO && y == yO || x == pO || y == lO) // condicion para generar numeros random
				{	
				
					bool validar= false;
					while(validar != true)
					{
						xO = (rand() % 28)+ 0;
						yO = (rand() % 13)+ 0;
						pO = (rand() % 30)+ 0; // x
						lO = (rand() % 14)+ 0; // y
						validar = checarMap1(xO,yO,pO,lO);
					}
					Color(BLACK, RED);
					matRand[0][contador] = xO; // guardamos la posicion dentro de la matriz y despues se lo pasamos a las coordenadas de xO
					matRand[1][contador] = yO; // guardamos la posicion dentro de la matriz y despues se lo pasamos a las coordenadas de yO
					gotoxy(xO,yO);printf("@");
					contador++; // este contador sirve para indicarle el renglon a la matriz, para posteriormente cambiarlo por las coordenadas xO y yO
				}
			}
		}
	}	getch();
}

/// funcion echa de varias funciones para que el laberinto funcione correctamente en el mapa 2
int movCarritoChafa2(char carritoCh,int xO,int yO, int pO, int lO)
{
	int x=1, y=17;
	int finalX=25;
	int finalY=0;
	int m=0;
	int m2=0;
	char vida1= '^';
	char vida2= '^';
	int matRand[30][27];
	int contador=0;
	int contVid=2;
	int contPunt=0;
	int contObs=0;
	Color(BLACK, WHITE);
	Color(BLACK, CYAN);
	gotoxy(x,y); printf("%c",carritoCh);
	Color(BLACK, WHITE);
	gotoxy(50,1);printf("%c %c",vida1,vida2);
	gotoxy(60,1);printf("Puntuacion: %d",puntos);
	gotoxy(38,0);printf("Timer");
	gotoxy(38,3);printf("Tu tiempo limite es 1:15:00");
	while(carritoCh != '@')
	{
		for(int s=0; s <= 90; s++) // es el for es para el cronometro
		{
			Color(BLACK, WHITE);
			gotoxy(60,0);printf("Obstaculos vencidos: %d",contObs);
			gotoxy(47,0);printf("Vidas: %d",contVid);
			//vidas(carritoCh,x,y,xO,yO,pO,lO);
			gotoxy(38,1);printf("%d:%d:%d",m2,m,s);
			Sleep(16);// velocidad del timer y carrito
			if(s == 60)
			{
				m++;
				s=0;
			}
			if(m == 60)
			{
				m2++;
				m=0;
			}
			if(m2 == 1 && m == 15)
			{
				Color(BLACK, WHITE);
				gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GAME OVER#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
				gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
				system("cls");
				gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
				gotoxy(38,6);printf("- Tus puntos ganados fueron: %d",contPunt);
				gotoxy(38,7);printf("- El tiempo que hiciste: %d:%d:%d",m2,m,s);
				gotoxy(38,8);printf("- Se te acabo el tiempo campeon!\n");
				gotoxy(38,9);system("pause");
				menu(carritoCh);
			}
			//opcion=getch();
			if(GetAsyncKeyState(0x25) && mapa2[y][x-1] == espacio)
			{
					gotoxy(x,y);printf(" ");
					x--;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x27) && mapa2[y][x+1] == espacio)
			{
					gotoxy(x,y);printf(" ");
					x++;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x28) && mapa2[y+1][x] == espacio)
			{
					gotoxy(x,y);printf(" ");
					y++;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x26) && mapa2[y-1][x] == espacio)
			{
					gotoxy(x,y);printf(" ");
					y--;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(x == finalX && y == finalY) // condicion para que se acabe el nivel del laberinto
			{
				if(m <= 30) // condicion para validar en cuanto tiempo termino el laberinto
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 350;
					gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("- Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("- El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
				if(m > 30 && m <= 60)
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 150;
					gotoxy(38,5);printf("Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
				if(m2 == 1 && m <= 30)
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 50;
					gotoxy(38,5);printf("Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
			}
			for(int r1=0; r1 < 30; r1++)
			{
				if(x == matRand[0][r1] && y == matRand[1][r1] && vida1 != ' ')
				{
					gotoxy(50,1);printf(" ");
					vida1 = ' ';
					matRand[0][r1] = 500;
					matRand[1][r1] = 400;
					contVid--;
					contObs++;
				}
			
			
				else if(vida1 == ' ' && x == matRand[0][r1] && y == matRand[1][r1])
				{
					gotoxy(51,1);printf("  ");
					vida2 = ' ';
					matRand[0][r1] = 500; // Esto sirve para que no corra el riesgo de que se repita la coordenada (Aqui corremos el riesgo de que se vuelva a repetir la coordenada y que no funcione correctamente)
					matRand[1][r1] = 400;
					contVid--;
					contObs++;
					
					if(m <= 30 || m > 30 || m2 == 1) // condicion para decirle en cuanto tiempo perdio
					{
						Color(BLACK, WHITE);
						system("cls");
						gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GAME OVER#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
						gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
						gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
						gotoxy(38,6);printf("- El tiempo que hiciste: %d:%d:%d",m2,m,s);
						gotoxy(38,7);printf("- Perdiste todas tus vidas\n");
						gotoxy(38,8);system("pause");
						menu(carritoCh);
					}
				}
			
				/*else if(vida2 == ' ' &&  x == matRand[0][r1] && y == matRand[1][r1])
				{
					gotoxy(52,1);printf(" ");
					gotoxy(52,1);printf("FF");
				}*/	
			
				if(x == xO && y == yO || x == pO || y == lO) // condicion para generar numeros random
				{	
				
					bool validar= false;
					while(validar != true)
					{
						xO = (rand() % 26)+ 0;
						yO = (rand() % 15)+ 0;
						pO = (rand() % 30)+ 0; // x
						lO = (rand() % 14)+ 0; // y
						validar = checarMap2(xO,yO,pO,lO);
					}
					Color(BLACK, GREEN);
					matRand[0][contador] = xO; // guardamos la posicion dentro de la matriz y despues se lo pasamos a las coordenadas de xO
					matRand[1][contador] = yO; // guardamos la posicion dentro de la matriz y despues se lo pasamos a las coordenadas de yO
					gotoxy(xO,yO);printf("@");
					contador++; // este contador sirve para indicarle el renglon a la matriz, para posteriormente cambiarlo por las coordenadas xO y yO
				}
			}
		}
	}	getch();
}


int movCarritoChafa3(char carritoCh,int xO,int yO, int pO, int lO)
{
	int x=0, y=20;
	// x=0 y=20
	int finalX=30;
	int finalY=0;
	int m=0;
	int m2=0;
	char vida1= '^';
	char vida2= '^';
	int matRand[30][27];
	int contador=0;
	int contVid=2;
	int contPunt=0;
	int contObs=0;
	Color(BLACK, WHITE);
	Color(BLACK, CYAN);
	gotoxy(x,y); printf("%c",carritoCh);
	Color(BLACK, WHITE);
	gotoxy(50,1);printf("%c %c",vida1,vida2);
	gotoxy(60,1);printf("Puntuacion: *%d*",puntos);
	gotoxy(38,0);printf("Timer");
	gotoxy(38,3);printf("Tu tiempo limite es 1:30:00");
	while(carritoCh != '@')
	{
		for(int s=0; s <= 90; s++) // es el for es para el cronometro
		{
			Color(BLACK, WHITE);
			gotoxy(60,0);printf("Obstaculos vencidos: %d",contObs);
			gotoxy(47,0);printf("Vidas: %d",contVid);
			//vidas(carritoCh,x,y,xO,yO,pO,lO);
			gotoxy(38,1);printf("%d:%d:%d",m2,m,s);
			Sleep(16);// velocidad del timer y carrito
			if(s == 60)
			{
				m++;
				s=0;
			}
			if(m == 60)
			{
				m2++;
				m=0;
			}
			if(m2 == 1 && m == 30)
			{
				Color(BLACK, WHITE);
				gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GAME OVER#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
				gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
				system("cls");
				gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
				gotoxy(38,6);printf("- Tus puntos ganados fueron: %d",contPunt);
				gotoxy(38,7);printf("- El tiempo que hiciste: %d:%d:%d",m2,m,s);
				gotoxy(38,8);printf("- Se te acabo el tiempo campeon!\n");
				gotoxy(38,9);system("pause");
				menu(carritoCh);
			}
			//opcion=getch();
			if(GetAsyncKeyState(0x25) && mapa3[y][x-1] == espacio)
			{
					gotoxy(x,y);printf(" ");
					x--;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x27) && mapa3[y][x+1] == espacio)
			{
					gotoxy(x,y);printf(" ");
					x++;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x28) && mapa3[y+1][x] == espacio)
			{
					gotoxy(x,y);printf(" ");
					y++;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(GetAsyncKeyState(0x26) && mapa3[y-1][x] == espacio)
			{
					gotoxy(x,y);printf(" ");
					y--;
					Color(BLACK, CYAN);gotoxy(x,y);printf("%c",carritoCh);
			}
			if(x == finalX && y == finalY) // condicion para que se acabe el nivel del laberinto
			{
				if(m <= 30) // condicion para validar en cuanto tiempo termino el laberinto
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 350;
					gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("- Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("- El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
				if(m > 30 && m <= 60)
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 150;
					gotoxy(38,5);printf("Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
				if(m2 == 1 && m <= 30)
				{
					Color(BLACK, WHITE);
					system("cls");
					gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GANASTE#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
					contPunt = 50;
					gotoxy(38,5);printf("Los obstaculos vencidos fueron: %d",contObs);
					gotoxy(38,6);printf("Tus puntos ganados fueron: %d",contPunt);
					gotoxy(38,7);printf("El tiempo que hiciste: %d:%d:%d\n",m2,m,s);
					return puntos + contPunt;
					gotoxy(38,8);system("pause");
					menu(carritoCh);
				}
			}
			for(int r1=0; r1 < 30; r1++)
			{
				if(x == matRand[0][r1] && y == matRand[1][r1] && vida1 != ' ')
				{
					gotoxy(50,1);printf(" ");
					vida1 = ' ';
					matRand[0][r1] = 500;
					matRand[1][r1] = 400;
					contVid--;
					contObs++;
				}
			
			
				else if(vida1 == ' ' && x == matRand[0][r1] && y == matRand[1][r1])
				{
					gotoxy(51,1);printf("  ");
					vida2 = ' ';
					matRand[0][r1] = 500; // Esto sirve para que no corra el riesgo de que se repita la coordenada (Aqui corremos el riesgo de que se vuelva a repetir la coordenada y que no funcione correctamente)
					matRand[1][r1] = 400;
					contVid--;
					contObs++;
					
					if(m <= 30 || m > 30 || m2 == 1) // condicion para decirle en cuanto tiempo perdio
					{
						Color(BLACK, WHITE);
						system("cls");
						gotoxy(0,1);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#GAME OVER#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
						gotoxy(0,22);printf("#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#--#");
						gotoxy(38,5);printf("- Los obstaculos vencidos fueron: %d",contObs);
						gotoxy(38,6);printf("- El tiempo que hiciste: %d:%d:%d",m2,m,s);
						gotoxy(38,7);printf("- Perdiste todas tus vidas\n");
						gotoxy(38,8);system("pause");
						menu(carritoCh);
					}
				}
			
				/*else if(vida2 == ' ' &&  x == matRand[0][r1] && y == matRand[1][r1])
				{
					gotoxy(52,1);printf(" ");
					gotoxy(52,1);printf("FF");
				}*/	
			
				if(x == xO && y == yO || x == pO || y == lO) // condicion para generar numeros random
				{	
				
					bool validar= false;
					while(validar != true)
					{
						xO = (rand() % 26)+ 0;
						yO = (rand() % 15)+ 0;
						pO = (rand() % 30)+ 0; // x
						lO = (rand() % 14)+ 0; // y
						validar = checarMap3(xO,yO,pO,lO);
					}
					Color(BLACK, YELLOW);
					matRand[0][contador] = xO; // guardamos la posicion dentro de la matriz y despues se lo pasamos a las coordenadas de xO
					matRand[1][contador] = yO; // guardamos la posicion dentro de la matriz y despues se lo pasamos a las coordenadas de yO
					gotoxy(xO,yO);printf("@");
					contador++; // este contador sirve para indicarle el renglon a la matriz, para posteriormente cambiarlo por las coordenadas xO y yO
				}
			}
		}
	}	getch();
}

//funcion para las coordenadas
void gotoxy(int x1, int y1)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x1;
	dwPos.Y = y1;
	SetConsoleCursorPosition(hcon,dwPos);
}

//funcion para Ocultar el cursor
void OcultaCursor() {
    CONSOLE_CURSOR_INFO cci = {100, FALSE};
    
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

//funciones para validar que no genere obstaculos random en las pardes del mapa
bool checarMap1(int xO, int yO, int pO, int lO)
{
	if(mapa1[yO][xO] == '#')
	{
		return false;
	}else 
	{
		return true;
	}
	if(mapa1[lO][pO] == '#')
	{
		return false;
	}else
	{
		return true;
	}
}

bool checarMap2(int xO, int yO, int pO, int lO)
{
	if(mapa2[yO][xO] == '#')
	{
		return false;
	}else 
	{
		return true;
	}
	if(mapa2[lO][pO] == '#')
	{
		return false;
	}else
	{
		return true;
	}
}

bool checarMap3(int xO, int yO, int pO, int lO)
{
	if(mapa3[yO][xO] == '#')
	{
		return false;
	}else 
	{
		return true;
	}
	if(mapa3[lO][pO] == '#')
	{
		return false;
	}else
	{
		return true;
	}
}

void portada()
{
	//C
	gotoxy(36,6);printf("C");Sleep(200);
	gotoxy(37,6);printf("C");Sleep(200);
	gotoxy(38,6);printf("C");Sleep(200);
	gotoxy(37,6);printf("C");Sleep(200);
	gotoxy(38,6);printf("C");Sleep(200);
	gotoxy(39,6);printf("C");Sleep(200);
	gotoxy(35,7);printf("C");Sleep(200);
	gotoxy(35,8);printf("C");Sleep(200);
	gotoxy(35,9);printf("C");Sleep(200);
	gotoxy(35,10);printf("C");Sleep(200);
	gotoxy(36,11);printf("C");Sleep(200);
	gotoxy(37,11);printf("C");Sleep(200);
	gotoxy(38,11);printf("C");Sleep(200);
	gotoxy(39,11);printf("C");Sleep(200);
	//A
	gotoxy(45,6);printf("A");Sleep(200);
	gotoxy(43,7);printf("A");Sleep(200);
	gotoxy(43,8);printf("A");Sleep(200);
	gotoxy(43,9);printf("A");Sleep(200);
	gotoxy(43,10);printf("A");Sleep(200);
	gotoxy(43,11);printf("A");Sleep(200);
	gotoxy(44,6);printf("A");Sleep(200);
	gotoxy(43,6);printf("A");Sleep(200);
	gotoxy(46,6);printf("A");Sleep(200);
	gotoxy(47,6);printf("A");Sleep(200);
	gotoxy(44,9);printf("A");Sleep(200);
	gotoxy(45,9);printf("A");Sleep(200);
	gotoxy(46,9);printf("A");Sleep(200);
	gotoxy(47,11);printf("A");Sleep(200);
	gotoxy(47,6);printf("A");Sleep(200);
	gotoxy(47,7);printf("A");Sleep(200);
	gotoxy(47,8);printf("A");Sleep(200);
	gotoxy(47,9);printf("A");Sleep(200);
	gotoxy(47,10);printf("A");Sleep(200);
	gotoxy(47,11);printf("A");Sleep(200);
	//D
	gotoxy(50,6);printf("D");Sleep(200);
	gotoxy(50,7);printf("D");Sleep(200);
	gotoxy(50,8);printf("D");Sleep(200);
	gotoxy(50,9);printf("D");Sleep(200);
	gotoxy(50,10);printf("D");Sleep(200);
	gotoxy(50,11);printf("D");Sleep(200);
	gotoxy(51,11);printf("D");Sleep(200);
	gotoxy(52,11);printf("D");Sleep(200);
	gotoxy(53,10);printf("D");Sleep(200);
	gotoxy(54,9);printf("D");Sleep(200);
	gotoxy(54,8);printf("D");Sleep(200);
	gotoxy(53,7);printf("D");Sleep(200);
	gotoxy(52,6);printf("D");Sleep(200);
	gotoxy(51,6);printf("D");Sleep(200);
	
	gotoxy(38,14);printf("CARRITO DEMENTE");Sleep(500);
	gotoxy(27,15);printf("UNIVERSIDAD AUTONOMA DE AGUASCALIENTES");Sleep(500);
	gotoxy(35,16);printf("INGENIERIA EN SISTEMAS");Sleep(500);
	gotoxy(38,17);printf("PROYECTO EN C++");Sleep(500);
	gotoxy(40,18);printf("0");Sleep(100);
	gotoxy(41,18);printf("5");Sleep(100);
	gotoxy(42,18);printf("/");Sleep(100);
	gotoxy(43,18);printf("1");Sleep(100);
	gotoxy(44,18);printf("2");Sleep(100);
	gotoxy(45,18);printf("/");Sleep(100);
	gotoxy(46,18);printf("2");Sleep(100);
	gotoxy(47,18);printf("0");Sleep(100);
	gotoxy(48,18);printf("2");Sleep(100);
	gotoxy(49,18);printf("0");Sleep(100);
	gotoxy(1,25);printf("CREADORES: JOSE JIMENEZ, LUIZ HUMBERTO, ANGEL RMZ Y ANDREA CANDELARIO");Sleep(1000);
	system("cls");
	gotoxy(1,25);printf("CARGANDO LABERINTO ");
	gotoxy(20,25);printf(".");Sleep(500);
	gotoxy(20,25);printf(" ");Sleep(500);
	gotoxy(21,25);printf(".");Sleep(500);
	gotoxy(21,25);printf(" ");Sleep(500);
	gotoxy(22,25);printf(".");Sleep(500);
	gotoxy(22,25);printf(" ");Sleep(500);
	gotoxy(20,25);printf(".");Sleep(500);
	gotoxy(20,25);printf(" ");Sleep(500);
	gotoxy(21,25);printf(".");Sleep(500);
	gotoxy(21,25);printf(" ");Sleep(500);
	gotoxy(22,25);printf(".");Sleep(500);
	gotoxy(22,25);printf(" ");Sleep(500);
	gotoxy(20,25);printf(".");Sleep(500);
	gotoxy(20,25);printf(" ");Sleep(500);
	gotoxy(21,25);printf(".");Sleep(500);
	gotoxy(21,25);printf(" ");Sleep(500);
	gotoxy(22,25);printf(".");Sleep(500);
	gotoxy(22,25);printf(" ");Sleep(500);
}

void tablaPunt(char tablaN[][10],char tablaP[][10])
{
	llenarTabla(tablaN,tablaP);
	mostrarTabla(tablaN,tablaP);
}

void llenarTabla(char tablaN[][10],char tablaP[][10])
{
	char textoPunt[10000];
	sprintf(textoPunt, "%d", puntos);
	/*for(int p=0; p < REN; p++)
	{
		tabla[i][0] = p+1; // el mas uno es para que se valla del 0 al 10
		printf("%d \t",p);
	}*/
	strcpy(tablaP[contP], textoPunt);
	strcpy(tablaN[contP], nombre);
}

void mostrarTabla(char tablaN[][10],char tablaP[][10])
{
	printf("\nNombre\t#Puntos\n");
	printf("\n-------------------\n");
	for(int i=0; i< contP + 1; i++)
	{
		printf("%s \t %s",tablaN[i],tablaP[i]);
		printf("\n");
	}
}

//funcion para ajustar la ventana de la consola
bool AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}


// función para cambiar el color del fondo y/o pantalla
void Color(int Background, int Text){ 

	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

	// Para cambiar el color, se utilizan números desde el 0 hasta el 255.
	// Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
	int    New_Color= Text + (Background * 16); 

	SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.

}
