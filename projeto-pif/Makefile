# Nome do executável
EXEC = jogo

# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Flags de compilação
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Arquivos fonte e headers
SRCS = $(wildcard $(SRC_DIR)/*.c)
HDRS = $(wildcard $(INCLUDE_DIR)/*.h)

# Caminho completo para o executável
TARGET = $(BUILD_DIR)/$(EXEC)

# Regra padrão
all: $(TARGET)

# Compilação (inclui headers como dependência)
$(TARGET): $(SRCS) $(HDRS)
	@echo ">>> Recompilando o jogo..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	chmod +x $@

# Limpeza
clean:
	rm -f $(TARGET)
