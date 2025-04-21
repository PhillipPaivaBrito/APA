# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -O3

# Nome do executável
TARGET = projeto_apa

# Arquivos fonte
SRCS = projeto.cpp

# Arquivos objeto (gerados automaticamente)
OBJS = $(SRCS:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra de ligação
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra de compilação
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET) *.o

# Regra para executar o programa com a instância de teste
run: $(TARGET)
	./$(TARGET) teste.txt

# Regra para executar e gerar saída em arquivo
run-output: $(TARGET)
	./$(TARGET) teste.txt > saida.txt

run-n3m10A:
	./$(TARGET) n3m10A.txt

run-output: $(TARGET)
	./$(TARGET) n3m10A.txt > n3m10A.txt

run-n3m10B:
	./$(TARGET) n3m10B.txt

run-output: $(TARGET)
	./$(TARGET) n3m10B.txt > n3m10B.txt

run-n3m10C:
	./$(TARGET) n3m10C.txt

run-output: $(TARGET)
	./$(TARGET) n3m10C.txt > n3m10C.txt

run-n3m10D:
	./$(TARGET) n3m10D.txt

run-output: $(TARGET)
	./$(TARGET) n3m10D.txt > n3m10D.txt

run-n3m10E:
	./$(TARGET) n3m10E.txt

run-output: $(TARGET)
	./$(TARGET) n3m10E.txt > n3m10E.txt

run_n3m20A:
	./$(TARGET) n3m20A.txt

run-output: $(TARGET)
	./$(TARGET) n3m20A.txt > n3m20A.txt

run_n3m20B:
	./$(TARGET) n3m20B.txt

run-output: $(TARGET)
	./$(TARGET) n3m20B.txt > n3m20B.txt

run_n3m20C:
	./$(TARGET) n3m20C.txt

run-output: $(TARGET)
	./$(TARGET) n3m20C.txt > n3m20C.txt

run_n3m20D:
	./$(TARGET) n3m20D.txt

run-output: $(TARGET)
	./$(TARGET) n3m20D.txt > n3m20D.txt

run_n3m20E:
	./$(TARGET) n3m20E.txt

run-output: $(TARGET)
	./$(TARGET) n3m20E.txt > n3m20E.txt

run_n3m40A:
	./$(TARGET) n3m40A.txt

run-output: $(TARGET)
	./$(TARGET) n3m40A.txt > n3m40A.txt

run_n3m40B:
	./$(TARGET) n3m40B.txt

run-output: $(TARGET)
	./$(TARGET) n3m40B.txt > n3m40B.txt

run_n3m40C:
	./$(TARGET) n3m40C.txt

run-output: $(TARGET)
	./$(TARGET) n3m40C.txt > n3m40C.txt

run_n3m40D:
	./$(TARGET) n3m40D.txt

run-output: $(TARGET)
	./$(TARGET) n3m40D.txt > n3m40D.txt

run_n3m40E:
	./$(TARGET) n3m40E.txt

run-output: $(TARGET)
	./$(TARGET) n3m40E.txt > n3m40E.txt

run_n3m50A:	
	./$(TARGET) n5m50A.txt

run-output: $(TARGET)
	./$(TARGET) n5m50A.txt > n3m50A.txt

run_n3m50B:
	./$(TARGET) n5m50B.txt

run-output: $(TARGET)
	./$(TARGET) n5m50B.txt > n3m50B.txt

run_n3m50C:
	./$(TARGET) n5m50C.txt

run-output: $(TARGET)
	./$(TARGET) n5m50C.txt > n3m50C.txt

run_n3m50D:
	./$(TARGET) n5m50D.txt

run-output: $(TARGET)	
	./$(TARGET) n5m50D.txt > n3m50D.txt
	
run_n3m50E:
	./$(TARGET) n5m50E.txt

run-output: $(TARGET)
	./$(TARGET) n5m50E.txt > n3m50E.txt

# Regra para debug (compila com símbolos de debug)
debug: CXXFLAGS += -g
debug: clean $(TARGET)

.PHONY: all clean run run-output debug