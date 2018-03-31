CC = g++
CFLAGS = -Wall -std=c++11

# Linux Library Linking
# SFMLINCLUDE = -I/Users/hancock/Downloads/SFML/SFML-2.4.1-osx-clang/include
# SFMLLIB = -L/Users/hancock/Downloads/SFML/SFML-2.4.1-osx-clang/lib -lsfml-graphics -lsfml-window -lsfml-system

# OSX Library Linking
SFMLINCLUDE = -F /Library/Frameworks
SFMLLIB = -framework sfml-window -framework sfml-graphics -framework sfml-system

ODIR = obj
SDIR = src
INC = -Iinc

_OBJS = main.o Game.o ResourceHolder.o SceneNode.o Entity.o Tile.o Map.o Unit.o World.o Command.o CommandQueue.o Player.o HexGrid.o

OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))
# patsubst take _OBJS and appends the ODIR directory to the front of each object file

OUT = Terraformers

all: $(OUT)

debug: CFLAGS += -DDEBUG
debug: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $^ $(SFMLLIB)
# $^ = The names of all prerequisites with spaces between them

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) $(SFMLINCLUDE) -o $@ $< $(CFLAGS)
# $@ = The file name of the target of the rule.
# $< = The name of the first prerequisite

.PHONY : clean
clean:
	rm -f $(ODIR)/*.o $(OUT)
