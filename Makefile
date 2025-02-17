CXX = g++
CXXFLAGS = -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2 -lSDL2_ttf

SRC_DIR = src

SRC_BINARY = 	$(SRC_DIR)/main.cpp \
				$(SRC_DIR)/Logic.cpp \
				$(SRC_DIR)/Game.cpp \
				$(SRC_DIR)/argsManagement.cpp \
				$(SRC_DIR)/Renderable/Renderable.cpp			\
				$(SRC_DIR)/Renderable/ToolsBar.cpp			\
				$(SRC_DIR)/Renderable/Grid.cpp			\
				$(SRC_DIR)/Renderable/Button.cpp \
				$(SRC_DIR)/struct/Case.cpp \
				$(SRC_DIR)/struct/Config.cpp \
				$(SRC_DIR)/struct/ConfigCase.cpp


TARGET = gameOfLife

all: 
	$(CXX) -o $(TARGET) $(SRC_BINARY) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o *.a *.so

fclean: clean
	rm -rf $(BINARY)

re:	fclean all
