#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Servo_ESP32.h>

static const int servoPin = 13;
static const int ldr = 36;

Servo_ESP32 servo1;

#define WIFI_SSID "jonathanlove"
#define WIFI_PASSWORD "ekeloveoenfam1510"

#define FIREBASE_HOST "https://iotminiproject4-43202-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "PbNq42PewFAQjK1VlJyOsSSaic6GerjM4KLfaQAb"

#define API_KEY "AIzaSyATwdMzzpiVkhKjIpBqjZI35FKbXCfayW4"

//Define Firebase Data object
FirebaseData firebaseData;

FirebaseAuth auth;
FirebaseConfig config;

void connection(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void ldrSensor(){
  int newServoValue = 180;
  int ldrValue = (0.009768*analogRead(ldr))+10;
  Serial.print("ldr Value: ");
  Serial.println(ldrValue);

  if(ldrValue <= 15){
    servo1.write(0);
    Serial.print("servo Value: ");
//    Serial.println(0);
    newServoValue = 0;
  }else if(ldrValue >15){
    servo1.write(180);
    Serial.print("servo Value: ");
//    Serial.println(180);
    newServoValue = 180;
  }
  
  Firebase.setInt(firebaseData, "/miniProject4/ldr", ldrValue);
  Firebase.setInt(firebaseData, "/miniProject4/servo", newServoValue);
  delay(1000);

}

int button;
int otomatisasi;

void setup(){
  Serial.begin(115200); 
  connection();
 
  servo1.attach(servoPin);

}

void loop(){
  Firebase.getInt(firebaseData, "/miniProject4/otomatisasi");
  otomatisasi = firebaseData.intData();
  
  if(otomatisasi == 1){
    ldrSensor();
  }else if(otomatisasi == 0){
    Firebase.getInt(firebaseData, "/miniProject4/button");
    button = firebaseData.intData();
    if(button == 1){
      servo1.write(180);
      Serial.print("button : ");
      Serial.println(button);
    }else if(button == 0){
      servo1.write(0);
      Serial.print("button : ");
      Serial.println(button);
  }
  }
}
