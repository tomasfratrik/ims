# Makefile
CC = g++
CPPLAGS = -std=c++2a
CPPLAGS_DBG = -std=c++2a -DDEBUG -g
LOGIN1=xjesko01
LOGIN2=xfratr01
TASK=07
ZIP_NAME=$(TASK)_$(LOGIN1)_$(LOGIN2).zip


TARGET = main

SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:%.cc=%.o)
DEPS := $(SRCS:%.cc=%.d)

.PHONY: all clean tar todo dbg

all: $(TARGET)

PROGRAM_ARGS = -w 80 -h 80 -s 1 -m 2 -p 3
run: $(TARGET)
	@echo "Running programm"
	@./$(TARGET) $(PROGRAM_ARGS) 
	@echo "Running visualisation"
	@./vis_data.py


$(TARGET): $(OBJS)
	$(CC) $(CPPLAGS) -o $@ $^

dbg: $(OBJS)
	$(CC) $(CPPLAGS_DBG) -o $@ $^

%.o: %.cc
	$(CC) -c $(CPPFLAGS) -MMD -MP $< -o $@

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) $(ZIP_NAME)

tar:
	tar -cvf project.tar $(SRCS) $(DEPS) Makefile

zip: clean
	@echo "Zipping into: $(ZIP_NAME)"
	zip  -r $(ZIP_NAME) --exclude=.vscode/* --exclude=documentation/* --exclude=.gitignore *

todo: # search for TODOs in the code
	grep -n -r -i --color=auto "TODO" src/ 
