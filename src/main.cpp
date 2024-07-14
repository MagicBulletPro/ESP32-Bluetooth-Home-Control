#include "BluetoothSerial.h"
#include <ArduinoJson.h>

BluetoothSerial SerialBT;

// Function declarations
void toggleGPIO(JsonDocument jsonDoc);
void syncController(JsonDocument jsonDoc);
void checkData(String payload);

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  // Initialize Bluetooth Serial with device name "ESP32_BT"
  SerialBT.begin("ESP32-BT");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop()
{
  // Check if there is data available from the Bluetooth connection
  if (SerialBT.available())
  {
    // Read the incoming data as a string
    String payload = SerialBT.readString();
    // Process the received data
    checkData(payload);
  }
  // Short delay to prevent overwhelming the processor
  delay(20);
}

void checkData(String payload)
{
  // Create a JSON document
  JsonDocument jsonDoc;
  // Deserialize the JSON document from the payload
  DeserializationError error = deserializeJson(jsonDoc, payload);
  // Check if the JSON deserialization was successful
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  // Check if the root of the JSON document is an object
  if (!jsonDoc.is<JsonObject>())
  {
    Serial.println(F("The root of the JSON document is not an object"));
    return;
  }

  // Extract the "type" field from the JSON document
  String type;
  if (jsonDoc.containsKey("type"))
  {
    type = jsonDoc["type"].as<String>();
    // Determine the action based on the type
    if (type == "command")
    {
      toggleGPIO(jsonDoc);
    }
    else if (type == "sync")
    {
      syncController(jsonDoc);
    }
    else
    {
      Serial.print(F("Unknown type: "));
      Serial.println(type);
    }
  }
  else
  {
    Serial.println(F("Key 'type' not found in JSON"));
  }
}

void toggleGPIO(JsonDocument jsonDoc)
{
  // Check if the JSON document contains the "accessory" key
  if (jsonDoc.containsKey("accessory"))
  {
    // Extract the accessory object from the JSON document
    JsonObject accessory = jsonDoc["accessory"];
    int accessory_id = accessory["acc_id"].as<int>();
    const char *name = accessory["name"].as<const char *>();
    int pin_number = accessory["gpio"].as<int>();
    bool pin_status = accessory["status"].as<bool>();

    // Set the pin mode to output and set the pin status
    pinMode(pin_number, OUTPUT);
    digitalWrite(pin_number, pin_status);
    Serial.println("GPIO " + String(pin_number) + " " + (pin_status ? "ON" : "OFF"));
  }
  else
  {
    Serial.println(F("Key 'accessory' not found in JSON"));
  }
}

void syncController(JsonDocument jsonDoc)
{
  // Check if the JSON document contains the "accessory_list" key
  if (jsonDoc.containsKey("accessory_list"))
  {
    // Extract the accessory list array from the JSON document
    JsonArray accessory_list = jsonDoc["accessory_list"];
    // Iterate through each accessory in the list
    for (JsonObject accessory : accessory_list)
    {
      int accessory_id = accessory["acc_id"].as<int>();
      const char *name = accessory["name"].as<const char *>();
      int pin_number = accessory["gpio"].as<int>();
      bool pin_status = accessory["status"].as<bool>();

      // Set the pin mode to output and set the pin status
      pinMode(pin_number, OUTPUT);
      digitalWrite(pin_number, pin_status);
    }
    Serial.println("Sync completed");
  }
}
