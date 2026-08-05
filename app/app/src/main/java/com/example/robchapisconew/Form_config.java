package com.example.robchapisconew;

import android.annotation.SuppressLint;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.example.robchapisconew.api.Config_Chapisco_Service;
import com.example.robchapisconew.model.SalvarConfig;

import org.jetbrains.annotations.NotNull;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class Form_config extends AppCompatActivity {

    private Retrofit retrofit;
    private EditText QTD_FRISOS;
    private EditText  FIO_SOLDA_POR_FRISO;
    private EditText  RPM_TAMBOR;
    private EditText  RECUO_DO_Y_PARA_X, RAMPA_EIXO_Y, RAMPA_EIXO_X, RAMPA_MANUAL, TEMPO_DE_GIRO, editQTD_CICLO;
    private EditText editPulsosPolegadas,editPulsosMilimetro, editPontoFinalAuto, editCursoMaximoTocha, editREDUCAO_SISTEMA;
    private TextView txtVelocidadeManual, txtVelocidadeAut;
    private SeekBar SeekManual, SeekAuto;
    private View layoutCursoMaximoTocha, layoutPontoFinalAuto, layoutPulsosMilimetro, layoutPulsosPolegadas,
            layoutRAMPA_EIXO_Y,layoutRAMPA_EIXO_X, layoutRAMPA_MANUAL,layoutRECUO_DO_Y_PARA_X,layoutTEMPO_DE_GIRO,
            layoutREDUCAO_SISTEMA,layoutQTD_CICLO;
    private RadioButton Radio1pol, Radio1_5pol, Radio2pol, Radio2_5pol, Radio3pol;
    @SuppressLint("UseSwitchCompatOrMaterialCode")
    private Switch Alimentador1, Alimentador2,Habcalibracao,HAB_sensor_giro,CHAPISCO_OU_SOLDA, HAB_OSCILACAO;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_form_config);

        layoutPulsosPolegadas = findViewById(R.id.layoutPulsosPolegadas);
        layoutPulsosMilimetro = findViewById(R.id.layoutPulsosMilimetro);
        layoutPontoFinalAuto = findViewById(R.id.layoutPontoFinalAuto);
        layoutCursoMaximoTocha = findViewById(R.id.layoutCursoMaximoTocha);
        layoutRAMPA_EIXO_Y = findViewById(R.id.layoutRAMPA_EIXO_Y);
        layoutRAMPA_EIXO_X = findViewById(R.id.layoutRAMPA_EIXO_X);
        layoutRAMPA_MANUAL = findViewById(R.id.layoutRAMPA_MANUAL);
        layoutTEMPO_DE_GIRO = findViewById(R.id.layoutTEMPO_DE_GIRO);
        layoutRECUO_DO_Y_PARA_X =  findViewById(R.id.layoutRECUO_DO_Y_PARA_X);
        layoutTEMPO_DE_GIRO  =  findViewById(R.id.layoutTEMPO_DE_GIRO);
        layoutREDUCAO_SISTEMA =  findViewById(R.id.layoutREDUCAO_SISTEMA);
        layoutQTD_CICLO =  findViewById(R.id.layoutQTD_CICLO);

        Radio1pol = findViewById(R.id.radio1pol);
        Radio1_5pol = findViewById(R.id.radio1_5pol);
        Radio2pol = findViewById(R.id.radio2pol);
        Radio2_5pol = findViewById(R.id.radio2_5pol);
        Radio3pol = findViewById(R.id.radio3pol);
        QTD_FRISOS = findViewById(R.id.editQTD_FRISOS);
        FIO_SOLDA_POR_FRISO = findViewById(R.id.editFIO_SOLDA_POR_FRISO);
        RPM_TAMBOR = findViewById(R.id.editRPM_TAMBOR);
        RECUO_DO_Y_PARA_X = findViewById(R.id.editRECUO_DO_Y_PARA_X);
        editPulsosPolegadas = findViewById(R.id.editPulsosPolegadas);
        editPulsosMilimetro = findViewById(R.id.editPulsosMilimetro);
        editPontoFinalAuto = findViewById(R.id.editPontoFinalAuto);
        editCursoMaximoTocha = findViewById(R.id.editCursoMaximoTocha);
        txtVelocidadeManual = findViewById(R.id.txtVelocidadeManual);
        txtVelocidadeAut = findViewById(R.id.txtVelocidadeAut);
        SeekAuto = findViewById(R.id.seekBarAuto);
        SeekManual = findViewById(R.id.seekBarSpeedManual);
        Alimentador1 = findViewById(R.id.alimentador1);
        Alimentador2 = findViewById(R.id.alimentador2);
        Habcalibracao = findViewById(R.id.habcalibraca);
        HAB_sensor_giro = findViewById(R.id.HAB_sensor_giro);
        RAMPA_EIXO_Y =  findViewById(R.id.editRAMPA_EIXO_Y);
        RAMPA_EIXO_X =  findViewById(R.id.editRAMPA_EIXO_X);
        RAMPA_MANUAL =  findViewById(R.id.editRAMPA_MANUAL);
        TEMPO_DE_GIRO =  findViewById(R.id.editTEMPO_DE_GIRO);
        CHAPISCO_OU_SOLDA = findViewById(R.id.CHAPISCO_OU_SOLDA);
        HAB_OSCILACAO = findViewById(R.id.HAB_OSCILACAO);
        editREDUCAO_SISTEMA = findViewById(R.id.editREDUCAO_SISTEMA);
        editQTD_CICLO = findViewById(R.id.editQTD_CICLO);


        SeekAuto.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @SuppressLint("SetTextI18n")
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                                          boolean fromUser) {
                txtVelocidadeAut.setText("Velocidade Automatico "+SeekAuto.getProgress()+"%");
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        SeekManual.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @SuppressLint("SetTextI18n")
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                                          boolean fromUser) {
                txtVelocidadeManual.setText("Velocidade Manual "+SeekManual.getProgress()+"%");
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        retrofit = new Retrofit.Builder()
                .baseUrl("http://192.168.4.1/")
                .addConverterFactory(GsonConverterFactory.create())
                .build();
    }
    // =================== Menus =================================
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.salvar, menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.sairesalvar) {
            Post_dados();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
    //=======================================================================
    private void getDadosEsp(){
        Config_Chapisco_Service Config = retrofit.create( Config_Chapisco_Service.class );
        Call<SalvarConfig> call = Config.RecuperaConfiguraoes();
        call.enqueue(new Callback<SalvarConfig>() {

            @SuppressLint("SetTextI18n")
            @Override
            public void onResponse(@NotNull Call<SalvarConfig> call, @NotNull Response<SalvarConfig> response) {
                if( response.isSuccessful() ){
                    SalvarConfig dados = response.body();
                    assert dados != null;
                    AtializaValores_form(dados);
                }
            }
            @Override
            public void onFailure(@NotNull Call<SalvarConfig> call, @NotNull Throwable t) {
                Toast.makeText(getApplicationContext(), "Sem Conexão",Toast.LENGTH_SHORT).show();
            }
        });
    }
    private void Post_dados(){
        Config_Chapisco_Service SalvaConfig = retrofit.create( Config_Chapisco_Service.class );
        Call<SalvarConfig> call;
        try {
            call = SalvaConfig.SalvaConfiguracoes(
                    passo_dofrisos(),
                    Integer.parseInt(QTD_FRISOS.getText().toString()),
                    Integer.parseInt(FIO_SOLDA_POR_FRISO.getText().toString()),
                    Integer.parseInt(RPM_TAMBOR.getText().toString()),
                    HAB_sensor_giro.isChecked(),
                    SeekManual.getProgress(),
                    SeekAuto.getProgress(),
                    Alimentador1.isChecked(),
                    Alimentador2.isChecked(),
                    Integer.parseInt(editPulsosPolegadas.getText().toString()),
                    Integer.parseInt(editPulsosMilimetro.getText().toString()),
                    Integer.parseInt(RECUO_DO_Y_PARA_X.getText().toString()),
                    Habcalibracao.isChecked(),
                    Integer.parseInt(editCursoMaximoTocha.getText().toString()),
                    Integer.parseInt(editPontoFinalAuto.getText().toString()),
                    Integer.parseInt(RAMPA_EIXO_Y.getText().toString()),
                    Integer.parseInt(RAMPA_EIXO_X.getText().toString()),
                    Integer.parseInt(RAMPA_MANUAL.getText().toString()),
                    Integer.parseInt(TEMPO_DE_GIRO.getText().toString()),
                    CHAPISCO_OU_SOLDA.isChecked(),
                    HAB_OSCILACAO.isChecked(),
                    Integer.parseInt(editREDUCAO_SISTEMA.getText().toString()),
                    Integer.parseInt(editQTD_CICLO.getText().toString())
            );
        } catch (NumberFormatException e) {
            Toast.makeText(getApplicationContext(), "Preencha todos os campos com números válidos", Toast.LENGTH_SHORT).show();
            return;
        }

        call.enqueue(new Callback<SalvarConfig>() {
            @SuppressLint("SetTextI18n")
            @Override
            public void onResponse(@NotNull Call<SalvarConfig> call, @NotNull Response<SalvarConfig> response) {
                if( response.isSuccessful() ){
                    SalvarConfig dados = response.body();
                    assert dados != null;
                    AtializaValores_form(dados);
                    Toast.makeText(getApplicationContext(), "Configurações Salvas",Toast.LENGTH_SHORT).show();


                }
            }
            @Override
            public void onFailure(@NotNull Call<SalvarConfig> call, @NotNull Throwable t) {
                Toast.makeText(getApplicationContext(), "Sem Conexão",Toast.LENGTH_SHORT).show();
            }
        });
    }
    void AtializaValores_form(SalvarConfig dados){

        if(dados.getDISTANCIA_ENTRE_FRISOS() == 1.5){
            Radio1_5pol.setChecked(true);
            Radio2pol.setChecked(false);
            Radio2_5pol.setChecked(false);
        }else if(dados.getDISTANCIA_ENTRE_FRISOS() == 2){
            Radio1_5pol.setChecked(false);
            Radio2pol.setChecked(true);
            Radio2_5pol.setChecked(false);
        }else if(dados.getDISTANCIA_ENTRE_FRISOS() == 2.5){
            Radio1_5pol.setChecked(false);
            Radio2pol.setChecked(false);
            Radio2_5pol.setChecked(true);
        }

        QTD_FRISOS.setText(String.valueOf(dados.getQTD_FRISOS()));
        FIO_SOLDA_POR_FRISO.setText(String.valueOf(dados.getFIO_SOLDA_POR_FRISO()));
        RPM_TAMBOR.setText(String.valueOf(dados.getRPM_TAMBOR()));
        RECUO_DO_Y_PARA_X.setText(String.valueOf(dados.getRECUO_DO_Y_PARA_X()));
        editPulsosPolegadas.setText(String.valueOf(dados.getPULSO_POL_X()));
        editPulsosMilimetro.setText(String.valueOf(dados.getPULSO_MM_Y()));
        editPontoFinalAuto.setText(String.valueOf(dados.getPONTO_FINAL_SOLDA_AUTO()));
        editCursoMaximoTocha.setText(String.valueOf(dados.getCURSO_MAX_TOCHA()));
        txtVelocidadeManual.setText("Velocidade Manual "+dados.getSPEED_MANUAL()+"%");
        txtVelocidadeAut.setText("Velocidade Automatico "+dados.getSPEED_AUTOMA()+"%");
        Alimentador1.setChecked(dados.isHAB_ALIMENTADOR_1());
        Alimentador2.setChecked(dados.isHAB_ALIMENTADOR_2());
        SeekManual.setProgress(dados.getSPEED_MANUAL());
        SeekAuto.setProgress(dados.getSPEED_AUTOMA());
        HAB_sensor_giro.setChecked(dados.isHAB_DESAB_SENSOR_GIRO());
        Habcalibracao.setChecked(dados.isMODO_CALIBRACAO());
        RAMPA_EIXO_Y.setText(String.valueOf(dados.getRAMPA_EIXO_Y()));
        RAMPA_EIXO_X.setText(String.valueOf(dados.getRAMPA_EIXO_X()));
        RAMPA_MANUAL.setText(String.valueOf(dados.getRAMPA_MANUAL()));
        TEMPO_DE_GIRO.setText(String.valueOf(dados.getTEMPO_DE_GIRO()));
        CHAPISCO_OU_SOLDA.setChecked(dados.isCHAPISCO_OU_SOLDA());
        HAB_OSCILACAO.setChecked(dados.isHAB_OSCILACAO());
        editREDUCAO_SISTEMA.setText(String.valueOf(dados.getREDUCAO_SISTEMA()));
        editQTD_CICLO.setText(String.valueOf(dados.getQTD_CICLO()));


        if(dados.isMODO_CALIBRACAO()){
            layoutPulsosPolegadas.setVisibility(View.VISIBLE);
            layoutPulsosMilimetro.setVisibility(View.VISIBLE);
            layoutPontoFinalAuto.setVisibility(View.VISIBLE);
            layoutCursoMaximoTocha.setVisibility(View.VISIBLE);
            layoutRAMPA_EIXO_Y.setVisibility(View.VISIBLE);
            layoutRAMPA_EIXO_X.setVisibility(View.VISIBLE);
            layoutRAMPA_MANUAL.setVisibility(View.VISIBLE);
            layoutRECUO_DO_Y_PARA_X.setVisibility(View.VISIBLE);
            layoutQTD_CICLO.setVisibility(View.VISIBLE);
        }else{
            layoutPulsosPolegadas.setVisibility(View.GONE);
            layoutPulsosMilimetro.setVisibility(View.GONE);
            layoutPontoFinalAuto.setVisibility(View.GONE);
            layoutCursoMaximoTocha.setVisibility(View.GONE);
            layoutRAMPA_EIXO_Y.setVisibility(View.GONE);
            layoutRAMPA_EIXO_X.setVisibility(View.GONE);
            layoutRAMPA_MANUAL.setVisibility(View.GONE);
            layoutRECUO_DO_Y_PARA_X.setVisibility(View.GONE);
            layoutQTD_CICLO.setVisibility(View.GONE);
        }

    }
double passo_dofrisos(){
        double passo =0.0;
    if(Radio1_5pol.isChecked()){
        passo = 1.5;
    }else if(Radio2pol.isChecked()){
        passo = 2.0;
    }else if(Radio2_5pol.isChecked()){
        passo = 2.5;
    }else{
        passo = 1.5;
    }
    return passo;
}
@Override
public void onResume() {
    getDadosEsp();

    super.onResume();
}

}

