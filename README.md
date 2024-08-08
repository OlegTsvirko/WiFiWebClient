WiFiWebClient class for connecting to WiFi and HTTP requests
with a number of parameters:
ssid - WiFi SSID.
pass - WiFi password.
server - Server address.
path - Path for the HTTP request.


Using example:

const char ssid[] = "YOUR_SSID";               // Your network SSID (name).

const char pass[] = "YOUR_SSID_PASSWORD";      // Your network password.

const char server[] = "wifitest.adafruit.com"; // Server address for Adafruit test.

const char path[] = "/testwifi/index.html";    // Path for the HTTP request.


WiFiWebClient webClient(ssid, password, server, path);

//Initializes the web client.

void setup() {
    webClient.setupWiFi();
}

// Continuously reads from server and checks client connection

void loop() {
    webClient.loopWiFi();
}
