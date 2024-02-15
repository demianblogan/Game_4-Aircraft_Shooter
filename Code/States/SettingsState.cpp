#include "SettingsState.h"
#include "../Utilities/Utilities.h"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context)
{
    backgroundSprite.setTexture(context.textureHolder->Get(Texture::ID::TitleScreen));

    // Build key binding buttons and labels:
    AddButtonAndLabel(Player::Action::MoveLeft, 200, "Move Left", context);
    AddButtonAndLabel(Player::Action::MoveRight, 250, "Move Right", context);
    AddButtonAndLabel(Player::Action::MoveUp, 300, "Move Up", context);
    AddButtonAndLabel(Player::Action::MoveDown, 350, "Move Down", context);
    AddButtonAndLabel(Player::Action::Fire, 400, "Fire", context);
    AddButtonAndLabel(Player::Action::LaunchMissile, 450, "Launch Missile", context);

    UpdateLabels();

    auto backButtonPtr = std::make_shared<GUI::Button>(context);
    backButtonPtr->setPosition(10, 600);
    backButtonPtr->SetText("Back");
    backButtonPtr->SetCallback(std::bind(&SettingsState::RequestStackPop, this));

    GUI_container.AddComponent(backButtonPtr);
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
    bool isNewKeyBounded = false;

    // Iterate through all key binding buttons to see if they are being pressed,
    // waiting for the user to enter a key:
    for (int action = 0; action < int(Player::Action::Count); action++)
    {
        if (bindingButtons[action]->IsActive())
        {
            isNewKeyBounded = true;
            if (event.type == sf::Event::KeyReleased)
            {
                GetContext().player->AssignKey(Player::Action(action), event.key.code);
                bindingButtons[action]->Deactivate();
            }
            break;
        }
    }

    if (isNewKeyBounded)
        UpdateLabels();
    else
        GUI_container.HandleEvent(event);

    return false;
}

bool SettingsState::Update(sf::Time deltaTime)
{
    return true;
}

void SettingsState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;

    window.draw(backgroundSprite);
    window.draw(GUI_container);
}

void SettingsState::UpdateLabels()
{
    Player& player = *GetContext().player;

    for (int action = 0; action < int(Player::Action::Count); action++)
    {
        sf::Keyboard::Key key = player.GetAssignedKey(Player::Action(action));
        bindingLabels[action]->SetText(ConvertKeyToString(key));
    }
}

void SettingsState::AddButtonAndLabel(Player::Action action, float y, const std::string& text, Context context)
{
    bindingButtons[int(action)] = std::make_shared<GUI::Button>(context);
    bindingButtons[int(action)]->setPosition(400, y);
    bindingButtons[int(action)]->SetText(text);
    bindingButtons[int(action)]->SetToggle(true);

    bindingLabels[int(action)] = std::make_shared<GUI::Label>("", *context.fontHolder);
    bindingLabels[int(action)]->setPosition(620, y + 15.0f);

    GUI_container.AddComponent(bindingButtons[int(action)]);
    GUI_container.AddComponent(bindingLabels[int(action)]);
}