

#ifndef __drivers_h_
      #define __drivers_h_
      #include "global.h"
      
  #define tempoMenorVelocidade  200 //Tempo em microsegundo de 10% da velocidade
  #define tempoMaiorVelocidade  20   //Tempo em microsegundo de 100% da velocidade 100 ficou bom
  #define E 2.71828182845904523536  //numero de Euler
  bool limites(bool direcao);
  void driver_modo_calibracao_Y(const bool avanca_recua, unsigned char rampa, const unsigned char speed_M, long int *contaPul_Y);
  void driver_modo_calibracao_X(const bool avanca_recua, unsigned char rampa, const unsigned char speed_M, long int *contaPul_X);
  void driver_manual_Y_mais (const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_Y);
  void driver_manual_Y_menos(const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_Y);
  void driver_manual_X_mais (const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_X);
  void driver_manual_X_menos(const bool *intertrava, const bool start_stop, const unsigned char speed_M, long int *contaPul_X);
  void posiciona_y();
  //========================== Driver Automatico ====================================
  
  void driverAutomatico(const unsigned int speed, unsigned char rampa, const char eixo, const long int posicao_atual, const long int onde_quero_chegar, long int *contaPul_Y, long int *contaPul_X);
  void saidaDriverY(unsigned int speed_mapeado);
  void saidaDriverX(unsigned int speed_mapeado);
  double calculo_do_instante(int i, double vetor_aceleracao, double declividade, double x_medio, double p_minimo, double amplitude);
  void Soldas(const unsigned int speed, unsigned char rampa, const char eixo, const long int posicao_atual, const long int onde_quero_chegar, long int *contaPul_Y, long int *contaPul_X);

#endif
