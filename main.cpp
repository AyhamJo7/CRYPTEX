#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

/**
 * @brief CipherTool - A class for encrypting and decrypting text using various methods
 * 
 * This class provides functionality for text encryption and decryption using
 * different algorithms including Caesar cipher and XOR encryption.
 */
class CipherTool {
private:
    // Maximum input length (can be adjusted as needed)
    static const int MAX_INPUT_LENGTH = 1024;
    
    /**
     * @brief Apply Caesar cipher to a string
     * 
     * @param text The text to encrypt/decrypt
     * @param key The shift value (positive for encryption, negative for decryption)
     * @return std::string The encrypted/decrypted text
     */
    std::string caesarCipher(const std::string& text, int key) {
        std::string result = text;
        for (size_t i = 0; i < result.length(); i++) {
            // Only shift alphanumeric characters
            if (std::isalpha(result[i])) {
                // Handle uppercase letters
                if (std::isupper(result[i])) {
                    result[i] = static_cast<char>((result[i] - 'A' + key + 26) % 26 + 'A');
                }
                // Handle lowercase letters
                else {
                    result[i] = static_cast<char>((result[i] - 'a' + key + 26) % 26 + 'a');
                }
            }
            else if (std::isdigit(result[i])) {
                // Handle digits (0-9)
                result[i] = static_cast<char>((result[i] - '0' + key + 10) % 10 + '0');
            }
            // Special characters remain unchanged
        }
        return result;
    }
    
    /**
     * @brief Apply XOR encryption to a string
     * 
     * @param text The text to encrypt/decrypt
     * @param key The encryption key
     * @return std::string The encrypted/decrypted text
     */
    std::string xorEncrypt(const std::string& text, const std::string& key) {
        std::string result = text;
        for (size_t i = 0; i < result.length(); i++) {
            // XOR each character with the corresponding key character
            result[i] = result[i] ^ key[i % key.length()];
        }
        return result;
    }
    
    /**
     * @brief Generate a simple hash from a string
     * 
     * @param input The input string
     * @return int A hash value derived from the input
     */
    int generateHash(const std::string& input) {
        int hash = 0;
        for (char c : input) {
            hash = (hash * 31 + c) % 1000000;
        }
        return hash;
    }
    
public:
    /**
     * @brief Encrypt text using Caesar cipher
     * 
     * @param text The text to encrypt
     * @param key The encryption key (shift value)
     * @return std::string The encrypted text
     */
    std::string encryptCaesar(const std::string& text, int key) {
        return caesarCipher(text, key);
    }
    
    /**
     * @brief Decrypt text using Caesar cipher
     * 
     * @param text The text to decrypt
     * @param key The decryption key (shift value)
     * @return std::string The decrypted text
     */
    std::string decryptCaesar(const std::string& text, int key) {
        return caesarCipher(text, -key);
    }
    
    /**
     * @brief Encrypt text using XOR with a string key
     * 
     * @param text The text to encrypt
     * @param key The encryption key
     * @return std::string The encrypted text
     */
    std::string encryptXOR(const std::string& text, const std::string& key) {
        return xorEncrypt(text, key);
    }
    
    /**
     * @brief Decrypt text using XOR with a string key
     * 
     * @param text The text to decrypt
     * @param key The decryption key
     * @return std::string The decrypted text
     */
    std::string decryptXOR(const std::string& text, const std::string& key) {
        // XOR encryption and decryption are the same operation
        return xorEncrypt(text, key);
    }
    
    /**
     * @brief Encrypt a file using the specified method
     * 
     * @param inputFile Path to the input file
     * @param outputFile Path to the output file
     * @param key The encryption key
     * @param method The encryption method (1 for Caesar, 2 for XOR)
     * @return bool True if successful, false otherwise
     */
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, 
                     const std::string& key, int method) {
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error: Could not open input file." << std::endl;
            return false;
        }
        
        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error: Could not create output file." << std::endl;
            inFile.close();
            return false;
        }
        
        std::vector<char> buffer(MAX_INPUT_LENGTH);
        while (inFile) {
            inFile.read(buffer.data(), buffer.size());
            std::streamsize bytesRead = inFile.gcount();
            
            if (bytesRead > 0) {
                std::string chunk(buffer.data(), bytesRead);
                std::string encrypted;
                
                if (method == 1) {
                    // Caesar cipher
                    int numKey = std::stoi(key);
                    encrypted = encryptCaesar(chunk, numKey);
                } else {
                    // XOR encryption
                    encrypted = encryptXOR(chunk, key);
                }
                
                outFile.write(encrypted.c_str(), encrypted.length());
            }
        }
        
        inFile.close();
        outFile.close();
        return true;
    }
    
    /**
     * @brief Decrypt a file using the specified method
     * 
     * @param inputFile Path to the input file
     * @param outputFile Path to the output file
     * @param key The decryption key
     * @param method The decryption method (1 for Caesar, 2 for XOR)
     * @return bool True if successful, false otherwise
     */
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, 
                     const std::string& key, int method) {
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error: Could not open input file." << std::endl;
            return false;
        }
        
        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error: Could not create output file." << std::endl;
            inFile.close();
            return false;
        }
        
        std::vector<char> buffer(MAX_INPUT_LENGTH);
        while (inFile) {
            inFile.read(buffer.data(), buffer.size());
            std::streamsize bytesRead = inFile.gcount();
            
            if (bytesRead > 0) {
                std::string chunk(buffer.data(), bytesRead);
                std::string decrypted;
                
                if (method == 1) {
                    // Caesar cipher
                    int numKey = std::stoi(key);
                    decrypted = decryptCaesar(chunk, numKey);
                } else {
                    // XOR decryption
                    decrypted = decryptXOR(chunk, key);
                }
                
                outFile.write(decrypted.c_str(), decrypted.length());
            }
        }
        
        inFile.close();
        outFile.close();
        return true;
    }
};

/**
 * @brief UserInterface - A class to handle user interaction
 * 
 * This class provides a command-line interface for the encryption/decryption tool.
 */
class UserInterface {
private:
    CipherTool cipherTool;
    
    /**
     * @brief Clear the input buffer
     */
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    /**
     * @brief Get a line of text from the user
     * 
     * @param prompt The prompt to display
     * @return std::string The user's input
     */
    std::string getInputLine(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }
    
    /**
     * @brief Get an integer from the user
     * 
     * @param prompt The prompt to display
     * @return int The user's input
     */
    int getInputInt(const std::string& prompt) {
        int input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cout << "Invalid input. Please enter a number: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        return input;
    }
    
    /**
     * @brief Handle text encryption
     */
    void handleTextEncryption() {
        std::cout << "\n===== Text Encryption =====\n";
        
        // Get encryption method
        std::cout << "Select encryption method:\n";
        std::cout << "1. Caesar Cipher (Simple shift cipher)\n";
        std::cout << "2. XOR Encryption (More secure)\n";
        int method = getInputInt("Enter your choice (1-2): ");
        
        if (method < 1 || method > 2) {
            std::cout << "Invalid choice. Using Caesar Cipher by default.\n";
            method = 1;
        }
        
        // Get the text to encrypt
        clearInputBuffer();
        std::string text = getInputLine("Enter the text to encrypt: ");
        
        // Get the encryption key
        std::string key;
        if (method == 1) {
            int shiftKey = getInputInt("Enter the shift key (number): ");
            key = std::to_string(shiftKey);
        } else {
            key = getInputLine("Enter the encryption key (string): ");
        }
        
        // Perform encryption
        std::string encrypted;
        if (method == 1) {
            encrypted = cipherTool.encryptCaesar(text, std::stoi(key));
        } else {
            encrypted = cipherTool.encryptXOR(text, key);
        }
        
        // Display result
        std::cout << "\nEncrypted text: " << encrypted << std::endl;
        
        // Option to save to file
        std::cout << "Do you want to save the encrypted text to a file? (y/n): ";
        char saveChoice;
        std::cin >> saveChoice;
        clearInputBuffer();
        
        if (saveChoice == 'y' || saveChoice == 'Y') {
            std::string filename = getInputLine("Enter the filename: ");
            std::ofstream outFile(filename);
            if (outFile) {
                outFile << encrypted;
                outFile.close();
                std::cout << "Encrypted text saved to " << filename << std::endl;
            } else {
                std::cout << "Error: Could not create file." << std::endl;
            }
        }
    }
    
    /**
     * @brief Handle text decryption
     */
    void handleTextDecryption() {
        std::cout << "\n===== Text Decryption =====\n";
        
        // Get decryption method
        std::cout << "Select decryption method:\n";
        std::cout << "1. Caesar Cipher (Simple shift cipher)\n";
        std::cout << "2. XOR Decryption (More secure)\n";
        int method = getInputInt("Enter your choice (1-2): ");
        
        if (method < 1 || method > 2) {
            std::cout << "Invalid choice. Using Caesar Cipher by default.\n";
            method = 1;
        }
        
        // Get the text to decrypt
        clearInputBuffer();
        std::string text = getInputLine("Enter the text to decrypt: ");
        
        // Get the decryption key
        std::string key;
        if (method == 1) {
            int shiftKey = getInputInt("Enter the shift key (number): ");
            key = std::to_string(shiftKey);
        } else {
            key = getInputLine("Enter the decryption key (string): ");
        }
        
        // Perform decryption
        std::string decrypted;
        if (method == 1) {
            decrypted = cipherTool.decryptCaesar(text, std::stoi(key));
        } else {
            decrypted = cipherTool.decryptXOR(text, key);
        }
        
        // Display result
        std::cout << "\nDecrypted text: " << decrypted << std::endl;
        
        // Option to save to file
        std::cout << "Do you want to save the decrypted text to a file? (y/n): ";
        char saveChoice;
        std::cin >> saveChoice;
        clearInputBuffer();
        
        if (saveChoice == 'y' || saveChoice == 'Y') {
            std::string filename = getInputLine("Enter the filename: ");
            std::ofstream outFile(filename);
            if (outFile) {
                outFile << decrypted;
                outFile.close();
                std::cout << "Decrypted text saved to " << filename << std::endl;
            } else {
                std::cout << "Error: Could not create file." << std::endl;
            }
        }
    }
    
    /**
     * @brief Handle file encryption
     */
    void handleFileEncryption() {
        std::cout << "\n===== File Encryption =====\n";
        
        // Get encryption method
        std::cout << "Select encryption method:\n";
        std::cout << "1. Caesar Cipher (Simple shift cipher)\n";
        std::cout << "2. XOR Encryption (More secure)\n";
        int method = getInputInt("Enter your choice (1-2): ");
        
        if (method < 1 || method > 2) {
            std::cout << "Invalid choice. Using Caesar Cipher by default.\n";
            method = 1;
        }
        
        // Get input and output filenames
        clearInputBuffer();
        std::string inputFile = getInputLine("Enter the input file path: ");
        std::string outputFile = getInputLine("Enter the output file path: ");
        
        // Get the encryption key
        std::string key;
        if (method == 1) {
            int shiftKey = getInputInt("Enter the shift key (number): ");
            key = std::to_string(shiftKey);
        } else {
            key = getInputLine("Enter the encryption key (string): ");
        }
        
        // Perform file encryption
        bool success = cipherTool.encryptFile(inputFile, outputFile, key, method);
        
        if (success) {
            std::cout << "File encrypted successfully!" << std::endl;
        }
    }
    
    /**
     * @brief Handle file decryption
     */
    void handleFileDecryption() {
        std::cout << "\n===== File Decryption =====\n";
        
        // Get decryption method
        std::cout << "Select decryption method:\n";
        std::cout << "1. Caesar Cipher (Simple shift cipher)\n";
        std::cout << "2. XOR Decryption (More secure)\n";
        int method = getInputInt("Enter your choice (1-2): ");
        
        if (method < 1 || method > 2) {
            std::cout << "Invalid choice. Using Caesar Cipher by default.\n";
            method = 1;
        }
        
        // Get input and output filenames
        clearInputBuffer();
        std::string inputFile = getInputLine("Enter the input file path: ");
        std::string outputFile = getInputLine("Enter the output file path: ");
        
        // Get the decryption key
        std::string key;
        if (method == 1) {
            int shiftKey = getInputInt("Enter the shift key (number): ");
            key = std::to_string(shiftKey);
        } else {
            key = getInputLine("Enter the decryption key (string): ");
        }
        
        // Perform file decryption
        bool success = cipherTool.decryptFile(inputFile, outputFile, key, method);
        
        if (success) {
            std::cout << "File decrypted successfully!" << std::endl;
        }
    }
    
public:
    /**
     * @brief Display the main menu and handle user choices
     */
    void run() {
        char continueChoice = 'y';
        
        while (continueChoice == 'y' || continueChoice == 'Y') {
            // Display welcome message and menu
            std::cout << "\n========================================\n";
            std::cout << "   CRYPTEX - Advanced Encryption Tool   \n";
            std::cout << "========================================\n\n";
            
            std::cout << "Select an option:\n";
            std::cout << "1. Encrypt Text\n";
            std::cout << "2. Decrypt Text\n";
            std::cout << "3. Encrypt File\n";
            std::cout << "4. Decrypt File\n";
            std::cout << "5. Exit\n";
            
            int choice = getInputInt("Enter your choice (1-5): ");
            
            switch (choice) {
                case 1:
                    handleTextEncryption();
                    break;
                case 2:
                    handleTextDecryption();
                    break;
                case 3:
                    handleFileEncryption();
                    break;
                case 4:
                    handleFileDecryption();
                    break;
                case 5:
                    std::cout << "Thank you for using CRYPTEX!\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
            
            std::cout << "\nDo you want to perform another operation? (y/n): ";
            std::cin >> continueChoice;
            clearInputBuffer();
        }
        
        std::cout << "Thank you for using CRYPTEX!\n";
    }
};

/**
 * @brief Main function
 * 
 * @return int Exit code
 */
int main() {
    UserInterface ui;
    ui.run();
    return 0;
}
