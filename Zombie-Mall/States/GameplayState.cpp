
#include "GameplayState.h"

#include "../Game.h"
#include "../Input/InputManager.h"
#include "PauseMenuState.h"
#include "../Entity/Player.h"
#include "../Entity/Person.h"
#include "../Entity/Guard.h"

GameplayState::GameplayState(Game& game) :
    mGame(game),
    mLevel(game),
    mPlayer(nullptr),
    mScoreText()
{}

GameplayState::~GameplayState() {}

void GameplayState::Enter()
{
    mLevel.LoadLevel("Resources/Data/Level.json");

    CreatePlayer();
    CreatePerson();

    mSpawns.emplace_back(mLevel.GetPersonSpawnTime(), std::bind(&GameplayState::CreatePerson, this));
    mSpawns.emplace_back(mLevel.GetGuardSpawnTime(), std::bind(&GameplayState::CreateGuard, this));

    mGame.ResetScore();

    auto font = mGame.GetFontManager().LoadFont("Resources/Fonts/FreeSans.ttf");
    if (font)
    {
        mScoreText = sf::Text("Score: 0", *font);
        mScoreText.setPosition(2.0f, 2.0f);
    }
}

void GameplayState::Exit()
{
    mSpawns.clear();
    mGame.GetEntityManager().ClearEntities();
    mPlayer = nullptr;

    mGame.GetWindow().setView(mGame.GetWindow().getDefaultView());
}

bool GameplayState::Input()
{
    if (InputManager::Global.IsKeyPressed(sf::Keyboard::Escape))
        mGame.GetStateManager().PushState(std::make_unique<PauseMenuState>(mGame));

    return true;
}

void GameplayState::Update()
{
    if (mGame.GetStateManager().GetCurrentState() != this)
    {
        for (auto& spawn : mSpawns)
            spawn.ResetTimer();

        return;
    }

    mLevel.HandleCollisions();

    for (auto& spawn : mSpawns)
        spawn.Update();

    mGame.GetEntityManager().Update();

    char buffer[16] = {};
    sprintf(buffer, "Score: %i", mGame.GetScore());
    mScoreText.setString(buffer);
}

void GameplayState::Render(sf::RenderTarget* const renderTarget)
{
    if (mGame.GetStateManager().GetCurrentState() != this)
        return;

    const sf::Vector2f playerPos(mPlayer->GetPosition());
    const sf::Vector2f windowSize(mGame.GetWindow().getSize());

    const sf::Vector2f center(
        std::clamp(playerPos.x, windowSize.x / 2.0f, mLevel.GetWidth() - (windowSize.x / 2.0f)),
        std::clamp(playerPos.y, windowSize.y / 2.0f, mLevel.GetHeight() - (windowSize.y / 2.0f)));

    const sf::View view(center, windowSize);
    mGame.GetWindow().setView(view);

    mLevel.Render(renderTarget);

    mGame.GetEntityManager().Render(renderTarget);

    mScoreText.setPosition(center - (windowSize / 2.0f));
    renderTarget->draw(mScoreText);
}

void GameplayState::CreatePlayer()
{
    std::unique_ptr<Player> player = std::make_unique<Player>(mGame);
    player->Load("Resources/Data/Player.json");

    mPlayer = player.get();
    mGame.GetEntityManager().AddEntity(std::move(player));
}

void GameplayState::CreatePerson()
{
    std::unique_ptr<Person> person = std::make_unique<Person>(mGame);
    person->Load("Resources/Data/Person.json");

    if (mPlayer->GetPosition().x > (mLevel.GetWidth() / 2.0f))
        person->SetPosition(sf::Vector2f(300.0f, 100.0f));
    else
        person->SetPosition(sf::Vector2f(1300.0f, 100.0f));

    mGame.GetEntityManager().AddEntity(std::move(person));
}

void GameplayState::CreateGuard()
{
    std::unique_ptr<Guard> guard = std::make_unique<Guard>(mGame, mPlayer);
    guard->Load("Resources/Data/Guard.json");

    if (mPlayer->GetPosition().x > (mLevel.GetWidth() / 2.0f))
        guard->SetPosition(sf::Vector2f(300.0f, 100.0f));
    else
        guard->SetPosition(sf::Vector2f(1300.0f, 100.0f));

    mGame.GetEntityManager().AddEntity(std::move(guard));
}