/*
  ============================================================
       ESP32-H2 + ZIGBEE + LED
       REDE ZIGBEE NA PRÁTICA - PARTE 2
  ============================================================

  FUNÇÃO DO ESP32-H2:
  - Atua como END DEVICE da rede Zigbee.
  - Entra na rede criada pelo ESP32-C6.
  - Possui um endpoint ZigbeeLight.
  - Recebe os comandos enviados através do BINDING.
  - Controla um LED físico.

  HARDWARE:

  ESP32-H2

  FUNCIONAMENTO:

  ESP32-C6 envia ON
        ↓
  BINDING ZIGBEE
        ↓
  ESP32-H2
        ↓
  ZigbeeLight
        ↓
  GPIO 13= HIGH
        ↓
  LED ACENDE


  ESP32-C6 envia OFF
        ↓
  BINDING ZIGBEE
        ↓
  ESP32-H2
        ↓
  ZigbeeLight
        ↓
  GPIO 13 = LOW
        ↓
  LED APAGA

  ============================================================
*/

#include <Arduino.h>

#ifndef ZIGBEE_MODE_ED
#error "Selecione Zigbee ED em Tools -> Zigbee mode"
#endif

#include "Zigbee.h"


/*
  ============================================================
                    CONFIGURAÇÃO
  ============================================================
*/

#define LED_PIN 13                         // Define o GPIO 13 para o LED azul

#define LIGHT_ENDPOINT 10                  // Endpoint Zigbee


/*
  Cria o endpoint ZigbeeLight.

  Esse endpoint representa uma lâmpada/dispositivo
  de iluminação dentro da rede Zigbee.
*/

ZigbeeLight zbLight(LIGHT_ENDPOINT);


/*
  ============================================================
                FUNÇÃO DE CONTROLE DO LED
  ============================================================
*/

void setLED(bool state)
{
  /*
    ==========================================================
                           BINDING
    ==========================================================

    Esta função é chamada quando o ESP32-H2 recebe
    através do Zigbee o comando enviado pelo ESP32-C6.

    state = true
       → LED ligado

    state = false
       → LED desligado
  */

  if (state)
  {
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Comando Zigbee recebido: LED ON");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);

    Serial.println("Comando Zigbee recebido: LED OFF");
  }
}


/*
  ============================================================
                         SETUP
  ============================================================
*/

void setup()
{
  Serial.begin(115200);


  /*
    Configura o GPIO do LED como saída.
  */

  pinMode(LED_PIN, OUTPUT);


  /*
    Inicia o LED desligado.
  */

  digitalWrite(LED_PIN, LOW);


  /*
    Define fabricante e modelo.
  */

  zbLight.setManufacturerAndModel(
    "RodRobot",
    "ESP32-H2-Zigbee-Light"
  );


  /*
    ==========================================================
                         BINDING
    ==========================================================

    Registra a função que será executada quando o estado
    do dispositivo ZigbeeLight for alterado.

    O comando chega pelo Zigbee e esta função transforma
    o comando Zigbee em uma ação física no GPIO 13.
  */

  zbLight.onLightChange(setLED);


  /*
    Adiciona o endpoint de iluminação ao núcleo Zigbee.
  */

  Serial.println("Adicionando endpoint ZigbeeLight...");

  Zigbee.addEndpoint(&zbLight);


  /*
    ==========================================================
                  INICIA O END DEVICE
    ==========================================================

    O ESP32-H2 será iniciado como End Device.

    Ele deverá encontrar a rede criada pelo ESP32-C6
    e entrar nela.
  */

  Serial.println("Iniciando ESP32-H2 como End Device...");


  if (!Zigbee.begin())
  {
    Serial.println("Falha ao iniciar Zigbee!");
    Serial.println("Reiniciando...");

    ESP.restart();
  }


  /*
    ==========================================================
                         CONEXÃO
    ==========================================================
  */

  Serial.println("Aguardando entrada na rede Zigbee...");


  while (!Zigbee.connected())
  {
    Serial.print(".");
    delay(500);
  }


  /*
    ==========================================================
                     REDE CONECTADA
    ==========================================================
  */

  Serial.println();
  Serial.println();
  Serial.println("======================================");
  Serial.println(" ESP32-H2 CONECTADO À REDE ZIGBEE");
  Serial.println("======================================");

  Serial.println("Aguardando comandos do ESP32-C6...");
}


/*
  ============================================================
                       LOOP
  ============================================================
*/

void loop()
{
  /*
    O processamento dos comandos Zigbee é realizado
    pela própria biblioteca.

    O ESP32-H2 permanece aguardando comandos enviados
    pelo dispositivo vinculado.
  */

  delay(100);
}