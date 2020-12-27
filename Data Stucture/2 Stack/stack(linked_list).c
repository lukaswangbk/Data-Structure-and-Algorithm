#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{
	ElementType Element;
	PtrToNode   Next;
};

/* START: fig3_40.txt */
int IsEmpty( Stack S )
{
	return S->Next == NULL;
}
/* END */

/* START: fig3_41.txt */
Stack CreateStack( void )
{
	Stack S;

	S = malloc( sizeof( struct Node ) );
	if( S == NULL )
		printf( "Out of space!!!" );
	S->Next = NULL;
	MakeEmpty( S );
	return S;
}

void MakeEmpty( Stack S )
{
	if( S == NULL )
		printf( "Must use CreateStack first" );
	else
		while( !IsEmpty( S ) )
			Pop( S );
}
/* END */

void DisposeStack( Stack S )
{
	MakeEmpty( S );
	free( S );
}

/* START: fig3_42.txt */
void Push( ElementType X, Stack S )
{
	PtrToNode TmpCell;

	TmpCell = malloc( sizeof( struct Node ) );
	if( TmpCell == NULL )
		printf( "Out of space!!!" );
	else
	{
		TmpCell->Element = X;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}
/* END */

/* START: fig3_43.txt */
ElementType Top( Stack S )
{
	if( !IsEmpty( S ) )
		return S->Next->Element;
	printf( "Empty stack" );
	return 0;  /* Return value used to avoid warning */
}
/* END */

/* START: fig3_44.txt */
void Pop( Stack S )
{
	PtrToNode FirstCell;

	if( IsEmpty( S ) )
		printf( "Empty stack" );
	else
	{
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		free( FirstCell );
	}
}
/* END */

main( )
{
    Stack S;
    int i;

    S = CreateStack( );
    for( i = 0; i < 10; i++ )
        Push( i, S );

    while( !IsEmpty( S ) )
    {
        printf( "%d\n", Top( S ) );
        Pop( S );
    }

    DisposeStack( S );
    return 0;
}
