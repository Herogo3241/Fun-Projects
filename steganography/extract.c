#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <stego.wav>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        printf("Error opening file.\n");
        return 1;
    }

    fseek(in, 44, SEEK_SET); // skip header

    // Read first 32 bits → msg_len
    uint32_t msg_len = 0;
    for (int i = 0; i < 32; i++) {
        int16_t sample;
        fread(&sample, sizeof(int16_t), 1, in);
        int bit = sample & 1;
        msg_len <<= 1;
        msg_len |= bit;
    }

    printf("Decoded message length: %u bytes\n", msg_len);

    char *msg = calloc(msg_len + 1, sizeof(char));
    if (!msg) {
        printf("Memory error.\n");
        fclose(in);
        return 1;
    }

    for (uint32_t bit_idx = 0; bit_idx < msg_len * 8; bit_idx++) {
        int16_t sample;
        fread(&sample, sizeof(int16_t), 1, in);

        int bit = sample & 1;
        msg[bit_idx / 8] <<= 1;
        msg[bit_idx / 8] |= bit;
    }

    fclose(in);

    printf("Extracted message: %s\n", msg);
    free(msg);
    return 0;
}