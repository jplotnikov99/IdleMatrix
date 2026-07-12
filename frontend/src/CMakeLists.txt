qt6_wrap_cpp(MOC_FILES 
    ../include/main_window.hpp
    ../include/increment_animator.hpp
    ../include/increment_animations.hpp
    ../include/upgradebuttonwidget.hpp
)

qt6_add_resources(RESOURCE_FILES ${CMAKE_SOURCE_DIR}/resources.qrc)

add_library(frontend
    main_window.cpp
    increment_animator.cpp
    increment_animations.cpp
    upgradebuttonwidget.cpp
    ${RESOURCE_FILES}
    ${MOC_FILES}
)

target_include_directories(frontend PUBLIC 
    ${frontend_include_dir} 
)

target_link_libraries(frontend PRIVATE fontmanager backend Qt6::Widgets)