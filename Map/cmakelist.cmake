MESSAGE( STATUS "Adding Map Sources")

set(SOURCE_FILES ${SOURCE_FILES}
	Map/src/Tile.cpp
	Map/src/TileBank.cpp
	Map/src/Map.cpp
	Map/src/HexGrid.cpp
)

include_directories( Map/inc )
