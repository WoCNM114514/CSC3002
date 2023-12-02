/* P1: 
 * File: stringmap.cpp
 * ----------------------
 * Implementation for the stringmap class.
 * 
 * @version 2014/10/08
 * - removed 'using namespace' statement
 */


#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <iomanip>
#include <iostream>
#include <string>
//include "CSC3002OJActive/assignment5/tokenscanner.h" // for OJ test
//include "CSC3002OJActive/assignment5/stringmap.h" // for OJ test
#include "tokenscanner.h" // for local test
#include "stringmap.h" // for local test
using namespace std;

TokenScanner::TokenScanner() {
    initScanner();
    setInput("");
}

TokenScanner::TokenScanner(std::string str) {
    initScanner();
    setInput(str);
}

TokenScanner::TokenScanner(std::istream & infile) {
    initScanner();
    setInput(infile);
}

TokenScanner::~TokenScanner() {
    if (stringInputFlag) delete isp;
}

void TokenScanner::setInput(std::string str) {
    stringInputFlag = true;
    buffer = str;
    isp = new std::istringstream(buffer);
    savedTokens = NULL;
}

void TokenScanner::setInput(std::istream & infile) {
    stringInputFlag = false;
    isp = &infile;
    savedTokens = NULL;
}

bool TokenScanner::hasMoreTokens() {
    std::string token = nextToken();
    saveToken(token);
    return (token != "");
}

std::string TokenScanner::nextToken() {
    if (savedTokens != NULL) {
        StringCell *cp = savedTokens;
        std::string token = cp->str;
        savedTokens = cp->link;
        delete cp;
        return token;
    }
    while (true) {
        if (ignoreWhitespaceFlag) skipSpaces();
        int ch = isp->get();
        if (ch == '/' && ignoreCommentsFlag) {
            ch = isp->get();
            if (ch == '/') {
                while (true) {
                    ch = isp->get();
                    if (ch == '\n' || ch == '\r' || ch == EOF) break;
                }
                continue;
            } else if (ch == '*') {
                int prev = EOF;
                while (true) {
                    ch = isp->get();
                    if (ch == EOF || (prev == '*' && ch == '/')) break;
                    prev = ch;
                }
                continue;
            }
            if (ch != EOF) isp->unget();
            ch = '/';
        }
        if (ch == EOF) return "";
        if ((ch == '"' || ch == '\'') && scanStringsFlag) {
            isp->unget();
            return scanString();
        }
        if (isdigit(ch) && scanNumbersFlag) {
            isp->unget();
            return scanNumber();
        }
        if (isWordCharacter(ch)) {
            isp->unget();
            return scanWord();
        }
        std::string op = std::string(1, ch);
        while (isOperatorPrefix(op)) {
            ch = isp->get();
            if (ch == EOF) break;
            op += ch;
        }
        while (op.length() > 1 && !isOperator(op)) {
            isp->unget();
            op.erase(op.length() - 1, 1);
        }
        return op;
    }
}

void TokenScanner::saveToken(std::string token) {
    StringCell *cp = new StringCell;
    cp->str = token;
    cp->link = savedTokens;
    savedTokens = cp;
}

void TokenScanner::ignoreWhitespace() {
    ignoreWhitespaceFlag = true;
}

void TokenScanner::ignoreComments() {
    ignoreCommentsFlag = true;
}

void TokenScanner::scanNumbers() {
    scanNumbersFlag = true;
}

void TokenScanner::scanStrings() {
    scanStringsFlag = true;
}

void TokenScanner::addWordCharacters(std::string str) {
    wordChars += str;
}

void TokenScanner::addOperator(std::string op) {
    StringCell *cp = new StringCell;
    cp->str = op;
    cp->link = operators;
    operators = cp;
}

int TokenScanner::getPosition() const {
    if (savedTokens == NULL) {
        return int(isp->tellg());
    } else {
        return int(isp->tellg()) - savedTokens->str.length();
    }
}

bool TokenScanner::isWordCharacter(char ch) const {
    return isalnum(ch) || wordChars.find(ch) != std::string::npos;
}

void TokenScanner::verifyToken(std::string expected) {
    std::string token = nextToken();
    if (token != expected) {
        error("TokenScanner::verifyToken: Found \"" + token + "\"" +
              " when expecting \"" + expected + "\"");
    }
}

TokenType TokenScanner::getTokenType(std::string token) const {
    if (token == "") return TokenType(EOF);
    char ch = token[0];
    if (isspace(ch)) return SEPARATOR;
    if (ch == '"' || (ch == '\'' && token.length() > 1)) return STRING;
    if (isdigit(ch)) return NUMBER;
    if (isWordCharacter(ch)) return WORD;
    return OPERATOR;
};

std::string TokenScanner::getStringValue(std::string token) const {
    std::string str = "";
    int start = 0;
    int finish = token.length();
    if (finish > 1 && (token[0] == '"' || token[0] == '\'')) {
        start = 1;
        finish--;
    }
    for (int i = start; i < finish; i++) {
        char ch = token[i];
        if (ch == '\\') {
            ch = token[++i];
            if (isdigit(ch) || ch == 'x') {
                int base = 8;
                if (ch == 'x') {
                    base = 16;
                    i++;
                }
                int result = 0;
                int digit = 0;
                while (i < finish) {
                    ch = token[i];
                    if (isdigit(ch)) {
                        digit = ch - '0';
                    } else if (isalpha(ch)) {
                        digit = toupper(ch) - 'A' + 10;
                    } else {
                        digit = base;
                    }
                    if (digit >= base) break;
                    result = base * result + digit;
                    i++;
                }
                ch = char(result);
                i--;
            } else {
                switch (ch) {
                case 'a': ch = '\a'; break;
                case 'b': ch = '\b'; break;
                case 'f': ch = '\f'; break;
                case 'n': ch = '\n'; break;
                case 'r': ch = '\r'; break;
                case 't': ch = '\t'; break;
                case 'v': ch = '\v'; break;
                case '"': ch = '"'; break;
                case '\'': ch = '\''; break;
                case '\\': ch = '\\'; break;
                }
            }
        }
        str += ch;
    }
    return str;
}

int TokenScanner::getChar() {
    return isp->get();
}

void TokenScanner::ungetChar(int) {
    isp->unget();
}

/* Private methods */

void TokenScanner::initScanner() {
    ignoreWhitespaceFlag = false;
    ignoreCommentsFlag = false;
    scanNumbersFlag = false;
    scanStringsFlag = false;
    operators = NULL;
}

/*
 * Implementation notes: skipSpaces
 * --------------------------------
 * Advances the position of the scanner until the current character is
 * not a whitespace character.
 */

void TokenScanner::skipSpaces() {
    while (true) {
        int ch = isp->get();
        if (ch == EOF) return;
        if (!isspace(ch)) {
            isp->unget();
            return;
        }
    }
}

/*
 * Implementation notes: scanWord
 * ------------------------------
 * Reads characters until the scanner reaches the end of a sequence
 * of word characters.
 */

std::string TokenScanner::scanWord() {
    std::string token = "";
    while (true) {
        int ch = isp->get();
        if (ch == EOF) break;
        if (!isWordCharacter(ch)) {
            isp->unget();
            break;
        }
        token += char(ch);
    }
    return token;
}

/*
 * Implementation notes: scanNumber
 * --------------------------------
 * Reads characters until the scanner reaches the end of a legal number.
 * The function operates by simulating what computer scientists
 * call a finite-state machine.  The program uses the variable
 * <code>state</code> to record the history of the process and
 * determine what characters would be legal at this point in time.
 */

std::string TokenScanner::scanNumber() {
    std::string token = "";
    NumberScannerState state = INITIAL_STATE;
    while (state != FINAL_STATE) {
        int ch = isp->get();
        switch (state) {
        case INITIAL_STATE:
            if (!isdigit(ch)) {
                error("TokenScanner::scanNumber: internal error: illegal call");
            }
            state = BEFORE_DECIMAL_POINT;
            break;
        case BEFORE_DECIMAL_POINT:
            if (ch == '.') {
                state = AFTER_DECIMAL_POINT;
            } else if (ch == 'E' || ch == 'e') {
                state = STARTING_EXPONENT;
            } else if (!isdigit(ch)) {
                if (ch != EOF) isp->unget();
                state = FINAL_STATE;
            }
            break;
        case AFTER_DECIMAL_POINT:
            if (ch == 'E' || ch == 'e') {
                state = STARTING_EXPONENT;
            } else if (!isdigit(ch)) {
                if (ch != EOF) isp->unget();
                state = FINAL_STATE;
            }
            break;
        case STARTING_EXPONENT:
            if (ch == '+' || ch == '-') {
                state = FOUND_EXPONENT_SIGN;
            } else if (isdigit(ch)) {
                state = SCANNING_EXPONENT;
            } else {
                if (ch != EOF) isp->unget();
                isp->unget();
                state = FINAL_STATE;
            }
            break;
        case FOUND_EXPONENT_SIGN:
            if (isdigit(ch)) {
                state = SCANNING_EXPONENT;
            } else {
                if (ch != EOF) isp->unget();
                isp->unget();
                isp->unget();
                state = FINAL_STATE;
            }
            break;
        case SCANNING_EXPONENT:
            if (!isdigit(ch)) {
                if (ch != EOF) isp->unget();
                state = FINAL_STATE;
            }
            break;
        default:
            state = FINAL_STATE;
            break;
        }
        if (state != FINAL_STATE) {
            token += char(ch);
        }
    }
    return token;
}

/*
 * Implementation notes: scanString
 * --------------------------------
 * Reads and returns a quoted string from the scanner, continuing until
 * it scans the matching delimiter.  The scanner generates an error if
 * there is no closing quotation mark before the end of the input.
 */

std::string TokenScanner::scanString() {
    std::string token = "";
    char delim = isp->get();
    token += delim;
    bool escape = false;
    while (true) {
        int ch = isp->get();
        if (ch == EOF) error("TokenScanner::scanString: found unterminated string");
        if (ch == delim && !escape) break;
        escape = (ch == '\\') && !escape;
        token += ch;
    }
    return token + delim;
}

/*
 * Implementation notes: isOperator, isOperatorPrefix
 * --------------------------------------------------
 * These methods search the list of operators and return true if the
 * specified operator is either in the list or a prefix of an operator
 * in the list, respectively.  This code could be made considerably more
 * efficient by implementing operators as a trie.
 */

bool TokenScanner::isOperator(std::string op) {
    for (StringCell *cp = operators; cp != NULL; cp = cp->link) {
        if (op == cp->str) return true;
    }
    return false;
}

bool TokenScanner::isOperatorPrefix(std::string op) {
    for (StringCell *cp = operators; cp != NULL; cp = cp->link) {
        if (startsWith(cp->str, op)) return true;
    }
    return false;
}

std::string toUpperCase(std::string str) {
   for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
   }
   return str;
}

std::string toLowerCase(std::string str) {
   for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
   }
   return str;
}

std::string integerToString(int n) {
    std::ostringstream stream;
    stream << n;
    return stream.str();
}

std::string longToString(long n) {
    std::ostringstream stream;
    stream << n;
    return stream.str();
}

double stringToReal(const std::string& str) {
   double db {std::stod(str)};
   return db;
}

double stringToDouble(const std::string& str) {
    return stringToReal(str);
}

int stringToInteger(const std::string& str) {
    std::istringstream stream(str);
    int value;
    stream >> value >> std::ws;
    if (stream.fail() || !stream.eof()) {
        error("stringToInteger: Illegal integer format (" + str + ")");
    }
    return value;
}

bool startsWith(const std::string& str, char prefix) {
    return str.length() > 0 && str[0] == prefix;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) return false;
    int nChars = prefix.length();
    for (int i = 0; i < nChars; i++) {
        if (str[i] != prefix[i]) return false;
    }
    return true;
}

void writeQuotedString(std::ostream & os, const std::string & str, bool forceQuotes) {
   if (!forceQuotes && stringNeedsQuoting(str)) forceQuotes = true;
   if (forceQuotes) os << '"';
   int len = str.length();
   for (int i = 0; i < len; i++) {
      char ch = str.at(i);
      switch (ch) {
       case '\a': os << "\\a"; break;
       case '\b': os << "\\b"; break;
       case '\f': os << "\\f"; break;
       case '\n': os << "\\n"; break;
       case '\r': os << "\\r"; break;
       case '\t': os << "\\t"; break;
       case '\v': os << "\\v"; break;
       case '\\': os << "\\\\"; break;
       default:
         if (isprint(ch) && ch != '"') {
            os << ch;
         } else {
            std::ostringstream oss;
            oss << std::oct << std::setw(3) << std::setfill('0') << (int(ch) & 0xFF);
            os << "\\" << oss.str();
         }
      }
   }
   if (forceQuotes) os << '"';
}

/*
 * Implementation notes: readQuotedString and writeQuotedString
 * ------------------------------------------------------------
 * Most of the work in these functions has to do with escape sequences.
 */

static const std::string STRING_DELIMITERS = ",:)}]\n";

bool stringNeedsQuoting(const std::string & str) {
   int n = str.length();
   for (int i = 0; i < n; i++) {
      char ch = str[i];
      if (isspace(ch)) return false;
      if (STRING_DELIMITERS.find(ch) != std::string::npos) return true;
   }
   return false;
}

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}


void error(std::string msg) {
   std::cout << "ERROR: " << msg << std::endl;
}

// ---------------------------------------------------------------------------------------------------------------------------
/*
 * Implementation notes: HashMap constructor and destructor
 * --------------------------------------------------------
 * The constructor allocates the array of buckets and initializes each
 * bucket to the empty list.  The destructor frees the allocated cells.
 */

StringMap::StringMap() {
   nBuckets = INITIAL_BUCKET_COUNT;
   buckets = new KeyValuePair[nBuckets];
   clear();
}

StringMap::~StringMap() {
   delete[] buckets;
}

/*
 * Implementation notes: get
 * -------------------------
 * The get method calls findKeyValuePair to search the linked list for the
 * matching key.  If no key is found, get returns the empty string.
 */

string StringMap::get(const string & key) const {
   int index = findKey(key);
   return (index == -1) ? "" : buckets[index].value;
}

/*
 * Implementation notes: put
 * -------------------------
 * The put method calls insertKey to search the bucket array for a matching
 * key.  If a key already exists, put simply resets the value field.  If no
 * matching key is found, put adds a new entry in the first free slot.
 */

void StringMap::put(const string & key, const string & value) {
   if ((double) count / nBuckets > REHASH_THRESHOLD) {
      rehash(2 * nBuckets + 1);
   }
   int index = insertKey(key);
   buckets[index].value = value;
}

int StringMap::size() const {
   return count;
}

bool StringMap::isEmpty() const {
   return count == 0;
}

bool StringMap::containsKey(const string & key) const {
   return findKey(key) != -1;
}

/*
 * Implementation notes: remove
 * ----------------------------
 * This implementation is tricky because removing one key can make later
 * keys inaccessible.  This implementation finds the first key that could
 * have gone in this position (if any) and moves it to this space, repeating
 * that process until an empty entry is found.  A much simpler but less
 * efficient strategy is to rehash after every deletion.
 */

void StringMap::remove(const string & key) {
   int index = findKey(key);
   if (index != -1) {
      buckets[index].occupied = false;
      count--;
      int toFill = index;
      while (true) {
         index = (index + 1) % nBuckets;
         if (!buckets[index].occupied) return;
         if (insertKey(buckets[index].key) == toFill) {
            buckets[toFill].value = buckets[index].value;
            buckets[index].occupied = false;
            toFill = index;
         }
      }
   }
}

void StringMap::clear() {
   for (int i = 0; i < nBuckets; i++) {
      buckets[i].occupied = false;
   }
   count = 0;
}

int StringMap::getNBuckets() {
   return nBuckets;
}

/* TODO PART:
 * Implementation notes: rehash
 * ----------------------------
 * The rehash method iterates over the existing key-value pairs, entering
 * them into a new table.
 */

void StringMap::rehash(int nBuckets) {
   // TODO
   int len = this->nBuckets;
   this->nBuckets = nBuckets;
   int temp = count;
   KeyValuePair *tmp = buckets;
   this->buckets = new KeyValuePair[nBuckets];
   clear();
   for (int i = 0; i < len; ++i) {
    // return 
    if (buckets[i].occupied) put(tmp[i].key, tmp[i].value);
   }
   this->count = temp;
   delete[] tmp;
}

/*
 * Private method: findKey
 * Usage: int index = findKey(key);
 * --------------------------------
 * This private method looks for a key in the buckets array.  If the
 * key is found, findKey returns its index.  If no match is found, the
 * findKey returns -1.
 */

int StringMap::findKey(const string & key) const {
    // TODO
   int idx = hashCode(key) % nBuckets;
   if (!buckets[idx].occupied) return -1;
   if (buckets[idx].occupied && buckets[idx].key == key) return idx++;

   while (idx < nBuckets) {
      if (buckets[idx].occupied) {
         if (buckets[idx].key == key) return idx++;
         else ++idx;
      } else ++idx;
   }
   idx = 0;
   while (idx < hashCode(key) % nBuckets) {
      if (buckets[idx].occupied) {
         if (buckets[idx].key == key) return idx++;
         else ++idx;
      } else ++idx;
   }
   return -1;
}

/*
 * Private method: insertKey
 * Usage: int index = insertKey(key);
 * ----------------------------------
 * This private method is identical to findKey except that it inserts the
 * key in the correct place if it is not already in the table.
 */

int StringMap::insertKey(const string & key) {
    // TODO
   if (containsKey(key)) return findKey(key);
   int idx = hashCode(key) % nBuckets;
   while (buckets[idx].occupied) {
      ++idx;
      if (idx == nBuckets) idx = 0;
   }
   buckets[idx].key = key;
   buckets[idx].occupied = true;
   ++count;
   return idx;
}

/*
 * Implementation notes: hashCode
 * ------------------------------
 * This function takes a string key and uses it to derive a hash code,
 * which is nonnegative integer related to the key by a deterministic
 * function that distributes keys well across the space of integers.
 * The specific algorithm used here is called djb2 after the initials
 * of its inventor, Daniel J. Bernstein, Professor of Mathematics at
 * the University of Illinois at Chicago.
 */

const int HASH_SEED = 5381;               /* Starting point for first cycle */
const int HASH_MULTIPLIER = 33;           /* Multiplier for each cycle      */
const int HASH_MASK = unsigned(-1) >> 1;  /* The largest positive integer   */

int hashCode(const string & str) {
   unsigned hash = HASH_SEED;
   int n = str.length();
   for (int i = 0; i < n; i++) {
      hash = HASH_MULTIPLIER * hash + str[i];
   }
   return int(hash & HASH_MASK);
}

void helpCommand() {
   cout << "Available commands:" << endl;
   cout << "  size         -- Prints the size of the map" << endl;
   cout << "  isEmpty      -- Prints whether the map is empty" << endl;
   cout << "  get key      -- Returns the value associated with key" << endl;
   cout << "  set key str  -- Sets the entry for key to str" << endl;
   cout << "  contains key -- Indicates whether the map contains key" << endl;
   cout << "  remove key   -- Removes the key from the table" << endl;
   cout << "  clear        -- Clears the map" << endl;
   cout << "  buckets      -- Prints the number of buckets" << endl;
   cout << "  rehash       -- Rehashes the map to have n buckets" << endl;
   cout << "  help         -- List these commands" << endl;
   cout << "  quit         -- Quits the program" << endl;
}


void executeCommand(TokenScanner & scanner, StringMap & map) {
   string cmd = scanner.nextToken();
   if (cmd == "size") {
      cout << map.size() << endl;
   } else if (cmd == "isEmpty") {
      cout << ((map.isEmpty()) ? "true" : "false") << endl;
   } else if (cmd == "clear") {
      map.clear();
   } else if (cmd == "get") {
      string key = scanner.getStringValue(scanner.nextToken());
      cout << map.get(key) << endl;
   } else if (cmd == "set") {
      string key = scanner.getStringValue(scanner.nextToken());
      map.put(key, scanner.getStringValue(scanner.nextToken()));
   } else if (cmd == "contains") {
      string key = scanner.getStringValue(scanner.nextToken());
      cout << ((map.containsKey(key)) ? "true" : "false") << endl;
   } else if (cmd == "remove") {
      string key = scanner.getStringValue(scanner.nextToken());
      map.remove(key);
   } else if (cmd == "buckets") {
      cout << map.getNBuckets() << endl;
   } else if (cmd == "rehash") {
      int n = stringToInteger(scanner.nextToken());
      map.rehash(n);
   } else if (cmd == "help") {
      helpCommand();
   } else if (cmd == "quit") {
      exit(0);
   } else if (cmd != "") {
      cout << "Unrecognized command: " << cmd << endl;
   }
}

int main() {
   StringMap map;
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.scanStrings();
   string str;
   while (true) {
      getline(cin,str);
      scanner.setInput(str);
      executeCommand(scanner, map);
   }
   return 0;
}
