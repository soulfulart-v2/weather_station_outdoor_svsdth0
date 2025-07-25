#include <weatherStation.h>

weatherStation weatherStation_zero;

int count_it = 0;

void setup(){
  Serial.begin(9600);
  pinMode (D0, INPUT);
}

void loop() {

  weatherStation_zero.startReadWeather();

}