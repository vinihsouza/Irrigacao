#include "main.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifiapp.h"
#include "mqttapp.h"

TaskHandle_t taskMqtt = NULL, taskWifi = NULL, taskOper = NULL;

void vTaskWIFI(void *pvParameters);
void vTaskMQTT(void *pvParameters);
void vTaskOPER(void *pvParameters);

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(vTaskWIFI, "WIFI TASK", WIFI_TASK_SIZE, NULL, 5, &taskWifi, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskOPER, "OPER TASK", OPER_TASK_SIZE, NULL, 5, &taskOper, PRO_CPU_NUM);
}

void loop() {
  vTaskDelay(3000);
}

void vTaskWIFI(void *pvParameters) {
  wifi_initialize(NOT_CONNECTED);
  for ( ;; ) {
    if(!connecting && WiFi.status() != WL_CONNECTED) {
      wifi_initialize(NOT_CONNECTED);
    } 
    else if (connecting && WiFi.status() != WL_CONNECTED) {
      wifi_initialize(CONNECTING);
    } 
    else if (connecting && WiFi.status() == WL_CONNECTED) {
      wifi_initialize(CONNECTED);
      xTaskCreatePinnedToCore(vTaskMQTT, "MQTT TASK", MQTT_TASK_SIZE, NULL, 5, &taskMqtt, APP_CPU_NUM);
    }
  }
}

void vTaskMQTT(void *pvParameters) {
  mqtt_initialize();
  for ( ;; ) {
    if((millis() - mqttLastCommunication > MQTT_INTERVAL_COMMUNICATION) && mqttConnected) {
      sendPower(potencia);
      sendCurrent(corrente);
      sendVoltage(tensao);
      mqttLastCommunication = millis();
    }
  }
}

void vTaskOPER(void *pvParameters) {
  disableCore0WDT();
  analogReadResolution(12);
  analogSetAttenuation(ADC_6db);
  uint8_t pins[3] = {UMIDADE, TENSAO, CORRENTE};
  for(uint8_t i=0; i<sizeof(pins); i++) pinMode(pins[i], INPUT);
  for ( ;; ) {
    tensao = (analogRead(TENSAO) * (12.6 / 2820));
    corrente = analogRead(CORRENTE);
    corrente = (sqrt(pow((((analogRead(CORRENTE) - 3505) ) ), 2)) / 39855917) * 100000;
    corrente < 0.08 ? corrente = 0.19 : corrente;
    potencia =  tensao * corrente;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
