#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для представления автора
typedef struct {
    int id;
    char name[100];
    char nationality[50];
} Author;

// Структура для представления книги
typedef struct {
    int id;
    char title[100];
    Author author;
    int year;
} Book;

// Структура для представления читателя
typedef struct {
    int id;
    char name[100];
    char address[200];
} Reader;


// Структура для представления заказа
typedef struct {
    int id;
    Book book;
    Reader reader;
    Librarian librarian;
    char order_date[11]; // формат: YYYY-MM-DD
} Order;

// Структура для представления библиотекаря
typedef struct {
    int id;
    char name[100];
    char position[50];
} Librarian;

