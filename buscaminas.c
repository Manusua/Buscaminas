#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <math.h>
#include<time.h>

struct Celda{
  int mina;
  int cerca;
  bool desc;
  bool marked;
}Celda;

void iniciar(int tam, int num_minas, struct Celda tablero[tam][tam]){
  srand (time(NULL));
  int i,cordx,cordy;
  printf("Posición de las %d minas:\n", num_minas );
  for(i = 0; i < num_minas; ++i){
    cordx = floor(rand()%tam);
    cordy = floor(rand()%tam);
    printf("CoordX: %d    CoordY: %d\n", cordx + 1, cordy + 1);
    if(tablero[cordx][cordy].mina == 1){
      i--;
    }
    else{
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
      for(k = -1; k < 2 && (i + k >= 0) && (i + k < tam) ;k++){
        for(l = -1; l < 2 && (j + l >= 0) && ( j + l < tam); l++){
          if(tablero[i + k][j + l].mina == 1){
            cont++;
          }
        }
      }
      if(tablero[i][j].mina == 1){
        cont--;
      }
      tablero[i][j].cerca = cont;
    }
  }
}

void imprimir( int tam, struct Celda tablero[tam][tam]){
  int i, k, j;

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
          printf("\033[0;36m");
          printf(" %d ", tablero[i][j].cerca );
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
        for(k = -1; k < 2 && (fil + k >= 0) && (fil + k < tam) ;k++){
          for(l = -1; l < 2 && (col + l >= 0) && ( col + l < tam); l++){
            procesar( tam, exp, fil + k, col + l, tablero, opt);
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

void main(){
  char name[100];
  int num_minas;
  int tam;
  char opt, endofline;
  int col, fil;
  int exp = 0, marked = 0;
  bool win = false;
  printf("BIENVENIDO AL MARAVILLOSO JUEGO DEL BUSCAMINAS\nIntroduzca su nombre: ");
  scanf("%s", name);
  printf("Hola %s, dispuesto a jugar el increible juego del buscaminas?\n", name);
  printf("-------------------------\n" );
  printf("Introduce el tamaño del tablero(recomendado 16)\n");
  scanf("%d", &tam);
  while (tam <= 0 || tam > 99) {
    system("clear");
    printf("Introduce un tamaño comprendido entre 1 y 99\n");
    scanf("%d", &tam);
  }
  printf("Introduce el numero de minas (recomendado 40)\n" );
  scanf("%d", &num_minas);

  while (num_minas <= 0 || num_minas > tam * tam - 1) {
    system("clear");
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
    system("clear");
    imprimir(tam, tablero);
    printf("¿Qué deseas hacer?\n\t(M) Marcar mina\tMarcadas(%d/%d)\n\t(D) Descubrir casilla\n", marked, num_minas);

    scanf("%c", &endofline);
    scanf("%c", &opt);
    scanf("%c", &endofline);
    while(opt != 'M' && opt != 'D'){
      printf("¿Qué deseas hacer?\n\t(M) Marcar mina\n\t(D) Descubrir casilla\n");
      scanf("%c", &opt);
      scanf("%c", &endofline);
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

printf("ENHORABUENA! HAS GANADO, AHORA %s PASARA AL PABELLON DE LA FAMA\n", name );
}
