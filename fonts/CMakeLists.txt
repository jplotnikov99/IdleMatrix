qt6_wrap_cpp(MOC_FILES 
    fontmanager.hpp
)

qt6_add_resources(RESOURCE_FILES ${CMAKE_SOURCE_DIR}/resources.qrc)

add_library(fontmanager
    fontmanager.cpp
    ${RESOURCE_FILES}
    ${MOC_FILES}
)

target_include_directories(fontmanager PUBLIC 
    ${fontmanager_include_dir} 
)

target_link_libraries(fontmanager PRIVATE Qt6::Widgets)