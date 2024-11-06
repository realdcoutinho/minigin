#pragma once
class DiffuseMaterial final : public Material<DiffuseMaterial>
{
public:
	DiffuseMaterial();
	~DiffuseMaterial() override = default;

	DiffuseMaterial(const DiffuseMaterial& other) = delete;
	DiffuseMaterial(DiffuseMaterial&& other) noexcept = delete;
	DiffuseMaterial& operator=(const DiffuseMaterial& other) = delete;
	DiffuseMaterial& operator=(DiffuseMaterial&& other) noexcept = delete;

	void SetDiffuseTexture(const std::wstring& assetFile);
	void FlipNormals();
	void InitializeEffectVariables() override;

protected:


private:
	TextureData* m_pDiffuseTexture{nullptr};
};

