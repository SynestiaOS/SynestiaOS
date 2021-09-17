#include <iostream>
#include <cstdint>
#include <memory>


#define MB  1024 * 1024

int main() {
    std::cout << "Will generate 32M increase file." << std::endl;
    FILE *fw = fopen("ext2_verify_file.bin", "wb");
    if (fw == nullptr) {
        return 0;
    }

    uint32_t *buf = new uint32_t[8 * MB];
    for (uint32_t i = 0; i < 8 * MB; i++) {
        buf[i] = i;
    }


    fwrite(buf, sizeof(uint32_t), 8 * MB, fw);

    fclose(fw);
    return 1;
}
