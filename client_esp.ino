
#include <ESP8266WiFi.h>
#include <espnow.h>
 
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    String d;
    bool e;
} struct_message;
 
// Create a struct_message called myData
struct_message myData;
 
// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.println(WiFi.macAddress());
}
  
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
   pinMode(13,OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
   
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
    if(myData.b==191919){
     digitalWrite(13,HIGH);
     delay(1000);
     digitalWrite(13,LOW);
  }
  Serial.println(WiFi.macAddress());

}
