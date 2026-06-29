# 🎲 Cubo Mágico em C

Implementação funcional de um **Cubo Mágico (Rubik's Cube) 3×3×3** em linguagem C, com embaralhador automático, visualizador interativo no terminal e resolvedor automático utilizando o método de camadas.

---

## 📋 Funcionalidades

- **Representação do cubo** como matriz tridimensional `[6][3][3]` com cores enumeradas
- **Rotações completas** nas 6 direções (Norte, Sul, Leste, Oeste, Frente, Trás), no sentido horário e anti-horário
- **Embaralhador automático** com geração de múltiplos cubos embaralhados salvos em arquivos `.txt`
- **Visualizador interativo** no terminal usando a biblioteca `ncurses`, com cores reais de cada face
- **Resolvedor automático** baseado no método de camadas (Layer-by-Layer):
  1. Cruz branca
  2. Cantos brancos
  3. Camada do meio
  4. Cruz amarela
  5. Face amarela
  6. Cantos amarelos
  7. Arestas amarelas

---

## 🗂️ Estrutura do Projeto

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

## ⚙️ Dependências

- Compilador C (`gcc`)
- Biblioteca `ncurses`

### Instalação das dependências (Ubuntu/Debian):

```bash
sudo apt install gcc libncurses5-dev libncursesw5-dev
```

---

## 🚀 Como Compilar e Executar

### Embaralhador

Gera `n` cubos embaralhados e salva na pasta `cubos_embaralhados/`:

```bash
gcc embaralhador.c rotacoes.c -o embaralhador
./embaralhador
```

### Resolvedor

Resolve um cubo a partir de um arquivo gerado pelo embaralhador:

```bash
gcc resolvedor.c rotacoes.c -o resolvedor -lncurses
./resolvedor cubos_embaralhados/cubo_1.txt
```

---

## 🎨 Visualização

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

Pressione `Q` para avançar entre as etapas da resolução.

---

## 🧠 Algoritmo de Resolução

O resolvedor implementa o clássico **método de camadas (Layer-by-Layer)**, resolvendo o cubo em 7 etapas sequenciais, da camada branca até as arestas amarelas.

---

## 📄 Formato dos Arquivos de Cubo

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

---

## 👨‍💻 Autor

Desenvolvido como projeto acadêmico em linguagem C.
