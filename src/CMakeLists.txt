find_package(Boost 1.56.0 COMPONENTS system filesystem regex REQUIRED)

if(${Boost_FOUND})
    message("Boost encontrado!")
endif()

#MESSAGE("${BOOST_INCLUDE_DIRS}")

#include_directories (${BOOST_INCLUDE_DIRS})

add_definitions (-DBOOST_REGEX_DYN_LINK)

add_library (Sqr sqr.cpp sqr.h)
add_library (QueryTranslate queryTranslate.cpp queryTranslate.h)

target_link_libraries(QueryTranslate ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})

