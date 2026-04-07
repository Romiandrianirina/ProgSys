import os
import sys

tube = os.pipe()
pid = os.fork()
if pid == 0:
    # fils
    os.close(tube[1])
    # prépare arguments : nom du programme, fd_lecture, fd_ecriture
    args = ["./fils.py", str(tube[0]), str(tube[1])]
    os.execv(args[0], args)
else:
    # père
    os.close(tube[0])
    message = "Voici un message pour mon fils"
    os.write(tube[1], message.encode())
    os.close(tube[1])
    os.wait()