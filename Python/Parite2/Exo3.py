import os

for i in range(5):
    pid = os.fork()
    if pid == 0:
        print(f"fils {i+1}")
        os._exit(0)
for _ in range(5):
    os.wait()