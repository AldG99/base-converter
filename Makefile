# Makefile for Number Base Converter (Console Version)

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
SRCDIR = src
OBJDIR = obj
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/NumberConverter.cpp $(SRCDIR)/BaseValidator.cpp $(SRCDIR)/StepByStepExplainer.cpp $(SRCDIR)/ArithmeticCalculator.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = base_converter

.PHONY: all clean test install

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(OBJDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

test: $(TARGET)
	@echo "Running basic tests..."
	@echo "255" | ./$(TARGET) || echo "Test requires interactive input"

install: $(TARGET)
	@echo "Installing to /usr/local/bin (requires sudo)"
	sudo cp $(TARGET) /usr/local/bin/

help:
	@echo "Available targets:"
	@echo "  all      - Build the console application (default)"
	@echo "  clean    - Remove built files"
	@echo "  test     - Run basic tests"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "For GUI version, use: make -f Makefile.gui"