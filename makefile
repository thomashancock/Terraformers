CC = g++
CFLAGS = -Wall -std=c++11

SFMLINCLUDE = -I/home/thomas/SFML-2.2/include
SFMLLIB = -L/home/thomas/SFML-2.2/lib -lsfml-graphics -lsfml-window -lsfml-system

ODIR = obj
SDIR = src
INC = -Iinc

_OBJS = main.o Game.o ResourceHolder.o SceneNode.o Entity.o Tile.o Map.o Ball.o Paddle.o World.o Command.o CommandQueue.o Player.o

OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))
# patsubst take _OBJS and appends the ODIR directory to the front of each object file

OUT = Terraformers.exe

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