# CRYPTEX - Advanced Encryption Tool

![Version](https://img.shields.io/badge/version-2.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

CRYPTEX is a powerful, user-friendly encryption and decryption tool designed for both text and file encryption. It provides multiple encryption methods with varying levels of security to protect your sensitive data.

## 🔑 Features

- **Multiple Encryption Methods**:
  - Caesar Cipher (simple character shifting)
  - XOR Encryption (more secure, uses string keys)
  
- **Versatile Functionality**:
  - Text encryption and decryption
  - File encryption and decryption
  - Support for saving encrypted/decrypted output to files
  
- **User-Friendly Interface**:
  - Clear menu system
  - Guided operation with helpful prompts
  - Input validation to prevent errors
  
- **Enhanced Security**:
  - Support for complex string keys with XOR encryption
  - Proper handling of special characters
  - Binary file support

## 📋 Requirements

- C++ compiler with C++11 support
- Standard C++ libraries

## 🚀 Getting Started

### Compilation

```bash
# Using g++
g++ -std=c++11 main.cpp -o cryptex

# Using clang
clang++ -std=c++11 main.cpp -o cryptex
```

### Running the Application

```bash
# On Windows
cryptex.exe

# On Linux/macOS
./cryptex
```

## 📖 How to Use

### Main Menu

When you start CRYPTEX, you'll see the main menu with the following options:

1. **Encrypt Text** - Encrypt a text string
2. **Decrypt Text** - Decrypt a text string
3. **Encrypt File** - Encrypt the contents of a file
4. **Decrypt File** - Decrypt the contents of a file
5. **Exit** - Exit the application

### Text Encryption

1. Select option 1 from the main menu
2. Choose your encryption method:
   - Caesar Cipher (simple shift cipher)
   - XOR Encryption (more secure)
3. Enter the text you want to encrypt
4. Provide the encryption key:
   - For Caesar Cipher: a numeric shift value
   - For XOR Encryption: a string key
5. View the encrypted result
6. Optionally save the result to a file

### Text Decryption

1. Select option 2 from the main menu
2. Choose your decryption method (must match the method used for encryption)
3. Enter the text you want to decrypt
4. Provide the decryption key (must match the key used for encryption)
5. View the decrypted result
6. Optionally save the result to a file

### File Encryption

1. Select option 3 from the main menu
2. Choose your encryption method
3. Enter the path to the input file
4. Enter the path for the output file
5. Provide the encryption key
6. The file will be encrypted and saved to the specified output path

### File Decryption

1. Select option 4 from the main menu
2. Choose your decryption method (must match the method used for encryption)
3. Enter the path to the encrypted file
4. Enter the path for the output file
5. Provide the decryption key (must match the key used for encryption)
6. The file will be decrypted and saved to the specified output path

## 📝 Use Cases

### 1. Secure Message Exchange

Alice wants to send a confidential message to Bob:

1. Alice uses CRYPTEX to encrypt her message using XOR encryption with a pre-shared key
2. Alice sends the encrypted message through a public channel
3. Bob receives the encrypted message and uses CRYPTEX to decrypt it using the same key
4. The original message is only readable by Bob, even if intercepted during transmission

### 2. Protecting Sensitive Files

A user wants to store sensitive documents securely:

1. The user selects the "Encrypt File" option in CRYPTEX
2. They choose XOR encryption and provide a strong password as the key
3. The encrypted file can be stored on a cloud service or shared drive
4. When needed, the user can decrypt the file using the same password

### 3. Simple Data Obfuscation

A developer wants to obfuscate configuration data:

1. The developer uses Caesar cipher to encrypt configuration values
2. The encrypted values are stored in the application's configuration files
3. The application decrypts the values at runtime using the known shift key
4. This provides a basic level of protection against casual inspection

### 4. Educational Tool

CRYPTEX can be used as an educational tool to demonstrate:

1. Basic principles of cryptography
2. How different encryption algorithms work
3. The importance of key management
4. The difference between weak and strong encryption methods

## ⚠️ Security Considerations

- **Caesar Cipher** is a very basic encryption method and should only be used for educational purposes or non-sensitive data
- **XOR Encryption** provides better security but is still not suitable for highly sensitive data
- For production-level security, consider using established encryption libraries that implement standards like AES, RSA, etc.
- Always keep your encryption keys secure and never share them through insecure channels

## 🔄 Version History

- **2.0.0** - Major update with new encryption methods, file encryption support, and improved UI
- **1.0.0** - Initial release with basic Caesar cipher functionality

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🔗 Links

- [Project Repository](https://github.com/AyhamJo7/CRYPTEX)
- [Report Issues](https://github.com/AyhamJo7/CRYPTEX/issues)

---

Made with ❤️ by AyhamJo7
