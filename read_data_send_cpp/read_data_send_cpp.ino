#include <weatherStation.h>

weatherStation weatherStation_zero;

void setup(){
  Serial.begin(9600);
  pinMode (D0, INPUT);
}

void loop() {

  weatherStation_zero.startReadWeather();

}