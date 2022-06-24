#include <PubSubClient.h>

#define TOKEN "BBFF-PlEgfKJAI3HyKUUobiE6o7XWU5m61S"
#define VARIABLE_LABEL_CORRENTE "corrente"
#define VARIABLE_LABEL_TENSAO "tensao"
#define VARIABLE_LABEL_POTENCIA "potencia"
#define DEVICE_ID1 "62b26a42e41edb35493f96cc"
#define DEVICE_ID2 "62b26a3e9f7bba2d02718692"
#define DEVICE_ID3 "62b26a46d1d5cb39a6fbe727"
#define SERVER "industrial.api.ubidots.com"
#define PORT 1883
#define TOPIC "/v1.6/devices/esp32"
#define MQTT_INTERVAL_COMMUNICATION 5000

void sendPower(float eletricy);
void sendCurrent(float eletricy);
void sendVoltage(float eletricy);
bool mqtt_initialize();

extern bool mqttConnected;