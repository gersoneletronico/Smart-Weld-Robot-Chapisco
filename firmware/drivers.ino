// Controle de baixo nível dos motores de passo (eixos X/Y): geração de pulsos
// STEP/DIR, rampas de aceleração/desaceleração e limites de curso.
#include "drivers.h"


void posiciona_y(){
  static int contador = 0;
  int stepp = parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y;
  char buf[12];
  for(unsigned int i = 0; i < stepp; i++){
    snprintf(buf, sizeof(buf), "%u", i);
    websockets.sendTXT(0, buf);
    if(!digitalRead(FIM_DE_CURSO)) break;
    digitalWrite(DO_STEP_DRIVER_Y, HIGH);             
    delayMicroseconds(10);
    digitalWrite(DO_STEP_DRIVER_Y, LOW);                     
    delayMicroseconds(10); 
    contador++; 
  }
}
bool limites(bool direcao){
  bool retorno = false;
  if(!IniciarChapiscoIHM                &&
     !Move_tocha_ponto_inicial          && 
     !Move_tocha_ponto_final            && 
     !Retorna_carrino                   &&
     !retorna_tocha_para_mover_x        &&
     !((!direcao && (contaPulsosY <= 0)) ||
     ( direcao && (contaPulsosY >= (parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y))))
     ){
    retorno = true;
  }  return retorno;
}
//========================== Driver Modo Calibração ====================================
void driver_modo_calibracao_Y(const bool avanca_recua, unsigned char rampa, const unsigned char speed_M, long int *contaPul_Y){

  if(avanca_recua){    
    if(digitalRead(DO_DIR_DRIVER_Y) != true)  digitalWrite(DO_DIR_DRIVER_Y, true);    
  }else{    
    if(digitalRead(DO_DIR_DRIVER_Y) != false)  digitalWrite(DO_DIR_DRIVER_Y, false);
  }
  
  unsigned int step = 10*parametro.PULSO_MM_Y;
  unsigned int ramp = 0;
  unsigned int resto_da_divisao = 0;
  //============ Calculo de Rampa =======================
   if(step >= 100){
        if(step%100 == 0){                                      //Se não tiver resto da divisão
          ramp = (step/100)*rampa;
        }else{
          resto_da_divisao = step%100;
          ramp = ((step-resto_da_divisao)/100)*rampa;
        }
   }else{
        if(step%3 == 0){                                        //Se não tiver resto da divisão
          ramp = step/3;
        }else{
          resto_da_divisao = step%3;
          ramp = (step-resto_da_divisao)/3;
        }
   }
   if(ramp*2 > step){ ramp = step/3; } // Proteção contra overflow de unsigned int
  //=====================================================
  //Inicializa a variável estática com a velocidade passada
  static unsigned char sp_m = speed_M;
  //Define macro para não repetir código
  #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
  //Mapeamento para adequar os valores de microsegundo
  static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;

  for(unsigned int i = 0; i < ramp; i++){
      if(digitalRead(DO_DIR_DRIVER_Y)){
        if(*contaPul_Y >= (parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y)) break;
      }else{
        if(*contaPul_Y <= 0) break;
      }      
      saidaDriverY(speed_mapeado);                 
      delayMicroseconds(100); 
      digitalRead(DO_DIR_DRIVER_Y) ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;       
  }
  for(unsigned int i = 0; i < step - (ramp*2); i++){       
      if(digitalRead(DO_DIR_DRIVER_Y)){
        if(*contaPul_Y >= (parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y)) break;
      }else{
        if(*contaPul_Y <= 0) break;
      } 
      saidaDriverY(speed_mapeado);  
      digitalRead(DO_DIR_DRIVER_Y) ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
  }
  for(unsigned int i = 0; i < ramp; i++){ 
      if(digitalRead(DO_DIR_DRIVER_Y)){
        if(*contaPul_Y >= (parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y)) break;
      }else{
        if(*contaPul_Y <= 0) break;
      }       
      saidaDriverY(speed_mapeado);                      
      delayMicroseconds(100); 
      digitalRead(DO_DIR_DRIVER_Y) ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1; 
     
  }
}
void driver_modo_calibracao_X(const bool avanca_recua, unsigned char rampa, const unsigned char speed_M, long int *contaPul_X){
  if(avanca_recua){
    if(digitalRead(DO_DIR_DRIVER_X) != true)  digitalWrite(DO_DIR_DRIVER_X, true);
  }else{
    if(digitalRead(DO_DIR_DRIVER_X) != false)  digitalWrite(DO_DIR_DRIVER_X, false);
  }

  unsigned int step = parametro.DISTANCIA_ENTRE_FRISOS*parametro.PULSO_POL_X;
  unsigned int ramp = 0;
  unsigned int resto_da_divisao = 0;
  //============ Calculo de Rampa =======================
   if(step >= 100){
        if(step%100 == 0){                                      //Se não tiver resto da divisão
          ramp = (step/100)*rampa;
        }else{
          resto_da_divisao = step%100;
          ramp = ((step-resto_da_divisao)/100)*rampa;
        }
   }else{
        if(step%3 == 0){                                      //Se não tiver resto da divisão
          ramp = step/3;
        }else{
          resto_da_divisao = step%3;
          ramp = (step-resto_da_divisao)/3;
        }
   }
   if(ramp*2 > step){ ramp = step/3; } // Proteção contra overflow de unsigned int
  //Inicializa a variável estática com a velocidade passada
  static unsigned char sp_m = speed_M;
  //Define macro para não repetir código
  #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
  //Mapeamento para adequar os valores de microsegundo
  static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;

  for(unsigned int i = 0; i < ramp; i++){
      saidaDriverX(speed_mapeado);
      delayMicroseconds(100);
      digitalRead(DO_DIR_DRIVER_X) ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
  }
  for(unsigned int i = 0; i < step - (ramp*2); i++){
      saidaDriverX(speed_mapeado);
      digitalRead(DO_DIR_DRIVER_X) ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
  }
  for(unsigned int i = 0; i < ramp; i++){   
      saidaDriverX(speed_mapeado);                     
      delayMicroseconds(100);  
      digitalRead(DO_DIR_DRIVER_X) ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;         
  }    
}
//========================== Driver Manual ====================================
void driver_manual_Y_mais (const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_Y){
      if(*contaPul_Y >= (parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y)) return;

      static unsigned int rampaYMais = parametro.RAMPA_MANUAL;
     
      if(start_stop){
        // === Rampa inicial 
        if(rampaYMais > 0) rampaYMais--;
      }else{
        // === Rampa de parada       
        if(*intertrava){rampaYMais = parametro.RAMPA_MANUAL;} 
        if(rampaYMais < parametro.RAMPA_MANUAL) rampaYMais++; else return;
      }
      
      //Inicializa a variável estática com a velocidade passada 
      static unsigned char sp_m = speed_M; 
      //Define macro para não repetir código
      #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
      //Mapeamento para adequar os valores de microsegundo
      static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;
      //Se passado outro valor de velocidade atualiza speed_mapeado
      if(sp_m != speed_M){sp_m = speed_M; speed_mapeado = MACRO_MAPEMENTO_SPEED;}  
      if(digitalRead(DO_DIR_DRIVER_Y) != true)  digitalWrite(DO_DIR_DRIVER_Y, true);
        saidaDriverY(speed_mapeado);                  
        delayMicroseconds(rampaYMais);  
        *contaPul_Y = *contaPul_Y+1;                
}
void driver_manual_Y_menos(const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_Y){
      if(*contaPul_Y <= 0) return;
      static unsigned int rampaYMenos = parametro.RAMPA_MANUAL;     
      if(start_stop){
        // === Rampa inicial 
        if(rampaYMenos > 0) rampaYMenos--;
      }else{
        // === Rampa de parada       
        if(*intertrava){rampaYMenos = parametro.RAMPA_MANUAL;} 
        if(rampaYMenos < parametro.RAMPA_MANUAL) rampaYMenos++; else return;
      }         
      //Inicializa a variável estática com a velocidade passada 
      static unsigned char sp_m = speed_M; 
      //Define macro para não repetir código
      #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
      //Mapeamento para adequar os valores de microsegundo
      static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;
      //Se passado outro valor de velocidade atualiza speed_mapeado
      if(sp_m != speed_M){sp_m = speed_M; speed_mapeado = MACRO_MAPEMENTO_SPEED;}  
      if(digitalRead(DO_DIR_DRIVER_Y) != false)  digitalWrite(DO_DIR_DRIVER_Y, false);  
        saidaDriverY(speed_mapeado);                  
        delayMicroseconds(rampaYMenos);  
        *contaPul_Y = *contaPul_Y-1;   
            
}
void driver_manual_X_mais (const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_X){
      static unsigned int rampaXMais = parametro.RAMPA_MANUAL;
     
      if(start_stop){
        // === Rampa inicial 
        if(rampaXMais > 0) rampaXMais--;
      }else{
        // === Rampa de parada       
        if(*intertrava){rampaXMais = parametro.RAMPA_MANUAL;} 
        if(rampaXMais < parametro.RAMPA_MANUAL) rampaXMais++; else return;
      } 
      //Inicializa a variável estática com a velocidade passada 
      static unsigned char sp_m = speed_M; 
      //Define macro para não repetir código
      #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
      //Mapeamento para adequar os valores de microsegundo
      static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;
      //Se passado outro valor de velocidade atualiza speed_mapeado
      if(sp_m != speed_M){sp_m = speed_M; speed_mapeado = MACRO_MAPEMENTO_SPEED;}  
      if(digitalRead(DO_DIR_DRIVER_X) != true)  digitalWrite(DO_DIR_DRIVER_X, true);
          saidaDriverX(speed_mapeado);                  
          delayMicroseconds(rampaXMais);  
          *contaPul_X = *contaPul_X+1;            
}
void driver_manual_X_menos(const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_X){
      static unsigned int rampaXMenos = parametro.RAMPA_MANUAL;
      if(start_stop){
        // === Rampa inicial 
        if(rampaXMenos > 0) rampaXMenos--;
      }else{
        // === Rampa de parada       
        if(*intertrava){rampaXMenos = parametro.RAMPA_MANUAL;} 
        if(rampaXMenos < parametro.RAMPA_MANUAL) rampaXMenos++; else return;
      }     
      //Inicializa a variável estática com a velocidade passada 
      static unsigned char sp_m = speed_M; 
      //Define macro para não repetir código
      #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
      //Mapeamento para adequar os valores de microsegundo
      static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;
      //Se passado outro valor de velocidade atualiza speed_mapeado
      if(sp_m != speed_M){sp_m = speed_M; speed_mapeado = MACRO_MAPEMENTO_SPEED;}  
      if(digitalRead(DO_DIR_DRIVER_X) != false)  digitalWrite(DO_DIR_DRIVER_X, false);
      for(unsigned int i = 0; i < (parametro.DISTANCIA_ENTRE_FRISOS*parametro.PULSO_POL_X)/2; i++){ 
          saidaDriverX(speed_mapeado);                     
          delayMicroseconds(rampaXMenos);  
          *contaPul_X = *contaPul_X-1;  
           if(!parametro.MODO_CALIBRACAO)break;
      }        
             
}
//========================== Driver Automatico ====================================
void driverAutomatico(const unsigned int speed, unsigned char rampa, const char eixo,const long int posicao_atual, const long int onde_quero_chegar, long int *contaPul_Y, long int *contaPul_X)
{
  unsigned int ramp = 0;
  unsigned int resto_da_divisao = 0;
  unsigned int rampas = 0;  
  // Variáveis da função
  bool direcao = false;
  unsigned int step = 1;
  //Inicializa a variável estática com a velocidade passada 
  static unsigned int sp_m = speed; 
  //Define macro para não repetir código
  #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
  //Mapeamento para adequar os valores de microsegundo
  static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;
 //================ Calcula quantidade de pulso para mover p/ destino ============
  if(posicao_atual >= 0 && onde_quero_chegar >= 0){
    if(posicao_atual > onde_quero_chegar){
       step = (posicao_atual-onde_quero_chegar);
       direcao = false; goto movimentar;
    }else{
       step = (onde_quero_chegar-posicao_atual);
       direcao = true; goto movimentar;
    }    
  }else if(posicao_atual <= 0 && onde_quero_chegar <= 0){
    if(posicao_atual > onde_quero_chegar){
       step = ((onde_quero_chegar*(-1)) - (posicao_atual*(-1)));
       direcao = false; goto movimentar;
    }else{
       step = ((posicao_atual*(-1))-(onde_quero_chegar*(-1)));
       direcao = true; goto movimentar;
    }        
  }else if(posicao_atual >= 0 && onde_quero_chegar <= 0){
       step = posicao_atual-onde_quero_chegar;
       direcao = false; goto movimentar;
  }else if(posicao_atual <= 0 && onde_quero_chegar >= 0){
       step = onde_quero_chegar-posicao_atual;
       direcao = true;
  }                                                                                      
  movimentar:
  if(limites(direcao)) return; 


  //===============================================================================================
  //speed_mapeado = map(speed, 1, 100, 500, 50);
  //speed_mapeado = map(speed, 1, 100, 1000, 100);  
  //if(ramp*2 > step){ ramp = 0;}
  //============ Calculo de Rampa =======================
   if(step >= parametro.PULSO_MM_Y*(rampa*3)){
        ramp = parametro.PULSO_MM_Y*rampa;
        /*
        if(step%100 == 0){                                      //Se não tiver resto da divisão
          ramp = (step/100)*rampa;
        }else{
          resto_da_divisao = step%100;
          ramp = ((step-resto_da_divisao)/100)*rampa;
        }
        */
   }else{
        if(step%3 == 0){                                      //Se não tiver resto da divisão
          ramp = step/3;
        }else{
          resto_da_divisao = step%3;
          ramp = (step-resto_da_divisao)/3;
        }
   }
   // Proteção contra overflow de unsigned int em "step - (ramp*2)" caso a rampa calculada
   // seja maior que o próprio deslocamento (parametrização incoerente ou EEPROM corrompida).
   if(ramp*2 > step){ ramp = step/3; }

  //=====================================================
  if(eixo == 'y' || eixo == 'Y'){
        if(digitalRead(DO_DIR_DRIVER_Y) != direcao)  digitalWrite(DO_DIR_DRIVER_Y, direcao);
        if(sp_m != speed){sp_m = speed; speed_mapeado = MACRO_MAPEMENTO_SPEED;}
              rampas = ramp;
              //=== Rampa de aceleração =========
              for(unsigned int i = 0; i < ramp; i++){
                    if(limites(direcao)) break;
                    saidaDriverY(speed_mapeado);
                    delayMicroseconds(rampas);
                    rampas--;
                    direcao ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
              }
              //=== sem rampa ===
              for(unsigned int i = 0; i < step - (ramp * 2); i++){
                    if(limites(direcao)) break;
                    saidaDriverY(speed_mapeado);
                    direcao ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
              }
              rampas = ramp;
              //desacelera_e_para:
              // === rampa de desaceleração ===
              for(unsigned int i = 0; i < ramp; i++){
                    if(limites(direcao)) break;
                    saidaDriverY(speed_mapeado);
                    delayMicroseconds(rampas);
                    rampas--;
                    direcao ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
              }

  }else if(eixo == 'x' || eixo == 'X'){
    if(digitalRead(DO_DIR_DRIVER_X) != direcao)  digitalWrite(DO_DIR_DRIVER_X, direcao);
        if(sp_m != speed){sp_m = speed; speed_mapeado = MACRO_MAPEMENTO_SPEED;}
          rampas = ramp;
          //=== Rampa de aceleração =========
          for(unsigned int i = 0; i < ramp; i++){
                if(!IniciarChapiscoIHM  && !Retorna_carrino) break;
                saidaDriverX(speed_mapeado);
                delayMicroseconds(rampas);
                rampas--;
                direcao ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
          }
          //=== sem rampa ===
          for(unsigned int i = 0; i < step - (ramp * 2); i++){
                if(!IniciarChapiscoIHM && !Retorna_carrino) break;
                saidaDriverX(speed_mapeado);
                direcao ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
          }
          //desacelera_e_para_X:
          // === rampa de desaceleração ===
          rampas = ramp;
          for(unsigned int i = 0; i < ramp; i++){
                if(!IniciarChapiscoIHM && !Retorna_carrino) break;
                saidaDriverX(speed_mapeado);
                delayMicroseconds(rampas);
                rampas--;
                direcao ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
          }

  }
} // fim driverAutomatico
void Soldas(const unsigned int speed, unsigned char rampa, const char eixo,const long int posicao_atual, const long int onde_quero_chegar, long int *contaPul_Y, long int *contaPul_X)
{
  unsigned int ramp = 0;
  unsigned int resto_da_divisao = 0;
  unsigned int rampas = 0;  
  // Variáveis da função
  bool direcao = false;
  unsigned int step = 1;
  //Inicializa a variável estática com a velocidade passada 
  static unsigned int sp_m = speed; 
  //Define macro para não repetir código
  #define MACRO_MAPEMENTO_SPEED map(sp_m, 10, 100, tempoMenorVelocidade, tempoMaiorVelocidade)
  //Mapeamento para adequar os valores de microsegundo
  static unsigned int speed_mapeado = MACRO_MAPEMENTO_SPEED;
 //================ Calcula quantidade de pulso para mover p/ destino ============
  if(posicao_atual >= 0 && onde_quero_chegar >= 0){
    if(posicao_atual > onde_quero_chegar){
       step = (posicao_atual-onde_quero_chegar);
       direcao = false; goto movimentar;
    }else{
       step = (onde_quero_chegar-posicao_atual);
       direcao = true; goto movimentar;
    }    
  }else if(posicao_atual <= 0 && onde_quero_chegar <= 0){
    if(posicao_atual > onde_quero_chegar){
       step = ((onde_quero_chegar*(-1)) - (posicao_atual*(-1)));
       direcao = false; goto movimentar;
    }else{
       step = ((posicao_atual*(-1))-(onde_quero_chegar*(-1)));
       direcao = true; goto movimentar;
    }        
  }else if(posicao_atual >= 0 && onde_quero_chegar <= 0){
       step = posicao_atual-onde_quero_chegar;
       direcao = false; goto movimentar;
  }else if(posicao_atual <= 0 && onde_quero_chegar >= 0){
       step = onde_quero_chegar-posicao_atual;
       direcao = true;
  }                                                                                      
  movimentar:
  if(limites(direcao)) return; 
  //===============================================================================================
  //speed_mapeado = map(speed, 1, 100, 500, 50);
  //speed_mapeado = map(speed, 1, 100, 1000, 100);  
  //if(ramp*2 > step){ ramp = 0;}
  //============ Calculo de Rampa =======================
   if(step >= parametro.PULSO_MM_Y*(rampa*3)){
        ramp = parametro.PULSO_MM_Y*rampa;
        /*
        if(step%100 == 0){                                      //Se não tiver resto da divisão
          ramp = (step/100)*rampa;
        }else{
          resto_da_divisao = step%100;
          ramp = ((step-resto_da_divisao)/100)*rampa;
        }
        */
   }else{
        if(step%3 == 0){                                      //Se não tiver resto da divisão
          ramp = step/3;
        }else{
          resto_da_divisao = step%3;
          ramp = (step-resto_da_divisao)/3;
        }
   }
   // Proteção contra overflow de unsigned int em "step - (ramp*2)" (ver driverAutomatico)
   if(ramp*2 > step){ ramp = step/3; }

  //=====================================================
  if(eixo == 'y' || eixo == 'Y'){
        if(digitalRead(DO_DIR_DRIVER_Y) != direcao)  digitalWrite(DO_DIR_DRIVER_Y, direcao);
        if(sp_m != speed){sp_m = speed; speed_mapeado = MACRO_MAPEMENTO_SPEED;}
              rampas = ramp;
              //=== Rampa de aceleração =========
              for(unsigned int i = 0; i < ramp; i++){
                    if(limites(direcao)) break;
                    saidaDriverY(speed_mapeado);
                    delayMicroseconds(rampas);
                    rampas--;
                    direcao ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
              }
              //=== sem rampa ===
              for(unsigned int i = 0; i < step - (ramp * 2); i++){
                    if(limites(direcao)) break;
                    saidaDriverY(speed_mapeado);
                    direcao ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
              }
              rampas = ramp;
              //desacelera_e_para:
              // === rampa de desaceleração ===
              for(unsigned int i = 0; i < ramp; i++){
                    if(limites(direcao)) break;
                    saidaDriverY(speed_mapeado);
                    delayMicroseconds(rampas);
                    rampas--;
                    direcao ? *contaPul_Y = *contaPul_Y+1 : *contaPul_Y = *contaPul_Y-1;
              }

  }else if(eixo == 'x' || eixo == 'X'){
    if(digitalRead(DO_DIR_DRIVER_X) != direcao)  digitalWrite(DO_DIR_DRIVER_X, direcao);
        if(sp_m != speed){sp_m = speed; speed_mapeado = MACRO_MAPEMENTO_SPEED;}
          rampas = ramp;
          //=== Rampa de aceleração =========
          for(unsigned int i = 0; i < ramp; i++){
                if(!IniciarChapiscoIHM  && !Retorna_carrino) break;
                saidaDriverX(speed_mapeado);
                delayMicroseconds(rampas);
                rampas--;
                direcao ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
          }
          //=== sem rampa ===
          for(unsigned int i = 0; i < step - (ramp * 2); i++){
                if(!IniciarChapiscoIHM && !Retorna_carrino) break;
                saidaDriverX(speed_mapeado);
                direcao ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
          }
          //desacelera_e_para_X:
          // === rampa de desaceleração ===
          rampas = ramp;
          for(unsigned int i = 0; i < ramp; i++){
                if(!IniciarChapiscoIHM && !Retorna_carrino) break;
                saidaDriverX(speed_mapeado);
                delayMicroseconds(rampas);
                rampas--;
                direcao ? *contaPul_X = *contaPul_X+1 : *contaPul_X = *contaPul_X-1;
          }

  }
} // fim Soldas
void saidaDriverY(unsigned int speed_mapeado){
    digitalWrite(DO_STEP_DRIVER_Y, HIGH);             
    delayMicroseconds(speed_mapeado);
    digitalWrite(DO_STEP_DRIVER_Y, LOW);                     
    delayMicroseconds(speed_mapeado);
}
void saidaDriverX(unsigned int speed_mapeado){
    digitalWrite(DO_STEP_DRIVER_X, HIGH);             
    delayMicroseconds(speed_mapeado);
    digitalWrite(DO_STEP_DRIVER_X, LOW);                     
    delayMicroseconds(speed_mapeado);
}
void saidaDriverX(unsigned int speed_mapeado, double instante){
    digitalWrite(DO_STEP_DRIVER_X, HIGH);             
    delayMicroseconds(speed_mapeado);
    digitalWrite(DO_STEP_DRIVER_X, LOW);                     
    delayMicroseconds(instante);
}
//Função necessária para calcular o período do passo do motor a cada iteração do loop (for)
double calculo_do_instante(int i, double vetor_aceleracao, double declividade, double p_minimo, double amplitude){
  double x_medio = ((-1)*log( amplitude / ((800*0.99999) - p_minimo) -1)) / declividade;
  double instante = ( amplitude / ( 1 + pow( E , (vetor_aceleracao * (declividade * (i - x_medio) ) ) ) ) ) + p_minimo;
  return instante;
  
}
