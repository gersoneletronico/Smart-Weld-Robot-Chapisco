#include "chapisco.h"

void AcionamentoArameMaquina(bool arame, bool maquina){    
    if(parametro.HAB_ALIMENTADOR_1 && arame){
      digitalWrite(DO_ARAME_1, HIGH);
    }else{
      digitalWrite(DO_ARAME_1, LOW);
    }
    if(parametro.HAB_ALIMENTADOR_1 && maquina){
      digitalWrite(DO_MAQ_1, HIGH);    
    }else{
      digitalWrite(DO_MAQ_1, LOW);
    }
    if(parametro.HAB_ALIMENTADOR_2 && arame){
      digitalWrite(DO_ARAME_2, HIGH);  
    }else{
      digitalWrite(DO_ARAME_2, LOW);
    }
    if(parametro.HAB_ALIMENTADOR_2 && maquina){
      digitalWrite(DO_MAQ_2, HIGH);
    }else{
      digitalWrite(DO_MAQ_2, LOW);
    }
}
void CalculaTempoGiro(const bool *HAB_DESAB_SENSOR_GIRO, const unsigned int *tempo_de_giro, const float *rpm_real, const unsigned char ParametroRPM){
    static unsigned long retarda_trip_giro = millis();
    if(parametro.CHAPISCO_OU_SOLDA == false){
      if(*HAB_DESAB_SENSOR_GIRO){
          if(*rpm_real > 1){
            tempGiro = (60/(*rpm_real))*1000;   //RPM real calculado pelo sensor de giro     
            retarda_trip_giro = millis();
          }else{ 
            if(IniciarChapiscoIHM) {
                if(millis() - retarda_trip_giro >= 3000){
                  IniciarChapiscoIHM = 0;
                  STATUS_PROCESSO = "Parou Pelo Giro da Moenda";
                  retarda_trip_giro = millis();
                }
            }else{
                  retarda_trip_giro = millis();
            }   
            
          }      
      }else{
          retarda_trip_giro = millis();
          if(ParametroRPM <= 0)
          tempGiro = (60/5)*1000;   //Rpm estimado nas configuração 
          else
          tempGiro = (60/ParametroRPM)*1000;   //Rpm estimado nas configuração 
      } 
    }else{
      if(*HAB_DESAB_SENSOR_GIRO){
         if(*tempo_de_giro > 1){
            tempGiro = *tempo_de_giro;   //RPM real calculado pelo sensor de giro     
            retarda_trip_giro = millis();
         }else{    
            tempGiro = 0;     
            if(IniciarChapiscoIHM) {
                if(millis() - retarda_trip_giro >= 3000){
                    IniciarChapiscoIHM = 0;
                    STATUS_PROCESSO = "Parou Pelo Giro da Moenda";
                    retarda_trip_giro = millis();
                }
            }else{
                    retarda_trip_giro = millis();
            }
         }      
      }else{
          retarda_trip_giro = millis();
          if(parametro.TEMPO_DE_GIRO < 5)
          tempGiro = 5000;   //Rpm estimado nas configuração 
          else
          tempGiro = parametro.TEMPO_DE_GIRO*1000;
      }       
    }
    

}
unsigned char movi_tocha(const long int *contaPul_Y, bool restart){
   static unsigned long pega_millis   = millis();
   if(!reset_tempo_chapisco){
       pega_millis = millis();   
     reset_tempo_chapisco=true;
   }    
   if(restart) {conta_fio_solda=1; return conta_fio_solda; reset_tempo_chapisco=false;}   
   if(contaPulsosY != PontoInicialSoldaY-(Largura_Fio_de_Solda * (conta_fio_solda-1))){
        driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, PontoInicialSoldaY-(Largura_Fio_de_Solda * (conta_fio_solda-1)), &contaPulsosY, &contaPulsosX);            
        pega_millis = millis(); 
        AcionamentoArameMaquina(true, true);
   }
   tempoGiroDecorrido = millis() - pega_millis;   
   if(millis() - pega_millis >= tempGiro){
        // Recua o Y a largura de um Fio      
        tempopPorFrisoDecorrido = (tempGiro/1000)*conta_fio_solda;
        conta_fio_solda++;        
        reset_tempo_chapisco=false;
    }     
    return conta_fio_solda;
} // fim move tocha
unsigned char oscila_tocha(const long int *contaPul_Y, bool restart){
   static unsigned long pega_millis = millis();
   static unsigned long tempo_decor = 0;
   if(!reset_tempo_chapisco){
     pega_millis = millis();   
     reset_tempo_chapisco=true;
   }    
   if(restart) {conta_fio_solda=1; return conta_fio_solda; reset_tempo_chapisco=false;}   
   if(contaPulsosY != PontoInicialSoldaY){
      driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, PontoInicialSoldaY, &contaPulsosY, &contaPulsosX); 
      if(parametro.HAB_OSCILACAO)
      driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, PontoFinalSoldaY, &contaPulsosY, &contaPulsosX);
      AcionamentoArameMaquina(true, true);  

   }

   if(millis() - pega_millis >= 1000){
       tempo_decor++;
       tempoGiroDecorrido = tempo_decor*1000;
       pega_millis = millis();         
   }
   
   if((tempo_decor*1000) >= tempGiro){
        // Recua o Y a largura de um Fio      
        tempopPorFrisoDecorrido=(tempGiro/1000)*conta_fio_solda;
        conta_fio_solda++;        
        reset_tempo_chapisco=false;
        tempo_decor=0;
    }     
    return conta_fio_solda;
} // fim oscila tocha
unsigned char movi_carrinho(const long int *contaPul_X, bool restart){
  if(restart) {conta_friso=1; return conta_friso; }
  passo_do_friso();
  conta_friso++;  
    if(Direcao_OPERACAO)
    conta_friso_para_posicao++;
    else
    conta_friso_para_posicao--;
  return conta_friso;
}
void passo_do_friso(){
  unsigned int passoFriso_move = parametro.DISTANCIA_ENTRE_FRISOS * parametro.PULSO_POL_X;
  if(Direcao_OPERACAO){
    driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_X, 'X', contaPulsosX, contaPulsosX+passoFriso_move, &contaPulsosY, &contaPulsosX);            
  }else{
    driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_X, 'X', contaPulsosX, contaPulsosX-passoFriso_move, &contaPulsosY, &contaPulsosX);            
  }
}
bool chapisco(){ 
  int passo_friso = parametro.PULSO_POL_X * parametro.DISTANCIA_ENTRE_FRISOS; 
  long int estremo_direito  =   passo_friso * (parametro.QTD_FRISOS-1);
  long int estremo_esquerdo =   passo_friso * (parametro.QTD_FRISOS-1)*(-1);
    
  if(conta_fio_solda <= parametro.FIO_SOLDA_POR_FRISO){ 
    // Pisiciona X na posição inicial se o mesmo estiver fora 
    if(!posiciona_eixo_x_uma_vez){    
      Posiciona_eixo_X();
      pararchapisco = true;
      posiciona_eixo_x_uma_vez = true;
    }else{
      conta_fio_solda = movi_tocha(&contaPulsosY, false);  
      pararchapisco = true;
    }             
  }else{ 
      AcionamentoArameMaquina(false, false);  
      // Zera contagem do fio de solda     
      conta_fio_solda = movi_tocha(&contaPulsosY, true);
      //Recua tocha para avança carrinhpo
      Recuatocha_para_mover_X();
      // Movimenta Carrinho        
      if(conta_friso < parametro.QTD_FRISOS){
          conta_friso = movi_carrinho(&contaPulsosX,false);
      }else if (Ciclo_de_chapisco < parametro.QTD_CICLO && (contaPulsosX == estremo_esquerdo || contaPulsosX == estremo_direito || contaPulsosX == 0)){ 
          Direcao_OPERACAO = !Direcao_OPERACAO;
          movi_carrinho(&contaPulsosX,false);
          conta_friso = movi_carrinho(&contaPulsosX,true)+1;
          Ciclo_de_chapisco++;
      }else{
        conta_friso = movi_carrinho(&contaPulsosX,true);
        STATUS_PROCESSO = "Chapisco Concluido";
        IniciarChapiscoIHM=false;
        Ciclo_de_chapisco = 1;
        conta_friso_para_posicao = 0;
        return true;
      }     
  }

  return false;
} // fim chapisco
bool Soldagem(){ 
  int passo_friso = parametro.PULSO_POL_X * parametro.DISTANCIA_ENTRE_FRISOS; 
  long int estremo_direito  =   passo_friso * (parametro.QTD_FRISOS-1);
  long int estremo_esquerdo =   passo_friso * (parametro.QTD_FRISOS-1)*(-1);
    
  if(conta_fio_solda <= 1){ 
    // Pisiciona X na posição inicial se o mesmo estiver fora 
    if(!posiciona_eixo_x_uma_vez){    
      Posiciona_eixo_X();
      pararchapisco = true;
      posiciona_eixo_x_uma_vez = true;
    }else{
      conta_fio_solda = oscila_tocha(&contaPulsosY, false);  
      pararchapisco = true;
    }             
  }else{ 
      AcionamentoArameMaquina(false, false);  
      // Zera contagem do fio de solda     
      conta_fio_solda = oscila_tocha(&contaPulsosY, true);
      //Recua tocha para avança carrinhpo
      Recuatocha_para_mover_X();
      // Movimenta Carrinho        
      if(conta_friso < parametro.QTD_FRISOS){
          conta_friso = movi_carrinho(&contaPulsosX,false);
      }else if (Ciclo_de_chapisco < parametro.QTD_CICLO  && (contaPulsosX == estremo_esquerdo || contaPulsosX == estremo_direito || contaPulsosX == 0)){ 
          Direcao_OPERACAO = !Direcao_OPERACAO;
          movi_carrinho(&contaPulsosX,false);
          conta_friso = movi_carrinho(&contaPulsosX,true)+1;
          Ciclo_de_chapisco++;
      }else{
        conta_friso = movi_carrinho(&contaPulsosX,true);
        STATUS_PROCESSO = "Chapisco Concluido";
        IniciarChapiscoIHM=false;
        Ciclo_de_chapisco = 1;
        conta_friso_para_posicao = 0;
        return true;
      }     
  }

  return false;
} // fim chapisco
void Posiciona_eixo_X(){
    Recuatocha_para_mover_X();
    passoFriso = parametro.DISTANCIA_ENTRE_FRISOS * parametro.PULSO_POL_X;    
    long int posicao_chapisco  = passoFriso*conta_friso_para_posicao;        
    driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_X, 'X', contaPulsosX, posicao_chapisco, &contaPulsosY, &contaPulsosX);            
}
bool Recuatocha_para_mover_X(){
      AcionamentoArameMaquina(false, false);       
      retorna_tocha_para_mover_x = true;
      reset_tempo_chapisco=false;
      rucuo_para_X = PontoFinalSoldaY-(parametro.RECUO_DO_Y_PARA_X * parametro.PULSO_MM_Y); 
      if(rucuo_para_X > 0)
        driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, rucuo_para_X, &contaPulsosY, &contaPulsosX);            
      else
        driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, 0, &contaPulsosY, &contaPulsosX);            
        retorna_tocha_para_mover_x=false;
    return true;
}
bool retorna_carrinho(){
  if(!(contaPulsosY <= rucuo_para_X || contaPulsosY == 0)){
      Recuatocha_para_mover_X();
  }
  if(contaPulsosX != 0){
    driverAutomatico(parametro.SPEED_AUTOMA, parametro.RAMPA_EIXO_X, 'X', contaPulsosX, 0, &contaPulsosY, &contaPulsosX);
    STATUS_PROCESSO = "Retornou Carrinho Pela IHM";
  }  
  if(contaPulsosX == 0)
      Retorna_carrino = false;
  return true;
}
