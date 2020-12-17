#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Constans.h"
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Shape {
	array<Vector2Byte, 4> verticies;
	Vector2Byte position;
	int currentOrientation = 0;

	//vector<const array<Vector2Byte, 4>*> pointer;

	vector<array<Vector2Byte, 4>> orientations;
	__int8 color = 0;
};

Shape randomShape() {
	Shape ret;
	short random = floor(rand() % 7);

	ret.position.x = 0;
	ret.position.y = -1;

	switch (random)
	{
	case 0:
		ret.verticies = SHAPE_I_0;
		ret.orientations = { SHAPE_I_0, SHAPE_I_1 };
		ret.color = 0;
		break;
	case 1:
		ret.verticies = SHAPE_O;
		ret.orientations = { SHAPE_O };
		ret.color = 1;
		break;
	case 2:
		ret.verticies = SHAPE_T_0;
		ret.orientations = { SHAPE_T_0, SHAPE_T_1, SHAPE_T_2, SHAPE_T_3 };
		ret.color = 2;
		break;
	case 3:
		ret.verticies = SHAPE_S_0;
		ret.orientations = { SHAPE_S_0, SHAPE_S_1 };
		ret.color = 3;
		ret.position.y = -2;
		break;
	case 4:
		ret.verticies = SHAPE_Z_0;
		ret.orientations = { SHAPE_Z_0, SHAPE_Z_1 };
		ret.color = 4;
		ret.position.y = -2;
		break;
	case 5:
		ret.verticies = SHAPE_J_0;
		ret.orientations = { SHAPE_J_0, SHAPE_J_1, SHAPE_J_2, SHAPE_J_3 };
		ret.color = 5;
		break;
	case 6:
		ret.verticies = SHAPE_L_0;
		ret.orientations = { SHAPE_L_0, SHAPE_L_1, SHAPE_L_2, SHAPE_L_3 };
		ret.color = 6;
		break;
	}
	return ret;
}

bool canMoveHorizontally(const Shape& shape, const __int8* grid, const __int8& direction) {
	for (Vector2Byte vertex : shape.verticies) // access by reference to avoid copying
	{
		int posX = vertex.x + shape.position.x + direction;
		int posY = vertex.y + shape.position.y;
		int posId = posX + posY * 10;

		if (posX < 0 || posX > 9)
			return false;
		else if (*(grid + posId) > -1)
			return false;
	}
	return true;
}

bool isTouchingGround(const Shape& shape,const __int8* grid) {
	for (Vector2Byte vertex : shape.verticies) // access by reference to avoid copying
	{
		if (vertex.y + shape.position.y + 1 >= 20)
			return true;
		int index = (vertex.y + shape.position.y + 1) * 10 + vertex.x + shape.position.x;
		if (*(grid + index) > -1)
			return true;
	}
	return false;
}

bool canBeSpawned(const Shape& shape,const __int8* grid) {
	for (Vector2Byte vertex : shape.verticies) // access by reference to avoid copying
	{
		int index = (vertex.y + shape.position.y + 1) * 10 + vertex.x + shape.position.x;
		if (*(grid + index) > -1)
			return false;
	}
	return true;
}

bool isRotationPossible(const Shape& shape, __int8* grid,const __int8& orientation) {
	for (Vector2Byte vertex : shape.orientations[orientation]) // access by reference to avoid copying
	{
		int posX = vertex.x + shape.position.x;
		int posY = vertex.y + shape.position.y;
		int posId = posX + posY * 10;

		if (posX < 0 || posX > 9)
			return false;
		else if (*(grid + posId) > -1)
			return false;
	}
	return true;
}

void placeShape(const Shape& shape, __int8* grid) {
	for (Vector2Byte vertex : shape.verticies)
	{
		int index = (vertex.y + shape.position.y) * 10 + vertex.x + shape.position.x;
		*(grid + index) = shape.color;
	}
}

void checkLineErasing(const Shape& shape, __int8* grid,unsigned int *score) {
	short endY = 0;
	short startY = 20;

	//determin min and max Y
	for (auto& vertex : shape.verticies)
	{
		if (vertex.y + shape.position.y < startY)
			startY = vertex.y + shape.position.y;
		if (vertex.y + shape.position.y > endY)
			endY = vertex.y + shape.position.y;
	}
	//check and remove lines
	short linesToMoveStart = 20;
	short lineSkip = 0;
	for (int j = startY; j <= endY; j++) {
		short sum = 0;
		for (short i = j * 10; i < j * 10 + 10; i++) {
			if (*(grid + i) > -1)
				sum++;
		}
		if (sum >= 10) {
			if (j - 1 < linesToMoveStart) linesToMoveStart = j - 1;
			//remove that line
			for (int i = j * 10; i < j * 10 + 10; i++) {
				*(grid + i) = -1;
			}
			lineSkip++;
		}
	}
	if (lineSkip == 0) return;

	for (int y = linesToMoveStart; y >= 0; y--) {
		for (int x = 0; x < 10; x++) {
			int id = x + y * 10;
			*(grid + id + lineSkip*10) = *(grid + id);
		}
	}
	
	*score += lineSkip * 100;
}

int shadeY(const Shape& shape,const __int8* grid) {
	for (int y = shape.position.y; y < 19; y++) {
		for (Vector2Byte vertex : shape.verticies)
		{
			int index = (y + vertex.y+1)* 10 + vertex.x + shape.position.x;
			if (index >= 200)
				return y;
			else if (*(grid + index) > -1)
				return y;
		}
	}
	return 19;
}

void overwriteHighscore(unsigned int highscore){
	ofstream dataFile;
	dataFile.open("res/data.txt");
	dataFile << highscore;
	dataFile.close();
}

int main(){
	srand(time(NULL));
	int frame = 0;

	unsigned int score = 0;
	unsigned int highscore = 0;
	bool isPlaying = true;

	string line;
	ifstream dataFile("res/data.txt");
	if (dataFile.is_open())
	{
		getline(dataFile, line);
		stringstream lineSS(line);
		lineSS >> highscore;
		dataFile.close();
	}

	__int8 gridArray[200];
	for(int i = 0; i < 200; i++) {
		gridArray[i] = -1;
	}

	Shape currentShape, nextShape;
	currentShape = randomShape();
	nextShape = randomShape();
	currentShape.position.y++;

	sf::Texture texture;
	texture.loadFromFile("res/block.png");
	sf::Sprite blockSprite;
	blockSprite.setScale(2, 2);
	blockSprite.setTexture(texture);

	sf::Texture texture1;
	texture1.loadFromFile("res/block_shadow.png");
	sf::Sprite blockShadowSprite;
	blockShadowSprite.setScale(2, 2);
	blockShadowSprite.setTexture(texture1);

	sf::Text text;
	sf::Font font;

	font.loadFromFile("res/font.ttf");

	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);

	sf::RenderWindow window(sf::VideoMode(720, 880), "Tetris!", sf::Style::Default);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				if (score > highscore)
					overwriteHighscore(score);
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && isPlaying)
			{

				switch (event.key.code)
				{
				case sf::Keyboard::Up:
				{
					__int8 desiredOrientation = currentShape.currentOrientation + 1;
					if (desiredOrientation >= currentShape.orientations.size())
						desiredOrientation = 0;

					if (isRotationPossible(currentShape, gridArray, desiredOrientation)) {
						currentShape.currentOrientation = desiredOrientation;
						currentShape.verticies = currentShape.orientations[currentShape.currentOrientation];
						//currentShape.verticies = *currentShape.pointer[currentShape.currentOrientation];
					}
				}	
				break;
				case sf::Keyboard::Right:
					if (canMoveHorizontally(currentShape, gridArray, 1))
						currentShape.position.x++;
					break;
				case sf::Keyboard::Left:
					if (canMoveHorizontally(currentShape, gridArray, -1))
						currentShape.position.x--;
					break;
				default:
					break;
				}
			}
		}
		if (!isPlaying)
			continue;
		uint8_t frameCount = 60;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			frameCount = 2;
			score++;
		}
		frame++;
		if (frame >= frameCount) {
			frame = 0;
			if (isTouchingGround(currentShape, gridArray)) {
				placeShape(currentShape, gridArray);
				checkLineErasing(currentShape, gridArray, &score);
				if (!canBeSpawned(nextShape, gridArray)) {
					cout << "You lost";
					isPlaying = false;
					continue;
				}
				currentShape = nextShape;
				nextShape = randomShape();
			}
			currentShape.position.y++;
		}

		window.clear();

		//draw borders
		blockSprite.setColor(sf::Color(200, 200, 200));
		//left and right
		for (int x = 0; x < 12; x++) {
			blockSprite.setPosition(x * 40, 0);
			window.draw(blockSprite);

			blockSprite.setPosition(x * 40, 840);
			window.draw(blockSprite);
		}
		//top and bottom
		for (int y = 1; y < 21; y++) {
			blockSprite.setPosition(0, y*40);
			window.draw(blockSprite);

			blockSprite.setPosition(440, y*40);
			window.draw(blockSprite);
		}

		//draw grid
		for (int i = 0; i < 200; i++) {
			if (gridArray[i] > -1) {
				int x = i % 10;
				int y = (i - x) / 10;
				blockSprite.setColor(COLORS[gridArray[i]]);
				blockSprite.setPosition(x * 40+40, y * 40+40);
				window.draw(blockSprite);
			}
		}

		//draw shade
		for (Vector2Byte vertex : currentShape.verticies)
		{
			blockShadowSprite.setPosition((vertex.x + currentShape.position.x) * 40 + 40, (vertex.y + shadeY(currentShape, gridArray)) * 40 + 40);
			blockShadowSprite.setColor(COLORS[currentShape.color]);
			window.draw(blockShadowSprite);
		}

		//draw currentShape
		for (Vector2Byte vertex : currentShape.verticies)
		{
			blockSprite.setPosition((vertex.x + currentShape.position.x) * 40 + 40, (vertex.y + currentShape.position.y) * 40 + 40);
			blockSprite.setColor(COLORS[currentShape.color]);
			window.draw(blockSprite);
		}

		//draw nextShape
		for (Vector2Byte vertex : nextShape.verticies)
		{
			if(nextShape.color == 3 || nextShape.color == 4)
				blockSprite.setPosition(vertex.x * 40 + 520, vertex.y * 40);
			else
				blockSprite.setPosition(vertex.x * 40 + 520, vertex.y * 40 + 40);

			blockSprite.setColor(COLORS[nextShape.color]);
			window.draw(blockSprite);
		}

		text.setString("NEXT");
		text.setPosition(520, 0);
		window.draw(text);

		text.setString("SCORE");
		text.setPosition(520, 160);
		window.draw(text);

		text.setString(to_string(score));
		text.setPosition(520, 200);
		window.draw(text);

		text.setString("HIGHSCORE");
		text.setPosition(520, 240);
		window.draw(text);

		text.setString(to_string(max(highscore,score)));
		text.setPosition(520, 280);
		window.draw(text);

		window.display();
	}

	return 0;
}