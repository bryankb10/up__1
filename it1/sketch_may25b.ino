#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <driver/ledc.h>
#include <SimpleDHT.h>
// Define I2C pins for ESP32
#define I2C_SDA 25
#define I2C_SCL 26

// LCD display settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

// WiFi credentials
const char* ssid = "Private wifi";
const char* password = "not allowed";

// NTP client settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // UTC time, update every 60 seconds

// Timezone configuration
const int timeZoneOffsetHours = 8; // Change this to your timezone offset in hours

const int inputPin = 36;
const int buzzer = 27;
const int ledPin = 17;
const int pinDHT11 = 15;
SimpleDHT11 dht11(pinDHT11);

const int buttonSetAlarm = 18;
const int buttonHour = 23;
const int buttonMinute = 13;
const int buttontenMinute = 16; // Button pins

int val = 0;
int alarmHour;   // Variables to store alarm time
int alarmMinute;
bool alarmSet = false;
bool alarmTriggered = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(buttonHour, INPUT_PULLUP);
  pinMode(buttonMinute, INPUT_PULLUP);
  pinMode(buttonSetAlarm, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial to initialize
  }

  // Initialize I2C communication
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize the LCD display
  lcd.init();
  lcd.backlight();

  // Connect to WiFi
  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(".");
  }
  lcd.setCursor(0, 1);
  lcd.print("Connected to WiFi");
  lcd.clear();

  // Initialize NTP client
  timeClient.begin();

  // Initialize LEDC for the buzzer
  ledcSetup(0, 5000, 8); // Channel 0, 5kHz, 8-bit resolution
  ledcAttachPin(buzzer, 0); // Attach pin to channel 0
}

void digitalClockDisplay() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  int temp = temperature;
  int hum = humidity;
  char timeBuffer[9];
  char dateBuffer[11];
  sprintf(timeBuffer, "%02d:%02d:%02d", hour(), minute(), second());
  sprintf(dateBuffer, "%02d/%02d/%04d", day(), month(), year());
  lcd.setCursor(0, 0); // Set cursor to the first line
  lcd.print("Time: ");
  lcd.print(timeBuffer);
  lcd.setCursor(0, 1); // Set cursor to the second line
  lcd.print(dateBuffer);
  lcd.setCursor(12,1);
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");
}

void playTone(int frequency, int duration) {
  ledcWriteTone(0, frequency);
  delay(duration);
  ledcWriteTone(0, 0); // Turn off tone
}

void spiderman() {
  int note_C5 = 523;
  int note_Cs5 = 554;
  int note_Gs5 = 831;
  int note_G5 = 784;
  int duration = 213;
  int duration_2 = 490;
  int note_C4 = 262;
  int note_Cs4 = 277;
  int note_Gs4 = 415;
  int note_G4 = 392;

  playTone(note_C5, duration);
  playTone(note_Cs5, duration);
  playTone(note_C5, duration);
  playTone(note_Cs5, duration);
  playTone(note_Gs5, duration);
  playTone(note_G5, duration_2);

  delay(2000); // Note duration (in milliseconds)
}

void triggerAlarm() {
  alarmTriggered = true;
  alarmHour = 0;
  alarmMinute = 0;
  Serial.println("Alarm triggered");
  while (alarmTriggered) {
    digitalWrite(ledPin, HIGH);
    spiderman();
    delay(500);
    digitalWrite(ledPin, LOW);
    spiderman();
    delay(500);

    // Read motion sensor input
    int reading = digitalRead(inputPin);
    if (reading == HIGH) {
      Serial.println("Motion detected, turning off alarm");
      ledcWriteTone(0, 0); // Turn off tone
      digitalWrite(ledPin, LOW);
      alarmTriggered = false;
      break;
    }
  }
}

void checkAlarm() {
  if (alarmSet && hour() == alarmHour && minute() == alarmMinute && second() >= 0 && second() <= 2) {
    triggerAlarm();
  }
}

void updateTimeFromNTP() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  setTime(epochTime + timeZoneOffsetHours * 3600);
}

void updateAlarmTime() {
  lcd.clear();
  if(digitalRead(buttonHour) == LOW) {
    alarmHour = (alarmHour + 1) % 24;
    lcd.setCursor(0, 0);
    lcd.print("Alarm =");
    lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute);
    delay(1000);
  }
  else if(digitalRead(buttonMinute) == LOW) {
    alarmMinute = (alarmMinute + 1) % 60;
    lcd.setCursor(0, 0);
    lcd.print("Alarm =");
    lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute);
    delay(1000);
  }
  else if(digitalRead(buttontenMinute) == LOW) {
    alarmMinute = (alarmMinute + 10) % 60;
    lcd.setCursor(0, 0);
    lcd.print("Alarm =");
    lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute);
    delay(1000);
  }
  else if(digitalRead(buttonSetAlarm) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALARM SET");
    lcd.setCursor(0, 1);
    lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute);
    delay(1000);
    alarmSet = true;
    if(alarmSet) {
      Serial.print("alarm set");
    }
  }
}

void loop() {
  updateTimeFromNTP();
  updateAlarmTime();
  val = digitalRead(inputPin);
  if (alarmSet) {
    checkAlarm();
  }
  digitalClockDisplay();
  delay(1000);
}
