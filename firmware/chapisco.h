#ifndef __chapisco_h_
      #define __chapisco_h_
      #include "global.h"
void CalculaTempoGiro(const bool *HAB_DESAB_SENSOR_GIRO, const unsigned int *tempo_de_giro, const int *rpm_real, const unsigned char ParametroRPM);
unsigned char movi_tocha(const long int *contaPul_Y, bool restart);
unsigned char oscila_tocha(const long int *contaPul_Y, bool restart);
unsigned char movi_carrinho(const long int *contaPul_X, bool restart);
bool chapisco();
bool Soldagem();
bool Pararchapisco();
void passo_do_friso();
bool retorna_carrinho();
void AcionamentoArameMaquina(bool arame, bool maquina);
void Posiciona_eixo_X();
void Posiciona_soldagem_eixo_X();
bool reset_tempo_chapisco = false;
long int passoFriso = 0;
long int rucuo_para_X=0;
bool posiciona_eixo_x_uma_vez = false;


#endif
