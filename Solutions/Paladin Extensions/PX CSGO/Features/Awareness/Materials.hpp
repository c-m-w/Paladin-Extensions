/// Materials.hpp

#pragma once

namespace PX::Features::Awareness
{
	bool PX_API CreateMaterials( );
	void PX_API RemoveMaterials( );
	bool PX_API OverrideMaterial( player_ptr_t pLocalPlayer, IMatRenderContext* pContext, const DrawModelState_t& _State, const ModelRenderInfo_t& _Info, matrix3x4_t* pMatrix, void* fnDrawModelExecute );
	void PX_API RenderEntities( );
}
