import sys
import os
import shutil

if len(sys.argv) != 2:
    print("Usage: python prog.py repertoire_destination")
else:
    dest = sys.argv[1]
    if not os.path.exists(dest):
        os.makedirs(dest)
    for item in os.listdir('.'):
        src = os.path.join('.', item)
        dst = os.path.join(dest, item)
        if os.path.isdir(src):
            shutil.copytree(src, dst, dirs_exist_ok=True)
        else:
            shutil.copy2(src, dst)
    print("Copie terminée")