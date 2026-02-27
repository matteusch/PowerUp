#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// WiFi and Telegram data
const char* ssid = "#";
const char* password = "#";
const char* BOT_TOKEN = "#";
const char* CHAT_ID = "#";

// Setup a secure connection for Telegram
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// Read from chat constants
int botRequestDelay = 1000; // Check for messages every 1 second
unsigned long lastTimeBotRan = 0;

void setup() {
  // Init serial
  Serial.begin(115200);
  delay(5000); // This needs to be here, otherwise some messages don't get printed via serial

// Check for wifi connection

  Serial.println("Attempting to connect to WiFi:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connection established.");

  secured_client.setInsecure();

  bot.sendMessage(CHAT_ID, "The device is online", "");



}
//Poll for new messages
void loop() {
  if (millis() - lastTimeBotRan > botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    
    lastTimeBotRan = millis();
  }
}

//Function that reads chat contents
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    
    String chat_id = bot.messages[i].chat_id;
    
    String text = bot.messages[i].text;

    if (text == "/on") {
      Serial.println("ON");
      bot.sendMessage(chat_id, "Turning PC on...");
    }
    
    else if (text == "/status") {
      Serial.println("STATUS");
      bot.sendMessage(chat_id, "System online");
    }

    else if (text == "/off"){
      Serial.println("OFF");
      bot.sendMessage(chat_id, "Turning PC off...");
    }

    else{
      bot.sendMessage(chat_id, "Unknown command. Try: /on, /off, /status");
    }
  }
}
