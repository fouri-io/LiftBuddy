#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// Wi-Fi Access Point credentials
const char* ssid = "LIFT_BUDDY_2";
const char* password = "Ward9044031391";

// Web server on port 80
WebServer server(80);

// Relay pins
const int relayUpPin = 26;
const int relayDownPin = 27;

// Timer tracking
unsigned long liftStartTime = 0;
unsigned long liftDuration = 0;
bool liftRunning = false;

void stopLift() {
  digitalWrite(relayUpPin, LOW);   // deactivate relays
  digitalWrite(relayDownPin, LOW);
  liftRunning = false;

  Serial.print("[" + String(millis()) + "] ");
  Serial.println("Lift stopped");
}

void startLift(String dir, unsigned long seconds) {
  stopLift();  // ensure clean start

  if (dir == "up") {
    digitalWrite(relayUpPin, HIGH);
    digitalWrite(relayDownPin, LOW);
  } else if (dir == "down") {
    digitalWrite(relayDownPin, HIGH);
    digitalWrite(relayUpPin, LOW);
  }

  liftDuration = seconds * 1000;
  liftStartTime = millis();
  liftRunning = true;

  Serial.print("[" + String(liftStartTime) + "] ");
  Serial.print("Lift started ");
  Serial.print(dir);
  Serial.print(" for ");
  Serial.print(seconds);
  Serial.println(" seconds");
}

// Serve main web page
void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

// Handle /start?dir=up&time=30
void handleStart() {
  if (!server.hasArg("dir") || !server.hasArg("time")) {
    server.send(400, "text/plain", "Missing dir or time");
    return;
  }

  String dir = server.arg("dir");
  unsigned long seconds = server.arg("time").toInt();
  if (seconds < 1 || seconds > 300) {
    server.send(400, "text/plain", "Invalid time range");
    return;
  }

  startLift(dir, seconds);
  server.send(200, "text/plain", "Lift started");
}

// Handle /stop
void handleStop() {
  stopLift();
  server.send(200, "text/plain", "Lift stopped");
}

void setup() {
  Serial.begin(115200);

  // Set pin HIGH *before* setting pinMode
  
  pinMode(relayUpPin, OUTPUT);
  pinMode(relayDownPin, OUTPUT);
  digitalWrite(relayDownPin, LOW);
  digitalWrite(relayUpPin, LOW);

  // Start SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Set static IP (optional)
  IPAddress local_ip(192, 168, 10, 1);
  IPAddress gateway(192, 168, 10, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  // Start Wi-Fi AP
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/start", handleStart);
  server.on("/stop", handleStop);
  server.begin();
}

void loop() {
  server.handleClient();

  // Auto stop relay if timer expired
  if (liftRunning && millis() - liftStartTime >= liftDuration) {
    stopLift();
  }
}
