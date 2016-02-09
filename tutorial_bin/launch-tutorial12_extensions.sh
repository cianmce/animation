#!/bin/sh
bindir=$(pwd)
cd /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial12_extensions/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/tutorial12_extensions 
	else
		"/home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/tutorial12_extensions"  
	fi
else
	"/home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin/tutorial12_extensions"  
fi
