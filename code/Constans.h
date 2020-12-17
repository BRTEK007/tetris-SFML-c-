#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>

using namespace std;

struct Vector2Byte {
	__int8 x, y;
	Vector2Byte() {
		x = 0;
		y = 0;
	}
	Vector2Byte(__int8 _x, __int8 _y) {
		x = _x;
		y = _y;
	}
};

const array<Vector2Byte, 4> SHAPE_I_1 = { Vector2Byte(0,0), Vector2Byte(0,1),
											 Vector2Byte(0,2),  Vector2Byte(0,3) };
const array<Vector2Byte, 4> SHAPE_I_0 = { Vector2Byte(1,0), Vector2Byte(2,0),
											 Vector2Byte(3,0),  Vector2Byte(0,0) };
/*------------------------------------------------------------------------------------------*/
const array<Vector2Byte, 4> SHAPE_O = { Vector2Byte(0,0), Vector2Byte(1,0),
										 Vector2Byte(0,1),  Vector2Byte(1,1) };
/*------------------------------------------------------------------------------------------*/
const array<Vector2Byte, 4> SHAPE_T_0 = { Vector2Byte(1,0), Vector2Byte(0,1),
											 Vector2Byte(1,1),  Vector2Byte(2,1) };
const array<Vector2Byte, 4> SHAPE_T_1 = { Vector2Byte(1,0), Vector2Byte(1,1),
											 Vector2Byte(1,2),  Vector2Byte(2,1) };
const array<Vector2Byte, 4> SHAPE_T_2 = { Vector2Byte(0,1), Vector2Byte(1,1),
											 Vector2Byte(1,2),  Vector2Byte(2,1) };
const array<Vector2Byte, 4> SHAPE_T_3 = { Vector2Byte(1,0), Vector2Byte(1,1),
											 Vector2Byte(0,1),  Vector2Byte(1,2) };
/*------------------------------------------------------------------------------------------*/
const array<Vector2Byte, 4> SHAPE_S_1 = { Vector2Byte(1,0), Vector2Byte(1,1),
											 Vector2Byte(0,1),  Vector2Byte(0,2) };
const array<Vector2Byte, 4> SHAPE_S_0 = { Vector2Byte(0,1), Vector2Byte(1,1),
											 Vector2Byte(1,2),  Vector2Byte(2,2) };
/*------------------------------------------------------------------------------------------*/
const array<Vector2Byte, 4> SHAPE_Z_1 = { Vector2Byte(1,0), Vector2Byte(1,1),
											 Vector2Byte(2,1),  Vector2Byte(2,2) };
const array<Vector2Byte, 4> SHAPE_Z_0 = { Vector2Byte(0,2), Vector2Byte(1,2),
											 Vector2Byte(1,1),  Vector2Byte(2,1) };
/*------------------------------------------------------------------------------------------*/
const array<Vector2Byte, 4> SHAPE_J_3 = { Vector2Byte(1,0), Vector2Byte(1,1),
											 Vector2Byte(1, 2),  Vector2Byte(0,2) };
const array<Vector2Byte, 4> SHAPE_J_0 = { Vector2Byte(0,0), Vector2Byte(0,1),
											 Vector2Byte(1,1),  Vector2Byte(2,1) };
const array<Vector2Byte, 4> SHAPE_J_1 = { Vector2Byte(1,0), Vector2Byte(2,0),
											 Vector2Byte(1,1),  Vector2Byte(1,2) };
const array<Vector2Byte, 4> SHAPE_J_2 = { Vector2Byte(0,1), Vector2Byte(1,1),
											 Vector2Byte(2,1),  Vector2Byte(2,2) };
/*------------------------------------------------------------------------------------------*/
const array<Vector2Byte, 4> SHAPE_L_3 = { Vector2Byte(1,0), Vector2Byte(1,1),
											 Vector2Byte(1, 2),  Vector2Byte(2,2) };
const array<Vector2Byte, 4> SHAPE_L_0 = { Vector2Byte(0,1), Vector2Byte(1,1),
											 Vector2Byte(2,1),  Vector2Byte(2,0) };
const array<Vector2Byte, 4> SHAPE_L_1 = { Vector2Byte(0,0), Vector2Byte(1,0),
											 Vector2Byte(1,1),  Vector2Byte(1,2) };
const array<Vector2Byte, 4> SHAPE_L_2 = { Vector2Byte(0,1), Vector2Byte(0,2),
											 Vector2Byte(1,1),  Vector2Byte(2,1) };

const sf::Color COLORS[] = { sf::Color::Cyan, sf::Color::Yellow,sf::Color(205,0,155),
				sf::Color::Green, sf::Color::Red,sf::Color::Blue, sf::Color(255,125,0) };
