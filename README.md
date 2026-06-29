# Cubo Mágico em C

Implementação funcional de um **Cubo Mágico (Rubik's Cube) 3×3×3** em linguagem C.

---

##  Funcionalidades

- **Representação do cubo** como matriz tridimensional `[6][3][3]` com cores enumeradas
- **Rotações completas** nas 6 direções (Norte, Sul, Leste, Oeste, Frente, Trás), no sentido horário e anti-horário
- **Embaralhador automático** com geração de múltiplos cubos embaralhados salvos em arquivos `.txt`
- **Visualizador interativo** no terminal usando a biblioteca `ncurses`, com cores reais de cada face
- **Resolvedor automático** baseado no método de camadas:
  1. Cruz branca
  2. Cantos brancos
  3. Camada do meio
  4. Cruz amarela
  5. Face amarela
  6. Cantos amarelos
  7. Arestas amarelas

---

##  Estrutura do Projeto

```
.
├── include/
│   ├── cubo.h          # Estrutura principal, tipos e protótipos
│   ├── rotacoes.h      # Protótipos das rotações
│   ├── detector.h      # Funções de leitura e verificação do cubo
│   └── curses.h        # Visualizador ncurses
├── rotacoes.c          # Implementação de todas as rotações
├── embaralhador.c      # Gerador de cubos embaralhados
├── resolvedor.c        # Algoritmo resolvedor (método de camadas)
└── README.md

```

---

##  Visualização

O visualizador usa `ncurses` para exibir o cubo no terminal com as cores reais de cada face:

```
        (UP)
(LEFT) (FRONT) (RIGHT) (BACK)
       (DOWN)
```

Cada face é exibida com sua cor correspondente:

| Cor | Face |
|---|---|
| ⬜ Branco | Cima |
| 🟡 Amarelo | Baixo |
| 🟢 Verde | Frente |
| 🔵 Azul | Direita |
| 🟣 Magenta | Esquerda |
| 🔴 Vermelho | Trás |

---


##  Formato dos Arquivos de Cubo

Os cubos são salvos em arquivos `.txt` no seguinte formato:

```
Face: CIMA
  0  0  0
  0  0  0
  0  0  0

Face: BAIXO
  1  1  1
...
```

Cada número representa uma cor (0 = Branco, 1 = Amarelo, 2 = Verde, 3 = Azul, 4 = Magenta, 5 = Vermelho).
