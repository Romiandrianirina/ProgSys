import os
import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python prog.py repertoire1 [repertoire2 ...]")
        sys.exit(1)
    for rep in sys.argv[1:]:
        print(f"Répertoire : {rep}")
        try:
            for entree in os.listdir(rep):
                chemin = os.path.join(rep, entree)
                try:
                    stat = os.stat(chemin)
                    if os.path.isfile(chemin) and stat.st_size > 1000000:
                        print(f"  {entree} (taille: {stat.st_size} octets, UID: {stat.st_uid})")
                except OSError:
                    pass
        except OSError as e:
            print(f"Erreur d'ouverture du répertoire {rep}: {e}")
        print()

if __name__ == "__main__":
    main()