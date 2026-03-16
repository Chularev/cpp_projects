# MetaQuotes

Want it in Russian? Scroll down.

По-русски - скролльте вниз.

## C++ programmer test task

Write a class on pure C++ which able to quickly read text logs of enormous size (tens or hundreds MiBs) and output lines which meet simple regexp criteria, at least operators `*` and `?`. A wider range of options is welcome.

- `*` - sequence of any characters of unlimited length;
- `?` - exactly one any symbol.

Following masks must work correctly:

- `*Some*`,
- `*Some`,
- `Some*`,
- `*****Some***`.

There are no restrictions of `*` position in the mask.

The result of the search should be lines that satisfy the mask.

Examples:

1. Mask `*abc*` selects all lines containg `abc`, which starts and ends of any sequence of any characters.
2. Mask `abc*` selects all lines beginning with `abc` and ending with any sequence of any characters.
3. Mask `abc?` selects all lines beginning with `abc` and ending with any one character.
4. Mask `abc` selects all lines which equal to `abc` exactly.

The class will not be expanded and will not be a base class. The only task is scanning and searching text in ANSI (not Unicode) files.

The class must have following public interface:

    class CLogReader
    {
    public:
        CLogReader(...);
        ~CLogReader(...);

        bool Open(...);                       // open file, false if error
        void Close();                         // close file

        bool SetFilter(const char *filter);  // set line filter, false if error
        bool GetNextLine(char *buf,          // select next found line
                         const int bufsize); // buf - buffer, bufsize - max buffer size
                                                // false if EOF or error
    };

Implementation requirements:

- Windows XP or later
- Maximum performance (search results and file contents caching is not required)
- Low memory costs (within reasonable limits)
- It is prohibited to use third-party libraries and STL. You can only use CRT and WinAPI
- It is prohibited to use Windows and C++ exceptions
- The code should be absolutely dead proof and protected from errors.

- The code must be as simple as possible.
- The code must be clean, beautiful and clear.
- Result should be a ready class (`.cpp` + `.h` files) and console example of its usage (open text log file of size of couple of megabytes and select `order*closed`). File and filter must be passed as command line arguments.
- Result should be an example of `.exe` file and Visual Studio project file (all in one archive).


## Тестовое задание С++ программиста

Необходимо написать на чистом С++ класс, умеющий максимально быстро читать текстовые лог-файлы огромных размеров (десятки и сотни мегабайт) и выдавать строки, удовлетворяющие условиям простейшего regexp: (как минимум операторы &#42; и ?, более широкий набор возможностей приветствуется):

cимвол '&#42;' - последовательность любых символов неограниченной длины;
cимвол "?" - один любой символ;
должны корректно отрабатываться маски: &#42;Some&#42;, &#42;Some, Some&#42;, &#42;&#42;&#42;&#42;&#42;Some&#42;&#42;&#42; - нет никаких ограничений на положение &#42; в маске.
Результатом поиска должны быть строки, удовлетворяющие маске.

Например:

1. Маска &#42;abc&#42;  отбирает все строки содержащие abc и начинающиеся и заканчивающиеся любой последовательностью символов.
2. Маска abc&#42;  отбирает все строки начинающиеся с abc и заканчивающиеся любой последовательностью символов.
3. Маска abc?  отбирает все строки начинающиеся с abc и заканчивающиеся любым дополнительным символом.
4. Маска abc   отбирает все строки которые равны этой маске.

Класс не будет расширяться и не будет базовым классом. Единственная задача: сканирование и поиск текстовых ANSI (не unicode) строк в файлах. 

Класс должен иметь следующий публичный интерфейс:

    class CLogReader
    {
    public:
        CLogReader(...);
        ~CLogReader(...);

        bool Open(...);                       // открытие файла, false - ошибка
        void Close();                         // закрытие файла

        bool SetFilter(const char *filter);  // установка фильтра строк, false - ошибка
        bool GetNextLine(char *buf,          // запрос очередной найденной строки, 
                         const int bufsize); // buf - буфер, bufsize - максимальная длина
                                                // false - конец файла или ошибка
    };

Требование к реализации:

Платформа: Windows XP и выше;
Функциональность: максимальная производительность (кэширование результатов поиска и файла не требуется);
Ресурсы: затраты памяти должны быть минимальны (в разумных пределах);
Компоненты: запрещено использование сторонних библиотек (в том числе STL) и компонентов. Разрешено использовать только WinAPI и CRT;
Исключения: нельзя использовать Windows и С++ исключения;
Код должен быть абсолютно «неубиваемый» и защищённым от ошибок.

Требования к оформлению:

Код должен быть максимально простым;
Код должен быть максимально чистым, красивым и понятным;
Результатом должен быть готовый класс (cpp + h файлы) и консольный пример (открыть текстовый файл в пару мегабайт и сделать выборку "order*closed") его использования. Файл и строка выбора должна указываться в аргументах примера;
Результатом должен быть образец работающего exе файла + проект для MS Visual Studio 2005/2008 и т.д. (все в одном архиве).

