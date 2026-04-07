import threading
import time
import random

# Partie a : deux threads
sem_T1 = threading.Semaphore(0)
sem_T2 = threading.Semaphore(0)

def T1():
    for i in range(10):
        print("T1 : début itération", i+1)
        time.sleep(2)
        print("T1 : fin itération", i+1)
        sem_T1.release()
        sem_T2.acquire()

def T2():
    for i in range(10):
        print("T2 : début itération", i+1)
        time.sleep(random.randint(4, 9))
        print("T2 : fin itération", i+1)
        sem_T2.release()
        sem_T1.acquire()

t1 = threading.Thread(target=T1)
t2 = threading.Thread(target=T2)
t1.start()
t2.start()
t1.join()
t2.join()