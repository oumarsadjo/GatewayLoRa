************************************************
************************************************
*** ANNEE: 2023-2024                         ***
*** PROJET: GetwayLoRa                       ***
*** NIVEAU: 4 annee                          ***
*** ECOLE: Polytch Nice Sophia               ***
*** ELEVES: Oumar Sadjo Barry                ***
***         Mor Djeng                        ***
*** PROFESSEUR: Christian Peter              ***
*** DERNIERE MISE AJOUR: 10/27/2023          ***
************************************************
************************************************

********************************************
*** LES ETAPES QUE NOUS AVONS SUIVI SONT ***
********************************************

1. LECTURES DES DIFFERENTES DOCUMENTATIONS
------------------------------------------
Nous avons commencé par lire attentivement toutes les documents (datasheets),
des deux cartes. C'est qui nous a donne une vue générale de leurs fonctionnements.
Nous avons analysé les differents schematics et prendre connaissance de leur brochages.

2. INTERCONNEXION DES DEUX CARTES (CABLAGE)
------------------------------------------
Apres avoir pris connaissance des deux datasheet, nous avons choisi un protocole de
communication UART pour permettre la transmission. Nous avons identifié l'alimentation
des deux cartes qui à 5V chacune.

3. PROTOCOLE ET BROCHAGE
------------------------
Protocole: UART
Connexion: ESP32 ============> SIM7000
           5V    ------------> V
           GND   ------------> G
           16    ------------> T //RX to TX
           17    ------------> R //TX to RX

4. UTILISATION DE IDE ARDUINO POUR LES TESTS
--------------------------------------------
Nous avons codé une première fonction "void sendCommand(String myCommand)", qui permet
d'envoyer des commandes AT et afficher le resultat au port serial désiré.
NOTE: Toutes les fonctions sont ecrites dans un fichier d'entete (header), nomme "myFonctions.h".

5. LES PREMIERES FONCTIONS
-------------------------
Nous avons ecris une premiere fonction capable d'envoyer un SMS a un numero désiré nommee : 
"void sendMessage(const char* numero, const char* texte)" et une deuxième fonction qui permet de lire
des messages recus nommee: "void readMessage()".

6. FONCTIONS PRINCIPALES
------------------------
A. void myWiFiConnexion(const char* ssid, const char* password): cette fonction nous permet de se connecter un reseau WiFi desire.

B. void sendRequestByWiFi(const char* ssid, const char* password, const String urlServer):
   Cette fonction permet d'envoyer des requettes HTTP GET en utilisant un reseau WiFi dedié. La limite de cette foncttionnalité,
   est que certains endroits où se projet sera utilisé; n'ont pas de WiFi. Pour aller plus loin, on va utiliser le GSM.
  Elle procede comme suit:
   a. Connexion a un reseau WiFi
   b. Verification de la connexion
   c. Initialisation du protocole HTTP
   d. Obtention de la longeur ou de la taille de la page
   e. Affichage du resultat obtenu
   f. Fermeture du protocole HTTP

C. void sendRequestByGSM(const char* url):
   Cette fonction permet d'envoyer des requettes HTTP GET en utilisant le reseau GSM. L'utilisateur precise le serveur ou le lien.
   Elle procede comme suit:
   a. Initialisation du reseau GSM
   b. Obtention d'une IP adress pour communiquer en GSM
   c. Initialisation du protocole HTTP
   d. Obtention de la longeur ou de la taille de la page
   e. Affichage du resultat obtenu
   f. Fermeture du protocole HTTP

7. ETAPES SCHEMATICS
---------------------
C'est cette etape nous devons commencer maintenant.....
La partie shematic est terminee et nous avons commence le routage le 22 Dec 2023
