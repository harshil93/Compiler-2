
enum
{
	Match = 256,
	Split = 257
};

struct State
{
	int c;
	State *out;
	State *out1;
	int lastlist;
};

/*
* Since the out pointers in the list are always
* uninitialized, we use the pointers themselves
* as storage for the Ptrlists.
*/
union Ptrlist
{
	Ptrlist *next;
	State *s;
};



/*
* A partially built NFA without the matching state filled in.
* Frag.start points at the start state.
* Frag.out is a list of places that need to be set to the
* next state for this fragment.
*/

struct Frag
{
	State *start;
	Ptrlist *out;
};

struct List
{
	State **s;
	int n;
};
class regex{
public:
	/*
	* Represents an NFA state plus zero or one or two arrows exiting.
	* if c == Match, no arrows out; matching state.
	* If c == Split, unlabeled arrows to out and out1 (if != NULL).
	* If c < 256, labeled arrow with character c to out.
	*/
	
	regex(){
		matchstate = { Match };
		listid = 0;
		nstate = 0;
	}
	State matchstate;	/* matching state */
	int nstate;
	List l1, l2;
	int listid;
	char* re2post(char *re);
	State* state(int c, State *out, State *out1);
	Ptrlist* list1(State **outp);
	void patch(Ptrlist *l, State *s);
	Ptrlist* append(Ptrlist *l1, Ptrlist *l2);
	State* post2nfa(char *postfix);
	void addstate(List*, State*);
	void step(List*, int, List*);
	int	ismatch(List *l);
	int	match(State *start, char *s);
	bool regMatch(char *string, char *re);
	List* startlist(State *start, List *l);
};


