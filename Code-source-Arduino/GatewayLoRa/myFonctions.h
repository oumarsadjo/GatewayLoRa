#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

#include <HTTPClient.h>
#include <Ethernet.h>
#include <Arduino.h>
#include <WiFi.h>

void sendRequestByWiFi(const char* ssid, const char* password, const String urlServer);  // GET by WiFi
void sendCommand(String myCommand, long baudSerial, long baudSerial2);                   // send AT command_1
void myWiFiConnexion(const char* ssid, const char* password);                            // Connexion WiFi
void sendMessage(const char* numero, const char* texte);
void byWiFi_HTTP(const String urlServer);  // Init HTT by WiFi
void sendRequestByGSM(const char* url);    // GET by GSM
void sendCommand(String myCommand);        // send AT command_1
void satellite_GPS();                     // Pour les applications GSM
void readMessage();
void readByteSerial2();  //Read all byte
void initHttpGMS();      // Init GSM --> APN
void closeGSM();         // Close GSM
void getMAC();           // Get MAC

//
void satellite_GPS(){
  String a = "AT+CGNSPWR=1";// Activation de la communication
  String b = "AT+CGNSINF"; // Fixation des donnees des Satellites
  sendCommand(a);
  delay(1000);
  sendCommand(b);
}

//-----------------------FONCTION POUR LES AT COMMANDES - D E B U T ----------------------------//

String sendCommand(String myCommand, long baudSerial, long baudSerial2, const char* expectedResponse, unsigned long timeout) {
  int TX = 16;
  int RX = 17;
  String response = "";
  Serial.begin(baudSerial);
  Serial2.begin(baudSerial2, SERIAL_8N1, TX, RX);

  Serial.println("Starting...");
  Serial.print("myCommand ");Serial.println(myCommand);
  Serial2.println(myCommand);

  unsigned long startTime = millis();
  Serial.println(startTime);
  while (millis() - startTime < timeout) {
    if (Serial2.available()) {
      response = Serial2.readString();
      Serial.print("response ---"); Serial.println(response);Serial.print("---");
      if (response.indexOf(expectedResponse) != -1) {
        Serial.println("j ai trouve OK");
        return response;  // Réponse attendue trouvée
      }
    }
  }
  Serial.println("timeout");
  return response;  // La réponse attendue n'a pas été trouvée dans le délai imparti
}

void sendCommand(String myCommand, const char* expectedResponse, unsigned long timeout) {
  sendCommand(myCommand, 9600, 115200, expectedResponse, timeout);
}

//3eme fonction de sendCommand definissant la reponse par defaut attendue "OK" et le temps d'attente 3s
void sendCommand(String myCommand) {
  sendCommand(myCommand, "OK", 3000);  // Valeurs par défaut pour l'attente "OK"
}
//---------------------------FONCTION POUR LES AT COMMANDES - F I N  ------------------------------//

//--------------------------------------D  E  B  U  T  -- G  S  M -------------------------------------//
//1. Fontion d'initialisation de la communication GSM --> APN SFR France "sl2sfr"
void initHttpGMS() {
  sendCommand("AT+SAPBR=3,1,\"Contype\", \"GPRS\"");
  sendCommand("AT+SAPBR=3,1,\"APN\",\"sl2sfr\"");  //Configure bearer profile APN: SFR France
  sendCommand("AT+SAPBR=1,1");                     //Open
  sendCommand("AT+SAPBR=2,1");                     //Get the IP
}

//1. Fontion principale d'envoie de la requete HTTP --> GET via GSM
void sendRequestByGSM(const char* url) {
  initHttpGMS();                         //Initialisation
  sendCommand("AT+HTTPINIT");            // Initialisation
  sendCommand("AT+HTTPPARA=\"CID\",1");  // Set parameters for HTTP session
  String urlCommand = "AT+HTTPPARA=\"URL\",\"";
  urlCommand += url;
  urlCommand += "\"";
  sendCommand(urlCommand.c_str());  // GET Data
  sendCommand("AT+HTTPACTION=0");   // GET session start / GET successfully
  sendCommand("AT+HTTPREAD");       // Read the data of HTTP server
}

//-- FONCTION CLOSE GSM COMM
void closeGSM() {
  sendCommand("AT+HTTPTERM");
}
//-------------------------------------- F I N  -- G  S  M -------------------------------------//

//-----------------------------------D  E  B  U  T  -- W i  F  i -------------------------------//
//1. Fontion principale : etablissement de la connexion WiFi et envoie de la requete HTTP --> GET
void sendRequestByWiFi(const char* ssid, const char* password, const String urlServer) {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connexion au réseau en cours...");
    int attempts = 0;
    attempts++;
    if (attempts > 10) {
      Serial.println("Échec de la connexion au réseau Wi-Fi.");
      while (1) {
      }
    }
  }

  Serial.println("-------------------------------");
  Serial.println("Connecté au réseau Wi-Fi");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Force du signal (RSSI) : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.println("-------------------------------");
  byWiFi_HTTP(urlServer);  //Envoi de la requete HTTP VIA LE WIFI
}

//2. Fontion d'envoie de la requete HTTP --> GET via WiFi

void byWiFi_HTTP(const String urlServer) {
  unsigned long lastTime = 0;
  lastTime = millis();
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String serverPath = urlServer;
    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET();
    Serial.print(httpResponseCode);
    Serial.print("httpResponseCode -> OK");

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code : ");
      Serial.print(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.print("Error code: ");
      Serial.print(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  lastTime = millis();
}
//----------------------------------- F  I  N  -- W i  F  i -------------------------------//
//
//----------------------------------- D E B U T  -- G S M ---------------------------------//

//-------------------------------------- F I N  -- G S M ---------------------------------//
//
//<<---FONCTION POUR LIRE TOUS LES BYTES DISPONIBLES SUR LE PORT SERIAL2-->>
void readByteSerial2() {
  while (Serial2.available()) {
    // Lire des nouveaux bytes:
    Serial.print((char)Serial2.read());
  }
}
//--------------------------------------------------------------------------//
//<<-------------- FONCTION POUR ENVOYER UN MESSAGE / SMS ----------------->>
void sendMessage(const char* numero, const char* texte) {

  sendCommand("AT+CMGF=1");  //Activation mode texte
  String command = "AT+CMGS=\"";
  command += numero;
  command += "\"";
  sendCommand(command);
  //delay(1000);

  Serial2.print(texte);
  //sendCommand(texte);
  Serial2.write(26);  // Envoi de Ctrl-Z pour indiquer la fin du message
  delay(1000);
  Serial.println("SMS envoyé avec succès !");
  delay(2000);
  sendCommand("AT+CMGD=1");  // Desactivation mode texte
}
//--------------------------------------------------------------------------//
//<<-------------- FONCTION POUR LIRE UN MESSAGE / SMS ------------------->>
void readMessage() {
  sendCommand("AT+CMGF=1");        // Activation du mode texte
  sendCommand("AT+CMGL=\"ALL\"");  // Lire tous les messages SMS

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
  }

  delay(1000);
  sendCommand("AT+CMGD=1,4");  // Supprimer tous les messages SMS lus
  sendCommand("AT+CMGF=0");    // Désactivation du mode texte
}
//--------------------------------------------------------------------------//
//<<----------------- FONCTION POUR LA CONNEXION WiFi -------------------->>//
void myWiFiConnexion(const char* ssid, const char* password) {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connexion au réseau en cours...");
    int attempts = 0;
    attempts++;
    if (attempts > 10) {
      Serial.println("Échec de la connexion au réseau Wi-Fi.");
      while (1) {
      }
    }
  }

  Serial.println("--------------------------------");
  Serial.println("Connecté au réseau Wi-Fi");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Force du signal (RSSI) : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.println("--------------------------------");
}
//--------------------------------------------------------------------------//
//<<----------------- FONCTION POUR ETABLIR LA CONNEXION ------------------>>//
void establishConnection(String dataType, String IPorDomain, String portIN) {
  Serial2.println("AT+CIPSTART=\"" + dataType + "\",\"" + IPorDomain + "\"," + portIN);
  delay(1000);

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
    if (response.indexOf("OK") != -1 || response.indexOf("ALREADY CONNECTED") != -1) {
      Serial.println("Connexion établie avec succès !");
      return;
    } else if (response.indexOf("ERROR") != -1) {
      Serial.println("Erreur lors de l'établissement de la connexion.");
      return;
    }
  }
}
//--------------------------------------------------------------------------//
//<<---------------- FONCTION POUR ENVOYER DES DONNEES ------------------->>//
void sendData(int datasize) {
  Serial2.println("AT+CIPSEND=\"" + datasize);
  delay(1000);

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
    if (response.indexOf("OK") != -1 || response.indexOf("DEJA ENVOYE") != -1) {
      Serial.println("Donnees envoyees avec succès !");
      return;
    } else if (response.indexOf("ERROR") != -1) {
      Serial.println("Erreur lors de l'envoi des donnees.");
      return;
    }
  }
}

//CONNAITRE SI LE PACKET EST RECU OU PAS

void testCIPSRIPCommand() {
  // Envoi de la commande AT+CIPSRIP=?
  Serial2.println("AT+CIPSRIP=?");

  // Attente de la réponse
  delay(1000);  // Attendez un certain temps pour que la réponse soit reçue

  // Lecture de la réponse
  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    if (response.startsWith("+CIPSRIP: ")) {
      // Affichez la liste des modes pris en charge
      Serial.print("Supported Modes: ");
      Serial.println(response.substring(10));
    } else if (response == "OK") {
      // Commande réussie
      Serial.println("Commande AT+CIPSRIP=? exécutée avec succès.");
    }
  }
}
/*********************************************************************/

void getMAC() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  uint8_t mac_gateway[6];
  esp_efuse_mac_get_default(mac_gateway);

  /* Affiche l'adresse MAC sur le port série */
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
                mac_gateway[0], mac_gateway[1], mac_gateway[2],
                mac_gateway[3], mac_gateway[4], mac_gateway[5]);
}

#endif
