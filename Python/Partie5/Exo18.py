import threading
import random

class TypeTableau:
    def __init__(self, taille):
        self.table = None
        self.taille = taille
        self.x = 0

def generer(tt):
    tt.table = [random.randint(0, 99) for _ in range(tt.taille)]

def verifier(tt):
    return 1 if tt.x in tt.table else 0

taille = 12
data = TypeTableau(taille)
t1 = threading.Thread(target=generer, args=(data,))
t1.start()
x = int(input("Valeur à rechercher: "))
data.x = x
t1.join()
t2 = threading.Thread(target=lambda: setattr(data, 'result', verifier(data)))
t2.start()
t2.join()
print("Présent :", "oui" if data.result else "non")