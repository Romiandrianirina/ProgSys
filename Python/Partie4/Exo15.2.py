import os
import sys

fd_lec = int(os.environ.get("FD_LECTURE", -1))
fd_ecr = int(os.environ.get("FD_ECRITURE", -1))
if fd_lec == -1 or fd_ecr == -1:
    print("Variables manquantes")
    sys.exit(1)
os.close(fd_ecr)
data = os.read(fd_lec, 256)
print("Message reçu:", data.decode())