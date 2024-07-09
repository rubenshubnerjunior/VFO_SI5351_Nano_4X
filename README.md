### Este projeto visa gerar frequência em quadratura ( 0º e 90° ) na faixa de 3 a 30 Mhz.
#### Basicamente temos o módulo SI 5351 comandado através do Arduino nano usando o protocolo I2C.
#### A saída do módulo I2C deve estar em uma frequência de 4 vezes a frequência desejada para que o divisor por 4 feito pelo flip flop 74AC74 gere a quadratura.
#### O Arduino nano recebe os comandos através da porta serial ou pelo encoder.
#### A faixa de 3 a 30 Mhz pode ser dividida em 08 subfaixas e coloca em nivel HI ou Low as saidas do conector para usar nas comutações dos filtros (vide esquema).
#### No encoder é possivel definir o Step que será aplicado a frequência de saída em Khz.
#### O display mostra a frequência de saída bem como a faixa e o Step ajustado.
#### Para maiores detalhes da comunicação Serial com o arduino, pode ser visto com mais detalhes em outro projeto: https://github.com/rubenshubnerjunior/VFO_SI5351_Serial .
#### Este projeto ainda falta implementar o PTT.
#### O código fonte do arduino está bem comentado.
### Sugestões sempre ajudam.

### 73's  PY2 RHJ

