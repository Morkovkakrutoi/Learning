#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>

void Counter(char* filename, long long* answer) {
    std::ifstream file(filename);
    long long counter_lines = 0;
    long long counter_bytes = 0;
    long long counter_words = 0;
    long long counter_alnum = 0;

    if (file.get() != EOF) {
        counter_lines++;
    }
    file.unget();
    bool is_space = 1;

    const size_t kBufferSize = 64;
    char buffer[kBufferSize];

    while ((file.read(buffer, kBufferSize)) || file.gcount() > 0){
        size_t was_read = file.gcount();
        for (size_t i = 0; i < was_read; i++) {
            // counting lines
            if (buffer[i] == '\n') {
                counter_lines++;
            }
            unsigned char symbol = buffer[i];
            // counting alnum
            if (std::isalpha(symbol) != 0) {
                counter_alnum++;
            }
            // counting bytes
            counter_bytes++;
            //counting words
            if (symbol == ' ' || symbol == '\n' || symbol == '\t' || symbol == '\r' || symbol == '\v' || symbol == '\f') {
                if (is_space == 0) {
                    is_space = 1;
                    counter_words++;
                }
            } else {
                is_space = 0;
            }
                
        }
    }
    if (is_space == 0) {counter_words++; }
    
    answer[0] = counter_lines;
    answer[1] = counter_words;
    answer[2] = counter_alnum;
    answer[3] = counter_bytes;
    return;
}

int main(int argc, char* argv[]) {
    bool is_lines = 0;
    bool is_bytes = 0;
    bool is_words = 0;
    bool is_alnum = 0;
    for (int i = 1; i < argc; i++) {
        // flags
        if (argv[i][0] == '-') {
            
            if (argv[i][1] == '-') {
                //full flags
                if (strcmp(argv[i], "--lines") == 0) {is_lines = true; }
                if (strcmp(argv[i], "--bytes") == 0) {is_bytes = true; }
                if (strcmp(argv[i], "--words") == 0) {is_words = true; }
                if (strcmp(argv[i], "--alnum") == 0) {is_alnum = true; }
            } else {
                // short flags
                for (int j = 1; j < strlen(argv[i]); j++) {
                    if (argv[i][j] == 'l') {is_lines = true; }
                    if (argv[i][j] == 'c') {is_bytes = true; }
                    if (argv[i][j] == 'w') {is_words = true; }
                    if (argv[i][j] == 'a') {is_alnum = true; }
                }
            }
        }
    }
    if (is_lines == 0 && is_bytes == 0 && is_words == 0 && is_alnum == 0) {
        is_lines = true;
        is_words = true;
        is_bytes = true;
    }
    std::cout << is_lines << ' ' << is_words << ' ' << is_alnum << ' ' << is_bytes << std::endl;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            char* filename = argv[i];
            // std::cout << filename << ' ';
            // std::cout << std::endl;
            long long answer[4] = {0};
            Counter(filename, answer);
            if (is_lines == true) {std::cout << answer[0] << ' '; }
            if (is_words == true) {std::cout << answer[1] << ' '; }
            if (is_alnum == true) {std::cout << answer[2] << ' '; }
            if (is_bytes == true) {std::cout << answer[3] << ' '; }

            std::cout << filename << std::endl;
        }
    }
    
    return 0;
}