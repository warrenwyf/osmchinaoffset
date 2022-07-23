#include "coords_handler.hh"
#include "version.hh"

#include <osmium/io/any_input.hpp>
#include <osmium/io/any_output.hpp>
#include <osmium/util/progress_bar.hpp>

#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

void print_usage(const char* prgname) {
  std::cerr << "Usage: " << prgname << " input.osm output.osm.pbf" << std::endl;
}

void print_help() {
  std::cout << "osmchinaoffset [OPTIONS] [IN_FILE [OUT_FILE]]\n\n"
            << "Offset the OSM data coordinates within China to GCJ-02.\n"
            << "If IN_FILE or OUT_FILE is not given, stdin/stdout is assumed.\n"
            << "File format is autodetected from file name suffix.\n"
            << "\nFile format:\n"
            << "  osm        XML encoding\n"
            << "  pbf        Protobuf encoding\n"
            << "  opl        OPL encoding\n"
            << "\nOptions:\n"
            << "  -h, --help           Print help\n"
            << "  -v, --version        Print version\n";
}

void print_version() {
  std::cout << "osmchinaoffset " << version << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    print_usage(argv[0]);
    return 0;
  }

  if (argc > 1 && (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help"))) {
    print_help();
    return 0;
  }

  if (argc > 1 && (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version"))) {
    print_version();
    return 0;
  }

  std::string input_file_name;
  std::string output_file_name;

  for (int i = 1; i < argc; ++i) {
    if (input_file_name.empty()) {
      input_file_name = argv[i];
    } else if (output_file_name.empty()) {
      output_file_name = argv[i];
    } else {
      print_usage(argv[0]);
      return 1;
    }
  }

  const osmium::io::File input_file{input_file_name};
  const osmium::io::File output_file{output_file_name};

  try {
    osmium::io::Reader reader{input_file};
    osmium::ProgressBar progress{reader.file_size(), osmium::isatty(2)};

    osmium::io::Header header = reader.header();
    header.set("generator", "osmchinaoffset");

    osmium::io::Writer writer{output_file, header, osmium::io::overwrite::allow,
                              osmium::io::fsync::yes};

    while (auto buffer = reader.read()) {
      progress.update(reader.offset());

      osmium::memory::Buffer output_buffer{buffer.committed(),
                                           osmium::memory::Buffer::auto_grow::yes};
      CoordsHandler handler{output_buffer};
      osmium::apply(buffer, handler);

      writer(std::move(output_buffer));
    }

    progress.done();
    writer.close();

    reader.close();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}