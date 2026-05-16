#include <iostream>
#include <cstring>
#include <cstdlib>

// Structura de date ce reflecta schema de obiecte din app.js
struct LeaveEntry {
    long long id;          // IDul ca si timestamp obtinut prin Date.now()
    char date[11];         // Format: YYYY-MM-DD
    char type[8];          // "earned" or "used"
    char category[12];     // "liber", "exercitiu", "recompensa"
    double amount;         // Numarul de zile
    char note[128];        // Optional: comentariu utilizator
    
    LeaveEntry* next;      // Linked list reference pointer
};


LeaveEntry* head = nullptr;


void addNode(long long id, const char* date, const char* type, const char* cat, double amount, const char* note) {
    LeaveEntry* newEntry = new LeaveEntry();
    newEntry->id = id;
    std::strncpy(newEntry->date, date, 11);
    std::strncpy(newEntry->type, type, 8);
    std::strncpy(newEntry->category, cat, 12);
    newEntry->amount = amount;
    std::strncpy(newEntry->note, note, 128);
    
    newEntry->next = head;
    head = newEntry;
}

// REST Route Simulation: GET /api/entries
void handleGetEntries() {
    std::cout << "\nHTTP/1.1 200 OK\nContent-Type: application/json\n\n";
    if (!head) {
        std::cout << "[]\n(No entries found in Wasm Memory Stack)\n";
        return;
    }
    
    LeaveEntry* current = head;
    while (current != nullptr) {
        std::cout << " -> [ID: " << current->id << "] " 
                  << current->date << " | " 
                  << current->type << " | "
                  << (std::strlen(current->category) > 0 ? current->category : "utilizata") << " | "
                  << current->amount << " zile (" << current->note << ")\n";
        current = current->next;
    }
}

// REST Route Simulation: POST /api/entries
void handlePostEntry() {
    char date[11], type[8], cat[12] = "", note[128] = "";
    double amount;
    long long id = 12345678; //Timestamp de test care sa mimeze un ID

    std::cout << "\n--- POST /api/entries (Create Resource) ---\n";
    std::cout << "Enter Type ('earned' / 'used'): "; std::cin >> type;
    std::cout << "Enter Date (YYYY-MM-DD): "; std::cin >> date;
    
    if (std::strcmp(type, "earned") == 0) {
        std::cout << "Enter Category ('liber' [2], 'exercitiu' [1], 'recompensa' [1]): ";
        std::cin >> cat;
        if (std::strcmp(cat, "liber") == 0) amount = 2.0;
        else if (std::strcmp(cat, "exercitiu") == 0 || std::strcmp(cat, "recompensa") == 0) amount = 1.0;
        else { std::cout << "Invalid category!\n"; return; }
    } else {
        std::cout << "Enter Amount of used days: "; std::cin >> amount;
    }
    
    std::cin.ignore(); // Clear newline buffer
    std::cout << "Enter Details/Note: "; std::cin.getline(note, 128);

    addNode(id, date, type, cat, amount, note);
    std::cout << "\nHTTP/1.1 201 Created\nResource added successfully to Linked List!\n";
}

// REST Route Simulation: GET /api/balance
void handleGetBalance() {
    double balance = 0.0;
    LeaveEntry* current = head;
    while (current != nullptr) {
        if (std::strcmp(current->type, "earned") == 0) balance += current->amount;
        else balance -= current->amount;
        current = current->next;
    }
    std::cout << "\nHTTP/1.1 200 OK\n";
    std::cout << "Computed Free Day Balance: " << balance << " days\n";
}

// JS va apela aceasta functie direct si va merge pe optiunea aleasa aici
extern "C" {
    void addEntryFromJS(long long id, const char* date, const char* type, const char* cat, double amount, const char* note) {
        addNode(id, date, type, cat, amount, note);
    }

    void clearWasmList() {
        LeaveEntry* current = head;
        while (current != nullptr) {
            LeaveEntry* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void routeRESTCommand(int option) {
        switch (option) {
            case 1: handleGetEntries(); break;
            case 2: handlePostEntry(); break;
            case 3: handleGetBalance(); break;
            default: std::cout << "404 Error: Request route match failed.\n";
        }
    }
}

int main() {
    return 0;
}