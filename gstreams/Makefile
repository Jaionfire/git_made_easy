# Compiler
CC = gcc

# Program Name
TARGET = exec

# Source File
SRC = example_live_stream_using_GST.c

# Compiler Flags
CFLAGS = `pkg-config --cflags gstreamer-1.0`
LIBS = `pkg-config --libs gstreamer-1.0`

# Build Target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

# Clean Target
clean:
	rm -f $(TARGET)

