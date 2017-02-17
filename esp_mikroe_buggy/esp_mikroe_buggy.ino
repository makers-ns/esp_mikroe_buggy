/*********************************************************************************
  Copyright (c) 2017 ChedaDSP@Makers-NS. All right reserved.

  esp2866 as web controller for MikroE Buggy

  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*****************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <Hash.h>
#include "buggy.h"

#define AP_MODE 1
//AP mode 1, WiFi clident 0

//////////////////////
// WiFi Definitions //
//////////////////////
#if AP_MODE
const char WiFiSSID[] = "espbuggy1";
const char WiFiAPPSK[] = "espbuggy1";
#else
const char* ssid = "yourSSIDhere";
const char* password = "yourPASShere";
#endif
const char host[] = "buggy";

ESP8266WebServer server(80);

void drive(){
  int direction = 0, throttle = 0; 
  if(server.hasArg("d")) {
    direction = server.arg("d").toInt();
  }
    if(server.hasArg("t")) {
    throttle = server.arg("t").toInt();
  }
  
  moveBuggy(direction, throttle);
  
  //Must play nice and return 200OK
  server.send(200, "text/plain", server.arg(0));
}

void setup(void)
{
  setupBuggy();

  Serial.begin(74880);
  Serial.setDebugOutput(true);

#if AP_MODE
  // Turn on AP MODE
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WiFiSSID, WiFiAPPSK);
#else
    //WIFI INIT
  Serial.printf("Connecting to %s\n", ssid);
  if (String(WiFi.SSID()) != String(ssid)) {
    WiFi.begin(ssid, password);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
#endif
  
  server.begin();
  
  SPIFFS.begin();
  MDNS.begin(host);
  Serial.print("Open http://");
  Serial.print(host);
  Serial.println(" to see conroler");
  
  //SERVER INIT
  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  // REST end point
  server.on("/drive", drive );
  
  server.begin();
  // Add service to MDNS
  MDNS.addService("http", "tcp", 80);
  Serial.println("HTTP server started");

}
 
void loop(void)
{
  server.handleClient();
}
