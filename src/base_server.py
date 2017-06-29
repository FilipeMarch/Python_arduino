# -*- coding: utf-8 -*-
"""
Created on Wed Jun 20 04:45:23 2017

@author: Filipovisk
"""

"""
Servidor: Abre um TCP/IP numa port, espera por uma menssagem
de um cliente, e manda uma mensagem de volta como resposta.
"""
 
from socket import *
 
# Cria o nome do host
meuHost = 'localhost'
 
# Utiliza este número de porta'
minhaPort = 50007
 
# Cria um objeto socket. As duas constantes referem-se a:
# Familia do endereço (padrão é socket.AF_INET)
# Se é stream (socket.SOCK_STREAM, o padrão) ou datagram (socket.SOCK_DGRAM)
# AF_INIT == Protocolo de endereço de IP
# SOCK_STREAM == Protocolo de transferência TCP
# Combinação = Server TCP/IP
sockobj = socket(AF_INET, SOCK_STREAM)
 
# Vincula o servidor ao número de porto
sockobj.bind((meuHost, minhaPort))
 
# O socket começa a esperar por clientes limitando a 
# 5 conexões por vez
sockobj.listen(5)
 
 
while True:
    # Aceita uma conexão quando encontrada e devolve a
    # um novo socket conexão e o endereço do cliente
    # conectado
    conexão, endereço = sockobj.accept()
    print('Server conectado por', endereço)
     
    while True:
        
        #Responde o cliente
        msg = input('Servidor: ')
        conexão.send(msg.encode())
        
        
         
        # Recebe data enviada pelo cliente
        data = conexão.recv(1024)
        print('Cliente: ', data.decode())
        
        #Se não houver nada, cair fora do loop
        if not data: break
 

     
    # Fecha a conexão criada depois de responder o
    # cliente
    conexão.close()
