import threading
import time
import random
import sys

def barriere(N, count, mutex, sem):
    mutex.acquire()
    count[0] += 1
    if count[0] == N:
        count[0] = 0
        for _ in range(N-1):
            sem.release()
        mutex.release()
    else:
        mutex.release()
        sem.acquire()

def thread_rdv(id, N, count, mutex, sem):
    for _ in range(5):
        duree = random.randint(1, 5)
        print(f"Thread {id} : début, durée {duree}s")
        time.sleep(duree)
        print(f"Thread {id} : arrivée")
        barriere(N, count, mutex, sem)
    print(f"Thread {id} terminé")

if len(sys.argv) != 2:
    print("Usage: python prog.py N")
    sys.exit(1)
N = int(sys.argv[1])
count = [0]
mutex = threading.Lock()
sem = threading.Semaphore(0)
threads = []
for i in range(N):
    t = threading.Thread(target=thread_rdv, args=(i+1, N, count, mutex, sem))
    t.start()
    threads.append(t)
for t in threads:
    t.join()