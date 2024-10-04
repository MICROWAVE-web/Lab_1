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

// Инициализация автора
Author createAuthor(int id, const char* name, const char* nationality) {
    Author author;
    author.id = id;
    strcpy(author.name, name);
    strcpy(author.nationality, nationality);
    return author;
}

// Инициализация книги
Book createBook(int id, const char* title, Author author, int year) {
    Book book;
    book.id = id;
    strcpy(book.title, title);
    book.author = author;
    book.year = year;
    return book;
}

// Инициализация читателя
Reader createReader(int id, const char* name, const char* address) {
    Reader reader;
    reader.id = id;
    strcpy(reader.name, name);
    strcpy(reader.address, address);
    return reader;
}

// Инициализация Заказа
Order createOrder(int id, Book book, Reader reader, Librarian librarian
        , const char* order_date) {
    Order order;
    order.id = id;
    order.book = book;
    order.reader = reader;
    order.librarian = librarian;
    strcpy(order.order_date, order_date);
    return order;
}

// Инициализация библиотекаря
Librarian createLibrarian(int id, const char* name, const char* position) {
    Librarian librarian;
    librarian.id = id;
    strcpy(librarian.name, name);
    strcpy(librarian.position, position);
    return librarian;
}


