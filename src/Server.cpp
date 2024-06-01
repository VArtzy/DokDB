#include <cstring>
#include <iostream>
#include <fstream>

const int HEADER_SIZE = 100;
int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string database_file_path = argv[1];
    std::string command = argv[2];

    if (command == ".dbinfo") {
        std::ifstream database_file(database_file_path, std::ios::binary);
        if (!database_file) {
            std::cerr << "Failed to open the database file" << std::endl;
            return 1;
        }

        database_file.seekg(16);  // Skip the first 16 bytes of the header
        
        char buffer[2];
        database_file.read(buffer, 2);
        
        unsigned short page_size = (static_cast<unsigned char>(buffer[1]) | (static_cast<unsigned char>(buffer[0]) << 8));
        
        std::cout << "database page size: " << page_size << std::endl;

        database_file_path.seekg(HEADER_SIZE + 3);
        database_file.read(buffer, 2);

        unsigned short table_count = (static_cast<unsigned char>(buffer[1] | static_cast<unsigned char>(buffer[0] << 8));

        std::cout << "number of tables: " << table_count << std::endl;
    }

    return 0;
}
