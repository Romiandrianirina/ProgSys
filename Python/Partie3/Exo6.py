import sys

if len(sys.argv) != 3:
    print("Usage: python prog.py n1 n2")
else:
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    print(f"Somme = {a + b}")