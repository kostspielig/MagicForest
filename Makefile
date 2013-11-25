# ***************************************************************** #
#                 INFORMÁTICA  GRÁFICA  	                    #       
#                                                                   #
#                                                                   #  
#            	María Carrasco Rodríguez                            #  
# ***************************************************************** #

#
TARGETS= practica1
SRC = src
INCLUDE = src
LIB = lib
BIN = bin
OBJ = obj
SDL_DIR=/usr


# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -fpermissive -Wall -I/usr/include -I.
CXXFLAGS=  -g -fpermissive -Wall -I/usr/include -I$(SDL_DIR)/include/ -I$(INCLUDE) -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS= -L/usr/X11R6/lib -lGLU -lGL -L$(SDL_DIR)/lib -lSDL -lSDL_mixer -lSDL_image
#-lXi
# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : magicforest

# Compilando practica1.cc
$(OBJ)/practica1.o : $(SRC)/practica1.cc 
	$(CXX) -c $(CXXFLAGS) $(SRC)/practica1.cc -o $(OBJ)/practica1.o

# Compilando practica2.cc
$(OBJ)/practica2.o : $(SRC)/practica2.cc 
	$(CC) -c $(CXXFLAGS) $(SRC)/practica2.cc -o $(OBJ)/practica2.o

# Compilando main.cpp
$(OBJ)/main.o : $(SRC)/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

# Compilando system.cpp
$(OBJ)/system.o : $(SRC)/system.cpp 
	$(CXX) -c $(CXXFLAGS) $(SRC)/system.cpp -o $(OBJ)/system.o

# Compilando eventmanager.cpp
$(OBJ)/eventmanager.o : $(SRC)/eventmanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(SRC)/eventmanager.cpp -o $(OBJ)/eventmanager.o


# Compilando cube.cpp
$(OBJ)/cube.o : $(SRC)/cube.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/cube.cpp -o $(OBJ)/cube.o

# Compilando cylinder.cpp
$(OBJ)/cylinder.o : $(SRC)/cylinder.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/cylinder.cpp -o $(OBJ)/cylinder.o

# Compilando sphere.cpp
$(OBJ)/sphere.o : $(SRC)/sphere.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/sphere.cpp -o $(OBJ)/sphere.o

# Compilando hemisphere.cpp
$(OBJ)/hemisphere.o : $(SRC)/hemisphere.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/hemisphere.cpp -o $(OBJ)/hemisphere.o

# Compilando cone.cpp
$(OBJ)/cone.o : $(SRC)/cone.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/cone.cpp -o $(OBJ)/cone.o

# Compilando ground.cpp
$(OBJ)/ground.o : $(SRC)/ground.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ground.cpp -o $(OBJ)/ground.o


# Compilando mesh.cpp
$(OBJ)/mesh.o : $(SRC)/mesh.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/mesh.cpp -o $(OBJ)/mesh.o

# Compilando scenenode.cpp
$(OBJ)/scenenode.o : $(SRC)/scenenode.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/scenenode.cpp -o $(OBJ)/scenenode.o

# Compilando file_ply_stl.cpp
$(OBJ)/file_ply_stl.o : $(SRC)/file_ply_stl.cc
	$(CXX) -c $(CXXFLAGS) $(SRC)/file_ply_stl.cc -o $(OBJ)/file_ply_stl.o

# Compilando plymesh.cpp
$(OBJ)/plymesh.o : $(SRC)/plymesh.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/plymesh.cpp -o $(OBJ)/plymesh.o

# Compilando camera.cpp
$(OBJ)/camera.o : $(SRC)/camera.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/camera.cpp -o $(OBJ)/camera.o

# Compilando mushroom.cpp
$(OBJ)/mushroom.o : $(SRC)/mushroom.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/mushroom.cpp -o $(OBJ)/mushroom.o

# Compilando entity.cpp
$(OBJ)/entity.o : $(SRC)/entity.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/entity.cpp -o $(OBJ)/entity.o

# Compilando entitymanager.cpp
$(OBJ)/entitymanager.o : $(SRC)/entitymanager.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/entitymanager.cpp -o $(OBJ)/entitymanager.o

# Compilando timer.cpp
$(OBJ)/timer.o : $(SRC)/timer.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/timer.cpp -o $(OBJ)/timer.o

# Compilando goblin.cpp
$(OBJ)/goblin.o : $(SRC)/goblin.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/goblin.cpp -o $(OBJ)/goblin.o

# Compilando enemy.cpp
$(OBJ)/enemy.o : $(SRC)/enemy.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/enemy.cpp -o $(OBJ)/enemy.o

# Compilando game.cpp
$(OBJ)/game.o : $(SRC)/game.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/game.cpp -o $(OBJ)/game.o


# Compilando treeent.cpp
$(OBJ)/treeent.o : $(SRC)/treeent.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/treeent.cpp -o $(OBJ)/treeent.o


magicforest: $(BIN)/magicforest
$(BIN)/magicforest : $(OBJ)/main.o $(OBJ)/system.o $(OBJ)/eventmanager.o $(OBJ)/ground.o $(OBJ)/cube.o $(OBJ)/scenenode.o $(OBJ)/cone.o $(OBJ)/cylinder.o $(OBJ)/sphere.o $(OBJ)/hemisphere.o $(OBJ)/mesh.o $(OBJ)/plymesh.o $(OBJ)/file_ply_stl.o $(OBJ)/camera.o $(OBJ)/entity.o $(OBJ)/mushroom.o $(OBJ)/entitymanager.o $(OBJ)/timer.o $(OBJ)/goblin.o $(OBJ)/enemy.o  $(OBJ)/game.o $(OBJ)/treeent.o
	$(CXX) $(OBJ)/main.o $(OBJ)/system.o $(OBJ)/eventmanager.o $(OBJ)/ground.o $(OBJ)/cube.o $(OBJ)/cone.o $(OBJ)/scenenode.o $(OBJ)/cylinder.o $(OBJ)/sphere.o $(OBJ)/hemisphere.o $(OBJ)/mesh.o $(OBJ)/plymesh.o $(OBJ)/file_ply_stl.o $(OBJ)/camera.o $(OBJ)/mushroom.o $(OBJ)/entity.o $(OBJ)/entitymanager.o $(OBJ)/timer.o $(OBJ)/goblin.o $(OBJ)/enemy.o  $(OBJ)/game.o $(OBJ)/treeent.o  $(LDFLAGS) -o $(BIN)/magicforest


practica1 : $(BIN)/practica1
$(BIN)/practica1 : $(OBJ)/practica1.o   
	$(CXX) $(OBJ)/practica1.o $(LDFLAGS) -o $(BIN)/practica1

practica2 : $(BIN)/practica2
$(BIN)/practica2 : $(OBJ)/practica2.o $(OBJ)/cube.o $(OBJ)/scenenode.o $(OBJ)/scenery.o $(OBJ)/cone.o $(OBJ)/cylinder.o $(OBJ)/sphere.o $(OBJ)/mesh.o $(OBJ)/plymesh.o $(OBJ)/file_ply_stl.o $(OBJ)/camera.o
	$(CXX) $(OBJ)/practica2.o $(OBJ)/cube.o  $(OBJ)/cone.o $(OBJ)/scenenode.o $(OBJ)/cylinder.o $(OBJ)/sphere.o $(OBJ)/mesh.o $(OBJ)/plymesh.o $(OBJ)/file_ply_stl.o $(OBJ)/camera.o $(LDFLAGS) -o $(BIN)/practica2


#
#
clean:
	rm -f $(OBJ)/*.o
	rm -f *.o
	rm -f $(TARGETS)
	rm -f $(BIN)/practica2

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *documentacion:
	\doxygen

#
#
documentacion:
	\doxygen

