#ifndef BASE64_H
#define BASE64_H

//Base64 Encoding consists of 26 upper and lower case chars = 52, numbers from 0 to 9 = 61, and + and / which will be 63
//Base64 is very safe because it's very hard to lose any data while using it
//Man encodes as bWFu
//Take letter values from ASCII table
//M = 77 (binary: 01001101)
//A = 97 (binary: 01100001)
//N = 110 (binary: 01101110)
//Binaries get grouped: 010011010110000101101110 (length is 3x8 = 24bits)
//24 bits are grouped into groups of 6 bits, because 2^6 = 64 so we can map them to our table
//010011 010110 000101 101110
//convert to decimal
//19 22 5 46
//map it out
//b W F u
//our algorithm will directly encode string to string but minor modifications are needed to encoded arbitrary byte sequences
//arbitrary byte sequences is what we gonna use to encrypt our code


#include <vector>//Data Structure like an array but far more advanced
#include <string>

namespace Base64
{
    std::string base64_encode(const std::string &);//Declare how function call will look

    //Encryption and Decryption keys, called SALTs
    const std::string &KEY1 = "root/toor";
    const std::string &KEY2 = "$ha#ha#ha$";
    const std::string &KEY3 = "name=noone";

    std::string EncryptB64(std::string s)//Encrypt the string
    {
        //Obscure the string so it will be harder to decrypt
        s = KEY1 + s + KEY2 + KEY3;
        s = base64_encode(s);
        s.insert(7, KEY3);//Insert key3 on 7th position of the string
        s += KEY1;
        s = base64_encode(s);
        s = KEY2 + KEY3 + s + KEY1;
        s = base64_encode(s);
        s.insert(1, "L");
        s.insert(7, "m");
        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64_encode(const std::string &s)
    {
        std::string ret;
        int val = 0;//index to map input to our table
        int bits = -6;//Number of bits in the group
        const unsigned int b63 = 0x3F;//0x declares that this is Hexadecimal value, 3F decimal value is 63

        for (const auto &c : s)//type auto so C++ will automatically detect type of the variable
        {//Assign every character from string S to C
            val = (val << 8) + c;//<< means that character that we get from a string will be shifted left by 8 places
            bits += 8;//Add bits to the string when we shit character, because base64 works with octals when extracting info from string
            while (bits >= 0)
            {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]);//Insert map number.>> means right shifting and & means binary end
                bits -= 6;//Grouping by 6 bits
            }
        }
        if (bits > -6)
        {
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
        }

        while(ret.size() % 4)//Detect if the value of the map is bigger than 0 or smaller
        {
            ret.push_back('=');
        }

        return ret;//Return encrypted string
    }

}

#endif // BASE_64
