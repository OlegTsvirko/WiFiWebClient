#include <WiFi.h>
#include <WiFiWebClient.h>

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
        WiFiWebClient(const char ssid[], const char pass[], const char server[], const char path[]){
            _ssid = ssid;
            _pass = pass; 
            _server = server; 
            _path = path;
            int status = WL_IDLE_STATUS;
        }

        /**
         * @brief Setup WiFi connection and starts HTTP request.
         */
        void setupWiFi() {
            Serial.begin(115200);
            while (!Serial) {
                ; // wait for serial port to connect. Needed for native USB port only
            }

            WifiConnection();
            serverConnection();
        }

        /**
         * @brief Continuously reads from server and checks client connection.
         */
        void loopWiFi(){
            readFromServer();
            checkClientConnection();
        }

    private:
        WiFiClient client;      ///< WiFi client.
        const char _ssid[];     ///< WiFi SSID.
        const char _pass[];     ///< WiFi password.
        const char _server[];   ///< Server address.
        const char _path[];     ///< Path for request.
        
        /**
         * @brief Connects to WiFi network.
         */
        void WifiConnection(){
            Serial.print("Attempting to connect to SSID: ");
            Serial.println(_ssid);

            WiFi.begin(_ssid, _pass);
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
            }

            Serial.println("");
            Serial.println("Connected to WiFi");
            printWifiStatus();
        };

        /**
         * @brief Connects to the server and makes an HTTP request.
         */
        void serverConnection(){
            Serial.println("\nStarting connection to server...");
            // if you get a connection, report back via serial:
            if (client.connect(_server, 80)) {
                Serial.println("connected to server");
                // Make a HTTP request:
                client.print("GET "); client.print(_path); client.println(" HTTP/1.1");
                client.print("Host: "); client.println(_server);
                client.println("Connection: close");
                client.println();
            }
        };

        /**
         * @brief Reads the response from the server.
         */
        void readFromServer(){
            while (client.available()) {
            char c = client.read();
            Serial.write(c);
            }
        };

        /**
         * @brief Checks if the client is connected to the server.
         */
        void checkClientConnection(){
            if (!client.connected()) {
                Serial.println();
                Serial.println("disconnecting from server.");
                client.stop();

                // do nothing forevermore:
                while (true) {
                delay(100);
                }
            }
        };

        /**
         * @brief Prints the WiFi SSID, IP address and signal strength.
         */
        void printWifiStatus() {
        // print the SSID of the network you're attached to:
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        // print your board's IP address:
        IPAddress ip = WiFi.localIP();
        Serial.print("IP Address: ");
        Serial.println(ip);

        // print the received signal strength:
        long rssi = WiFi.RSSI();
        Serial.print("signal strength (RSSI):");
        Serial.print(rssi);
        Serial.println(" dBm");
        };
}