import platform, shutil

e = Environment()

if(platform.system() == "Linux"):
   e.Append( CPPFLAGS = '-Wall -pedantic -pthread -Wno-long-long' )
   e.Append( LINKFLAGS = '-Wall -pthread' )
   e.Append( CPPPATH = ['/usr/include/python3.6'] )
   e.Append( LIBPATH = ['/usr/lib/python3.6'] )
   e.Append( LIBS = [ 'boost_python3' ] )

   target = 'build/text_correction.so'
elif(platform.system() == "Windows"):
   e.Append( CPPFLAGS = ' /EHsc /D "WIN32" /D "_WIN32_WINNT#0x501" /D "_CONSOLE" /W4 /MD' )
   e.Append( CPPPATH = [ 'C:/local/boost_1_60_0', 
			 'C:/Python27/include' ] )
   e.Append( LIBPATH = [ 'C:/local/boost_1_60_0/libs', 
			 'C:/Python27/libs' ] )


   target = 'build/text_correction.pyd'
else:
   print (platform.system() + " not supported")

def build_link_to_lib( target, source, env):
   '''tworzy link (symboliczny) do biblioteki - uzywany w serwerze'''
   shutil.copy( str(source[0]), str(target[0]) )
   return

dll = e.SharedLibrary(source = ["src/text_correction.cpp", 
				"src/english_word_popularity.cpp", 
				"src/word_rating.cpp", 
				"src/dictionary.cpp", 

				"src/algorithms/norvig.cpp",
				"src/algorithms/symspell_adapter.cpp", 
				"src/algorithms/trie.cpp",
				"src/algorithms/trie_algorithm.cpp"], 
				
				
target = 'build/text_correction' )
e.Command(target, dll, build_link_to_lib )




