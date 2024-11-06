#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
class TransformComponent;

unsigned int dae::GameObject::m_NextID = 0;


dae::GameObject::GameObject()
	: m_pComponents()
	, m_pTransformComponent(nullptr)
	, m_LocalPosition{}
{
	m_ID = m_NextID++;  
}

dae::GameObject::~GameObject() = default;


void dae::GameObject::Update()
{
	if (m_IsActive == false)
	{
		return;
	}
	for (auto& component : m_pComponents)
	{
		if (component->IsActive()) {
			component->Update();
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		if (component->IsActive()) {
			component->Render();
		}
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_pTransformComponent->SetPosition(x, y, 0.0f);
	SetChildrenDirty();
}


void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_pTransformComponent->SetPosition(pos);
	SetChildrenDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec2& pos)
{
	m_pTransformComponent->SetPosition(pos);
	SetChildrenDirty();
}

void dae::GameObject::SetChildrenDirty()
{
	for (auto& child : m_Children)
	{
		auto transform  = child->GetComponent<TransformComponent>();
		if (transform)
		{
			transform->SetDirty();
		}

	}
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
	std::unique_ptr<TransformComponent> pComp = std::make_unique<TransformComponent>(*this);
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

void dae::GameObject::SetParent(GameObject* newParent, bool keepWorldPosition)
{
	// 1. Check if the new parent is valid
	if (newParent == this || IsDescendantOf(*newParent))
	{
		// Invalid parent, possibly throw an exception or log an error
		return;
	}
	if (newParent == nullptr)
	{
		//oldParent->m_Children.erase(std::remove(oldParent->m_Children.begin(), oldParent->m_Children.end(), shared_from_this()), oldParent->m_Children.end());
		glm::vec3 worldPos = GetWorldPosition();
		SetLocalPosition(worldPos);
	}
	else
	{
		if (keepWorldPosition)
		{
			//m_pTransformComponent->SetPosition(GetLocalPosition() - newParent->GetWorldPosition());
			SetLocalPosition(GetLocalPosition() - newParent->GetWorldPosition());
		}
	}

	// 2. Remove itself from the previous parent (if any)
	if (auto oldParent = m_parent/*.lock()*/)
	{
		oldParent->m_Children.erase(std::remove(oldParent->m_Children.begin(), oldParent->m_Children.end(), /*shared_from_this()*/ this), oldParent->m_Children.end());
	}

	// 3. Set the given parent on itself
	m_parent = newParent; // Assuming m_parent is a std::weak_ptr<GameObject>

	// 4. Add itself as a child to the given parent
	if (newParent)
	{
		newParent->m_Children.push_back(/*shared_from_this()*/ this);
	}
}

bool dae::GameObject::IsDescendantOf(const GameObject& potentialAncestor) const //automatically check for nullptr
{
	// Recursive function to check if 'this' is a descendant of 'potentialAncestor'
	auto parent = m_parent;
	while (parent)
	{
		if (parent == &potentialAncestor)
		{
			return true;
		}
		parent = parent->m_parent;
	}
	return false;
}

void dae::GameObject::SetActive(bool active)
{	
	m_IsActive = active;
	for (auto& child : m_Children)
	{
		child->SetActive(active);
	}
}

bool dae::GameObject::IsActive() const
{
	return m_IsActive;
}

