# -*- coding: utf-8 -*-
"""
Created on Wed Jun 21 03:41:23 2017

@author: Filipovisk
"""

"""
Cliente: Usa sockets para mandar data para o servidor e depois imprime
a resposta do servidor. Podemos colocar o host como sendo localhost para 
indicar que o servidor está na mesma máquina. 
"""
 
from socket import *


def modificar():
    info = msg2[0:1]+msg2[2:-2]
    print('Servidor: ', msg2)
    print('Cliente: ', info)
    sockobj.send(info.encode())
    return

def requisitar():
    info = msg2[0:1]+msg2[2:-2]
    print('Servidor: ', msg2)
    print('Cliente: ', info)
    sockobj.send(info.encode())
    return

def debugar():
    info = msg2[0:1]+msg2[2:-2]
    print('Servidor: ', msg2)
    print('Cliente: Compre Paçoca!')
    sockobj.send(info.encode())
    return

def retornar():
    info = msg2[0:1]+msg2[2:-2]
    print('Servidor: ', msg2)
    print('Cliente :', info)
    sockobj.send(info.encode())
    return


# Configurações de conexão do servidor
# O nome do servidor pode ser um endereço de IP ou um domínio
serverHost = 'localhost'
serverPort = 50007
 
# Criamos o socket e o conectamos ao servidor
sockobj = socket(AF_INET, SOCK_STREAM)
sockobj.connect((serverHost, serverPort))
 

while True:
    # Anota e manda a mensagem
    '''
    msg = input("Cliente: ")
    sockobj.send(msg.encode())
    '''
 
    # Recebe uma mensagem (em bytes) do servidor
    data = sockobj.recv(1024)
    # Salva a mensagem numa variável
    if data:
        msg2 = data.decode()
        
    
    # Se a mensagem começar com S, então modificar
    if msg2[0] == 'S':
        modificar() 
        
    # Se a mensagem começar com G, então requisitar    
    elif msg2[0] == 'G':
        requisitar()
        
    # Se a mensagem começar com M, então mostrar mensagens de debug
    elif msg2[0] == "M":
        debugar()
    
    # Se a mensagem começar com R, então mostrar retorno de Get ou Set
    elif msg2[0] == "R":
        retornar()
        
 
# Fechamos a conexão
sockobj.close()
