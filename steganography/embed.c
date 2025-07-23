#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input.wav> <output.wav>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");



    uint8_t header[44];
    fread(header, sizeof(uint8_t), 44, in);
    fwrite(header, sizeof(uint8_t), 44, out);

    char msg[1024];
    printf("Enter the Secret Message: ");
    fgets(msg, sizeof(msg), stdin);

    int msg_len = strlen(msg);


    int bit_idx = 0;
    int total_bits = 32 + msg_len * 8;

    while (!feof(in) && bit_idx < total_bits) {
        int16_t sample;
        size_t read = fread(&sample, sizeof(int16_t), 1, in);
        if (read != 1) break;

        int bit;
        if (bit_idx < 32) {
            // Get bit from msg_len
            bit = (msg_len >> (31 - bit_idx)) & 1;
        } else {
            // Get bit from msg bytes
            int m_idx = bit_idx - 32;
            char byte = msg[m_idx / 8];
            bit = (byte >> (7 - (m_idx % 8))) & 1;
        }

        // Clear LSB & set
        sample &= ~1;
        sample |= bit;

        fwrite(&sample, sizeof(int16_t), 1, out);

        bit_idx++;
    }



    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, in) == 1) {
        fwrite(&sample, sizeof(int16_t), 1, out);
    }

    fclose(in);
    fclose(out);

    printf("Message embedded.\n");



    return 0;
}