#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Node {
    int freq;
    char ch;
    Node *left;
    Node *right;
    Node *next;

    Node(char c, int x) {
        ch = c;
        freq = x;
        left = NULL;
        right = NULL;
        next = NULL;
    }

    Node(int x, Node *l, Node *r) {
        ch = '\0';
        freq = x;
        left = l;
        right = r;
        next = NULL;
    }
};

string filename;


class PriorityQueue {
public:
    void Queue(Node *newN) {
        if (!head || newN->freq < head->freq) {
            newN->next = head;
            head = newN;
        } else {
            Node *current = head;
            Node *previous = current;
            while (current != NULL && newN->freq >= current->freq) {
                previous = current;
                current = current->next;
            }
            newN->next = current;
            previous->next = newN;
        }
    }

    Node *deleteQueue() {
        if (head == NULL) {
            cout << "\n\tQueue is empty." << endl;
            return NULL;
        } else {
            while (head->next != NULL) {
                Node *left = head;
                Node *right = head->next;
                int sum = left->freq + right->freq;
                Node *rootN = new Node(sum, left, right);
                Queue(rootN);
                head = head->next->next;
            }
            Node *temp = head;
            head = NULL;
            return temp;
        }
    }

private:
    Node *head;
};

class Huff {
    int frequency[256];
    string huffmancode[256];
    PriorityQueue Que;

public:
    Huff() {
        root = NULL;
    }

    void huffman(const string file) {
        initialize();
        counter(file);
        root = startQueue();
        system("cls");
        cout << "\n\t+--------------------------------------------------------+" << endl;
        cout << "\n\t" << setw(10) << "Character" << setw(12) << "Frequency" << setw(17) << "ASCII Value" << setw(17) << "Huffman Code" << endl;
        cout << "\n\t+--------------------------------------------------------+" << endl;
        cout<<endl;
        getCode(root, "");
        makebit(file);
    }

    void initialize() {
        for (int i = 0; i < 256; i++) {
            frequency[i] = 0;
        }
    }

    void counter(const string file) {
        ifstream in(file);
        if (in.is_open()) {
            char c;
            while (in.get(c)) {
                cout << c << endl;
                frequency[(int)c]++;
            }
        }
    }

    Node *startQueue() {
        for (int i = 0; i < 256; i++) {
            if (frequency[i] > 0) {
                Node *newN = new Node((char)i, frequency[i]);
                Que.Queue(newN);
            }
        }
        return Que.deleteQueue();
    }

    void getCode(Node *r, string huffcode) {
        if (r == NULL) {
            return;
        } else {
            getCode(r->left, huffcode + "0");
            getCode(r->right, huffcode + "1");
            if (r->left == NULL && r->right == NULL) {
                cout << "\n\t";
                huffmancode[(int)r->ch] = huffcode;
                cout << setw(5) << r->ch << setw(12) << frequency[(int)r->ch] << setw(17) << (int)r->ch << setw(18) << huffcode << endl;
            }
        }
    }

    void makebit(const string& file) {
    ifstream in(file);
    if (in.is_open()) {
        char c;
        string bits;
        while (in.get(c)) {
            bits += huffmancode[(int)c];
        }

        save(bits);
        int bitSize = bits.length();
        int remainder = bitSize % 6;

        if (remainder > 0) {
            for (int i = remainder; i < 6; i++) {
                bits = bits + "1";
            }
        }
        padBits(bits);
    } else {
        cerr << "Error opening file." << endl;
    }
}

void padBits(const string& bits) {
    int bitSize = bits.length();
    int index = 0;
    int count = 0;
    string padded, character;
    while (index < bitSize) {

        count++;
        padded += bits[index];
        if (count == 6) {
            int ascii = stoi(padded, nullptr, 2);
            int add = ascii + 32;
            character += static_cast<char>(add);
            count = 0;
            padded = "";
        }
        index++;
    }
    ofstream out("file.compression");
    if (out.is_open()) {
        out << character;
    }
}


    void save(string bits) {
        ofstream out("save.compression");
        if (out) {
            out << bits.length() << endl;
            for (int i = 0; i < 256; i++) {
                if (frequency[i] > 0) {
                    if ((char)i == 10)
                        out << "NEWLINE" << endl << frequency[i] << endl;
                    else if ((char)i == 32)
                        out << "SPACE" << endl << frequency[i] << endl;
                    else if ((char)i == 9)
                        out << "TAB" << endl << frequency[i] << endl;
                    else
                        out << (char)i << endl << frequency[i] << endl;
                }
            }
        }
    }

private:
    Node *root;
};

int main() {
    Huff hufman;
	printf("\n\t+===============================================================+\n");
	printf("\t|        FINAL PROJECT: FILE COMPRESSION AND DECOMPRESSION      |\n");
	printf("\t|                  DATA STRUCTURES AND ALGORITHMS               |\n");
	printf("\t|                         -HUFFMAN ENCODER-                     |\n");
	printf("\t|                          Rowela Perpetua                      |\n");
	printf("\t|                       Johanna Villahermosa                    |\n");
	printf("\t|                              BSIS-2A                          |\n");
	printf("\t+===============================================================+\n\n");
    printf("\tEnter the name of the\n\tfile to be compressed\t: ");
    cin >> filename;
    const string file = filename+".txt";
    ifstream read(file);
    if (!read.is_open()) {
        cerr << "\n\tError opening file." << endl;
    } else {
        hufman.huffman(file);
    }

    return 0;
}
