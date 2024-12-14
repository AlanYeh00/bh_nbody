CC = /home/hpc/software/intel/oneapi/compiler/2022.1.0/linux/bin/intel64/icpc
CFLAGS = -qopenmp -O3 -std=c++14 -I.
SRCS = BarnesHut.cpp Node.cpp OctTree.cpp Body.cpp Timer.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = BarnesHut


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -ldl


%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
