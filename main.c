//
// Author: Adithya Jose, UIC, Fall 2021
// CS 211: Programming Practicum
// Assignment: Project 2
//
//
//  A C program that will determine whether input is given with properly balanced
// symbols. 
//
//

#include <stdio.h>

#define TRUE  1
#define FALSE 0

int DebugMode;

// Stack Struct
struct Stack
{
  char* arr; // Dynamic Array
  int size; // Allocated Space
  int back; // Back of Stack
};


// initializing the stack; use the function name: init( ) 
void init(struct Stack* stack)
{
  stack->arr = (char*) malloc (2 * sizeof (char));
  stack->size = 2;
  stack->back = 0;
}

// checking if the stack is empty; use the function name: is_empty( ) 
int is_empty(struct Stack* stack)
{
  if (stack->back == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// pushing/adding an element onto the stack; use the function name: push( ) 
void push(struct Stack* stack, char element)
{
  stack->arr[stack->back] = element;
  stack->back++;

  if (stack->back == stack->size)
  {
    char* temp = (char*) malloc ((stack->size * 2) * sizeof (char));

    for (int i = 0; i < stack->size; ++i)
    {
      temp[i] = stack->arr[i];
    }

    stack->arr = temp;
    stack->size = 2 * stack->size;
  }
}

// popping/removing an element off of the stack; use the function name: pop( ) 
void pop(struct Stack* stack)
{
  stack->back--;
}

// accessing/returning the top element on the stack; use the function name: top( ) 
char top(struct Stack* stack)
{
  return stack->arr[stack->back - 1];
}

// clear the stack so that it is empty and ready to be used again; use the function name: clear( ) 
void clear(struct Stack* stack)
{
  stack->arr = (char*) malloc (2 * sizeof (char));
  stack->size = 2;
  stack->back = 0;
}

int main(int argc, char** argv)
{
  char input[301];
  struct Stack stack;
  
  stack.size = -1;
  stack.back = -1;

  init(&stack);

  /* Check for command line argument of -d */
  DebugMode = FALSE;
  
  for (int i = 0; i < argc; ++i)
  {
    if ( strcmp (argv[i], "-d") == 0)
    {
        DebugMode = TRUE;
    }
  }

  /* Set up an infinite loop */
  while (1)
  {
    int num_spaces = 0;
    
    /* Get line of input from standard input */
    printf("\nEnter input to check or q to quit\n");
    fgets(input, 300, stdin);

    /* Remove the newline character from the input */
    int i = 0;
    while (input[i] != '\n' && input[i] != '\0')
    {
      i++;
    }
    input[i] = '\0';

    /* Check if user enter q or Q to quit program */
    if ((strcmp(input, "q") == 0) || (strcmp(input, "Q") == 0))
    {
      break;
    }

    printf("%s\n", input);

    i = 0;
    int x = 1;

    while (input[i] != '\0')
    {
      if (input[i] == '(' || input[i] == '{' || input[i] == '[' || input[i] == '<')
      {
        push(&stack, input[i]);
      }
      else if (input[i] == ')' || input[i] == '}' || input[i] == ']' || input[i] == '>')
      {
        if (is_empty(&stack))
        {
          char a;
          if (input[i] == ')')
          {
            a = '(';
          }
          else if (input[i] == '}')
          {
            a = '{';
          }
          else if (input[i] == ']')
          {
            a = '[';
          }
          else if (input[i] == '>')
          {
            a = '<';
          }
          for (int j = 0; j < num_spaces; ++j)
          {
            printf(" ");
          }
          printf("^ missing %c\n", a);
          x = 0;
          break;
        }

        if (input[i] == ')' && top(&stack) == '(')
        {
          pop(&stack);
        }
        else if (input[i] == '}' && top(&stack) == '{')
        {
          pop(&stack);
        }
        else if (input[i] == ']' && top(&stack) == '[')
        {
          pop(&stack);
        }
        else if (input[i] == '>' && top(&stack) == '<')
        {
          pop(&stack);
        }
        else
        {
          char e;

          if (top(&stack) == '(')
          {
            e = ')';
          }
          else if (top(&stack) == '{')
          {
            e = '}';
          }
          else if (top(&stack) == '[')
          {
            e = ']';
          }
          else if (top(&stack) == '<')
          {
            e = '>';
          }
          for (int k = 0; k < num_spaces; k++)
          {
            printf(" ");
          }
          printf("^ expecting %c\n", e);
          x = 0;
          break;
        }
      }

      i++;
      num_spaces++;

    }
    if (is_empty(&stack) && x)
    {
      printf("Expression is balanced\n");
    }
    else if (!is_empty(&stack) && x)
    {
      char c;
      if (top(&stack) == '(')
      {
        c = ')';
      }
      else if (top(&stack) == '{')
      {
        c = '}';
      }
      else if (top(&stack) == '[')
      {
        c = ']';
      }
      else if (top(&stack) == '<')
      {
        c = '>';
      }
      for (int j = 0; j < num_spaces; ++j)
      {
        printf(" ");
      }
      printf("^ missing %c\n", c);
    }

    clear(&stack);
    /* Run the algorithm to determine is input is balanced... */
  }

  printf("\nGoodbye\n");
  return 0;
}