# SUIVI COMPLET DU PROJET -> GatewayLoRa
- Annee: 2023-2024
- Projet: GetwayLoRa
- Niveau: 4 annee
- Ecole: Polytch Nice Sophia
- Eleves: Oumar Sadjo Barry & Mor Djeng / oumar-sadjo.barry@etu.univ-cotedazur.fr & mor.dieng@etu.univ-cotedazur.fr
- Professeur: Monsieur Christian Peter / christian.peter@univ-cotedazur.fr
- Derniere mise a jour: _Lundi 05 Fevrier 2024_          

## LES ETAPES QUE NOUS AVONS SUIVI SONT

_1. LECTURES DES DIFFERENTES DOCUMENTATIONS
------------------------------------------
Nous avons commencé par lire attentivement toutes les documents (datasheets),
des deux cartes. C'est qui nous a donne une vue générale de leurs fonctionnements.
Nous avons analysé les differents schematics et prendre connaissance de leur brochages.

_2. INTERCONNEXION DES DEUX CARTES (CABLAGE)
------------------------------------------
Apres avoir pris connaissance des deux datasheet, nous avons choisi un protocole de
communication UART pour permettre la transmission. Nous avons identifié l'alimentation
des deux cartes qui à 5V chacune.

_3. PROTOCOLE ET BROCHAGE
------------------------
- Protocole: UART
- Connexion:
- ESP32 (ports) vers SIM7000G (ports)
- 5V    ------------> V
- GND   ------------> G
- 16    ------------> T //RX to TX
- 17    ------------> R //TX to RX

_4. UTILISATION DE IDE ARDUINO POUR LES TESTS
--------------------------------------------
Nous avons codé une première fonction "void sendCommand(String myCommand)", qui permet
d'envoyer des commandes AT et afficher le resultat au port serial désiré.
NOTE: Toutes les fonctions sont ecrites dans un fichier d'entete (header), nomme "myFonctions.h".

_5. LES PREMIERES FONCTIONS
-------------------------
Nous avons ecris une premiere fonction capable d'envoyer un SMS a un numero désiré nommee : 
"void sendMessage(const char* numero, const char* texte)" et une deuxième fonction qui permet de lire
des messages recus nommee: "void readMessage()".

_6. FONCTIONS PRINCIPALES
------------------------
- A. void myWiFiConnexion(const char* ssid, const char* password): cette fonction nous permet de se connecter un reseau WiFi desire.

- B. void sendRequestByWiFi(const char* ssid, const char* password, const String urlServer):
   Cette fonction permet d'envoyer des requettes HTTP GET en utilisant un reseau WiFi dedié. La limite de cette foncttionnalité,
   est que certains endroits où se projet sera utilisé; n'ont pas de WiFi. Pour aller plus loin, on va utiliser le GSM.
  Elle procede comme suit:
  - a. Connexion a un reseau WiFi
  - b. Verification de la connexion
  - c. Initialisation du protocole HTTP
  - d. Obtention de la longeur ou de la taille de la page
  - e. Affichage du resultat obtenu
  - f. Fermeture du protocole HTTP
    
- C. void sendRequestByGSM(const char* url):
   Cette fonction permet d'envoyer des requettes HTTP GET en utilisant le reseau GSM. L'utilisateur precise le serveur ou le lien.
   Elle procede comme suit:
  - a. Initialisation du reseau GSM
  - b. Obtention d'une IP adress pour communiquer en GSM
  - c. Initialisation du protocole HTTP
  - d. Obtention de la longeur ou de la taille de la page
  - e. Affichage du resultat obtenu
  - f. Fermeture du protocole HTTP

_7. ETAPES SCHEMATICS
--------------------
Pour cette etape de Design, nous avons choisi l'ensemble des composants et voir leur disponibilite sur le site du sous-traitant.
Le design a ete valide par notre professeur. Nous avons constitue le BOM et l'envoye au professeur pour commander les composants.
Nous allons maintenant passer a l'etape de routage.

Lors de la seance du 13 Fevrier 2024, nous avons apporter des corrections au schematic et ajouter le convertisseur TXB0108PWR
pour connecter les tensions de +1V8.

_8. ETAPES ROUTAGE
--------------------
Comme le design a ete valide et les materiels sont disponible, nous allons maintenant continuer le routage...
A continuer lors de la prochaine seance : _Mardi 18 Fevrier 2024_
