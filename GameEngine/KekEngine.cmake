# For frameClock includes
include_directories(BEFORE ${MY_SOURCE_DIR}../GameEngine/frameclock/)

# For Collisions
include_directories(BEFORE ${MY_SOURCE_DIR}../GameEngine/collisions/)
set(COLLISIONS_SRC ../GameEngine/collisions/Collision.cpp)

# For Animations
include_directories(BEFORE ${MY_SOURCE_DIR}../GameEngine/animations/)
set(ANIMATIONS_SRC ../GameEngine/animations/AnimatedSprite.cpp ../GameEngine/animations/Animation.cpp)

# For KekEngine
include_directories(BEFORE ${MY_SOURCE_DIR}../GameEngine/KekEngine/includes/)
set(KEKENGINE_SRC ../GameEngine/KekEngine/src/cameraHandler.cpp ../GameEngine/KekEngine/src/graphicHandler.cpp ../GameEngine/KekEngine/src/entity.cpp ../GameEngine/KekEngine/src/livingEntity.cpp ../GameEngine/KekEngine/src/mediaHandler.cpp ../GameEngine/KekEngine/src/player.cpp ../GameEngine/KekEngine/src/tilesetHandler.cpp ../GameEngine/KekEngine/src/movementsCamera.cpp ../GameEngine/KekEngine/src/movementsEntities.cpp ../GameEngine/KekEngine/src/physics.cpp ../GameEngine/KekEngine/src/draw.cpp)
