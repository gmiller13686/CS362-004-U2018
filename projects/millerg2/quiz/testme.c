#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char symbol;
    int num;
    //Get the random number in range from 97 - 129
    num = (rand() % 33) + 97;

    //Assign an appropriate character to symbol
    if (num < 124) {  //Already a valid character
        symbol = num;
    }
    else {  //Num is not the value of valid character yet
        if (num == 124) {
            symbol = ' ';
        }
        else if (num == 125) {
            symbol = '(';
        }
        else if (num == 126) {
            symbol = ')';
        }
        else if (num == 127) {
            symbol = '[';
        }
        else if (num == 128) {
            symbol = ']';
        }
        else if (num == 129) {
            symbol = '}';
        }
        else {  //Error
            printf("Random character number %d is invalid.  Exiting.\n", num);
            exit(1);
        }
    }

    return symbol;
}

char *inputString()
{
    int i;
    int num;
    char* array = malloc(6);
    if (!array) {
        printf("String process error.  Exiting.\n");
        exit(1);
    }
    memset(array, 0, 6);

    //Assign one of four random letters to indices 0-4 in the array.
    for(i = 0; i < 5; i++) {
        num = (rand() % 4) + 114;
        if (num < 117) {
            array[i] = num; 
        }
        else {
            array[i] = 'e';
        }
    }

    return array;
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

