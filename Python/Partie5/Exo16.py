import threading

def ma_fonction_thread(tableau):
    print("Tableau :", tableau)

tab = [1, 2, 3, 4, 5]
thread = threading.Thread(target=ma_fonction_thread, args=(tab,))
thread.start()
thread.join()