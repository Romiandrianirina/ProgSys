import os, signal

n = int(input("Entrez un entier : "))
with open("/tmp/entier.txt", "w") as f:
    f.write(str(n))
os.kill(0, signal.SIGUSR1)