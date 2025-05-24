using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <cctype>

// 파일에서 문자열 다루기

int pushC = 0;
int pushD = 0;
int pushE = 0;
int pushF = 0;
int pushG = 0;
int pushR = 0;

void StoreFile()
{
    ofstream outFile("data.txt");

    if (outFile.is_open())
    {
        outFile << "This is computer graphics warming up program.\n";
        outFile << " 1 2 3 4 5 6 7 8 9 10\n";
        outFile << " File input-output sample program\n";
        outFile << " 2024 Fall semester 3D computer graphics\n";
        outFile << " Tech University     Korea\n";
        outFile << " Software College Game and multimedia engineering department\n";
        outFile << " It was so hot this summer and I'm glad I was able to endure this extreme heat well.\n";
        outFile << "Computer graphics class this semester is on Mondays, Tuesdays, and Wednesdays.\n";
        outFile << "fall Computer Korea DEPARTMENT multi 3D\n";
        outFile << " Monday&Tuesday&Wednesday&Thursday&Friday\n";
        outFile.close(); // 파일 닫기
        cout << "파일이 성공적으로 저장되었습니다.\n";
    }

    else
    {
        cerr << "파일을 열 수 없습니다.\n";
    }
}

void PrintFile()
{
    ifstream inFile("data.txt"); // 앞에서 저장한 파일
    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        cout << "[문장] " << line << endl;

        istringstream iss(line); // 공백 단위로 분리하기 위해 스트림에 라인 넣기
        string word;

        while (iss >> word) 
        { // 공백 하나 이상을 하나로 취급하며 단어 분리
            cout << "[단어] " << word << endl;
        }
    }

    inFile.close();
}

// 대문자로 시작되는 단어를 찾아 그 단어를 다른색으로 출력.
// 몇 개 있는지 계산해 출력
// 다시 누르면 원래대로 출력
void UpperWord()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    int upperCount = 0;
    string line;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        string word;

        if (pushC % 2 == 1)
        {
            while (iss >> word)
            {
                if (!word.empty() && isupper(word.front()))
                {
                    cout << "\033[1;31m" << word << "\033[0m ";
                    upperCount++;
                }

                else
                {
                    cout << word << " ";
                }
            }
            cout << endl;
        }
        else
        {
            cout << line << endl;
        }
    }
    cout << "대문자 시작 단어의 개수: " << upperCount << endl;
}

// 문장 한 줄 전체를 거꾸로 출력
void ReverseSentence()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;

    while (getline(inFile, line))
    {
        if (pushD % 2 == 1)
        {
            reverse(line.begin(), line.end());
            cout << line << endl;
        }

        else
        {
            cout << line << endl;
        }
    }
}

// 글자 3개 단위로 @2개 출력
void InsertAt()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;

    while (getline(inFile, line))
    {
        if (pushE % 2 == 1)
        {
            int charCount = 0;

            for (char ch : line)
            {
                cout << ch;
                charCount++;

                if (charCount % 3 == 0)
                {
                    cout << "@@";
                }
            }

            cout << endl;
        }

        else
        {
            cout << line << endl;
        }
    }
}

// 공백 기준으로 단어들을 거꾸로 출력
void ReverseWord()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            if (pushF % 2 == 1)
            {
                reverse(word.begin(), word.end());
                cout << word << " ";
            }

            else
            {
                cout << word << " ";
            }
        }
        cout << endl;
    }
}

// 바꾸고 싶은 문자를 입력 받음
char InputChar()
{
    char changeChar;

    cout << "바꾸고 싶은 문자를 입력 하세요: ";
    cin >> changeChar;

    return changeChar;
}

// 바뀔 문자를 입력 받음
char WantChar()
{
    char wantChar;

    cout << "바뀔 문자를 입력 하세요: ";
    cin >> wantChar;

    return wantChar;
}

// 문자 내부의 특정 문자를 다른 문자로 바꾸기
void ChangeChar()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;

    if (pushG % 2 == 1)
    {
        char changeChar = InputChar();
        char wantChar = WantChar();

        while (getline(inFile, line))
        {
            for (char& ch : line)
            {
                if (ch == changeChar)
                    ch = wantChar;
            }

            cout << line << endl;
        }
    }

    else
    {
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
    }
}

// 각 줄의 단어 개수 출력
void WordCount()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        string word;
        int wordCount = 0;

        while (iss >> word)
        {
            wordCount++;
        }

        cout << line << endl;
        cout << "단어 개수: " << wordCount << endl;
        wordCount = 0;
    }
}

// 한 문장의 단어의 개수를 세어 오름차순, 내림차순 문장 출력
void SortPrint()
{
    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    // map은 중복 키가 허용이 안돼서 vector사용.
    vector<pair<int, string>> sentences; // (단어 수, 문장)

    string line;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        string word;
        int wordCount = 0;

        while (iss >> word)
        {
            wordCount++;
        }

        if (pushR % 3 == 0)
            cout << line << endl;

        sentences.push_back({ wordCount, line });
    }

    inFile.close();

    if (pushR % 3 == 1)
    {
        cout << "단어 개수대로 문장 오름차순 정렬" << endl;
        sort(sentences.begin(), sentences.end());
        for (const auto& p : sentences)
        {
            cout << p.second << "단어 " << p.first << "개" << endl;
        }
    }

    else if (pushR % 3 == 2)
    {
        cout << "단어 개수대로 문장 내림차순 정렬" << endl;
        sort(sentences.rbegin(), sentences.rend());
        for (const auto& p : sentences)
        {
            cout << p.second << "단어 " << p.first << "개" << endl;
        }
    }
}

// 단어 입력
string InputWord()
{
    string word;

    cout << "단어를 입력하세요: ";
    cin >> word;

    return word;
}

// 만약 해당 단어 보유시 해당 단어 색상 변경
void WordColor()
{
    string key = InputWord();

    // key를 소문자로 변환
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    ifstream inFile("data.txt");

    if (!inFile.is_open())
    {
        cerr << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;
    int wordCount = 0;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {

            // 비교를 위해 word도 소문자로 복사해서 변환
            string temp = word;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

            if (temp == key)
            {
                cout << "\033[1;31m" << word << "\033[0m ";
                wordCount++;
            }

            else
            {
                cout << word << " ";
            }
        }
        cout<< endl;
    }

    cout << key << " 단어 개수: " << wordCount << endl;
}

// 명령어 입력
void Choose()
{
    char choose;
    cout << "명령어 입력: ";
    cin >> choose;

    switch (choose)
    {
    case 'c':
        pushC++;
        UpperWord();
        break;

    case 'd':
        pushD++;
        ReverseSentence();
        break;

    case 'e':
        pushE++;
        InsertAt();
        break;

    case 'f':
        pushF++;
        ReverseWord();
        break;

    case 'g':
        pushG++;
        ChangeChar();
        break;

    case 'h':
        WordCount();
        break;

    case 'r':
        pushR++;
        SortPrint();
        break;

    case 's':
        WordColor();
        break;

    case 'q':
        exit(0);
        break;

    default:
        cout << "잘못된 명령어 입니다" << endl;
        break;
    }
}

int main()
{
    StoreFile();
    PrintFile();

    while (true)
    {
        Choose();
    }
}
