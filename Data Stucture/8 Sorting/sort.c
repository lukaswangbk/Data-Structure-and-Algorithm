/* This file contains a collection of sorting routines */

#include <stdlib.h>

typedef int ElementType;

void Swap( ElementType *Lhs, ElementType *Rhs )
{
	ElementType Tmp = *Lhs;
	*Lhs = *Rhs;
	*Rhs = Tmp;
}

/* START: fig7_2.txt */
void InsertionSort( ElementType A[ ], int N )
{
	int j, P;
	ElementType Tmp;

	for( P = 1; P < N; P++ )
	{
		Tmp = A[ P ];
		for( j = P; j > 0 && A[ j - 1 ] > Tmp; j-- )
			A[ j ] = A[ j - 1 ];
			A[ j ] = Tmp;
	}
}
/* END */

/* START: fig7_4.txt */
void Shellsort( ElementType A[ ], int N )
{
	int i, j, Increment;
	ElementType Tmp;

	for( Increment = N / 2; Increment > 0; Increment /= 2 )
		for( i = Increment; i < N; i++ )
		{
			Tmp = A[ i ];
			for( j = i; j >= Increment; j -= Increment )
				if( Tmp < A[ j - Increment ] )
					A[ j ] = A[ j - Increment ];
				else
					break;
				A[ j ] = Tmp;
		}
}
/* END */

/* START: fig7_8.txt */
#define LeftChild( i )  ( 2 * ( i ) + 1 )

void PercDown( ElementType A[ ], int i, int N )
{
	int Child;
	ElementType Tmp;

	for( Tmp = A[ i ]; LeftChild( i ) < N; i = Child )
	{
		Child = LeftChild( i );
		if( Child != N - 1 && A[ Child + 1 ] > A[ Child ] )
			Child++;
		if( Tmp < A[ Child ] )
			A[ i ] = A[ Child ];
		else
			break;
	}
	A[ i ] =Tmp;
}

void Heapsort( ElementType A[ ], int N )
{
	int i;

	for( i = N / 2; i >= 0; i-- )  /* BuildHeap */
		PercDown( A, i, N );
	for( i = N - 1; i > 0; i-- )
	{
		Swap( &A[ 0 ], &A[ i ] );  /* DeleteMax */
		PercDown( A, 0, i );
	}
}
/* END */

/* START: fig7_10.txt */
/* Lpos = start of left half, Rpos = start of right half */
void Merge( ElementType A[ ], ElementType TmpArray[ ],
	int Lpos, int Rpos, int RightEnd )
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	/* main loop */
	while( Lpos <= LeftEnd && Rpos <= RightEnd )
		if( A[ Lpos ] <= A[ Rpos ] )
			TmpArray[ TmpPos++ ] = A[ Lpos++ ];
		else
			TmpArray[ TmpPos++ ] = A[ Rpos++ ];

	while( Lpos <= LeftEnd )  /* Copy rest of first half */
		TmpArray[ TmpPos++ ] = A[ Lpos++ ];
	while( Rpos <= RightEnd ) /* Copy rest of second half */
		TmpArray[ TmpPos++ ] = A[ Rpos++ ];

	/* Copy TmpArray back */
	for( i = 0; i < NumElements; i++, RightEnd-- )
		A[ RightEnd ] = TmpArray[ RightEnd ];
}
/* END */

/* START: fig7_9.txt */
void MSort( ElementType A[ ], ElementType TmpArray[ ], int Left, int Right )
{
	int Center;

	if( Left < Right )
	{
		Center = ( Left + Right ) / 2;
		MSort( A, TmpArray, Left, Center );
		MSort( A, TmpArray, Center + 1, Right );
		Merge( A, TmpArray, Left, Center + 1, Right );
	}
}

void Mergesort( ElementType A[ ], int N )
{
	ElementType *TmpArray;

	TmpArray = malloc( N * sizeof( ElementType ) );
	if( TmpArray != NULL )
	{
		MSort( A, TmpArray, 0, N - 1 );
		free( TmpArray );
	}
	else
		printf( "No space for tmp array!!!" );
}
/* END */

/* START: fig7_13.txt */
/* Return median of Left, Center, and Right */
/* Order these and hide the pivot */

ElementType Median3( ElementType A[ ], int Left, int Right )
{
	int Center = ( Left + Right ) / 2;

	if( A[ Left ] > A[ Center ] )
		Swap( &A[ Left ], &A[ Center ] );
	if( A[ Left ] > A[ Right ] )
		Swap( &A[ Left ], &A[ Right ] );
	if( A[ Center ] > A[ Right ] )
		Swap( &A[ Center ], &A[ Right ] );

	/* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */
	Swap( &A[ Center ], &A[ Right - 1 ] );  /* Hide pivot */
	return A[ Right - 1 ];                /* Return pivot */
}
/* END */

/* START: fig7_14.txt */
#define Cutoff ( 3 )
void Qsort( ElementType A[ ], int Left, int Right )
{
	int i, j;
	ElementType Pivot;

	if( Left + Cutoff <= Right )
	{
		Pivot = Median3( A, Left, Right );
		i = Left; j = Right - 1;
		for( ; ; )
		{
			while( A[ ++i ] < Pivot ){ }
			while( A[ --j ] > Pivot ){ }
			if( i < j )
				Swap( &A[ i ], &A[ j ] );
			else
				break;
		}
		Swap( &A[ i ], &A[ Right - 1 ] );  /* Restore pivot */

		Qsort( A, Left, i - 1 );
		Qsort( A, i + 1, Right );
	}
	else  /* Do an insertion sort on the subarray */
		InsertionSort( A + Left, Right - Left + 1 );
}
/* END */

/* START: fig7_12.txt */
void Quicksort( ElementType A[ ], int N )
{
	Qsort( A, 0, N - 1 );
}
/* END */

/* START: fig7_16.txt */
/* Places the kth smallest element in the kth position */
/* Because arrays start at 0, this will be index k-1 */
void Qselect( ElementType A[ ], int k, int Left, int Right )
{
	int i, j;
	ElementType Pivot;

	if( Left + Cutoff <= Right )
	{
		Pivot = Median3( A, Left, Right );
		i = Left; j = Right - 1;
		for( ; ; )
		{
			while( A[ ++i ] < Pivot ){ }
			while( A[ --j ] > Pivot ){ }
			if( i < j )
				Swap( &A[ i ], &A[ j ] );
			else
				break;
		}
		Swap( &A[ i ], &A[ Right - 1 ] );  /* Restore pivot */

		if( k <= i )
			Qselect( A, k, Left, i - 1 );
		else if( k > i + 1 )
			Qselect( A, k, i + 1, Right );
	}
	else  /* Do an insertion sort on the subarray */
		InsertionSort( A + Left, Right - Left + 1 );
}
/* END */

/* ROUTINES TO TEST THE SORTS */
void Permute( ElementType A[ ], int N )
{
	int i;

	for( i = 0; i < N; i++ )
		A[ i ] = i;
	for( i = 1; i < N; i++ )
		Swap( &A[ i ], &A[ rand( ) % ( i + 1 ) ] );
}

void Checksort( ElementType A[ ], int N )
{
	int i;
	for( i = 0; i < N; i++ )
		if( A[ i ] != i )
			printf( "Sort fails: %d %d\n", i, A[ i ] );
	printf( "Check completed\n" );
}

void Copy( ElementType Lhs[ ], const ElementType Rhs[ ], int N )
{
	int i;
	for( i = 0; i < N; i++ )
		Lhs[ i ] = Rhs[ i ];
}

#define MaxSize 7000
int Arr1[ MaxSize ];
int Arr2[ MaxSize ];

main( )
{
	int i;

	for( i = 0; i < 10; i++ )
	{
		Permute( Arr2, MaxSize );
		Copy( Arr1, Arr2, MaxSize );
		InsertionSort( Arr1, MaxSize );
		Checksort( Arr1, MaxSize );

		Copy( Arr1, Arr2, MaxSize );
		Shellsort( Arr1, MaxSize );
		Checksort( Arr1, MaxSize );

		Copy( Arr1, Arr2, MaxSize );
		Heapsort( Arr1, MaxSize );
		Checksort( Arr1, MaxSize );

		Copy( Arr1, Arr2, MaxSize );
		Mergesort( Arr1, MaxSize );
		Checksort( Arr1, MaxSize );

		Copy( Arr1, Arr2, MaxSize );
		Quicksort( Arr1, MaxSize );
		Checksort( Arr1, MaxSize );

		Copy( Arr1, Arr2, MaxSize );
		Qselect( Arr1, MaxSize / 2 + 1 + i, 0, MaxSize - 1 );
		if( Arr1[ MaxSize / 2 + i ] != MaxSize / 2 + i )
			printf( "Select error: %d %d\n", MaxSize / 2 + i , Arr1[ MaxSize / 2 + i ] );
		else
			printf( "Select works\n" );
	}

	return 0;
}

