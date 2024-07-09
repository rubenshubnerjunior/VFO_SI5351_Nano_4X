Este projeto serve para comandar o modulo SI 5351 via arduino nano e a saida em quadratura usando o Flip-Flop 74AC74 como divisor por 4.
Portanto a saída do módulo SI 5351 deve ter uma frequência 4 vezes a frequ~encia desejada.
O Arduino nano recebe o comando para ajustar a frequencia através da porta serial e comanda o modulo com a comunicação I2C.
A faixa de 3 a 30 Mhz é dividada em 08 subfaixas e com a saida em nivel HI para acionar a troca dos filtros.
