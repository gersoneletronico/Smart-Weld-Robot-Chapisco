#include "global.h"

void Define_IO(){
    // Saidas para o driver
    pinMode(DO_STEP_DRIVER_Y,         OUTPUT);
    pinMode(DO_DIR_DRIVER_Y,          OUTPUT);
    pinMode(DO_STEP_DRIVER_X,         OUTPUT);
    pinMode(DO_DIR_DRIVER_X,          OUTPUT);
    // Saidas a relé
    pinMode(DO_ARAME_1,               OUTPUT);
    pinMode(DO_ARAME_2,               OUTPUT);
    pinMode(DO_MAQ_1,                 OUTPUT);
    pinMode(DO_MAQ_2,                 OUTPUT);
    // Desliga todas saidas por  segurança
    digitalWrite(DO_STEP_DRIVER_Y,       LOW);
    digitalWrite(DO_DIR_DRIVER_Y,        LOW);
    digitalWrite(DO_STEP_DRIVER_X,       LOW);
    digitalWrite(DO_DIR_DRIVER_X,        LOW);
    
    digitalWrite(DO_ARAME_1,             LOW);
    digitalWrite(DO_ARAME_2,             LOW);
    digitalWrite(DO_MAQ_1,               LOW);
    digitalWrite(DO_MAQ_2,               LOW);
    // Entradas foto acopladas
    pinMode(DI_INICIA_PARA,     INPUT_PULLUP);
    pinMode(DI_RETORNA_X,       INPUT_PULLUP);   
    pinMode(FIM_DE_CURSO,       INPUT); // Sem pull-up/pull-down interno
    pinMode(SENSOR_GIRO,        INPUT); // Sem pull-up/pull-down interno  
    pinMode(LED_PLACA,        OUTPUT);
}
void OTA_WIFI(){
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void BTN_INICIAR_PARA(){
      static bool flag01 = false;
      static unsigned long base_tempo = 0;   
      //============ Logica Botão DI_INICIA_PARA =============================================
    // === Botão inicia/parar/Retorna Chapisco  quando pressionado e pressionando por 2s========
    if (!digitalRead(DI_INICIA_PARA) && flag01) { // Botão Pressionado
      // si pressionado por 2s retorna carrinho
      if(millis() - base_tempo >= 50) {
          //Retorna_carrino=true;
          //STATUS_PROCESSO = "Retornou Pelo Botão Local";
          if(PontoInicialSoldaY != 0 && PontoInicialSoldaY > PontoFinalSoldaY){
            IniciarChapiscoIHM = !IniciarChapiscoIHM;
            IniciarChapiscoIHM ? STATUS_PROCESSO = "Iniciou Pelo Botão Local" : STATUS_PROCESSO = "Parou Pelo Botão Local";
          }
          flag01 = false;
      }   
    }
    
    // === Botão inicia/parar/Retorna Chapisco quando solto ========
    if (digitalRead(DI_INICIA_PARA) && !flag01) {
      base_tempo = millis();
      flag01 = true;
    }

}//fim da função BTN_INICIAR_PARA()
