
SRCDIR = src
OBJDIR = obj
BINDIR = .

UTILSDIR = src

HEADERDIR = include

HEADERS = $(wildcard $(HEADERDIR)/*.h) \
			$(wildcard $(SRCDIR)/*.h)

CC := g++

EXTRAS := -DDEBUG

CFLAGS  := -std=c++11 -I$(HEADERDIR) -I$(SRCDIR) -Istpl/stpl $(EXTRAS)

LDFLAGS := 

ISRELEASE = 0
ifeq ($(REL), 1)
	ISRELEASE = 1
endif

ifeq ($(RELEASE), 1)
	ISRELEASE = 1
endif

ifeq ($(ISRELEASE), 1)
	CFLAGS += -DRELEASE -O3
else
	CFLAGS += -g 
endif

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)

UTILS := $(wildcard $(UTILSDIR)/*.cpp)

OBJECTS  := $(SOURCES:.cpp=.o)

UTILS_OBJS := $(UTILS:.cpp=.o)

#MAINS := $(UTILS:.cpp=.o)

#main = $(UTILS:.cpp=)
main = wiki2json

executables = $(main) 

all: $(executables)

$(main): $(OBJECTS) $(SRCDIR)/$(main).o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
install: $(executables)
	cp $(executables) /usr/local/bin/	

clean:
	\rm -rf $(OBJECTS) $(UTILS_OBJS) $(executables)

