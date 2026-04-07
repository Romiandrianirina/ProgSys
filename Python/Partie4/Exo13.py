import os
import sys

tube1 = os.pipe()
tube2 = os.pipe()
pid = os.fork()
if pid == 0:
    os.close(tube1[0])
    os.close(tube2[1])
    mot = input("Mot: ")
    os.write(tube1[1], mot.encode())
    result = int.from_bytes(os.read(tube2[0], 4), 'little')
    print("Trouvé" if result else "Non trouvé")
else:
    os.close(tube1[1])
    os.close(tube2[0])
    # redirection stdin vers tube1[0]
    os.dup2(tube1[0], 0)
    os.close(tube1[0])
    # redirection stdout vers tube2[1]
    os.dup2(tube2[1], 1)
    os.close(tube2[1])
    mot = sys.stdin.readline().strip()
    trouve = 0
    try:
        with open("texte.txt", "r") as f:
            for ligne in f:
                if mot in ligne.split():
                    trouve = 1
                    break
    except FileNotFoundError:
        pass
    print(trouve, end='')  # écrit sur stdout redirigé
    sys.stdout.flush()
    os.wait()