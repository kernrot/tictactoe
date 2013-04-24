//
//	TTT.cpp
//	(Konsolenanwendung in C)
//
//	TicTacToe (XXO) mit KI 
//	erstellt von Conrad Kernrot 4-2013
//	tictactoe@conradhenke.de
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

char Taste(int d) {
	// Fängt einen Tastendruck ab und gibt das passende Zeichen zurück
	char key=0;
	while (key == 0) {
		_sleep(100);
		key = kbhit();
	}
	key = getch();
	if (key == -32 || key == 0) key = getch();	// Umgehung für Sondertasten
	if(d)printf("\nDebug: Taste: %d", key);
	return key;
}

void ki_sZ(int f[3][3],int z){ //setze in Zeile
	for(int s=0; s<3; s++){
		if ((f[z][s]) == 0) { f[z][s] = -1; return; }
	}
	return;
}

void ki_sS(int f[3][3],int s){ //setze in Spalte
	for(int z=0; z<3; z++){
		if ((f[z][s]) == 0) { f[z][s] = -1; return; }
	}
	return;
}

void ki_sF(int f[3][3]){ //setze erste möglichkeit
	for(int z=0; z<3; z++){
		for(int s=0; s<3; s++){
			if ((f[z][s]) == 0) { f[z][s] = -1; return; }
		}
	}
	return;
}

void ki_sDl(int f[3][3]){ //setze Diagonale "\"
	if (f[0][0] == NULL) { f[0][0] = -1; return; }
	if (f[1][1] == NULL) { f[1][1] = -1; return; }
	if (f[2][2] == NULL) { f[2][2] = -1; return; }
	return;
}

void ki_sDr(int f[3][3]){ //setze Diagonale "/"
	if (f[0][2] == NULL) { f[0][2] = -1; return; }
	if (f[1][1] == NULL) { f[1][1] = -1; return; }
	if (f[2][0] == NULL) { f[2][0] = -1; return; }
	return;
}

void ki(int f[3][3]){
	/* KI Prinzipien:
	1. Gewinnen
	2. Gegnergewinn blocken
	3. Mitte
	4. Erste freier platz */

	// 1. & 2. Gewinnen(Verlieren verhindern) Spieler oder KI hat 2 in Reihe

	//Zeile
	for(int z=0; z<3; z++){
		if (f[z][0]+f[z][1]+f[z][2] == 2) {ki_sZ(f,z); return;}
		if (f[z][0]+f[z][1]+f[z][2] == -2) {ki_sZ(f,z); return;}}
	//Spalte
	for(int s=0; s<3; s++){
		if (f[0][s]+f[1][s]+f[2][s] == 2) {ki_sS(f,s); return;}
		if (f[0][s]+f[1][s]+f[2][s] == 2) {ki_sS(f,s); return;}}
	//Diagonalen
	if (f[0][0]+f[1][1]+f[2][2] == 2) {ki_sDl(f); return;}
	if (f[0][0]+f[1][1]+f[2][2] == -2) {ki_sDl(f); return;}
	if (f[0][2]+f[1][1]+f[2][0] == 2) {ki_sDr(f); return;}
	if (f[0][2]+f[1][1]+f[2][0] == -2) {ki_sDr(f); return;}

	// Mitte

	if (f[1][1] == NULL) { f[1][1] = -1; return; }

	// erster freier Platz

	ki_sF(f);	return;
}

int checkAlleBelegt(int f[3][3]){
	int anzBelegt = 0;
	for(int z=0; z<3; z++){
		for(int s=0; s<3; s++){
			if(f[z][s]) anzBelegt++;
		}
	}
	if (anzBelegt<9) { return 0; } else { return 1; }
}

int checkGewonnen(int f[3][3]){
	//Alle belegt?
	if(checkAlleBelegt(f)) return -2;
	//Wagerecht
	for(int z=0; z<3; z++){
		if (f[z][0]+f[z][1]+f[z][2] == 3) return 1;
		if (f[z][0]+f[z][1]+f[z][2] == -3) return -1;}
	//Senkrecht
	for(int s=0; s<3; s++){
		if (f[0][s]+f[1][s]+f[2][s] == 3) return 1;
		if (f[0][s]+f[1][s]+f[2][s] == -3) return -1;}
	//Diagonalen
	if (f[0][0]+f[1][1]+f[2][2] == 3) return 1;
	if (f[0][0]+f[1][1]+f[2][2] == -3) return -1;
	if (f[0][2]+f[1][1]+f[2][0] == 3) return 1;
	if (f[0][2]+f[1][1]+f[2][0] == -3) return -1;
	return 0;
}

void printFeld(int f[3][3], int p[2]){
	printf("\n\tTicTacToe\t\tvon Conrad Kernrot\n\t\t\t\ttictactoe\100kernrot.de\n\t");
	for(int z=0; z<3; z++){
		for(int s=0; s<3; s++){

			switch (f[z][s])				{
			case 1:			if(p[0]==z && p[1]==s) printf(">"); else printf(" ");	printf("X ");	break;
			case -1:			if(p[0]==z && p[1]==s) printf(">"); else printf(" ");	printf("O ");	break;
			default:		if(p[0]==z && p[1]==s) printf(">"); else printf(" ");	printf("  ");	break;
			}
			if(s<2)printf("|");
		}
		if(z<2)printf("\t\n\t-----------\n\t");
	}
	printf("\n\n");
};

void main(){

	int d=0;
	int f[3][3] = {{0}};	//Spielfeld
	int z[2] = {0};		//Setzpfeil
	int spiel = 1;


	printFeld(f,z);
	while(spiel){

		switch(Taste(d)){
		case 72: if(z[0]>0) z[0]--; break; //oben
		case 80: if(z[0]<2) z[0]++; break; //unten
		case 77: if(z[1]<2) z[1]++; break; //rechts
		case 75: if(z[1]>0) z[1]--; break; //links
		case 13: f[z[0]][z[1]] = 1; ki(f);  break; //enter
		case 27: spiel = NULL; break; //esc
		}

		system("cls");
		printFeld(f,z);
		if(checkGewonnen(f)) {
			spiel=NULL;				// Ende
			if(checkGewonnen(f) == 1)	printf("\tSie gewinnen!\n");
			if(checkGewonnen(f) == -1)	printf("\tComputer gewinnt!\n");
			if(checkGewonnen(f) == -2)	printf("\tUnentschieden!\n");
			printf("\n\t(Enter) zum Beenden, (beliebige Taste) noch ein Spiel");

			if(Taste(d) != 13) {
				spiel = 1;					// Spiel erneut initialisieren
				memset(f,0,sizeof(f));
				system("cls");
				printFeld(f,z);
			}
		}
	}
}