/* 
 * Adafruit Sub/Pub: Example for how to publish/subscribe to Adafruit.io feeds
 * Author: Daniel Stromberg
 * Date: 6/7/24
 */

#include "Particle.h"
#include <Adafruit_MQTT.h>      //Install Adafruit_MQTT library
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentials.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

//Variables
int subData;
int totalPassCount = 14;
int lastPubTime = 0;

void MQTT_connect();
bool MQTT_ping();
void adaPublish();

TCPClient TheClient;
Adafruit_MQTT_SPARK mqtt(&TheClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe exampleSub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/flower4passcount");
Adafruit_MQTT_Publish examplePub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/totalflowerpass");


void setup() {
    Serial.begin(9600);

    mqtt.subscribe(&exampleSub);    //include one for each thing you're subscribing to
}

void loop() {
    MQTT_connect();     //Connects to Adafruit anytime it disconnects
    MQTT_ping();        //Keeps the connection alive

    Adafruit_MQTT_Subscribe *subscription;
    while((subscription = mqtt.readSubscription(100))){
        if(subscription == &exampleSub){
            subData = strtol((char *)exampleSub.lastread, NULL, 10);
        }
        //if subscribing to more than one item, add them to this if statement like so:
        // }else if(subscription ==&example2Sub){
        //      do something
        // }
    }
}

//Publish to Adafruit.io (publish infrequently - Adafruit gets mad if you do too many)
//      I believe 6 per minute is the limit for a free account. Check for paid account limits.
void adaPublish(){
    if((millis()-lastPubTime)>30000){     //in this example, it is limited to once every 30 seconds
        if(mqtt.Update()){
            examplePub.publish(totalPassCount);
            lastPubTime = millis();
        }
    }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care of connecting.
void MQTT_connect(){
    int8_t ret;

    // Return if already connected.
    if (mqtt.connected()){
        return;
    }

    Serial.print("Connecting to MQTT... ");

    while((ret = mqtt.connect()) != 0){
        Serial.printf("Error Code %s\n", mqtt.connectErrorString(ret));
        Serial.printf("Retrying MQTT connection in 5 seconds...\n");
        mqtt.disconnect();
        delay(5000);
    }
    Serial.printf("MQTT Connected!\n");
}

//Keeps the connection open to Adafruit
bool MQTT_ping() {
    static unsigned int last;
    bool pingStatus;

    if ((millis()-last)>120000) {
        Serial.printf("Pinging MQTT \n");
        pingStatus = mqtt.ping();
        if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
        }
        last = millis();
    }
    return pingStatus;
}