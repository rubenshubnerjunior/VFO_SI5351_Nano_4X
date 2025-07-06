

import numpy as np
import matplotlib.pyplot as plt

# Intervalo de graus
t_graus = np.linspace(0, 360, 1000)  # de 0° a 360°

# Frequências (em ciclos por 360 graus)
fA = 1000  # A faz 1000 ciclos em 360°
fB = 30000  # B faz 30000 ciclos em 360°

# Converter graus para radianos para usar np.cos
t_rad_A = np.deg2rad(fA * t_graus)
t_rad_B = np.deg2rad(fB * t_graus)

# Gerar sinais
A = np.cos(t_rad_A)
B = np.cos(t_rad_B)
produto = A * B

# Plotar
plt.figure(figsize=(12, 6))
plt.plot(t_graus, A, label='cos(A)', alpha=0.7)
plt.plot(t_graus, B, label='cos(B)', alpha=0.7)
plt.plot(t_graus, produto, label='cos(A) * cos(B)', linewidth=2, color='black')

plt.title('Produto de cos(A) * cos(B) em graus')
plt.xlabel('Ângulo (graus)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
