#pragma once
namespace dae
{
	class ServicesLoader final
	{
	public:
		ServicesLoader();
		~ServicesLoader() = default;
	private:
		void LoadServices();
		void LoadAudioService();

	};
}


