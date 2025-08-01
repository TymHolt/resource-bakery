cfiles = src/main.c src/bake_context.c src/format/cpp/format_cpp_text.c src/format/java/format_java_text.c src/format/java/format_java_raw.c

bake: $(cfiles)
	gcc -Isrc $(cfiles) -o bake -mtune=generic -march=x86-64

clean:
	rm bake