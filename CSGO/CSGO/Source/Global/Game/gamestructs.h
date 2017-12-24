#pragma once

struct audio_t
{
	vector_t localSound[8] { };
	int soundscapeIndex { };
	int localBits { };
	int entIndex { };
};

struct fog_t
{
	vector_t dirPrimary { };
	int colorPrimary { };
	int colorSecondary { };
	BYTE unknown2[0x8] { };
	float start { };
	float end { };
	BYTE unknown3[0x4] { };
	float maxdensity { };
	BYTE unknown4[0x14] { };
	int enable { };
	int blend { };
	BYTE unknown5[0x3] { };
	float flHDRColorScale { };
};

struct skybox3D_t
{
	int scale { };
	vector_t origin { };
	int area { };
	BYTE unknown1[0x4] { };
	fog_t fog;
	BYTE unknown2[0x4] { };
};

struct attributelist_t
{
	int lengthprop32; // 0x0
	int iAttributeDefinitionIndex; // 0x4
	int iRawValue32; // 0x8
	int iRawInitialValue32; // 0xc
	int nRefundableCurrency; // 0x10
	int bSetBonus; // 0x14
};
