#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include "Arduino.h"
#include <map>
#include <DHT11.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define delta_voltage 5
#define time_read_ms 3000
#define delay_wind_speed_ms 1
#define turn_count 2000
#define km_per_turn 2.4
#define DHT11PIN D2

class weatherStation{

    public:
        //Defining public methods
        weatherStation();
        void startReadWeather();

    private:
        //variables
        String wind_direction_value = "OO";
        String weather_message = "replace";
        const String raw_weather_message = "{\"time\": \"#TIME#\", \"model\": \"ws2032\", \"id\": 24788, \"temperature_c\": #TEMP#, \"humidity\": #HUM#, \"wind_dir_deg\": #WINDDIR#, \"wind_avg_km_h\": #WINDS#, \"local_ip\": #LOCAL_IP#, \"latitude\": #LATITUDE#, \"longitude\": #LONGITUDE#}";
        int speed_digital_measure[turn_count];
        int speed_kmh = -1;
        int temperature = 0, humidity = 0;
        String latitude = "00.0000", longitude = "00.0000";
        String wifi_ssid = "", wifi_pass = "";
        String local_ip = "255.255.255.0";

        //methods
        String getCurrentDate();
        void checkConnection();
        void checkWindDirection ();
        void checkWindSpeed();
        void checkTempHum();
        void generateMessage();
        void setWifiNamePass();
        void commandManager();
        void genericCommand();
        void setPosition();

};

#endif