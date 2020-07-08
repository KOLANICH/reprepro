file(GLOB_RECURSE SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDRFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE PUBLIC_HDRFILES "${Include_subdir}/*.h" "${Include_subdir}/*.hpp")

message(STATUS "WITH_LIBARCHIVE ${WITH_LIBARCHIVE} ${LibArchive_LIBRARY}")
if(WITH_LIBARCHIVE)
	list(REMOVE_ITEM SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/extractcontrol.c")
else()
	list(REMOVE_ITEM SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/ar.c" "${CMAKE_CURRENT_SOURCE_DIR}/debfile.c" "${CMAKE_CURRENT_SOURCE_DIR}/debfilecontents.c")
endif()

add_library(libreprepro_utils SHARED "${SRCFILES}")

if(WITH_LIBARCHIVE)
	target_link_libraries(libreprepro_utils "${LibArchive_LIBRARY}")
endif()

target_link_libraries(libreprepro_utils "${GPGME_LIBRARIES}")

if(WITH_BERKELEY_DB)
	target_link_libraries(libreprepro_utils "${BerkeleyDB_LIBRARY}")
endif()


target_include_directories(libreprepro_utils PUBLIC "${Include_subdir}")
set_property(TARGET libreprepro_utils PROPERTY CXX_STANDARD 20)
harden(libreprepro_utils)
