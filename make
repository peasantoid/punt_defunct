#!/bin/bash
mkbuilddir() {
<<<<<<< HEAD:make
  mkdir -p build/{,punt,modules,obj/{,punt,modules}}
=======
  mkdir -p build/{,obj/{,punt,modules},modules}
>>>>>>> 01a37f7f53df68814399a41113694686ae7cb53c:make
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
<<<<<<< HEAD:make
  gcc build/obj/punt/*.o -o build/punt/punt
=======
  gcc build/obj/punt/*.o -o build/punt
>>>>>>> 01a37f7f53df68814399a41113694686ae7cb53c:make
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
<<<<<<< HEAD:make
  cp build/punt/punt "$DESTDIR/$PREFIX/$BIN_DIR" &&
=======
  cp build/punt "$DESTDIR/$PREFIX/$BIN_DIR" &&
>>>>>>> 01a37f7f53df68814399a41113694686ae7cb53c:make

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

