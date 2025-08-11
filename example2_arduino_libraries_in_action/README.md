# Hello World Arduino as ESP-IDF Component

Este projeto demonstra como integrar o Arduino como um componente em um projeto ESP-IDF, utilizando sensores SHTC3 (umidade/temperatura) e ICM42670 (IMU/pedômetro), além de controle de LEDs.

Este exemplo é baseado em:
- [Exemplo do Pedômetro ICM42670P](https://github.com/tdk-invn-oss/motion.arduino.ICM42670P/blob/main/examples/APEX_Pedometer/APEX_Pedometer.ino)
- [Exemplo Básico do Adafruit SHTC3](https://github.com/adafruit/Adafruit_SHTC3/blob/master/examples/SHTC3test/SHTC3test.ino)

Os códigos originais foram adaptados e integrados para funcionar com ESP-IDF usando Arduino como componente.

## Dependências
- ESP-IDF (versão recomendada: 5.x)
- Arduino-ESP32 (como componente ESP-IDF)
- Biblioteca ICM42670
- Biblioteca Adafruit_SHTC3

### Bibliotecas Adafruit
O sensor SHTC3 requer as seguintes bibliotecas:
- Adafruit_SHTC3 (principal)
- Adafruit_Sensor (dependência necessária para tipos de dados de sensores)
- Adafruit_BusIO (dependência para comunicação I2C/SPI)

Todas as bibliotecas devem ser adicionadas como componentes no diretório `components/`:
```bash
components/
  ├── Adafruit_SHTC3/
  ├── Adafruit_Sensor/
  └── Adafruit_BusIO/
```

### Adicionando Bibliotecas Arduino como Componentes
Para adicionar uma biblioteca Arduino como componente ESP-IDF:

1. Crie um diretório para a biblioteca em `components/`:
   ```bash
   mkdir -p components/nome_da_biblioteca
   ```

2. Copie os arquivos fonte da biblioteca para o diretório:
   ```bash
   components/nome_da_biblioteca/
   ├── library.cpp
   ├── library.h
   └── CMakeLists.txt
   ```

3. Crie um arquivo `CMakeLists.txt` com o seguinte conteúdo:
   ```cmake
   # Nome mínimo da versão do CMake
   cmake_minimum_required(VERSION 3.5)

   # Registre o componente
   idf_component_register(
     SRCS "library.cpp"          # Arquivos fonte (.cpp, .c)
     INCLUDE_DIRS "."           # Diretório de headers
     REQUIRES "arduino-esp32"   # Dependência do Arduino
   )
   ```

4. Se a biblioteca depender de outros componentes, adicione-os em `REQUIRES`:
   ```cmake
   idf_component_register(
     SRCS "Adafruit_SHTC3.cpp"
     INCLUDE_DIRS "."
     REQUIRES "arduino-esp32" "Adafruit_BusIO" "Adafruit_Sensor"
   )
   ```

5. Para várias fontes, você pode usar:
   ```cmake
   file(GLOB_RECURSE SOURCES "*.cpp" "src/*.cpp")
   idf_component_register(
     SRCS ${SOURCES}
     INCLUDE_DIRS "." "src"
     REQUIRES "arduino-esp32"
   )
   ```

## Funcionalidades
- Inicialização e leitura do sensor SHTC3 (umidade e temperatura)
- Inicialização e leitura do sensor ICM42670 (IMU com pedômetro e interrupção)
- Controle de um LED RGB e um LED de status
- Comunicação I2C com pinos customizados
- Saída de dados via Serial para depuração

## Hardware Necessário
- Rust ESP Board v1.2 [Documentação](https://github.com/esp-rs/esp-rust-board/tree/v1.2)

### Diagrama de Pinos
```
ESP32-C3 DevKit
+----------------+
|         GPIO2  |-- RGB LED
|         GPIO10 |-- LED Status
|         GPIO7  |-- SDA (SHTC3/ICM42670)
|         GPIO8  |-- SCL (SHTC3/ICM42670)
|              5V|
|             GND|
+----------------+
```

### Configurações de Hardware
- ESP32C3 (ou compatível com ESP-IDF e Arduino-ESP32)
- Sensor SHTC3
- Sensor ICM42670
- LED RGB conectado ao pino 2 (definido como `RGB_LED_PIN`)
- LED de status conectado ao pino 10 (definido como `LED_PIN`)
- Pinos I2C: SDA no pino 7 (`SDA_PIN`), SCL no pino 8 (`SCL_PIN`)

## Como funciona
- O programa inicializa a comunicação serial, sensores e LEDs.
- O loop principal faz o LED de status piscar, alterna as cores do LED RGB, lê e imprime temperatura/umidade e, se houver interrupção do IMU, imprime dados do pedômetro.

## Estrutura do Código
- `setup()`: Inicializa periféricos, sensores e LEDs.
- `loop()`: Executa a lógica principal, leitura dos sensores e controle dos LEDs.
- `irq_handler()`: Manipulador de interrupção do IMU para o pedômetro.

## Configuração e Compilação
1. Instale o ESP-IDF (v5.x ou superior):
   ```bash
   . $HOME/esp/esp-idf/export.sh
   ```

2. Clone este repositório:
   ```bash
   git clone [URL_DO_REPOSITORIO]
   cd hello_world_arduino_as_component
   ```

3. Configure o projeto:
   ```bash
   idf.py set-target esp32c3
   idf.py menuconfig
   # Configure: Component Config -> Arduino Configuration
   ```

4. Compile e faça upload:
   ```bash
   idf.py build
   idf.py -p [PORTA] flash monitor
   ```

## Saída Serial Esperada
```
Hello World from Arduino as Component!
SHTC3 test
Found SHTC3 sensor
ICM42670 Pedometer initialized successfully
Temperature: 25.3 degrees C
Humidity: 45.2% rH
Step count: 10
Step cadence: 90.5
activity: walking
```

## Troubleshooting
- **SHTC3 não encontrado**: 
  - Verifique as conexões I2C e se os pinos estão corretos
  - Confirme se todas as bibliotecas Adafruit estão presentes (SHTC3, Sensor e BusIO)
  - Verifique se as bibliotecas estão corretamente configuradas como componentes
- **ICM42670 falha na inicialização**: Verifique o endereço I2C e as conexões
- **LED RGB não funciona**: Confirme se o pino está configurado corretamente
- **Erro de compilação**: 
  - Certifique-se que todas as dependências estão instaladas
  - Verifique se os CMakeLists.txt de cada componente estão configurados corretamente

## Observações
- Certifique-se de que os pinos definidos nos macros correspondem ao seu hardware.
- O código pode ser expandido para outros sensores ou funcionalidades do Arduino.

---

**Autor:** Rodrigo Garcia Github@SuGlider\
**Licença:** Apache
