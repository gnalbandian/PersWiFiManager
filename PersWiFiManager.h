#ifndef PERSWIFIMANAGER_H
#define PERSWIFIMANAGER_H

#include <FS.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>       //https://github.com/me-no-dev/ESPAsyncTCP
#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer
#include <ESPAsyncDNSServer.h> //https://github.com/devyte/ESPAsyncDNSServer
//                             //https://github.com/me-no-dev/ESPAsyncUDP
#include <SPIFFSEditor.h>
#include <Arduino.h>
#include <Ticker.h>

//#define WIFI_HTM_PROGMEM
//#define WIFI_HTM_GZ_PROGMEM

#define WIFI_CONNECT_TIMEOUT 120

class PersWiFiManager
{

public:
  typedef std::function<void(void)> WiFiChangeHandlerFunction;

  PersWiFiManager(AsyncWebServer &s, AsyncDNSServer &d, const fs::FS& fs = SPIFFS);

  bool attemptConnection(const String &ssid = "", const String &pass = "");

  void setupWiFiHandlers();

  bool begin(const String &ssid = "", const String &pass = "");

  String getApSsid();

  void setApCredentials(const String &apSsid, const String &apPass = "");

  void setFSCredentials(const String &http_user = "admin", const String &http_pass = "password");

  void setConnectNonBlock(bool b);

  void handleWiFi();

  void startApMode();

  void onConnect(WiFiChangeHandlerFunction fn);

  void onAp(WiFiChangeHandlerFunction fn);

private:

  Ticker _tkWiFiH;
  fs::FS _fs;
  AsyncWebServer *_aserver;
  AsyncDNSServer *_adnsServer;
  String _apSsid, _apPass;
  String _fsUser = "admin", _fsPass = "password";

  bool _connectNonBlock;
  unsigned long _connectStartTime;

  WiFiChangeHandlerFunction _connectHandler;
  WiFiChangeHandlerFunction _apHandler;

}; //class

#endif
