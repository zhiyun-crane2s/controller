#include "config_mode.h"
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include "settings.h"

// DNS server for captive-portal
static const byte DNS_PORT = 53;
DNSServer dnsServer;

// HTTP server on port 80
AsyncWebServer server(80);

// HTML form (you can refine this or load from LittleFS)
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head><title>GimbalBox Config</title></head>
  <body>
    <h1>Configure GimbalBox</h1>
    <form action="/save" method="POST">
      Phone Wi-Fi SSID:       <input name="ssid"  value="%SSID%"><br>
      Phone  Wi-Fi Password:   <input name="pass"  type="password"><br>
      Phone IP:         <input name="ip"    value="%IP%"><br>
      WebSocket Port:   <input name="port"  type="number" value="%PORT%"><br>
      Gimbal MAC:       <input name="mac"   value="%MAC%"><br>
      LED Enabled:      <input name="led"   type="checkbox" %LED%><br>
      Smoothness (0–100):<input name="smooth" type="range" min="0" max="100" value="%SMOOTH%"><br>
      <input type="submit" value="Save">
    </form>
  </body>
</html>
)rawliteral";

void startConfigPortal() {
  // 1. Start AP
  IPAddress apIP(192,168,4,1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));
  WiFi.softAP("GimbalBox-Setup");

  // 2. Start DNS for captive portal (redirect all domains)
  dnsServer.start(DNS_PORT, "*", apIP);

  // 3. HTTP GET / → serve form with current settings
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    String page = INDEX_HTML;
    page.replace("%SSID%",    currentSettings.wifi_ssid);
    page.replace("%IP%",      currentSettings.phone_ip);
    page.replace("%PORT%",    String(currentSettings.websocket_port));
    page.replace("%MAC%",     currentSettings.gimbal_mac);
    page.replace("%LED%",     currentSettings.led_enabled ? "checked" : "");
    page.replace("%SMOOTH%",  String(int(currentSettings.smoothness * 100)));
    req->send(200, "text/html", page);
  });

  // 4. HTTP POST /save -> grab params & save
  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *req){
    if (auto p = req->getParam("ssid", true)) currentSettings.wifi_ssid      = p->value();
    if (auto p = req->getParam("pass", true)) currentSettings.wifi_pass      = p->value();
    if (auto p = req->getParam("ip",   true)) currentSettings.phone_ip       = p->value();
    if (auto p = req->getParam("port", true)) currentSettings.websocket_port = p->value().toInt();
    if (auto p = req->getParam("mac",  true)) currentSettings.gimbal_mac     = p->value();
    currentSettings.led_enabled  = req->getParam("led", true) != nullptr;
    if (auto p = req->getParam("smooth", true)) currentSettings.smoothness   = p->value().toInt() / 100.0f;

    saveSettings();

    req->send(200, "text/html",
      "<html><body><h2>Settings Saved!</h2>"
      "<p>The device will reboot now.</p></body></html>"
    );
    delay(2000);
    ESP.restart();
  });

  // 5. Start server
  server.begin();

  // 6. Loop here handling DNS (and server runs in background)
  while (true) {
    dnsServer.processNextRequest();
    delay(1);
  }
}
