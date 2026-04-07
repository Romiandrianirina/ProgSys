import threading
import random
import time
import sys

def generer(taille, result):
    result[:] = [random.randint(0, 99) for _ in range(taille)]

def inclusion(t1, t2):
    return all(e in t2 for e in t1)

def annulation():
    input()  # attend touche
    if sys.stdin.read(1) in ('A', 'a'):
        print("Annulation du programme")
        sys.exit(0)

T1, T2 = [], []
t_gen1 = threading.Thread(target=generer, args=(5, T1))
t_gen2 = threading.Thread(target=generer, args=(100, T2))
t_annul = threading.Thread(target=annulation, daemon=True)
t_annul.start()
t_gen1.start()
t_gen2.start()
t_gen1.join()
t_gen2.join()
print("T1 =", T1)
print("T2 =", T2)
res = inclusion(T1, T2)
print("T1 inclus dans T2" if res else "T1 non inclus dans T2")