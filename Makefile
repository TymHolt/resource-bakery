main_files = src/main.c src/bake_context.c src/utils.c
cpp_format_files = src/format/cpp/format_cpp_text.c #src/format/cpp/format_cpp_raw.c
java_format_files =  src/format/java/format_java_text.c src/format/java/format_java_raw.c

c_files = $(main_files) $(cpp_format_files) $(java_format_files)

bake: $(c_files)
	gcc -Isrc $(c_files) -o bake -mtune=generic -march=x86-64

clean:
	rm bake