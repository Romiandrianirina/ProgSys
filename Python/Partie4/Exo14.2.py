import os
import sys

if len(sys.argv) != 3:
    sys.exit(1)
fd_lecture = int(sys.argv[1])
fd_ecriture = int(sys.argv[2])
os.close(fd_ecriture)
data = os.read(fd_lecture, 256)
print("Message reçu:", data.decode())