# Configuração USB CDC no ESP-IDF com Arduino

Este documento detalha as configurações necessárias para usar comunicação serial USB em projetos ESP-IDF com Arduino como componente.

## Modos de Operação

### 1. Hardware CDC / JTAG (ESP32-C2/C3/C5/C6/C61/H2/H21/S3/P4)
Usa uma implementação em silício apenas para USB CDC (não pode ser usado para outros funções):
```cmake
list(APPEND compile_definitions "ARDUINO_USB_CDC_ON_BOOT=1")
list(APPEND compile_definitions "ARDUINO_USB_MODE=1")
```

```cpp
void setup() {
  Serial.begin();  // Baud rate não é necessário
  while(!Serial) { // aguarda até que a porta USB CDC seja conectada a uma apllicação como Serial Monitor
    delay(100);
  }
}
```

### 2. USB OTG (ESP32-S2/S3/P4)
Usa USB nativo via TinyUSB:
```cmake
list(APPEND compile_definitions "ARDUINO_USB_CDC_ON_BOOT=1")
list(APPEND compile_definitions "ARDUINO_USB_MODE=0")
```

```cpp
void setup() {
  Serial.begin();  // Baud rate ignorado
  // aguarda até que a porta USB CDC seja conectada a uma apllicação como Serial Monitor
  while (!Serial) delay(10);
}
```

## Configuração do Projeto

### CMakeLists.txt
Adicione antes do `project.cmake`:
```cmake
# Configuração USB CDC
list(APPEND compile_definitions "ARDUINO_USB_CDC_ON_BOOT=1")
list(APPEND compile_definitions "ARDUINO_USB_MODE=1")  # ou 0 para TinyUSB

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(seu_projeto)
```

### Menuconfig
Para USB OTG (ESP32-S2/S3/P4):
```
Component Config → TinyUSB Stack → Enable TinyUSB driver
  → CDC Enable → Enable CDC feature
```

Para Hardware CDC:
```
Component Config → Arduino Configuration
  → Enable CDC on Boot
```

## Parâmetros de Configuração

### ARDUINO_USB_CDC_ON_BOOT
- `1`: Habilita CDC na inicialização - Arduino `Serial` será a porta USB CDC
- `0`: CDC precisa ser inicializado manualmente - Arduino `Serial` será a porta UART0

### ARDUINO_USB_MODE
- `1`: Hardware CDC (ESP32-C2/C3/C5/C6/C61/H2/H21/S3/P4)
  - Não requer baud rate
  - USB CDC somente implementado no próprio SoC (Hardware)

- `0`: USB OTG (ESP32-S2/S3/P4)
  - Não requer baud rate
  - USB nativo
