# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\86176\Downloads\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\86176\Downloads\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\c++\test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\c++\test\build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/async.cc.obj: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/async.cc.obj: CMakeFiles/test.dir/includes_CXX.rsp
CMakeFiles/test.dir/async.cc.obj: D:/c++/test/async.cc
CMakeFiles/test.dir/async.cc.obj: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\c++\test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/async.cc.obj"
	C:\Users\86176\Downloads\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/async.cc.obj -MF CMakeFiles\test.dir\async.cc.obj.d -o CMakeFiles\test.dir\async.cc.obj -c D:\c++\test\async.cc

CMakeFiles/test.dir/async.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test.dir/async.cc.i"
	C:\Users\86176\Downloads\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\c++\test\async.cc > CMakeFiles\test.dir\async.cc.i

CMakeFiles/test.dir/async.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test.dir/async.cc.s"
	C:\Users\86176\Downloads\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\c++\test\async.cc -o CMakeFiles\test.dir\async.cc.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/async.cc.obj"

# External object files for target test
test_EXTERNAL_OBJECTS =

test.exe: CMakeFiles/test.dir/async.cc.obj
test.exe: CMakeFiles/test.dir/build.make
test.exe: CMakeFiles/test.dir/linkLibs.rsp
test.exe: CMakeFiles/test.dir/objects1.rsp
test.exe: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\c++\test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test.exe
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\c++\test D:\c++\test D:\c++\test\build D:\c++\test\build D:\c++\test\build\CMakeFiles\test.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test.dir/depend

