MESSAGE( STATUS "Adding Core Sources")

set(SOURCE_FILES ${SOURCE_FILES}
	Core/src/main.cpp
	Core/src/Game.cpp
	Core/src/ResourceHolder.cpp
	Core/src/SceneNode.cpp
	Core/src/Entity.cpp
	Core/src/Tile.cpp
	Core/src/TileBank.cpp
	Core/src/Map.cpp
	Core/src/Unit.cpp
	Core/src/World.cpp
	Core/src/Command.cpp
	Core/src/CommandQueue.cpp
	Core/src/Player.cpp
	Core/src/HexGrid.cpp
	Core/src/Component.cpp
	Core/src/System.cpp
)

include_directories( Core/inc )
