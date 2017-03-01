/**
 *  This file is part of BBC Notif.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2017 Jérôme Labidurie jerome@labidurie.fr
 */

/**
 * Behaviour
 * ---------
 * -> power on
 * if smail present:
 *   reset wifi config from eeprom
 * tries to connect to wifi stored in eeprom
 * if ok:
 *   start web server with config infos for 1 min
 *   go to deepsleep
 * else
 *   start AP and wait for configuration via web server
 *   start web server with config infos for 1 min
 *   go to deepsleep
 *
 * -> wake up from deepsleep
 * if smail present:
 *   if no email send:
 *     tries to connect to wifi stored in eeprom
 *     send Email
 * go to deepsleep
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include "Gsender.h"

extern "C" {
#include "user_interface.h"
extern struct rst_info resetInfo;
}

#define BUTTON D1

#define SLEEP_SEC 10

#define HOSTNAME "BrainBox"
#define baseSSID "BBC-"
#define VERSION "BrainBox v1.0"
#define MYSSID_LEN 13
char mySSID[MYSSID_LEN];

ESP8266WebServer server(80);
unsigned long sleepTime = 0;

void setup (void) {
	uint32_t emailState = 0; /** is email has been send ? */

	EEPROM.begin(512);
	pinMode (BUTTON,      INPUT);
	pinMode (BUILTIN_LED, OUTPUT);
	digitalWrite (BUILTIN_LED, HIGH);

	Serial.begin (115200);
	Serial.printf ("\n\n%s\n", VERSION);
	Serial.println (ESP.getResetReason());

	if ( resetInfo.reason == REASON_DEEP_SLEEP_AWAKE ) {
		// read email state
		ESP.rtcUserMemoryRead (0, &emailState, 4);
		Serial.printf ("emailState:%d\n", emailState);
		if (isMail() ) {
			if (emailState == 0) {
				// wake up from deep-sleep, there's mail and email not yet send
				setupWifi();

				// read email from eeprom
				char email[100];
				memset (email, 0, 100);
				for (int i=0; i < 100; i++) {
					email[i] = char(EEPROM.read(i+32+64));
				}
				sendEmail (email);
				// store email send state in RTC memory
				emailState = 1;
				ESP.rtcUserMemoryWrite (0, &emailState, 4);
			}
		} else {
				// store email not send state in RTC memory
				emailState = 0;
				ESP.rtcUserMemoryWrite (0, &emailState, 4);
		}
		Serial.printf("Sleep for %d seconds ...\n", SLEEP_SEC);
		ESP.deepSleep(SLEEP_SEC * 1000000);
	} else if ( resetInfo.reason != REASON_DEEP_SLEEP_AWAKE ) {
		// store email not send state in RTC memory
		emailState = 0;
		ESP.rtcUserMemoryWrite (0, &emailState, 4);
		if (isMail()) {
			// switched on and mail, assume we want to reset
			Serial.println("reset wifi config");
			wicoResetWifiConfig (0);
		}
		setupWifi();
		// set DeepSleep time at now + 1min
		sleepTime = millis() + 60 * 1000;
	}
} // setup()

void loop(void) {
	server.handleClient();
	if ( (sleepTime != 0) && (millis() >= sleepTime) ) {
		sleepTime = 0;
		Serial.printf("Sleep for %d seconds after wifi config ...\n", SLEEP_SEC);
		ESP.deepSleep(SLEEP_SEC * 1000000);
	}
} // loop()

void setupWifi (void) {
	uint8_t r = 0;
	IPAddress myIP;
        char mySSID[MYSSID_LEN];
	uint8_t mac[6];

	// create ~uniq ssid
	WiFi.macAddress(mac);
        snprintf (mySSID, MYSSID_LEN, "%s%02X%02X", baseSSID, mac[4], mac[5]);

	// setup wifi
	do {
		r = wicoWifiConfig (0, mySSID, &myIP);
		Serial.println(myIP);
		if (r == 0 ) {
			// AP has been created, start web server
			Serial.write (mySSID);
			wicoSetupWebServer ();
		}
	} while (!r);

	// setup webserver
	WiFi.hostname (HOSTNAME);
	server.on ("/", handleRoot);
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println("HTTP server started");

	//TODO: portail captif
	// Set up mDNS responder:
	// - first argument is the domain name, in this example
	//   the fully-qualified domain name is "esp8266.local"
	// - second argument is the IP address to advertise
	//   we send our IP address on the WiFi network
	if (!MDNS.begin(HOSTNAME, myIP)) {
		Serial.println("Error setting up MDNS responder!");
		while(1) {
			delay(1000);
		}
	}
	Serial.println("mDNS responder started");
	// Add service to MDNS-SD
	MDNS.addService("http", "tcp", 80);
}


void handleRoot(void) {
	char ssid[32];
	char pwd[64];
	char email[100];

	// get current config
	memset (ssid,  0,  32);
	memset (pwd,   0,  64);
	memset (email, 0, 100);
	wicoReadWifiConfig (0, ssid, pwd, email);

	String s = "<html><body><h1>BBC</h1>";
	s += "<br/>SSID: ";  s += ssid;
	s += "<br/>email: "; s += email;
	s += "<p><form>Reset config <input type='checkbox' name='reset'><input type='submit' value='send'></form></p>\n";
	s += "</body></html>";
	if (server.hasArg("reset") ) {
		Serial.println("reset");
		wicoResetWifiConfig (0);
	}

	server.send ( 200, "text/html", s );
} // handleRoot()

void handleNotFound(void) {
  String message = "Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  server.send ( 404, "text/plain", message );
}

/** check if there's mail
 * TODO: update for real input value
 */
boolean isMail () {
	boolean ret;
	ret = (digitalRead(BUTTON) == 0 );
	if (ret) {
		Serial.println ("MAIL!");
	}
	return ret;
}

/** blink the builtin led
 *
 * usage:
 *  pinMode(BUILTIN_LED, OUTPUT);
 *  blink (5, 100);
 *
 * @param nb number of blinks
 * @param wait delay (ms) between blinks
 */
void blink (uint8_t nb, uint32_t wait) {
   // LED: LOW = on, HIGH = off
   for (int i = 0; i < nb; i++)
   {
      digitalWrite(BUILTIN_LED, LOW);
      delay(wait);
      digitalWrite(BUILTIN_LED, HIGH);
      delay(wait);
   }
}

/** send notification email
 * @param[in] to destination email
 * @return 0 if ok
 */
uint8_t sendEmail (char* to) {
	Serial.printf("Sending email to %s\n", to);

	Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
	String subject = "Brain Box notification";
	if(gsender->Subject(subject)->Send(to, "Bonjour.\nVous avez du courrier.\n\nVotre dévouée Brain Box.")) {
		Serial.println("Message send.");
	} else {
		Serial.print("Error sending message: ");
		Serial.println(gsender->getError());
	}
} // sendEmail

