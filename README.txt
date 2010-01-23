This software requires:

 - CMake 2.8 - http://www.cmake.org/
 - Boost 1.40 - http://www.boost.org/
      Should work with previous versions, but it wasn't tested
 - GTest Trunk r367 - http://code.google.com/p/googletest/
      I developed cuke4cpp with the 1.4, but trunk comes with a CMake script
 - JsonCpp Trunk r91 - http://jsoncpp.sourceforge.net/
      Partially included in the 3rd_party with a simple CMake script

CMake hints:

 - For GTest, set GTEST_ROOT to the location of the GTest install prefix.
   If the GTest libraries were installed in /usr/local/lib and the includes
   are in /usr/local/include/gtest, then add "-DGTEST_ROOT=/usr/local" to
   the cmake command line.


