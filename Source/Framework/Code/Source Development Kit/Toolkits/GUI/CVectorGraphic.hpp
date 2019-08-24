/// CVectorGraphic.hpp

#pragma once

class CVectorGraphic: public IWidget
{
private:

	void CreateDrawables( ) override;

	std::string strResourceName = ENC( "PX Logo.svg" );
	unsigned char* bImageData = nullptr;

public:

	CVectorGraphic( );

	void SetResourceName( const std::string& strNewResourceName );
};
