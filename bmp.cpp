#include "bmp.h"
#include "image.h"

BMPHeader ReadBMPHeader(std::ifstream& in) {
    BMPHeader bmp_header;
    ReadNum(in, bmp_header.file_type);
    ReadNum(in, bmp_header.file_size);
    ReadNum(in, bmp_header.reserved1);
    ReadNum(in, bmp_header.reserved2);
    ReadNum(in, bmp_header.offset_data);
    return bmp_header;
}

DIBHeader ReadDIBHeader(std::ifstream& in) {
    DIBHeader dib_header;
    ReadNum(in, dib_header.header_size);
    ReadNum(in, dib_header.size.width);
    ReadNum(in, dib_header.size.height);
    ReadNum(in, dib_header.color_planes);
    ReadNum(in, dib_header.bits_per_pixel);
    ReadNum(in, dib_header.compression_method);
    ReadNum(in, dib_header.bitmap_data_size);
    ReadNum(in, dib_header.resolution.horizontal);
    ReadNum(in, dib_header.resolution.vertical);
    ReadNum(in, dib_header.colors.important);
    ReadNum(in, dib_header.colors.total);
    return dib_header;
}

void WriteBMPHeader(std::ofstream& out, const BMPHeader& bmp_header) {
    WriteNum(out, bmp_header.file_type);
    WriteNum(out, bmp_header.file_size);
    WriteNum(out, bmp_header.reserved1);
    WriteNum(out, bmp_header.reserved2);
    WriteNum(out, bmp_header.offset_data);
}

void WriteDIBHeader(std::ofstream& out, const DIBHeader& dib_header) {
    WriteNum(out, dib_header.header_size);
    WriteNum(out, dib_header.size.width);
    WriteNum(out, dib_header.size.height);
    WriteNum(out, dib_header.color_planes);
    WriteNum(out, dib_header.bits_per_pixel);
    WriteNum(out, dib_header.compression_method);
    WriteNum(out, dib_header.bitmap_data_size);
    WriteNum(out, dib_header.resolution.horizontal);
    WriteNum(out, dib_header.resolution.vertical);
    WriteNum(out, dib_header.colors.important);
    WriteNum(out, dib_header.colors.total);
}

template <typename T>
void ReadNum(std::ifstream& in, T& value) {
    uint8_t buff[sizeof(value)];
    in.read(reinterpret_cast<char*>(buff), sizeof(value));
    for (int i = 0; i < sizeof(value); i++) {
        value |= buff[i] << (8 * i);
    }
}

template <typename T>
void WriteNum(std::ofstream& out, const T& value) {
    for (int i = 0; i < sizeof(value); ++i) {
        out.put(value >> (8 * i) & 0xFF);
    }
}

Image LoadBMP(const std::string& path) {
    std::ifstream in{path, std::ios::binary};
    ReadBMPHeader(in);
    DIBHeader dib_header = ReadDIBHeader(in);
    Image image{dib_header.size.width, dib_header.size.height};
    for (auto i = 0; i < dib_header.size.height; ++i) {
        for (auto j = 0; j < dib_header.size.width; ++j) {
            Image::Color el;
            ReadNum(in, el.R);
            ReadNum(in, el.G);
            ReadNum(in, el.B);
            image.GetPixel(j, dib_header.size.height - i - 1) = el;
        }
    }
    auto read_bytes = sizeof(Image::Color) * dib_header.size.width;
    while (read_bytes % 4 != 0) {
        uint8_t padding;
        ReadNum(in, padding);
        ++read_bytes;
    }
    return image;
}

void SaveBMP(const Image& image, const std::string& path) {
    BMPHeader bmp_header;
    bmp_header.file_type = 0x4d42;
    bmp_header.file_size = sizeof(BMPHeader) + sizeof(DIBHeader) + image.GetHeight() * image.GetWidth() * 3;
    bmp_header.offset_data = sizeof(BMPHeader) + sizeof(DIBHeader);

    DIBHeader dib_header;
    dib_header.size.width = image.GetWidth();
    dib_header.size.height = image.GetHeight();
    auto row_length = image.GetWidth() * 3;
    auto padding = ((row_length + 3) / 4) * 4 - row_length;
    dib_header.bitmap_data_size = image.GetHeight() * (row_length + padding);

    std::ofstream out{path, std::ofstream::binary};
    WriteBMPHeader(out, bmp_header);
    WriteDIBHeader(out, dib_header);
    for (int i = static_cast<size_t>(image.GetHeight() - 1); i >= 0; --i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            WriteNum(out, image.GetPixel(j, i).R);
            WriteNum(out, image.GetPixel(j, i).G);
            WriteNum(out, image.GetPixel(j, i).B);
        }
        for (size_t j = 0; j < padding; ++j) {
            WriteNum<char>(out, 0);
        }
    }
    out.close();
}