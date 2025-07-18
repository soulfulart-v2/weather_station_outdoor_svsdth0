#include "weatherStation.h"

weatherStation::weatherStation(){
}

void weatherStation::startReadWeather(){

    this->checkWindDirection();
    this->checkWindSpeed();
    this->checkTempHum();
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

void weatherStation::checkWindSpeed(){
    int number_turns = 0, iterator = 0;

    for (iterator = 0; iterator < turn_count; iterator++){
        this->speed_digital_measure[iterator] = digitalRead(D0);
        delay(delay_wind_speed_ms);
    }

    for (iterator = 1; iterator < turn_count; iterator++){
        if (this->speed_digital_measure[iterator] != this->speed_digital_measure[iterator - 1]){
            number_turns = number_turns + 1;
        }
    }

    this->speed_kmh = number_turns * km_per_turn;

}

void weatherStation::checkTempHum(){

    DHT11 dht_sensor_0(DHT11PIN);

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht_sensor_0.readTemperatureHumidity(this->temperature, this->humidity);

}

void weatherStation::generateMessage(){


    /*String final_message = weather_message
     + wind_direction_value + 
     ", Speed: " + String(this->speed_kmh) +
     ", Temp: " + String(this->temperature) +
     ", Humidity: " + String(this->humidity);*/
    this->weather_message = raw_weather_message;
    this->weather_message.replace("#TEMP#", String(this->temperature));
    this->weather_message.replace("#HUM#", String(this->humidity));
    this->weather_message.replace("#WINDDIR#", this->wind_direction_value);
    this->weather_message.replace("#WINDS#", String(this->speed_kmh));
    Serial.println(this->weather_message);

}