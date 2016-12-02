
.PHONY	: clean all

TARGET:= fake_ut
all : $(TARGET)
	./$(TARGET)

SRC_DIRS:=. sample/

CPPUTEST:=../external/cpputest
CPPUTEST_INCLUDE:=$(CPPUTEST)/include
CPPUTEST_LIB:=$(CPPUTEST)/cpputest_build/lib

C_SRCS:=$(foreach d, $(SRC_DIRS), $(wildcard $d/*.c))
CXX_SRCS:=$(foreach d,$(SRC_DIRS), $(wildcard $d/*.cpp))
C_OBJS:=$(C_SRCS:.c=.o)
CXX_OBJS:=$(CXX_SRCS:.cpp=.o)
FLAGS:=-I$(CPPUTEST_INCLUDE) -I src -I .
LDFLAGS:=-L$(CPPUTEST_LIB) -lCppUTest -lstdc++ -lm

$(TARGET) : $(CXX_OBJS) $(C_OBJS)
	echo $(LDFLAGS)
	gcc -o $@ $^ $(LDFLAGS)

$(C_OBJS) : %.o : %.c
	gcc -c -o $@ $^ $(FLAGS)

$(CXX_OBJS) : %.o : %.cpp
	gcc -c -o $@ $^ $(FLAGS)

clean:
	-rm $(C_OBJS) $(CXX_OBJS) $(TARGET)

