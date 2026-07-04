qt6_wrap_cpp(MOC_FILES 
    ../include/gameloop.hpp
)

add_library(gameLoop
    gameloop.cpp
    ${MOC_FILES}
)

target_include_directories(gameLoop PUBLIC 
    ${gameLoop_include_dir} 
)

target_link_libraries(gameLoop PRIVATE backend Qt6::Widgets)