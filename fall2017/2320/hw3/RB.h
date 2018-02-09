// Top-down red-black tree header file
// CSE 2320 lab 3, fall 2017

// These will have to change if data in node is more than just an int.
typedef int Key;
typedef Key Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))

typedef struct STnode* link;

struct STnode 
{
    Item item;  // Data for this node
    link l, r;  // left & right links
    char red;   // RB color
    int N;      // subtree size
};

extern Item NULLitem;

void STprintBatch();


void STinit();          // Initialize tree with just a sentinel

Item STsearch(Key v);   // Find node for a key

// Search for a batch of keys
// out[i] gets result of STsearch(in[i])
void STsearchBatch(int num, Key *in, Item *out);

Item STselect(int k);   // Treat tree as flattened into an ordered array

// Search for a batch of ranks
// out[i] gets result of STselect(in[i])
void STselectBatch(int num, int *in, Item *out);

int STinvSelect(Key v); // Inverse of STselect

// Ranks for a batch of keys
// out[i] gets result of STinvSelect(in[i])
void STinvSelectBatch(int num, Key *in, int *out);

void extendedTraceOn(); // Full tracing of intermediate trees

void basicTraceOn();    // Just trace down and up passes for insert

void traceOff();        // Run silent

void STinsert(Item item);     // Insert an item.  No uniqueness check

void verifyRBproperties();    // Ensure that tree isn't damaged

void STprintTree();           // Dumps out tree

void cleanUpUnbalanced(link h);  // Includes subtree sizes and verifies a tree
                                 // built without balancing
