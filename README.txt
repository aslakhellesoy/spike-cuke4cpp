This is a spike solution to explore the possibility of writing Cucumber
steps in C++, using GTest (Google C++ Testing Framework) as a backend.

It includes a sample borrowed from Cuke4Nuke that uses the same feature
definitions but tests a C++ implementation.


Required tools and libraries:

 - CMake 2.8 - http://www.cmake.org/
 - Boost 1.40 - http://www.boost.org/
      Should work with some previous versions, but it wasn't tested
 - GTest Trunk r367 - http://code.google.com/p/googletest/
      I developed cuke4cpp with the 1.4, but the trunk comes with a
      convenient CMake script
 - JsonCpp Trunk r91 - http://jsoncpp.sourceforge.net/
      Partially included in the 3rd_party directory, with a simple
      CMake script. There is no need to install this library.


Quick start on Linux (with in-source build):

cmake .
cmake --build .
examples/Calc/CalculatorSteps >/dev/null &
cucumber examples/Calc/CalcFeatures/features


CMake hints:

 - For GTest, set GTEST_ROOT to the location of the GTest install prefix.
   If the GTest libraries were installed in /usr/local/lib and the includes
   are in /usr/local/include/gtest, then add "-DGTEST_ROOT=/usr/local" to
   the cmake command line.

 - For Boost, set BOOST_ROOT to the location of the Boost install prefix
   if CMake has troubles finding it.

