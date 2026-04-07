import os

nom_fichier = input("Nom du fichier texte : ")
os.execl("/usr/bin/emacs", "emacs", nom_fichier)