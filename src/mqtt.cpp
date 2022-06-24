#include "mqttapp.h"
#include "wifiapp.h"

WiFiClient ubidots;
PubSubClient client(ubidots);

bool mqttConnected;

bool mqtt_initialize() {
  client.setServer(SERVER, PORT);
  while(!client.connect(DEVICE_ID1, TOKEN, "") && !client.connect(DEVICE_ID2, TOKEN, "") && !client.connect(DEVICE_ID3, TOKEN, "")) {
      Serial.println("MQTT - Connect error");
      return false;
  }

  Serial.println("MQTT - Connect ok");
  mqttConnected = true;
  return true;
}

void sendPower(float potencia) {
  char json[250];
  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"potencia\":%02.02f}}}", VARIABLE_LABEL_POTENCIA, potencia, potencia);
  client.publish(TOPIC, json) ? Serial.println("Successfully sent power data") : Serial.println("Failed to send power data");
}

void sendCurrent(float corrente) {
  char json[250];
  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"corrente\":%02.02f}}}", VARIABLE_LABEL_CORRENTE, corrente, corrente);
  client.publish(TOPIC, json) ? Serial.println("Successfully sent current data") : Serial.println("Failed to send current data"); 
}

void sendVoltage(float tensao) {
  char json[250];
  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"tensao\":%02.02f}}}", VARIABLE_LABEL_TENSAO, tensao, tensao);
  client.publish(TOPIC, json) ? Serial.println("Successfully sent voltage data") : Serial.println("Failed to send voltage data"); 
}
