#ifndef WiFiWebClient_h
#define WiFiWebClient_h

#include <WiFi.h>

/**
 * @brief WiFiWebClient class for connecting to WiFi and HTTP requests.
 */
class WiFiWebClient
{
    public:
        /**
         * @brief Constructs a new WiFiWebClient object.
         * 
         * @param ssid WiFi SSID.
         * @param pass WiFi password.
         * @param server Server address.
         * @param path Path for the HTTP request.
         */
        WiFiWebClient(const char ssid[], const char pass[], const char server[], const char path[]);

        /**
         * @brief Setup WiFi connection and starts HTTP request.
         */
        void setupWiFi();

        /**
         * @brief Continuously reads from server and checks client connection.
         */
        void loopWiFi();

    private:
        WiFiClient client;      ///< WiFi client.
        const char _ssid[];     ///< WiFi SSID.
        const char _pass[];     ///< WiFi password.
        const char _server[];   ///< Server address.
        const char _path[];     ///< Path for request.
        
        /**
         * @brief Connects to WiFi network.
         */
        void WifiConnection();

        /**
         * @brief Connects to the server and makes an HTTP request.
         */
        void serverConnection();

        /**
         * @brief Reads the response from the server.
         */
        void readFromServer();

        /**
         * @brief Checks if the client is connected to the server.
         */
        void checkClientConnection();

        /**
         * @brief Prints the WiFi SSID, IP address and signal strength.
         */
        void printWifiStatus();
}
#endif