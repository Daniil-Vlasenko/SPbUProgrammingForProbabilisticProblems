# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build

# Include any dependencies generated for this target.
include CMakeFiles/terminalApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/terminalApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/terminalApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/terminalApp.dir/flags.make

CMakeFiles/terminalApp.dir/main.cpp.o: CMakeFiles/terminalApp.dir/flags.make
CMakeFiles/terminalApp.dir/main.cpp.o: ../main.cpp
CMakeFiles/terminalApp.dir/main.cpp.o: CMakeFiles/terminalApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/terminalApp.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/terminalApp.dir/main.cpp.o -MF CMakeFiles/terminalApp.dir/main.cpp.o.d -o CMakeFiles/terminalApp.dir/main.cpp.o -c /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/main.cpp

CMakeFiles/terminalApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/terminalApp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/main.cpp > CMakeFiles/terminalApp.dir/main.cpp.i

CMakeFiles/terminalApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/terminalApp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/main.cpp -o CMakeFiles/terminalApp.dir/main.cpp.s

CMakeFiles/terminalApp.dir/mathLibrary.cpp.o: CMakeFiles/terminalApp.dir/flags.make
CMakeFiles/terminalApp.dir/mathLibrary.cpp.o: ../mathLibrary.cpp
CMakeFiles/terminalApp.dir/mathLibrary.cpp.o: CMakeFiles/terminalApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/terminalApp.dir/mathLibrary.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/terminalApp.dir/mathLibrary.cpp.o -MF CMakeFiles/terminalApp.dir/mathLibrary.cpp.o.d -o CMakeFiles/terminalApp.dir/mathLibrary.cpp.o -c /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/mathLibrary.cpp

CMakeFiles/terminalApp.dir/mathLibrary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/terminalApp.dir/mathLibrary.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/mathLibrary.cpp > CMakeFiles/terminalApp.dir/mathLibrary.cpp.i

CMakeFiles/terminalApp.dir/mathLibrary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/terminalApp.dir/mathLibrary.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/mathLibrary.cpp -o CMakeFiles/terminalApp.dir/mathLibrary.cpp.s

# Object files for target terminalApp
terminalApp_OBJECTS = \
"CMakeFiles/terminalApp.dir/main.cpp.o" \
"CMakeFiles/terminalApp.dir/mathLibrary.cpp.o"

# External object files for target terminalApp
terminalApp_EXTERNAL_OBJECTS =

terminalApp: CMakeFiles/terminalApp.dir/main.cpp.o
terminalApp: CMakeFiles/terminalApp.dir/mathLibrary.cpp.o
terminalApp: CMakeFiles/terminalApp.dir/build.make
terminalApp: CMakeFiles/terminalApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable terminalApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/terminalApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/terminalApp.dir/build: terminalApp
.PHONY : CMakeFiles/terminalApp.dir/build

CMakeFiles/terminalApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/terminalApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/terminalApp.dir/clean

CMakeFiles/terminalApp.dir/depend:
	cd /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build /home/daniil/programming/cpp/SPbUProgrammingForProbabilisticProblems/terminalApp/build/CMakeFiles/terminalApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/terminalApp.dir/depend
