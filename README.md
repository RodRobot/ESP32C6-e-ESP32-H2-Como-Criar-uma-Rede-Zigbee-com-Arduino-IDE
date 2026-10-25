# ESP32C6-e-ESP32-H2-Como-Criar-uma-Rede-Zigbee-com-Arduino-IDE

Projeto educativo de comunicação sem fio utilizando duas placas ESP32: o **ESP32-C6 como coordenador Zigbee** e o **ESP32-H2 como dispositivo final (End Device)**.

O objetivo é controlar o LED azul do ESP32-H2 por meio de um botão conectado ao ESP32-C6, utilizando uma rede Zigbee própria, sem necessidade de conexão com a internet.

## Objetivo do projeto

Neste projeto, vamos aprender a:

- Configurar o Arduino IDE para trabalhar com Zigbee.
- Utilizar o ESP32-C6 como coordenador da rede.
- Configurar o ESP32-H2 como dispositivo final.
- Estabelecer a comunicação sem fio entre as placas.
- Controlar um LED remotamente por meio de um botão.
- Acompanhar a inicialização e a conexão pelo Monitor Serial.

## Hardware utilizado

- 1 × ESP32-C6 Dev Module
- 1 × ESP32-H2
- 1 × botão tátil
- Cabos USB compatíveis com as placas
- Computador com Arduino IDE

O LED azul utilizado no teste é o LED da própria placa ESP32-H2, conectado ao GPIO 13 conforme a configuração deste projeto.

## Como funciona

### ESP32-C6 — Coordenador Zigbee

O ESP32-C6 inicia a rede Zigbee e realiza a leitura do botão conectado ao GPIO 23.

Ao pressionar o botão, o programa alterna o estado da iluminação e envia o comando correspondente ao ESP32-H2.

### ESP32-H2 — End Device

O ESP32-H2 entra na rede Zigbee e recebe os comandos enviados pelo coordenador.

O programa utiliza o endpoint `ZigbeeLight` e a função `onLightChange()` para tratar as mudanças de estado e controlar o LED azul no GPIO 13.

### Comportamento esperado

1. Primeiro pressionamento do botão: LED aceso.
2. Segundo pressionamento do botão: LED apagado.
3. Os pressionamentos seguintes alternam entre ligado e desligado.

A comunicação entre as placas acontece por rádio, sem ligação física de dados entre elas.

## Ligações do hardware

### ESP32-C6

| Componente | Conexão |
|---|---|
| Botão — terminal 1 | GPIO 23 |
| Botão — terminal 2 | GND |
| Alimentação | USB |

### ESP32-H2

| Componente | Conexão |
|---|---|
| LED azul da placa | GPIO 13, conforme o hardware utilizado |
| Alimentação | USB |

**Atenção:** confirme a identificação do LED e do GPIO 13 na sua placa ESP32-H2. A ligação do LED integrado pode variar entre modelos.

## Configuração do Arduino IDE

Utilize uma versão compatível do pacote de placas ESP32 da Espressif. Este projeto foi desenvolvido com **Arduino-ESP32 3.3.11**.

### Configuração do ESP32-C6

Em `Ferramentas`, selecione as opções correspondentes:

- **Placa:** ESP32C6 Dev Module
- **USB CDC On Boot:** Disabled
- **Zigbee Mode:** Zigbee ZCZR (coordinator/router)
- **Partition Scheme:** Zigbee ZCZR 4MB with spiffs

A opção USB CDC On Boot foi utilizada como Disabled nos testes deste projeto para permitir o funcionamento esperado do Monitor Serial na conexão utilizada.

### Configuração do ESP32-H2

- Placa: ESP32H2 Dev Module.
- USB CDC On Boot: Enabled.
- Zigbee Mode: Zigbee ED (end device).
- Partition Scheme: Zigbee 4MB with spiffs.

Os nomes e as opções podem variar de acordo com a versão do pacote ESP32 e o modelo da placa.

### Erase All Flash Before Sketch Upload

A opção **Erase All Flash Before Sketch Upload** pode ser habilitada quando for necessário limpar configurações persistentes de projetos anteriores.

Ela apaga os dados da memória flash antes do upload e pode remover configurações da rede Zigbee. Utilize-a com atenção e desabilite-a após a limpeza, caso queira preservar dados persistentes.

Se o ESP32-H2 não entrar automaticamente em modo de gravação, tente colocá-lo em modo de download utilizando os botões BOOT e RESET, conforme o modelo da placa.

## Como gravar os programas

1. Abra o código do coordenador no Arduino IDE.
2. Conecte o ESP32-C6 ao computador.
3. Selecione a placa, a porta serial e as configurações indicadas.
4. Grave o programa do coordenador.
5. Abra o código do dispositivo final.
6. Conecte o ESP32-H2 ao computador.
7. Selecione a placa, a porta serial e o modo Zigbee ED.
8. Grave o programa do dispositivo final.

Os códigos-fonte do C6 e do H2 devem ficar em pastas separadas, cada uma contendo seu próprio arquivo `.ino`.

## Como testar

1. Ligue o ESP32-C6.
2. Abra o Monitor Serial e verifique a inicialização do coordenador.
3. Ligue o ESP32-H2.
4. Verifique se o dispositivo final entra na rede Zigbee.
5. Confirme que o vínculo ou mecanismo de controle necessário está estabelecido.
6. Pressione o botão conectado ao GPIO 23 do C6.
7. Observe o LED azul do H2 acender e apagar a cada novo pressionamento.

A conexão à rede e o vínculo entre os endpoints são etapas distintas. Se o dispositivo se conectar, mas o LED não responder, confira a configuração dos endpoints e do mecanismo de controle Zigbee.

## Tecnologias utilizadas

- ESP32-C6
- ESP32-H2
- Zigbee
- Arduino IDE
- Arduino-ESP32 3.3.11

## Aplicações e possibilidades

Este projeto pode servir como ponto de partida para desenvolver:

- Interruptores sem fio.
- Sensores de abertura de portas.
- Sistemas de iluminação.
- Automação residencial.
- Redes locais de sensores e atuadores.

## Sobre o projeto

Projeto educacional desenvolvido para o **RodRobot**, com foco em eletrônica, microcontroladores, IoT, robótica e automação.

Blog: [https://rodrobot.blogspot.com/p/projetos.html/](https://rodrobot.blogspot.com/p/projetos.html)

## 📺 Vídeo tutorial no YouTube

Assista ao vídeo para acompanhar a montagem e a configuração do projeto passo a passo.

▶️ **[ESP32-C6 e ESP32-H2 — Tutorial no YouTube](https://www.youtube.com/watch?v=PTjINxsFHuM&t=58s)**

**RodRobot — Aprenda, monte e programe!**
