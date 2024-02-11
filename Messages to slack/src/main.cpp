#include <Arduino.h>
#include <WiFi.h>
#include <Slack.cpp>

#include <Config.h>

#define LED 2
#define BUTTON_1_PIN 13
#define BUTTON_2_PIN 21

WiFiClient client;

int status = WL_IDLE_STATUS;

int button_1_last_state = HIGH;
int button_1_current_state;

int button_2_last_state = HIGH;
int button_2_current_state;

void setup()
{
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED, HIGH);
  }

  digitalWrite(LED, LOW);
}

void loop()
{
  button_1_current_state = digitalRead(BUTTON_1_PIN);
  button_2_current_state = digitalRead(BUTTON_2_PIN);

  if (button_1_last_state == LOW && button_1_current_state == HIGH)
  {
    sendMessage("{\"text\":\"Olisiko nyt sopiva aika söydä ruokaa?\"}", SLACK_WEBHOOK_URL);
  }

  if (button_2_last_state == LOW && button_2_current_state == HIGH)
  {
    sendMessage("{\"text\":\":k-market:?\"}", SLACK_WEBHOOK_URL);
  }

  button_1_last_state = button_1_current_state;
  button_2_last_state = button_2_current_state;
}
