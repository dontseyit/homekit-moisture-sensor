#include <homekit/homekit.h>
#include <homekit/characteristics.h>

// Called to identify this accessory. See HAP section 6.7.6 Identify Routine
// Generally this is called when paired successfully or click the "Identify Accessory" button in Home APP.
void my_accessory_identify(homekit_value_t _value)
{
    printf("accessory identify\n");
}

// For MOISTURE_SENSOR,
// the required characteristics are: CURRENT_RELATIVE_HUMIDITY
// the optional characteristics are: NAME, STATUS_ACTIVE, STATUS_FAULT, STATUS_TAMPERED, STATUS_LOW_BATTERY
// See HAP section 8.41 and characteristics.h

// (required) format: float; HAP section 9.35; min 0, max 100, step 0.1, unit celsius
homekit_characteristic_t cha_current_humidity = HOMEKIT_CHARACTERISTIC_(CURRENT_RELATIVE_HUMIDITY, 0);

// (optional) format: string; HAP section 9.62; max length 64
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "Moisture Sensor");

// (optional): Adapt the characteristics to your needs
homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id = 1, .category = homekit_accessory_category_sensor, .services = (homekit_service_t *[]) {
      HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics = (homekit_characteristic_t *[]) {
        HOMEKIT_CHARACTERISTIC(NAME, "Moisture Sensor 1"), 
        HOMEKIT_CHARACTERISTIC(MANUFACTURER, "ad hoc"), 
        HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"), 
        HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"), 
        HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"), 
        HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify), 
        NULL
      }),
        HOMEKIT_SERVICE(HUMIDITY_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &cha_current_humidity,
            &cha_name,
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"};