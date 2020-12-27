#include <stdio.h>
#include <stdlib.h>

#define MinQueueSize ( 5 )

typedef int ElementType;
struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
};
typedef struct QueueRecord *Queue;

int IsEmpty( Queue Q )
{
	return Q->Size == 0;
}

int IsFull( Queue Q )
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue( int MaxElements )
{
	Queue Q;

	if( MaxElements < MinQueueSize )
		printf( "Queue size is too small" );

	Q = malloc( sizeof( struct QueueRecord ) );
	if( Q == NULL )
		printf( "Out of space!!!" );

	Q->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( Q->Array == NULL )
		printf( "Out of space!!!" );
	Q->Capacity = MaxElements;
	MakeEmpty( Q );

	return Q;
}

/* START: fig3_59.txt */
void MakeEmpty( Queue Q )
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}
/* END */

void DisposeQueue( Queue Q )
{
	if( Q != NULL )
	{
		free( Q->Array );
		free( Q );
	}
}

/* START: fig3_60.txt */
static int Succ( int Value, Queue Q )
{
	if( ++Value == Q->Capacity )
		Value = 0;
	return Value;
}

void Enqueue( ElementType X, Queue Q )
{
	if( IsFull( Q ) )
		printf( "Full queue" );
	else
	{
		Q->Size++;
		Q->Rear = Succ( Q->Rear, Q );
		Q->Array[ Q->Rear ] = X;
	}
}
/* END */



ElementType Front( Queue Q )
{
	if( !IsEmpty( Q ) )
		return Q->Array[ Q->Front ];
	printf( "Empty queue" );
	return 0;  /* Return value used to avoid warning */
}

void Dequeue( Queue Q )
{
	if( IsEmpty( Q ) )
		printf( "Empty queue" );
	else
	{
		Q->Size--;
		Q->Front = Succ( Q->Front, Q );
	}
}

ElementType FrontAndDequeue( Queue Q )
{
	ElementType X = 0;

	if( IsEmpty( Q ) )
		printf( "Empty queue" );
	else
	{
		Q->Size--;
		X = Q->Array[ Q->Front ];
		Q->Front = Succ( Q->Front, Q );
	}
	return X;
}

main( )
{
    Queue Q;
    int i;

    Q = CreateQueue( 12 );

    for( i = 0; i < 10; i++ )
        Enqueue( i, Q );

    while( !IsEmpty( Q ) )
    {
        printf( "%d\n", Front( Q ) );
        Dequeue( Q );
    }
    for( i = 0; i < 10; i++ )
        Enqueue( i, Q );

    while( !IsEmpty( Q ) )
    {
        printf( "%d\n", Front( Q ) );
        Dequeue( Q );
    }

    DisposeQueue( Q );
    return 0;
}
