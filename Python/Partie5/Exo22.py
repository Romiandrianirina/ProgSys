import threading
import time
import random

compteur = 0
u = 1.0
mutex = threading.Lock()

def f1(x):
    return (x-1)**2 / 4.0

def f2(x):
    return (x-2)**2 / 6.0

def thread_T1():
    global compteur, u
    while True:
        with mutex:
            u = f1(u)
            compteur += 1
            print(f"T1: u = {u}, iterations = {compteur}")
        time.sleep(random.randint(1, 5))

def thread_T2():
    global compteur, u
    while True:
        with mutex:
            u = f2(u)
            compteur += 1
            print(f"T2: u = {u}, iterations = {compteur}")
        time.sleep(random.randint(1, 5))

t1 = threading.Thread(target=thread_T1, daemon=True)
t2 = threading.Thread(target=thread_T2, daemon=True)
t1.start()
t2.start()
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass