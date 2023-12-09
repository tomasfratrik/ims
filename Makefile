
CC = g++
CPPLAGS = -std=c++2a
CPPLAGS_DBG = -std=c++2a -DDEBUG -g

TARGET = main

SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:%.cc=%.o)
DEPS := $(SRCS:%.cc=%.d)

.PHONY: all clean tar todo dbg

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CPPLAGS) -o $@ $^

dbg: $(OBJS)
	$(CC) $(CPPLAGS_DBG) -o $@ $^

%.o: %.cc
	$(CC) -c $(CPPFLAGS) -MMD -MP $< -o $@

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

tar:
	tar -cvf project.tar $(SRCS) $(DEPS) Makefile

todo: # search for TODOs in the code
	grep -n -r -i --color=auto "TODO" src/ 
