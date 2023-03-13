#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// define the pins used by the transceiver module
#define cs D8
#define rst D4
#define dio0 D2

int counter = 0;

void setup()
{
    // initialize Serial Monitor
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println("LoRa Sender");

    // setup LoRa transceiver module
    LoRa.setPins(cs, rst, dio0);

    // replace the LoRa.begin(---E-) argument with your location's frequency
    // 433E6 for Asia
    // 866E6 for Europe
    // 915E6 for North America
    while (!LoRa.begin(866E6))
    {
        Serial.println(".");
        delay(500);
    }
    // Change sync word (0xF3) to match the receiver
    // The sync word assures you don't get LoRa messages from other LoRa transceivers
    // ranges from 0-0xFF
    LoRa.setTxPower(17);
    // LoRa.setSpreadingFactor(8);
    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa Initializing OK!");
}

void loop()
{
    Serial.print("Sending packet: ");
    Serial.println(counter);

    // Send LoRa packet to receiver
    LoRa.beginPacket();
    LoRa.print("This is a string containing at least a hundred characters. Made with the purpose of showcasing Lora's capabilities");
    LoRa.print(counter);
    LoRa.endPacket();

    counter++;

    delay(1000);
}
