file(GLOB_RECURSE SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDRFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE PUBLIC_HDRFILES "${Include_subdir}/*.h" "${Include_subdir}/*.hpp")

add_executable(rredtool "${SRCFILES}")
#add_library(librredtool SHARED "${SRCFILES}")
target_include_directories(rredtool PUBLIC "${Include_subdir}")
target_link_libraries(rredtool libreprepro_utils)
harden(rredtool)

install(TARGETS "rredtool"
	RUNTIME
	COMPONENT "rredtool"
)
#install(TARGETS "librredtool"
#	LIBRARY
#	COMPONENT "lib_rredtool"
#	ARCHIVE
#	COMPONENT "lib_rredtool_dev"
#)

install(DIRECTORY ${Include_subdir}
	DESTINATION
	"${CMAKE_INSTALL_FULL_INCLUDEDIR}"
	COMPONENT "lib_rredtool_dev"
)

set(CPACK_DEBIAN_RREDTOOL_PACKAGE_NAME "rredtool")
set(CPACK_RPM_RREDTOOL_PACKAGE_NAME "rredtool")
set(CPACK_DEBIAN_RREDTOOL_PACKAGE_DEPENDS "libqt${Qt5Core_VERSION_MAJOR}core${Qt5Core_VERSION_MAJOR}a, libqt${Qt5Widgets_VERSION_MAJOR}widgets${Qt5Widgets_VERSION_MAJOR}")

set(CPACK_DEBIAN_DEV_PACKAGE_NAME "${CPACK_DEBIAN_RREDTOOL_PACKAGE_NAME}-dev")
set(CPACK_RPM_DEV_PACKAGE_NAME "${CPACK_RPM_RREDTOOL_PACKAGE_NAME}-devel")
set(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "${CPACK_DEBIAN_RREDTOOL_PACKAGE_NAME}, qtbase${Qt5Core_VERSION_MAJOR}-dev")

pass_through_cpack_vars()

# link only hash libs
#rredtool_SOURCES = rredtool.c rredpatch.c mprintf.c filecntl.c sha1.c
