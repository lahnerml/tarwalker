#include <filesystem>
#include <fstream>
#include <iostream>

#include "tar_utility.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "No filename given" << std::endl;
    return -1;
  }

  const std::filesystem::path file_name{argv[1]};
  std::ifstream fs(file_name.string(), std::ios::binary);
  std::string cont;
  const size_t tar_size = std::filesystem::file_size(file_name);
  cont.resize(tar_size);
  fs.read(&cont.front(), tar_size);
  fs.close();

  size_t offset = 0;
  constexpr size_t block_size = 512;
  const std::string end_sequence (2 * block_size, 0);

  while (cont.compare(offset, end_sequence.size(), end_sequence)) {
    posix_header header;
    posix_block block;
    std::memcpy(&header, cont.data() + offset, block_size);
    offset += block_size;

    size_t file_size = std::strtol(header.size, nullptr, 10);
    const size_t n_blocks = 1 + file_size / block_size;

    std::cout << header << std::endl;

    for (size_t i = 0; i < n_blocks; ++i) {
      std::memcpy(&block, cont.data() + offset, block_size);
      offset += block_size;
      std::cout << block << std::endl;
    }
  }

  return 0;
}
