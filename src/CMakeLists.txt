find_package(Boost 1.56.0 COMPONENTS system filesystem regex REQUIRED)

if(${Boost_FOUND})
    message("Boost encontrado! - ${Boost_INCLUDE_DIRS}")
endif()

OPTION(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
	SET (LIB_TYPE SHARED)
	ADD_DEFINITIONS(-DQueryTranslate_SHARED)
ENDIF (BUILD_SHARED_LIBS)

#MESSAGE("${BOOST_INCLUDE_DIRS}")

include_directories (${Boost_INCLUDE_DIRS})
#link_directories(${BOOST_INCLUDE_DIRS})
include (GenerateExportHeader)

#add_definitions (-DBOOST_REGEX_DYN_LINK)

add_library (Sqr sqr.cpp sqr.h)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library (QueryTranslate ${LIB_TYPE} queryTranslate.cpp queryTranslate.h token.h tokenType.h etx2Sql.cpp etx2Sql.h)

GENERATE_EXPORT_HEADER( QueryTranslate )

target_link_libraries(QueryTranslate ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})


