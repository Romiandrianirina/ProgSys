import os
import sys

fichiers = []
while True:
    nom = input("Nom du fichier (vide pour finir) : ")
    if nom == "":
        break
    fichiers.append(nom)
if fichiers:
    os.execl("/usr/bin/emacs", "emacs", *fichiers)