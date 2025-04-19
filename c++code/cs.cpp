#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

const vector<string> week = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int M, N, P;
vector<string> names;
map<string, int> name2id;

struct Statement {
    int speaker; // id
    int type; // 0: "I am guilty", 1: "I am not guilty", 2: "X is guilty", 3: "X is not guilty", 4: "Today is XXX", 5: irrelevant
    int target; // id for type 2/3, -1 otherwise
    int day; // 0~6 for type 4, -1 otherwise
};

vector<Statement> statements;

int get_day(const string& s) {
    for (int i = 0; i < 7; ++i)
        if (s == week[i]) return i;
    return -1;
}

Statement parse_statement(const string& speaker, const string& content) {
    Statement st;
    st.speaker = name2id[speaker];
    st.type = 5; // irrelevant by default
    st.target = -1;
    st.day = -1;
    if (content == "I am guilty.") {
        st.type = 0;
    } else if (content == "I am not guilty.") {
        st.type = 1;
    } else if (content.substr(0, 6) == "Today ") {
        // Today is XXX.
        if (content.size() >= 13 && content.substr(6, 3) == "is ") {
            string day = content.substr(9, content.size() - 10); // remove "Today is " and "."
            int d = get_day(day);
            if (d != -1) {
                st.type = 4;
                st.day = d;
            }
        }
    } else {
        // Try "XXX is guilty." or "XXX is not guilty."
        for (int i = 0; i < M; ++i) {
            string prefix = names[i] + " is guilty.";
            if (content == prefix) {
                st.type = 2;
                st.target = i;
                break;
            }
            prefix = names[i] + " is not guilty.";
            if (content == prefix) {
                st.type = 3;
                st.target = i;
                break;
            }
        }
    }
    return st;
}

bool check(int criminal, int liar_mask, int today) {
    // liar_mask: bitmask, 1 means liar
    for (const auto& st : statements) {
        bool is_liar = (liar_mask >> st.speaker) & 1;
        bool truth;
        switch (st.type) {
            case 0: // I am guilty.
                truth = (st.speaker == criminal);
                break;
            case 1: // I am not guilty.
                truth = (st.speaker != criminal);
                break;
            case 2: // XXX is guilty.
                truth = (st.target == criminal);
                break;
            case 3: // XXX is not guilty.
                truth = (st.target != criminal);
                break;
            case 4: // Today is XXX.
                truth = (st.day == today);
                break;
            case 5: // irrelevant
                continue;
        }
        if (is_liar) truth = !truth;
        if (!truth) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> M >> N >> P;
    names.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> names[i];
        name2id[names[i]] = i;
    }
    string line;
    getline(cin, line); // consume newline
    for (int i = 0; i < P; ++i) {
        getline(cin, line);
        int pos = line.find(": ");
        string speaker = line.substr(0, pos);
        string content = line.substr(pos + 2);
        statements.push_back(parse_statement(speaker, content));
    }

    set<int> possible_criminals;
    for (int criminal = 0; criminal < M; ++criminal) {
        for (int today = 0; today < 7; ++today) {
            // enumerate all liar combinations
            vector<int> ids(M);
            for (int i = 0; i < M; ++i) ids[i] = i;
            vector<int> liar_mask_list;
            // generate all combinations of N liars
            vector<int> mask(M, 0);
            for (int i = 0; i < N; ++i) mask[i] = 1;
            do {
                int liar_mask = 0;
                for (int i = 0; i < M; ++i)
                    if (mask[i]) liar_mask |= (1 << i);
                if (check(criminal, liar_mask, today)) {
                    possible_criminals.insert(criminal);
                    break; // only need one valid liar assignment for this criminal
                }
            } while (prev_permutation(mask.begin(), mask.end()));
        }
    }
    if (possible_criminals.size() == 0) {
        cout << "Impossible" << endl;
    } else if (possible_criminals.size() == 1) {
        cout << names[*possible_criminals.begin()] << endl;
    } else {
        cout << "Cannot Determine" << endl;
    }
    return 0;
}