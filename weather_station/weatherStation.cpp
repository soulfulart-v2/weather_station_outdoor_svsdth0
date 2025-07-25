#include "weatherStation.h"

weatherStation::weatherStation(){
}

void weatherStation::startReadWeather(){

    this->checkWindDirection();
    this->checkWindSpeed();
    this->checkTempHum();
    this->checkConnection();
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

void weatherStation::checkConnection(){

    if (WiFi.status() != WL_CONNECTED){
        WiFi.mode(WIFI_STA);
        WiFi.begin(this->wifi_ssid, this->wifi_pass);
    }
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    this->local_ip = WiFi.localIP().toString();

}

String weatherStation::getCurrentDate(){

    this->checkConnection();

    String current_time_measure = "YYYY-MM-DD hh:mm:ss";
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP);

    timeClient.begin();
    timeClient.update();
    delay(500); //time to update
    time_t raw_time = timeClient.getEpochTime();
    struct tm *ptm = gmtime(&raw_time);

    current_time_measure.replace("YYYY", String(ptm->tm_year + 1900));

    if (ptm->tm_mon + 1 < 10){
        current_time_measure.replace("MM", "0" + String(ptm->tm_mon + 1));
    }
    else {
        current_time_measure.replace("MM", String(ptm->tm_mon + 1));
    }

    if (ptm->tm_mday < 10){
        current_time_measure.replace("DD", "0" + String(ptm->tm_mday));
    }
    else {
        current_time_measure.replace("DD", String(ptm->tm_mday));
    }

    if (ptm->tm_hour < 10){
        current_time_measure.replace("hh", "0" + String(ptm->tm_hour));
    }
    else {
        current_time_measure.replace("hh", String(ptm->tm_hour));
    }

    if (ptm->tm_min < 10){
        current_time_measure.replace("mm", "0" + String(ptm->tm_min));
    }
    else {
        current_time_measure.replace("mm", String(ptm->tm_min));
    }

    if (ptm->tm_sec < 10){
        current_time_measure.replace("ss", "0" + String(ptm->tm_sec));
    }
    else {
        current_time_measure.replace("ss", String(ptm->tm_sec));
    }

    return String(current_time_measure);

}

void weatherStation::generateMessage(){

    this->weather_message = raw_weather_message;
    this->weather_message.replace("#TIME#", this->getCurrentDate());
    this->weather_message.replace("#TEMP#", String(this->temperature));
    this->weather_message.replace("#HUM#", String(this->humidity));
    this->weather_message.replace("#WINDDIR#", this->wind_direction_value);
    this->weather_message.replace("#WINDS#", String(this->speed_kmh));
    this->weather_message.replace("#LOCAL_IP#", String(this->local_ip));
    Serial.println(this->weather_message);

}