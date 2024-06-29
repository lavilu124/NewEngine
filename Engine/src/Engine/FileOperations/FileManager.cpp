#include "FileManager.h"
#include <fstream>
#include <sstream>

#include <filesystem>

using std::filesystem::directory_iterator;

std::map <std::string, Input::InputAction> FileManager::inputs;
std::map <std::string, std::function<void()>> FileManager::m_functionMap;

std::vector <sf::Texture> textures;
std::vector <sf::SoundBuffer> buffers;

std::map <std::string, sf::Sound> FileManager::sounds;
std::map <std::string, sf::Sprite> FileManager::sprites;

void FileManager::AddInputFunc(std::string name, std::function<void()> function) {
    m_functionMap[name] = function;
}
void FileManager::CreateInput(std::string Name, Input::inputType Type, Input::KeyType Key, Input::inputPart Part, std::string OnInput, std::string OffInput) {
    inputs.emplace(Name, Input::InputAction(
        Type,
        Key,
        Name,
        Part,
        [=]() { m_functionMap[OnInput](); },
        [=]() { m_functionMap[OffInput](); }
    ));
}
void FileManager::CreateInput(std::string Name, Input::inputType Type, Input::KeyType Key, Input::inputPart Part, std::string OnInput) {
    inputs.emplace(Name, Input::InputAction(
        Type,
        Key,
        Name,
        Part,
        [=]() { m_functionMap[OnInput](); }
    ));
}
void FileManager::LoadInput() {
    std::ifstream file("../Resources\\settings\\Input.cfg");
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            // Skip empty lines and comments
            continue;
        }

        std::istringstream iss(line);
        std::string Type, Key, Name, Part, OnInput, OffInput;


        std::getline(iss, Type, ',');
        std::getline(iss, Key, ',');
        std::getline(iss, Name, ',');
		std::getline(iss, Part, ',');
        std::getline(iss, OnInput, ',');
        std::getline(iss, OffInput, ',');

        if (!Name.empty() && Name[0] == ' ') {
            Name.erase(0, 1);
        }

        if (!Part.empty() && Part[0] == ' ') {
            Part.erase(0, 1);
        }

        if (!OnInput.empty() && OnInput[0] == ' ') {
            OnInput.erase(0, 1);
        }

        if (!OffInput.empty() && OffInput[0] == ' ') {
            OffInput.erase(0, 1);
        }


        // Check if OnInput function exists in FunctionMap
        if (m_functionMap.find(OnInput) == m_functionMap.end()) {
            continue;
        }
        
        Input::inputPart inputPart = Input::inputPart::Pressed; // Default to Pressed
        if (Part == "started") {
            inputPart = Input::inputPart::Started;
        }
        else if (Part == "released") {
            inputPart = Input::inputPart::Released;
        }

        Input::inputType InputType = Input::inputType::KeyboardKey;
        Input::KeyType InputKey;
		if (Type == "MouseKey") {
            InputKey = sf::Mouse::Button(std::stoi(Key));
			InputType = Input::inputType::MouseButton;
        }
        else if (Type == "ControllerKey") {
            InputKey = sf::Joystick::Axis(std::stoi(Key));
            InputType = Input::inputType::ControllerButton;
        }
        else {
            InputKey = sf::Keyboard::Key(std::stoi(Key));
        }

        if (!OffInput.empty()) {
            CreateInput(Name, InputType, InputKey, inputPart, OnInput, OffInput);
        }
        else {
            CreateInput(Name, InputType, InputKey, inputPart, OnInput);
        }
    }
}

void FileManager::SetPaths() {
    std::string Folders[] = { "\\Resources\\graphics", "\\Resources\\sounds" };
    std::string path = std::filesystem::current_path().string();
    const std::string remove = "\\Engine";

    const std::string::size_type pos = path.find(remove);
    if (pos != std::string::npos) {
        path.erase(pos, remove.length());
    }

    std::ofstream CurFile(path);

    for (int i = 0; i < sizeof(Folders) / sizeof(Folders[0]); i++)
    {
        GetFilesInDir(path + Folders[i]);
    }
}

int GetFileCount(std::string Directory) {

    int FileCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(Directory)) {
        if (entry.is_regular_file()) {
            FileCount++;
        }
    }

    return FileCount;
}

void FileManager::GetFilesInDir(std::string Dir) {
    if (Dir.find("graphics") != std::string::npos) {
        textures.reserve(GetFileCount(Dir));
	}
    else if (Dir.find("sounds") != std::string::npos) {
        buffers.reserve(GetFileCount(Dir));
    }

    for (const auto& File : directory_iterator(Dir)) {
        std::string pathString{ File.path().u8string() };

        std::string fileName = pathString.substr(pathString.find_last_of("\\") + 1, pathString.length() - 1);
        LoadAsset(pathString, fileName);
    }
}

void FileManager::LoadAsset(std::string Path, std::string FileName) {
    if (FileName.find(".png") != std::string::npos) {
        sf::Texture NewTexture;
        NewTexture.loadFromFile(Path);
		textures.push_back(NewTexture);


        sf::Sprite NewSprite;
        NewSprite.setTexture(textures[textures.size() - 1]);
        sprites[FileName] = NewSprite;
	}
    else if (FileName.find(".wav") != std::string::npos) {
        sf::SoundBuffer NewBuffer;
        NewBuffer.loadFromFile(Path);
        buffers.push_back(NewBuffer);

        sf::Sound newSound;
        newSound.setBuffer(buffers[buffers.size() - 1]);
        sounds[FileName] = newSound;
    }
}