# Smart Weld Robot - Chapisco

Robô cartesiano (eixos X/Y) para chapisco/solda em tambores.

## Estrutura

```
Smart-Weld-Robot-Chapisco/
├── firmware/       ESP32 (Arduino/.ino) — abrir a PASTA firmware/ no Arduino IDE ou VS Code
└── android-app/    App Android (Java)   — abrir a PASTA android-app/ no Android Studio
    └── app/        (módulo Gradle "app", dentro de android-app/ — não abrir isolado)
```

- `firmware/` — Firmware ESP32 (Arduino), controla os motores de passo e expõe WebSocket (porta 81) + HTTP REST (porta 80) para o app.
  - Sketch principal: `firmware/NewRoboChapisco_29_04_25.ino`
- `android-app/` — App Android (Java) que se conecta ao ESP32 via Wi-Fi (AP local) para controle e telemetria em tempo real.
  - **No Android Studio, use File → Open e selecione a pasta `android-app/`** (não a raiz do repositório, nem a subpasta `android-app/app/`).

## Comunicação

- App e firmware trocam telemetria via WebSocket usando uma string separada por `:` (~24-30 campos) e comandos numéricos ("1".."26").
- Configuração de parâmetros via HTTP REST (Retrofit no app / WebServer no ESP32), persistida em EEPROM no ESP32.
