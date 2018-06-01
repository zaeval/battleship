CC = g++
CFLAGS = -std=c++14
TARGET = battleship
SOURCES = Main.cpp \
		GameManager.cpp \
		CBattleShipApp.cpp \
		CBattleShipMap.cpp \
		InputPane.cpp \
		Pane.cpp \
		StatPane.cpp \
		Player.cpp \
		Ship.cpp \
		Aircraft.cpp \
		BattleShip.cpp \
		Cruiser.cpp \
		Destroyer.cpp
LDFLAGS = -lncursesw

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -rf *.o $(TARGET)
