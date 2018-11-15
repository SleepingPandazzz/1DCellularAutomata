#include <string>
#include <iostream>
#include <sstream>

using namespace std;


class Automaton
{
private:
   static const int RULES_SIZE = 8;

   bool rules[RULES_SIZE];
   string thisGen;
   string extremeBit;
   int displayWidth;

public:
   static const int MAX_DISPLAY_WIDTH = 121;

   Automaton(int rule);
   string toStringCurrentGen();
   bool setRule(int newRule);
   void resetFirstGen();
   bool setDisplayWidth(int width);
   void propagateNewGeneration();
};

int main()
{
   int rule, k, widthInput;
   rule = 0;
   widthInput = 121; //change displayWidth here

   do
   {
      cout << "Enter Rule (0 - 255): ";
      cin >> rule;
   } while (rule < 0 || rule > 255);
   Automaton aut(rule);

   if (aut.setDisplayWidth(widthInput)) {

      cout << "   start" << endl;
      for (k = 0; k < 100; k++)
      {

         cout << aut.toStringCurrentGen() << endl;
         aut.propagateNewGeneration();
      }
      cout << "   end" << endl;
   }

   system("pause");

   return 0;
}

Automaton::Automaton(int rule) {
   //sanitize rule
   setRule(rule);
   resetFirstGen();
}

string Automaton::toStringCurrentGen() {
   string modifiedThisGen = "";
   string returnString = "";
   int size = thisGen.length();

   //change thisGen from O's and 1's to " " and "*"
   for (int i = 0; i < size; i++) {
      if (thisGen[i] == '0') {
         modifiedThisGen += ' ';
      }
      else {
         modifiedThisGen += '*';
      }
   }

   int stringSize = modifiedThisGen.length();
   int midWidth = ((displayWidth + 1) / 2) - 1;
   int midStringLength = ((stringSize + 1) / 2) - 1;
   int thisGenIndex = midStringLength;

   for (int i = 0; i < displayWidth && thisGenIndex != stringSize; i++) {
      if (i >= midWidth && i < displayWidth) {
         returnString += modifiedThisGen[thisGenIndex];
         thisGenIndex++;
      }
      else {
         returnString += " ";
      }
   }

   return returnString;
}

bool Automaton::setRule(int newRule) {
   int num, check;
   num = newRule;

   if (num < 0 && num > 255) {
      cout << "***illegal***" << endl;
      return false;
   }

   for (int index = 0; index < RULES_SIZE; index++) {
      check = num % 2;
      if (num != 0) {
         if (check == 0) {
            rules[index] = false;
         }
         else if (check == 1) {
            rules[index] = true;
         }
      }
      else {
         rules[index] = false;
      }
      num = num / 2;
   }

   cin.get();

   return true;
}

void Automaton::resetFirstGen() {
   thisGen = "1";
   extremeBit = "0";
   displayWidth = MAX_DISPLAY_WIDTH;
}

bool Automaton::setDisplayWidth(int width) {
   int check;

   if (width < 0 || width > MAX_DISPLAY_WIDTH) {
      cout << "Width must be between 0 and " << MAX_DISPLAY_WIDTH << endl;
      return false;
   }

   check = width % 2;

   if (check != 1) {
      cout << "Width must be odd!" << endl;
      return false;
   }
   displayWidth = width;
   cout << "Set the display width to " << displayWidth << endl;

   return true;
}

void Automaton::propagateNewGeneration() {
   string nextGen, tempGen, newtempGen;
   int thisGenIndex = 0;
   int genIndex = 0;
   tempGen = "";
   tempGen = extremeBit + extremeBit + thisGen + extremeBit + extremeBit;
   nextGen = "";

   for (int index = 0; index < tempGen.length() - 2; index++) {
      newtempGen = "";
      for (int j = 0; j < 3; j++) {
         newtempGen += tempGen[thisGenIndex + j];
      }
      string boolHold;

      if (newtempGen == "000") {
         boolHold = to_string(rules[0]);
      }
      else if (newtempGen == "001") {
         boolHold = to_string(rules[1]);
      }
      else if (newtempGen == "010") {
         boolHold = to_string(rules[2]);
      }
      else if (newtempGen == "011") {
         boolHold = to_string(rules[3]);
      }
      else if (newtempGen == "100") {
         boolHold = to_string(rules[4]);
      }
      else if (newtempGen == "101") {
         boolHold = to_string(rules[5]);
      }
      else if (newtempGen == "110") {
         boolHold = to_string(rules[6]);
      }
      else if (newtempGen == "111") {
         boolHold = to_string(rules[7]);
      }
      nextGen += boolHold;

      thisGenIndex++;
      genIndex++;
   }

   this->thisGen = nextGen;
}
