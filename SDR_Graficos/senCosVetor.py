

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Cria a figura e os eixos
fig, ax = plt.subplots(1, 2, figsize=(10, 5))
circle_ax, graph_ax = ax

# Configura o gráfico do círculo unitário
circle_ax.set_xlim(-1.5, 1.5)
circle_ax.set_ylim(-1.5, 1.5)
circle_ax.set_aspect('equal')
circle_ax.set_title('Representação Vetorial')
circle_ax.grid()

# Desenha o círculo unitário
circle = plt.Circle((0, 0), 1, color='lightgray', fill=False)
circle_ax.add_artist(circle)

# Vetor girando
line, = circle_ax.plot([], [], 'r-', lw=2)
dot, = circle_ax.plot([], [], 'ro')

# Projeções seno e cosseno
cos_proj, = circle_ax.plot([], [], 'b--')
sin_proj, = circle_ax.plot([], [], 'g--')

# Configura o gráfico do seno e cosseno
graph_ax.set_xlim(0, 2*np.pi)
graph_ax.set_ylim(-1.2, 1.2)
graph_ax.set_title('Seno (verde) e Cosseno (azul)')
graph_ax.grid()

xdata, ysin, ycos = [], [], []
line_sin, = graph_ax.plot([], [], 'g-')
line_cos, = graph_ax.plot([], [], 'b-')

# Função de inicialização da animação
def init():
    line.set_data([], [])
    dot.set_data([], [])
    cos_proj.set_data([], [])
    sin_proj.set_data([], [])
    line_sin.set_data([], [])
    line_cos.set_data([], [])
    return line, dot, cos_proj, sin_proj, line_sin, line_cos

# Função de atualização
def update(frame):
    theta = frame
    x = np.cos(theta)
    y = np.sin(theta)

    # Vetor girando
    line.set_data([0, x], [0, y])
    dot.set_data([x], [y])
    cos_proj.set_data([0, x], [0, 0])
    sin_proj.set_data([0, 0], [0, y])

    # Atualiza os dados do gráfico
    xdata.append(theta)
    ysin.append(y)
    ycos.append(x)
    line_sin.set_data(xdata, ysin)
    line_cos.set_data(xdata, ycos)

    return line, dot, cos_proj, sin_proj, line_sin, line_cos

# Cria a animação
ani = animation.FuncAnimation(fig, update, frames=np.linspace(0, 2*np.pi, 200),
                              init_func=init, blit=True, interval=50, repeat=True)

plt.tight_layout()
plt.show()
