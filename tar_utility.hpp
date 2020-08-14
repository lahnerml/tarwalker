#pragma once

#include <tar.h>

struct posix_header { /* byte offset */
public:
  char name[100];     /*   0 */
  char mode[8];       /* 100 */
  char uid[8];        /* 108 */
  char gid[8];        /* 116 */
  char size[12];      /* 124 */
  char mtime[12];     /* 136 */
  char chksum[8];     /* 148 */
  char typeflag;      /* 156 */
  char linkname[100]; /* 157 */
  char magic[6];      /* 257 */
  char version[2];    /* 263 */
  char uname[32];     /* 265 */
  char gname[32];     /* 297 */
  char devmajor[8];   /* 329 */
  char devminor[8];   /* 337 */
  char prefix[155];   /* 345 */
                      /* 500 */
  char pad[12];

  inline friend std::ostream &operator<<(std::ostream &os,
                                         const posix_header &h);
};

struct posix_block {
  unsigned char data[512];
  inline friend std::ostream &operator<<(std::ostream &os,
                                         const posix_block &b);
};

inline std::ostream &operator<<(std::ostream &os, const posix_header &h) {
  os << "name: " << h.name << std::endl
     << "mode: " << h.mode << std::endl
     << "uid: " << h.uid << std::endl
     << "gid: " << h.gid << std::endl
     << "size: ";
  for (int i = 0; i < 12; ++i) {
    os << h.size[i];
  }
  os << std::endl << "mtime: ";
  for (int i = 0; i < 12; ++i) {
    os << h.mtime[i];
  }
  os << std::endl
     << "chksum: " << h.chksum << std::endl
     << "typeflag: " << h.typeflag << std::endl
     << "linkname: " << h.linkname << std::endl
     << "magic: " << h.magic << std::endl
     << "version: ";
  for (int i = 0; i < 2; ++i) {
    os << h.version[i];
  }
  os << std::endl
     << "uname: " << h.uname << std::endl
     << "gname: " << h.gname << std::endl
     << "devmajor: " << h.devmajor << std::endl
     << "devminor: " << h.devminor << std::endl
     << "prefix: " << h.prefix << std::endl;
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const posix_block &b) {
  return os << "data: " << b.data << std::endl;
}


