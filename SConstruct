# SConstruct for FontSystem library

import os

# How do we do this correctly?
font_sys_code = '../FontSystem/Code'
_3dmath_sys_code = '../3DMath/Code'
if 'DESTDIR' in os.environ:
  font_sys_code = '../../fontsystem/install/include'
  _3dmath_sys_code = '../../3dmath/install/include'

obj_env = Environment( parse_flags = '!wx-config --cxxflags' )
obj_env.Append( CCFLAGS = '--std=c++11' )
obj_env.Append( CCFLAGS = '-DLINUX' )
obj_env.Append( CCFLAGS = '-I/usr/include/freetype2' )
obj_env.Append( CCFLAGS = '-I' + font_sys_code )
obj_env.Append( CCFLAGS = '-I' + _3dmath_sys_code )
obj_env.Append( CCFLAGS = '-ggdb' )

cpp_source_list = Glob( 'Code/*.cpp' )
h_source_list = Glob( 'Code/*.h' )
source_list = cpp_source_list + h_source_list

object_list = []
for source_file in cpp_source_list:
  object_file = obj_env.StaticObject( source_file )
  object_list.append( object_file )

prog_env = Environment( PROGNAME = 'TwistyPuzzle', LIBPATH = [ '../3DMath', '../FontSystem' ], parse_flags = '!wx-config --libs core base adv html xml gl' )
prog_env.Append( LIBS = '-lGL' )
prog_env.Append( LIBS = '-lGLU' )
prog_env.Append( LIBS = '-l3DMath' )
prog_env.Append( LIBS = '-lFontSystem' )
prog_env.Append( LIBS = '-lfreetype' )
prog = prog_env.Program( '$PROGNAME', source = object_list )

dest_dir = '/usr'
if 'DESTDIR' in os.environ:
  dest_dir = os.environ[ 'DESTDIR' ]

install_env = Environment(
  BIN = dest_dir + '/bin',
  SHARE = dest_dir + '/share' )

doc_list = Glob( 'Data/Documentation/*' )
font_list = Glob( 'Data/Fonts/*' )

install_env.Install( '$SHARE/TwistyPuzzle/Data/Documentation', doc_list )
install_env.Install( '$SHARE/TwistyPuzzle/Data/Fonts', font_list )
install_env.Install( '$BIN', prog )
install_env.Alias( 'install', [
  '$BIN',
  '$SHARE/TwistyPuzzle/Data/Documentation',
  '$SHARE/TwistyPuzzle/Data/Fonts' ] )
