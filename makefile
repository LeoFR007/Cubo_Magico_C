CC      = gcc
CFLAGS  = -Wall -Wextra -g -I. -Iinclude
LDLIBS  =

# Diretório dos objetos
OBJDIR  = obj

# Executáveis principais (compilados por padrão)
ALVOS = resolvedor embaralhador

# Geradores extras: dependem de funções (cuboResolvido, imprimeCuboTerminal,
# imprimeCuboArquivo) que hoje só existem em embaralhador.c / resolvedor.c.
# Compile com 'make extras' depois de mover essas funções para um .c comum.
EXTRAS = geradorcuboresolvido geradordecubosaleatorios

all: $(OBJDIR) $(ALVOS)

extras: $(OBJDIR) $(EXTRAS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# --- Objetos ---
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Executáveis ---
# resolvedor usa curses (getch) + rotações
resolvedor: $(OBJDIR)/resolvedor.o $(OBJDIR)/rotacoes.o
	$(CC) $^ -o $@ -lncurses

# embaralhador usa as rotações para embaralhar um cubo resolvido
embaralhador: $(OBJDIR)/embaralhador.o $(OBJDIR)/rotacoes.o
	$(CC) $^ -o $@

geradorcuboresolvido: $(OBJDIR)/geradorcuboresolvido.o
	$(CC) $^ -o $@

geradordecubosaleatorios: $(OBJDIR)/geradordecubosaleatorios.o
	$(CC) $^ -o $@

# --- Atalhos de execução ---
run: resolvedor
	./resolvedor

# --- Limpeza ---
clean:
	rm -rf $(OBJDIR) $(ALVOS) $(EXTRAS) cubos_embaralhados

.PHONY: all extras run clean