#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
class TransformComponent;

dae::GameObject::GameObject()
	: m_pComponents()
	, m_pTransformComponent(nullptr)
	, m_LocalPosition{}
{
}

dae::GameObject::~GameObject() = default;
//{
//	//delete m_pTransformComponent;
//}

void dae::GameObject::Update(float elaspsed)
{
	for (auto& comp : m_pComponents)
	{
		comp->Update(elaspsed);
	}
	for (auto& child : m_Children)
	{
		child->	Update(elaspsed);
	}
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_pComponents)
	{
		comp->Render();
	}

	for (auto& child : m_Children)
	{
		child->Render();
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_pTransformComponent->SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_pTransformComponent->SetPosition(pos);
}

glm::vec3& dae::GameObject::GetWorldPosition()
{
	return m_pTransformComponent->GetWorldPosition();
}

glm::vec3& dae::GameObject::GetLocalPosition() 
{
	return m_pTransformComponent->GetLocalPosition();
}

//
void dae::GameObject::InitializeTransformComponent()
{
	std::unique_ptr<TransformComponent> pComp = std::make_unique<TransformComponent>(shared_from_this());
	m_pTransformComponent = pComp.get();
	AddComponent(std::move(pComp));
}

void dae::GameObject::RemoveComponent(BaseComponent* pComponent/*, bool deleteObject*/)
{

	auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(),
		[pComponent](const std::unique_ptr<dae::BaseComponent>& componentPtr) {
			return componentPtr.get() == pComponent;
		});

	if (it != m_pComponents.end())
	{
		m_pComponents.erase(it);
	}
}

void dae::GameObject::SetParent(const std::shared_ptr<GameObject>& newParent, bool keepWorldPosition)
{
	// 1. Check if the new parent is valid
	if (newParent.get() == this || IsDescendantOf(newParent))
	{
		// Invalid parent, possibly throw an exception or log an error
		return;
	}
	if (newParent.get() == nullptr)
	{
		glm::vec3 worldPos = GetWorldPosition();
		SetLocalPosition(worldPos);
	}
	else
	{
		if (keepWorldPosition)
		{
			m_pTransformComponent->SetPosition(GetLocalPosition() - newParent->GetWorldPosition());
		}
	}

	// 2. Remove itself from the previous parent (if any)
	if (auto oldParent = m_parent.lock())
	{
		oldParent->m_Children.erase(std::remove(oldParent->m_Children.begin(), oldParent->m_Children.end(), shared_from_this()), oldParent->m_Children.end());
	}

	// 3. Set the given parent on itself
	m_parent = newParent; // Assuming m_parent is a std::weak_ptr<GameObject>

	// 4. Add itself as a child to the given parent
	if (newParent)
	{
		newParent->m_Children.push_back(shared_from_this());
	}
}

bool dae::GameObject::IsDescendantOf(const std::shared_ptr<GameObject>& potentialAncestor) const
{
	// Recursive function to check if 'this' is a descendant of 'potentialAncestor'
	auto parent = m_parent.lock();
	while (parent)
	{
		if (parent == potentialAncestor)
		{
			return true;
		}
		parent = parent->m_parent.lock();
	}
	return false;
}

