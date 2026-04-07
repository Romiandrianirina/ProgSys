import struct
import os

nom = input("Nom du fichier à charger : ")
taille = os.path.getsize(nom)
nb = taille // 4
tab = []
with open(nom, "rb") as f:
    for _ in range(nb):
        val = struct.unpack('i', f.read(4))[0]
        tab.append(val)
print(f"{nb} entiers lus :", tab)