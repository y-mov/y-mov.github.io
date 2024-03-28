#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length) {
    *output_length = 4 * ((input_length + 2) / 3); // 计算输出字符串的长度
    char* encoded_data = malloc(*output_length + 1); // 分配存储空间（记得释放）
    if (encoded_data == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        unsigned char byte1 = i < input_length ? data[i++] : 0;
        unsigned char byte2 = i < input_length ? data[i++] : 0;
        unsigned char byte3 = i < input_length ? data[i++] : 0;

        unsigned char encoded_byte1 = byte1 >> 2;
        unsigned char encoded_byte2 = ((byte1 & 0x03) << 4) | (byte2 >> 4);
        unsigned char encoded_byte3 = ((byte2 & 0x0F) << 2) | (byte3 >> 6);
        unsigned char encoded_byte4 = byte3 & 0x3F;

        encoded_data[j++] = base64_chars[encoded_byte1];
        encoded_data[j++] = base64_chars[encoded_byte2];
        encoded_data[j++] = i - 2 < input_length ? base64_chars[encoded_byte3] : '=';
        encoded_data[j++] = i - 1 < input_length ? base64_chars[encoded_byte4] : '=';
    }

    encoded_data[j] = '\0';
    return encoded_data;
}

unsigned char* base64_decode(const char* encoded_data, size_t input_length, size_t* output_length) {
    if (input_length % 4 != 0) {
        return NULL; // Base64编码的长度必须是4的倍数
    }

    *output_length = input_length / 4 * 3; // 计算输出数据的长度
    if (encoded_data[input_length - 1] == '=') {
        (*output_length)--;
    }
    if (encoded_data[input_length - 2] == '=') {
        (*output_length)--;
    }

    unsigned char* decoded_data = malloc(*output_length); // 分配存储空间（记得释放）
    if (decoded_data == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        unsigned char encoded_byte1 = encoded_data[i++];
        unsigned char encoded_byte2 = encoded_data[i++];
        unsigned char encoded_byte3 = encoded_data[i++];
        unsigned char encoded_byte4 = encoded_data[i++];

        unsigned char byte1 = strchr(base64_chars, encoded_byte1) - base64_chars;
        unsigned char byte2 = strchr(base64_chars, encoded_byte2) - base64_chars;
        unsigned char byte3 = strchr(base64_chars, encoded_byte3) - base64_chars;
        unsigned char byte4 = strchr(base64_chars, encoded_byte4) - base64_chars;

        unsigned char decoded_byte1 = (byte1 << 2) | (byte2 >> 4);
        unsigned char decoded_byte2 = (byte2 << 4) | (byte3 >> 2);
        unsigned char decoded_byte3 = (byte3 << 6) | byte4;

        decoded_data[j++] = decoded_byte1;
        if (j < *output_length) {
            decoded_data[j++] = decoded_byte2;
        }
        if (j < *output_length) {
            decoded_data[j++] = decoded_byte3;
        }
    }

    return decoded_data;
}

int main() {
    const char* input = "Hello, World!"; // 输入字符串
    size_t input_length = strlen(input);
    size_t encoded_length = 0;
    char* encoded_data = base64_encode((const unsigned char*)input, input_length, &encoded_length);

    if (encoded_data != NULL) {
        printf("Base64 Encoded Data: %s\n", encoded_data);

        size_t decoded_length = 0;
        unsigned char* decoded_data = base64_decode(encoded_data, encoded_length, &decoded_length);

        if (decoded_data != NULL) {
            printf("Base64 Decoded Data: %s\n", decoded_data);

            free(decoded_data); // 释放分配的内存
        }

        free(encoded_data); // 释放分配的内存
    }

    return 0;
}