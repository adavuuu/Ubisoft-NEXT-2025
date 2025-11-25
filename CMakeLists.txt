cmake_minimum_required(VERSION 4.0)

# Set the C++ version to be C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(UbiTorContestAPI)

set(VENDOR_SRC_DIR "${PROJECT_SOURCE_DIR}/src/ContestAPI/vendor")

###############################################################################
# Common Project for Setup
# This project exists to provide common definitions and config for all platforms
# Most notably, this includes platform definitions
###############################################################################

add_library(Common INTERFACE)

set(IS_PLATFORM_WINDOWS 0)
set(IS_PLATFORM_APPLE 0)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
	set(IS_PLATFORM_WINDOWS 1)
endif()

if (CMAKE_SYSTEM_NAME MATCHES Apple)
	set(IS_PLATFORM_APPLE 1)
endif()

target_compile_definitions(Common INTERFACE 
    BUILD_PLATFORM_WINDOWS=${IS_PLATFORM_WINDOWS}
	BUILD_PLATFORM_APPLE=${IS_PLATFORM_APPLE}
	GL_SILENCE_DEPRECATION
)

#homebrew installs to /usr/local on intel macs and /opt/homebrew on apple chip macs
#This sets it up to find SDL3 and link it
if (CMAKE_SYSTEM_NAME MATCHES Apple)
	target_include_directories(Common INTERFACE
		"/usr/local/include"
		"/opt/homebrew/include"
	)
	target_link_directories(Common INTERFACE
		"/usr/local/lib"
		"/opt/homebrew/lib"
	)
endif()

message(STATUS "System Name is ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler Name is ${CMAKE_CXX_COMPILER_ID}")


###############################################################################
#FreeGLUT lib/dll
#On windows, we need to link the freeglut dll 
###############################################################################

set(FREEGLUT_INC_DIR "")

if (CMAKE_SYSTEM_NAME MATCHES Windows)
	set(FREEGLUT_ROOT_DIR "${VENDOR_SRC_DIR}/glut/")

	#Here we declare that this is an imported lib, and configure the .lib and .dll files
	#This allows us to copy the DLL to the build directory
	add_library(FreeGLUT SHARED IMPORTED)
	set_target_properties(FreeGLUT PROPERTIES
		IMPORTED_LOCATION "${FREEGLUT_ROOT_DIR}/bin/x64/freeglut.dll"
		IMPORTED_IMPLIB "${FREEGLUT_ROOT_DIR}/lib/x64/freeglut.lib"
	)
	set(FREEGLUT_LIB_NAME "FreeGLUT")
	set(FREE_GLUT_INC_DIR "${FREEGLUT_ROOT_DIR}/include")
endif()

###############################################################################
#SDL3 lib - need on macos for controller support
###############################################################################

if (CMAKE_SYSTEM_NAME MATCHES Apple)
	find_package(SDL3 REQUIRED)
endif()

###############################################################################
#Contest API library
#This configures the contest api as it's own project
###############################################################################

message(STATUS "Project Source Dir is ${PROJECT_SOURCE_DIR}")
message(STATUS "Vendor Source Dir is ${VENDOR_SRC_DIR}")

file(GLOB CONTEST_API_INC_FILES ${PROJECT_SOURCE_DIR}/src/ContestAPI/*.h)
file(GLOB CONTEST_API_SRC_FILES ${PROJECT_SOURCE_DIR}/src/ContestAPI/*.cpp)
file(GLOB MINIAUDIO_SRC_FILES ${VENDOR_SRC_DIR}/miniaudio/*.cpp)
file(GLOB STB_IMAGE_SRC_FILES ${VENDOR_SRC_DIR}/stb_image/*.cpp)

add_library(ContestAPI 
	${CONTEST_API_INC_FILES} 
	${CONTEST_API_SRC_FILES} 
	${MINIAUDIO_SRC_FILES} 
	${STB_IMAGE_SRC_FILES} 
)

target_include_directories(ContestAPI PUBLIC 
	"${PROJECT_SOURCE_DIR}/src/ContestAPI"
)

target_include_directories(ContestAPI PRIVATE 
	"${FREE_GLUT_INC_DIR}"
	"${VENDOR_SRC_DIR}/miniaudio"
	"${VENDOR_SRC_DIR}/stb_image"
)

target_link_libraries(ContestAPI PUBLIC Common)

# For Apple, we need to specify that we link with GLUT, OpenGL and libC++
# For the different compilers, specifying the c++ lib has different arguments
if (CMAKE_SYSTEM_NAME MATCHES Apple)
	
	target_link_libraries(ContestAPI PUBLIC SDL3)

	target_link_libraries(ContestAPI PUBLIC "-framework GLUT -framework OpenGL")

	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
	 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=stdlibc++")
	else()
		message(FATAL_ERROR "Unhandled Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
	endif()

endif()

# For windows, we can link with the custom freeglut target we defined
if (CMAKE_SYSTEM_NAME MATCHES Windows)
	target_link_directories(ContestAPI PUBLIC "${VENDOR_SRC_DIR}/glut/lib/x64")
	target_link_libraries(ContestAPI PUBLIC FreeGLUT)
endif()

###############################################################################
# Game Project
# This configures the game project, where participants will write their code
###############################################################################

file(GLOB_RECURSE GAME_INC_FILES ${PROJECT_SOURCE_DIR}/src/Game/*.h)
file(GLOB_RECURSE GAME_SRC_FILES ${PROJECT_SOURCE_DIR}/src/Game/*.cpp)

add_executable(Game WIN32
	${GAME_INC_FILES} 
	${GAME_SRC_FILES}
)

target_include_directories(Game PRIVATE 
	"${PROJECT_SOURCE_DIR}/src/Game"
	"${FREE_GLUT_INC_DIR}"
)

# Link our contest API
target_link_libraries(Game PRIVATE Common ContestAPI)

# Add custom command 'run' for makefiles to run the output exe
# This allows us to write 'make run' in the terminal and have it run in the correct directory pointing to data
if (CMAKE_SYSTEM_NAME MATCHES Apple)

	add_custom_target(run 
		DEPENDS Game 
		COMMAND "./build/macos/Game"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	)

endif()

if (CMAKE_SYSTEM_NAME MATCHES Windows)
	#Sets the game to run in the root working directory
	set_target_properties( Game PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	)

	message(STATUS "Project Runtime DLLS: $<TARGET_RUNTIME_DLLS:Game>")

	# Add commands to copy runtime DLLS to output directories, only needed on windows
	if (CMAKE_IMPORT_LIBRARY_SUFFIX)
		add_custom_command(
			TARGET ContestAPI POST_BUILD 
			COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_RUNTIME_DLLS:Game>" "$<TARGET_FILE_DIR:Game>"
			COMMAND_EXPAND_LISTS
		)
	endif()
	
	#Sets the VS startup project to be the Game one. If this is not called then the startup project is ALL_BUILD which results in an error in VS
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)
endif()