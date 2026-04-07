import os
import sys

def main():
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} n k output_file")
        sys.exit(1)
    n = int(sys.argv[1])
    k = int(sys.argv[2])
    output = sys.argv[3]

    if k == 0 or k == n:
        with open(output, 'w') as f:
            f.write("1\n")
        sys.exit(0)

    # créer deux fichiers temporaires
    import tempfile
    fd1, temp1 = tempfile.mkstemp(prefix="/tmp/binom_")
    fd2, temp2 = tempfile.mkstemp(prefix="/tmp/binom_")
    os.close(fd1)
    os.close(fd2)

    pid1 = os.fork()
    if pid1 == 0:
        os.execl(sys.argv[0], sys.argv[0], str(n-1), str(k-1), temp1)
    pid2 = os.fork()
    if pid2 == 0:
        os.execl(sys.argv[0], sys.argv[0], str(n-1), str(k), temp2)

    os.waitpid(pid1, 0)
    os.waitpid(pid2, 0)

    with open(temp1, 'r') as f:
        val1 = int(f.read().strip())
    with open(temp2, 'r') as f:
        val2 = int(f.read().strip())
    result = val1 + val2
    with open(output, 'w') as f:
        f.write(f"{result}\n")
    os.unlink(temp1)
    os.unlink(temp2)

if __name__ == "__main__":
    main()