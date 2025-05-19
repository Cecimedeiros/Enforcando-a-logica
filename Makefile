# Makefile do projeto Enforcando a Lógica

# Nome do executável
EXEC = Enforcando-a-logica

# Compilador
CC = gcc

# Diretórios (corrigido para subpasta projeto-pif)
SRC_DIR = projeto-pif/src
BUILD_DIR = projeto-pif/build
INCLUDE_DIR = projeto-pif/include

# Flags de compilação
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Caminho completo para o executável
TARGET = $(BUILD_DIR)/$(EXEC)

# Regra padrão
all: $(TARGET)

# Compilação
$(TARGET): $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Limpeza
clean:
	rm -f $(TARGET)
