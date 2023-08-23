#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
    public:
        string ISBN;
        string title;
        string author;
        int copyright_date;
        bool checked_out;
        enum Genre {fiction, nonfiction, periodical, biography, children};
        Genre genre;
    public:
        Book(string i, string t, string a, int c, bool co, Genre g) : ISBN{i}, title{t}, author{a}, copyright_date{c},
            checked_out{co}, genre{g} {}
        string get_ISBN() const { return ISBN; }
        string get_title() const { return title; }
        string get_author() const { return author; }
        int get_copyright_date() const { return copyright_date; }
        bool get_checked_out() const { return checked_out; }
        Genre get_genre() const { return genre; }
        void check_out() { checked_out = true; }
        void check_in() { checked_out = false; }
        friend bool operator==(const Book& b1, const Book& b2) {
            return b1.ISBN == b2.ISBN;
        }
        friend bool operator!=(const Book& b1, const Book& b2) {
            return !(b1 == b2);
        }
        friend ostream& operator<<(ostream& os, const Book& b) {
            os << "Title: " << b.title << endl;
            os << "Author: " << b.author << endl;
            os << "ISBN: " << b.ISBN << endl;
            os << "Genre: ";
            switch(b.genre) {
                case fiction:
                    os << "Fiction";
                    break;
                case nonfiction:
                    os << "Non-fiction";
                    break;
                case periodical:
                    os << "Periodical";
                    break;
                case biography:
                    os << "Biography";
                    break;
                case children:
                    os << "Children";
                    break;
            }
            os << endl;
            return os;
        }
};

class Patron {
    public:
        string user_name;
        string card_number;
        int owed_fees;
    public:
        Patron(string u, string c) : user_name{u}, card_number{c}, owed_fees{0} {}
        string get_user_name() const { return user_name; }
        string get_card_number() const { return card_number; }
        int get_owed_fees() const { return owed_fees; }
        bool owes_fees() const { return owed_fees > 0; }
        void set_owed_fees(int f) { owed_fees = f; }
};

class Transaction {
    public:
        Book book;
        Patron patron;
        enum Activity {check_out, check_in};
        Activity activity;
    public:
        Transaction(Book b, Patron p, Activity a) : book{b}, patron{p}, activity{a} {}
};

class Library {
    public:
        vector<Book> books;
        vector<Patron> patrons;
        vector<Transaction> transactions;
    public:
        void add_book(Book b) { books.push_back(b); }

        void check_out_book(Book b, Patron p) {
            if (find(books.begin(), books.end(), b) == books.end()) {
                cout << "Error: book not found in library" << endl;
                return;
            }

            if (p.owes_fees()) {
                cout << "Error: patron owes fees" << endl;
                return;
            }

            b.check_out();
            transactions.push_back(Transaction(b, p, Transaction::check_out));
            cout << "Book checked out successfully" << endl;
        }

        vector<string> patrons_owing_fees() {
            vector<string> owing_patrons;
            for (Patron p : patrons) {
                if (p.owes_fees()) {
                    owing_patrons.push_back(p.get_user_name());
                }
            }
            return owing_patrons;
        }
};

int main() {
    // Example usage
    Book b1("1234567890", "The Great Gatsby", "F. Scott Fitzgerald", 1925, false, Book::fiction);
    Book b2("0987654321", "To Kill a Mockingbird", "Harper Lee", 1960, false, Book::fiction);
    Patron p1("Alice", "0001");
    Patron p2("Bob", "0002");

    Library lib;
    lib.add_book(b1);
    lib.add_book(b2);
    lib.check_out_book(b1, p1);
    lib.check_out_book(b2, p2);

    vector<string> owing_patrons = lib.patrons_owing_fees();
    if (owing_patrons.empty()) {
        cout << "No patrons owe fees" << endl;
    } else {
        cout << "Patrons owing fees:" << endl;
        for (string s : owing_patrons) {
            cout << s << endl;
        }
    }

    return 0;
}
//done by 
//names                       reg number
//Rukundo olivier             222014827
//UMUHOZA KAMANA Nadine       222013252
