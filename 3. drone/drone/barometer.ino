#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Create an instance of the BMP180 sensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void barometer_setup()
{
    Serial.begin(9600);
    Serial.println("BMP180 Test");

    // Initialize the BMP180 sensor
    led_output(1, 1, 0);
    while (true)
    {
        if (bmp.begin())
        {
            Serial.println("BMP180 connection successful");
            break; // Connection successful
        }
        else
        {
            Serial.println("Could not find a valid BMP180 sensor, check wiring!"); // connection failed
            blinkLED(green2, 500);
        }
    }
}

void find_height()
{
    // Get the sensor event
    sensors_event_t event;
    bmp.getEvent(&event);

    // Check if the event is valid
    if (event.pressure)
    {
        // Get the temperature
        float temperature;
        bmp.getTemperature(&temperature);

        // Calculate altitude
        float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA; // Use a known sea level pressure for your location
        float altitude = bmp.pressureToAltitude(seaLevelPressure, event.pressure, temperature);

        // Print the results
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        Serial.print("Pressure: ");
        Serial.print(event.pressure);
        Serial.println(" hPa");

        Serial.print("Altitude: ");
        Serial.print(altitude);
        Serial.println(" meters");
    }
    else
    {
        Serial.println("Sensor error");
    }
}
