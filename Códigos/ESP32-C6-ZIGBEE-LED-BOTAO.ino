/*
  ============================================================
       ESP32-C6 + ESP32-H2
       REDE ZIGBEE NA PRÁTICA - PARTE 2
  ============================================================

  FUNÇÃO:

  ESP32-C6:
  - Coordenador Zigbee
  - Botão no GPIO 23
  - ZigbeeSwitch
  - Binding com o ESP32-H2

  ESP32-H2:
  - End Device
  - ZigbeeLight
  - LED controlado pelo C6

  FUNCIONAMENTO DO BOTÃO:

  1º toque  -> LED LIGA
  2º toque  -> LED DESLIGA
  3º toque  -> LED LIGA
  4º toque  -> LED DESLIGA

  O LED NÃO depende de o botão permanecer pressionado.

  ============================================================
*/

#include <Arduino.h>

#ifndef ZIGBEE_MODE_ZCZR
#error "Selecione Zigbee ZCZR em Tools -> Zigbee mode"
#endif

#include "Zigbee.h"


/*
  ============================================================
                    CONFIGURAÇÃO
  ============================================================
*/

#define BUTTON_PIN 23                       // GPIO do botão

#define SWITCH_ENDPOINT 1                   // Endpoint do Switch


/*
  Cria o endpoint ZigbeeSwitch.
*/

ZigbeeSwitch zbSwitch(SWITCH_ENDPOINT);


/*
  ============================================================
                    VARIÁVEIS
  ============================================================
*/


/*
  Estado anterior do botão.

  HIGH = botão solto
  LOW  = botão pressionado
*/

bool lastButtonState = HIGH;


/*
  Estado atual do LED.

  false = desligado
  true  = ligado
*/

bool ledState = false;


/*
  ============================================================
                         SETUP
  ============================================================
*/

void setup()
{
  Serial.begin(115200);


  /*
    Configura o botão utilizando o resistor
    de pull-up interno.

    Botão solto:
    GPIO 23 = HIGH

    Botão pressionado:
    GPIO 23 = LOW
  */

  pinMode(BUTTON_PIN, INPUT_PULLUP);


  /*
    ==========================================================
                         BINDING
    ==========================================================

    Permite um dispositivo vinculado ao Switch.

    O ESP32-H2 será o dispositivo de iluminação
    que receberá os comandos.
  */

  zbSwitch.allowMultipleBinding(false);


  /*
    Define fabricante e modelo.
  */

  zbSwitch.setManufacturerAndModel(
    "RodRobot",
    "ESP32-C6-Zigbee-Switch"
  );


  /*
    Adiciona o endpoint Switch à rede Zigbee.
  */

  Zigbee.addEndpoint(&zbSwitch);


  /*
    ==========================================================
                         BINDING
    ==========================================================

    Abre a rede durante 180 segundos para permitir
    a entrada e o binding do ESP32-H2.
  */

  Zigbee.setRebootOpenNetwork(180);


  /*
    ==========================================================
                    INICIA O COORDENADOR
    ==========================================================
  */

  Serial.println();
  Serial.println("Iniciando coordenador Zigbee...");


  if (!Zigbee.begin(ZIGBEE_COORDINATOR))
  {
    Serial.println("Falha ao iniciar Zigbee!");

    ESP.restart();
  }


  Serial.println();
  Serial.println("======================================");
  Serial.println(" ESP32-C6 - COORDENADOR ZIGBEE");
  Serial.println("======================================");

  Serial.println("Aguardando ESP32-H2...");
  Serial.println("Aguardando Binding Zigbee...");


  /*
    ==========================================================
                         BINDING
    ==========================================================

    Aguarda até que exista um dispositivo vinculado
    ao ZigbeeSwitch.
  */

  while (!zbSwitch.bound())
  {
    Serial.print(".");
    delay(500);
  }


  /*
    ==========================================================
                  BINDING CONCLUÍDO
    ==========================================================
  */

  Serial.println();
  Serial.println();
  Serial.println("======================================");
  Serial.println(" BINDING REALIZADO COM SUCESSO!");
  Serial.println("======================================");


  /*
    Mostra os dispositivos vinculados.
  */

  zbSwitch.printBoundDevices(Serial);


  Serial.println();
  Serial.println("Sistema pronto!");
  Serial.println("Pressione o botao para alternar o LED.");
}


/*
  ============================================================
                         LOOP
  ============================================================
*/

void loop()
{
  /*
    Lê o estado atual do botão.
  */

  bool buttonState = digitalRead(BUTTON_PIN);


  /*
    ==========================================================
                  DETECÇÃO DO PRESSIONAMENTO
    ==========================================================

    Só executamos a ação quando o botão muda de:

    HIGH -> LOW

    Ou seja, no momento em que o botão é pressionado.

    Isso é importante porque o LED não ficará ligado
    somente enquanto o botão estiver pressionado.
  */

  if (lastButtonState == HIGH && buttonState == LOW)
  {
    /*
      Pequeno debounce.

      Evita que o contato mecânico do botão
      gere vários acionamentos.
    */

    delay(50);


    /*
      Confirma se o botão continua pressionado.
    */

    if (digitalRead(BUTTON_PIN) == LOW)
    {
      /*
        ======================================================
                             BINDING
        ======================================================

        Inverte o estado do LED.

        Se estava desligado:
        → envia ON

        Se estava ligado:
        → envia OFF
      */

      ledState = !ledState;


      /*
        ======================================================
                         LED LIGADO
        ======================================================
      */

      if (ledState)
      {
        Serial.println();
        Serial.println("Botao pressionado");
        Serial.println("Binding -> enviando comando ON");

        zbSwitch.lightOn();
      }


      /*
        ======================================================
                        LED DESLIGADO
        ======================================================
      */

      else
      {
        Serial.println();
        Serial.println("Botao pressionado");
        Serial.println("Binding -> enviando comando OFF");

        zbSwitch.lightOff();
      }
    }
  }


  /*
    Atualiza o estado anterior do botão.

    Assim conseguimos detectar somente um novo
    pressionamento.
  */

  lastButtonState = buttonState;


  /*
    Pequeno intervalo entre as leituras.
  */

  delay(10);
}
