#ifndef __web_serve_h_
      #define __web_serve_h_ 
      #include "global.h"  
      #include "parametrizacao.h"    
      const char *ssid = "Robô Chapisco";
      const char *password = "Wura1013";
      WebServer server(80);
      void postDados();
      void getDados();
      void Inicia_Servidor();
#endif
