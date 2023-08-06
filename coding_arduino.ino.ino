#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <AccelStepper.h>
#include "time.h"

#define DHTPIN D8
#define BUTTON D5
#define HEATER D6
#define BUZZER D7
#define MotorInterfaceType 4

#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

#define WIFI_SSID "ihsan"
#define WIFI_PASSWORD "12345678"

// Database URL and Secret
#define DATABASE_URL "tugas-akhir-eb318-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define DATABASE_SECRET "7vrfZn9i0c3KkwWoisRPpq1U3vBnTnwCXSJiCNxi"

float h, t;
int btn;

DHT dht(DHTPIN, DHTTYPE);

FirebaseData fbdo;

String databasePath;

// Database child nodes
String hPath = "/Humidity";
String tPath = "/Temperature";
String dtPath = "/Timestamp";

FirebaseJson json;

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(MotorInterfaceType, D4, D2, D3, D1);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200;
const int   daylightOffset_sec = 0;

// Variable to save current epoch time
String datetime;

// the following variables are unsigned longs because the time, measured in milliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long sendDataPrevMillis = 0;
// Set timer to 5 minutes (350000)
unsigned long timerDelay = 350000;

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi..");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current time
String getTime() {
  time_t rawtime;
  struct tm* timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  
  char currentDateTime[27];
  strftime(currentDateTime, 27, "%d-%m-%Y %T", timeinfo);
  String asString(currentDateTime);
  
  
  return currentDateTime;
}

void setup() {
  Serial.begin(115200);
  
  myStepper.setMaxSpeed(1000);
  myStepper.setAcceleration(800);
  myStepper.setSpeed(1000);
  myStepper.setCurrentPosition(0);
  myStepper.moveTo(20380); //  atur putaran
  
  pinMode(DHTPIN, INPUT);
  pinMode(HEATER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(HEATER, LOW);

  initWiFi();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getTime();

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Connect to Database
  Firebase.begin(DATABASE_URL, DATABASE_SECRET);
  
  dht.begin();
}

void loop() {
  btn = digitalRead(BUTTON);
  Serial.println(btn);
  
  if (btn == 0) {
    sendDataPrevMillis = 0;
    
    h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
    
    // Kelembapan Tinggi
    if (h >= 45.0) {
      // if (h >= 75.0) {
      // Heater Nyala
      digitalWrite(HEATER, HIGH);
      // Serial.println("Heater Hidup");
      myStepper.run();
      if (myStepper.distanceToGo() == 0) {
        send_data();
        myStepper.moveTo(-myStepper.currentPosition());
      }
    }
    // Kelembapan Rendah
    else if (h < 45.0) {
      Serial.printf("Turning On Notification ... %s\n", Firebase.RTDB.setBool(&fbdo, "doneState", true) ? "Done!" : fbdo.errorReason().c_str());
      
      // Heater Mati
      digitalWrite(HEATER, LOW);
      // Serial.println("Heater Mati");
      digitalWrite(BUZZER, HIGH);
      // Serial.println("Buzzer Nyala");
      delay(500);
      digitalWrite(BUZZER, LOW);
      // Serial.println("Buzzer Mati");
      delay(500);
      
      send_data();
    }
    Serial.print("H : ");
    Serial.print(h, 1);
    Serial.println(" %");
    Serial.print("T : ");
    Serial.print(t, 1);
    Serial.println(" C");
  }
}

void send_data() {
  // Send new readings to the database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    databasePath = "/DataSensor/";

    datetime = getTime();
    Serial.print("time: ");
    Serial.println(datetime);

    // Create a FirebaseJson object to store data along with the timestamp
    FirebaseJson json;
    json.set(dtPath.c_str(), datetime);
    json.set(hPath.c_str(), h);
    json.set(tPath.c_str(), t);
    
    // Push the FirebaseJson object to the database
    Serial.printf("Uploading Data ... %s\n", Firebase.RTDB.pushJSON(&fbdo, databasePath.c_str(), &json) ? "Done!" : fbdo.errorReason().c_str());
  }
}
