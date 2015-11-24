/*
Hal9k postkasse overvågning /slack client 

replace INSET AUTH TOKEN HERE!! with your slack api auth token 
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "hal9k";
//const char* ssid = "ZyXEL_95F4";
//const char* password = "JNF44HMKHA93V";

const char* host = "slack.com";
const int httpsPort = 443;

int postpin = 2;
String url = "/api/chat.postMessage?token=INSET AUTH TOKEN HERE!!&channel=%23general&text=<!here%7Chere>%3A%20S%C3%A5%20er%20der%20post%20til%20%3Ahal9k%3A&as_user=true&pretty=1";

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "‎‎AB F0 5B A9 1A E0 AE 5F CE 32 2E 7C 66 67 49 EC DD 6D 6A 38";

void setup() {
  pinMode(postpin, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid); 
  //WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


void loop() {



  if(digitalRead(postpin)==LOW){
    Serial.println("if");
    sendmessage();
    delay(5000);
  
    }
    else {
      Serial.println("else");
      }
      delay(500);
      //delay(500000);
}

void sendmessage(){
       // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client; //
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) { //, 
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }
  
  
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: POSTCHECKERESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  /*if (line.startsWith("{\"message\"")) {
    Serial.println("esp8266/Arduino post successfull!");
  } else {
    Serial.println("esp8266/Arduino post has failed");
  }*/
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  }
