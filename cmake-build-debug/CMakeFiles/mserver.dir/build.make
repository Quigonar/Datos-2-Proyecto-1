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
CMAKE_SOURCE_DIR = /home/marcos/Documents/GitHub/Datos-2-Proyecto-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mserver.dir/flags.make

CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.o: CMakeFiles/mserver.dir/flags.make
CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.o: ../Cliente-Servidor/servidor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.o -c /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/Cliente-Servidor/servidor.cpp

CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/Cliente-Servidor/servidor.cpp > CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.i

CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/Cliente-Servidor/servidor.cpp -o CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.s

# Object files for target mserver
mserver_OBJECTS = \
"CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.o"

# External object files for target mserver
mserver_EXTERNAL_OBJECTS =

mserver: CMakeFiles/mserver.dir/Cliente-Servidor/servidor.cpp.o
mserver: CMakeFiles/mserver.dir/build.make
mserver: CMakeFiles/mserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mserver.dir/build: mserver

.PHONY : CMakeFiles/mserver.dir/build

CMakeFiles/mserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mserver.dir/clean

CMakeFiles/mserver.dir/depend:
	cd /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/Documents/GitHub/Datos-2-Proyecto-1 /home/marcos/Documents/GitHub/Datos-2-Proyecto-1 /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug /home/marcos/Documents/GitHub/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles/mserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mserver.dir/depend

