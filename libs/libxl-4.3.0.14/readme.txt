LibXL is a library for direct reading and writing Excel files.

Package contents:

  doc              C++ documentation
  examples/c       C examples (type 'make' to build them)
  examples/c++     C++ examples (type 'make' to build them)
  examples/cb      Code::Blocks project
  examples/qt      Qt project
  include_c        headers for c
  include_cpp      headers for c++
  lib              32-bit dynamic library
  lib64            64-bit dynamic library
  lib-armhf        ARMv7 hardware floating dynamic library
  php_excel        source code of plug-in for PHP 
  changelog.txt    version history
  license.txt      end-user license agreement
  readme.txt       this file

Usage:

  g++ -I <path_to_headers> -L <path_to_library> -lxl -Wl,-rpath,<path_to_library> <your_cpp_file>

Documentation:

  http://www.libxl.com/doc

Contact:

  support@libxl.com

