#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

int main() {
    // смена кодировки консоли на UTF-16
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    // открытие файлов для чтения и записи
    FILE* FirstFile_F = _wfopen(L"source1.txt", L"rt, ccs=UTF-8");        //открытие 1-го файла F с 1-м исходным текстом
    FILE* SecondFile_G = _wfopen(L"source2.txt", L"rt, ccs=UTF-8");       //открытие 2-го файла G со 2-м исходным текстом 
    FILE* TotalFile_Q = _wfopen(L"NewSource.txt", L"wt, ccs=UTF-8");      //открытие файла Q для записи нового текста

    // проверка файлов на открытие
    if (FirstFile_F == NULL)
    {
        std::wcout << L"Ошибка в открытии 1-го файла F" << std::endl;
        return 1;
    }
    if (SecondFile_G == NULL)
    {
        std::wcout << L"Ошибка в открытии 2-го файла G" << std::endl;
        return 1;
    }
    if (TotalFile_Q == NULL)
    {
        std::wcout << L"Ошибка в открытии общего файла" << std::endl;
        return 1;
    }

    // инициализация символьных массивов для записи слов
    wchar_t First_Arr[1000], Second_Arr[1000], TotalFile_Q_Text[2000];
    int index = 0;

    // очистка памяти, занимаемой массивом TotalFileQ_Text
    ZeroMemory(TotalFile_Q_Text, sizeof(TotalFile_Q_Text));

    // цикл, внутри которого слова из двух файлов записываются в общий файл, пока в одном из исходных файлов не закончатся слова
    while (fwscanf(FirstFile_F, L"%s", First_Arr) != EOF && fwscanf(SecondFile_G, L"%s", Second_Arr) != EOF)
    {
        fwprintf(TotalFile_Q, L"%s ", First_Arr);
        fwprintf(TotalFile_Q, L"%s ", Second_Arr);

        // запись слов из двух массивов в TotalFile_Q_Text поочередно
        int len1 = lstrlenW(First_Arr);
        int len2 = lstrlenW(Second_Arr);

        // циклы посимвольной записи слов в общий массив
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
        TotalFile_Q_Text[index] = ' '; // добавляем пробел между словами
        index++;
    }
    std::wcout << L"\nФайлы F и G были успешно объединены в файл Q!\n" << std::endl;
    std::wcout << L"Готовый текст из файла Q:" << std::endl;
    std::wcout << L"\n" << TotalFile_Q_Text << std::endl;

    //закрытие всех файлов
    _fcloseall();
    return 0;
}