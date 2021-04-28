PROBLEMS	:= 
EXTRA_SRCS	:=
EXTRA_HDRS	:= graph.hpp

PROB_OBJS	:= $(patsubst %, %.o, $(PROBLEMS)) $(patsubst %.cpp, %.o, $(EXTRA_SRCS))
PROB_SRCS	:= $(patsubst %, %.cpp, $(PROBLEMS)) $(EXTRA_SRCS)
PROB_HDRS	:= $(patsubst %, %.hpp, $(PROBLEMS)) $(EXTRA_HDRS)

OUT	:= tugas
OBJS	:= main.o $(PROB_OBJS)
SOURCE	:= main.cpp $(PROB_SRCS)
HEADER	:= $(PROB_HDRS)

OUT_TEST	:= tugas_test
OBJS_TEST	:= main_test.o $(PROB_OBJS)
SOURCE_TEST	:= main_test.cpp $(PROB_SRCS)
HEADER_TEST	:= $(PROB_HDRS)

DEPS	:= $(patsubst %.o, %.d, $(OBJS) $(OBJS_TEST))

CXX	:= g++
FLAGS	:= -g -c -Wall -Wpedantic -Wextra -std=c++14 -MMD $(extra_flags)
LFLAGS	:= -Wall -Wpedantic -Wextra -std=c++14 $(extra_lflags)

ifeq ($(OS),Windows_NT)
	FLAGS += -Wa,-mbig-obj
	OUT := $(OUT).exe
	OUT_TEST := $(OUT_TEST).exe
endif

ifeq (,$(findstring /bin/,$(SHELL)))
	CLEAN_CMD := cmd /c del /q *.o *.d *.exe 2>nul
else
	CLEAN_CMD := rm -f *.o *.d $(OUT) $(OUT_TEST)
endif

all: $(OUT) $(OUT_TEST)

$(OUT): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $(OUT)

$(OUT_TEST): $(OBJS_TEST)
	$(CXX) $(LFLAGS) $(OBJS_TEST) -o $(OUT_TEST)

%.o: %.cpp
	$(CXX) $(FLAGS) $< -o $@

run: $(OUT)
	./$(OUT)

test: $(OUT_TEST)
	./$(OUT_TEST) $(spec)

clean:
	$(CLEAN_CMD)

.DELETE_ON_ERROR:
.PHONY: all run test clean

-include $(DEPS)