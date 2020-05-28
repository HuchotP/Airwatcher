# CFLAGS = -O3  (for best performance)
# CFLAGS = -g   (for debugging)
CFLAGS = -g -Wall

LIBS = -lm

DEP = ./src/Agence.cpp ./src/Capteur.cpp ./src/Cleaner.cpp ./src/Entreprise.cpp ./src/logReader.cpp ./src/measurementsReader.cpp ./src/Mesure.cpp ./src/Utilisateur.cpp ./src/UtilisateurPrive.cpp ./src/main.cpp
all: Airwatcher

Airwatcher: $(DEP)
	g++ $(CFLAGS) $^ -o ./bin/$@ $(LIBS)

clean:
	rm -f bin/*

.PHONY: all clean


