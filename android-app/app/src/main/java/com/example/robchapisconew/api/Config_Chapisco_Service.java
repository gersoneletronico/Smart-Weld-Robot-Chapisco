package com.example.robchapisconew.api;

import com.example.robchapisconew.model.SalvarConfig;


import retrofit2.Call;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.GET;
import retrofit2.http.POST;

// Endpoints Retrofit do servidor HTTP do ESP32 (porta 80) para ler e salvar
// os parâmetros de configuração do robô.
public interface Config_Chapisco_Service {
    @GET("config")
    Call<SalvarConfig> RecuperaConfiguraoes();

    @FormUrlEncoded
   @POST("config")
    Call<SalvarConfig> SalvaConfiguracoes(
            @Field("DISTANCIA_ENTRE_FRISOS") double DISTANCIA_ENTRE_FRISOS,
            @Field("QTD_FRISOS") int QTD_FRISOS,
            @Field("FIO_SOLDA_POR_FRISO") int FIO_SOLDA_POR_FRISO,
            @Field("RPM_TAMBOR") int RPM_TAMBOR,
            @Field("HAB_DESAB_SENSOR_GIRO") Boolean HAB_DESAB_SENSOR_GIRO,
            @Field("SPEED_MANUAL") int SPEED_MANUAL,
            @Field("SPEED_AUTOMA") int SPEED_AUTOMA,
            @Field("HAB_ALIMENTADOR_1") Boolean HAB_ALIMENTADOR_1,
            @Field("HAB_ALIMENTADOR_2") Boolean HAB_ALIMENTADOR_2,
            @Field("PULSO_POL_X") int PULSO_POL_X,
            @Field("PULSO_MM_Y") int PULSO_MM_Y,
            @Field("RECUO_DO_Y_PARA_X") int RECUO_DO_Y_PARA_X,
            @Field("MODO_CALIBRACAO") Boolean MODO_CALIBRACAO,
            @Field("CURSO_MAX_TOCHA") int CURSO_MAX_TOCHA,
            @Field("PONTO_FINAL_SOLDA_AUTO") int PONTO_FINAL_SOLDA_AUTO,
            @Field("RAMPA_EIXO_Y") int RAMPA_EIXO_Y,
            @Field("RAMPA_EIXO_X") int RAMPA_EIXO_X,
            @Field("RAMPA_MANUAL") int RAMPA_MANUAL,
            @Field("TEMPO_DE_GIRO") int TEMPO_DE_GIRO,
            @Field("CHAPISCO_OU_SOLDA") Boolean CHAPISCO_OU_SOLDA,
            @Field("HAB_OSCILACAO") Boolean HAB_OSCILACAO,
            @Field("REDUCAO_SISTEMA") int REDUCAO_SISTEMA,
            @Field("QTD_CICLO") int QTD_CICLO
    );

}
