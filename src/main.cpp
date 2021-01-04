#include <Arduino.h>
#include "AnimationController.h"
#include "TacticSwitchController.h"
#include "MotionSensorController.h"
#include "ClassicSwitchController.h"

#include <ESP8266WiFi.h>

#ifdef __AVR__
    #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 60 // Popular NeoPixel ring size

#define SENSOR_A_PIN 13
#define SENSOR_B_PIN 15

AnimationController<ClassicSwitchController> animationController(NUMPIXELS, PIN, SENSOR_A_PIN, SENSOR_B_PIN, 35);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write("Setup");

  WiFi.mode(WIFI_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
  animationController.update();
}