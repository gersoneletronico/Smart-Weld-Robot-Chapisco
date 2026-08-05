// Sketch principal: setup(), loop() e as tasks FreeRTOS do WebSocket e do servidor HTTP.
#include "global.h"
#include "eeeprom.h"
#include "drivers.h"
#include "web_serve.h"
#include "websocket.h"
#include "chapisco.h"



// *************** Controle Manual *************
void controle_manual() {
  unsigned char sp_man = parametro.SPEED_MANUAL;
  //===============================Driver_Y_Manualmais=========================
  if(parametro.MODO_CALIBRACAO){
    if (Driver_Y_Manualmais){
        driver_modo_calibracao_Y(true, parametro.RAMPA_EIXO_Y, sp_man, &contaPulsosY);
        Driver_Y_Manualmais=false;
    } 
    if (Driver_Y_Manualmenos){
        driver_modo_calibracao_Y(false, parametro.RAMPA_EIXO_Y, sp_man, &contaPulsosY);
        Driver_Y_Manualmenos=false;
    } 
    if (Driver_X_Manualmais){
        driver_modo_calibracao_X(true, parametro.RAMPA_EIXO_X, sp_man, &contaPulsosX);
        Driver_X_Manualmais=false;
    } 
    if (Driver_X_Manualmenos){
        driver_modo_calibracao_X(false, parametro.RAMPA_EIXO_X, sp_man, &contaPulsosX);
        Driver_X_Manualmenos=false;
    }     
  
  }else{

    if (Driver_Y_Manualmais) {
      Driver_Y_Manualmenos = false;      
      driver_manual_Y_mais(&Driver_Y_Manualmenos, true, sp_man, &contaPulsosY);
    } else {
      driver_manual_Y_mais(&Driver_Y_Manualmenos, false, sp_man, &contaPulsosY);
    }
    //===============================Driver_Y_Manualmenos=========================
    if (Driver_Y_Manualmenos) {
      Driver_Y_Manualmais = false;
      driver_manual_Y_menos(&Driver_Y_Manualmais, true, sp_man, &contaPulsosY);
    } else {
      driver_manual_Y_menos(&Driver_Y_Manualmais, false, sp_man, &contaPulsosY);
    }
    //===============================Driver_X_Manualmais=========================
    if (Driver_X_Manualmais) {
      Driver_X_Manualmenos = false;
      driver_manual_X_mais(&Driver_X_Manualmenos, true, sp_man, &contaPulsosX);
    } else {
      driver_manual_X_mais(&Driver_X_Manualmenos, false, sp_man, &contaPulsosX);
    }
    //===============================Driver_X_Manualmenos=========================
    if (Driver_X_Manualmenos) {
      Driver_X_Manualmais = false;
      driver_manual_X_menos(&Driver_X_Manualmais, true, sp_man, &contaPulsosX);
    } else {
      driver_manual_X_menos(&Driver_X_Manualmais, false, sp_man, &contaPulsosX);
    }
  }  
}  // end controle_manual
// *************** Task servidor web para app *************
void Task_servidor(void *parameter) {
  while (true) {
    //Serial.println(contaPulsosY);
    //Serial.println(contaPulsosX);
    //Serial.println(websockets.connectedClients()); // Quantidade de clientes
    server.handleClient();          //WiFi.softAPgetStationNum();
    eeprom_automatica(&parametro);  //grava parametros inicias
    //ArduinoOTA.handle();
    delay(1);
  }
}
void Task_websockets(void *parameter) {
  bool flagSensorGiro = 0;
  volatile byte pulsos = 0;
  unsigned long timeold = 0;
  //Altere o numero abaixo de acordo com o seu disco encoder
  unsigned int pulsos_por_volta = 8;

  
  while (true) {  // Loop infinito da tasck
    // inicializa loop do websocket
    websockets.loop();  //Servidor websocket
    //========== Envio de mensagems IHM ============
      if (millis() - tenpor_messagen_ws >= 100) {
          String ST_SOCKET = tratamentoString_P_IHM();

          if(ihm_conectado)
            websockets.sendTXT(ID_DA_IHM, ST_SOCKET);
            
        tenpor_messagen_ws = millis();
      }
      //========== Envio de mensagems medidor ============
      if (millis() - tenpor_messagen_ws_medidor >= 1000) {

          if(medidor_conectado && ID_Medidor_arame != ID_DA_IHM)
            websockets.sendTXT(ID_Medidor_arame, "Check");
            
        tenpor_messagen_ws_medidor = millis();
      }
    BTN_INICIAR_PARA();
    if (!digitalRead(DI_RETORNA_X)){
      if(!IniciarChapiscoIHM){
        Retorna_carrino=true;  
        STATUS_PROCESSO = "Retornou Pelo Botão Local"; 
      }        
    }

    
    
    //=====================================================================================================
    //=== Sensore de giro ==============================
    if (digitalRead(SENSOR_GIRO)) {
      flagSensorGiro = 0;
    }
    if (!digitalRead(SENSOR_GIRO) && !flagSensorGiro) {
      pulsos++;
      flagSensorGiro = 1;
    }
    const int tempo_amostrar = 5000;
    if (millis() - timeold >= tempo_amostrar) {
      if(pulsos != 0)
      tempo_de_giro = ((tempo_amostrar/pulsos) * pulsos_por_volta)*parametro.REDUCAO_SISTEMA;
      else      
      tempo_de_giro = 0;
      float rp = (60 * 1000 / pulsos_por_volta) / tempo_amostrar * pulsos;      
      //if (rp <= 50)  // limita em 50RPM a leitura
      rpm = rp;
      timeold = millis();
      pulsos = 0; 
    }  //end if
    CalculaTempoGiro(&parametro.HAB_DESAB_SENSOR_GIRO, &tempo_de_giro, &rpm, parametro.RPM_TAMBOR);
    //=====================================================
    delay(1);
  }  //end while
}
// *************** Setup do projeto *************
void setup() {

  WiFi.softAP(ssid, password);         // Inicia wifi em modo AP
  Serial.begin(115200);                // Inicia porta serial para debang
  Define_IO();                         // Inicia Configuração dos GPIOs
  EEPROM.begin(512);                   // Inicializa lib eeprom
  if(!digitalRead(DI_RETORNA_X)){
    EEPROM.write(500, 0);
    digitalWrite(LED_PLACA, HIGH);
    EEPROM.commit();
    delay(2000);
    digitalWrite(LED_PLACA, LOW);
  }
  eeprom_automatica(&parametro);       // eeprom_automaticaGrava parametros inicias
  Inicia_Servidor();                   // Inicializa servidor WEB
  websockets.begin();                  // Inicia Servidor Web Socket
  websockets.onEvent(webSocketEvent);  // Inicia callback  
  /* 
      * Quando for gravar em um esp que ja foi 
      * utilizado em outros projetos descomenta 
      * na primeira gravação
    */
        //for(int i = 0; i < 512; i++)  {
        //  EEPROM.write(i, 0);
        //}
        //  EEPROM.commit();
  xTaskCreate(Task_websockets, "Task_websockets", 10000, NULL, 1, NULL);
  delay(100);
  xTaskCreate(Task_servidor, "Task_servidor", 10000, NULL, 1, NULL);
  delay(100);


  
 // posiciona_y();                       // Posiciona tocha em 0
    //OTA_WIFI();
}  // End Setup
// *************** Funções *************
void Move_Tocha_Ponto_inicial(){
    if(Move_tocha_ponto_inicial){
      driverAutomatico(parametro.SPEED_MANUAL, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, PontoInicialSoldaY, &contaPulsosY, &contaPulsosX);
      Move_tocha_ponto_inicial=false;
    }
} // end Move_Tocha_ponto_inicial
void Move_Tocha_Ponto_final(){
    if(Move_tocha_ponto_final){
      driverAutomatico(parametro.SPEED_MANUAL, parametro.RAMPA_EIXO_Y, 'Y', contaPulsosY, PontoFinalSoldaY, &contaPulsosY, &contaPulsosX);
      Move_tocha_ponto_final=false;
    }
} // end Move_tocha_ponto_final
void Chapiscar(){
    static bool conclusao_chapisco = false;
    if(IniciarChapiscoIHM){ 
      if(parametro.CHAPISCO_OU_SOLDA){
        conclusao_chapisco = Soldagem(); 
      }else{
        conclusao_chapisco = chapisco();
      }     
    }else{  // Chapico Parado
      posiciona_eixo_x_uma_vez = false;            
  
      if(pararchapisco){
        Recuatocha_para_mover_X();
        pararchapisco = false;
      }  
      if(Retorna_carrino){
        retorna_carrinho();        
      } 
      Move_Tocha_Ponto_inicial();
      Move_Tocha_Ponto_final();
      controle_manual();  
    }   
    if(IniciarChapiscoIHM && !parametro.HAB_OSCILACAO) 
    controle_manual(); 
}
// *************** Loop do projeto *************
void loop() {   
  Chapiscar(); 
}  // End loop
