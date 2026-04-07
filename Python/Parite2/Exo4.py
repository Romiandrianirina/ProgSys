import os

numero = [0]  # variable globale simulée

for i in range(1, 6):
    numero[0] = i
    pid = os.fork()
    if pid == 0:
        print(f"je suis le fils {numero[0]}")
        os._exit(0)
for _ in range(5):
    os.wait()