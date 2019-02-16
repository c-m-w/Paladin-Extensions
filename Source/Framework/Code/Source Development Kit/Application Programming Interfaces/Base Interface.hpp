/// Base Interface.hpp

#pragma once

/** \brief Base interface which every class that needs to be initialized\n
			should inherit. */
class IBase
{
protected:

	/** \brief Initialize child class */
	/** \return Initialization success state */
	[ [ nodiscard ] ] virtual bool Initialize( ) = 0;
	/** \brief Uninitialize child class */
	virtual void Uninitialize( ) = 0;

	/** \brief Defines initialization state */
	bool bInitialization;

public:

	IBase( ): bInitialization( false )
	{ }

	virtual ~IBase( ) = default;
	IBase( const IBase & ) = delete;
	IBase( IBase && ) = delete;
	IBase &operator=( const IBase & ) = delete;
	IBase &operator=( IBase && ) = delete;

	/** \brief Sets up child class for public use */
	/** \return Setup success state */
	[ [ nodiscard ] ] bool Setup( )
	{
		return bInitialization = Initialize( );
	};

	/** \brief Shuts down child class from public use */
	void Shutdown( )
	{
		if ( bInitialization )
			Uninitialize( );

		bInitialization = false;
	}

	/** \brief Returns if child class has been initialized through Setup member function */
	/** \return Encapsulated initialization state */
	bool GetInitializationState( )
	{
		return bInitialization;
	}
};
