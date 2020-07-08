file(GLOB_RECURSE SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#file(GLOB_RECURSE HDRFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
#file(GLOB_RECURSE PUBLIC_HDRFILES "${Include_subdir}/*.h" "${Include_subdir}/*.hpp")

add_executable(reprepro "${SRCFILES}")
#add_library(libreprepro SHARED "${SRCFILES}")
target_include_directories(reprepro PUBLIC "${Include_subdir}")


target_link_libraries(reprepro libreprepro_utils)
set_property(TARGET reprepro PROPERTY CXX_STANDARD 20)
harden(reprepro)

if(WITH_LIBLZMA)
	target_link_libraries(reprepro "${LIBLZMA_LIBRARY}")
endif()

if(WITH_BZIP2)
	target_link_libraries(reprepro "${BZIP2_LIBRARY}")
endif()

if(WITH_ZLIB)
	target_link_libraries(reprepro "${ZLIB_LIBRARY}")
endif()

install(TARGETS "reprepro"
	RUNTIME
	COMPONENT "reprepro"
)

#install(TARGETS "reprepro"
#	LIBRARY
#	COMPONENT "lib_reprepro"
#	ARCHIVE
#	COMPONENT "lib_reprepro_dev"
#)

install(DIRECTORY ${Include_subdir}
	DESTINATION
	"${CMAKE_INSTALL_FULL_INCLUDEDIR}"
	COMPONENT "lib_reprepro_dev"
)

set(CPACK_DEBIAN_REPREPRO_PACKAGE_NAME "reprepro")
set(CPACK_RPM_REPREPRO_PACKAGE_NAME "reprepro")
set(CPACK_DEBIAN_REPREPRO_PACKAGE_DEPENDS "")

set(CPACK_DEBIAN_REPREPRO_DEV_PACKAGE_NAME "${CPACK_DEBIAN_REPREPRO_PACKAGE_NAME}-dev")
set(CPACK_RPM_REPREPRO_DEV_PACKAGE_NAME "${CPACK_RPM_REPREPRO_PACKAGE_NAME}-devel")
set(CPACK_DEBIAN_REPREPRO_DEV_PACKAGE_DEPENDS "${CPACK_DEBIAN_REPREPRO_PACKAGE_NAME}")

pass_through_cpack_vars()

# link db and archive libs
