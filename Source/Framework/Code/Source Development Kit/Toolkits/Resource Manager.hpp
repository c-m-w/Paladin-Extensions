/// Resource Manager.hpp

#pragma once

class CResourceManager: public IBase
{
private:

	bool Initialize( ) override;

public:

	void Uninitialize( ) override;
} inline _ResourceManager;
