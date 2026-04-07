import os

tube1 = os.pipe()  # fils->père
tube2 = os.pipe()  # père->fils

pid = os.fork()
if pid == 0:  # fils
    os.close(tube1[0])
    os.close(tube2[1])
    mot = input("Le mot que vous recherchez: ")
    os.write(tube1[1], mot.encode())
    os.close(tube1[1])
    result = int.from_bytes(os.read(tube2[0], 4), 'little')
    if result:
        print("Le mot a été trouvé")
    else:
        print("Le mot n'existe pas")
else:  # père
    os.close(tube1[1])
    os.close(tube2[0])
    mot_recu = os.read(tube1[0], 50).decode().strip('\x00')
    trouve = 0
    try:
        with open("texte.txt", "r") as f:
            for ligne in f:
                for mot in ligne.split():
                    if mot == mot_recu:
                        trouve = 1
                        break
                if trouve:
                    break
    except FileNotFoundError:
        pass
    os.write(tube2[1], trouve.to_bytes(4, 'little'))
    os.close(tube2[1])
    os.wait()