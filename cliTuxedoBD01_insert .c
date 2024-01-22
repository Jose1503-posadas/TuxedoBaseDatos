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
  
  /* Manejo del Buffer FML */
  printf ("\nInsertamos datos en buffer FML.");
  if(Fadd32 (fbfr, CODIGO, (char *)&bib.codigo, 0) < 0){
    printf ("\n\tError insertando campo FML (CODIGO)");
    tpfree((char*)fbfr);
    tpterm();
    return (0);
  }
  if(Fadd32 (fbfr, AUTOR, bib.autor, 0) < 0){
    printf ("\n\tError insertando campo FML (AUTOR)");
    tpfree((char*)fbfr);
    tpterm();
    return (0);
  }
  if(Fadd32 (fbfr, TITULO, bib.titulo, 0) < 0) {
    printf ("\n\tError insertando campo FML (TITULO)");
    tpfree((char*)fbfr);
    tpterm();
    return (0);
  }
  if(Fadd32 (fbfr, DESC, bib.descrp, 0) < 0) {
    printf ("\n\tError insertando campo FML (DESC)") ;
    tpfree((char*)fbfr);
    tpterm();
    return (0);
  }
  // Invocamos el servicio
  printf("Llamada al servicio 'INSERT_FML32'\n");
  if(tpcall("INSERT_FML32", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt,0L) ==-1){
    printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
    tpfree((char *)fbfr);
    tpfree((char *)recv);
    tpterm();
    return (1);
  }
  flen = sizeof(msgbuf);
  Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
  printf("Respuesta del servidor: %s\n", msgbuf);
  // Liberamos el buffer y desconectamos de la aplicacion
  printf("Liberamos Buffer y desconectamos de la aplicacion\n");
  tpfree((char *)fbfr);
  tpfree((char *)recv);
  tpterm();
  return 0;
}
