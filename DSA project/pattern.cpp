//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// Helper function to generate character sequences like "a", "ab", "abc", etc.
//// k: Represents the Nth character (1 for 'a', 2 for 'b', etc.)
//string getCharSequence(int k) {
//    if (k == 0) { // Base case for the character sequence builder
//        return "";
//    }
//    // Recursively builds the string: "abc" is "ab" + 'c'
//    return getCharSequence(k - 1) + (char)('a' + k - 1);
//}
//
//// Recursive function to generate the full pattern
//// n: The input number (1 <= n <= 26)
//string generatePattern(int n) {
//    if (n == 1) {
//        // Base case: For n=1, the pattern is just "a"
//        return getCharSequence(1);
//    }
//
//    // Recursive step:
//    // 1. Get the complete pattern block for (n-1)
//    string prev_pattern_block = generatePattern(n - 1);
//
//    // 2. Get the character sequence for the current level 'n' (e.g., "ab" for n=2)
//    string current_level_char_seq = getCharSequence(n);
//
//    // 3. Get the character sequence for the previous level 'n-1' (e.g., "a" for n=2)
//    string prev_level_char_seq = getCharSequence(n - 1);
//
//    // 4. Compose the middle line of the current pattern
//    //    It's (char sequence for n-1) + " " + (char sequence for n)
//    string middle_line = prev_level_char_seq + " " + current_level_char_seq;
//
//    // 5. Compose the bottom line of the current pattern
//    //    It's (char sequence for n-1) + " " + (char sequence for n) + " " + (char sequence for n-1)
//    string bottom_line = prev_level_char_seq + " " + current_level_char_seq + " " + prev_level_char_seq;
//
//    // 6. Combine all parts with newlines
//    return prev_pattern_block + "\n" + middle_line + "\n" + bottom_line;
//}
//
//
//int main() {
//    int n_input;
//    cout << "Enter a number (1-26): ";
//    cin >> n_input;
//
//    if (n_input >= 1 && n_input <= 26) {
//        cout << "Pattern for n = " << n_input << ":" << endl;
//        cout << generatePattern(n_input) << endl;
//    } else {
//        cout << "Invalid input. Please enter a number between 1 and 26." << endl;
//    }
//
//    return 0;
//}
