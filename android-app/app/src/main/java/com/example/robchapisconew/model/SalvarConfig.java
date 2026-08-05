package com.example.robchapisconew.model;

// Modelo dos parâmetros de configuração do robô, espelhando a struct Parametros do
// firmware ESP32 — usado tanto para ler (GET) quanto para salvar (POST) via Retrofit.
public class SalvarConfig {
    double DISTANCIA_ENTRE_FRISOS;
    int QTD_FRISOS;
    int FIO_SOLDA_POR_FRISO;
    int RPM_TAMBOR;
    Boolean HAB_DESAB_SENSOR_GIRO;
    int SPEED_MANUAL;     // Valor de 0 a 100%
    int SPEED_AUTOMA;     // Valor de 0 a 100%
    Boolean HAB_ALIMENTADOR_1;
    Boolean HAB_ALIMENTADOR_2;
    Boolean MODO_CALIBRACAO;  //Não grava na eeprom
    int CURSO_MAX_TOCHA;
    int PONTO_FINAL_SOLDA_AUTO;     //Quando é gravado pela primeira vez o ponto inicial da solda grava o final auto
    // === Parametro não visivel para o operador ===
    int PULSO_POL_X; //Valor de pulsos
    int PULSO_MM_Y; //Valor de pulsos
    int RECUO_DO_Y_PARA_X;     //Recua o Y para mover o X por segurança, valor em mm
    int RAMPA_EIXO_Y;
    int RAMPA_EIXO_X;
    int RAMPA_MANUAL;
    int TEMPO_DE_GIRO;

    int REDUCAO_SISTEMA;

    Boolean CHAPISCO_OU_SOLDA;

    Boolean HAB_OSCILACAO;

    public int getQTD_CICLO() {
        return QTD_CICLO;
    }

    int QTD_CICLO;

    public int getRAMPA_EIXO_Y() {
        return RAMPA_EIXO_Y;
    }

    public int getRAMPA_EIXO_X() {
        return RAMPA_EIXO_X;
    }

    public int getRAMPA_MANUAL() {
        return RAMPA_MANUAL;
    }


    public double getDISTANCIA_ENTRE_FRISOS() {
        return DISTANCIA_ENTRE_FRISOS;
    }

    public int getQTD_FRISOS() {
        return QTD_FRISOS;
    }

    public int getFIO_SOLDA_POR_FRISO() {
        return FIO_SOLDA_POR_FRISO;
    }

    public int getRPM_TAMBOR() {
        return RPM_TAMBOR;
    }

    public boolean isHAB_DESAB_SENSOR_GIRO() {
        return HAB_DESAB_SENSOR_GIRO;
    }

    public int getSPEED_MANUAL() {
        return SPEED_MANUAL;
    }

    public int getSPEED_AUTOMA() {
        return SPEED_AUTOMA;
    }

    public boolean isHAB_ALIMENTADOR_1() {
        return HAB_ALIMENTADOR_1;
    }

    public boolean isHAB_ALIMENTADOR_2() {
        return HAB_ALIMENTADOR_2;
    }

    public int getPULSO_POL_X() {
        return PULSO_POL_X;
    }

    public int getPULSO_MM_Y() {
        return PULSO_MM_Y;
    }

    public int getRECUO_DO_Y_PARA_X() {
        return RECUO_DO_Y_PARA_X;
    }

    public boolean isMODO_CALIBRACAO() {
        return MODO_CALIBRACAO;
    }

    public int getCURSO_MAX_TOCHA() {
        return CURSO_MAX_TOCHA;
    }

    public int getPONTO_FINAL_SOLDA_AUTO() {
        return PONTO_FINAL_SOLDA_AUTO;
    }

    public int getTEMPO_DE_GIRO() {
        return TEMPO_DE_GIRO;
    }

    public boolean isCHAPISCO_OU_SOLDA() {
        return CHAPISCO_OU_SOLDA;
    }

    public boolean isHAB_OSCILACAO() {
        return HAB_OSCILACAO;
    }
    public int getREDUCAO_SISTEMA() {
        return REDUCAO_SISTEMA;
    }





}
