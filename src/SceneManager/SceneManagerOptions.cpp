#include "SceneManager/SceneManagerOptions.h"
#include "SceneGraph/TextureList.h"
#include "SceneGraph/DrawableNode.h"
#include "Controller/GameController.h"
#include "Controller/Localization.h"
#include "Controller/MusicController.h"
#include "Controller/SoundController.h"

namespace MenuFunctions
{
    void Keybindings(SceneManagerOptions* sm)
    {
        sm->Keybindings();
    }
    void Close(SceneManagerOptions* sm)
    {
        sm->Close();
    }
    void SetKey(SceneManagerOptions* sm, Configuration::Keys key)
    {
        sm->SetKey(key);
    }
    void SoundOptions(SceneManagerOptions* sm)
    {
        sm->SoundOptions();
    }
    void ChangeMusic(SceneManagerOptions* sm)
    {
        sm->ChangeMusic();
    }
    void ChangeSfx(SceneManagerOptions* sm)
    {
        sm->ChangeSfx();
    }
}

SceneManagerOptions::SceneManagerOptions()
{
    //ctor
    //ctor
    int padding = 8;
    m_soundOptionWidth = 100.0f;
    m_configKey = false;
    m_finished = false;
    m_changeMusic = false;
    m_changeSfx = false;
    m_sfxRect = nullptr;
    m_musicRect = nullptr;

    //Set Background
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::InGameMenu));
    DrawableNode* background = new DrawableNode(backgroundSprite);
    int x = GameController::getInstance()->GetWindowWidth() - backgroundSprite->getLocalBounds().width;
    x /= 2;
    int y = GameController::getInstance()->GetWindowHeight() - backgroundSprite->getLocalBounds().height;
    y /= 2;
    background->moveNode(x,y);
    m_gui->addChild(background);
    m_menuWidth = backgroundSprite->getLocalBounds().width;

    //Set Menu function
    m_mainMenu = new MenuNode(m_menuWidth - 2* padding);
    m_mainMenu->CancelAvailable(true);
    m_mainMenu->CallOnCancel(std::function<void()>(std::bind(&MenuFunctions::Close,this)));
    Localization* local = Localization::GetInstance();
    m_mainMenu->AddOption(local->GetLocalization("menu.keyBindings"),std::function<void()>(std::bind(&MenuFunctions::Keybindings,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.sound"),std::function<void()>(std::bind(&MenuFunctions::SoundOptions,this)),true);
    m_mainMenu->AddOption(local->GetLocalization("menu.close"),std::function<void()>(std::bind(&MenuFunctions::Close,this)),true);
    background->addChild(m_mainMenu);

    //Set Menu looks
    m_mainMenu->SetPadding(padding,padding);
    m_mainMenu->SetBackgroundColor(sf::Color::Transparent);
    m_mainMenu->SetForegroundColor(sf::Color::Black);
    m_mainMenu->SetOutlineColor(sf::Color::Transparent);
    m_mainMenu->SetSelectedTexture(TextureList::getTexture(TextureList::InGameMenuSelected));
    m_mainMenu->SetFontSize(45);
    m_mainMenu->SetSpacing(34);
}

SceneManagerOptions::~SceneManagerOptions()
{
    //dtor
}

void SceneManagerOptions::Tick()
{
    GameController* controller = GameController::getInstance();
    if(m_configKey)
    {
        //set Keybindings
        Configuration* config = Configuration::GetInstance();
        sf::Keyboard::Key key = config->GetLastKey();
        if(key != sf::Keyboard::Unknown)
        {
            if(config->SetKeyConfig(m_updateKey, key))
            {
                GameController::getInstance()->IsKeyPressed(m_updateKey);
                m_keybindings->AddValueToOption((int)m_updateKey, config->KeyToString(key));
                m_configKey = false;
            }
        }
    }
    else if(m_changeMusic)
    {
        if(controller->IsKeyPressed(Configuration::Accept) || controller->IsKeyPressed(Configuration::Cancel))
        {
            m_changeMusic = false;
        }
        else if(controller->IsKeyPressed(Configuration::MoveLeft))
        {
            MusicController* musicController = MusicController::GetInstance();
            float volume = musicController->GetVolume();
            volume -= 10.0f;
            if(volume < 0.0f)
                volume = 0.0f;
            musicController->SetVolume(volume);
            Configuration::GetInstance()->SetMusicVolume(volume);
            SetMusicRect();
        }
        else if(controller->IsKeyPressed(Configuration::MoveRight))
        {
            MusicController* musicController = MusicController::GetInstance();
            float volume = musicController->GetVolume();
            volume += 10.0f;
            if(volume > 100.0f)
                volume = 100.0f;
            musicController->SetVolume(volume);
            Configuration::GetInstance()->SetMusicVolume(volume);
            SetMusicRect();
        }
    }
    else if(m_changeSfx)
    {
        if(controller->IsKeyPressed(Configuration::Accept) || controller->IsKeyPressed(Configuration::Cancel))
        {
            m_changeSfx = false;
        }
        else if(controller->IsKeyPressed(Configuration::MoveLeft))
        {
            SoundController* soundController = SoundController::GetInstance();
            float volume = soundController->GetVolume();
            volume -= 10.0f;
            if(volume < 0.0f)
                volume = 0.0f;
            soundController->SetVolume(volume);
            Configuration::GetInstance()->SetSfxVolume(volume);
            SetSfxRect();
        }
        else if(controller->IsKeyPressed(Configuration::MoveRight))
        {
            SoundController* soundController = SoundController::GetInstance();
            float volume = soundController->GetVolume();
            volume += 10.0f;
            if(volume > 100.0f)
                volume = 100.0f;
            soundController->SetVolume(volume);
            Configuration::GetInstance()->SetSfxVolume(volume);
            SetSfxRect();
        }
    }
    else
    {
        m_mainMenu->CheckKeyboardInput();
    }
}

bool SceneManagerOptions::IsFinished()
{
    return m_finished;
}

void SceneManagerOptions::Close()
{
    m_finished = true;
}

void SceneManagerOptions::Keybindings()
{
    m_keybindings = new MenuNode(m_menuWidth);
    m_keybindings->SetPadding(3,0);
    m_keybindings->SetMaxShownOptions((int)Configuration::KEYS_END);
    m_keybindings->CancelAvailable(true);
    m_mainMenu->addChild(m_keybindings);
    Configuration* config = Configuration::GetInstance();
    Configuration::Keys key;
    Localization* local = Localization::GetInstance();
    for(int i = 0; i < (int)Configuration::KEYS_END; i++)
    {
        key = (Configuration::Keys) i;
        m_keybindings->AddOption(local->GetLocalization("menu.keyBindings." + config->KeyToString(key)), std::function<void()>(std::bind(&MenuFunctions::SetKey,this, key)));
        m_keybindings->AddValueToOption(i, config->KeyToString(config->GetKey(key)));
    }
}

void SceneManagerOptions::SoundOptions()
{
    m_soundOptions = new MenuNode(m_menuWidth);
    m_soundOptions->SetPadding(3,0);
    m_soundOptions->SetMaxShownOptions((int)Configuration::KEYS_END);
    m_soundOptions->CancelAvailable(true);
    m_mainMenu->addChild(m_soundOptions);
    Configuration* config = Configuration::GetInstance();
    Configuration::Keys key;
    Localization* local = Localization::GetInstance();
    m_soundOptions->AddOption(local->GetLocalization("menu.sound.music"), std::function<void()>(std::bind(&MenuFunctions::ChangeMusic, this)));
    m_soundOptions->AddOption(local->GetLocalization("menu.sound.sfx"), std::function<void()>(std::bind(&MenuFunctions::ChangeSfx, this)));

    m_musicRect = new sf::RectangleShape();
    SetMusicRect();
    DrawableNode* musicNode = new DrawableNode(m_musicRect);
    musicNode->moveNode(m_menuWidth - m_soundOptionWidth - 5.0f, 2.0f);
    m_soundOptions->AddNodeToOption(0,musicNode);

    m_sfxRect = new sf::RectangleShape();
    SetSfxRect();
    DrawableNode* sfxNode = new DrawableNode(m_sfxRect);
    sfxNode->moveNode(m_menuWidth - m_soundOptionWidth - 5.0f, 2.0f);
    m_soundOptions->AddNodeToOption(1,sfxNode);
}

void SceneManagerOptions::SetKey(Configuration::Keys key)
{
    m_updateKey = key;
    m_configKey = true;
    Configuration::GetInstance()->ResetLastKey();
    m_keybindings->AddValueToOption((int)m_updateKey, "_");
}

void SceneManagerOptions::ChangeMusic()
{
    m_changeMusic = true;
}

void SceneManagerOptions::ChangeSfx()
{
    m_changeSfx = true;
}

void SceneManagerOptions::SetMusicRect()
{
    m_musicRect->setSize(sf::Vector2f((MusicController::GetInstance()->GetVolume() / 100.0f) * m_soundOptionWidth, 20));
}

void SceneManagerOptions::SetSfxRect()
{
    m_sfxRect->setSize(sf::Vector2f((SoundController::GetInstance()->GetVolume() / 100.0f) * m_soundOptionWidth, 20));
}
