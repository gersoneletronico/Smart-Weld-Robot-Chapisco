package com.example.robchapisconew;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Color;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.concurrent.atomic.AtomicBoolean;

import tech.gusavila92.websocketclient.WebSocketClient;

public class MainActivity extends AppCompatActivity {
    boolean desabilitaclickGravaInicial = false, desabilitaclickGravaFinal = false;
    boolean retorno_do_alerta;
    String OPERACAO_DIR;
    private boolean Pontons_Gravados = false;
    private WebSocketClient webSocketClient;
    boolean conectou_medidor;
    private String Valor = "0";
    private String ValorInicial = "0";
    private String ValorFinal = "0";
    private SeekBar seekBarArame1,seekBarArame2;
    private LinearLayout layout_medidor, layout_botoes_de_controle, Layout_opraracao, Layout_rpm, layout_pussos, layout_informacoes;
    protected Button Ymais,Ymenos,Xmais,Xmenos,btngravainicio,
            btngravafinal,btnIniciar, botao_grande_parar_chapisco,
            btnretornarX,btnArame1,btnArame2,Maquina_arame1,Maquina_arame2;
    private TextView txtStepsY, txtStepsX, txtVelocidadeArame1, txtVelocidadeArame2, txtRPM_tambor;
    private TextView txtPulsosY, txtFiosdesolda, txtPulsosX, txtFrisosSoladados, txtLarguraFio,
            txtTempoGiro, txtCiclo_chapisco, txtPontoInicialY,
            txtTempoPorFriso, txtTempoTotal, txtTamanhoChapisco,
            txtStatus;
    //=================== Alimentadores ==========================
    private TextView txt_velocidade_arame_1, txt_velocidade_arame_2, txt_volume_arame_1, txt_volume_arame_2, txt_compri_arame_1, txt_compri_arame_2;
    //===============================================================
    private boolean StatusChapisco = false;
    private boolean auxiliar_1  = false, auxiliar_2  = false;

    String Passo_do_friso;
    @SuppressLint("UseSwitchCompatOrMaterialCode")
    private Switch SWdirecaodeoperaco;
    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Ymais = findViewById(R.id.btnYmais);
        Ymenos = findViewById(R.id.btnYmenos);
        Xmais = findViewById(R.id.btnXmais);
        Xmenos = findViewById(R.id.btnXmenos);
        btngravainicio = findViewById(R.id.btnGravarInicio);
        btngravafinal = findViewById(R.id.btnGravarFinal);
        txtStepsY = findViewById(R.id.txtStepsY);
        txtStepsX = findViewById(R.id.txtStepsX);
        btnIniciar = findViewById(R.id.btnIniciar);
        btnIniciar.setVisibility(View.INVISIBLE);
        btnArame1 = findViewById(R.id.btnArame1);
        btnArame2 = findViewById(R.id.btnArame2);
        Maquina_arame1 = findViewById(R.id.Maquina_arame1);
        Maquina_arame2 = findViewById(R.id.Maquina_arame2);
        SWdirecaodeoperaco = findViewById(R.id.sw);
        btnretornarX = findViewById(R.id.btnretornarX);
        btnretornarX.setVisibility(View.INVISIBLE);
        seekBarArame1 = findViewById(R.id.seekBarArame1);
        seekBarArame2 = findViewById(R.id.seekBarArame2);
        txtRPM_tambor = findViewById(R.id.txtRPM_tambor);
        txtVelocidadeArame1 = findViewById(R.id.txtVelocidadeArame1);
        txtVelocidadeArame2 = findViewById(R.id.txtVelocidadeArame2);

        txtPulsosY = findViewById(R.id.txtPulsosY);
        txtPontoInicialY = findViewById(R.id.txtPontoInicialY);
        txtTamanhoChapisco = findViewById(R.id.txtLarguradochapisco);
        txtFiosdesolda = findViewById(R.id.txtFiosdesolda);
        txtPulsosX = findViewById(R.id.txtPulsosX);
        txtFrisosSoladados = findViewById(R.id.txtFrisosSoladados);
        txtLarguraFio = findViewById(R.id.txtLarguraFio);
        txtTempoGiro = findViewById(R.id.txtTempoGiro);
        txtCiclo_chapisco = findViewById(R.id.txtCiclo_chapisco);
        txtTempoPorFriso = findViewById(R.id.txtTempoPorFriso);
        txtTempoTotal = findViewById(R.id.txtTempoTotal);
        txtStatus = findViewById(R.id.txtStatus);

        botao_grande_parar_chapisco = findViewById(R.id.btn_iniciar_para);
        layout_botoes_de_controle = findViewById(R.id.layout_boteos_controle);
        Layout_opraracao = findViewById(R.id.Layout_opraracao);
        Layout_rpm = findViewById(R.id.Layout_rpm);
        layout_pussos = findViewById(R.id.layout_pussos);
        layout_informacoes = findViewById(R.id.layout_informacoes);

        //=================== Alimentadores ==========================
        txt_velocidade_arame_1 = findViewById(R.id.txt_velocidade_arame_1);
        txt_velocidade_arame_2 = findViewById(R.id.txt_velocidade_arame_2);
        txt_volume_arame_1 = findViewById(R.id.txt_volume_arame_1);
        txt_volume_arame_2 = findViewById(R.id.txt_volume_arame_2);
        txt_compri_arame_1 = findViewById(R.id.txt_compri_arame_1);
        txt_compri_arame_2 = findViewById(R.id.txt_compri_arame_2);
        //=============================================================================

        layout_medidor = findViewById(R.id.layout_medidor);
        layout_medidor.setVisibility(View.GONE);

        botao_grande_parar_chapisco.setVisibility(View.GONE);
        // Ao pressionar por um tempo é gravado ponto inicil da solda
        btngravainicio.setOnLongClickListener(v -> {
            desabilitaclickGravaInicial=true;
            if(!StatusChapisco)
            webSocketClient.send("19");
            return false;
        });
        // Ao pressionar por um tempo é gravado ponto final da solda
        btngravafinal.setOnLongClickListener(v -> {
            desabilitaclickGravaFinal=true;
            if(!StatusChapisco)
            webSocketClient.send("20");
            return false;
        });
        // se estiver gravado ponto inicial libera para movimentar em um click
        btngravainicio.setOnClickListener(v -> {
            if(Pontons_Gravados && !desabilitaclickGravaInicial)
                webSocketClient.send("21");
            desabilitaclickGravaInicial=false;
        });
        // se estiver gravado ponto inicial libera para movimentar em um click
        btngravafinal.setOnClickListener(v -> {
            if(Pontons_Gravados && !desabilitaclickGravaFinal)
                webSocketClient.send("22");
            desabilitaclickGravaFinal=false;
        });
        // BOTÃO MAIS Y ==============
        Ymais.setOnTouchListener((view, motionEvent) -> {
            Log.d("TAG", "onCreateView: "+motionEvent);
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    if(!StatusChapisco)
                        webSocketClient.send("1");
                    break;
                case MotionEvent.ACTION_UP:
                    if(StatusChapisco){
                        webSocketClient.send("2");
                    }else{
                        webSocketClient.send("2");
                    }
                    break;
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("2");
                    break;
            }
            return false;
        });

        // ============================
        // BOTÃO MENOS Y ==============

        // BOTÃO MAIS Y ==============
        Ymenos.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    if(!StatusChapisco)
                        webSocketClient.send("3");
                    break;
                case MotionEvent.ACTION_UP:
                    if(StatusChapisco){
                        webSocketClient.send("4");
                    }else{
                        webSocketClient.send("4");
                    }
                    break;
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("4");
                    break;
            }
            return false;
        });

        // =============================

        // BOTÃO MAIS X ==============
        Xmais.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    if(true)
                        webSocketClient.send("5");
                    break;
                case MotionEvent.ACTION_UP:
                    if(StatusChapisco){
                        webSocketClient.send("6");
                    }else{
                        webSocketClient.send("6");
                    }
                    break;
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("6");
                    break;
            }
            return false;
        });
        // =============================
        // BOTÃO MENOS X ==============
        Xmenos.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    if(true)
                        webSocketClient.send("7");
                    break;
                case MotionEvent.ACTION_UP:
                    if(StatusChapisco){
                        webSocketClient.send("8");
                    }else{
                        webSocketClient.send("8");
                    }
                    break;
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("8");
                    break;
            }
            return false;
        });
        // ==============================
        btnIniciar.setOnClickListener(v -> {
            if(!StatusChapisco){
                diologo("DIREÇÃO OPERAÇÃO "+OPERACAO_DIR+" ?");
            }else{
                webSocketClient.send("9");
            }

        });
        botao_grande_parar_chapisco.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    webSocketClient.send("10");
                    break;
                case MotionEvent.ACTION_UP:
                    //webSocketClient.send("10");
                    break;
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("10");
                    break;
            }
            return false;
        });

        btnretornarX.setOnClickListener(v ->
                webSocketClient.send("12")
        );
        SWdirecaodeoperaco.setOnClickListener(v -> webSocketClient.send("11"));
        // BOTÃO ARAME 1 ==============
        btnArame1.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    webSocketClient.send("13");
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("14");
                    break;
            }
            return false;
        });

        // BOTÃO ARAME 2 ==============
        btnArame2.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    webSocketClient.send("15");
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("16");
                    break;
            }
            return false;
        });
        // BOTÃO ARAME  e maquina 1 ==============
        Maquina_arame1.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    webSocketClient.send("23");
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("24");
                    break;
            }
            return false;
        });

        // BOTÃO ARAME e maquina2 ==============
        Maquina_arame2.setOnTouchListener((view, motionEvent) -> {
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    webSocketClient.send("25");
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_CANCEL:
                    webSocketClient.send("26");
                    break;
            }
            return false;
        });
    }

    private void diologo(String msg){
        AlertDialog alertDialog = new AlertDialog.Builder(this)
                .setIcon(android.R.drawable.ic_dialog_alert)
                .setTitle("!!!! Atenção !!!!")
                .setMessage(msg)
                .setPositiveButton("SIM", (dialogInterface, i) -> {
                    diologo_passo("O FRISO DA MOENDA É "+Passo_do_friso+"in ?");

                })
                .setNegativeButton("NÃO", (dialogInterface, i) -> {
                    //set what should happen when negative button is clicked
                    Toast.makeText(getApplicationContext(),"Você Pode reiniciar quando quiser",Toast.LENGTH_LONG).show();
                })
                .show();

    }
    private void diologo_passo(String msg){
        AlertDialog alertDialog = new AlertDialog.Builder(this)
                .setIcon(android.R.drawable.ic_dialog_alert)
                .setTitle("!!!! Atenção Verificar!!!!")
                .setMessage(msg)
                .setPositiveButton("SIM", (dialogInterface, i) -> {
                    webSocketClient.send("9");
                    //finish();
                })
                .setNegativeButton("AJUSTAR", (dialogInterface, i) -> {
                    Intent intent = new Intent(this, Form_config.class);
                    startActivity(intent);
                })
                .show();

    }
    private void createWebSocketClient() {
        URI uri;
        try {
            // Connect to local host
            uri = new URI("ws://192.168.4.1:81/");
        }
        catch (URISyntaxException e) {
            e.printStackTrace();
            return;
        }
        webSocketClient = new WebSocketClient(uri) {
            @Override
            public void onOpen() {

            }
            @SuppressLint("SuspiciousIndentation")
            @Override
            public void onTextReceived(String s) {
                runOnUiThread(() -> {
                    try{
                        if(s.equals("conectado_ao_servidor_arame")) {
                            Layout_opraracao.setVisibility(View.GONE);
                            Layout_rpm.setVisibility(View.GONE);
                            layout_pussos.setVisibility(View.GONE);
                            layout_informacoes.setVisibility(View.GONE);
                            layout_botoes_de_controle.setVisibility(View.GONE);
                            layout_medidor.setVisibility(View.VISIBLE);
                            conectou_medidor = true;
                        }else if(s.equals("conectado_ao_servidor_robo")){
                            Layout_opraracao.setVisibility(View.VISIBLE);
                            Layout_rpm.setVisibility(View.VISIBLE);
                            layout_pussos.setVisibility(View.VISIBLE);
                            layout_informacoes.setVisibility(View.VISIBLE);
                            layout_botoes_de_controle.setVisibility(View.VISIBLE);
                            layout_medidor.setVisibility(View.GONE);
                            conectou_medidor=false;

                        }else{
                            if(conectou_medidor)
                            LerWebsocket_alimentadores(s);
                            else
                            LerWebsocket(s);
                        }

                    } catch (Exception e){
                        e.printStackTrace();
                    }
                });
            }
            @Override
            public void onBinaryReceived(byte[] data) {
            }
            @Override
            public void onPingReceived(byte[] data) {
            }
            @Override
            public void onPongReceived(byte[] data) {
            }
            @Override
            public void onException(Exception e) {
                System.out.println(e.getMessage());
            }
            @Override
            public void onCloseReceived() {

            }
        };
        webSocketClient.setConnectTimeout(10000);
        webSocketClient.setReadTimeout(1800000);// reinica conexão
        webSocketClient.enableAutomaticReconnection(5000);
        webSocketClient.connect();
    }

    // =================== Menus =================================
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        getMenuInflater().inflate(R.menu.reset, menu);

        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.menu_main) {
            Intent intent = new Intent(this, Form_config.class);
            startActivity(intent);
            return true;
        }
        if(id == R.id.resetar){
            webSocketClient.send("17");
        }
        return super.onOptionsItemSelected(item);
    }
    //=======================================================================
    @Override
    public void onResume() {
        createWebSocketClient();
        super.onResume();
    }
    @Override
    public void onStop() {
        webSocketClient.close();
        super.onStop();
    }
    @Override
    public void onStart() {

        super.onStart();
    }
    @Override
    public void onPause() {

        super.onPause();
    }
    @SuppressLint("SetTextI18n")
    void LerWebsocket_alimentadores(String dados){
        String[] Dados = dados.split(":");
        if(!dados.equals("conectado_ao_servidor_arame")){
            if (Dados.length < 6) {
                Log.w("LerWebsocket_alimentadores", "Mensagem incompleta, ignorando: " + dados);
                return;
            }
            txt_velocidade_arame_1.setText(Dados[0]+" m/min");
            txt_velocidade_arame_2.setText(Dados[1]+" m/min");
            txt_volume_arame_1.setText(Dados[2]+" Kg");
            txt_volume_arame_2.setText(Dados[3]+" kg");
            txt_compri_arame_1.setText(Dados[4]+ " m");
            txt_compri_arame_2.setText(Dados[5]+ " m");
        }
    }
    @SuppressLint("SetTextI18n")
    void LerWebsocket(String dados){
        int rpm_a_exibir = 17;
        String[] Dados = dados.split(":");
        if (Dados.length < 30) {
            Log.w("LerWebsocket", "Mensagem incompleta, ignorando (" + Dados.length + " campos): " + dados);
            return;
        }
        txtStepsY.setText("Tocha\n"+Dados[0]+ " mm");
        txtStepsX.setText("Carrinho\n"+Dados[1]+" in");
        btngravainicio.setText("Inicio Solda\n"+Dados[2]+ " mm");
        btngravafinal.setText("Final Solda\n"+Dados[3]+ " mm");

        if (Dados[15].equals("0")) {
            Pontons_Gravados = false;
            btnIniciar.setVisibility(View.INVISIBLE);
            btnretornarX.setVisibility(View.INVISIBLE);
        } else if (Dados[15].equals("1")){
            btnIniciar.setVisibility(View.VISIBLE);
            Pontons_Gravados = true;
        }

        txtRPM_tambor.setText(Dados[18]+" RPM");
        int rpm = Integer.parseInt(Dados[18]);
        if(rpm  <  2){
           txtRPM_tambor.setTextColor(Color.parseColor("#F6112B"));
        }else{
           txtRPM_tambor.setTextColor(Color.parseColor("#03F603"));
        }

        if (Dados[6].equals("1")) {
            //btnIniciar.setBackgroundResource(R.color.BTNOFF);
            //btnIniciar.setText("Parar Chapisco ?");
            //btnIniciar.setTextColor(Color.parseColor("#F6112B"));
            StatusChapisco = true;
            btnIniciar.setText("Parar operação ?");
            btnIniciar.setTextColor(Color.parseColor("#B10101"));
            //btnretornarX.setVisibility(View.INVISIBLE);
            //botao_grande_parar_chapisco.setVisibility(View.VISIBLE);
            //layout_botoes_de_controle.setVisibility(View.GONE);
        } else if (Dados[6].equals("0")){
            botao_grande_parar_chapisco.setVisibility(View.GONE);
            layout_botoes_de_controle.setVisibility(View.VISIBLE);
            //btnIniciar.setBackgroundResource(R.color.BTNON);
            StatusChapisco = false;

            btnIniciar.setText("Iniciar Chapisco ?");
            btnIniciar.setTextColor(Color.parseColor("#03F603"));
        }
        if(!Dados[1].equals("0.00") && !StatusChapisco){
            btnretornarX.setVisibility(View.VISIBLE);
        }else{
            btnretornarX.setVisibility(View.INVISIBLE);
        }
        if(Dados[7].equals("1")){
            SWdirecaodeoperaco.setChecked(true);
            SWdirecaodeoperaco.setText("DIREÇÃO DE OPERAÇÃO CARRINHO: >>> Direita >>>");
            OPERACAO_DIR = ">>DIREITA>>";
            Xmais.setText(">>>");
            Xmenos.setText("");
        }else if(Dados[7].equals("0")){
            SWdirecaodeoperaco.setChecked(false);
            SWdirecaodeoperaco.setText("DIREÇÃO DE OPERAÇÃO CARRINHO: <<< Esquerda <<<");
            OPERACAO_DIR = "<<ESQUERDA<<";
            Xmais.setText("");
            Xmenos.setText("<<<");
        }
        txtTamanhoChapisco.setText(Dados[14]+" mm");
        if(Dados[19].equals("1")){ // Sensor de giro
            rpm_a_exibir = 18;
        }else{
            rpm_a_exibir = 17;
        }
        txtPulsosY.setText(Dados[0]+ " mm");
        txtPulsosX.setText(Dados[1]+" in");
        txtCiclo_chapisco.setText(Dados[4]);
        txtTempoGiro.setText(Dados[8]+ "s /"+Dados[16]+"s /"+Dados[rpm_a_exibir]+" RPM");
        txtFiosdesolda.setText(Dados[9] +" de "+ Dados[10]);
        txtFrisosSoladados.setText(Dados[11] +" de "+ Dados[12]);
        txtLarguraFio.setText(Dados[13] +" mm");
        txtPontoInicialY.setText(Dados[2]+"/"+Dados[3]+"mm");
        int tempogiro = Integer.parseInt(Dados[8]);
        int qtdfiosolda = Integer.parseInt(Dados[10]);
        int TempoPorFriso = (tempogiro*qtdfiosolda)/60;
        txtTempoPorFriso.setText(TempoPorFriso+"min / "+ Dados[20]+"min");
        txtTempoTotal.setText((TempoPorFriso*Integer.parseInt(Dados[12]))/60+"h / "+ Dados[21]+"min");
        Passo_do_friso = Dados[22];
        txtStatus.setText(Dados[23]);
        // Arame consumo
        txt_velocidade_arame_1.setText(Dados[24]+" m/min");
        txt_velocidade_arame_2.setText(Dados[25]+" m/min");
        txt_volume_arame_1.setText(Dados[26]+" Kg");
        txt_volume_arame_2.setText(Dados[27]+" kg");
        txt_compri_arame_1.setText(Dados[28]+ " m");
        txt_compri_arame_2.setText(Dados[29]+ " m");
    }
}