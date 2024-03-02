#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
class TransformComponent;

dae::GameObject::GameObject()
	: m_transform()
	, m_texture(nullptr)
	, m_pComponents()
	, m_pTransformComponent(nullptr)
	, m_LocalPosition{}
{
	//InitializeTransformComponent();
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
	const auto& pos = m_transform.GetPosition();
	if (m_texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	for (auto& comp : m_pComponents)
	{
		comp->Render();
	}

	for (auto& child : m_Children)
	{
		child->Render();
	}

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	//m_transform.SetPosition(x, y, 0.0f);

	m_pTransformComponent->SetPosition(x, y, 0.0f);
	//m_LocalPosition = glm::vec3(x, y, 0.0f);


	//return m_LocalPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	//m_LocalPosition = pos;

	m_pTransformComponent->SetPosition(pos);
}

glm::vec3& dae::GameObject::GetWorldPosition()
{
	return m_pTransformComponent->GetWorldPosition();
}

glm::vec3& dae::GameObject::GetLocalPosition() 
{
	return m_pTransformComponent->GetLocalPosition();

	//return m_pTransformComponent->GetLocalPosition();
}

//
void dae::GameObject::InitializeTransformComponent()
{
	//m_pTransformComponent = new TransformComponent();
	//AddComponent(pComp.get());

			//	m_pTransformComponent = comp;
		//	std::unique_ptr<TransformComponent> pComp(comp);
		//	AddComponent(comp);

	//m_pTransformComponent = new TransformComponent(shared_from_this());
	//std::unique_ptr<TransformComponent> pComp(m_pTransformComponent);

	std::unique_ptr<TransformComponent> pComp = std::make_unique<TransformComponent>(shared_from_this());
	m_pTransformComponent = pComp.get();

	AddComponent(std::move(pComp));
}

//TransformComponent* dae::GameObject::GetTransformComponent()
//{
//	return m_pTransformComponent;
//}

void dae::GameObject::RemoveComponent(BaseComponent* pComponent/*, bool deleteObject*/)
{

	auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(),
		[pComponent](const std::unique_ptr<dae::BaseComponent>& componentPtr) {
			return componentPtr.get() == pComponent;
		});

	//auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(),
	//	[pComponent](const BaseComponent* componentPtr) {
	//		return componentPtr == pComponent;
	//	});

	if (it != m_pComponents.end())
	{
		m_pComponents.erase(it);
	}
}

void dae::GameObject::SetParent(const std::shared_ptr<GameObject>& newParent)
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
	//else
	//{
	//	/////


	//}

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

	// 5. Update position, rotation, and scale
	//UpdateTransformRelativeToNewParent();
	//m_pTransformComponent->GetWorldPosition();
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

