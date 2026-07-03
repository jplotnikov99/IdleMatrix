qt6_wrap_cpp(MOC_FILES 
    ../include/main_window.hpp
    ../include/increment_animator.hpp
)

add_library(frontend
    main_window.cpp
    increment_animator.cpp
    ${MOC_FILES}
)

target_include_directories(frontend PUBLIC 
    ${frontend_include_dir} 
)

target_link_libraries(frontend PRIVATE Qt6::Widgets)