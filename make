#!/bin/bash
make_build_punt() {
  echo 'Building interpreter...'
  for file in src/*.c; do
    file=$(basename $file .c)
    echo "-- $file"
    gcc -c src/$file.c -o build/obj/punt/$file.o -D "MODULE_DIR=\"$PREFIX/$MODULE_DIR\"" || return 1
  done
  gcc build/obj/punt/*.o -o build/punt
}

make_build_modules() {
  echo 'Building modules...'
  ls modules | while read mod; do
    echo "-- $mod"
    mkdir -p "build/obj/modules/$mod"
    for file in "modules/$mod/"*.c; do
      file=$(basename "$file" .c)
      echo "  -- $file"
      gcc -c "modules/$mod/$file.c" -o "build/obj/modules/$mod/$file.o"
    done
    gcc "build/obj/modules/$mod/"* -o "build/modules/$mod.so" --shared -fPIC
  done
}

make_clean() {
  find build -type f | while read file; do
    rm $file;
  done
}

make_install() {
  cp build/punt "$DESTDIR/$PREFIX/$BIN_DIR" &&

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

