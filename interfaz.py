import os
import re
import threading
import time
import tkinter as tk

import servidor

PATRON = re.compile(r"Placa:\s*(\S+)\s*\|\s*Hora:\s*(\S+)\s*\|\s*Espacio:\s*(\d+)")


class Interfaz:
    def __init__(self):
        self.placas = {}
        self.lineas = []
        self.celdas = {}

        self.ventana = tk.Tk()
        self.ventana.title("Parqueadero")
        marco = tk.Frame(self.ventana)
        marco.grid(row=0, column=0, padx=10, pady=10)
        for n in range(1, 101):
            celda = tk.Label(marco, text=f"{n}\n", width=9, height=2, bg="green", fg="white")
            celda.grid(row=(n - 1) // 10, column=(n - 1) % 10, padx=1, pady=1)
            self.celdas[n] = celda
        self.contador = tk.Label(self.ventana, font=("Arial", 14, "bold"))
        self.contador.grid(row=0, column=1, sticky="n", padx=10, pady=10)
        self.lista = tk.Listbox(self.ventana, width=45, height=22)
        self.lista.grid(row=0, column=1, padx=10, pady=(50, 10))
        self.actualizar_contador()

        lectura, escritura = os.pipe()
        os.dup2(escritura, 1)
        threading.Thread(target=self.leer_pipe, args=(lectura,), daemon=True).start()
        threading.Thread(target=self.correr_servidor, daemon=True).start()

        self.ventana.after(200, self.revisar)
        self.ventana.mainloop()

    def correr_servidor(self):
        while True:
            servidor.iniciar_servidor()
            time.sleep(1)

    def leer_pipe(self, pipe):
        texto = ""
        while True:
            texto += os.read(pipe, 4096).decode(errors="replace")
            *completas, texto = texto.split("\n")
            self.lineas.extend(completas)

    def revisar(self):
        while self.lineas:
            datos = PATRON.search(self.lineas.pop(0))
            if datos:
                self.procesar(datos[1], datos[2], int(datos[3]))
        self.ventana.after(200, self.revisar)

    def procesar(self, placa, hora, espacio):
        if placa in self.placas:
            n = self.placas.pop(placa)
            self.celdas[n].config(bg="green", text=f"{n}\n")
            self.lista.insert(0, f"{hora} SALE   {placa} (celda {n})")
        else:
            libres = [n for n in range(1, 101) if n not in self.placas.values()]
            if not libres:
                self.lista.insert(0, f"{hora} LLENO  {placa}")
                return
            n = espacio if espacio in libres else libres[0]
            self.placas[placa] = n
            self.celdas[n].config(bg="red", text=f"{n}\n{placa}")
            self.lista.insert(0, f"{hora} ENTRA  {placa} (celda {n})")
        self.actualizar_contador()

    def actualizar_contador(self):
        ocupadas = len(self.placas)
        self.contador.config(text=f"Libres: {100 - ocupadas}   Ocupadas: {ocupadas}")


Interfaz()
