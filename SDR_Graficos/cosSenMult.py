

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Frequências
A = 1000  # frequência mais alta
B = 10   # frequência mais baixa

# Vetor de tempo
t = np.linspace(0, 2 * np.pi, 500)

# Componentes da identidade trigonométrica
cos_sum = 0.5 * np.cos((A + B) * t)    # cos((A+B)t)/2
cos_diff = 0.5 * np.cos((A - B) * t)   # cos((A-B)t)/2
produto = cos_sum + cos_diff           # cos(A t) * cos(B t)

# Criação da figura
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(9, 9), gridspec_kw={'height_ratios': [2, 1]})

# === Painel vetorial ===
ax1.set_xlim(-1.5, 1.5)
ax1.set_ylim(-1.5, 1.5)
ax1.set_aspect('equal')
ax1.grid(True)
ax1.set_title("Identidade trigonométrica: cos(A·t)·cos(B·t)")

# Círculo de fundo
circle = plt.Circle((0, 0), 1, color='lightgray', fill=False)
ax1.add_patch(circle)

# Vetores individuais
line_sum, = ax1.plot([], [], color='orange', lw=2, label='cos((A+B)·t)/2')
line_diff, = ax1.plot([], [], color='purple', lw=2, label='cos((A−B)·t)/2')
line_prod, = ax1.plot([], [], 'g-', lw=3, label='Soma (produto final)')

ax1.legend(loc="upper right")

# === Painel do sinal no tempo ===
ax2.set_xlim(t[0], t[-1])
ax2.set_ylim(-1.1, 1.1)
ax2.grid(True)
ax2.set_title("cos(A·t)·cos(B·t) = ½[cos((A−B)·t) + cos((A+B)·t)]")

# Sinais no tempo
ax2.plot(t, cos_sum, color='orange', linestyle='--', label='cos((A+B)t)/2')
ax2.plot(t, cos_diff, color='purple', linestyle='--', label='cos((A−B)t)/2')
ax2.plot(t, produto, 'gray', lw=1, label='Produto final')
point_signal, = ax2.plot([], [], 'ro')  # ponto em movimento
ax2.legend(loc="upper right")

# Inicialização
def init():
    line_sum.set_data([], [])
    line_diff.set_data([], [])
    line_prod.set_data([], [])
    point_signal.set_data([], [])
    return line_sum, line_diff, line_prod, point_signal

# Animação
def animate(i):
    t_val = t[i]

    # Componentes da identidade
    angle_sum = (A + B) * t_val
    angle_diff = (A - B) * t_val

    # Vetores rotacionando no círculo
    x_sum = 0.5 * np.cos(angle_sum)
    y_sum = 0.5 * np.sin(angle_sum)

    x_diff = 0.5 * np.cos(angle_diff)
    y_diff = 0.5 * np.sin(angle_diff)

    # Soma vetorial dos dois componentes
    x_prod = x_sum + x_diff
    y_prod = y_sum + y_diff

    # Atualizar vetores no painel vetorial
    line_sum.set_data([0, x_sum], [0, y_sum])
    line_diff.set_data([0, x_diff], [0, y_diff])
    line_prod.set_data([0, x_prod], [0, y_prod])

    # Atualizar ponto no gráfico do tempo
    prod_val = np.cos(A * t_val) * np.cos(B * t_val)
    point_signal.set_data([t_val], [prod_val])

    return line_sum, line_diff, line_prod, point_signal

# Criar animação
ani = animation.FuncAnimation(
    fig, animate, init_func=init,
    frames=len(t), interval=20, blit=True
)

plt.tight_layout()
plt.show()
