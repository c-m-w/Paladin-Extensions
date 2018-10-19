/// Tools.inl

#pragma once

namespace PX::Tools
{
	template< class _Child > _Child& PX_API ASingleton< _Child >::Get( )
	{
		static _Child _ChildClassObject { };
		return _ChildClassObject;
	}

	template< typename _fn > _fn CStandardHook::GetOriginalFunction( unsigned uIndex )
	{
		px_assert( uIndex >= 0 && uIndex <= zTableLength );
		return reinterpret_cast< _fn >( pOldTable[ uIndex ] );
	}

	// INFO: Differentiates casting from like or unlike string types
	template< typename _To, typename _From > px_abstract_class AStringCastImplementation
	{
	public:
		static _To Cast( const _From& _Source )
		{
			return _To( _Source.begin( ), _Source.end( ) );
		}
	};
	template< typename _From > px_abstract_class AStringCastImplementation< _From, _From >
	{
	public:
		static const _From& Cast( const _From& _Source )
		{
			return _Source;
		}
	};

	// INFO: Interface for C-Style string casting
	template< typename > px_abstract_class AStringTypeOfCharacter;
	template< > px_abstract_class AStringTypeOfCharacter< Types::cstr_t >
	{
	public:
		typedef Types::str_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::cstr16_t >
	{
	public:
		typedef Types::str16_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::cstr32_t >
	{
	public:
		typedef Types::str32_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::wcstr_t >
	{
	public:
		typedef Types::wstr_t wrap_t;
	};
	template< > px_abstract_class AStringTypeOfCharacter< Types::bcstr_t >
	{
	public:
		typedef Types::bstr_t wrap_t;
	};

	template< typename _fn > _fn CTrampolineHook::GetOriginalFunction( unsigned uIndex )
	{
		return reinterpret_cast< _fn >( uIndex == 0 || uIndex > sTable ? ptr_t( ) : pOldTable[ uIndex ] );
	}

	template< typename _To, typename _From > _To PX_API string_cast( const _From& _Source )
	{
		return AStringCastImplementation< _To, _From >::Cast( _Source );
	}
	template< typename _To, typename _From > _To PX_API string_cast( _From* _Source )
	{
		return AStringCastImplementation< _To, typename AStringTypeOfCharacter< const _From* >::wrap_t >::Cast( _Source );
	}
}
