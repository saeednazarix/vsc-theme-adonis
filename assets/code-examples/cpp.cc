#include "gcs_fast_transfers.h"
#include <fstream>
#include <limits>
#include <vector>

#ifndef GCS_FAST_TRANSFERS_GCS_FAST_TRANSFERS_H
#define GCS_FAST_TRANSFERS_GCS_FAST_TRANSFERS_H

namespace gcs_fast_transfers {

po::variables_map parse_command_line(int argc, char* argv[]);
int check_system_call(std::string const& name, int result);

std::string format_size(std::int64_t size) {
  struct range_definition {
    std::int64_t max_value;
    std::int64_t scale;
    char const* units;
  } ranges[] = {
      {kKiB, 1, "Bytes"},  {kMiB, kKiB, "KiB"}, {kGiB, kMiB, "MiB"},
      {kTiB, kGiB, "GiB"}, {kPiB, kTiB, "TiB"},
  };
  for (auto d : ranges) {
    if (size < d.max_value) return std::to_string(size / d.scale) + d.units;
  }
  return std::to_string(size / kPiB) + "PiB";
}

std::pair<std::int64_t, std::string> file_info(std::string const& filename) {
  std::ifstream is(filename);
  std::vector<char> buffer(1024 * 1024L);
  std::uint32_t crc32c = 0;
  std::int64_t size = 0;
  do {
    is.read(buffer.data(), buffer.size());
    if (is.bad()) break;
    crc32c = crc32c::Extend(
        crc32c, reinterpret_cast<std::uint8_t*>(buffer.data()), is.gcount());
    size += is.gcount();
  } while (not is.eof());

  static_assert(std::numeric_limits<unsigned char>::digits == 8,
                "This program assumes an 8-bit char");
  boost::endian::big_uint32_buf_at buf(crc32c);
  return {size, cppcodec::base64_rfc4648::encode(
                    std::string(buf.data(), buf.data() + sizeof(buf)))};
}

}
