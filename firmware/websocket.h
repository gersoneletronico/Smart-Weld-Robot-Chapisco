#ifndef __websocket_H
      #define __websocket_H      
      #include "global.h"
      WebSocketsServer websockets(81);       
      unsigned long tenpor_messagen_ws = 0;
      unsigned long tenpor_messagen_ws_medidor = 0;
      uint8_t ID_Medidor_arame = 0;
      bool medidor_conectado = false;
      uint8_t ID_DA_IHM = 0;
      bool ihm_conectado = false;
      void reset_variaves_controle();
      String tratamentoString_P_IHM();
      void comandos(const int codigo);
      void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

#endif
