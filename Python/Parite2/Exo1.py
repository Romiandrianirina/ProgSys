import os

pid_fils = os.fork()
if pid_fils == -1:
    print("Erreur de fork")
elif pid_fils == 0:
    print("je suis le fils")
else:
    print("je suis le père")
    os.wait()