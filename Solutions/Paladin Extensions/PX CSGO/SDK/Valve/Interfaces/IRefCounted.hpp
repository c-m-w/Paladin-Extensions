#pragma once

class IRefCounted
{
	volatile long lRefCounted;

public:
	virtual void Destructor( char bDelete ) = 0;
	virtual bool OnFinalRelease( ) = 0;

	void Unreference( )
	{
		if ( InterlockedDecrement( &lRefCounted ) == 0 && OnFinalRelease( ) )
			Destructor( 1 );
	}
};

inline void ClearRefCountedVector( CUtlVector< IRefCounted* > *vecRef )
{
	for ( auto i = 0; i < vecRef->m_Size; i++ )
	{
		auto &pElement = vecRef->m_pElements[ i ];
		if ( pElement != nullptr )
		{
			pElement->Unreference( );
			pElement = nullptr;
		}
	}
	vecRef->RemoveAll( );
}
