#include <stdio.h>
#include <stdlib.h>


// - TODONE: implement a node struct
struct node
{
  // - cont pointer: stores a char*
  char* cont;
  // - prev pointer: stores a node*
  struct node* prev;
};

// - TODO: handle error cases according to the README

// - TODO: first just make it print the contents of the files

// - TODO: uncomment final, head, current, thirdFile as needed

// - TODO address memory leaks

int main(int argc, char *argv[])
{
  // - pointer setup
    // - set final pointer to be null
    //struct node* final = NULL;
    // - set head pointer to be null
    struct node* head = NULL;
    // - set current pointer to be null
    struct node* current = NULL;
    // - set input filename to null
    FILE *input = NULL;
    // - set output filename to null
    FILE *output = NULL;
    // - set line pointer to null
    char *line = NULL;

  // - optput choice setup
    // - int thirdFile set to 0
    //int thirdFile = 0;
    // - TODO: I dont think I need this?

  // - other misc setup
    // - len of the line in
    size_t len = 0;

  // - nothing passed in error case
  if(argc==1)
  {
    // - print the error message `usage: reverse <input> <output>`
    fprintf(stderr, "usage: reverse <input> <output>\n");
    // - return 1
    return 1;
  }

  // - if only 2 cmd line args
  if(argc == 2)
  {
    // - open second filename
    input = fopen(argv[1],"r");
    // - handle file open errors
    if (input == NULL)
    {
      fprintf(stderr, "error: cannot open file: %s \n", argv[1]);
      // - return 1
      return 1;
    }
  }

  // - if only 3 cmd line args
  if (argc == 3)
  {
    // - changing thirdFile to be 1 (true)
    //thirdFile = 1;
    // - TODO: dont htink i need this?

    // - check for namespace collision between second and third file
      // - make counter
      int i = 0;
      // - deconstruct strings into chars
      while(argv[1][i] != '\0' && argv[2][i] != '\0')
      {
        // - check chars
        if(argv[1][i] == argv[2][i])
        {
          // - handle collision
          fprintf(stderr, "error: input and output file must differ\n");
          // - return 1
          return 1;
        }
        // - incriment counter
        i++;
      }

    // - open second filename
    input = fopen(argv[1],"r");
    // - handle file open errors
    if (input == NULL)
    {
      fprintf(stderr, "error: cannot open file %s: \n", argv[1]);
      // - return 1
      return 1;
    }

    // - open third filename
    output = fopen(argv[2],"r");
    // - handle file open errors
    if (output == NULL)
    {
      fprintf(stderr, "error: cannot open file %s: \n", argv[2]);
      // - return 1
      return 1;
    }
    fclose(output);
    output = fopen(argv[2],"w");
  }

  // - While readline is still something I can do:
  // - read content using getline as it has malloc in it
  while((getline(&line, &len, input))!= -1)
  {
    // - fprintf the contents for debugging
    //fprintf(stdout, "%s", line);

    // - testing the malloc inside getline for failure
    if(line==NULL)
    {
      // - printing error message
      fprintf(stderr, "error: getline malloc failed\n");
      // - return 1
      return 1;
    }

    // - allocate a new node object with malloc(sizeof(struct node))
    struct node *new_node = malloc(sizeof(struct node));

    // - testing the node's malloc for failure
    if(new_node==NULL)
    {
      // - printing error message
      fprintf(stderr, "error: node malloc failed\n");
      // - return 1
      return 1;
    }

    // - set current's pointer to the new node
    current = new_node;
    // - set cont to be the line I just read in
    new_node->cont = line;
    // - set prev to be the value of the head pointer (not the pointer itself, just where it points!)
    new_node->prev = head;
    // - set head pointer to current's node
    head = new_node;
    // - forcing getline to allocate more space for new line by emptying line and size
    line = NULL;
    len = 0;
  }

  // - error checking to see if getline(input) got all the way through
  if(ferror(input))
  {
    // - print error
    fprintf(stderr, "error: cannot open file %s \n", argv[1] );
    // - return 1
    return 1;
  }
  // - while head is not null
  while(head!=NULL)
  {
    // - extract value from head node
    // - TODO: do i need this??

    // - if only 2 cmd line args
    if(argc==2)
    {
      // - print cont to stdout
      fprintf(stdout,"%s",head->cont);
    }

    // - if only 3 cmd line args
    if(argc==3)
    {
      // - print cont to file
      fprintf(output,"%s",head->cont);
    }

    // - set head pointer to the value pointed to by the current node's prev pointer (the node itself!)
    head = current -> prev;
    // - free the current node's cont pointer
    free(current->cont);
    // - free the current node
    free(current);
    // - set current node's pointer equal to head pointer's node
    current = head;
  }

  // - if only 3 cmd line args
  if(argc==3)
  {
    // - close output file
    if(fclose(output)!=0)
    {
      fprintf(stderr,"fclose failed - output");
    }

  }

  // - close the input file
  if(fclose(input)!=0)
    {
      fprintf(stderr,"fclose failed - input");
    }

  // - close the "line" object i have been using to read stuff in
  free(line);

  // - TODO: comment this out at some point...
	printf("TODO: write a main function\n");
	return 0;
}
