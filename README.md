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
│   ├── cubo.h                   # Estrutura principal, tipos e protótipos
│   ├── rotacoes.h               # Protótipos das rotações
│   ├── detector.h               # Funções de leitura e verificação do cubo
│   └── curses.h                 # Visualizador ncurses
├── cubos_embaralhados/          # Exemplos de cubos embaralhados (cubo_1.txt ... cubo_6.txt)
├── rotacoes.c                   # Implementação de todas as rotações
├── embaralhador.c               # Gerador de cubos embaralhados
├── resolvedor.c                 # Algoritmo resolvedor (método de camadas)
├── cubo3x3.c                    # Primeiro protótipo (matrizes 3×3×3)
├── geradorcuboresolvido.c       # Gerador de um cubo resolvido
├── geradordecubosaleatorios.c   # Gerador de cubos aleatórios
├── makefile
└── README.md
```

---

##  Como compilar e executar

### Requisitos

- Linux ou WSL (Ubuntu)
- `gcc`, `make` e a biblioteca `ncurses`

```bash
sudo apt update
sudo apt install -y build-essential libncurses-dev
```

### Compilar

```bash
git clone https://github.com/LeoFR007/Cubo_Magico_C.git
cd Cubo_Magico_C
make
```

O `make` gera dois executáveis: `embaralhador` e `resolvedor`.

### Executar

1. **Gerar cubos embaralhados** (opcional, a pasta `cubos_embaralhados/` já vem com 6 exemplos):

   ```bash
   ./embaralhador
   ```

   O programa pergunta quantos cubos criar e salva cada um em `cubos_embaralhados/cubo_N.txt`. Ele apaga os cubos anteriores antes de criar os novos.

2. **Resolver um cubo:**

   ```bash
   ./resolvedor
   ```

   Digite o número do cubo (por exemplo, `1` para `cubo_1.txt`). O visualizador abre no terminal e mostra o cubo após cada etapa do método de camadas. Aperte qualquer tecla para avançar.

### Limpar

```bash
make clean
```

Remove os objetos, os executáveis e também a pasta `cubos_embaralhados/`.

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
