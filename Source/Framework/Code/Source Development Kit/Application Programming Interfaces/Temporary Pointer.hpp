/// Temporary Pointer.hpp

#pragma once

template< typename _Context >
union UHookCallback
{
	void ( __cdecl *fn )( void *pThis, _Context* );
	void *p;
};

template < typename _t >
class temp_ptr
{
	_t *p;
public:
	temp_ptr( )
	{
		p = new _t;
	}
	template < typename... _Construction >
	temp_ptr( _Construction... _Constructions )
	{
		p = new _t ( _Constructions... );
	}
	operator _t *( )
	{
		return p;
	}
	~temp_ptr( )
	{
		delete p;
	}
	temp_ptr( const temp_ptr & ) = delete;
	temp_ptr( temp_ptr && ) = delete;
	temp_ptr &operator= ( const temp_ptr & ) = delete;
	temp_ptr &operator= ( temp_ptr && ) = delete;
};
