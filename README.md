### Este projeto visa gerar frequência em quadratura ( 0º e 90° ) na faixa de 3 a 30 Mhz.
- ![alt text](https://github.com/rubenshubnerjunior/VFO_SI5351_Nano_4X/blob/main/Fotos/VFO_5351_4X.jpg)
#### Basicamente temos o módulo SI 5351 comandado através do Arduino nano usando o protocolo I2C.
#### A saída do módulo SI 5352 deve estar em uma frequência de 4 vezes a frequência desejada para que o divisor por 4 feito pelo flip flop 74AC74 gere a quadratura.
#### O Arduino nano recebe os comandos através da porta serial ou pelo encoder veja o diagrama abaixo:
#### A faixa de 3 a 30 Mhz pode ser dividida em 08 subfaixas e coloca em nivel HI ou Low as saidas do conector para usar nas comutações dos filtros (vide esquema).
#### O software HDSDR junto com o Omni-rig usando a configuração TS-480 controla a frequencia e o PTT deste VFO.
#### No encoder é possivel definir o Step que será aplicado a frequência de saída em Khz.
#### O display mostra a frequência de saída bem como a faixa e o Step ajustado.
#### O código fonte do arduino (pasta cat11) está bem comentado.
### Sugestões sempre ajudam.

### 73's  PY2 RHJ     ID DMR:7245251

