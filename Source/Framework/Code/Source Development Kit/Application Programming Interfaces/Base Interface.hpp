/// Base Interface.hpp

#pragma once

/** \brief Base interface which every class that needs to be initialized\n 
			should inherit. */
class IBase
{
protected:

	/** \brief Initialize implementing class. */
	/** \return Whether or not initialization was successful. */
	[ [ nodiscard ] ] virtual bool Initialize( ) = 0;
	/** \brief Uninitialize implementing. */
	virtual void Uninitialize( ) = 0;

	/** \brief Whether or not the class has been initialized. */
	bool bInitialized;

	IBase( ): bInitialized( false )
	{ }

	virtual ~IBase( ) = default;

public:

	IBase( const IBase & ) = delete;
	IBase( IBase && ) = delete;
	IBase &operator=( const IBase & ) = delete;
	IBase &operator=( IBase && ) = delete;

	/** \brief Sets up implementing class for use. */
	/** \return Whether or not initialization was successful. */
	[ [ nodiscard ] ] bool Setup( )
	{
		return bInitialized = Initialize( );
	};

	/** \brief Shuts down implementing class from public use. */
	void Shutdown( )
	{
		if ( bInitialized )
			Uninitialize( );

		bInitialized = false;
	}

	/** \brief Gets information about the initialization state of the implementing class. */
	/** \return Whether or not the implementing class is initialized. */
	bool GetInitializationState( ) const
	{
		return bInitialized;
	}
};
