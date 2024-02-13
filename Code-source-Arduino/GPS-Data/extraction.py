import sys

def extraire_localisation(phrase):
    parties = phrase.split(',')
    status = int(parties[1])
    latitude = float(parties[3])
    longitude = float(parties[4])
    altitude = float(parties[5])
    return status, latitude, longitude, altitude

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Utilisation: python extraction.py <phrase>")
        sys.exit(1)
    
    phrase = sys.argv[1]
    status, latitude, longitude, altitude = extraire_localisation(phrase)
    print("Status:", status)
    print("Latitude:", latitude)
    print("Longitude:", longitude)
    print("Altitude:", altitude)
