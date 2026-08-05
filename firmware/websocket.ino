#include "websocket.h"
#include "parametrizacao.h"

String tratamentoString_P_IHM(){
  // Monta a string em um buffer fixo (em vez de concatenar objetos String em série),
  // evitando fragmentação de heap nesta função que roda a cada ~100ms continuamente.
  static char buf[220];
  int n = snprintf(buf, sizeof(buf),
            "%.2f:%.2f:%.2f:%.2f:%u de %u:%.2f:%d:%d:%u:%d:%u:%d:%u:%.2f:%.2f:%d:%lu:%u:%.2f:%d:%.2f:%.2f:%.2f:%s:",
            (float) contaPulsosY/parametro.PULSO_MM_Y,                    // Dados[0]
            (float) contaPulsosX/parametro.PULSO_POL_X,                   // Dados[1]
            (float) PontoInicialSoldaY/parametro.PULSO_MM_Y,              // Dados[2]
            (float) PontoFinalSoldaY/parametro.PULSO_MM_Y,                // Dados[3]
            (unsigned int) Ciclo_de_chapisco, (unsigned int) parametro.QTD_CICLO, // Dados[4]
            (float) PontoFinalSoldaX/parametro.PULSO_POL_X,               // Dados[5]
            (int) IniciarChapiscoIHM,                                     // Dados[6]
            (int) Direcao_OPERACAO,                                       // Dados[7]
            (unsigned int)(tempGiro/1000),                                // Dados[8]
            conta_fio_solda,                                              // Dados[9]
            (unsigned int) parametro.FIO_SOLDA_POR_FRISO,                 // Dados[10]
            conta_friso,                                                  // Dados[11]
            (unsigned int) parametro.QTD_FRISOS,                          // Dados[12]
            (float) Largura_Fio_de_Solda/parametro.PULSO_MM_Y,            // Dados[13]
            (float) (PontoInicialSoldaY-PontoFinalSoldaY)/parametro.PULSO_MM_Y, // Dados[14]
            (int) liberachapisco,                                         // Dados[15]
            (unsigned long)(tempoGiroDecorrido/1000),                     // Dados[16]
            (unsigned int) parametro.RPM_TAMBOR,                          // Dados[17]
            (float) rpm,                                                  // Dados[18]
            (int) parametro.HAB_DESAB_SENSOR_GIRO,                        // Dados[19]
            (float) tempopPorFrisoDecorrido/60,                           // Dados[20]
            (float) (tempopPorFrisoDecorrido*conta_friso)/60,             // Dados[21]
            (float) parametro.DISTANCIA_ENTRE_FRISOS,                     // Dados[22]
            STATUS_PROCESSO.c_str()                                       // Dados[23]
  );
  String resultado = String(buf) + dados_do_arame; //Dados[24] ,Dados[25] ,Dados[26] ,Dados[27] ,Dados[28] ,Dados[29]
  return resultado;
}

void reset_variaves_controle()
{
    Driver_Y_Manualmais  = false;
    Driver_Y_Manualmenos = false;
    Driver_X_Manualmais  = false;
    Driver_X_Manualmenos = false;
}

void comandos(const int codigo)
{    
    static long int pulsos = contaPulsosX;
    switch(codigo){
        case   1: 
          Driver_Y_Manualmais  = true;
          
    break;
        case   2: 
          Driver_Y_Manualmais  = false;
          if(IniciarChapiscoIHM){
              PontoInicialSoldaY = PontoInicialSoldaY+parametro.PULSO_MM_Y;
              PontoFinalSoldaY=PontoFinalSoldaY+parametro.PULSO_MM_Y;
          }
    break;
        case   3: 
          Driver_Y_Manualmenos  = true;
    break;
        case   4: 
          Driver_Y_Manualmenos  = false;  
          if(IniciarChapiscoIHM){
              PontoFinalSoldaY=PontoFinalSoldaY-parametro.PULSO_MM_Y;
             PontoInicialSoldaY = PontoInicialSoldaY-parametro.PULSO_MM_Y;
          }
    break;
        case   5: 
        if(IniciarChapiscoIHM && !parametro.HAB_OSCILACAO)
          Driver_X_Manualmais  = true;    

        if(!IniciarChapiscoIHM)
           Driver_X_Manualmais  = true;
         
    break;
        case   6: 
        Driver_X_Manualmais  = false; 
        if(IniciarChapiscoIHM && !parametro.HAB_OSCILACAO){
           //delay(10);
           Gravainicial(&contaPulsosY,&contaPulsosX,&PontoInicialSoldaY,&PontoFinalSoldaY);
        }             
    break;
        case   7: 
        if(IniciarChapiscoIHM && !parametro.HAB_OSCILACAO)
          Driver_X_Manualmenos  = true;
        if(!IniciarChapiscoIHM)
          Driver_X_Manualmenos  = true;
    break;
        case   8: 
          Driver_X_Manualmenos  = false; 
        if(IniciarChapiscoIHM && !parametro.HAB_OSCILACAO){
           //delay(10);
           Gravainicial(&contaPulsosY,&contaPulsosX,&PontoInicialSoldaY,&PontoFinalSoldaY);
        }  
    break;     
        case   9: 
          IniciarChapiscoIHM  = !IniciarChapiscoIHM;   
          IniciarChapiscoIHM ? STATUS_PROCESSO = "Iniciou Chapisco pela IHM" : STATUS_PROCESSO = "Parou Chapisco pela IHM";
    break; 
        case   10: 
          IniciarChapiscoIHM  = false;   
          STATUS_PROCESSO = "Parou Chapisco pela IHM";
    break;       
        case   11: 
         //if(!IniciarChapiscoIHM)
           Direcao_OPERACAO = !Direcao_OPERACAO;
    break;
        case   12: 
          Retorna_carrino=true;
          STATUS_PROCESSO = "Retorna Carrinho pela IHM";
    break;
        case   13: 
        if(parametro.HAB_ALIMENTADOR_1)
        digitalWrite(DO_ARAME_1, HIGH);
    break;
        case   14: 
        digitalWrite(DO_ARAME_1, LOW);
    break;
        case   15: 
        if(parametro.HAB_ALIMENTADOR_2)
        digitalWrite(DO_ARAME_2, HIGH);
    break;
        case   16: 
        digitalWrite(DO_ARAME_2, LOW);
    break;
    case   17:
        if(!IniciarChapiscoIHM){
            PontoInicialSoldaY = 0;
            PontoFinalSoldaY = 0; 
            conta_fio_solda=1;
        }            
    break;
    case   18: 

    break;
    case   19: 
      if(!parametro.MODO_CALIBRACAO && !parametro.HAB_OSCILACAO){
         Gravainicial(&contaPulsosY,&contaPulsosX,&PontoInicialSoldaY,&PontoFinalSoldaY);
      }else if(!parametro.MODO_CALIBRACAO){
         Gravainicial(&contaPulsosY,&contaPulsosX,&PontoInicialSoldaY,&PontoFinalSoldaY);
      }      
    break; 
    case   20: 
      if(!parametro.MODO_CALIBRACAO)
      Gravafinal(&contaPulsosY,&PontoInicialSoldaY,&PontoFinalSoldaY);
    break;    
    case   21: 
      Move_tocha_ponto_inicial = true;
    break; 
    case   22: 
      Move_tocha_ponto_final = true;
    break;  
        case   23: 
        if(parametro.HAB_ALIMENTADOR_1){
          digitalWrite(DO_ARAME_1, HIGH);
          digitalWrite(DO_MAQ_1, HIGH);
        }        
    break;
        case   24: 
        digitalWrite(DO_ARAME_1, LOW);
        digitalWrite(DO_MAQ_1, LOW);
    break;
        case   25: 
        if(parametro.HAB_ALIMENTADOR_2){
        digitalWrite(DO_ARAME_2, HIGH);
        digitalWrite(DO_MAQ_2, HIGH);
        }
    break;
        case   26: 
        digitalWrite(DO_ARAME_2, LOW);
        digitalWrite(DO_MAQ_2, LOW);
    break;    

    }
}// end comando    

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{ 
    static IPAddress ip;
    static String Dados_Str = ""; 
    static int codigo = 0;
  
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            ip = websockets.remoteIP(num); 
            reset_variaves_controle();
            if(ip[3] == 10){
              medidor_conectado = false;
            }else{
              ihm_conectado = false;
            }
        
            break;
        case WStype_CONNECTED:      
        {
            ip = websockets.remoteIP(num);            
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            // send message to client
            if(ip[3] == 10){
             ID_Medidor_arame = num; 
             medidor_conectado = true;            
             websockets.sendTXT(num, "Connected");
             Serial.println("Medidor conectado");
            }else{
             ID_DA_IHM = num;
             websockets.sendTXT(ID_DA_IHM, "conectado_ao_servidor_robo");             
             Serial.println("IHM conectada");
             ihm_conectado = true;             
             }             
       
        }              
            break;
        case WStype_TEXT:
            Serial.printf("[%u] String recebida: %s\n", num, payload);
            Dados_Str = String((char*)(payload));
            if(num == ID_DA_IHM && ihm_conectado){
                codigo = Dados_Str.toInt(); 
                if(codigo > 0 && codigo < 100){
                  comandos(codigo);
                }else if (codigo != 0){
                  reset_variaves_controle();  
                  Serial.println("codigo > 0 && codigo < 100: "+String(codigo));
                }
            }else if(num == ID_Medidor_arame && medidor_conectado){
                dados_do_arame = Dados_Str;
                Serial.println(dados_do_arame);
            }
          
           break;  
        case WStype_BIN:
            Serial.printf("get binary length: %u\n", length);
            
				break;
		case WStype_ERROR:	reset_variaves_controle(); Serial.println("WStype_ERROR"); break;              		
		case WStype_FRAGMENT_TEXT_START:	reset_variaves_controle(); Serial.println("WStype_FRAGMENT_TEXT_START"); break;
		case WStype_FRAGMENT_BIN_START:	reset_variaves_controle(); Serial.println("WStype_FRAGMENT_BIN_START"); break;
		case WStype_FRAGMENT:	reset_variaves_controle(); Serial.println("WStype_FRAGMENT"); break;
		case WStype_FRAGMENT_FIN:	reset_variaves_controle();  Serial.println("WStype_FRAGMENT_FIN"); break; 
    default:
          //reset_variaves_controle();
    break;    
    }// end switch
  } // Fim da função webSocketEvent
    
