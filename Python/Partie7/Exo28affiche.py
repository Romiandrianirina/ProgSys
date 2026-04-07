import signal, time

entier = 0
def handler(sig, frame):
    global entier
    with open("/tmp/entier.txt", "r") as f:
        entier = int(f.read())
    print(f"Entier reçu : {entier}")

signal.signal(signal.SIGUSR1, handler)
while True:
    time.sleep(1)