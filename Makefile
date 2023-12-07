
CC = g++
CPPLAGS = -std=c++2a

TARGET = main

SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:%.cc=%.o)
DEPS := $(SRCS:%.cc=%.d)

.PHONY: all clean tar todo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CPPLAGS) -o $@ $^

%.o: %.cc
	$(CC) -c $(CPPFLAGS) -MMD -MP $< -o $@

#$(CC) $(CPPFLAGS) -c $< -o $@
-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

tar:
	tar -cvf project.tar $(SRCS) $(DEPS) Makefile

todo: # search for TODOs in the code
	grep -n -r -i --color=auto "TODO" src/ 