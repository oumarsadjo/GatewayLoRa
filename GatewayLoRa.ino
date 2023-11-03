#include "myFonctions.h"

void setup() {
  Serial.begin(9600);
  //myWiFiConnexion("Network", "unefoisoui@23");
  //sendRequestByWiFi("Network","unefoisoui@23","http://rucher.polytech.unice.fr/~cpeter/exemple.html");
  sendRequestByGSM("http://rucher.polytech.unice.fr/~cpeter/exemple.html");
  //initHttpGMS();
}

void loop() {
  readByteSerial2();  //Pour les commandes AT
  
}
