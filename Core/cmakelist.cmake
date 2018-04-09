MESSAGE( STATUS "Adding Core Sources")

set(SOURCE_FILES ${SOURCE_FILES}
	Core/src/main.cpp
	Core/src/Game.cpp
	Core/src/ResourceHolder.cpp
	Core/src/SceneNode.cpp
	Core/src/Entity.cpp
	Core/src/World.cpp
	Core/src/Component.cpp
	Core/src/System.cpp
)

include_directories( Core/inc )
