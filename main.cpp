#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "tar_utility.hpp"

[[maybe_unused]] const auto showContainer = [](const auto container,
                                               const std::string &sep) {
  std::for_each(container.begin(), container.end(),
                [&sep](const auto &element) { std::cout << element << sep; });
  std::cout << std::endl;
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "No filename given" << std::endl;
    return -1;
  }

  const std::filesystem::path file_name{argv[1]};
  std::ifstream fs(file_name.string(), std::ios::binary);
  std::vector<uint8_t> cont;
  const size_t tar_size = std::filesystem::file_size(file_name);
  cont.resize(tar_size);
  fs.read(reinterpret_cast<char *>(cont.data()), tar_size);
  fs.close();

  size_t offset = 0;
  constexpr size_t block_size = 512;

  while (std::any_of(std::next(cont.cbegin(), offset),
                     std::next(cont.cbegin(), offset + 2 * block_size),
                     [](const uint8_t c) { return c != 0; })) {
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
