#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
	ElementType Element;
	Position Next;
};

List MakeEmpty( List L )
{
	if( L != NULL )
		DeleteList( L );
	L = malloc( sizeof( struct Node ) );
	if( L == NULL )
		printf( "Out of memory!" );
	L->Next = NULL;
	return L;
}

/* START: fig3_8.txt */
/* Return true if L is empty */

int IsEmpty( List L )
{
	return L->Next == NULL;
}
/* END */

/* START: fig3_9.txt */
/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast( Position P, List L )
{
	return P->Next == NULL;
}
/* END */

/* START: fig3_10.txt */
/* Return Position of X in L; NULL if not found */
Position Find( ElementType X, List L )
{
	Position P;

	P = L->Next;
	while( P != NULL && P->Element != X )
		P = P->Next;

	return P;
}
/* END */

/* START: fig3_11.txt */
/* Delete from a list */
/* Cell pointed to by P->Next is wiped out */
/* Assume that the position is legal */
/* Assume use of a header node */
void Delete( ElementType X, List L )
{
	Position P, TmpCell;

	P = FindPrevious( X, L );

	if( !IsLast( P, L ) )  /* Assumption of header use */
	{                      /* X is found; delete it */
		TmpCell = P->Next;
		P->Next = TmpCell->Next;  /* Bypass deleted cell */
		free( TmpCell );
	}
}
/* END */

/* START: fig3_12.txt */
/* If X is not found, then Next field of returned value is NULL */
/* Assumes a header */
Position FindPrevious( ElementType X, List L )
{
	Position P;

	P = L;
	while( P->Next != NULL && P->Next->Element != X )
		P = P->Next;

	return P;
}
/* END */

/* START: fig3_13.txt */
/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */

void Insert( ElementType X, List L, Position P )
{
	Position TmpCell;

	TmpCell = malloc( sizeof( struct Node ) );
	if( TmpCell == NULL )
		printf( "Out of space!!!" );

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
/* END */

/* START: fig3_15.txt */
/* Correct DeleteList algorithm */
void DeleteList( List L )
{
	Position P, Tmp;

	P = L->Next;  /* Header assumed */
	L->Next = NULL;
	while( P != NULL )
	{
		Tmp = P->Next;
		free( P );
		P = Tmp;
	}
}
/* END */

Position Header( List L )
{
	return L;
}

Position First( List L )
{
	return L->Next;
}

Position Advance( Position P )
{
	return P->Next;
}

ElementType Retrieve( Position P )
{
	return P->Element;
}

void PrintList( const List L )
{
    Position P = Header( L );

    if( IsEmpty( L ) )
        printf( "Empty list\n" );
    else
    {
        do
        {
            P = Advance( P );
            printf( "%d ", Retrieve( P ) );
        } while( !IsLast( P, L ) );
        printf( "\n" );
    }
}

main( )
{
    List L;
    Position P;
    int i;

    L = MakeEmpty( NULL );
    P = Header( L );
    PrintList( L );

    for( i = 0; i < 10; i++ )
    {
        Insert( i, L, P );
        PrintList( L );
        P = Advance( P );
    }
    for( i = 0; i < 10; i+= 2 )
        Delete( i, L );

    for( i = 0; i < 10; i++ )
        if( ( i % 2 == 0 ) == ( Find( i, L ) != NULL ) )
            printf( "Find fails\n" );

    printf( "Finished deletions\n" );

    PrintList( L );

    DeleteList( L );

    return 0;
}
