# PowerUp

PowerUp is a remote switch used to turn a PC on utilising a STM32F103C8T6, an ESP-01 and a SG-90 servo: instead of relays or modifing the motherboard, a servo arm physically presses the PC's power button on command.

## How it works

You send a message to a Telegram bot from your phone. The ESP-01, connected to your Wi-Fi, receives it and forwards a command to the STM32 over UART. The STM32 runs a servo control loop that swings the SG-90 arm onto the power button - the same finger-press, just repeatable from anywhere.

## Hardware

| Component | Role |
| --- | --- |
| STM32F103C8T6 | Main controller, runs the servo control loop |
| ESP-01 | Wi-Fi link, talks to the Telegram bot |
| SG-90 servo | Presses the PC power button |

## Repository structure

```
Code/PowerUpSTM/      STM32 firmware (STM32CubeIDE project)
Code/PowerUpESP-01/   ESP-01 sketch (Arduino IDE, esp01/esp01.ino)
```

## Setup

1. **Telegram bot:** create a bot with @BotFather to get its token, and note your chat ID.
2. **ESP-01:** open the sketch in the Arduino IDE (ESP8266 board support), create a `confidential.h` next to it defining `WIFI_SSID`, `WIFI_PASS`, `BOT_TOKEN` and `CHAT_ID`, then flash.
3. **STM32:** open the project in STM32CubeIDE, build and flash.

The `confidential.h` header with Wi-Fi and bot credentials is gitignored and intentionally not part of this repository.
