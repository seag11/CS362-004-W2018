#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int c;
    char arr[9] = {'[','(','{',' ','a','x','}',')',']'};
    c = rand() % 9;  //compute random 0-8 for array index
    return arr[c];
}

char *inputString()
{
    char str[6];
    memset(str, '\0', sizeof(str));		//clear memory at string address
    char* returnStr;
    int i;
    for (i=0; i<5; i++){
		int decimal = rand() % 26;		// 26 letters in alphabet
		decimal+=97;  					// shift decimal value a-z
		char ascii = (char)decimal;		// cast to char ascii value
		str[i] = ascii;
	}
    returnStr = str;
    return returnStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
