#include <GyverOLED.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <Hash.h>
#include <WiFiManager.h> // Include WiFiManager library

#include "logo.h" 
#include "web-page.h"
#include "function.h"


ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 