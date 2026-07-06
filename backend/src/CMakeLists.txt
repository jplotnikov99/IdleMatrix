qt6_wrap_cpp(MOC_FILES 
    ../include/gamestate.hpp
)

add_library(backend
    gamestate.cpp
    ${MOC_FILES}
)

target_include_directories(backend PUBLIC 
    ${backend_include_dir} 
)


target_link_libraries(backend PRIVATE Qt6::Core Qt6::Widgets)