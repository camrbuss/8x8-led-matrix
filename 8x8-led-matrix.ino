#include "index.h"
#include "Board.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

extern "C" {
  #include "hw_timer.h"
}

#define TIMER_INTERVAL_US 1000
#define DAT 5
#define CLC 0
#define LTC 4

//SSID and Password of your WiFi router
const char* ssid = "PENGUIN";
const char* password = "****";
ESP8266WebServer server(80); //Server on port 80

Board _board(LTC, CLC, DAT);

os_timer_t myTimer;

void allOff(){
  _board.allOff();
  server.send(200,"text/plain", "black");
}
void allOn(){
  _board.allOn();
  server.send(200,"text/plain", "green");
}
void setHeart(){
  _board.setHeart();
  server.send(200,"text/plain", "red");
}
void setSnake(){
  _board.setSnake();
  server.send(200,"text/plain", "blue");
}
void multiplex(){
  _board.multiplexRow();
}

void incrementFrame(void *pArg) {
  if (_board.animation) {
    os_timer_arm(&myTimer, _board.frameRateTimerMS, true);
    _board.incrementFrame();
  }
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.on("/",[](){server.send_P(200,"text/html", MAIN_page);});
  server.on("/allOff", allOff);
  server.on("/allOn", allOn);
  server.on("/setHeart", setHeart);
  server.on("/setSnake", setSnake);
  server.begin();
  
  hw_timer_init(FRC1_SOURCE, 1);
  hw_timer_set_func(multiplex);
  hw_timer_arm(TIMER_INTERVAL_US);

  os_timer_setfn(&myTimer, incrementFrame, NULL); // Set timer callback
  os_timer_arm(&myTimer, _board.frameRateTimerMS, true); // Set timer time
}

void loop() {
  server.handleClient();          //Handle client requests
}
