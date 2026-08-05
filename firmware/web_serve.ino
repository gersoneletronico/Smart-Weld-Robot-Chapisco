#include "web_serve.h"


void postDados() {     
      DynamicJsonDocument doc(1024);
      //==========================================================================================
      String S = "DISTANCIA_ENTRE_FRISOS";          // String nome do argumento
      #define D DISTANCIA_ENTRE_FRISOS              // difine D para substituir 
      String s = server.arg(S);                     // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        float f = s.toFloat();                      // Conversão
        if(f >= 1.00 && f <= 3.00)                  // Define o faixa de valor 
        parametro.D = f;                            // Atribui os valores
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "QTD_FRISOS";                             // String nome do argumento
      #define D QTD_FRISOS                          // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char uc = s.toInt();               // Conversão
        if(uc >= 1 && uc <= 50)                     // Define o faixa de valor 
        parametro.D = uc;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "FIO_SOLDA_POR_FRISO";                    // String nome do argumento
      #define D FIO_SOLDA_POR_FRISO                 // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char fs = s.toInt();               // Conversão
        if(fs >= 2 && fs <= 80)                     // Define o faixa de valor 
        parametro.D = fs;                           // Atualiza o valor da variavel
        calcula_largura_fio_solda();
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "RPM_TAMBOR";                             // String nome do argumento
      #define D RPM_TAMBOR                          // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char rp = s.toInt();               // Conversão
        if(rp >= 1 && rp <= 30)                     // Define o faixa de valor 
        parametro.D = rp;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "HAB_DESAB_SENSOR_GIRO";                  // String nome do argumento
      #define D HAB_DESAB_SENSOR_GIRO               // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
         if(s == "false")                                 // Define o faixa de valor 
        parametro.D = false;                        // Atualiza o valor da variavel
        else if (s == "true")
        parametro.D = true;                        // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "SPEED_MANUAL";                           // String nome do argumento
      #define D SPEED_MANUAL                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char sm = s.toInt();               // Conversão
        if(sm >= 10 && sm <= 100)                   // Define o faixa de valor 
        parametro.D = sm;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "SPEED_AUTOMA";                           // String nome do argumento
      #define D SPEED_AUTOMA                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char sa = s.toInt();               // Conversão
        if(sa >= 10 && sa <= 100)                   // Define o faixa de valor 
        parametro.D = sa;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "HAB_ALIMENTADOR_1";                      // String nome do argumento
      #define D HAB_ALIMENTADOR_1                   // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        if(s == "false")                                 // Define o faixa de valor 
        parametro.D = false;                        // Atualiza o valor da variavel
        else if (s == "true")
        parametro.D = true;                        // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "HAB_ALIMENTADOR_2";                      // String nome do argumento
      #define D HAB_ALIMENTADOR_2                   // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
         if(s == "false")                                 // Define o faixa de valor 
        parametro.D = false;                        // Atualiza o valor da variavel
        else if (s == "true")
        parametro.D = true;                        // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "PULSO_POL_X";                           // String nome do argumento
      #define D PULSO_POL_X                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned int po = s.toInt();               // Conversão
        if(po >= 10 && po <= 100000)                // Define o faixa de valor 
        parametro.D = po;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "PULSO_MM_Y";                           // String nome do argumento
      #define D PULSO_MM_Y                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned int mm = s.toInt();               // Conversão
        if(mm >= 10 && mm <= 100000)                   // Define o faixa de valor 
        parametro.D = mm;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "RECUO_DO_Y_PARA_X";                           // String nome do argumento
      #define D RECUO_DO_Y_PARA_X                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char xy = s.toInt();               // Conversão
        if(xy >= 10 && xy <= 80)                    // Define o faixa de valor 
        parametro.D = xy;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "MODO_CALIBRACAO";                        // String nome do argumento
      #define D MODO_CALIBRACAO                     // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
         if(s == "false")                           // Define o faixa de valor 
        parametro.D = false;                        // Atualiza o valor da variavel
        else if (
            s == "true"                                                        &&
            //contaPulsosY >= (parametro.CURSO_MAX_TOCHA*parametro.PULSO_MM_Y)/2 &&
            contaPulsosX == 0                                                  &&
            PontoInicialSoldaY == 0                                            &&
            !IniciarChapiscoIHM
          )
        parametro.D = true;                         // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "CURSO_MAX_TOCHA";                        // String nome do argumento
      #define D CURSO_MAX_TOCHA                     // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char cm = s.toInt();               // Conversão
        if(cm >= 50 && cm <= 250)                    // Define o faixa de valor 
        parametro.D = cm;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "PONTO_FINAL_SOLDA_AUTO";                        // String nome do argumento
      #define D PONTO_FINAL_SOLDA_AUTO                     // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char pa = s.toInt();               // Conversão
        if(pa >= 5 && pa <= 15)                    // Define o faixa de valor 
        parametro.D = pa;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "RAMPA_EIXO_Y";                           // String nome do argumento
      #define D RAMPA_EIXO_Y                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char rtd = s.toInt();               // Conversão
        if(rtd >= 1 && rtd <= 50)                     // Define o faixa de valor 
        parametro.D = rtd;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "RAMPA_EIXO_X";                           // String nome do argumento
      #define D RAMPA_EIXO_X                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char gtf = s.toInt();               // Conversão
        if(gtf >= 1 && gtf <= 50)                     // Define o faixa de valor 
        parametro.D = gtf;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "RAMPA_MANUAL";                           // String nome do argumento
      #define D RAMPA_MANUAL                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned int sdf = s.toInt();               // Conversão
        if(sdf >= 100 && sdf <= 1200)                   // Define o faixa de valor 
        parametro.D = sdf;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "TEMPO_DE_GIRO";                           // String nome do argumento
      #define D TEMPO_DE_GIRO                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned int fdds = s.toInt();               // Conversão
        if(fdds >= 5 && fdds <= 10000)                // Define o faixa de valor 
        parametro.D = fdds;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      S = "CHAPISCO_OU_SOLDA";                      // String nome do argumento
      #define D CHAPISCO_OU_SOLDA                   // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
         if(s == "false")                                 // Define o faixa de valor 
        parametro.D = false;                        // Atualiza o valor da variavel
        else if (s == "true")
        parametro.D = true;                        // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      //==========================================================================================
      S = "HAB_OSCILACAO";                          // String nome do argumento
      #define D HAB_OSCILACAO                       // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
         if(s == "false")                           // Define o faixa de valor 
        parametro.D = false;                        // Atualiza o valor da variavel
        else if (s == "true")
        parametro.D = true;                         // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      //==========================================================================================
      S = "REDUCAO_SISTEMA";                           // String nome do argumento
      #define D REDUCAO_SISTEMA                        // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned int dfds = s.toInt();               // Conversão
        if(dfds >= 1 && dfds <= 200)                  // Define o faixa de valor 
        parametro.D = dfds;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
      //==========================================================================================
      S = "QTD_CICLO";                             // String nome do argumento
      #define D QTD_CICLO                          // difine D para substituir 
      s = server.arg(S);                            // Ler o argumento do post
      if(s != "" && s != String(parametro.D)){      // Verifica se o valor e null ou diferente
        unsigned char dfd = s.toInt();               // Conversão
        if(dfd >= 1 && dfd <= 8)                     // Define o faixa de valor 
        parametro.D = dfd;                           // Atualiza o valor da variavel
      }
      doc[S] = parametro.D;                         // Retorna o valor do argumeto
      //==========================================================================================
 
      String buf;
      serializeJson(doc, buf);
      server.send(200, F("application/json"), buf);    
        
}// Fim da função postDados
void getDados() {
      DynamicJsonDocument doc(1024);
      doc[F("DISTANCIA_ENTRE_FRISOS")] = parametro.DISTANCIA_ENTRE_FRISOS;
      doc[F("QTD_FRISOS")]             = parametro.QTD_FRISOS;
      doc[F("FIO_SOLDA_POR_FRISO")]    = parametro.FIO_SOLDA_POR_FRISO;
      doc[F("RPM_TAMBOR")]             = parametro.RPM_TAMBOR;
      doc[F("HAB_DESAB_SENSOR_GIRO")]  = parametro.HAB_DESAB_SENSOR_GIRO;
      doc[F("SPEED_MANUAL")]           = parametro.SPEED_MANUAL;
      doc[F("SPEED_AUTOMA")]           = parametro.SPEED_AUTOMA; 
      doc[F("HAB_ALIMENTADOR_1")]      = parametro.HAB_ALIMENTADOR_1;
      doc[F("HAB_ALIMENTADOR_2")]      = parametro.HAB_ALIMENTADOR_2; 
      doc[F("PULSO_POL_X")]            = parametro.PULSO_POL_X;
      doc[F("PULSO_MM_Y")]             = parametro.PULSO_MM_Y;       
      doc[F("RECUO_DO_Y_PARA_X")]      = parametro.RECUO_DO_Y_PARA_X;
      doc[F("MODO_CALIBRACAO")]        = parametro.MODO_CALIBRACAO;  
      doc[F("CURSO_MAX_TOCHA")]        = parametro.CURSO_MAX_TOCHA;
      doc[F("PONTO_FINAL_SOLDA_AUTO")] = parametro.PONTO_FINAL_SOLDA_AUTO;
      doc[F("RAMPA_EIXO_Y")]           = parametro.RAMPA_EIXO_Y;
      doc[F("RAMPA_EIXO_X")]           = parametro.RAMPA_EIXO_X;
      doc[F("RAMPA_MANUAL")]           = parametro.RAMPA_MANUAL;
      doc[F("TEMPO_DE_GIRO")]          = parametro.TEMPO_DE_GIRO;
      doc[F("CHAPISCO_OU_SOLDA")]      = parametro.CHAPISCO_OU_SOLDA;
      doc[F("HAB_OSCILACAO")]          = parametro.HAB_OSCILACAO;
      doc[F("REDUCAO_SISTEMA")]        = parametro.REDUCAO_SISTEMA;
      doc[F("QTD_CICLO")]              = parametro.QTD_CICLO;
      

      Serial.println("Chamando GET");
  
       String buf;
      serializeJson(doc, buf);
      server.send(200, F("application/json"), buf);
}// Fim da função getDados
void Inicia_Servidor() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"),
        F("Welcome ao Melhor Robo de chapisco do mundo"));
    });
    server.on(F("/getdados"),     getDados);
    server.on(F("/config"),         postDados);
    // server.on(F("/gravainicial"), Gravainicial);
    //server.on(F("/gravafinal"),   Gravafinal);
    //server.on(F("/controle"),     Controle);
    // Iniciando servidor
    server.begin();   
}// Fim da função Inicia_Servidor
