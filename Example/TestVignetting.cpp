#include <Vignetting.h>
#include <fstream>
#include <vector>
enum color_format {
    YUV420_10BE,
    YUV420_10LE,
    YUV444,
    YUV422,
    YUV420,
    UYVY,
    YUYV,
    YYY,
    PACKED_YUV444,
    NV12,
    NV21,
    RGB32,
    RGB24,
    RGB16,
};

int ReadYUV(const std::string& filename, std::vector<char>& data) {
    std::ifstream yuv(filename, std::ios::binary);
    if (yuv.is_open() == false) {
        return -1;
    }
    yuv.seekg(0, std::ios::end);
    int filesize = (int)yuv.tellg();
    yuv.seekg(0, std::ios::beg);

    data.resize(filesize);
    yuv.read(data.data(), filesize);
    return 0;
}

int WriteData(const std::string filename, const std::vector<char>& data) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open() == false) {
        return -1;
    }
    out.write(data.data(), data.size());
    return 0;
}

int GetFileSize(int width, int height, int fmt) {
    return width * height * 2;
}

int UnpackYUVData(const std::vector<char>& input, std::vector<char>& output, int width, int height, int fmt) {
    if (input.size() != output.size() || input.size() == 0) {
        return -1;
    }
    int filesize = GetFileSize(width, height, fmt);
    if (filesize != input.size()) {
        return -2;
    }
    output.assign(input.begin(), input.end());
    return 0;
}

int main(int argc, char* argv[]) {
    std::string filename = "suzie_qcif_yuv422p.yuv";
    std::vector<char> filenameOut(260);
    int width = 176;
    int height = 144;
    std::vector<char> yuv;
    ReadYUV(filename, yuv);
    for (int i = 1; i <= 9; i++) {
        std::vector<char> temp(yuv);
        ApplyVignetting((uint8_t*)temp.data(), width, height, i * 0.1f, 0.7f);
        sprintf(filenameOut.data(), "suzie_qcif_yuv422p_vignetting_%d.yuv", i);
        int ret = WriteData(filenameOut.data(), temp);
    }
    return 0;
}
