MESSAGE( STATUS "Adding Animated Sprite Sources")

set(SOURCE_FILES ${SOURCE_FILES}
	AnimatedSprite/src/AnimatedSprite.cpp
	AnimatedSprite/src/Animation.cpp
)

include_directories( AnimatedSprite/inc )
