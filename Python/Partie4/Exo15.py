import os

tube = os.pipe()
pid = os.fork()
if pid == 0:
    os.close(tube[1])
    os.environ["FD_LECTURE"] = str(tube[0])
    os.environ["FD_ECRITURE"] = str(tube[1])
    os.execv("./fils_env.py", ["./fils_env.py"])
else:
    os.close(tube[0])
    message = "Message via variable d'environnement"
    os.write(tube[1], message.encode())
    os.close(tube[1])
    os.wait()