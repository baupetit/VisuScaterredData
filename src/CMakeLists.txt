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
  
# Realite Virtuelle
add_executable(visu ${HEADERS} ${SOURCES} )
#lien des bib. sur viewer
#target_link_libraries(../paraglider  TowerEngine  )









