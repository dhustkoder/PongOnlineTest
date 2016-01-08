#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class GameWindow final
{

	static constexpr unsigned defaultWidth = 800;
	static constexpr unsigned defaultHeight = 420;
public:
	static std::unique_ptr<GameWindow> 
		makeUniqueWindow(sf::VideoMode &&mode = {defaultWidth, defaultHeight, 32},
				 const char* windowName = "Game-Window") noexcept;
	static std::unique_ptr<GameWindow> 
		makeUniqueWindow(const char* windowName) noexcept;

	~GameWindow();
	void updateWindowState() noexcept;
	void setSize(const unsigned Width, const unsigned Height) noexcept;
	bool isOpen() const noexcept;

	template<typename ...Ts>
	void drawAndDisplay(Ts&& ...args) noexcept;

public:
	static const unsigned &Width, &Height;

private:
	GameWindow(sf::VideoMode&&, const char*) noexcept;


	sf::RenderWindow m_renderWindow;
	sf::Event m_event;
	static int sm_instances;
	static unsigned sm_width, sm_height;

	// deleted functions
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

};


inline GameWindow::~GameWindow() {
	--sm_instances;
}

inline bool GameWindow::isOpen() const noexcept {
	return m_renderWindow.isOpen();
}

// sends all args to sf::RenderWindow draw fuction. 
// (the arguments need to be implicit conversible to sf::Drawable)
template<typename ...Ts>
void GameWindow::drawAndDisplay(Ts &&...args) noexcept
{
	(void)std::initializer_list<int>
	{
		(m_renderWindow.draw(std::forward<Ts>(args)), 0)...
	};

	m_renderWindow.display();
}




#endif // GAMEWINDOW_H
