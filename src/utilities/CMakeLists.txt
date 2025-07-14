add_library(utilities
        thread.hpp thread.cpp)

target_link_libraries(utilities
        PUBLIC Qt::Core)
