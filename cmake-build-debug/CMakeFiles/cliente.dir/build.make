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
include CMakeFiles/cliente.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cliente.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cliente.dir/flags.make

CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.o: CMakeFiles/cliente.dir/flags.make
CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.o: ../Cliente-Servidor/cliente.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.o -c "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/Cliente-Servidor/cliente.cpp"

CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/Cliente-Servidor/cliente.cpp" > CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.i

CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/Cliente-Servidor/cliente.cpp" -o CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.s

# Object files for target cliente
cliente_OBJECTS = \
"CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.o"

# External object files for target cliente
cliente_EXTERNAL_OBJECTS =

cliente: CMakeFiles/cliente.dir/Cliente-Servidor/cliente.cpp.o
cliente: CMakeFiles/cliente.dir/build.make
cliente: /usr/lib/x86_64-linux-gnu/libsfml-system.so
cliente: /usr/lib/x86_64-linux-gnu/libsfml-window.so
cliente: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
cliente: /usr/lib/x86_64-linux-gnu/libsfml-network.so
cliente: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
cliente: CMakeFiles/cliente.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cliente"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cliente.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cliente.dir/build: cliente

.PHONY : CMakeFiles/cliente.dir/build

CMakeFiles/cliente.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cliente.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cliente.dir/clean

CMakeFiles/cliente.dir/depend:
	cd "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug" "/home/david/Documents/Proyecto 1/Datos-2-Proyecto-1/cmake-build-debug/CMakeFiles/cliente.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cliente.dir/depend
