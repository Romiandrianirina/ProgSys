import os
import time
import random

debut = time.time()

for i in range(1, 3):
    pid = os.fork()
    if pid == 0:
        duree = random.randint(1, 10)
        print(f"Fils {i} : je vais dormir {duree} secondes")
        time.sleep(duree)
        print(f"Fils {i} : réveillé, je termine")
        os._exit(0)

for _ in range(2):
    os.wait()

fin = time.time()
print(f"Durée totale d'attente : {int(fin - debut)} secondes")