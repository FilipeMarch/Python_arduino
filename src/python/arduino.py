#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jul  9 02:47:55 2017

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
print ("You have selected", bluetooth.lookup_name(dispositivos_proximos[selecao]))

#Salvando o endereço bluetooth do dispositivo selecionado
bd_addr = dispositivos_proximos[selecao]

#Porta estabelecida para conexão
port = 1


class Application(Frame):
    
    #Instanciando um objeto da classe bluetooth
    sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )

    #Função para desconectar
    def disconnect(self):
        self.sock.close()
        
    #Função que faz o arduíno andar para frente
    def para_frente(self):
        data = "F"
        self.sock.send(data)
        
    #Função que faz o arduíno andar para trás
    def para_tras(self):
        data = "T"
        self.sock.send(data)

    #Criação de interface gráfica para controle do arduíno através de botões
    #numa aplicação
    def createWidgets(self):
        self.QUIT = Button(self)
        self.QUIT["text"] = "QUIT"
        self.QUIT["fg"]   = "red"
        self.QUIT["command"] =  self.quit

        self.QUIT.pack({"side": "left"})

        self.disconnectFrom = Button(self)
        self.disconnectFrom["text"] = "Disconnect"
        self.disconnectFrom["fg"]   = "darkgrey"
        self.disconnectFrom["command"] =  self.disconnect

        self.disconnectFrom.pack({"side": "left"})

        self.turnOn = Button(self)
        self.turnOn["text"] = "Para_frente",
        self.turnOn["fg"] = "green"
        self.turnOn["command"] = self.para_frente

        self.turnOn.pack({"side": "left"})

        self.turnOff = Button(self)
        self.turnOff["text"] = "Para_tras"
        self.turnOff["fg"] = "red"
        self.turnOff["command"] = self.para_tras

        self.turnOff.pack({"side": "left"})

    def __init__(self, master=None):
        #Conectando ao dispositivo bluetooth
        self.sock.connect((bd_addr, port))
        Frame.__init__(self, master)
        self.pack()
        self.createWidgets()

root = Tk()
app = Application(master=root)
app.mainloop()
root.destroy()
