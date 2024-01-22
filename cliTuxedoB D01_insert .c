#include <stdio.h>
#include <atmi.h>
#include <fml32.h>
#include <string.h>
#include "biblioBD01.fml.h"

typedef struct biblio{
  int codigo;
  char autor[51];
  char titulo[151];
  char descrp[251];
}biblio;

int main(int argc, char **argv){
  int ivL_resLlamd;
  long lvL_tamLongt;
  float fvL_recValor;
  FBFR32 *fbfr;
  FBFR32 *recv;
  FLDLEN32 flen;
  char msgbuf[64];
  /* Inicializamos una referencia bibliografica */
  biblio bib;
  printf("\n*************************************************\n");
  printf("Codigo : "); scanf("%d", &bib.codigo);
  printf("Autor : "); scanf("%s", bib.autor);
  printf("Titulo : "); scanf("%s", bib.titulo);
  printf("Descripcion : "); scanf("%s", bib.descrp);
  printf("\n*************************************************\n");
  /* Conectamos con la aplicacion Tuxedo Server */
  printf ("Conectamos con la aplicacion\n") ;
  if(tpinit((TPINIT *) NULL) == - 1){
      printf("Error en la conexion, tperrno = %d\n", tperrno);
      return (1) ;
  }
  // Reservamos espacio para el buffer FML
  printf ("Reservamos Espacio para los buffers FML\n") ;
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
    printf("Error Reservando espacio para Buffer fbfr\n");
    tpterm();
    return(1);
  }
  if((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
    printf("Error Reservando espacio para Buffer recv\n");
    tpterm();
    return(1);
  }
}
