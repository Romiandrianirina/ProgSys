import os, signal

pid = os.fork()
if pid == 0:
    while True:
        pass
else:
    while True:
        c = input("Menu: s (endormir), r (réveiller), q (quitter): ")
        if c == 's':
            os.kill(pid, signal.SIGSTOP)
        elif c == 'r':
            os.kill(pid, signal.SIGCONT)
        elif c == 'q':
            os.kill(pid, signal.SIGTERM)
            os.wait()
            break