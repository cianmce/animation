# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin

# Include any dependencies generated for this target.
include CMakeFiles/tutorial08_basic_shading.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tutorial08_basic_shading.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tutorial08_basic_shading.dir/flags.make

CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o: CMakeFiles/tutorial08_basic_shading.dir/flags.make
CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o: ../tutorial08_basic_shading/tutorial08.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o -c /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial08_basic_shading/tutorial08.cpp

CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial08_basic_shading/tutorial08.cpp > CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.i

CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial08_basic_shading/tutorial08.cpp -o CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.s

CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.requires:
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.requires

CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.provides: CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial08_basic_shading.dir/build.make CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.provides

CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.provides.build: CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o

CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o: CMakeFiles/tutorial08_basic_shading.dir/flags.make
CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o: ../common/shader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o -c /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/shader.cpp

CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/shader.cpp > CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.i

CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/shader.cpp -o CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.s

CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.requires:
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.requires

CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.provides: CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial08_basic_shading.dir/build.make CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.provides

CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.provides.build: CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o

CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o: CMakeFiles/tutorial08_basic_shading.dir/flags.make
CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o: ../common/controls.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o -c /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/controls.cpp

CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/controls.cpp > CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.i

CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/controls.cpp -o CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.s

CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.requires:
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.requires

CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.provides: CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial08_basic_shading.dir/build.make CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.provides

CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.provides.build: CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o

CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o: CMakeFiles/tutorial08_basic_shading.dir/flags.make
CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o: ../common/texture.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o -c /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/texture.cpp

CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/texture.cpp > CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.i

CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/texture.cpp -o CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.s

CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.requires:
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.requires

CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.provides: CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial08_basic_shading.dir/build.make CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.provides

CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.provides.build: CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o

CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o: CMakeFiles/tutorial08_basic_shading.dir/flags.make
CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o: ../common/objloader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o -c /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/objloader.cpp

CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/objloader.cpp > CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.i

CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/common/objloader.cpp -o CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.s

CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.requires:
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.requires

CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.provides: CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial08_basic_shading.dir/build.make CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.provides

CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.provides.build: CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o

# Object files for target tutorial08_basic_shading
tutorial08_basic_shading_OBJECTS = \
"CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o" \
"CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o" \
"CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o" \
"CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o" \
"CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o"

# External object files for target tutorial08_basic_shading
tutorial08_basic_shading_EXTERNAL_OBJECTS =

tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o
tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o
tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o
tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o
tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o
tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/build.make
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libGLU.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libGL.so
tutorial08_basic_shading: external/glfw-3.1.2/src/libglfw3.a
tutorial08_basic_shading: external/libGLEW_1130.a
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libGLU.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/librt.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libm.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libX11.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXrandr.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXinerama.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXi.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXcursor.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/librt.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libm.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libX11.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXrandr.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXinerama.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXi.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libXcursor.so
tutorial08_basic_shading: /usr/lib/x86_64-linux-gnu/libGL.so
tutorial08_basic_shading: CMakeFiles/tutorial08_basic_shading.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tutorial08_basic_shading"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorial08_basic_shading.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/./tutorial08_basic_shading /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial08_basic_shading/

# Rule to build all files generated by this target.
CMakeFiles/tutorial08_basic_shading.dir/build: tutorial08_basic_shading
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/build

CMakeFiles/tutorial08_basic_shading.dir/requires: CMakeFiles/tutorial08_basic_shading.dir/tutorial08_basic_shading/tutorial08.cpp.o.requires
CMakeFiles/tutorial08_basic_shading.dir/requires: CMakeFiles/tutorial08_basic_shading.dir/common/shader.cpp.o.requires
CMakeFiles/tutorial08_basic_shading.dir/requires: CMakeFiles/tutorial08_basic_shading.dir/common/controls.cpp.o.requires
CMakeFiles/tutorial08_basic_shading.dir/requires: CMakeFiles/tutorial08_basic_shading.dir/common/texture.cpp.o.requires
CMakeFiles/tutorial08_basic_shading.dir/requires: CMakeFiles/tutorial08_basic_shading.dir/common/objloader.cpp.o.requires
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/requires

CMakeFiles/tutorial08_basic_shading.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tutorial08_basic_shading.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/clean

CMakeFiles/tutorial08_basic_shading.dir/depend:
	cd /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33 /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33 /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/CMakeFiles/tutorial08_basic_shading.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tutorial08_basic_shading.dir/depend

