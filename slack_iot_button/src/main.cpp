#include <Arduino.h>
#include <WiFi.h>
#include <Slack.cpp>

#include <Config.h>

#define LED_PIN GPIO_NUM_10

void setup()
{
  Serial.begin(115200);

  pinMode(GPIO_NUM_4, INPUT_PULLUP);
  pinMode(GPIO_NUM_3, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.println("Connecting to WiFi..");
  }

  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  uint64_t wakeup_status = esp_sleep_get_gpio_wakeup_status();

  int GPIO = log(wakeup_status) / log(2);

  if (GPIO == 3)
  {
    digitalWrite(LED_PIN, HIGH);
    sendMessage("{\"text\":\":k-market:?\"}", SLACK_WEBHOOK_URL);
    digitalWrite(LED_PIN, LOW);
  }
  else if (GPIO == 4)
  {
    digitalWrite(LED_PIN, HIGH);
    sendMessage("{\"text\":\"Olisiko nyt sopiva aika söydä ruokaa?\"}", SLACK_WEBHOOK_URL);
    digitalWrite(LED_PIN, LOW);
  }

  esp_deep_sleep_enable_gpio_wakeup(1 << GPIO_NUM_4, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_enable_gpio_wakeup(1 << GPIO_NUM_3, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}
