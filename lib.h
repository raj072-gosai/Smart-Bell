#include <GyverOLED.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>

#include "logo.h" 
#include "web-page.h"
#include "function.h"


AsyncWebServer server(80);
WebSocketsServer websockets(81);


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 