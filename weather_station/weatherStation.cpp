#include "Arduino.h"
#include "weatherStation.h"
#include <map>

weatherStation::weatherStation(){
}

void weatherStation::startReadWeather(){

    this->checkWindDirection();
    this->generateMessage();
    delay(time_read_ms);

}

void weatherStation::checkWindDirection(){

    int voltage_measure = analogRead(A0);

    std::map<String, int> wind_direction_map = {
        {"S", 835},
        {"W", 800},
        {"N", 953},
        {"E", 909},
        {"SE", 974},
        {"SW", 934},
        {"NE", 1009},
        {"NW", 990}
    };

    for (auto it = wind_direction_map.begin(); it != wind_direction_map.end(); ++it) {
        if (voltage_measure >= it->second - delta_voltage && voltage_measure <= it->second + delta_voltage){
            this->wind_direction_value = String(it->first);
            break;
        }
    }

}

void weatherStation::generateMessage(){

    String final_message = weather_message + wind_direction_value;
    Serial.println(final_message);

}