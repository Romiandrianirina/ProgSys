import threading
import random
import time

N = 100
tableau = [0.0] * N
mutex = threading.Lock()

def thread_moyenne():
    global tableau
    while True:
        with mutex:
            copie = tableau[:]
            for i in range(1, N-1):
                tableau[i] = (copie[i-1] + copie[i] + copie[i+1]) / 3.0
        time.sleep(random.randint(1, 3))

def thread_affiche():
    while True:
        time.sleep(4)
        with mutex:
            print("Tableau :", [round(x,2) for x in tableau])

# initialisation
for i in range(N):
    if i == 0 or i == N-1:
        tableau[i] = 0.0
    else:
        tableau[i] = random.randint(0, 100)

t1 = threading.Thread(target=thread_moyenne, daemon=True)
t2 = threading.Thread(target=thread_affiche, daemon=True)
t1.start()
t2.start()
# laisser tourner (Ctrl+C pour arrêter)
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass