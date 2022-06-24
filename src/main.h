#include <Arduino.h>

/*Definindo tamanho máximo das tasks*/
#define WIFI_TASK_SIZE 16384
#define MQTT_TASK_SIZE  8192
#define OPER_TASK_SIZE  4096

/*Mapeamento de pinos*/ 
#define UMIDADE  25
#define TENSAO   32
#define CORRENTE 33

/*Inicializando variáveis*/ 
float tensao, corrente, potencia;
unsigned int mqttLastCommunication;