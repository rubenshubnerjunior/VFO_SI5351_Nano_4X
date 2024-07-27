
# Escrito por Rubens Hubner Junior em 07/01/2024

# Ajusta a frequencia do VFO pela porta serial
# Trabalha com o Sketch do arduino nano (cat11) para controle do VFO SI5351
# Abre a porta serial que esta sendo usada pelo arduino nano
# Após a digitação gera a String no formato Omni-Rig TS-480 "FA00006000000;" e envia para a porta Serial


#  pip install pyserial ( para usar a porta serial)
#  pip install pyinstaller ( para gerar arquivo .exe)
#  pyinstaller --onefile -w testeVFO.py

import serial
import time
from tkinter import *

janela = Tk()

open_serial = False
arduino=""


def concatenar(elemento): # Concatena valores digitatos nos botoes

    equacao = inDig.get() # Leitura do campo texto
    inDig.delete(0,END) # limpa o campo de texto
    inDig.insert(0,equacao + elemento) # concatena os numeros chegados e coloca no campo texto
  
def limpar():
    inDig.delete(0,END) # Limpa o campo texto da frequencia enviada

def limpar1():
    msgEnviada.delete(0,END) # Limpa o campo texto da mensagem enviada


def hz():
    valorDig= inDig.get() #Leitura do campo texto
    fHz=float(valorDig) # conversao para float
    intHz= int(fHz)  # desconsidera a casa decimal

    freqTotal = "00000000000000000" + str(intHz)
    final = len(freqTotal)
    inicio = final-11
    freqFinal=freqTotal[inicio:final]
    msgFormat= "FA"+ freqFinal + ";" # String enviado no Formato do Omni-Rig TS-480
    print(msgFormat)
    serialCom(msgFormat)
    limpar()
    limpar1()
    msgEnviada.insert(0,msgFormat) 


def khz():
    valorDig= inDig.get() #Leitura do campo texto
    fKHz=float(valorDig) # conversao para float
    fKHz=fKHz*1000 # escala Khz para Hz
    intKhz=int(fKHz) # desconsidera a casa decimal

    freqTotal = "00000000000000000" + str(intKhz)
    final = len(freqTotal)
    inicio = final-11
    freqFinal=freqTotal[inicio:final]
    msgFormat= "FA"+ freqFinal + ";" # String enviado no Formato do Omni-Rig TS-480
    print(msgFormat)
    serialCom(msgFormat)
    limpar()
    limpar1()
    msgEnviada.insert(0,msgFormat) 

def mhz():
    valorDig= inDig.get() #Leitura do campo texto
    fMHz=float(valorDig) # conversao para float
    fMHz=fMHz*1000000 # escala Mhz para Hz
    intMhz=int(fMHz) # desconsidera a casa decimal

    freqTotal = "00000000000000000" + str(intMhz)
    final = len(freqTotal)
    inicio = final-11
    freqFinal=freqTotal[inicio:final]
    msgFormat= "FA"+ freqFinal + ";" # String enviado no Formato do Omni-Rig TS-480
    print(msgFormat)
    serialCom(msgFormat)
    limpar()
    limpar1()
    msgEnviada.insert(0,msgFormat) 

def tx():
    serialCom("TX;") # String enviado no Formato do Omni-Rig TS-480
    limpar1()
    msgEnviada.insert(0,"TX;") 

def rx():
    serialCom("RX;") # String enviado no Formato do Omni-Rig TS-480
    limpar1()
    msgEnviada.insert(0,"RX;") 

def serialCom(msg):
    global open_serial
    global arduino

    msg = msg +"\n"
    print(msg)
    if(open_serial==False): #Precisa confirmar se a porta está aberta
        abreSerial() 
        time.sleep(2)
    try:
       arduino.write(msg.encode())
       print("Enviando...")
    except:
        print("nao enviou")
        pass   


def abreSerial():
    global open_serial
    global arduino
    com = portaSerial.get() # Porta Com digitado no campo texto
    try:
      arduino = serial.Serial(com, 115200)
      print(arduino)
      open_serial=True
    except serial.SerialException:
        print("Porta nao encontrada")
        open_serial=False
        pass
   
    
janela.title('Ajusta VFO SI5351')


fonte="Helvetica 10 bold"

#=======================Elementos da GUI=========================================

bt0 =       Button(janela,font=fonte,padx=50,pady=20, text = '0',relief="raised", command=lambda:concatenar("0")) # lambda para passar paramentro para a funcao
bt1 =       Button(janela,font=fonte,padx=50,pady=20, text = '1',relief="raised", command=lambda:concatenar("1")) # lambda para passar paramentro para a funcao
bt2 =       Button(janela,font=fonte,padx=50,pady=20, text = '2',relief="raised", command=lambda:concatenar("2")) # lambda para passar paramentro para a funcao
bt3 =       Button(janela,font=fonte,padx=50,pady=20, text = '3',relief="raised", command=lambda:concatenar("3")) # lambda para passar paramentro para a funcao
bt4 =       Button(janela,font=fonte,padx=50,pady=20, text = '4',relief="raised", command=lambda:concatenar("4")) # lambda para passar paramentro para a funcao
bt5 =       Button(janela,font=fonte,padx=50,pady=20, text = '5',relief="raised", command=lambda:concatenar("5")) # lambda para passar paramentro para a funcao
bt6 =       Button(janela,font=fonte,padx=50,pady=20, text = '6',relief="raised", command=lambda:concatenar("6")) # lambda para passar paramentro para a funcao
bt7 =       Button(janela,font=fonte,padx=50,pady=20, text = '7',relief="raised", command=lambda:concatenar("7")) # lambda para passar paramentro para a funcao
bt8 =       Button(janela,font=fonte,padx=50,pady=20, text = '8',relief="raised", command=lambda:concatenar("8")) # lambda para passar paramentro para a funcao
bt9 =       Button(janela,font=fonte,padx=50,pady=20, text = '9',relief="raised", command=lambda:concatenar("9")) # lambda para passar paramentro para a funcao
btVirg =    Button(janela,font=fonte,padx=50,pady=20, text = ',',relief="raised", command=lambda:concatenar(".")) # lambda para passar paramentro para a funcao
btHz =      Button(janela,font=fonte,padx=45,pady=20, text = 'Hz',relief="raised",command = hz) # chamada da funcao sem passar paramentro
btKhz =     Button(janela,font=fonte,padx=40,pady=20, text = 'Khz',relief="raised",command = khz) # chamada da funcao sem passar paramentro
btMhz =     Button(janela,font=fonte,padx=40,pady=20, text = 'Mhz',relief="raised",command = mhz) # chamada da funcao sem passar paramentro
btLimpar =  Button(janela,font=fonte,padx=40,pady=20, text = 'DEL',relief="raised", command = limpar) # chamada da funcao sem passar paramentro
btTX =      Button(janela,font=fonte,padx=45,pady=20, text = 'TX',relief="raised", command = tx) # chamada da funcao sem passar paramentro
btRX =      Button(janela,font=fonte,padx=45,pady=20, text = 'RX',relief="raised", command = rx) # chamada da funcao sem passar paramentro

labelDig = Label(janela, font=fonte, text="Digitado:")
inDig = Entry(janela,font=fonte,width=30)

labelPorta = Label(janela,font=fonte, text="Porta Serial:")
portaSerial = Entry(janela,font=fonte,width=30)

portaSerial.insert(0,"COM1")

labelMsgEnviada = Label(janela,font=fonte, text="Mensagem Enviada:")
msgEnviada = Entry(janela,font=fonte,width=30)


#=============Colocando componentes na grid===============================
bt7.grid(row = 0, column = 0)
bt8.grid(row = 0, column = 1) # linha 0
bt9.grid(row = 0, column = 2)
btHz.grid(row = 0, column = 3)

bt4.grid(row = 1, column = 0)
bt5.grid(row = 1, column = 1)  # linha 1
bt6.grid(row = 1, column = 2)
btKhz.grid(row = 1, column = 3)

bt1.grid(row = 2, column = 0)
bt2.grid(row = 2, column = 1)  # linha 2
bt3.grid(row = 2, column = 2)
btMhz.grid(row = 2, column = 3)

bt0.grid(row = 3, column = 0)
btVirg.grid(row = 3, column = 1)  # linha 3
btLimpar.grid(row = 3, column =2)

btTX.grid(row = 4, column = 2) # linha 4
btRX.grid(row = 4, column = 3)


labelDig.grid(row = 5, column = 0)
inDig.grid(row = 5,    column = 1,pady=30)  # linha 5

labelPorta.grid(row = 6, column = 0)
portaSerial.grid(row = 6, column = 1)  # linha 6

labelMsgEnviada.grid(row = 7, column = 0)
msgEnviada.grid(row = 7,    column = 1,pady=30)  # linha 7


janela.configure(bg='WHITE')
janela.geometry("600x500")
janela.resizable(False, False)
janela.mainloop()

