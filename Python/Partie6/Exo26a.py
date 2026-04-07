import struct
import os

n = int(input("Nombre d'entiers : "))
tab = []
for i in range(n):
    tab.append(int(input(f"Entier {i+1} : ")))
nom = input("Nom du fichier de sauvegarde : ")
with open(nom, "wb") as f:
    for val in tab:
        f.write(struct.pack('i', val))

os.chmod(nom, 0o664)