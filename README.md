# ESP32 stuff

This repo contains multiple ESP32 projects. Each project is in a separate folder. The projects are written in C++ and use the PlatformIO.
This is monorepo since these are small projects and I don't want to create a separate repo for each one. Also these are not really meant to be shared with others, but rather to be used as a reference for myself.

## Projects

- slack_iot_button
  - This uses the ESP32-C3 Wi-Fi and HTTP client to send messages to a Slack channel. The idea is simple, when user presses a button, the ESP32 sends a message to a Slack channel.
  - You need to create a new file called `Config.h` and define the following constants:
    - `WIFI_SSID`
    - `WIFI_PASSWORD`
    - `SLACK_WEBHOOK_URL`
