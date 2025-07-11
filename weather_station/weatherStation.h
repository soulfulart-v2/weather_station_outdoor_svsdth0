#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#define delta_voltage 5
#define time_read_ms 300

class weatherStation{

    public:
        //Defining common variables of the class
        String weather_message = "wind_direction: ";
        String wind_direction_value = "OO";

        //Defining public methods
        weatherStation();
        void startReadWeather();

    private:
        void checkWindDirection ();
        void generateMessage();

};

#endif