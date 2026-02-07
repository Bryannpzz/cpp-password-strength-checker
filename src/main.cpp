#include <iostream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

bool hasUpper(const string& s) {
    for (char c : s) if (isupper(static_cast<unsigned char>(c))) return true;
    return false;
}

bool hasLower(const string& s) {
    for (char c : s) if (islower(static_cast<unsigned char>(c))) return true;
    return false;
}

bool hasDigit(const string& s) {
    for (char c : s) if (isdigit(static_cast<unsigned char>(c))) return true;
    return false;
}

bool hasSymbol(const string& s) {
    for (char c : s) {
        if (!isalnum(static_cast<unsigned char>(c)) && !isspace(static_cast<unsigned char>(c))) return true;
    }
    return false;
}

// Very simple pattern checks (not perfect, but good for a student project)
bool containsCommonPattern(const string& s) {
    string lower;
    lower.reserve(s.size());
    for (char c : s) lower += static_cast<char>(tolower(static_cast<unsigned char>(c)));

    // common weak patterns
    if (lower.find("password") != string::npos) return true;
    if (lower.find("1234") != string::npos) return true;
    if (lower.find("qwerty") != string::npos) return true;
    if (lower == "admin" || lower == "letmein") return true;

    return false;
}

int scorePassword(const string& pwd) {
    int score = 0;

    // Length scoring
    if (pwd.length() >= 8) score += 2;
    if (pwd.length() >= 12) score += 2;
    if (pwd.length() >= 16) score += 1;

    // Variety scoring
    if (hasLower(pwd)) score += 1;
    if (hasUpper(pwd)) score += 1;
    if (hasDigit(pwd)) score += 1;
    if (hasSymbol(pwd)) score += 2;

    // Penalties
    if (pwd.length() < 8) score -= 2;
    if (containsCommonPattern(pwd)) score -= 3;

    return score;
}

string strengthLabel(int score) {
    if (score <= 2) return "WEAK";
    if (score <= 6) return "MEDIUM";
    return "STRONG";
}

void printFeedback(const string& pwd) {
    cout << "\nWhy this score?\n";
    cout << "- Length: " << pwd.length() << " characters\n";

    cout << "- Has lowercase: " << (hasLower(pwd) ? "yes" : "no") << "\n";
    cout << "- Has uppercase: " << (hasUpper(pwd) ? "yes" : "no") << "\n";
    cout << "- Has digits:    " << (hasDigit(pwd) ? "yes" : "no") << "\n";
    cout << "- Has symbols:   " << (hasSymbol(pwd) ? "yes" : "no") << "\n";

    if (pwd.length() < 8) {
        cout << "- Weakness: too short (try 12+)\n";
    }
    if (containsCommonPattern(pwd)) {
        cout << "- Weakness: contains a common pattern (avoid predictable words/number sequences)\n";
    }

    cout << "\nQuick tips:\n";
    cout << "- Use 12-16+ characters\n";
    cout << "- Mix upper/lower + numbers + symbols\n";
    cout << "- Avoid common words like 'password' and simple sequences like '1234'\n";
}

int main() {
    cout << "=== C++ Password Strength Checker ===\n";
    cout << "(This tool uses basic rules and does not store your password.)\n\n";

    while (true) {
        string pwd = readLine("Enter a password to check (or type EXIT to quit): ");

        // allow quit
        string tmp;
        tmp.reserve(pwd.size());
        for (char c : pwd) tmp += static_cast<char>(toupper(static_cast<unsigned char>(c)));
        if (tmp == "EXIT") {
            cout << "Goodbye!\n";
            break;
        }

        if (pwd.empty()) {
            cout << "Please enter something.\n\n";
            continue;
        }

        int score = scorePassword(pwd);
        string label = strengthLabel(score);

        cout << "\nResult: " << label << " (score: " << score << ")\n";
        printFeedback(pwd);
        cout << "\n-------------------------------------\n\n";
    }

    return 0;
}
