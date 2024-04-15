#include <WiFi.h>
#include <HTTPClient.h>

void sendMessage(const char *message, const char *webhook_url)
{
  HTTPClient http;

  http.begin(webhook_url);

  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(message);

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
