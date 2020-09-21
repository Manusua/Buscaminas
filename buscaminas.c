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
}Celda;

void iniciar(int tam, int num_minas, struct Celda tablero[tam][tam]){
  srand (time(NULL));
  int i,cordx,cordy;
  for(i = 0; i < num_minas; ++i){
    cordx = floor(rand()%tam);
    cordy = floor(rand()%tam);
    printf("CoordX: %d    CoordY: %d\n", cordx, cordy );
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
  for (i = 0; i < tam; i++){
    printf("|");
    for(j = 0; j <tam; ++j){
      if(tablero[i][j].desc){
        if(tablero[i][j].mina == 1){
          printf(" M |");
        }
        else{
          printf(" %d |", tablero[i][j].cerca );
        }
      }
      else{
        printf(" ? |");
      }
    }
    printf("\n");

  }
}

void procesar( int tam, int exp, int fil, int col, struct Celda tablero[tam][tam]){
int k, l;
  if (!tablero[fil][col].desc){
    tablero[fil][col].desc = true;
    exp++;
    if(tablero[fil][col].mina == 1){
      printf("LO SIENTO, HAS PERDIDO, HABIA UNA MINA CACHO INUTIL\n");
      exit(0);
    }
    if(tablero[fil][col].cerca == 0){
      for(k = -1; k < 2 && (fil + k >= 0) && (fil + k < tam) ;k++){
        for(l = -1; l < 2 && (col + l >= 0) && ( col + l < tam); l++){
          procesar( tam, exp, fil + k, col + l, tablero);
        }
      }
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
    }
  }
}

void main(){
  char name[100];
  int num_minas;
  int tam;
  int col, fil;
  int exp = 0;
  bool win = false;
  printf("BIENVENIDO AL MARAVILLOSO JUEGO DEL BUSCAMINAS\nIntroduzca su nombre");
  scanf("%s", name);
  printf("HOLA %s, dispuesto a jugar el increible juego del buscaminas?\n", name);
  printf("-------------------------\n" );
  printf("Introduce el tamaño del tablero(recomendado 16)\n");
  scanf("%d", &tam);
  printf("Introduce el numero de minas (recomendado 40)\n" );
  scanf("%d", &num_minas );

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
    printf("Introduce la fila y la columna que deseas descubrir\n" );
    scanf("%d %d", &fil, &col );
    procesar( tam, exp, fil, col, tablero);
    if(exp == tam*tam - num_minas) win = true;
  }

printf("ENHORABUENA! HAS GANADO, AHORA %s PASARA AL PABELLON DE LA FAMA\n", name );
}
