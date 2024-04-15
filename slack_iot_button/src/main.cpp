#include <Arduino.h>
#include <WiFi.h>
#include <Slack.cpp>

#include <Config.h>

#define LED 8
#define BUTTON_1_PIN 4
#define BUTTON_2_PIN 21

void setup()
{
  Serial.begin(115200);

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  pinMode(LED, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
  }

  digitalWrite(LED, LOW);
}

void loop()
{
  delay(1000);
  uint64_t wakeup_status = esp_sleep_get_gpio_wakeup_status();

  int GPIO = log(wakeup_status) / log(2);

  Serial.println(GPIO);

  if (GPIO == 4)
  {
    sendMessage("{\"text\":\":k-market:?\"}", SLACK_WEBHOOK_URL);
  }
  else if (GPIO == 5)
  {
    sendMessage("{\"text\":\"Olisiko nyt sopiva aika söydä ruokaa?\"}", SLACK_WEBHOOK_URL);
  }

  esp_deep_sleep_enable_gpio_wakeup(1 << BUTTON_1_PIN, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}
