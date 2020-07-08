cmake_minimum_required(VERSION 3.8)

project("reprepro")

enable_language(CXX)

include(GNUInstallDirs)
include(CPackComponent)
include(CheckIncludeFile)
include(CheckSymbolExists)

set(CMAKE_USE_RELATIVE_PATHS ON)
set(BUILD_SHARED_LIBS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(Hardening)


set(C_STANDARD 11)  # todo: 18, 21 https://gitlab.kitware.com/cmake/cmake/-/issues/17755

# Workaround
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu2x")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options("-fdiagnostics-color=always")
endif()

if(${CMAKE_VERSION} VERSION_GREATER "3.12")
	set(CMAKE_CXX_STANDARD 20)
else()
	if(${CMAKE_VERSION} VERSION_GREATER "3.8")
		set(CMAKE_CXX_STANDARD 17)
	else()
		set(CMAKE_CXX_STANDARD 14)
	endif()
endif()

macro(pass_through_cpack_vars)
	get_cmake_property(cpackVarsToPassthrough VARIABLES)
	foreach(varName ${cpackVarsToPassthrough})
		if(varName MATCHES "^CPACK_")
			set("${varName}" "${${varName}}" PARENT_SCOPE)
		endif()
	endforeach()
endmacro()


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-portability -Wall -g -Wmissing-prototypes -Wstrict-prototypes -Wshadow -Wsign-compare -Wlogical-op")
#AM_CONFIG_HEADER(config.h)


#SPLINT=splint
#SPLITFLAGSFORVIM= -linelen 10000 -locindentspaces 0
#SPLINTFLAGS= +posixlib -booltype bool -numabstractcast -fixedformalarray -enumint +enumindex +charint $(SPLITFLAGSFORVIM) $(EXTRASPLINTFLAGS)

#splint:
#	$(SPLINT) -DSPLINT=1 $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) -D_GNU_SOURCE=1 $(SPLINTFLAGS) $(foreach file,$(reprepro_SOURCES),$(srcdir)/$(file))



set(Example_dir "${CMAKE_CURRENT_SOURCE_DIR}/example")

set(Source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(Include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(Include_subdir "${Include_dir}/reprepro")
set(Docs_dir "${CMAKE_CURRENT_SOURCE_DIR}/docs")
set(Tests_dir "${CMAKE_CURRENT_SOURCE_DIR}/tests")

option(WITH_LIBARCHIVE "use libarchive" ON)
option(WITH_LIBLZMA "use liblzma" ON)
option(WITH_ZLIB "use zlib" ON)
option(WITH_BZIP2 "use bzip2" ON)
option(WITH_BERKELEY_DB "use BerkeleyDB" ON)

find_package(PkgConfig REQUIRED)

if(WITH_BERKELEY_DB)
	find_package(BerkeleyDB)
endif()
if(WITH_ZLIB)
	find_package(ZLIB)
endif()
if(WITH_BZIP2)
	find_package(BZip2)
endif()
if(WITH_LIBLZMA)
	find_package(LibLZMA)
endif()
if(WITH_LIBARCHIVE)
	find_package(LibArchive)
endif()

pkg_check_modules(GPGME REQUIRED gpgme)

CHECK_INCLUDE_FILE("stdbool.h" HAVE_STDBOOL_H)

check_symbol_exists("closefrom" "stdlib.h" "unistd.h" "fcntl.h" HAVE_CLOSEFROM)
check_symbol_exists("dprintf" "stdio.h" HAVE_DPRINTF)
CHECK_INCLUDE_FILE("inttypes.h" HAVE_INTTYPES_H)

check_symbol_exists("mkostemp" "stdlib.h" HAVE_MKOSTEMP)
check_symbol_exists("mkstemp" "stdlib.h" HAVE_MKSTEMP)
check_symbol_exists("strndup" "string.h" HAVE_STRNDUP)
check_symbol_exists("tdestroy" "search.h" HAVE_TDESTROY)
check_symbol_exists("_Bool" "stdbool.h" HAVE__BOOL)

set(HAVE_LIBARCHIVE "${LibArchive_FOUND}")
set(HAVE_LIBBZ2 "${BZIP2_FOUND}")
set(HAVE_LIBGPGME "${GPGME_FOUND}")
set(HAVE_LIBGPG_ERROR "${GPGME_FOUND}") # gpg-error -lgpg-error
set(HAVE_LIBLZMA "${LIBLZMA_FOUND}")
set(HAVE_LIBZ "${ZLIB_FOUND}") #`z' library -lz 


set(CPACK_PACKAGE_CHECKSUM "SHA512")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
option(CPACK_RPM_COMPONENT_INSTALL "Split into multiple rpm packages" ON)
option(CPACK_DEB_COMPONENT_INSTALL "Split into multiple deb packages" ON)
set(CPACK_PACKAGE_VENDOR "reprepro developers")
set(CPACK_PACKAGE_CONTACT "brlink@debian.org")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://salsa.debian.org/brlink/reprepro")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/docs/CPack.Description.txt")

set(CPACK_DEBIAN_PACKAGE_NAME "reprepro")
set(VERSION "5.3.0")


set(PACKAGE "${CPACK_DEBIAN_PACKAGE_NAME}")
set(PACKAGE_BUGREPORT "${CPACK_PACKAGE_CONTACT}")
set(PACKAGE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}")
set(PACKAGE_VERSION "${VERSION}")
set(PACKAGE_STRING "${CPACK_DEBIAN_PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${CPACK_DEBIAN_PACKAGE_NAME}")
set(PACKAGE_URL "${CPACK_PACKAGE_HOMEPAGE_URL}")


configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${Include_subdir}/config.h")

add_subdirectory("${Source_dir}")
#add_subdirectory("${Include_subdir}")
#add_subdirectory("${Docs_dir}")
#add_subdirectory("${Tests_dir}")



set(CPACK_COMPONENTS_GROUPING "IGNORE")
set(CPACK_MONOLITHIC_INSTALL OFF)

include(CPack)
