/// CImage.hpp

#pragma once

class CImage: public IWidget
{
private:

	void CreateDrawables( ) override;

	std::string strResourceName { };

public:

	CImage( const std::string& strResourceName );
};
