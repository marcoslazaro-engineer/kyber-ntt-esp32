# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/marcos/esp/esp-idf/components/bootloader/subproject"
  "/home/marcos/esp/kyber-ntt/build/bootloader"
  "/home/marcos/esp/kyber-ntt/build/bootloader-prefix"
  "/home/marcos/esp/kyber-ntt/build/bootloader-prefix/tmp"
  "/home/marcos/esp/kyber-ntt/build/bootloader-prefix/src/bootloader-stamp"
  "/home/marcos/esp/kyber-ntt/build/bootloader-prefix/src"
  "/home/marcos/esp/kyber-ntt/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/marcos/esp/kyber-ntt/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/marcos/esp/kyber-ntt/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
