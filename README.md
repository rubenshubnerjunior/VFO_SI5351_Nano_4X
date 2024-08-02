### Este projeto visa gerar frequência em quadratura ( 0º e 90° ) na faixa de 3 a 30 Mhz.
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/VFO_5351_4X.jpg)
#### Basicamente temos o módulo SI 5351 que é comandado através do Arduino Nano usando o protocolo I2C.
#### A saída do módulo SI 5351 deve estar em uma frequência de 4 vezes a frequência desejada para que o divisor por 4 feito pelo flip flop 74AC74 gere a quadratura.
#### O software HDSDR junto com o Omni-Rig usando a configuração TS-480 controla a frequencia e o PTT deste VFO.
#### Foi codificado em python um programa testeVFO.exe para testar o programa do arduino e está na pasta testeVFO o script e o executável.
#### O arquivo testeVFO.exe envia pela porta serial as Strings semelhante as geradas pelo HDSDR.
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/testeVFO.jpg)
#### O Arduino nano recebe os comandos através da porta serial (Terminal Serial ou do HDSDR/Omni-Rig) veja abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Diagramas/diagrama_vfo.jpg)
#### A Frequência (3 - 30 Mhz) e o Step ( 1Khz, 10Khz, 100Khz e 1000Khz) também pode ser ajustada através do Encoder em KHZ.
#### O PTT também pode ser acionado via contato diretamente na placa.
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/VFO_Encoder.jpg)
#### A faixa de 3 a 30 Mhz pode ser dividida em 08 subfaixas e coloca em nivel HI ou Low as saidas do conector para usar nas comutações dos filtros (vide esquema).
#### O display mostra a frequência de saída bem como a faixa e o Step ajustado.
#### O código fonte do arduino (pasta cat11) está bem comentado (CAT= Computer Aided Transceiver ou Computer Aided Tuning).
#### Durante o processo de programação para fazer o Debug foi utilizado outro arduino Nano como escravo I2C pois a porta serial do arduino usado no VFO fica ocupada recebendo e enviando dados para o computador:
-  ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/nano_debug.jpg)
#### Foi usado o codigo monitor_I2C em outro Arduino Nano Escravo para fazer o Debug pela porta serial (I2C -> Serial), acrescidas linhas de codigo no arduino do cat11.ino para enviar mensagens ao escravo isto somente para Debug depois as linhas foram comentadas e o arduino Nano escravo retirado do circuito.

#### Alguns comandos enviados e recebidos via porta Serial:
- FA00006000000; // HDSDR ajusta o VFO para 6 Mhz
- FA00030000000;  // HDSDR ajusta o VFO para 30 Mhz
- TX1;  // HDSDR envia informação para entrar no modo TX
- RX;   // HDSDR  envia informação para entrar no modo RX
- FA;   // HDSDR pede informação da frequência para o VFO
- FA00007349999; // VFO informa a frequencia para o HDSDR
#### Os comandos do HDSDR para o VFO e do VFO para o HDSDR sempre tem o (;) no final
#### O HDSDR pede várias informações ao VFO e não implementei todas por isto fica a mensagem de Rig não responde.
####  Tela de Configuração do Omni-Rig (A porta do Arduino Nano pode ser localizada no Gerenciador de Dispositivos):
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/Omnia_Config.jpg)
#### No HDSDR no menu Options:
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/HDSDR_01.jpg)
  #### Não esquecer de ativar.
  #### No HDSDR no menu Options:
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/HDSDR_02.jpg)
  #### No HDSDR no menu Options:
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/HDSDR_03.jpg)
  #### No HDSDR no menu Options:
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/HDSDR_04.jpg)
### O HDSDR tem muitas configurações mas estas são suficientes para acionar o VFO, outras deverão ser feitas quando for receber ou gerar os sinais I e Q da placa de som.
### Testes:
- https://www.youtube.com/watch?v=RT_Q52dTLLc&t=126s
#### Sugestões sempre ajudam.

### 73's  PY2 RHJ     ID DMR:7245251

