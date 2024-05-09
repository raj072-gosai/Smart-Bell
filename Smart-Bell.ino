#include "lib.h"





void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not found");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char *)(payload));
      Serial.println(message);
      if (message.equals(message)) {
        oled.init();
        oled.setCursor(0, 0);
        oled.setScale(2);
        oled.clear();
        oled.invertText(false);
        oled.autoPrintln(true);
        oled.print(message);
        oled.update();
        buzzerBeep();
        buzzerBeep();
        delay(500);
        buzzerBeep();
        delay(500);
        buzzerBeep();
        delay(500);
        buzzerBeep();
        delay(500);
        buzzerBeep();
        delay(500);
        buzzerBeep();
      }
      break;
  }
}



void setup() {
  pinMode(buttonPin1, INPUT);
  Serial.begin(115200);
  oled.init();
  oled.clear();
  oled.drawBitmap(0, 0, bitmap_128x64, 128, 64);
  pinMode(BUZZER_PIN, OUTPUT);
  oled.home();
  oled.update();

  //softAp(String ApName ,String ApPass)
   softAp("Rupali", "12345678");

  //softSta(String StaName ,String StaPass)
  // softSta("SMARTLAB", "C@M_SERVER@2019");


  oled.init();
  oled.clear();
  oled.drawBitmap(0, 0, bitmap_128x64, 128, 64);
  oled.update();
  if (MDNS.begin("WirelessBell")) {
    Serial.println("MDNS responder started");
  }
  MDNS.addService("http", "tcp", 80);
  server.on("/", [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", webpage);
  });
  server.on("/oled/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", webpage);
  });
  server.onNotFound(notFound);
  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  oled.update();
}
void loop(void) {

  MDNS.update();
  websockets.loop();
  buttonlick1();
}

void buttonlick1() {
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == LOW && lastButtonState1 == LOW && !messageSent1) {
    Serial.println("YES");
    websockets.broadcastTXT("Yes! Its Preparing.");
    messageSent1 = true;
    delay(500);
    oled.init();
    oled.clear();
    oled.drawBitmap(0, 0, bitmap_128x64, 128, 64);
    oled.update();
  } else if (buttonState1 == HIGH) {
    messageSent1 = false;
  }
  lastButtonState1 = buttonState1;
}
