file(GLOB_RECURSE SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDRFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE PUBLIC_HDRFILES "${Include_subdir}/*.h" "${Include_subdir}/*.hpp")

add_executable(changestool "${SRCFILES}")
#add_library(changestool SHARED "${SRCFILES}")
target_include_directories(changestool PUBLIC "${Include_subdir}")
target_link_libraries(changestool libreprepro_utils)
set_property(TARGET changestool PROPERTY CXX_STANDARD 20)
harden(changestool)

install(TARGETS "changestool"
	RUNTIME
	COMPONENT "changestool"
)

#install(TARGETS "libchangestool"
#	LIBRARY
#	COMPONENT "lib_changestool"
#	ARCHIVE
#	COMPONENT "lib_changestool_dev"
#)

install(DIRECTORY ${Include_subdir}
	DESTINATION
	"${CMAKE_INSTALL_FULL_INCLUDEDIR}"
	COMPONENT "lib_changestool_dev"
)

set(CPACK_DEBIAN_CHANGESTOOL_PACKAGE_NAME "libchangestool")
set(CPACK_RPM_CHANGESTOOL_PACKAGE_NAME "libchangestool")
set(CPACK_DEBIAN_CHANGESTOOL_PACKAGE_DEPENDS "")

set(CPACK_DEBIAN_CHANGESTOOL_DEV_PACKAGE_NAME "${CPACK_DEBIAN_CHANGESTOOL_PACKAGE_NAME}-dev")
set(CPACK_RPM_CHANGESTOOL_DEV_PACKAGE_NAME "${CPACK_RPM_CHANGESTOOL_PACKAGE_NAME}-devel")
set(CPACK_DEBIAN_CHANGESTOOL_DEV_PACKAGE_DEPENDS "${CPACK_DEBIAN_CHANGESTOOL_PACKAGE_NAME}")

pass_through_cpack_vars()


#link only archives libs