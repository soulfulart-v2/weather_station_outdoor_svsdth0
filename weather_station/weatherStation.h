#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include "Arduino.h"
#include <map>
#include <DHT11.h>

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
        const String raw_weather_message = "{\"time\": \"#TIME#\", \"model\": \"ws2032\", \"id\": 24788, \"temperature_c\": #TEMP#, \"humidity\": #HUM#, \"wind_dir_deg\": #WINDDIR#, \"wind_avg_km_h\": #WINDS#}";
        int speed_digital_measure[turn_count];
        int speed_kmh = -1;
        int temperature = 0, humidity = 0;

        //methods
        void checkWindDirection ();
        void checkWindSpeed();
        void checkTempHum();
        void generateMessage();

};

#endif