#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <math.h>
#include <time.h>
#include <ctype.h>

struct Celda{
  int mina;
  int cerca;
  bool desc;
  bool marked;
}Celda;

//TODO tablon de la FAMA y de la miseria
//TODO interfaz grafica
//Pasar valdgrind


void iniciar(int tam, int num_minas, struct Celda tablero[tam][tam]){
  srand (time(NULL));
  int i,cordx,cordy;
//  printf("Posición de las %d minas:\n", num_minas );
  for(i = 0; i < num_minas; ++i){
    cordx = floor(rand()%tam);
    cordy = floor(rand()%tam);
    if(tablero[cordx][cordy].mina == 1){
      i--;
    }
    else{
    //  printf("CoordX: %d    CoordY: %d\n", cordx + 1, cordy + 1);
      tablero[cordx][cordy].mina = 1;
    }
  }
}

void comprobar(int tam, struct Celda tablero[tam][tam]){
  int i,j,k,l;
  int cont;
  for(i = 0; i < tam; ++i){
    for(j = 0; j < tam; ++j){
      cont = 0;
      for(k = -1; k < 2; k++){
        if((i + k >= 0) && (i + k < tam)){
          for(l = -1; l < 2; l++){
            if((j + l >= 0) && ( j + l < tam) && tablero[i + k][j + l].mina == 1){
              cont++;
            }
          }
        }
      }
      if(tablero[i][j].mina == 1){
        cont--;
      }
      tablero[i][j].cerca = cont;
      //printf("Numero de minas en %d, %d: %d\n", i + 1, j + 1, cont);
    }
  }
}

void imprimir( int tam, struct Celda tablero[tam][tam]){
  int i, k, j, z;

  printf("     ");
  for (i = 0; i < tam; i++){
    if(i >= 9){
      printf("%d  ", i + 1);
    }
    else{
      printf(" %d  ", i + 1);
    }
  }
  printf("\n");
  printf("     ");
  printf("\033[0;35m");
  for (z = 0; z < tam; z++){

    printf("----");
  }
  printf("\n");
  printf("\033[0m");

  for (i = 0; i < tam; i++){
    if(i >= 9){
      printf("%d  ", i + 1);
    }
    else{
      printf(" %d  ", i + 1);
    }
    printf("\033[0;35m");
    printf("|");
    printf("\033[0m");
    for(j = 0; j <tam; ++j){
      if(tablero[i][j].desc){/*
        if(tablero[i][j].mina == 1){
          printf("\033[0;31mm");
          printf(" M ");
          printf("\033[0;35m");
          printf("|");
          printf("\033[0m");
        }
        else{*/
          switch (tablero[i][j].cerca) {
            case 0:
              printf("\033[0;36m");
              printf("   ");
              break;
            case 1:
              printf("\033[1;36m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 2:
              printf("\033[1;34m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 3:
              printf("\033[0;34m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 4:
              printf("\033[0;35m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 5:
              printf("\033[1;35m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 6:
              printf("\033[0;31m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 7:
              printf("\033[1;31m");
              printf(" %d ", tablero[i][j].cerca );
              break;
            case 8:
              printf("\033[0;33m");
              printf(" %d ", tablero[i][j].cerca );
              break;
          }
          printf("\033[0;35m");
          printf("|");
          printf("\033[0m");
        //}
      }
      else if (tablero[i][j].marked){
        printf("\033[0;31m");
        printf(" M ");
        printf("\033[0;35m");
        printf("|");
        printf("\033[0m");
      }
      else{
        printf(" ? ");
        printf("\033[0;35m");
        printf("|");
        printf("\033[0m");
      }
    }
    printf("  %d\n", i + 1);

    printf("     ");
    printf("\033[0;35m");
    for (z = 0; z < tam; z++){

      printf("----");
    }
    printf("\n");
    printf("\033[0m");
  }

  printf("     ");
  for(i = 0; i < tam; i++){
    if(i >= 9){
      printf("%d  ", i + 1);
    }
    else{
      printf(" %d  ", i + 1);
    }
  }
  printf("\n");
}

void procesar( int tam, int *exp, int fil, int col, struct Celda tablero[tam][tam], char opt){
  int k, l, aux;
  if (!tablero[fil][col].desc){
    switch(opt){
      case 'M':
        tablero[fil][col].marked = true;
        break;
      case 'D':
      tablero[fil][col].desc = true;
      aux = *exp + 1;
      memcpy(exp, &aux, sizeof(int));
      if(tablero[fil][col].mina == 1){
        if(opt == 'D'){
          printf("LO SIENTO, HAS PERDIDO, HABIA UNA MINA CACHO INUTIL\n");
          exit(0);
        }
      }
      if(tablero[fil][col].cerca == 0){
        for(k = -1; k < 2;k++){
          if((fil + k >= 0) && (fil + k < tam)){
            for(l = -1; l < 2; l++){
              if((col + l >= 0) && ( col + l < tam)){
                procesar( tam, exp, fil + k, col + l, tablero, opt);
              }
            }
          }
        }
      }
      break;
    }

  }
}

void inicializar( int tam, struct Celda tablero[tam][tam]){
  int i, j;
  for(i = 0; i < tam; ++i){
    for(j = 0; j < tam; j++){
      tablero[i][j].mina = 0;
      tablero[i][j].cerca = 0;
      tablero[i][j].desc = false;
      tablero[i][j].marked = false;
    }
  }
}

void jugar(){

  int num_minas;
  int tam;
  char opt, men;
  int col, fil;
  int exp = 0, marked = 0;
  bool win = false;

  printf("Introduce el tamaño del tablero(recomendado 16)\n");
  scanf("%d", &tam);
  while (tam <= 0 || tam > 99) {
    //system("clear");
    printf("Introduce un tamaño comprendido entre 1 y 99\n");
    scanf("%d", &tam);
  }
  printf("Introduce el numero de minas (recomendado 40)\n" );
  scanf("%d", &num_minas);

  while (num_minas <= 0 || num_minas > tam * tam - 1) {
    //system("clear");
    printf("Introduce un número de minas comprendido entre 1 y %d\n", tam * tam - 1);
    scanf("%d", &num_minas);
  }

  struct Celda tablero[tam][tam];
  inicializar(tam, tablero);
  printf("inicializado\n" );
  iniciar( tam, num_minas, tablero);
  printf("iniciado\n");
  comprobar(tam, tablero);
  printf("comporbado\n" );

  while(!win){
    //system("clear");
    imprimir(tam, tablero);
    printf("¿Qué deseas hacer?\n\t(M) Marcar mina\tMarcadas(%d/%d)\n\t(D) Descubrir casilla\n", marked, num_minas);

    scanf(" %c", &opt);
    opt = toupper(opt);
    while(opt != 'M' && opt != 'D'){
      //system("clear");
      printf("Por favor, introduce un caracter valido\n¿Qué deseas hacer?\n\t(M) Marcar mina\n\t(D) Descubrir casilla\n");
      scanf(" %c", &opt);
      opt = toupper(opt);
    }

    switch(opt){
      case 'M':
        printf("Introduce la fila y la columna que deseas marcar\n" );
        marked++;
        break;
      case 'D':
        printf("Introduce la fila y la columna que deseas descubrir\n" );
        break;
    }

    scanf("%d %d", &fil, &col );
    while(fil <= 0 || fil > tam || col <= 0 || col > tam){
      printf("Lo siento, introduce una fila y columna dentro del rango del tablero \n");
      scanf("%d %d", &fil, &col );
    }

    fil--;
    col--;
    procesar(tam, &exp, fil, col, tablero, opt);
    if(exp == tam*tam - num_minas) win = true;
  }

  imprimir(tam, tablero);
}


void tablon_fama(){}

void tablon_miseria(){}

char menu_principal(){
  char men;
  printf("¿Qué deseas hacer?\n\t(J) Jugar\n\t(F) Ver el tablón de la fama\n\t(M) Ver el tablón de la miseria\n");

  scanf(" %c", &men);
  men = toupper(men);
  while(men != 'J' && men != 'F' && men != 'M'){
    //system("clear");
    printf("Por favor, introduce un caracter valido\n¿Qué deseas hacer?\n\t(J) Jugar\n\t(F) Ver el tablón de la fama\n\t(M) Ver el tablón de la miseria\n");
    scanf(" %c", &men);
    men = toupper(men);
  }
  return men;
}


void main(){
  char name[100];
  char men;
  printf("BIENVENIDO AL MARAVILLOSO JUEGO DEL BUSCAMINAS\nIntroduzca su nombre: ");
  scanf("%s", name);
  printf("Hola %s, dispuesto a jugar el increible juego del buscaminas?\n", name);
  printf("-------------------------\n" );

  men = menu_principal();
  while(men != 'J'){
    switch(men){
      case 'M':
        tablon_miseria();
        men = menu_principal();
        break;
      case 'F':
        tablon_fama();
        men = menu_principal();
        break;
      }
  }

  jugar();

  printf("ENHORABUENA! HAS GANADO, AHORA %s PASARA AL PABELLON DE LA FAMA\n", name );

  return;
}
