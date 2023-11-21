# PYTHON = python
# TARGET = 40193909_detector
# FILE1 =
# FILE2 = 

# all: $(TARGET)

# $(TARGET):
# 	$(PYTHON) $(TARGET).py $(FILE1) $(FILE2)
	
# run: $(TARGET)

# clean: 
# 	rm -rf "__pycache__"

CXX = g++
CXXFLAGS = -std=c++11
TARGET = detector
FILE1 =
FILE2 =

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

run: $(TARGET)
	./$(TARGET) $(FILE1) $(FILE2)
	
testPlagiarism: 
	@echo "Testing plagiarism test cases in ../data/plagiarismXX"
	@for file in ../data/plagiarism*; do echo "Testing $$file"; $(PYTHON) $(TARGET).py $$file/1.txt $$file/2.txt;done

testNonPlagiarism: 
	@echo "Testing non-plagiarism test cases in ../data/okayXX"
	@for file in ../data/okay*; do echo "Testing $$file"; $(PYTHON) $(TARGET).py $$file/1.txt $$file/2.txt;done

test: testPlagiarism testNonPlagiarism


