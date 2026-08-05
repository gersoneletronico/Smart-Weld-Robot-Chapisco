package com.example.robchapisconew.model;

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



//    public SalvarConfig(
//            double DISTANCIA_ENTRE_FRISOS,
//            int QTD_FRISOS,
//            int FIO_SOLDA_POR_FRISO,
//            int RPM_TAMBOR,
//            boolean HAB_DESAB_SENSOR_GIRO,
//            int SPEED_MANUAL,
//            int SPEED_AUTOMA,
//            boolean HAB_ALIMENTADOR_1,
//            boolean HAB_ALIMENTADOR_2,
//            int PULSO_POL_X,
//            int PULSO_MM_Y,
//            int RECUO_DO_Y_PARA_X,
//            boolean MODO_CALIBRACAO,
//            int CURSO_MAX_TOCHA,
//            int PONTO_FINAL_SOLDA_AUTO
//    ) {
//        this.DISTANCIA_ENTRE_FRISOS = DISTANCIA_ENTRE_FRISOS;
//        this.QTD_FRISOS = QTD_FRISOS;
//        this.FIO_SOLDA_POR_FRISO = FIO_SOLDA_POR_FRISO;
//        this.RPM_TAMBOR = RPM_TAMBOR;
//        this.HAB_DESAB_SENSOR_GIRO = HAB_DESAB_SENSOR_GIRO;
//        this.SPEED_MANUAL = SPEED_MANUAL;
//        this.SPEED_AUTOMA = SPEED_AUTOMA;
//        this.HAB_ALIMENTADOR_1 = HAB_ALIMENTADOR_1;
//        this.HAB_ALIMENTADOR_2 = HAB_ALIMENTADOR_2;
//        this.PULSO_POL_X = PULSO_POL_X;
//        this.PULSO_MM_Y = PULSO_MM_Y;
//        this.RECUO_DO_Y_PARA_X = RECUO_DO_Y_PARA_X;
//        this.MODO_CALIBRACAO = MODO_CALIBRACAO;
//        this.CURSO_MAX_TOCHA = CURSO_MAX_TOCHA;
//        this.PONTO_FINAL_SOLDA_AUTO = PONTO_FINAL_SOLDA_AUTO;
//    }


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
