#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "###";
const char* password = "###";
const String url = "###";

const int ledPin = 2;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");

  HTTPClient http;
  http.begin(url);
  
  // Specify content type as JSON if required by your API
  http.addHeader("Content-Type", "application/json");

  // If your API requires any data in the request body, provide it here
  String requestBody = "{}"; // Empty JSON body
  
  int httpResponseCode = http.POST(requestBody);
  if (httpResponseCode == HTTP_CODE_OK) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println();
    Serial.println(payload);

    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
    }
  }
}

void loop() {
  delay(100);
}
