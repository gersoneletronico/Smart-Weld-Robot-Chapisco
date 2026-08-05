#include "parametrizacao.h"
//========= Função para calcular largura de solda ===============
void calcula_largura_fio_solda(){
    if(PontoInicialSoldaY > 0 && PontoFinalSoldaY >= 0 && parametro.FIO_SOLDA_POR_FRISO > 1){
        Largura_Fio_de_Solda = (PontoInicialSoldaY - PontoFinalSoldaY)/(parametro.FIO_SOLDA_POR_FRISO-1);
    }
    if(PontoInicialSoldaY > 0 && PontoFinalSoldaY > 0 && PontoInicialSoldaY > PontoFinalSoldaY)
        liberachapisco = true;
    else
        liberachapisco = false;
}
//================ Grava ponto inicial de chapisco  ==============
void Gravainicial(
   const long int *contaPulsosY,
   long int *contaPulsosX, 
   long int *PontoInicialSoldaY,
   long int *PontoFinalSoldaY
   ){
  long int pontoInicialX = 0;
  int passo_friso = parametro.PULSO_POL_X * parametro.DISTANCIA_ENTRE_FRISOS;
  if(*contaPulsosY != *PontoInicialSoldaY && *contaPulsosY > *PontoFinalSoldaY){        
      *PontoInicialSoldaY = *contaPulsosY;
      if(*PontoFinalSoldaY == 0){
        int ponto_final = *PontoInicialSoldaY-((int) parametro.DISTANCIA_ENTRE_FRISOS * (parametro.PULSO_MM_Y*parametro.PONTO_FINAL_SOLDA_AUTO));
 
          if(parametro.CHAPISCO_OU_SOLDA && !parametro.HAB_OSCILACAO){
            *PontoFinalSoldaY = *PontoInicialSoldaY - parametro.PULSO_MM_Y; 
          }else{
            if(ponto_final > 0){
            *PontoFinalSoldaY = ponto_final; 
            Move_tocha_ponto_final = true;
            }
          }              
      }  
  }
  STATUS_PROCESSO = "Gravou Inicio do chapisco no Friso";  
  // O PONTO INICIAL DEVE SEMPRE SER NO PRIMEIRO FRISO    
    pontoInicialX = passo_friso * conta_friso_para_posicao;
    int meio_friso = passo_friso/2;
    //ponto inicial sempre = 0
    //*contaPulsosX = pontoInicialX;
    if(conta_friso == 1){
      *contaPulsosX = 0;
    }else{
      long int diferenca = *contaPulsosX-pontoInicialX;
      if(diferenca < meio_friso && diferenca > (meio_friso*(-1)))
      *contaPulsosX = *contaPulsosX - diferenca;  
    }              
    calcula_largura_fio_solda();
}// Fim da função Gravainicial

void Gravafinal(
  const long int *contaPulsosY,
   long int *PontoInicialSoldaY,
   long int *PontoFinalSoldaY
){
  if(*contaPulsosY >= 0 && *PontoInicialSoldaY > *contaPulsosY){
    *PontoFinalSoldaY = *contaPulsosY ;
    calcula_largura_fio_solda();
    STATUS_PROCESSO = "Gravou Final do chapisco no Friso";
  }
}// Fim da função Gravafinal
