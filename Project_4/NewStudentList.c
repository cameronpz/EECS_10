#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define SLEN 40

/*Function Declarations and Structs */

struct Student
{ 
	int ID;
	char Name[SLEN+1];
	char Grade;
};
typedef struct Student STUDENT;
	
typedef struct StudentList SLIST;
typedef struct StudentEntry SENTRY;
struct StudentList
{
	int Length;
	SENTRY *First;
	SENTRY *Last;
};
struct StudentEntry
{
	SLIST *List;
	SENTRY *Next;
	SENTRY *Prev;
	STUDENT *Student;
};

typedef int CMP_F(STUDENT *s1, STUDENT *s2);
void DeleteStudent(STUDENT *s);
STUDENT *NewStudent(int ID, char *Name, char Grade);
void PrintStudent(STUDENT *s);
static SENTRY *NewStudentEntry(STUDENT *s);
static STUDENT *DeleteStudentEntry(SENTRY *e);
SLIST *NewStudentList(void);
STUDENT *RemoveFirstStudent(SLIST *l);
void InsertStudent(SLIST *l, STUDENT *s, CMP_F *CompareFct);
void DeleteStudentList(SLIST *l);
void AppendStudent(SLIST *l, STUDENT *s);
int CompareStudentName (STUDENT *s1, STUDENT *s2);
SLIST *SortStudentList(SLIST *l, CMP_F *CompareFct);
STUDENT *FindStudentName (SLIST *l, char *Name);
void InsertStudent(SLIST *l, STUDENT *s, CMP_F *CompareFct);
void PrintStudentList(SLIST *l);
void InsertStudentBefore(SENTRY *e, STUDENT *s);

void InsertStudentBefore(SENTRY *e, STUDENT *s)
{
	SENTRY *New;
	New = NewStudentEntry(s);
	New->List = e->List;
	New->Next = e;
	New->Prev = e->Prev;
	e->Prev = New;
	if (New->Prev)
	{
		New->Prev->Next = New;
	}
	else
	{
		assert(New->List->First == e);
		New->List->First = New;
	}
	New->List->Length++;
}

void PrintStudentList(SLIST *l)
{
	SENTRY *e;
	assert(l);
	e = l->First;
	while(e)
	{
		PrintStudent(e->Student);
		e = e->Next;
	}
}

/*delete a student record */
void DeleteStudent(STUDENT *s)
{
	assert(s);
	free(s);
}

/*allocate a new student record */
STUDENT *NewStudent(int ID, char *Name, char Grade)
{
	STUDENT *s;
	s = malloc(sizeof(STUDENT));
	if (!s)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	s->ID = ID;
	strncpy(s->Name, Name, SLEN);
	s->Name[SLEN] = '\0';
	s->Grade = Grade;
	return s;
}
/*print a student record */
void PrintStudent(STUDENT *s)
{
	assert(s);
	printf("Student ID: %d\n", s->ID);
	printf("Student Name: %s\n", s->Name);
	printf("Student Grade: %c\n", s->Grade);
}
static SENTRY *NewStudentEntry(STUDENT *s)
{
	SENTRY *e;
	e = malloc(sizeof(SENTRY));
	if (!e)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->Student = s;
	return e;
}
static STUDENT *DeleteStudentEntry(SENTRY *e)
{
	STUDENT *s;
	assert(e);
	s = e->Student;
	free(e);
	return s;
}

/*allocate a new student list */
SLIST *NewStudentList(void)
{
	SLIST *l;
	l = malloc(sizeof(SLIST));
	if (!l)
	{
		perror("out of memory! Aborting...");
		exit(10);
	}
	l->Length = 0;
	l->First = NULL;
	l->Last = NULL;
	return l;
}

/*remove the first student from the list */
STUDENT *RemoveFirstStudent(SLIST *l)
{
	SENTRY *e = NULL;
	assert(l);
	if (l->First)
	{
		e = l->First;
		l->First = e->Next;
		if (l->First)
		{
			l->First->Prev = NULL;
		}
		else 
		{
			assert(l->Last == e);
			l->Last = NULL;
		}
		l->Length--;
		return DeleteStudentEntry(e);
	}
	else
	{
		return(NULL);
	}
}

/*delete a student list (and all entries) */
void DeleteStudentList(SLIST *l)
{
	SENTRY *e, *n;
	STUDENT *s;
	assert(l);
	e = l->First;
	while(e)
	{
		n = e->Next;
		s = DeleteStudentEntry(e);
		DeleteStudent(s);
		e = n;
	}
	free(l);
}
/*append a student at end of list */
void AppendStudent(SLIST *l, STUDENT *s)
{
	SENTRY *e = NULL;
	assert(l);
	assert(s);
	e = NewStudentEntry(s);
	if (l->Last)
	{
		e->List = l;
		e->Next = NULL;
		e->Prev = l->Last;
		l->Last->Next = e;
		l->Last = e;
	}
	else
	{
		e->List = l;
		e->Next = NULL;
		e->Prev = NULL;
		l->First = e;
		l->Last = e;
	}
	l->Length++;
}

/*swap first name and last name */
STUDENT swap (STUDENT *s)
{
	char *FirstName;
        char *LastName;
        char delim[]= " ";
        char *ptr;
        ptr = strtok(s->Name, delim);
        FirstName = ptr;
        ptr = strtok(NULL, delim);
        LastName = ptr;
	s->Name = strcat(LastName, FirstName);
	return s;
}
	
/* students by name */
int CompareStudentName (STUDENT *s1, STUDENT *s2)
{
	assert(s1);
	assert(s2);
	return(strcmp(s1->Name, s2->Name));
}

/* sort a student list (insertion sort) */
SLIST *SortStudentList(SLIST *l, CMP_F *CompareFct)
{
	SLIST *l2 = NULL;
	STUDENT *s = NULL;
	
	assert (l);
	assert (CompareFct);
	l2 = NewStudentList();
	while((s = RemoveFirstStudent(l)))
	{ InsertStudent(l2, s, CompareFct);
	}

	assert(l->Length == 0);
	DeleteStudentList(l);
	return(l2);
}

/*find a student by last name in a sorted list */

STUDENT *FindStudentName (SLIST *l, char *Name)
{
	SENTRY *e;
	int CompVal;
	assert(l);
	assert(Name);
	e = l->First;
	while(e)
	{
	CompVal = strcmp(e->Student->Name, Name);
		if (CompVal == 0)
		{
			return (e->Student);
		}
		if (CompVal > 0)
		{
			break;
		}
		e = e->Next;
	}
	return(NULL);
}

/* insert a student into a sorted list */
void InsertStudent(SLIST *l, STUDENT *s, CMP_F *CompareFct)
{
	SENTRY *e = NULL;
	assert(l);
	assert(s);
	assert(CompareFct);
	e = l->First;
	while (e)
	{ 
		if(CompareFct(e->Student, s) > 0)
		{
			break;
		}
		e = e->Next;
	}
	if(e)
	{
		InsertStudentBefore(e, s);
	}
	else
	{
		AppendStudent(l, s); 
	}
}

int main ()
{
	SLIST *l = NULL;
	SENTRY *e = NULL;
	e = l->First;
	l = NewStudentList();
	AppendStudent(l, NewStudent(1001, "Jane Doe", 'A'));
	AppendStudent(l, NewStudent(1002, "John Doe", 'C'));
	AppendStudent(l, NewStudent(1000, "Jim Doe", 'F'));
	AppendStudent(l, NewStudent(1003, "Jane Doe", 'B'));
	AppendStudent(l, NewStudent(1009, "Z End", 'A'));
	AppendStudent(l, NewStudent(1008, "Alice A", 'A'));
	AppendStudent(l, NewStudent(1007, "Bob B", 'B'));
	AppendStudent(l, NewStudent(1006, "Carl C", 'C'));
	AppendStudent(l, NewStudent(1005, "Dave D", 'D'));
	AppendStudent(l, NewStudent(1004, "Eve E", 'F'));
	printf("Student list sorted by last name: \n");
	while (e)
        {
                swap(s);
                e = e->Next;

        }
	l =  SortStudentList(l, CompareStudentName);
	e = l->First;
	while (e)
        {
                swap(s);
                e = e->Next;

        }
	PrintStudentList(l);
	assert(FindStudentName(l, "John Doe") != NULL);
	assert(FindStudentName(l, "No Body") == NULL);
	return 0;
}

