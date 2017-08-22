file(REMOVE_RECURSE
  "libdecrepit.pdb"
  "libdecrepit.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/decrepit.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
