### Este projeto visa gerar frequência em quadratura ( 0º e 90° ) na faixa de 3 a 30 Mhz.
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/VFO_5351_4X.jpg)
#### Basicamente temos o módulo SI 5351 que é comandado através do Arduino nano usando o protocolo I2C.
#### A saída do módulo SI 5351 deve estar em uma frequência de 4 vezes a frequência desejada para que o divisor por 4 feito pelo flip flop 74AC74 gere a quadratura.
#### O Arduino nano recebe os comandos através da porta serial (Terminal Serial ou do HDSDR/Omni-Rig) veja abaixo:
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Diagramas/diagrama_vfo.jpg)
#### A frequência e o Step tambem pode ser ajustada através do Encoder em KHZ.
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/VFO_Encoder.jpg)
#### A faixa de 3 a 30 Mhz pode ser dividida em 08 subfaixas e coloca em nivel HI ou Low as saidas do conector para usar nas comutações dos filtros (vide esquema).
#### O software HDSDR junto com o Omni-rig usando a configuração TS-480 controla a frequencia e o PTT deste VFO.
#### O display mostra a frequência de saída bem como a faixa e o Step ajustado.
#### O código fonte do arduino (pasta cat11) está bem comentado.
#### Durante o processo de programação para fazer o Debug foi utilizado outro arduino Nano como escravo I2C pois a porta serial do arduino usado no VFO fica ocupada recebendo e enviando dados para o computador:
-  ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/nano_debug.jpg)
#### Foi usado o codigo 


### Sugestões sempre ajudam.

### 73's  PY2 RHJ     ID DMR:7245251

