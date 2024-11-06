#include "LevelManager.h"
#include "CoilyComponent.h"


namespace dae
{
	void LevelManager::SetCurrentQbertNode(GridNode* pNode)
	{
		m_CurrentQbertNode = pNode;
		
		for (auto pCoily : m_pCoilies)
		{
			if (pCoily != nullptr)
				pCoily->Hunt(*pNode);
		}
	}
}

