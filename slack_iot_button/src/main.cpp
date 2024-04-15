#include <Arduino.h>
#include <WiFi.h>
#include <Slack.cpp>

#include <Config.h>

void setup()
{
  Serial.begin(115200);

  pinMode(GPIO_NUM_4, INPUT_PULLUP);
  pinMode(GPIO_NUM_3, INPUT_PULLUP);

  pinMode(GPIO_NUM_8, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.println("Connecting to WiFi..");
  }

  digitalWrite(GPIO_NUM_8, LOW);
}

void loop()
{
  uint64_t wakeup_status = esp_sleep_get_gpio_wakeup_status();

  int GPIO = log(wakeup_status) / log(2);

  if (GPIO == 3)
  {
    sendMessage("{\"text\":\":k-market:?\"}", SLACK_WEBHOOK_URL);
  }
  else if (GPIO == 4)
  {
    sendMessage("{\"text\":\"Olisiko nyt sopiva aika söydä ruokaa?\"}", SLACK_WEBHOOK_URL);
  }

  esp_deep_sleep_enable_gpio_wakeup(1 << GPIO_NUM_4, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_enable_gpio_wakeup(1 << GPIO_NUM_3, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}
