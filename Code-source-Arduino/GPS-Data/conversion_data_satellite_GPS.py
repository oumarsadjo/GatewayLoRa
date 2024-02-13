import sys
import folium
import os

def parse_rmc(rmc_sentence):
    # Exemple de trame RMC : "$GPRMC,064036.289,A,4836.5375,N,00740.9373,E,3.2,200.2,120222,000.0,W*7F"
    parts = rmc_sentence.split(',')
    if len(parts) < 12:
        return None  # Trame invalide

    # Heure d'envoi (UTC)
    heure = parts[1]
    # Statut du positionnement (A pour actif)
    statut = parts[2]
    # Latitude (format DDMM.MMMM)
    latitude = float(parts[3]) / 100
    # Longitude (format DDDMM.MMMM)
    longitude = float(parts[5]) / 100
    # Vitesse en nœuds
    vitesse = float(parts[7])
    # Route sur le fond en degrés
    route = float(parts[8])
    # Date (format DDMMYY)
    date = parts[9]

    return {
        'heure': heure,
        'statut': statut,
        'latitude': latitude,
        'longitude': longitude,
        'vitesse': vitesse,
        'route': route,
        'date': date
    }

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python extra_NMEA.py <trame_rmc>")
        sys.exit(1)

    trame_rmc = sys.argv[1]
    resultat = parse_rmc(trame_rmc)
    if resultat:
        print("Heure:", resultat['heure'])
        print("Statut:", resultat['statut'])
        print("Latitude:", resultat['latitude'])
        print("Longitude:", resultat['longitude'])
        print("Vitesse:", resultat['vitesse'], "nœuds")
        print("Route:", resultat['route'], "degrés")
        print("Date:", resultat['date'])

        # Écriture des données dans un fichier texte
        with open('donnees_rmc.txt', 'w') as f:
            f.write(f"Heure: {resultat['heure']}\n")
            f.write(f"Statut: {resultat['statut']}\n")
            f.write(f"Latitude: {resultat['latitude']}\n")
            f.write(f"Longitude: {resultat['longitude']}\n")
            f.write(f"Vitesse: {resultat['vitesse']} nœuds\n")
            f.write(f"Route: {resultat['route']} degrés\n")
            f.write(f"Date: {resultat['date']}\n")

        # Création de la carte avec folium
        latitude = resultat['latitude']
        longitude = resultat['longitude']
        carte = folium.Map(location=[latitude, longitude], zoom_start=14)
        folium.Marker([latitude, longitude],
                      popup="Position",
                      #icon=folium.Icon(color='red')
                     ).add_to(carte)

        # Enregistrement de la carte dans un fichier HTML
        if os.path.exists('maCarte.html'):
            carte.save('maCarte.html')
            print("Fichier maCarte.html créé.")
        else:
            print("Le fichier maCarte.html n'existe pas.")
    else:
        print("Trame RMC invalide.")
