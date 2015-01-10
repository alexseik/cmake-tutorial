find_package(Boost 1.56.0 COMPONENTS system filesystem regex REQUIRED)

if(${BOOST_REGEX_FOUND})
    message("Estamos en UNIX")
    FOREACH (LIB ${BOOST_INCLUDE_DIRS})
        FIND_LIBRARY(FOUND_LIB ${LIB} PATHS ${SEARCH_PATHS})
        MESSAGE("Lib: ${LIB}")
        MESSAGE("Found Lib: ${FOUND_LIB}")
    ENDFOREACH(LIB)
endif()

MESSAGE("${BOOST_INCLUDE_DIRS}")

include_directories (${BOOST_INCLUDE_DIRS})

add_definitions (-DBOOST_REGEX_DYN_LINK)

add_library (Sqr sqr.cpp sqr.h)
add_library (QueryTranslate queryTranslate.cpp queryTranslate.h)

target_link_libraries(QueryTranslate ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})

