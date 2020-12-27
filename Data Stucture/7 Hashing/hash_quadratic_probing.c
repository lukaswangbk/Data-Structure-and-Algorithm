#include <stdio.h>
#include <stdlib.h>

#define MinTableSize (10)
#define NumItems 400

typedef int ElementType;
typedef unsigned int Index;
typedef Index Position;

enum KindOfEntry { Legitimate, Empty, Deleted };

struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;
/* Cell *TheCells will be an array of HashEntry cells, allocated later */
struct HashTbl
{
	int TableSize;
	Cell *TheCells;
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

/* START: fig5_15.txt */
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

	/* Allocate array of Cells */
	H->TheCells = malloc( sizeof( Cell ) * H->TableSize );
	if( H->TheCells == NULL )
		printf( "Out of space!!!" );

	for( i = 0; i < H->TableSize; i++ )
		H->TheCells[ i ].Info = Empty;

	return H;
}
/* END */

/* START: fig5_16.txt */
Position Find( ElementType Key, HashTable H )
{
	Position CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash( Key, H->TableSize );
	while( H->TheCells[ CurrentPos ].Info != Empty 
		&& H->TheCells[ CurrentPos ].Element != Key )
		/* Probably need strcmp!! */
	{
		CurrentPos += 2 * ++CollisionNum - 1;
		if( CurrentPos >= H->TableSize )
			CurrentPos -= H->TableSize;
	}
	return CurrentPos;
}
/* END */

/* START: fig5_17.txt */
void Insert( ElementType Key, HashTable H )
{
	Position Pos;

	Pos = Find( Key, H );
	if( H->TheCells[ Pos ].Info != Legitimate )
	{
		/* OK to insert here */
		H->TheCells[ Pos ].Info = Legitimate;
		H->TheCells[ Pos ].Element = Key;
		/* Probably need strcpy! */
	}
}
/* END */

/* START: fig5_22.txt */
HashTable Rehash( HashTable H )
{
	int i, OldSize;
	Cell *OldCells;

	OldCells = H->TheCells;
	OldSize  = H->TableSize;

	/* Get a new, empty table */
	H = InitializeTable( 2 * OldSize );

	/* Scan through old table, reinserting into new */
	for( i = 0; i < OldSize; i++ )
		if( OldCells[ i ].Info == Legitimate )
			Insert( OldCells[ i ].Element, H );

	free( OldCells );

	return H;
}
/* END */

ElementType Retrieve( Position P, HashTable H )
{
	return H->TheCells[ P ].Element;
}

void DestroyTable( HashTable H )
{
	free( H->TheCells );
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
        if( i > CurrentSize / 2 )
        {
            H = Rehash( H );
            printf( "Rehashing...\n" );
            CurrentSize *= 2;
        }
        Insert( j, H );
    }

    for( i = 0, j = 0; i < NumItems; i++, j += 71 )
        if( Retrieve( ( P = Find( j, H ) ), H ) != j )
            printf( "Error at %d\n", j );

    printf( "End of program.\n" );
    return 0;
}
