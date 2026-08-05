# Smart Weld Robot - Chapisco

Robô cartesiano (eixos X/Y) para chapisco/solda em tambores.

## Estrutura

- `firmware/` — Firmware ESP32 (Arduino), controla os motores de passo e expõe WebSocket (porta 81) + HTTP REST (porta 80) para o app.
- `app/` — App Android (Java) que se conecta ao ESP32 via Wi-Fi (AP local) para controle e telemetria em tempo real.

## Comunicação

- App e firmware trocam telemetria via WebSocket usando uma string separada por `:` (~24-30 campos) e comandos numéricos ("1".."26").
- Configuração de parâmetros via HTTP REST (Retrofit no app / WebServer no ESP32), persistida em EEPROM no ESP32.
