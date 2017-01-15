# SConstruct for FontSystem library

obj_env = Environment( parse_flags = '!wx-config --cxxflags' )
obj_env.Append( CCFLAGS = '--std=c++11' )
obj_env.Append( CCFLAGS = '-DLINUX' )
obj_env.Append( CCFLAGS = '-I/usr/include/freetype2' )
obj_env.Append( CCFLAGS = '-I../FontSystem/Code' )
obj_env.Append( CCFLAGS = '-I../3DMath/Code' )

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
prog_env.Program( '$PROGNAME', source = object_list )
