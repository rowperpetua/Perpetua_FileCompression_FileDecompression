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
class PriorityQueue {
public:
    PriorityQueue(){
        head=NULL;
    }
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
            cout<<head->freq;
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

    void huffman() {
        initialize();
        int sizeBit=counter();
        if(sizeBit==0){
            return;
        }else{
            root = startQueue();
            cout << setw(10) << "Character" << setw(12) << "Frequency" << setw(12) << "ASCII Value" << setw(20) << "Huffman Code" << endl;
            getCode(root, "");
            string trav=retrieve(sizeBit);
            getChar(root,trav);
        }

    }

    void initialize() {
        for (int i = 0; i < 256; i++) {
            frequency[i] = 0;
        }
    }

    int counter() {
        const string SAVE_FILE = "save.compression";
        ifstream in(SAVE_FILE);
         int sizeBit;
        if (in.is_open()) {

            in>>sizeBit;
            string line;

            int freq;
            while (in>>line>>freq) {
                if(line=="SPACE"){
                    line=" ";
                }else if(line=="NEWLINE"){
                    line="\n";
                }else if(line=="TAB"){
                    line="\t";
                }
                frequency[(int)line[0]]=freq;
                cout<<line<<endl<<freq<<endl;
            }
            return sizeBit;
        }
    return 0;
    }

    Node *startQueue() {
        for (int i = 0; i < 256; i++) {
            if (frequency[i] > 0) {
                Node *newN = new Node((char)i, frequency[i]);
                Que.Queue(newN);
            }
        }
        Node *temp=Que.deleteQueue();
        return temp;
    }

    void getCode(Node *r, string huffcode) {
    Node *temp=r;

    if (temp == NULL) {
            return;
        } else {
            getCode(temp->left, huffcode + "0");
            getCode(temp->right, huffcode + "1");
            if (temp->left == NULL && temp->right == NULL) {
                cout << setw(10) << temp->ch << setw(12) << frequency[(int)temp->ch] << setw(12) << (int)temp->ch << setw(20) << huffcode << endl;
            }
        }
    }

    string retrieve(int sizeBit){
    const string COMPRESSED_FILE = "file.compression";
    ifstream fp(COMPRESSED_FILE);
    string BITS, ORIG;
    if(fp.is_open()){

        char c;
        while(fp.get(c)){
            int ch=(int)c;
            int origCH=ch-32;
            string binary = "";
            if (origCH == 0) {
                binary="000000";
            }else{
                while (origCH > 0) {
                int remainder = origCH % 2;
                binary = static_cast<char>('0' + remainder) + binary;
                origCH /= 2;
                }

                while (binary.length() < 6) {
                    binary = '0' + binary;
                }
            }

            BITS+=binary;
            binary="";
        }
        int index=0;
        while(index<sizeBit){
            ORIG+=BITS[index];
            index++;
        }
        cout<<ORIG<<endl;
        }
        system("cls");
	printf("\n\t+===============================================================+\n");
	printf("\t|        FINAL PROJECT: FILE COMPRESSION AND DECOMPRESSION      |\n");
	printf("\t|                  DATA STRUCTURES AND ALGORITHMS               |\n");
	printf("\t|                         -HUFFMAN ENCODER-                     |\n");
	printf("\t|                          Rowela Perpetua                      |\n");
	printf("\t|                       Johanna Villahermosa                    |\n");
	printf("\t|                              BSIS-2A                          |\n");
	printf("\t+===============================================================+\n\n");
    printf("\tDecompressed File: ");
        cout << "\n\n\n";
        return ORIG;
    }

    void getChar(Node *r, string& trav){
    Node *temp=r;
    if(temp!=NULL){
        for(char c: trav){
            if(c=='1'){
                temp=temp->right;
            }else if(c=='0'){
                temp=temp->left;
            }
            if(temp->left==NULL && temp->right==NULL){
                cout<<temp->ch;
                temp=r;
            }
        }
    }
    }


private:
    Node *root;
};

int main() {
    Huff hufman;
    hufman.huffman();

return 0;
}
