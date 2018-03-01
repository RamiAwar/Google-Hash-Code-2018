ifndef TEST
$(error NO TEST WAS SPECIFIED)
endif

CC=g++
INCLUDEDIR=./include
SOURCEDIR=./src
CSVDIR=./csv_files
TESTSDIR=./tests
BINDIR=./bin
CFLAGS=-I$(INCLUDEDIR) -std=c++11

OBJFILES= $(patsubst ($SOURCEDIR)/%.cpp, $(SOURCEDIR)/%.o, $(wildcard $(SOURCEDIR)/*.cpp))
DEPS= $(wildcard $(INCLUDEDIR)/*.h)

$(SOURCEDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINDIR)/$(TEST) : $(OBJFILES) $(TESTSDIR)/$(TEST).cpp
	mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS)

build: $(BINDIR)/$(TEST)

run: build
	$(BINDIR)/$(TEST)
