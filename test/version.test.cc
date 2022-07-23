#include "version.hh"

#include <gtest/gtest.h>

TEST(version, version_nums) {
  ASSERT_GE(version_major, 0);
  ASSERT_GE(version_minor, 0);
  ASSERT_GE(version_patch, 0);
}

TEST(version, version_string) {
  std::cout << "[**********] version = " << version << std::endl;
  std::ostringstream buffer;
  buffer << version_major << "." << version_minor << "." << version_patch;
  ASSERT_EQ(version, buffer.str());
}