class Osmchinaoffset < Formula
  desc "Offset the OSM data coordinates within China to GCJ-02"
  homepage "https://github.com/warrenwyf/osmchinaoffset"
  url "https://github.com/warrenwyf/osmchinaoffset/archive/v1.0.0.tar.gz"
  sha256 "bbe06b6732e817b0faa001f9978b32b0558cf42588d7d3e4f6f0cf1c05773be9"
  license "GPL-3.0-or-later"

  depends_on "cmake" => :build
  depends_on "googletest" => :build
  depends_on "libosmium" => :build

  uses_from_macos "expat"

  def install
    protozero = Formula["libosmium"].opt_libexec/"include"
    system "cmake", "-S", ".", "-B", "build",
                    "-DPROTOZERO_INCLUDE_DIR=#{protozero}",
                    *std_cmake_args
    system "cmake", "--build", "build"
    system "cmake", "--install", "build"
  end

  test do
    output = shell_output("#{bin}/osmchinaoffset -v")
    assert_match("osmchinaoffset 1.0.0", output)
  end
end
