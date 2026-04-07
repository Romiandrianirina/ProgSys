import threading
import time
import random
import sys

compt = 0
mutex = threading.Lock()
stop = False

def incrementeur(limite):
    global compt, stop
    while not stop:
        with mutex:
            if compt >= limite:
                stop = True
                break
            compt += 1
            print(f"Incrementeur : compt = {compt}")
        time.sleep(random.randint(1, 5))

def afficheur(limite):
    global stop
    while not stop:
        time.sleep(2)
        with mutex:
            if compt >= limite:
                stop = True
                break
            print(f"Afficheur : compt = {compt}")

if len(sys.argv) != 2:
    print("Usage: python prog.py limite")
    sys.exit(1)
limite = int(sys.argv[1])
t1 = threading.Thread(target=incrementeur, args=(limite,))
t2 = threading.Thread(target=afficheur, args=(limite,))
t1.start()
t2.start()
t1.join()
t2.join()
print(f"Valeur limite {limite} atteinte")