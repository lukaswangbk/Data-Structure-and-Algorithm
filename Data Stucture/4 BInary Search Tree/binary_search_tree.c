#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct TreeNode
{
	ElementType Element;
	SearchTree  Left;
	SearchTree  Right;
};

/* START: fig4_17.txt */
SearchTree MakeEmpty( SearchTree T )
{
	if( T != NULL )
	{
		MakeEmpty( T->Left );
		MakeEmpty( T->Right );
		free( T );
	}
	return NULL;
}
/* END */

/* START: fig4_18.txt */
Position Find( ElementType X, SearchTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Element )
		return Find( X, T->Left );
	else if( X > T->Element )
		return Find( X, T->Right );
	else
		return T;
}
/* END */

/* START: fig4_19.txt */
Position FindMin( SearchTree T )
{
	if( T == NULL )
		return NULL;
	else if( T->Left == NULL )
		return T;
	else
		return FindMin( T->Left );
}
/* END */

/* START: fig4_20.txt */
Position FindMax( SearchTree T )
{
	if( T != NULL )
	while( T->Right != NULL )
		T = T->Right;

	return T;
}
/* END */

/* START: fig4_22.txt */
SearchTree Insert( ElementType X, SearchTree T )
{
	if( T == NULL )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct TreeNode ) );
		if( T == NULL )
			printf( "Out of space!!!" );
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if( X < T->Element )
		T->Left = Insert( X, T->Left );
	else if( X > T->Element )
		T->Right = Insert( X, T->Right );
	/* Else X is in the tree already; we'll do nothing */

	return T;  /* Do not forget this line!! */
}
/* END */

/* START: fig4_25.txt */
SearchTree Delete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if( T == NULL )
		printf( "Element not found" );
	else if( X < T->Element )  /* Go left */
		T->Left = Delete( X, T->Left );
	else if( X > T->Element )  /* Go right */
		T->Right = Delete( X, T->Right );
	else if( T->Left && T->Right )  /* Two children */
	{
		/* Replace with smallest in right subtree */
		TmpCell = FindMin( T->Right );
		T->Element = TmpCell->Element;
		T->Right = Delete( T->Element, T->Right );
	}
	else  /* One or zero children */
	{
		TmpCell = T;
		if( T->Left == NULL ) /* Also handles 0 children */
			T = T->Right;
		else if( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}

	return T;
}
/* END */

ElementType Retrieve( Position P )
{
	return P->Element;
}

main( )
{
    SearchTree T;
    Position P;
    int i;
    int j = 0;

    T = MakeEmpty( NULL );
    for( i = 0; i < 50; i++, j = ( j + 7 ) % 50 )
        T = Insert( j, T );
    for( i = 0; i < 50; i++ )
        if( ( P = Find( i, T ) ) == NULL || Retrieve( P ) != i )
            printf( "Error at %d\n", i );

    for( i = 0; i < 50; i += 2 )
        T = Delete( i, T );

    for( i = 1; i < 50; i += 2 )
        if( ( P = Find( i, T ) ) == NULL || Retrieve( P ) != i )
            printf( "Error at %d\n", i );
    for( i = 0; i < 50; i += 2 )
        if( ( P = Find( i, T ) ) != NULL )
            printf( "Error at %d\n", i );

    printf( "Min is %d, Max is %d\n", Retrieve( FindMin( T ) ),
               Retrieve( FindMax( T ) ) );

    return 0;
}

