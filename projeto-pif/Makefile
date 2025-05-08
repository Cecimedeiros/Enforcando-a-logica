# Makefile do projeto Enforcando a Lógica

# Nome do executável
EXEC = Enforcando-a-logica

# Compilador
CC = gcc

# Diretórios e seus respectivos caminhos
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Flags de compilação
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Caminho completo para o executável
TARGET = $(BUILD_DIR)/$(EXEC)

# Regra padrão para promover a criação do arquivo executável
all: $(TARGET)

# Compila e gera o executável
$(TARGET): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Limpeza (caso decida limpar e recompilar, do início)
clean:
	rm -f $(TARGET)
