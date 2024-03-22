#include "myFonctions.h"

void setup() {
  Serial.begin(9600);
  //DEMONSTRATION
  //1. Envoi et reception de message
  //sendMessage("+33605537064","Test");
  ///initHttpGMS();
  readMessage();
  
  //2. Acceder et parser un sie web par connexion WiFi --> GET/POST
  //sendRequestByWiFi("Network","unefoisoui@1","http://rucher.polytech.unice.fr/~cpeter/exemple.html");
    /*Parameters:
      const char * ssid
      const char * password
      const String urlServer */
  //sendCommand("AT+CMGF=1");
  //3. Acceder et parser un sie web par LTE --> GET/POST
  //sendRequestByGSM("http://rucher.polytech.unice.fr/~cpeter/exemple.html");
  /*Parameters:
    const char * url
    Fontion principale d'envoie de la requete HTTP --> GET via GSM */
  
  //4. Trouver une location en parsant les satellites de localisation
  //satellite_GPS();
  
  
  //String a = "AT+CGNSPWR=1";// Activation de la communication
  //String b = "AT+CGNSINF"; // Fixation des donnees des Satellites*/
  //sendCommand(a,"toto",7000);


  //5. Principe
  /*Nous avons utiliser 100% la documentation
    pour implementer nos propres fonction sans passer par
    des bibliotheques. Ce qui rend nos codes puissants,
    personnalisable pour tout besoin et surtout tres rapide */

}
  //unsigned long startTime = millis();

 
void loop() {
 readByteSerial2();  //Pour les commandes AT
}
