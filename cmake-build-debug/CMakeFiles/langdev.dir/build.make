# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dreamtowards/CLionProjects/langdev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dreamtowards/CLionProjects/langdev/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/langdev.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/langdev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/langdev.dir/flags.make

CMakeFiles/langdev.dir/src/main.cpp.o: CMakeFiles/langdev.dir/flags.make
CMakeFiles/langdev.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dreamtowards/CLionProjects/langdev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/langdev.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/langdev.dir/src/main.cpp.o -c /Users/dreamtowards/CLionProjects/langdev/src/main.cpp

CMakeFiles/langdev.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/langdev.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dreamtowards/CLionProjects/langdev/src/main.cpp > CMakeFiles/langdev.dir/src/main.cpp.i

CMakeFiles/langdev.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/langdev.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dreamtowards/CLionProjects/langdev/src/main.cpp -o CMakeFiles/langdev.dir/src/main.cpp.s

CMakeFiles/langdev.dir/src/lexer/lexer.cpp.o: CMakeFiles/langdev.dir/flags.make
CMakeFiles/langdev.dir/src/lexer/lexer.cpp.o: ../src/lexer/lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dreamtowards/CLionProjects/langdev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/langdev.dir/src/lexer/lexer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/langdev.dir/src/lexer/lexer.cpp.o -c /Users/dreamtowards/CLionProjects/langdev/src/lexer/lexer.cpp

CMakeFiles/langdev.dir/src/lexer/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/langdev.dir/src/lexer/lexer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dreamtowards/CLionProjects/langdev/src/lexer/lexer.cpp > CMakeFiles/langdev.dir/src/lexer/lexer.cpp.i

CMakeFiles/langdev.dir/src/lexer/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/langdev.dir/src/lexer/lexer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dreamtowards/CLionProjects/langdev/src/lexer/lexer.cpp -o CMakeFiles/langdev.dir/src/lexer/lexer.cpp.s

# Object files for target langdev
langdev_OBJECTS = \
"CMakeFiles/langdev.dir/src/main.cpp.o" \
"CMakeFiles/langdev.dir/src/lexer/lexer.cpp.o"

# External object files for target langdev
langdev_EXTERNAL_OBJECTS =

langdev: CMakeFiles/langdev.dir/src/main.cpp.o
langdev: CMakeFiles/langdev.dir/src/lexer/lexer.cpp.o
langdev: CMakeFiles/langdev.dir/build.make
langdev: CMakeFiles/langdev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dreamtowards/CLionProjects/langdev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable langdev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/langdev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/langdev.dir/build: langdev

.PHONY : CMakeFiles/langdev.dir/build

CMakeFiles/langdev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/langdev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/langdev.dir/clean

CMakeFiles/langdev.dir/depend:
	cd /Users/dreamtowards/CLionProjects/langdev/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dreamtowards/CLionProjects/langdev /Users/dreamtowards/CLionProjects/langdev /Users/dreamtowards/CLionProjects/langdev/cmake-build-debug /Users/dreamtowards/CLionProjects/langdev/cmake-build-debug /Users/dreamtowards/CLionProjects/langdev/cmake-build-debug/CMakeFiles/langdev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/langdev.dir/depend
