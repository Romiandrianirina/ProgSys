import struct, os

nom = input("Nom du fichier : ")
taille = os.path.getsize(nom)
nb = taille // 4
tab = []
with open(nom, "rb") as f:
    for _ in range(nb):
        tab.append(struct.unpack('i', f.read(4))[0])
print(f"{nb} entiers lus :", tab)