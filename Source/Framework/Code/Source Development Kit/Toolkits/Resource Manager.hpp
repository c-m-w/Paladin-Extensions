/// Resource Manager.hpp

#pragma once

class CResourceManager: public IBase
{
private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

	std::map< std::string, std::string > _LoadedResources { };

public:

	std::string& GetResource( const std::string& strRelativePath );
	bool ResourceExists( const std::string& strRelativePath );

} extern _ResourceManager;
