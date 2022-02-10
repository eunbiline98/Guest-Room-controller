#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Kost Pak Josa";
const char *password = "joputra1";
const char *MQTT_SERVER = "192.168.1.21";

const char *MQTT_TOPIC1 = "relay/1/state";
const char *MQTT_TOPIC2 = "relay/2/state";
const char *MQTT_TOPIC3 = "relay/3/state";
const char *MQTT_TOPIC4 = "relay/4/state";
const char *MQTT_TOPIC5 = "relay/5/state";
const char *MQTT_TOPIC6 = "relay/6/state";
const char *MQTT_TOPIC7 = "relay/7/state";
const char *MQTT_TOPIC8 = "relay/8/state";

const char *R1 = "relay/1/cmd";
const char *R2 = "relay/2/cmd";
const char *R3 = "relay/3/cmd";
const char *R4 = "relay/4/cmd";
const char *R5 = "relay/5/cmd";
const char *R6 = "relay/6/cmd";
const char *R7 = "relay/7/cmd";
const char *R8 = "relay/8/cmd";

const char *MQTT_CLIENT_ID = "guest_room_1";
const char *MQTT_USERNAME = "admin";
const char *MQTT_PASSWORD = "admin";

WiFiClient espClient;
PubSubClient client(espClient);

// Pin Setup
#define relay_1 15
#define relay_2 12
#define relay_3 5
#define relay_4 18
#define relay_5 19
#define relay_6 21
#define relay_7 22
#define relay_8 23

#define keyCard 13
#define btn_1 12
#define btn_2 14
#define btn_3 27
#define btn_4 26
#define btn_5 25

int lastMilis = 0;
unsigned long nowMillis = millis();

void setup_wifi()
{
  // Connect to Wifi Network
  pinMode(4, OUTPUT); // WiFi Indicator
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(4, HIGH);
    delay(80);
    digitalWrite(4, LOW);
    delay(80);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    Serial.println();
    if ((char)message[i] != '"')
      messageTemp += (char)message[i];
  }

  if (String(topic) == R1)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_1, HIGH);
      client.publish(MQTT_TOPIC1, "1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_1, LOW);
       client.publish(MQTT_TOPIC1,"0");
    }
  }

  if (String(topic) == R2)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_2, HIGH);
      client.publish(MQTT_TOPIC2,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_2, LOW);
      client.publish(MQTT_TOPIC2,"0");
    }
  }

  if (String(topic) == R3)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_3, HIGH);
      client.publish(MQTT_TOPIC3,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_3, LOW);
      client.publish(MQTT_TOPIC3,"0");
    }
  }

  if (String(topic) == R4)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_4, HIGH);
      client.publish(MQTT_TOPIC4,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_4, LOW);
      client.publish(MQTT_TOPIC4,"0");
    }
  }

  if (String(topic) == R5)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_5, HIGH);
      client.publish(MQTT_TOPIC5,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_5, LOW);
      client.publish(MQTT_TOPIC5,"0");
    }
  }

  if (String(topic) == R6)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_6, HIGH);
      client.publish(MQTT_TOPIC6,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_6, LOW);
      client.publish(MQTT_TOPIC6,"0");
    }
  }

  if (String(topic) == R7)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_7, HIGH);
      client.publish(MQTT_TOPIC7,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_7, LOW);
      client.publish(MQTT_TOPIC7,"0");
    }
  }

  if (String(topic) == R8)
  {
    if (messageTemp == "1")
    {
      digitalWrite(relay_8, HIGH);
      client.publish(MQTT_TOPIC8,"1");
    }
    else if (messageTemp == "0")
    {
      digitalWrite(relay_8, LOW);
      client.publish(MQTT_TOPIC8,"0");
    }
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
    {
      Serial.println("connected");
      // subscribe
      client.subscribe(R1);
      client.subscribe(R2);
      client.subscribe(R3);
      client.subscribe(R4);
      client.subscribe(R5);
      client.subscribe(R6);
      client.subscribe(R7);
      client.subscribe(R8);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  setup_wifi();

  // MQTT Server Setup
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);

  pinMode(4, OUTPUT); // WiFi Indicator
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);
  pinMode(relay_8, OUTPUT);

  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
  pinMode(btn_3, INPUT);
  pinMode(btn_4, INPUT);
  pinMode(btn_5, INPUT);
  pinMode(keyCard, INPUT);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
