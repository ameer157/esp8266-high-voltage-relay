#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "sside";
const char* password = "password";

ESP8266WebServer server(80);

String page = "";
int LEDPin = D5;

void setup() {
  page = "<head><style>input {border-radius: 6px; background: white; border: 0; padding: 6px; cursor: pointer;}</style><title>Bedroom LEDs</title><link href=\"data:image/x-icon;base64,AAABAAEAEBAAAAAAAABoBQAAFgAAACgAAAAQAAAAIAAAAAEACAAAAAAAAAEAAAAAAAAAAAAAAAEAAAAAAABO5/sAAAAAAAKdxgDS19UADaTIAFJXVQBL6PgAT+j9AC+vxAAFoMMAAJ7DAE7m/QBTVlQA0NXTAFe92QBO6PsATOn6AAOdwgDP1NIAAp7BAACgxAABoMQAAgICAM7T0QBQ6f0ACaPDAAGfwwBOWFMAr9nmAA+gyQAAncMAAQEBAACewgA20OgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQEBAQEMHxYfAQEBAQEBAQEBAQEBDAMDAwwBAQEBAQEBAQEBAQwNFxIMAQEBAQEBAQEBAQEMAwMNDAEBAQEBAQEBAQEBDgUFBRsBAQEBAQEBAQEBAR4ABxAVAQEBAQEBAQEBAQEVBwcHFQEBAQEBAQEBAQEIIAcHBwYVAQEBAQEBAQEBFQsHBwcHIAEBAQEBAQEBCSEHBwcHBxgTAQEBAQEBARUHBwcHBwcHFQEBAQEBAQEVBwcHBwcHBxUBAQEBAQEBFQ8HBwcHBwcVAQEBAQEBARwVBwcHBwcZHQEBAQEBAQEBAgoHBwcRFQEBAQEBAQEBAQEcGhQUBAEBAQEBAfh/AAD4PwAA+D8AAPg/AAC4OwAA2DcAAPg/AADwHwAA8B8AAOAPAABgDQAA4A8AAOAPAADgDwAA8B8AALg7AAA=\" rel=\"icon\" type=\"image/x-icon\" /><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head></head><style>body {background: #151515; color: white; text-align: center;}</style><input type=\"button\" name=\"bl\" value=\"Turn ON \" onclick=\"location.href='/ON'\"><br><br><input type=\"button\" name=\"bl\" value=\"Turn OFF\" onclick=\"location.href='/OFF'\">";
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", page);
  });
  server.on("/ON", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/OFF", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000);
  });
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}
