/// CVectorGraphic.hpp

#pragma once

class CVectorGraphic: public IWidget
{
private:

	void CreateDrawables( ) override;

	std::string strResourceName { };

public:

	CVectorGraphic( const std::string& strResourceName );
};
