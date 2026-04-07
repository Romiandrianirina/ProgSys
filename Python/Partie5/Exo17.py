import threading
import random

def creer_tableau(taille):
    tab = [random.randint(0, 99) for _ in range(taille)]
    return tab

taille = 10
resultat = [None]
def worker():
    resultat[0] = creer_tableau(taille)
thread = threading.Thread(target=worker)
thread.start()
thread.join()
print("Tableau reçu :", resultat[0])