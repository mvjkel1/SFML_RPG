#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("fonts/Dosis-Light.ttf");
}


void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(1.8f, this->vm);
	float height = gui::p2pY(3.3f, this->vm);
	float x = gui::p2pX(1.25f, this->vm);
	float y = gui::p2pY(3.3f, this->vm);


	this->levelBarText.setFont(this->font);


	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 250, 160));
	this->levelBarBack.setPosition(x, y);


	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 110));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.7f, this->vm),
		this->levelBarBack.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}

void PlayerGUI::initEXPBar()
{
	float width = gui::p2pX(7.8f, this->vm);
	float height = gui::p2pY(3.3f, this->vm);
	float x = gui::p2pX(1.25, this->vm);
	float y = gui::p2pY(6.6f, this->vm);

	this->expBarMaxWidth = width;

	this->expBarText.setFont(this->font);


	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(20, 20, 20, 160));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color(20, 220, 20, 160));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 130));
	this->expBarText.setPosition(
		this->expBarInner.getPosition().x + gui::p2pX(1.5f, this->vm),
		this->expBarInner.getPosition().y + gui::p2pY(0.16f, this->vm)
	);
}

void PlayerGUI::initHPBar()
{
	float width = gui::p2pX(7.8f, this->vm);
	float height = gui::p2pY(3.3f, this->vm);
	float x = gui::p2pX(1.25f, this->vm);
	float y = gui::p2pY(10.5f, this->vm);

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 160));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 160));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 130));
	this->hpBarText.setPosition(
		this->hpBarInner.getPosition().x + gui::p2pX(1.5f, this->vm),
		this->hpBarInner.getPosition().y - gui::p2pY(0.16f, this->vm)
	);
}

PlayerGUI::PlayerGUI(Player *player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;
	this->initFont();
	this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
}

PlayerGUI::~PlayerGUI()
{

}

//Functions
void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);


	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);


	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float & dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}


void PlayerGUI::renderLevelBar(sf::RenderTarget & target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget & target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGUI::renderHPBar(sf::RenderTarget & target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget & target)
{
	this->renderLevelBar(target);
	this->renderEXPBar(target);
	this->renderHPBar(target);
}

