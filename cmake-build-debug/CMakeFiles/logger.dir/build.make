# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/logger.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/logger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/logger.dir/flags.make

CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.o: CMakeFiles/logger.dir/flags.make
CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.o: ../Cliente-Servidor/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.o -c "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/Cliente-Servidor/Logger.cpp"

CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/Cliente-Servidor/Logger.cpp" > CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.i

CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/Cliente-Servidor/Logger.cpp" -o CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.s

# Object files for target logger
logger_OBJECTS = \
"CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.o"

# External object files for target logger
logger_EXTERNAL_OBJECTS =

logger: CMakeFiles/logger.dir/Cliente-Servidor/Logger.cpp.o
logger: CMakeFiles/logger.dir/build.make
logger: CMakeFiles/logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable logger"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/logger.dir/build: logger

.PHONY : CMakeFiles/logger.dir/build

CMakeFiles/logger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/logger.dir/clean

CMakeFiles/logger.dir/depend:
	cd "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles/logger.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/logger.dir/depend

