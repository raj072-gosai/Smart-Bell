#include "lib.h"

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    webSocket.sendTXT(num, "Connected from server");
  }
  break;
  case WStype_TEXT:
    Serial.printf("[%u] get Text: %s\n", num, payload);
    String message = String((char *)(payload));
    Serial.println(message);
    if (message.equals(message))
    {
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

void setup()
{
  pinMode(buttonPin1, INPUT);
  Serial.begin(115200);
  oled.init();
  oled.clear();
  oled.drawBitmap(0, 0, bitmap_128x64, 128, 64);
  pinMode(BUZZER_PIN, OUTPUT);
  oled.home();
  oled.update();

  // softAp(String ApName ,String ApPass)
  // softAp("SmartBell", "12345678");

  // softSta(String StaName ,String StaPass)
  //  softSta("SMARTLAB", "C@M_SERVER@2019");

  // Initialize WiFiManager
  WiFiManager wifiManager;
  wifiManager.setMinimumSignalQuality(8);
  wifiManager.setTimeout(120); // 2 minutes

  if (!wifiManager.autoConnect("SmartBell"))
  {
    Serial.println("Failed to connect and hit timeout");
    // Reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }
  // if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  oled.init();
  oled.clear();
  oled.drawBitmap(0, 0, bitmap_128x64, 128, 64);
  oled.update();
  if (MDNS.begin("smartbell"))
  {
    Serial.println("MDNS responder started");
  }
  MDNS.addService("http", "tcp", 80);
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.on("/", handleMain);
  server.onNotFound(handleNotFound);
  server.begin();
  oled.update();
}
void loop(void)
{

  MDNS.update();
  websockets.loop();
  server.handleClient();
  buttonlick1();
}

void buttonlick1()
{
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == LOW && lastButtonState1 == LOW && !messageSent1)
  {
    Serial.println("YES");
    websockets.broadcastTXT("Yes! Its Preparing.");
    messageSent1 = true;
    delay(500);
    oled.init();
    oled.clear();
    oled.drawBitmap(0, 0, bitmap_128x64, 128, 64);
    oled.update();
  }
  else if (buttonState1 == HIGH)
  {
    messageSent1 = false;
  }
  lastButtonState1 = buttonState1;
}
void handleMain()
{
  server.send_P(200, "text/html", webpage);
}

void handleNotFound()
{
  server.send(404, "text/html", "<html><body><p>404 Error</p></body></html>");
}