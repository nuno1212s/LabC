# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/nuno/Documents/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/nuno/Documents/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nuno/CLionProjects/LabC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nuno/CLionProjects/LabC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LabC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LabC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LabC.dir/flags.make

CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o: ../src/posts/PostManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o -c /home/nuno/CLionProjects/LabC/src/posts/PostManager.cpp

CMakeFiles/LabC.dir/src/posts/PostManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/posts/PostManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/posts/PostManager.cpp > CMakeFiles/LabC.dir/src/posts/PostManager.cpp.i

CMakeFiles/LabC.dir/src/posts/PostManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/posts/PostManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/posts/PostManager.cpp -o CMakeFiles/LabC.dir/src/posts/PostManager.cpp.s

CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.requires

CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.provides: CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.provides

CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.provides.build: CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o


CMakeFiles/LabC.dir/src/posts/Post.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/posts/Post.cpp.o: ../src/posts/Post.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LabC.dir/src/posts/Post.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/posts/Post.cpp.o -c /home/nuno/CLionProjects/LabC/src/posts/Post.cpp

CMakeFiles/LabC.dir/src/posts/Post.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/posts/Post.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/posts/Post.cpp > CMakeFiles/LabC.dir/src/posts/Post.cpp.i

CMakeFiles/LabC.dir/src/posts/Post.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/posts/Post.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/posts/Post.cpp -o CMakeFiles/LabC.dir/src/posts/Post.cpp.s

CMakeFiles/LabC.dir/src/posts/Post.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/posts/Post.cpp.o.requires

CMakeFiles/LabC.dir/src/posts/Post.cpp.o.provides: CMakeFiles/LabC.dir/src/posts/Post.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/posts/Post.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/posts/Post.cpp.o.provides

CMakeFiles/LabC.dir/src/posts/Post.cpp.o.provides.build: CMakeFiles/LabC.dir/src/posts/Post.cpp.o


CMakeFiles/LabC.dir/src/Main.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LabC.dir/src/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/Main.cpp.o -c /home/nuno/CLionProjects/LabC/src/Main.cpp

CMakeFiles/LabC.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/Main.cpp > CMakeFiles/LabC.dir/src/Main.cpp.i

CMakeFiles/LabC.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/Main.cpp -o CMakeFiles/LabC.dir/src/Main.cpp.s

CMakeFiles/LabC.dir/src/Main.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/Main.cpp.o.requires

CMakeFiles/LabC.dir/src/Main.cpp.o.provides: CMakeFiles/LabC.dir/src/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/Main.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/Main.cpp.o.provides

CMakeFiles/LabC.dir/src/Main.cpp.o.provides.build: CMakeFiles/LabC.dir/src/Main.cpp.o


CMakeFiles/LabC.dir/src/users/User.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/users/User.cpp.o: ../src/users/User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LabC.dir/src/users/User.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/users/User.cpp.o -c /home/nuno/CLionProjects/LabC/src/users/User.cpp

CMakeFiles/LabC.dir/src/users/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/users/User.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/users/User.cpp > CMakeFiles/LabC.dir/src/users/User.cpp.i

CMakeFiles/LabC.dir/src/users/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/users/User.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/users/User.cpp -o CMakeFiles/LabC.dir/src/users/User.cpp.s

CMakeFiles/LabC.dir/src/users/User.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/users/User.cpp.o.requires

CMakeFiles/LabC.dir/src/users/User.cpp.o.provides: CMakeFiles/LabC.dir/src/users/User.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/users/User.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/users/User.cpp.o.provides

CMakeFiles/LabC.dir/src/users/User.cpp.o.provides.build: CMakeFiles/LabC.dir/src/users/User.cpp.o


CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o: ../src/rest/RestHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o -c /home/nuno/CLionProjects/LabC/src/rest/RestHandler.cpp

CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/rest/RestHandler.cpp > CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.i

CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/rest/RestHandler.cpp -o CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.s

CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.requires

CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.provides: CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.provides

CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.provides.build: CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o


CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o: ../src/storage/MySQL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o -c /home/nuno/CLionProjects/LabC/src/storage/MySQL.cpp

CMakeFiles/LabC.dir/src/storage/MySQL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/storage/MySQL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/storage/MySQL.cpp > CMakeFiles/LabC.dir/src/storage/MySQL.cpp.i

CMakeFiles/LabC.dir/src/storage/MySQL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/storage/MySQL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/storage/MySQL.cpp -o CMakeFiles/LabC.dir/src/storage/MySQL.cpp.s

CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.requires

CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.provides: CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.provides

CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.provides.build: CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o


CMakeFiles/LabC.dir/src/users/UserManager.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/users/UserManager.cpp.o: ../src/users/UserManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/LabC.dir/src/users/UserManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/users/UserManager.cpp.o -c /home/nuno/CLionProjects/LabC/src/users/UserManager.cpp

CMakeFiles/LabC.dir/src/users/UserManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/users/UserManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/users/UserManager.cpp > CMakeFiles/LabC.dir/src/users/UserManager.cpp.i

CMakeFiles/LabC.dir/src/users/UserManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/users/UserManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/users/UserManager.cpp -o CMakeFiles/LabC.dir/src/users/UserManager.cpp.s

CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.requires

CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.provides: CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.provides

CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.provides.build: CMakeFiles/LabC.dir/src/users/UserManager.cpp.o


CMakeFiles/LabC.dir/src/storage/JSON.cpp.o: CMakeFiles/LabC.dir/flags.make
CMakeFiles/LabC.dir/src/storage/JSON.cpp.o: ../src/storage/JSON.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/LabC.dir/src/storage/JSON.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LabC.dir/src/storage/JSON.cpp.o -c /home/nuno/CLionProjects/LabC/src/storage/JSON.cpp

CMakeFiles/LabC.dir/src/storage/JSON.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabC.dir/src/storage/JSON.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuno/CLionProjects/LabC/src/storage/JSON.cpp > CMakeFiles/LabC.dir/src/storage/JSON.cpp.i

CMakeFiles/LabC.dir/src/storage/JSON.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabC.dir/src/storage/JSON.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuno/CLionProjects/LabC/src/storage/JSON.cpp -o CMakeFiles/LabC.dir/src/storage/JSON.cpp.s

CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.requires:

.PHONY : CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.requires

CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.provides: CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.requires
	$(MAKE) -f CMakeFiles/LabC.dir/build.make CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.provides.build
.PHONY : CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.provides

CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.provides.build: CMakeFiles/LabC.dir/src/storage/JSON.cpp.o


# Object files for target LabC
LabC_OBJECTS = \
"CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o" \
"CMakeFiles/LabC.dir/src/posts/Post.cpp.o" \
"CMakeFiles/LabC.dir/src/Main.cpp.o" \
"CMakeFiles/LabC.dir/src/users/User.cpp.o" \
"CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o" \
"CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o" \
"CMakeFiles/LabC.dir/src/users/UserManager.cpp.o" \
"CMakeFiles/LabC.dir/src/storage/JSON.cpp.o"

# External object files for target LabC
LabC_EXTERNAL_OBJECTS =

LabC: CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o
LabC: CMakeFiles/LabC.dir/src/posts/Post.cpp.o
LabC: CMakeFiles/LabC.dir/src/Main.cpp.o
LabC: CMakeFiles/LabC.dir/src/users/User.cpp.o
LabC: CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o
LabC: CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o
LabC: CMakeFiles/LabC.dir/src/users/UserManager.cpp.o
LabC: CMakeFiles/LabC.dir/src/storage/JSON.cpp.o
LabC: CMakeFiles/LabC.dir/build.make
LabC: CMakeFiles/LabC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable LabC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LabC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LabC.dir/build: LabC

.PHONY : CMakeFiles/LabC.dir/build

CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/posts/PostManager.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/posts/Post.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/Main.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/users/User.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/rest/RestHandler.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/storage/MySQL.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/users/UserManager.cpp.o.requires
CMakeFiles/LabC.dir/requires: CMakeFiles/LabC.dir/src/storage/JSON.cpp.o.requires

.PHONY : CMakeFiles/LabC.dir/requires

CMakeFiles/LabC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LabC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LabC.dir/clean

CMakeFiles/LabC.dir/depend:
	cd /home/nuno/CLionProjects/LabC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nuno/CLionProjects/LabC /home/nuno/CLionProjects/LabC /home/nuno/CLionProjects/LabC/cmake-build-debug /home/nuno/CLionProjects/LabC/cmake-build-debug /home/nuno/CLionProjects/LabC/cmake-build-debug/CMakeFiles/LabC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LabC.dir/depend
