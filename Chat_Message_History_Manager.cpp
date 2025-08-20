#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

struct Message {
    string text;
    string timestamp;
};

// Get current timestamp
string getTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday << " "
       << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min << ":"
       << setw(2) << setfill('0') << ltm->tm_sec;
    return ss.str();
}

class ChatManager {
private:
    queue<Message> incoming;
    stack<Message> undoStack;
    stack<Message> redoStack;
    vector<Message> history;

public:
    void sendMessage(string text) {
        Message msg = {text, getTimestamp()};
        incoming.push(msg);
        undoStack.push(msg);
        history.push_back(msg);
        cout << "Message Sent: " << msg.text << " [" << msg.timestamp << "]" << endl;
    }

    void undoMessage() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        Message msg = undoStack.top();
        undoStack.pop();
        redoStack.push(msg);
        cout << "Undo: " << msg.text << endl;
    }

    void redoMessage() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }
        Message msg = redoStack.top();
        redoStack.pop();
        undoStack.push(msg);
        cout << "Redo: " << msg.text << endl;
    }

    void exportCSV(const string &filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }
        file << "Message,Timestamp\n";
        for (auto &msg : history) {
            file << "\"" << msg.text << "\",\"" << msg.timestamp << "\"\n";
        }
        file.close();
        cout << "History exported to " << filename << endl;
    }
};

int main() {
    ChatManager chat;
    int choice;
    string text;

    while (true) {
        cout << "\n1. Send Message\n2. Undo\n3. Redo\n4. Export CSV\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter message: ";
                getline(cin, text);
                chat.sendMessage(text);
                break;
            case 2:
                chat.undoMessage();
                break;
            case 3:
                chat.redoMessage();
                break;
            case 4:
                chat.exportCSV("data/messages.csv");
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
