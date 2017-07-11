#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 10 15:48:07 2017

@author: filipemarch
"""

#Importando as bibliotecas tkinter para construção de interface gráfica e
#a biblioteca bluetooth da PyBluez
from tkinter import *
import bluetooth

print ("Procurando por dispositivos...")
print ("")

#Detectando dispositivos próximos
dispositivos_proximos = bluetooth.discover_devices()
num = 0

#Mostrando os nomes dos dispositivos detectados
print ("Selecione seu disposito inserindo o número correspondente...")
for dispositivo in dispositivos_proximos:
	num+=1
	print (num, ": ", bluetooth.lookup_name(dispositivo))
    
selecao = int(input("> ")) - 1

#Avisando qual dispositivo selecionado
print ("Você selecionou ", bluetooth.lookup_name(dispositivos_proximos[selecao]))

#Salvando o endereço bluetooth do dispositivo selecionado
bd_addr = dispositivos_proximos[selecao]

#Porta estabelecida para conexão
port = 1

#Conectando ao dispositivo bluetooth
sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))    
    
 
running = False
root = Tk()
jobid = None

#Iniciando o motor...
def start_motor(direction):
    
    sock.send('f')
    move(direction)

#Parando o motor após largar o click do botão
def stop_motor():
    sock.send('f')
    global jobid
    root.after_cancel(jobid)
    
#Continua enviando mensagens ao arduíno enquanto estiver clicando no botão de direção
def move(direction):
    global jobid
    sock.send(direction)
    jobid = root.after(100, move, direction)

#Criando os botões de direção e definindo o que acontece enquanto se clica e ao largar o clique
for direction in ("norte", "sul", "leste", "oeste"):
    button = Button(root, text=direction)
    button.pack(side=LEFT)
    button.bind('<ButtonPress-1>', lambda event, direction=direction[0]: start_motor(direction))
    button.bind('<ButtonRelease-1>', lambda event: stop_motor())

#Tchãn rãm...
root.mainloop()
