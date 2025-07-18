#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#define delta_voltage 5
#define time_read_ms 5000
#define delay_wind_speed_ms 1
#define turn_count 2000
#define km_per_turn 2.4

class weatherStation{

    public:
        //Defining common variables of the class
        String weather_message = "wind_direction: ";
        String wind_direction_value = "OO";
        int speed_kmh = -1;

        //Defining public methods
        weatherStation();
        void startReadWeather();

    private:
        //variables
        int speed_digital_measure[turn_count];
    
        //methods
        void checkWindDirection ();
        void checkWindSpeed();
        void generateMessage();

};

#endif