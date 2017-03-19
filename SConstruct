# SConstruct for TwistyPuzzle library

import os

obj_env = Environment( parse_flags = '!wx-config --cxxflags' )
obj_env.Append( CCFLAGS = '--std=c++14' )
obj_env.Append( CCFLAGS = '-DLINUX' )
obj_env.Append( CCFLAGS = '-I/usr/include/freetype2' )
obj_env.Append( CCFLAGS = '-I../FontSystem/Code' )
obj_env.Append( CCFLAGS = '-I../../fontsystem/install/include' )
obj_env.Append( CCFLAGS = '-I../3DMath/Code' )
obj_env.Append( CCFLAGS = '-I../../3dmath/install/include' )
obj_env.Append( CCFLAGS = '-I../rapidjson/include' )
obj_env.Append( CCFLAGS = '-I../../rapidjson/include' )
obj_env.Append( CCFLAGS = '-I../PermutationGroup/Code' )
obj_env.Append( CCFLAGS = '-I../../PermutationGroup/Code' )
#obj_env.Append( CCFLAGS = '-ggdb' )

cpp_source_list = Glob( 'Code/*.cpp' )
h_source_list = Glob( 'Code/*.h' )
source_list = cpp_source_list + h_source_list

object_list = []
for source_file in cpp_source_list:
  object_file = obj_env.StaticObject( source_file )
  object_list.append( object_file )

prog_env = Environment(
  PROGNAME = 'TwistyPuzzle',
  LIBPATH = [
    '../3DMath',
    '../FontSystem',
		'../PermutationGroup',
    '../../3dmath/install/lib',
    '../../fontsystem/install/lib',
		'../../permutationgroup/install/lib'
  ],
  parse_flags = '!wx-config --libs core base adv html xml gl' )
prog_env.Append( LIBS = '-lGL' )
prog_env.Append( LIBS = '-lGLU' )
prog_env.Append( LIBS = '-lGLEW' )
prog_env.Append( LIBS = '-l3DMath' )
prog_env.Append( LIBS = '-lFontSystem' )
prog_env.Append( LIBS = '-lfreetype' )
prog_env.Append( LIBS = '-lPermutationGroup' )
prog = prog_env.Program( '$PROGNAME', source = object_list )

dest_dir = '/usr/local'
if 'DESTDIR' in os.environ:
  dest_dir = os.environ[ 'DESTDIR' ]

install_env = Environment(
  BIN = dest_dir + '/bin',
  SHARE = dest_dir + '/share' )

doc_list = Glob( 'Data/Documentation/*' )
font_list = Glob( 'Data/Fonts/*' )
shader_list = Glob( 'Data/Shaders/*' )
stabchain_list = Glob( 'Data/StabChains/*' )

install_env.Install( '$SHARE/TwistyPuzzle/Data/Documentation', doc_list )
install_env.Install( '$SHARE/TwistyPuzzle/Data/Fonts', font_list )
install_env.Install( '$SHARE/TwistyPuzzle/Data/Shaders', shader_list )
install_env.Install( '$SHARE/TwistyPuzzle/Data/StabChains', stabchain_list )
install_env.Install( '$BIN', prog )
install_env.Alias( 'install', [
  '$BIN',
  '$SHARE/TwistyPuzzle/Data/Documentation',
  '$SHARE/TwistyPuzzle/Data/Fonts',
  '$SHARE/TwistyPuzzle/Data/Shaders',
	'$SHARE/TwistyPuzzle/Data/StabChains' ] )
