#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../SystemLogic/InputAction.h"

class FileManager
{
public:
	static void LoadInput();
	static void AddInputFunc(std::string name, std::function<void()> function);

	static void SetPaths();

public:
	static std::map <std::string, Input::InputAction> inputs;
	static std::map < std::string, sf::Sprite> sprites;
	static std::map < std::string, sf::Sound> sounds;
private:
	static void GetFilesInDir(std::string Dir);
	static void CreateInput(std::string Name, Input::inputType Type, Input::KeyType Key, Input::inputPart Part, std::string OnInput, std::string OffInput);
	
	static void CreateInput(std::string Name, Input::inputType Type, Input::KeyType Key, Input::inputPart Part, std::string OnInput);
	static void LoadAsset(std::string Path, std::string FileName);

private:
	static std::map <std::string, std::function<void()>> m_functionMap;
};

