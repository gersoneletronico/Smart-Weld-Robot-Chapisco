#ifndef __parametrizacao_h_
      #define __parametrizacao_h_
      #include "global.h"
void Gravainicial(
   const long int *contaPulsosY,
   long int *contaPulsosX, 
   long int *PontoInicialSoldaY,
   long int *PontoFinalSoldaY
);
void Gravafinal(
  const long int *contaPulsosY,
   long int *PontoInicialSoldaY,
   long int *PontoFinalSoldaY
);
#endif
