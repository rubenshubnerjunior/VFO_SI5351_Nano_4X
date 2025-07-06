

import numpy as np
import matplotlib.pyplot as plt

# Intervalo de ângulos em graus
t_graus = np.linspace(0, 360, 1000)

# Frequências (ciclos por 360 graus)
fA = 1000  # frequência de A
fB = 30000  # frequência de B

# Conversão para radianos
t_rad_A = np.deg2rad(fA * t_graus)
t_rad_B = np.deg2rad(fB * t_graus)

# Sinais cos
cosA = np.cos(t_rad_A)
cosB = np.cos(t_rad_B)
produto_cos = cosA * cosB

# Sinais sin
sinA = np.sin(t_rad_A)
sinB = np.sin(t_rad_B)
produto_sin = sinA * sinB

# Soma dos produtos: cos(A)*cos(B) + sin(A)*sin(B)
soma = produto_cos + produto_sin

# Equivalente a cos(A - B)
t_rad_diff = np.deg2rad((fA - fB) * t_graus)
cos_diff = np.cos(t_rad_diff)

# Gráficos
plt.figure(figsize=(8, 14))

# Gráfico 1: cos(A) * cos(B)
plt.subplot(3, 1, 1)
plt.plot(t_graus, cosA, label='cos(A)', alpha=0.7)
plt.plot(t_graus, cosB, label='cos(B)', alpha=0.7)
plt.plot(t_graus, produto_cos, label='cos(A) * cos(B)', linewidth=2, color='black')
plt.title('Produto de cos(A) * cos(B)')
#plt.xlabel('Ângulo (graus)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.legend()

# Gráfico 2: sin(A) * sin(B)
plt.subplot(3, 1, 2)
plt.plot(t_graus, sinA, label='sin(A)', alpha=0.7)
plt.plot(t_graus, sinB, label='sin(B)', alpha=0.7)
plt.plot(t_graus, produto_sin, label='sin(A) * sin(B)', linewidth=2, color='black')
plt.title('Produto de sin(A) * sin(B)')
#plt.xlabel('Ângulo (graus)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.legend()

# Gráfico 3: soma dos produtos (cos(A)*cos(B) + sin(A)*sin(B)) e comparação com cos(A-B)
plt.subplot(3, 1, 3)
plt.plot(t_graus, soma, label='cos(A)*cos(B) + sin(A)*sin(B)', linewidth=2, color='black')
plt.plot(t_graus, cos_diff, label='cos(A - B)', linestyle='--', color='red')
plt.title('Soma dos Produtos = cos(A - B)')
#plt.xlabel('Ângulo (graus)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()
