# Planejamento - Scaner OBD-II com ESP32

## Introdução

O projeto consiste em um dispositivo que pode ser utilizado para ler dados úteis da porta OBD-II de um carro por meio de um módulo ELM327 Bluetooth. O dispositivo é capaz de ler e exibir RPM, velocidade, temperatura do líquido de arrefecimento, posição do acelerador, temperatura do ar de admissão, nível de combustível, pressão do combustível, pressão do coletor de admissão, carga do motor, consumo de combustível, voltagem da bateria, e mais.

[Link para o repositório do projeto](https://github.com/brxxxl/dingus-32)

## Atividades planejadas

### Mês 1

- ✅ Definição do projeto
- ✅ Decisão do tema e pesquisa sobre possíveis implementações
- ✅ Escolha dos materiais
- ❗ Compra dos materiais
  - Como o módulo de alimentação do circuito ainda não foi definido e projetado, a compra dos materiais deste módulo foi adiada.
- ✅ Leitura e discussão acerca de materiais relevantes reunidos nas últimas semanas (i.e. protocolos OBD, scanners, interfaces possíveis, etc)
- ❗ Análise do funcionamento dos materiais comprados
  - Os materiais funcionaram conforme o esperado, no começo. Porém, após mais testes, constatamos que o módulo ELM327 Bluetooth comprado não funcionava corretamente, por se tratar de um produto pirata (descobrimos isso após abrir o módulo e ver que não havia um chip ELM327 dentro dele). Por isso, tivemos que comprar um novo módulo ELM327.
- ❗ Estudo de viabilidade (simulação)
  - Não existe simulador para o módulo ELM327, assim como para o microcontrolador ESP32. Por isso, não foi possível simular o projeto. No entanto, serão necessárias simulações do circuito de alimentação antes da implementação.
- ✅ Execução na protoboard (validação do projeto)
  - O projeto foi validado na protoboard, com a ressalva de que o módulo ELM327 Bluetooth comprado não funcionava corretamente.

### Mês 2

- Definição do circuito de alimentação
- Simulação do circuito de alimentação
- Compra dos materiais do circuito de alimentação
- Implementação do circuito de alimentação na protoboard
- Novos testes com o módulo ELM327 novo
- Projeto da PCB
- Manufatura da PCB
- Montagem da PCB
- Finalização do código

#### Cronograma - Mês 2

| Atividade | Início | Fim | Semana |
|-----------|--------|-----|--------|
| Definição do circuito de alimentação | 07/10/2021 | 11/10/2021 | 1 |
| Simulação do circuito de alimentação | 07/10/2021 | 11/10/2021 | 1 |
| Compra dos materiais do circuito de alimentação | 07/10/2021 | 11/10/2021 | 1 |
| Implementação do circuito de alimentação na protoboard | 12/10/2021 | 18/10/2021 | 2 |
| Novos testes com o módulo ELM327 novo | 12/10/2021 | 18/10/2021 | 2 |
| Projeto da PCB | 19/10/2021 | 25/10/2021 | 3 |
| Manufatura da PCB | 26/10/2021 | 01/11/2021 | 4 |
| Montagem da PCB | 26/10/2021 | 01/11/2021 | 4 |

## Desenvolvimento

### Módulo de alimentação

O módulo de alimentação do circuito foi projetado para ser alimentado por baterias, como uma de 9V (pilha) ou 12V (carro), ou por USB (5V). O circuito foi projetado para ser capaz de fornecer 5V e 3.3V para os componentes do projeto, como o ESP32, o display LCD, e outros.

Utilizando um regulador de tensão LM7805, o circuito fornece 5V para os componentes que necessitam desta tensão. Como o módulo de desenvolvimento ESP32 utilizado (NodeMCU-32S) já possui um regulador de tensão embutido, o circuito fornece 3.3V para os componentes que necessitam desta tensão.

### Display LCD

O display LCD utilizado é um display 16x2 com interface I2C, que utiliza o chip PCF8574 para expandir as portas do microcontrolador. O display foi utilizado para mostrar as informações lidas do carro, como RPM, velocidade, temperatura do motor, posição do acelerador, etc.

### Módulo ELM327

O módulo ELM327 é um módulo que se comunica com a ECU do carro através do protocolo OBD-II. O módulo utilizado é um módulo Bluetooth, que se comunica com o ESP32 por meio da biblioteca BluetoothSerial. O módulo ELM327 é capaz de ler informações do carro, como RPM, velocidade, temperatura do motor, posição do acelerador, etc.

### Botões

O projeto utiliza alguns (indefinidos) botões para navegar entre as telas do display LCD. Os botões são conectados ao ESP32 por meio de um resistor pull-up.

Utilizamos uma matriz 4x4 de botões. A detecção da ativação de um botão é feita por meio das interrupções do ESP32.

### Código

O código do projeto foi desenvolvido utilizando a plataforma PlatformIO, com o framework Arduino. Diversas partes do código foram baseadas em exemplos disponíveis na internet, especialmente os exemplos da biblioteca ELMduino.

Diversas partes do código já estão implementadas e funcionando, como a comunicação Serial do ESP32 com um PC, para debug, a comunicação Bluetooth entre o ESP32 e o módulo ELM327, a leitura de dados do módulo ELM327, a leitura de botões por meio de interrupções (para evitar que o ESP32 fique preso esperando um botão ser pressionado), e a comunicação com o display LCD.

Além disso, algumas funcionalidades extra foram implementadas, como a capacidade de exibir caracteres especiais no display LCD, como setas, que não são suportadas nativamente pelo display, e animações de carregamento (com pontos que piscam).

### PCB

O projeto da PCB provavelmente será feito no software Altium Designer, devido a facilidade de uso da ferramenta. A PCB será projetada para ser o mais compacta possível, para facilitar a montagem do projeto.

## Referências

- [ELM327 Datasheet](https://www.elmelectronics.com/wp-content/uploads/2016/07/ELM327DS.pdf)
- [ELMduino](https://github.com/PowerBroker2/ELMduino)
- [PCF8574 Datasheet](https://www.ti.com/lit/ds/symlink/pcf8574.pdf)
- [LM7805 Datasheet](https://www.sparkfun.com/datasheets/Components/LM7805.pdf)
- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [16x2 LCD Datasheet](https://www.waveshare.com/datasheet/LCD_en_PDF/LCD1602.pdf)

## Autores

- João Pedro Assoni - 21203978
- [Leonardo Henrique Dill Bruxel](https://github.com/brxxxl/) - 22100857
- Rafaella Rivello Dal Pont - 21205011
