#include <stdio.h>
#include <stdlib.h>

#define MinTableSize (10)
#define NumItems 400

typedef int ElementType;
typedef unsigned int Index;
typedef struct ListNode *Position;

struct ListNode
{
	ElementType Element;
	Position    Next;
};

typedef Position List;
/* List *TheLists will be an array of lists, allocated later */
/* The lists use headers (for simplicity), though this wastes space */
struct HashTbl
{
	int TableSize;
	List *TheLists;
};

typedef struct HashTbl *HashTable;

/* Return next prime; assume N >= 10 */
static int NextPrime( int N )
{
	int i;

	if( N % 2 == 0 )
		N++;
	for( ; ; N += 2 )
	{
		for( i = 3; i * i <= N; i += 2 )
			if( N % i == 0 )
				goto ContOuter;  /* Sorry about this! */
		return N;
		ContOuter: ;
	}
}

/* Hash function for ints */
Index Hash( ElementType Key, int TableSize )
{
	return Key % TableSize;
}

/* START: fig5_8.txt */
HashTable InitializeTable( int TableSize )
{
	HashTable H;
	int i;

	if( TableSize < MinTableSize )
	{
		printf( "Table size too small" );
		return NULL;
	}

	/* Allocate table */
	H = malloc( sizeof( struct HashTbl ) );
	if( H == NULL )
		printf( "Out of space!!!" );

	H->TableSize = NextPrime( TableSize );

	/* Allocate array of lists */
	H->TheLists = malloc( sizeof( List ) * H->TableSize );
	if( H->TheLists == NULL )
		printf( "Out of space!!!" );

	/* Allocate list headers */
	for( i = 0; i < H->TableSize; i++ )
	{
		H->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
		if( H->TheLists[ i ] == NULL )
			printf( "Out of space!!!" );
		else
			H->TheLists[ i ]->Next = NULL;
	}

	return H;
}
/* END */

/* START: fig5_9.txt */
Position Find( ElementType Key, HashTable H )
{
	Position P;
	List L;

	L = H->TheLists[ Hash( Key, H->TableSize ) ];
	P = L->Next;
	while( P != NULL && P->Element != Key ) /* Probably need strcmp!! */
		P = P->Next;
	return P;
}
/* END */

/* START: fig5_10.txt */
void Insert( ElementType Key, HashTable H )
{
	Position Pos, NewCell;
	List L;

	Pos = Find( Key, H );
	if( Pos == NULL )   /* Key is not found */
	{
		NewCell = malloc( sizeof( struct ListNode ) );
		if( NewCell == NULL )
			printf( "Out of space!!!" );
		else
		{
			L = H->TheLists[ Hash( Key, H->TableSize ) ];
			NewCell->Next = L->Next;
			NewCell->Element = Key;  /* Probably need strcpy! */
			L->Next = NewCell;
		}
	}
}
/* END */

ElementType Retrieve( Position P )
{
	return P->Element;
}

void DestroyTable( HashTable H )
{
	int i;

	for( i = 0; i < H->TableSize; i++ )
	{
		Position P = H->TheLists[ i ];
 		Position Tmp;

		while( P != NULL )
		{
			Tmp = P->Next;
 			free( P );
			P = Tmp;
		}
	}

	free( H->TheLists );
	free( H );
}

main( )
{
    HashTable H;
    Position P;
    int i;
    int j = 0;
    int CurrentSize;

    H = InitializeTable( CurrentSize = 13 );

    for( i = 0; i < NumItems; i++, j += 71 )
    {
        Insert( j, H );
    }

    for( i = 0, j = 0; i < NumItems; i++, j += 71 )
        if( ( P = Find( j, H ) ) == NULL || Retrieve( P ) != j )
            printf( "Error at %d\n", j );

    printf( "End of program.\n" );
    return 0;
}
