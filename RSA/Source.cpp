#include<iostream>
#include<string>
#include<numeric>
#include<vector>
#include<sstream>
std::vector<std::uint64_t> encoding_message(std::string msg, std::uint64_t public_key, uint64_t prod)
{
    std::vector<uint64_t> message_to_int;
    std::vector<uint64_t> for_return;
    for (auto& it : msg)
    {
        message_to_int.push_back(uint64_t(it));
    }
    for (std::vector<uint64_t>::iterator it = message_to_int.begin(); it != message_to_int.end(); it++)
    {
        uint64_t rez = 1;
        uint64_t e1 = public_key;
        while (e1--)
        {
            rez *= *it;
            rez %= prod;
        }
        for_return.push_back(rez);
    }
    return for_return;
}
std::string decoding_message(std::vector<uint64_t> encrypted_message, std::uint64_t private_key, uint64_t prod)
{
    std::string string_return = "";
    for (std::vector<uint64_t>::iterator it = encrypted_message.begin(); it != encrypted_message.end(); it++) {
        std::uint64_t d1 = private_key;
        std::uint64_t decrypted = 1;
        while (d1--)
        {
            decrypted *= *it;
            decrypted %= prod;
        }
        std::stringstream ss;
        ss << (uint8_t)decrypted;
        std::string temporar;
        ss >> temporar;
        string_return += temporar;
    }
    return string_return;
}
int main()
{
    uint64_t p = 17;
    uint64_t q = 43;
    uint64_t n = p * q;
    uint64_t phi = ((p - 1) * (q - 1));
    uint64_t public_key = 2;
    uint64_t private_key = 2;
    std::string message = "salut";
    //std::cout << "Introdu mesajul: ";
    //std::getline(std::cin, message);
    while (1)
    {
        if (std::gcd(public_key, phi) == 1)
            break;
        public_key++;
    }
    while (1)
    {
        if ((private_key * public_key) % phi == 1)
            break;
        private_key++;
    }
    std::cout << "public key: " << public_key << "\nprivate key: " << private_key << "\nMesaj criptat: ";
    std::vector<uint64_t> encrypted_message = encoding_message(message, public_key, n);
    for (std::vector<uint64_t>::iterator it = encrypted_message.begin(); it != encrypted_message.end(); it++)
    {
        std::cout << *it;
    }
    std::string decrypted_message = decoding_message(encrypted_message, private_key, n);
    std::cout << "\n" << decrypted_message;
}