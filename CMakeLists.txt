CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FILE(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
IF(NOT EXISTS "${d}")
    MESSAGE(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
ENDIF(NOT EXISTS "${d}")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
FIND_PACKAGE(Imagine)

<<<<<<< HEAD
ImagineAddExecutable(Projet main.cpp Obstacle.cpp Piaf.cpp Fonctions.cpp Bouton.cpp Classes.h Fonctions.h)
=======
ImagineAddExecutable(Projet main.cpp Obstacle.cpp Piaf.cpp Fonctions.cpp Bouton.cpp Piece.cpp Classes.h Fonctions.h)
>>>>>>> FETCH_HEAD
ImagineUseModules(Projet Images)
