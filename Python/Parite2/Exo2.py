import os

pid_fils1 = os.fork()
if pid_fils1 == 0:
    print("je suis le fils 1")
else:
    pid_fils2 = os.fork()
    if pid_fils2 == 0:
        print("je suis le fils 2")
    else:
        print("je suis le père")
        os.wait()
        os.wait()