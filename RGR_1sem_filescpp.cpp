#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

int main() {
    // ����� ��������� ������� �� UTF-16
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    // �������� ������ ��� ������ � ������
    FILE* FirstFile_F = _wfopen(L"source1.txt", L"rt, ccs=UTF-8");        //�������� 1-�� ����� F � 1-� �������� �������
    FILE* SecondFile_G = _wfopen(L"source2.txt", L"rt, ccs=UTF-8");       //�������� 2-�� ����� G �� 2-� �������� ������� 
    FILE* TotalFile_Q = _wfopen(L"NewSource.txt", L"wt, ccs=UTF-8");      //�������� ����� Q ��� ������ ������ ������

    // �������� ������ �� ��������
    if (FirstFile_F == NULL)
    {
        std::wcout << L"������ � �������� 1-�� ����� F" << std::endl;
        return 1;
    }
    if (SecondFile_G == NULL)
    {
        std::wcout << L"������ � �������� 2-�� ����� G" << std::endl;
        return 1;
    }
    if (TotalFile_Q == NULL)
    {
        std::wcout << L"������ � �������� ������ �����" << std::endl;
        return 1;
    }

    // ������������� ���������� �������� ��� ������ ����
    wchar_t First_Arr[1000], Second_Arr[1000], TotalFile_Q_Text[2000];
    int index = 0;

    // ������� ������, ���������� �������� TotalFileQ_Text
    ZeroMemory(TotalFile_Q_Text, sizeof(TotalFile_Q_Text));

    // ����, ������ �������� ����� �� ���� ������ ������������ � ����� ����, ���� � ����� �� �������� ������ �� ���������� �����
    while (fwscanf(FirstFile_F, L"%s", First_Arr) != EOF && fwscanf(SecondFile_G, L"%s", Second_Arr) != EOF)
    {
        fwprintf(TotalFile_Q, L"%s ", First_Arr);
        fwprintf(TotalFile_Q, L"%s ", Second_Arr);

        // ������ ���� �� ���� �������� � TotalFile_Q_Text ����������
        int len1 = lstrlenW(First_Arr);
        int len2 = lstrlenW(Second_Arr);

        // ����� ������������ ������ ���� � ����� ������
        for (int i = 0; i < len1; i++)
        {
            TotalFile_Q_Text[index] = First_Arr[i];
            index++;
        }
        TotalFile_Q_Text[index] = ' ';
        index++;
        for (int i = 0; i < len2; i++)
        {
            TotalFile_Q_Text[index] = Second_Arr[i];
            index++;
        }
        TotalFile_Q_Text[index] = ' '; // ��������� ������ ����� �������
        index++;
    }
    std::wcout << L"\n����� F � G ���� ������� ���������� � ���� Q!\n" << std::endl;
    std::wcout << L"������� ����� �� ����� Q:" << std::endl;
    std::wcout << L"\n" << TotalFile_Q_Text << std::endl;

    //�������� ���� ������
    _fcloseall();
    return 0;
}