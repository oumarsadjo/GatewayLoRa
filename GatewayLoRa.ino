#include "myFonctions.h"

void setup() {
  Serial.begin(9600);
  //myWiFiConnexion("Network", "unefoisoui@23");
  //sendRequestByWiFi("Network","unefoisoui@23","http://rucher.polytech.unice.fr/~cpeter/exemple.html");
  //sendRequestByGSM("http://rucher.polytech.unice.fr/~cpeter/exemple.html");
  //initHttpGMS();
  // sendCommand("AT+CGNSPWR=1");
  // delay(10000);

  //sendCommand("AT+CGNSINF");
  //sendCommand("AT+CGPSSTATUS");
  //sendCommand("AT+CGNSPWR=0");
  //delay(1000);
  sendCommand("AT+CGNSSEQ=\"GGA\"");
  //delay(600);
  //  sendCommand("AT+CGNSTST=1");
  //sendCommand("AT+CGNSPWR=0");
  //  applicationGPS();
}

void loop() {
  readByteSerial2();  //Pour les commandes AT
}
