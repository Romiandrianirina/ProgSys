import os, signal, time, sys

fils = []
for _ in range(5):
    pid = os.fork()
    if pid == 0:
        def term(sig, frame):
            print(f"Fils {os.getpid()} terminé")
            sys.exit(0)
        signal.signal(signal.SIGTERM, term)
        while True:
            time.sleep(1)
    else:
        fils.append(pid)

def pere_term(sig, frame):
    print("Père tué")
    sys.exit(0)
signal.signal(signal.SIGTERM, pere_term)

while True:
    print("1-Endormir, 2-Réveiller, 3-Terminer, 4-Quitter")
    choix = int(input())
    if choix == 4:
        break
    num = int(input("Numéro (1-5) : ")) - 1
    if 0 <= num < 5:
        if choix == 1:
            os.kill(fils[num], signal.SIGSTOP)
        elif choix == 2:
            os.kill(fils[num], signal.SIGCONT)
        elif choix == 3:
            os.kill(fils[num], signal.SIGTERM)
for p in fils:
    os.kill(p, signal.SIGTERM)
for _ in range(5):
    os.wait()