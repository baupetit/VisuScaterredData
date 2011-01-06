cmake_minimum_required(VERSION 2.6)

# Nom du projet
project(VisualisationScientifique)

SET(HEADERS
  type.h
  matrix.h
  output.h
  interpolate.h
  data.h
  )

SET(SOURCES
  main.c
  matrix.c
  output.c
  interpolate.c
  data.c
  )

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Math library
if(UNIX)
  link_libraries(m)
endif(UNIX)

add_executable(visu ${HEADERS} ${SOURCES} )

#lien des bib. sur viewer
#target_link_libraries(../paraglider  TowerEngine  )









