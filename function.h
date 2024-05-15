#define BUZZER_PIN D5
int buzzerState = LOW;
const int buttonPin1 = 12;
int buttonState1 = 0;
int lastButtonState1 = LOW;
bool messageSent1 = false;


IPAddress local_IP(192, 168, 1, 28);
IPAddress gateway(192, 168, 1, 28);
IPAddress subnet(255, 255, 0, 0);

void buzzerBeep() 
{
  tone(BUZZER_PIN,10,1000); // Beep at 1000 Hz for 500 milliseconds
  delay(100); // Add a short delay to distinguish individual beeps
  tone(BUZZER_PIN, 0, 0); 
}

void WiFimanager(String ApName){

}

void softAp(String ApName ,String ApPass){
    WiFi.softAP(ApName, ApPass);
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
   Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP()); 
}

void softSta(String StaName ,String StaPass){
  if (!WiFi.config(local_IP, gateway, subnet))//, primaryDNS, secondaryDNS))
  {
    Serial.println("STA Failed to configure");
  }  
    WiFi.mode(WIFI_STA);
    WiFi.begin(StaName, StaPass);
    while (WiFi.status() != WL_CONNECTED) 
    {
         delay(1000);
         Serial.println("Connecting to WiFi...");
    }

  Serial.println(WiFi.localIP());

}
