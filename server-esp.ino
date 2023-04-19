/*
 Welcome to GND_TO_VCC!! 
  
*/
 
#include <ESP8266WiFi.h>
#include <espnow.h>
 
// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x60, 0x01, 0x94, 0x3C, 0x2D, 0x7E};  // bir boşluk bırakılarak yazılmalıdır.
 
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;
 
// Create a struct_message called myData
struct_message myData;
 
// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
  
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(13,INPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
   
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
  
void loop() {
  // Set values to send
  if(digitalRead(14)==1){
    myData.b=191919; //açma mesajı
    delay(100);
  }
  else{
    //delay(200);
    myData.b=0;
  }
  Serial.println(myData.b);
 
  // Send message via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
 
  delay(100);
}
