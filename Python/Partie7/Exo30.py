import signal

def segfault_handler(sig, frame):
    print("Erreur de segmentation, réessayez")
    raise Exception("segfault")

signal.signal(signal.SIGSEGV, segfault_handler)

n = int(input("Nombre d'éléments : "))
tab = [0]*n
for i in range(n):
    tab[i] = int(input(f"tab[{i}] = "))
while True:
    i = int(input("Indice à afficher : "))
    try:
        print(f"tab[{i}] = {tab[i]}")
        break
    except Exception:
        print("Erreur de segmentation, réessayez")