#include "eeeprom.h"

void primeira_leitura(struct Parametros *parametro){
  int address = 0;
  Serial.println("**Leitura EEPROM**");
  //================================================
  #define D DISTANCIA_ENTRE_FRISOS
  parametro->D = EEPROM.readFloat(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);  
  //================================================
  //================================================
  #define D QTD_FRISOS
  parametro->D = EEPROM.readUChar(address);  
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D FIO_SOLDA_POR_FRISO         
  parametro->D = EEPROM.readUChar(address);  
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D RPM_TAMBOR         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D HAB_DESAB_SENSOR_GIRO                         
  parametro->D = EEPROM.readBool(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D SPEED_MANUAL                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D SPEED_AUTOMA                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D HAB_ALIMENTADOR_1                                    
  parametro->D = EEPROM.readBool(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D HAB_ALIMENTADOR_2                                    
  parametro->D = EEPROM.readBool(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D PULSO_POL_X                         
  parametro->D = EEPROM.readUInt(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D PULSO_MM_Y                         
  parametro->D = EEPROM.readUInt(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D RECUO_DO_Y_PARA_X                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D CURSO_MAX_TOCHA                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D PONTO_FINAL_SOLDA_AUTO                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D RAMPA_EIXO_Y                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D RAMPA_EIXO_X                         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D RAMPA_MANUAL                         
  parametro->D = EEPROM.readUInt(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D TEMPO_DE_GIRO                         
  parametro->D = EEPROM.readUInt(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D CHAPISCO_OU_SOLDA                                    
  parametro->D = EEPROM.readBool(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D HAB_OSCILACAO                                    
  parametro->D = EEPROM.readBool(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D REDUCAO_SISTEMA                         
  parametro->D = EEPROM.readUInt(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  //================================================
  #define D QTD_CICLO         
  parametro->D = EEPROM.readUChar(address);
  Serial.println("Address: "+String(address)+"|| Valor: "+String(parametro->D));
  address += sizeof(parametro->D);
  //================================================
  Serial.println("================================");
  
}
int eeprom_automatica(struct Parametros *parametro){
  static bool HAB_LEITURA = EEPROM.readBool(500); //ESSE PARAMETRO DEVE SER SETADO PAR 1
  static bool flag = false;
  if(HAB_LEITURA && !flag){                //Só fais a leitura quando algum parametro for auterado
    primeira_leitura(parametro); 
    flag=true;   
  } 
  static struct Parametros parametrosInicias = *parametro;  //Recebe uma unica veiz na inicialização os valores dos parametros 
  int address = 0;
  //==============================================================
  #define D DISTANCIA_ENTRE_FRISOS                          //Pega nome do parametro 
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){  //Verifica se a variavel parametro foi alterada
    parametrosInicias.D = parametro->D;                     //Atualiza valor da variavel
    EEPROM.writeFloat(address, parametro->D);               //Grava na memoria eeprom
    Serial.println("   EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));//Emprime na serial
  }                                                         //Fim if
  address += sizeof(parametro->D);                                 //Atualiza para o proximo endereço
  //=============================================================
  #define D QTD_FRISOS
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);            //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  #define D FIO_SOLDA_POR_FRISO
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);             //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  #define D RPM_TAMBOR
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);              //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  #define D HAB_DESAB_SENSOR_GIRO
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeBool(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  #define D SPEED_MANUAL
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);             //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  #define D SPEED_AUTOMA                
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);              //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  #define D HAB_ALIMENTADOR_1                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeBool(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  #define D HAB_ALIMENTADOR_2                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeBool(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  #define D PULSO_POL_X                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUInt(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  #define D PULSO_MM_Y                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUInt(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  #define D RECUO_DO_Y_PARA_X                
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }  
  address += sizeof(parametro->D);
  //=============================================================
  #define D CURSO_MAX_TOCHA                
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }  
  address += sizeof(parametro->D);
  //=============================================================
  #define D PONTO_FINAL_SOLDA_AUTO                
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }  
  address += sizeof(parametro->D);
  //=============================================================
  #define D RAMPA_EIXO_Y                
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }  
  address += sizeof(parametro->D);
  //=============================================================
  #define D RAMPA_EIXO_X                
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }  
  address += sizeof(parametro->D);
  //=============================================================
  #define D RAMPA_MANUAL                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUInt(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  //=============================================================
  #define D TEMPO_DE_GIRO                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUInt(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  //=============================================================
  #define D CHAPISCO_OU_SOLDA
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeBool(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  //=============================================================
  #define D HAB_OSCILACAO
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeBool(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  //=============================================================
  #define D REDUCAO_SISTEMA                           
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUInt(address, parametro->D);               //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);
  //=============================================================
  //=============================================================
  #define D QTD_CICLO
  if(parametrosInicias.D != parametro->D || !HAB_LEITURA){
    parametrosInicias.D = parametro->D;
    EEPROM.writeUChar(address, parametro->D);            //Efetiva a gravação
    Serial.println("Gravado EEPROM Address: "+String(address)+"|| Valor: "+String(parametro->D));
  }
  address += sizeof(parametro->D);  
  //=============================================================
  if(!HAB_LEITURA){
    EEPROM.writeBool(500,true);
    EEPROM.commit();
    HAB_LEITURA=true;
  }
  EEPROM.commit();                         
  return address;
}
