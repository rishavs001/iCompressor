#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;
#define word_bank "wordbank.txt"
void compress();
void decompress();

int main()
{
    while (1)
    {
        int choice;
        cout << "     PRESS 1 TO COMPRESS\n";
        cout << "     PRESS 2 TO DECOMPRESS\n";
        cout << "---------------------------------\n";
        cout << "ENTER CHOICE: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            compress();
            break;
        case 2:
            decompress();
            break;
        default:
            cout << "WRONG CHOICE\nEXITED";
            exit(0);
        }
    }
    return 0;
}
void compress()
{
    string f, f1, f2;
    cout << "Enter file name to compress: ";
    cin >> f;
    f1 = f + ".txt";
    f2 = f + "_compressed.txt";
    ifstream file1(f1);
    ifstream file2(word_bank);
    ofstream file3(f2);
    map<string, int> word_map;

    // read file2 into word_map
    string word = "";
    int line_number = 1;
    while (file2 >> word)
    {
        word_map[word] = line_number++;
    }

    if (file1.is_open())
    {
        char c;
        word = "0";
        while (file1.get(c))
        {
            if (c == ' ' || c == '\n')
            {
                if (c == ' ')
                {
                    c = '$';
                }
                else if (c == '\n')
                {
                    c = '@';
                }

                if (word_map.find(word) != word_map.end())
                {
                    file3 << word_map[word] << c; // word found, print line number
                }
                else
                {
                    word_map[word] = line_number++; // word not found, add to word_map
                    ofstream file2(word_bank, ios::app);

                    file2 << word << endl;         // and file2
                    file3 << line_number - 1 << c; // print line number
                }
                word = "0";
            }
            else
            {
                word += c;
            }
        }
        file1.close();
        file2.close();
        file3.close();

        // Finding file reduction percentage
        uintmax_t inputFileSize = fs::file_size(f1);
        uintmax_t outputFileSize = fs::file_size(f2);
        uintmax_t differenceprcnt = ((inputFileSize - outputFileSize) * 100) / inputFileSize;
        cout << "   <<File compressed by " << differenceprcnt << "%>>\n\n\n";
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

void decompress()
{
    string f, f1, f2;
    cout << "Enter file name to decompress: ";
    cin >> f;
    f1 = f + ".txt";
    f2 = f + "_decompressed.txt";

    // Open file1 for reading, file2 for reading, and file3 for writing
    long long num = 0, n1, n;
    ifstream file1(f1);
    ifstream file2(word_bank);
    ofstream file3(f2);
    vector<int> line_bankNum;

    if (file1.is_open())
    {
        char c;

        while (file1.get(c))
        {
            if (c == '$' || c == '@')
            {
                if (num != 0)
                {
                    line_bankNum.push_back(num);
                }
                if (c == '$')
                {
                    line_bankNum.push_back(-1);
                }
                else if (c == '@')
                {
                    line_bankNum.push_back(-2);
                }

                num = 0;
            }
            else
            {
                // converting string to number
                n = (int)c - '0';
                num = num * 10 + n;
            }
        }
        file2.close();
        string line;

        for (int i = 0; i < line_bankNum.size(); i++)
        {
            n1 = line_bankNum[i];

            if (n1 == -1)
            {
                file3 << " ";
            }

            else if (n1 == -2)
            {
                file3 << "\n";
            }
            else
            {
                ifstream file2(word_bank);
                int lineNumber = 0;
                while (getline(file2, line))
                {

                    lineNumber++;

                    if (lineNumber == n1)
                    {
                        if (line.length() > 1)
                        {
                            line = line.substr(1);
                        }
                        else
                        {
                            line = "";
                        }

                        file3 << line;

                        file2.close();
                    }
                }
            }
        }

        file1.close();
        file2.close();
        file3.close();
        cout << "  <<FILE DECOMPRESSED>>\n";
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}