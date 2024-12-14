#Zatím jen pro Linux

CC = gcc # c compiler
#OBJS = graph.o error_messages.o stack.o parser.o operator.o calculator.o ps_maker.o
BIN = graph
CCFLAGS = -Wall -Wextra -pedantic -ansi -g
BUILD_DIR = build

all: clean $(BUILD_DIR) $(BUILD_DIR)/$(BIN) install

$(BUILD_DIR)/$(BIN): $(BUILD_DIR)/graph.o $(BUILD_DIR)/error_messages.o $(BUILD_DIR)/stack.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/operator.o $(BUILD_DIR)/calculator.o $(BUILD_DIR)/ps_maker.o
	$(CC) -o $@ $^ -lm $(CCFLAGS)

$(BUILD_DIR)/graph.o: src/graph.c
	$(CC) -c $(CCFLAGS) -o $@ $<

$(BUILD_DIR)/error_messages.o: src/error_messages.c
	$(CC) -c $(CCFLAGS) -o $@ $<

$(BUILD_DIR)/stack.o: src/stack.c
	$(CC) -c $(CCFLAGS) -o $@ $<

$(BUILD_DIR)/parser.o: src/parser.c
	$(CC) -c $(CCFLAGS) -o $@ $<	

$(BUILD_DIR)/operator.o: src/operator.c
	$(CC) -c $(CCFLAGS) -o $@ $<	

$(BUILD_DIR)/calculator.o: src/calculator.c
	$(CC) -c $(CCFLAGS) -o $@ $<

$(BUILD_DIR)/ps_maker.o: src/ps_maker.c
	$(CC) -c $(CCFLAGS) -o $@ $<	

$(BUILD_DIR):
	mkdir $@		

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(BIN)

# Nutno přidat do all
install: $(BUILD_DIR)/$(BIN)
	cp $(BUILD_DIR)/$(BIN) ./$(BIN)