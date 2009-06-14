#!/bin/bash
mkbuilddir() {
  mkdir -p build/{,punt,modules,obj/{,punt,modules}}
}

make_build_punt() {
  mkbuilddir
  echo 'Building interpreter...'
  for file in src/*.c; do
    file=$(basename $file .c)
    echo "  $file"
    gcc -c src/$file.c -o build/obj/punt/$file.o \
      -fPIC -Wall \
      -D "MODULE_DIR=\"$PREFIX/$MODULE_DIR\"" \
      || return 1
  done
  gcc build/obj/punt/*.o -o build/punt/punt \
    -fPIC -Wall \
    -l dl
}

make_build_modules() {
  mkbuilddir
  echo 'Building modules...'
  ls -1 modules | while read mod; do
    echo "  $mod"
    mkdir -p "build/obj/modules/$mod"
    for file in "modules/$mod/"*.c; do
      file=$(basename "$file" .c)
      echo "    $file"
      gcc -c "modules/$mod/$file.c" -o "build/obj/modules/$mod/$file.o" \
        -fPIC -Wall \
        -D "MODULE_DIR=\"$PREFIX/$MODULE_DIR\""
    done
    gcc "build/obj/modules/$mod/"* build/obj/punt/*.o -o "build/modules/$mod.so" \
      --shared -fPIC \
      $(test -f "modules/$mod/GCC_OPTS" && cat "modules/$mod/GCC_OPTS")
  done
}

make_clean() {
  rm -r build/*
}

make_install() {
  cp build/punt/punt "$DESTDIR/$PREFIX/$BIN_DIR" &&

  mkdir -p "$DESTDIR/$PREFIX/$MODULE_DIR" &&
  cp build/modules/* "$DESTDIR/$PREFIX/$MODULE_DIR"
}

make_help() {
  echo 'Usage: ./make [punt|modules|install|clean|help|all]'
  echo '  punt:    build interpreter'
  echo '  modules: build modules'
  echo '  install: install interpreter and modules'
  echo '  clean:   remove build (by)products'
  echo '  help:    show this help'
  echo '  all:     (default) build interpreter and modules'
}

source makeconf &&
case "$1" in
  punt)
    make_build_punt
    ;;
  modules)
    make_build_modules
    ;;
  install)
    make_install
    ;;
  clean)
    make_clean
    ;;
  help)
    make_help
    ;;
  all|*)
    make_build_punt &&
    make_build_modules
    ;;
esac

