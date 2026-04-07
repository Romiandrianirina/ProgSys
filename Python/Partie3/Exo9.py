import os
import shutil

while True:
    rep = input("Nom du répertoire de destination (quit pour arrêter) : ")
    if rep == "quit":
        break
    if not os.path.exists(rep):
        os.makedirs(rep)
    for item in os.listdir('.'):
        src = os.path.join('.', item)
        dst = os.path.join(rep, item)
        if os.path.isdir(src):
            shutil.copytree(src, dst, dirs_exist_ok=True)
        else:
            shutil.copy2(src, dst)
    print(f"Copie vers {rep} effectuée")