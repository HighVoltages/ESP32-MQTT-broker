#include<sMQTTBroker.h>


const char* MQTT_CLIENT_USER = "Admin"; // username for mqtt clients. Set your own value here.
const char* MQTT_CLIENT_PASSWORD = "High voltages"; // password for mqtt clients. Set your own value here.


class MyBroker:public sMQTTBroker
{
public:
    bool onEvent(sMQTTEvent *event) override
    {
        switch(event->Type())
        {
        case NewClient_sMQTTEventType:
            {
                sMQTTNewClientEvent *e=(sMQTTNewClientEvent*)event;
                // Check username and password used for new connection
                if ((e->Login() != MQTT_CLIENT_USER) || (e->Password() != MQTT_CLIENT_PASSWORD)) {
                  Serial.println("Invalid username or password");  
                  return false;
                  }
            };
            break;
        case LostConnect_sMQTTEventType:
            WiFi.reconnect();
            break;
        case UnSubscribe_sMQTTEventType:
        case Subscribe_sMQTTEventType:
            {
                sMQTTSubUnSubClientEvent *e=(sMQTTSubUnSubClientEvent*)event;
            }
            break;
        }
        return true;
    }
};


MyBroker broker;



void setup()
{
    Serial.begin(115200);
      // Set up Wi-Fi in Access Point mode
  const char *ssid = "SSID";
const char *password = "Password";
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
    }
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
   
    const unsigned short mqttPort=1883;
    broker.init(mqttPort);
    // all done
    // your magic code

};
void loop()
{
    broker.update();
    // your code here
};
