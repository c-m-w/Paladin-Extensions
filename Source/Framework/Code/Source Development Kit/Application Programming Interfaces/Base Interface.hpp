/// Base Interface.hpp

#pragma once

/** \brief Base interface which every class that needs to be initialized\n
			should inherit. */
class IBase
{
protected:

	[ [ nodiscard ] ] virtual bool Initialize( ) = 0;
	virtual void Uninitialize( ) = 0;

	bool bInitialization;

public:

	IBase( ): bInitialization( false )
	{ }

	virtual ~IBase( ) = default;
	IBase( const IBase & ) = delete;
	IBase( IBase && ) = delete;
	IBase &operator=( const IBase & ) = delete;
	IBase &operator=( IBase && ) = delete;

	[ [ nodiscard ] ] bool Setup( )
	{
		return bInitialization = Initialize( );
	};

	void Shutdown( )
	{
		if ( bInitialization )
			Uninitialize( );

		bInitialization = false;
	}

	bool GetInitializationState( )
	{
		return bInitialization;
	}
};
