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
      -D "MODULE_DIR=\"$PREFIX/$MODULE_DIR\"" \
      || return 1
  done
  gcc build/obj/punt/*.o -o build/punt/punt \
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
      gcc -c "modules/$mod/$file.c" -o "build/obj/modules/$mod/$file.o" -fPIC \
        -D "MODULE_DIR=\"$PREFIX/$MODULE_DIR\""
    done
    gcc "build/obj/modules/$mod/"* -o "build/modules/$mod.so" --shared
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
  *)
    make_build_punt &&
    make_build_modules
    ;;
esac

