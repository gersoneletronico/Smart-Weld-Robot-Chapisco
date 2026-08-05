/*
Usando a biblioteca WebServer na versão 1.0 na pasta: C:\Users\G_Automation\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\libraries\WebServer 
Usando a biblioteca WiFi na versão 1.0 na pasta: C:\Users\G_Automation\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\libraries\WiFi 
Usando a biblioteca arduinoWebSockets-master na versão 2.3.5 na pasta: C:\Users\G_Automation\Documents\Arduino\libraries\arduinoWebSockets-master 
Usando a biblioteca WiFiClientSecure na versão 1.0 na pasta: C:\Users\G_Automation\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\libraries\WiFiClientSecure 
Usando a biblioteca ArduinoJson na versão 6.19.3 na pasta: C:\Users\G_Automation\Documents\Arduino\libraries\ArduinoJson 
Usando a biblioteca ESPmDNS na versão 1.0 na pasta: C:\Users\G_Automation\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\libraries\ESPmDNS 
Usando a biblioteca EEPROM na versão 1.0.3 na pasta: C:\Users\G_Automation\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\libraries\EEPROM 
Usando a biblioteca FS na versão 1.0 na pasta: C:\Users\G_Automation\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\libraries\FS 
*/

#ifndef __global_h_
      #define __global_h_      
#include <WebServer.h>
#include <WebSocketsServer.h> //https://github.com/Links2004/arduinoWebSockets
#include <ArduinoJson.h>      //https://arduinojson.org/?utm_source=meta&utm_medium=library.properties
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <math.h>
#include <EEPROM.h>
#include <ArduinoOTA.h>
  
// === Variaves manipulada pela função Driver ===
  long int contaPulsosY = 0;
  long int contaPulsosX = 0;
// === Variaveis manipulada pela função web socket ===
  boolean Driver_Y_Manualmais = false;
  boolean Driver_Y_Manualmenos = false;
  boolean Driver_X_Manualmais = false;
  boolean Driver_X_Manualmenos = false;
// === Variavel de controle ===
bool IniciarChapiscoIHM = false;
// === Variavel Leitura externa ===
float rpm = 0;
unsigned int tempo_de_giro = 0;

String dados_do_arame = "";

// === Variavel de Log IHM
String STATUS_PROCESSO = "";

// === Dados de Configuração Salvar Memoria eeprom ===
struct Parametros{
  float DISTANCIA_ENTRE_FRISOS              = 1.5;    //Valor de polegada
  unsigned char QTD_FRISOS                  = 45;
  unsigned char FIO_SOLDA_POR_FRISO         = 50;
  unsigned char RPM_TAMBOR                  = 5;  
  bool HAB_DESAB_SENSOR_GIRO                = false;
  unsigned char SPEED_MANUAL                = 13;     // Valor de 0 a 100%
  unsigned char SPEED_AUTOMA                = 13;     // Valor de 0 a 100%
  bool HAB_ALIMENTADOR_1                    = true;
  bool HAB_ALIMENTADOR_2                    = true;
  // === Parametro não visivel para o operador ===
  unsigned int PULSO_POL_X                  = 5338; //Valor de pulsos
  unsigned int PULSO_MM_Y                   = 215; //Valor de pulsos
  unsigned char RECUO_DO_Y_PARA_X           = 40;     //Recua o Y para mover o X por segurança, valor em mm
  bool MODO_CALIBRACAO                      = false;  //Não grava na eeprom
  unsigned char CURSO_MAX_TOCHA             = 210;
  unsigned char PONTO_FINAL_SOLDA_AUTO      = 10;     //Quando é gravado pela primeira vez o ponto inicial da solda grava o final auto
  unsigned char RAMPA_EIXO_Y                = 1;     //Rampa de 1 a 50%
  unsigned char RAMPA_EIXO_X                = 5;     //Rampa de 1 a 50%
  unsigned int RAMPA_MANUAL                 = 600;     //Rampa 0 a 1200
  unsigned int TEMPO_DE_GIRO                = 475;     //Seria 5 RPM
  bool CHAPISCO_OU_SOLDA                    = false;  //FALSO SERIA CHAPISCO
  bool HAB_OSCILACAO                        = false;  //Liga e desliga oscilação
  unsigned int REDUCAO_SISTEMA              = 5;     //Divide a rotação
  unsigned char QTD_CICLO                   = 2;
  
};
struct Parametros parametro;

bool controleDriverManual = false;

long int PontoInicialSoldaY = 0;
long int PontoFinalSoldaY = 0;
unsigned char Ciclo_de_chapisco = 1;
long int PontoFinalSoldaX = 0;
long int Largura_Fio_de_Solda = 0;

// ===== Variaves de comando driver ===
bool Move_tocha_ponto_final = false;
bool Move_tocha_ponto_inicial = false;
bool Retorna_carrino = false;
bool retorna_tocha_para_mover_x = false;

// ===== Variaves chapisco ========
int conta_friso = 1;
int conta_friso_para_posicao = 0;
int conta_fio_solda = 1;
bool Direcao_OPERACAO = true;
unsigned int tempGiro = 0;
bool pararchapisco = false;
unsigned long tempoGiroDecorrido = 0;
unsigned long tempopPorFrisoDecorrido = 0;
// ===== Variaves segurança ========
bool liberachapisco = false;
// ===== Variaves para entradas digitas ========

unsigned long tempo_anti_balse2 = 0;


//=============== Portas utilizadas =======================
#define DO_STEP_DRIVER_Y    23
#define DO_DIR_DRIVER_Y     22
#define DO_STEP_DRIVER_X    21
#define DO_DIR_DRIVER_X     19

#define DO_ARAME_1          18
#define DO_ARAME_2          5
#define DO_MAQ_1            17
#define DO_MAQ_2            16

#define DI_INICIA_PARA      32
#define DI_RETORNA_X        33  
#define FIM_DE_CURSO        34 // Sem pull-up/pull-down interno
#define SENSOR_GIRO         35 // Sem pull-up/pull-down interno
#define CW    true
#define CCW   false     
#define LED_PLACA      2
//=========================================================
// ============== Configuração dos GPIOs ==================
void Define_IO();
void OTA_WIFI();


void BTN_INICIAR_PARA();

#endif
