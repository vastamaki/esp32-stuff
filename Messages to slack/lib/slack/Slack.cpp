#include <WiFi.h>
#include <HTTPClient.h>

void sendMessage(char *message, char *webhook_url)
{
  if (WiFi.status() == WL_CONNECTED)
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
  else
  {
    Serial.println("WiFi Disconnected");
  }
  Serial.println("WiFi Disconnected");
}
