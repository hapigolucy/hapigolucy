#include "StringsRegEx.h"

unsigned char hexchar_to_int(char const ch)
{
    if(ch >= '0' && ch <= '9')
        return ch - '0';
    if(ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    if(ch >= 'a' && ch <= 'z')
        return ch - 'a';

    throw std::invalid_argument("Invalid hex chartacter!!!");
}

string& capitalize(string& text)
{
    bool newWord = true;
    for( auto& ch : text)
    {
        newWord = newWord || std::ispunct(ch) || std::isspace(ch);
        if(std::isalpha(ch))
        {
            if(newWord)
            {
                ch = std::toupper(ch);
                newWord = false;
            }
            else
                ch = std::tolower(ch);
        }
    }
    return text;
}

string& capitalizeSentence(string& text)
{
    string::iterator endIter = end(text);

    auto finder = [endIter](string::iterator begIter) {
        auto endMinus1 = endIter - 1;
        std::vector<char> str = { '?', '!', '.'};
        std::cout << "\nFinding from => " << *begIter << " to => " << *endMinus1 << std::endl;
        return std::find_first_of(begIter, endIter, begin(str), end(str));
    };

    auto capitalizer = [](string::iterator iter) {
        ++iter;
        if(isspace(*iter))
            ++iter;
        return pair<string::iterator, char>(iter, toupper(*iter));
    };

    auto retIter = finder(begin(text));
    if(retIter != endIter)
    {
        std::cout << "Found => " << *retIter << std::endl;
        pair<string::iterator, char> retPair = capitalizer(retIter);
        retIter = retPair.first;
        *retIter = retPair.second;
        retIter = finder(retIter);
    }

    return text;
}

string compressString(string& input){
    //string input = "abcaaaaabbccccd";

    auto adjacentFinder = [&input](auto begIter, auto endIter) {
        auto iter = adjacent_find(begIter, endIter);
        return iter;
    };

    auto adjacentCountFinder = [&input, adjacentFinder](auto begIter, auto endIter) {
        auto iter = adjacentFinder(begIter, endIter);
        int count = 0;
        if(iter != end(input)) {
            ++iter; count = 2;
            while(*iter == *(iter+1))
            {
                ++iter; ++count;
            }
        }
        cout << "Returning : " << *iter << endl;
        return std::pair<char, int>(*iter, count);
    };

    auto iter = adjacentFinder(begin(input), end(input));
    while(iter != end(input)) {
        auto char_count = adjacentCountFinder(iter, end(input));
        char repChar   = char_count.first;
        char charCount = (char)char_count.second;
        string replacement(1, repChar);
        replacement.push_back(charCount);
        cout << "replacement is : " << replacement << endl;
        input.replace(iter, iter+charCount, replacement);
        iter = adjacentFinder(begin(input), end(input));
    }
    return move(input);
}

void runStringAndRegEx()
{
    cout << "\n\n***************String And RegEx***************" << endl;
    std::vector<unsigned char> v{ 0xBA, 0xAD, 0xF0, 0x0D };
    std::cout << "CAPS ON  : " << bytes_to_hexstr(v, true) << endl;
    std::cout << "CAPS OFF : " << bytes_to_hexstr(v) << endl;

    std::array<unsigned char, 6> a{ {1,2,3,4,5,6} };
    std::cout << "CAPS ON  : " << bytes_to_hexstr(a, true) << endl;
    std::cout << "CAPS OFF : " << bytes_to_hexstr(a) << endl;

    std::string input = "THIS IS an ExamplE,should wORk! The C++ Challenger";
    //cout << input << " --> in capitalized form is --> " << capitalize(input) << endl;

    input = "This is an example, should work? c++ Challenger? hopefully this works as expected.";
    cout << input << " --> sentence capitalized form --> \n" << capitalizeSentence(input) << endl;

    cout << "Enter the string that you want to compress : ";
    cin >> input;
    cout << input << " ---> " << compressString(input) << endl;
    cin >> input;
}
