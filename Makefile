bake: src/main.c src/bake_context.c src/format_cpp.c
	gcc -Isrc src/main.c src/bake_context.c src/format_cpp.c -o bake