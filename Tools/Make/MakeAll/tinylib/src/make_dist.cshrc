# tcsh script that
# copies library header files and library files to the include directory

# include directory relative to library's source dir (where this script resides)
set inc_dir = ../include

# show executed commands
set echo

#
# common header files
#
cp always.hpp $inc_dir/.

#
# object related header files
#
cp --parents a/a.hpp $inc_dir
cp --parents b/b.hpp $inc_dir

# --- Do not change below this line --------------------------------------------

#
# library files: debug and release versions
#
mkdir -p $inc_dir/build/debug
mkdir -p $inc_dir/build/release

cp ../build/debug/tinylib.a   $inc_dir/build/debug/.
cp ../build/release/tinylib.a $inc_dir/build/release/.

# unset
unset echo
