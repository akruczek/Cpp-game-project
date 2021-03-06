#include "library.h"
bool antialiasing = true;
bool fullscreenMode = false;

using namespace std;
using namespace sf;

RenderWindow window;
Event event;
Color darkRed(220, 220, 50, 100);
string incode = "";
int mouseX, mouseY;
Clock mainClock;
Time mainTime;
int timeSeconds, timeMilliseconds;
int timer = 0;
Uint32 unicode = event.text.unicode;

void MAIN_MENU(), MAIN_MENU_SETTINGS(), MAIN_MENU_LOAD_GAME(), MAIN_MENU_NEW_GAME();
void CHECKBOX(int posX, int posY, bool argumanet[], wstring checkboxName, int boxesNumber, wstring box1, wstring box2, wstring box3, wstring box4, wstring box5, wstring box6);
string INPUT_TEXT(int posX, int posY, wstring inputTextName, string outputString);
void START_GAME();
void CHEATS();
void YES_NO_BOX(wstring boxContent, wstring boxExtraContent);
void RELOAD_LANGUAGE_STRINGS();
void NEXT_TURN();
void CHECK_STATUS_1();
void FOOD_MORE();
void FOOD_MORE_MAIN(int i, int j, bool YesOrNo);
void MATERIALS_MORE();
void MATERIALS_MORE_MAIN(int i, int j, bool YesOrNo);
bool yesNoBoxActive = false;
bool difficulty[3] = { 1, 0, 0 };


bool textareaActive = false;
String inputText("");
random_device rd;

mt19937 rng(rd());
uniform_int_distribution<int> uni(1, 1000);
auto random_integer = uni(rng);
int tAddon = 0;

#include "myFunctions.h"
#include "fonts.h"
#include "sounds.h"
#include "textures.h"
#include "saves.h"
#include "map.h"
#include "player.h"
#include "text.h"

Color colorSp1_4 = sp[1][4].getColor();

int main()	{
	window.create(VideoMode(1280, 720, 32), "Main Menu");		//TWORZENIE OKNA (1280x720)
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);	//Limit 30FPS
	LOAD_FONTS();
	LOAD_SOUNDS();
	MAIN_MENU();
}

void MAIN_MENU() {
	incode = "mainMenu";
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) { CHEATS(); }
			if (event.type == Event::MouseButtonPressed) {
				for (int i = 0; i < 4; i++) {
					if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i)) {
						switch (i) {
						case 0:	//NOWA GRA
							MAIN_MENU_NEW_GAME();
							break;
						case 1:	//WCZYTAJ GR�
							MAIN_MENU_LOAD_GAME();
							break;
						case 2:	//USTWIENIA
							window.clear();
							MAIN_MENU_SETTINGS();
							break;
						case 3:	//WYJ�CIE
							window.close();
							break;
						}
					}
				}
			}
		}
		window.clear();
		
		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 4; i++) {	//TEXT
			window.draw(txt[0][i]);
			
			if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i))
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		window.display();
	}
}

void MAIN_MENU_SETTINGS() {
	incode = "mainMenuSettings";
	window.setTitle("Main Menu - Settings");
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				for (int i = 0; i < 4; i++) {
					if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i)) {
						switch (i) {
						case 0:	//J�ZYK
							if (lang == "english")
								lang = "polish";
							else
								lang = "english";
							SET_TEXT(incode);
							break;
						case 1:	//FULLSCREEN
							if (fullscreenMode == false) {
								window.create(VideoMode(1280, 720, 32), "life-simulator", Style::Fullscreen);
								fullscreenMode = true;
							}
							else {
								window.create(VideoMode(1280, 720, 32), "life-simulator");
								fullscreenMode = true;
							}
							SET_TEXT(incode);
							break;
						case 2:	//ANTIALIASING
							if (antialiasing == false) {
								SET_ANTIALIASING();
								antialiasing = true;
							}
							else {
								SET_ANTIALIASING();
								antialiasing = false;
							}
							SET_TEXT(incode);
							break;
						case 3:	//POWR�T
							window.clear();
							MAIN_MENU();
							break;
						}
					}
				}
			}
		}
		window.clear();

		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 4; i++) {	//TEXT
			window.draw(txt[0][i]);

			if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i))
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		for (int i = 4; i < 7; i++) {	//TEXT
			window.draw(txt[0][i]);
		}

		window.display();
	}
}

void MAIN_MENU_LOAD_GAME() {
	incode = "mainMenuLoadGame";
	window.setTitle("Main Menu - Load Game");
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				for (int i = 0; i < 4; i++) {
					if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i)) {
						switch (i) {
						case 0:	//SAVE 1

							break;
						case 1:	//SAVE 2
							
							break;
						case 2:	//SAVE 3
							
							break;
						case 3:	//POWR�T
							MAIN_MENU();
							break;
						}
					}
				}
			}
		}
		window.clear();

		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 4; i++) {	//TEXT
			window.draw(txt[0][i]);

			if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i))
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		for (int i = 4; i < 7; i++) {	//TEXT
			window.draw(txt[0][i]);
		}

		window.display();
	}
}

void MAIN_MENU_NEW_GAME() {
	mainClock.restart();
	incode = "mainMenuNewGame";
	window.setTitle("Main Menu - New Game");
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	textareaActive = false;
	txt[5][8].setString("");
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				cout << endl << difficulty[0] << endl;
				cout << mapSize[0] << endl;
				if (mouseX >= txt[0][0].getPosition().x && mouseX <= txt[0][0].getPosition().x + txt[0][0].getLocalBounds().width && mouseY >= txt[0][0].getPosition().y && mouseY <= txt[0][0].getPosition().y + txt[0][0].getLocalBounds().height) {
					window.clear();
					MAIN_MENU();
					break;
				}
				if (mouseX >= txt[0][1].getPosition().x && mouseX <= txt[0][1].getPosition().x + txt[0][1].getLocalBounds().width && mouseY >= txt[0][1].getPosition().y && mouseY <= txt[0][1].getPosition().y + txt[0][1].getLocalBounds().height) {
					window.clear();
					MAP_GENERATOR();	//[!] GENEROWANIE MAPY [!]
					START_GAME();
					break;
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				textareaActive = false;
		}
		window.clear();

		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 2; i++) {	//TEXT
			window.draw(txt[0][i]);

			if (mouseX >= txt[0][i].getPosition().x && mouseX <= txt[0][i].getPosition().x + txt[0][i].getLocalBounds().width && mouseY >= txt[0][i].getPosition().y && mouseY <= txt[0][i].getPosition().y + txt[0][i].getLocalBounds().height)
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		
		if (lang == "english")	CHECKBOX(480, 120, difficulty, L"Difficulty", 3, L"Easy", L"Medium", L"Hard", L"", L"", L"");
		if (lang == "polish")	CHECKBOX(480, 120, difficulty, L"Trudno��", 3, L"�atwy", L"�redni", L"Trudny", L"", L"", L"");

		if (lang == "english")	CHECKBOX(640, 120, mapSize, L"Map Size", 3, L"Small", L"Medium", L"Large", L"", L"", L"");
		if (lang == "polish")	CHECKBOX(640, 120, mapSize, L"Rozmiar", 3, L"Ma�y", L"�redni", L"Du�y", L"", L"", L"");

		if (lang == "english")	mapName = INPUT_TEXT(470, 300, L"World Name", mapName);
		if (lang == "polish")	mapName = INPUT_TEXT(470, 300, L"Nazwa �wiata", mapName);

		window.display();
	}
}

void START_GAME() {
	incode = "startGame";
	window.setTitle("Start Game");
	yesNoBoxActive = false;
	playerWoodValue = 100;
	playerStoneValue = 75;
	playerIronValue = 50;
	turn = 1;
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	int fieldActiveByMouseX = 0;
	int fieldActiveByMouseY = 0;
	bool placeBuilding = false;
	bool pickingMaterialsWood = false;
	bool pickingMaterialsStone = false;
	bool pickingMaterialsIron = false;
	bool pickingMaterialsFood = false;
	bool removingBuildings = false;
	bool upgradingBuildings = false;
	bool moreFood = false;
	bool moreMaterials = false;
	int placeBuildingId = 0;
	string placeBuildingName = "";
	CHECK_STATUS_1();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				if (mouseX > 700 || mouseX < 50 || mouseY < 50 || mouseY > 700) {
					placeBuilding = false;			pickingMaterialsWood = false;	pickingMaterialsStone = false; pickingMaterialsIron = false;
					pickingMaterialsFood = false;	removingBuildings = false;		upgradingBuildings = false;
				}
				if (!moreFood && !moreMaterials) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 3; j++) {
							if (mouseX >= 720 + (55 * i) && mouseX <= 770 + (55 * i) && mouseY >= 660 - (55 * j) && mouseY <= 710 - (55 * j)) {
								switch (j) {
								case 0:	//PIERWSZY WIERSZ OD DO�U
									switch (i) {
									case 0: NEXT_TURN(); break;
									case 1: break;
									case 2: removingBuildings = true; break;
									case 3: upgradingBuildings = true; break;
									case 4: pickingMaterialsFood = true; break;
									case 5: pickingMaterialsWood = true; break;
									case 6: pickingMaterialsStone = true; break;
									case 7: pickingMaterialsIron = true; break;
									case 8: CHEATS(); break;	//INFO
									case 9: yesNoBoxActive = true; break;
									}
									break;
								case 1:	//DRUGI WIERSZ OD DO�U
									switch (i) {
									case 0: placeBuilding = true; placeBuildingName = "simpleHouse"; placeBuildingId = 2; break;
									case 1: placeBuilding = true; placeBuildingName = "woodenHouse"; placeBuildingId = 3; break;
									case 2: placeBuilding = true; placeBuildingName = "stoneHouse"; placeBuildingId = 4; break;
									case 3: placeBuilding = true; placeBuildingName = "lumberjack"; placeBuildingId = 5; break;
									case 4: placeBuilding = true; placeBuildingName = "quarry"; placeBuildingId = 6; break;
									case 5: placeBuilding = true; placeBuildingName = "mine"; placeBuildingId = 7; break;
									case 6: break;
									case 7: break;
									case 8: placeBuilding = true; placeBuildingName = "storage"; placeBuildingId = 1; break;
									case 9: /*TOWN HALL*/break;
									}
									break;
								case 2:	//TRZECI WIERSZ OD DO�U
									switch (i) {
									case 0: placeBuilding = true; placeBuildingName = "farm"; placeBuildingId = 8; break;
									case 1: placeBuilding = true; placeBuildingName = "fish"; placeBuildingId = 9; break;
									case 2: placeBuilding = true; placeBuildingName = "hunting"; placeBuildingId = 10; break;
									case 3: placeBuilding = true; placeBuildingName = "gather"; placeBuildingId = 11; break;
									case 4: placeBuilding = true; placeBuildingName = "windmill"; placeBuildingId = 12; break;
									case 5: placeBuilding = true; placeBuildingName = "carpenter"; placeBuildingId = 13; break;
									case 6: placeBuilding = true; placeBuildingName = "foundry"; placeBuildingId = 14; break;
									case 7: break;
									case 8: break;
									case 9: break;
									}
									break;
								}
							}
						}
					}
				}

				//YES_NO BOX
				if (yesNoBoxActive) {
					if (mouseX >= window.getSize().x / 2 - 200 + 60 && mouseX <= window.getSize().x / 2 - 200 + 150 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						window.clear();
						MAIN_MENU();
					}
					if (mouseX >= window.getSize().x / 2 - 200 + 245 && mouseX <= window.getSize().x / 2 - 200 + 337 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						yesNoBoxActive = false;
					}
				}

				//PLACE BUILDING
				if (placeBuilding) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								ADD_BUILDING(i, j, placeBuildingId, placeBuildingName);
								placeBuilding = false;
							}
						}
					}
				}

				//PICKING MATERIALS \/
				if (pickingMaterialsWood || pickingMaterialsStone || pickingMaterialsIron || pickingMaterialsFood) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								if (pickingMaterialsWood && mapFieldsWoodValue[i][j]>=1) {
									if (mapFieldsWoodValue[i][j] > 1) {
										if (mapFieldsNames[i][j] != "water") {
											playerWoodValue++;
											mapFieldsWoodValue[i][j]--;
										}
										else {
											playerWoodValue += 0.1;
											mapFieldsWoodValue[i][j] -= 0.1;
										}
										NEXT_TURN();
									}
								}
								else if (pickingMaterialsStone && mapFieldsStoneValue[i][j] >= 1) {
									if (mapFieldsStoneValue[i][j] > 1) {
										if (mapFieldsNames[i][j] != "water") {
											playerStoneValue++;
											mapFieldsStoneValue[i][j]--;
										}
										else {
											playerStoneValue += 0.1;
											mapFieldsStoneValue[i][j] -= 0.1;
										}
										NEXT_TURN();
									}
								}
								else if (pickingMaterialsIron && mapFieldsIronValue[i][j] >= 1) {
									if (mapFieldsIronValue[i][j] > 1) {
										if (mapFieldsNames[i][j] != "water") {
											playerIronValue++;
											mapFieldsIronValue[i][j]--;
										}
										else {
											playerIronValue += 0.1;
											mapFieldsIronValue[i][j] -= 0.1;
										}
										NEXT_TURN();
									}
								}
								else if (pickingMaterialsFood) {
									playerFoodValue += 10;
									mapFieldsWoodValue[i][j] -= 0.1;
									NEXT_TURN();
								}
							}
						}
					}
				}

				//REMOVE 
				if (removingBuildings) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								if (mapFieldsBuildings[i][j] == "")
									removingBuildings = false;
								else {
									if (mapFieldsBuildings[i][j] != "townHall") {
										for (int k = 0; k < 50; k++) {
											if (mapFieldsBuildings[i][j] == buildingsStrings[k]) {
												removingBuildings = false;
												REMOVE_BUILDING(i, j, k); break; 
											}
										}
									}
									else
										removingBuildings = false;
								}
							}
						}
					}
				}

				//UPGRADE
				if (upgradingBuildings) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								if (mapFieldsBuildings[i][j] != "" && !upgradeBuilding[i][j]) {
									UPGRADE_BUILDING(i, j, mapFieldsBuildings[i][j]);
									upgradingBuildings = false;
								}
								else
									upgradingBuildings = false;
							}
						}
					}
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) { CHEATS(); }

				//MORE BUTTON (FOOD)
				if (mouseX <= sp[5][46].getPosition().x || (mouseX >= sp[5][46].getPosition().x + sp[5][46].getGlobalBounds().width) || mouseY <= sp[5][46].getPosition().y || (mouseY >= sp[5][46].getPosition().y + sp[5][46].getGlobalBounds().height)) moreFood = false;
				if (mouseX >= 675 && mouseX <= 691 && mouseY >= 32 && mouseY <= 48) { moreFood = !moreFood ? true : false; }
				if (mouseX >= (sp[5][46].getPosition().x + 288) && mouseX <= (sp[5][46].getPosition().x + 295) && mouseY >= (sp[5][46].getPosition().y+3) && mouseY <= (sp[5][46].getPosition().y + 11) && moreFood)	moreFood = false;

				//MORE BUTTON (MATERIALS)
				if (mouseX <= sp[5][45].getPosition().x || (mouseX >= sp[5][45].getPosition().x + sp[5][45].getGlobalBounds().width) || mouseY <= sp[5][45].getPosition().y || (mouseY >= sp[5][45].getPosition().y + sp[5][45].getGlobalBounds().height)) moreMaterials = false;
				if (mouseX >= 1253 && mouseX <= 1273 && mouseY >= 177 && mouseY <= 196) { moreMaterials = !moreMaterials ? true : false; }
				if (mouseX >= (sp[5][45].getPosition().x + 288) && mouseX <= (sp[5][45].getPosition().x + 295) && mouseY >= (sp[5][45].getPosition().y + 3) && mouseY <= (sp[5][45].getPosition().y + 11) && moreMaterials)	moreMaterials = false;
				
			}
			window.clear(Color::White);

			window.draw(sp[0][0]);	//T�O

			//WY�WIETLANIE T�A PRZYCISK�W U DO�U EKRANU
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 3; j++) {
					sp[0][1].setPosition(720 + (55 * i), 660 - (55 * j));
					window.draw(sp[0][1]);
				}
			}

			//POD�WIETLENIE IKON \/
			if (!yesNoBoxActive) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 3; j++) {
						if (mouseY >= 660 - (j * 55) && mouseY <= 706 - (j * 55) && mouseX >= 720 + (55 * i) && mouseX <= 720 + (55 * i) + 50 - 4) {	//2-4px cie� [!]
							sp[4][20 + i + (j * 10)].setColor(darkRed);
						}
						else {
							sp[4][20 + i + (j * 10)].setColor(Color::Black);
							if (i == 9 && j == 1)	sp[4][20 + i + (j * 10)].setColor(darkRed);		//RATUSZ
						}
					}
				}
			}

			//WY�WIETLANIE IKON PRZYCISK�W U DO�U EKRANU \/?
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 3; j++) {
					sp[4][20 + i + (j * 10)].setPosition(727 + (55 * i), 666 - (55 * j));
					if (i == 9 && j == 0)	sp[4][20 + i + (j * 10)].move(-2, 2);			//EXIT
					if (i == 9 && j == 1)	sp[4][20 + i + (j * 10)].setColor(darkRed);		//RATUSZ
					window.draw(sp[4][20 + i + (j * 10)]);
				}
			}

			//WY�WIETLANIE P�L
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k < 1; k++) {
						if (mapFieldsNames[i][j] == "grass") {
							sp[5][5].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][5]);
							break;
						}
						if (mapFieldsNames[i][j] == "dirt") {
							sp[5][6].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][6]);
							break;
						}
						if (mapFieldsNames[i][j] == "water") {
							sp[5][7].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][7]);
							break;
						}
						if (mapFieldsNames[i][j] == "forest") {
							sp[5][8].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][8]);
							break;
						}
						if (mapFieldsNames[i][j] == "mountain") {
							sp[5][9].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][9]);
							break;
						}
					}
				}
			}

			//YW�WIETLANIE ZBLI�ENIA POLA
			if (!yesNoBoxActive && !moreFood && !moreMaterials) {
				if (mouseX >= 50 && mouseX <= 700 && mouseY >= 50 && mouseY <= 700) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								fieldActiveByMouseX = i;
								fieldActiveByMouseY = j;
								for (int k = 0; k < 1; k++) {
									if (mapFieldsNames[i][j] == "grass") {
										sp[4][0].setTexture(tex[4][0]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "dirt") {
										sp[4][0].setTexture(tex[4][1]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "water") {
										sp[4][0].setTexture(tex[4][2]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "forest") {
										sp[4][0].setTexture(tex[4][3]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "mountain") {
										sp[4][0].setTexture(tex[4][4]);
										FIELD_ZOOM(i, j);
										break;
									}
								}
							}
						}
					}
					window.draw(sp[4][0]);
					for (int i = 0; i < 5; i++)
						window.draw(txt[0][i]);
					window.draw(txt[0][12]);
				}
			}
			window.draw(txt[5][10]);

			//IKONY BUDYNK�W \/
			SHOW_BUILD();

			sp[5][47].setPosition(645, 3);
			window.draw(sp[5][47]);
			txt[0][17].setString(TO_STRINGSTREAM(playerFoodValue));
			txt[0][17].setFillColor(Color::White);
			window.draw(txt[0][17]);

			sp[4][5].setPosition(450, 10);
			window.draw(sp[4][5]);
			sp[4][6].setPosition(451, 11);
			window.draw(sp[4][6]);
			for (int i = 0; i < (((playerFoodValue / playerFoodCapacity)) * 100) - 13; i++) {
				sp[4][6].move(2, 0);
				window.draw(sp[4][6]);
			}
			txt[0][16].setString(TO_STRINGSTREAM(((playerFoodValue / playerFoodCapacity)) * 100) + "%");
			txt[0][16].setPosition(540 - txt[0][16].getLocalBounds().width / 2, 18);
			window.draw(txt[0][16]);
			window.draw(txt[0][15]);

			//WY�WIETLANIE IKON SUROWC�W (JE�LI WI�KSZE NI� 100) \/
			for (int i = 0; i < 3; i++)
				sp[1][i].setScale(0.35, 0.35);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					tAddon = 0;
					if (mapFieldsWoodValue[i][j] >= 100) {
						sp[1][0].setPosition(52 + (65 * i), 95 + (65 * j));
						window.draw(sp[1][0]);
						tAddon++;
					}
					if (mapFieldsStoneValue[i][j] >= 100) {
						sp[1][1].setPosition(52 + (20 * tAddon) + (65 * i), 95 + (65 * j));
						window.draw(sp[1][1]);
						tAddon++;
					}
					if (mapFieldsIronValue[i][j] >= 100) {
						sp[1][2].setPosition(52 + (20 * tAddon) + (65 * i), 95 + (65 * j));
						window.draw(sp[1][2]);
					}
				}
			}

			//WY�WIETLANIE ILO�CI SUROWC�W ETC.
			sp[5][49].setPosition(1175, 50);
			sp[5][48].setPosition(1216, 200);
			window.draw(sp[5][49]);
			window.draw(sp[5][48]);
			for (int i = 0; i < 3; i++) {
				sp[1][i].setScale(0.65, 0.65);
				sp[1][i].setPosition(1180, 60 + (45 * i));
				window.draw(sp[1][i]);
			}
			for (int i = 5; i < 8; i++)
				window.draw(txt[0][i]);
			for (int i = 0; i < 3; i++) {
				txt[0][8].setPosition(1220, 65 + (45 * i));
				window.draw(txt[0][8]);
			}
			for (int i = 9; i < 12; i++)
				window.draw(txt[0][i]);

			//moreButton (food)
			sp[1][4].setPosition(675, 32);
			if (mouseX >= 646 && mouseX <= 691 && mouseY >= 5 && mouseY <= 48)	sp[1][4].setColor(colorSp1_4);
			else sp[1][4].setColor(Color::Transparent);
			window.draw(sp[1][4]);
			//moreButton (materials)
			sp[1][4].setPosition(1253, 177);
			if (mouseX >= 1176 && mouseX <= 1271 && mouseY >= 52 && mouseY <= 195)	sp[1][4].setColor(colorSp1_4);
			else sp[1][4].setColor(Color::Transparent);
			window.draw(sp[1][4]);


			if (yesNoBoxActive == true) {
				if (lang == "english")
					YES_NO_BOX(L"Are you sure you want to Exit?", L"Unsaved progress will be lost!");
				if (lang == "polish")
					YES_NO_BOX(L"Na pewno chcesz opu�ci� gr�?", L"Nie zapisane dane zostan� utracone!");
			}

			//PLACE BUILDINGS 
			if (placeBuilding == true) { PLACE_BUILDING(placeBuildingName); window.draw(txt[0][13]); }

			//NEXT TURN
			if (mouseX >= 720 && mouseX <= 765 && mouseY >= 660 && mouseY <= 705 && !placeBuilding) {
				txt[0][13].setFillColor(Color::Color(0, 100, 0, 255));
				txt[0][13].setPosition(1125, 60);			txt[0][13].setString("+" + TO_STRINGSTREAM_DOUBLE(ROUND(((playerPopulation * 0.09) * 1) * buildingsAmount[5])));	window.draw(txt[0][13]);
				txt[0][13].setPosition(1125, 60 + 50);		txt[0][13].setString("+" + TO_STRINGSTREAM_DOUBLE(ROUND(((playerPopulation * 0.06) * 1) * buildingsAmount[6])));	window.draw(txt[0][13]);
				txt[0][13].setPosition(1125, 60 + 100);		txt[0][13].setString("+" + TO_STRINGSTREAM_DOUBLE(ROUND(((playerPopulation * 0.04) * 1) * buildingsAmount[7])));	window.draw(txt[0][13]);
			}

			//NARZ�DZIA MANUALNEGO ZBIERANIA SUROWC�W/JEDZENIA
			if (pickingMaterialsWood || pickingMaterialsStone || pickingMaterialsIron || pickingMaterialsFood) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
							sp[5][3].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][3]);
							if (pickingMaterialsFood) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(700, 15); txt[0][13].setString("+10"); window.draw(txt[0][13]);
							}
							if (pickingMaterialsWood && mapFieldsWoodValue[i][j] >= 1) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(1125, 60); txt[0][13].setString("+1");
								if (mapFieldsNames[i][j] == "water") txt[0][13].setString("+0.1");
								window.draw(txt[0][13]);
							}
							if (pickingMaterialsStone && mapFieldsStoneValue[i][j] >= 1) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(1125, 60 + 50); txt[0][13].setString("+1");
								if (mapFieldsNames[i][j] == "water") txt[0][13].setString("+0.1");
								window.draw(txt[0][13]);
							}
							if (pickingMaterialsIron && mapFieldsIronValue[i][j] >= 1) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(1125, 60 + 100); txt[0][13].setString("+1");
								if (mapFieldsNames[i][j] == "water") txt[0][13].setString("+0.1");
								window.draw(txt[0][13]);
							}
						}
					}
				}
				if (pickingMaterialsFood) { sp[4][24].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][24]); }
				if (pickingMaterialsWood) { sp[4][25].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][25]); }
				if (pickingMaterialsStone) { sp[4][26].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][26]); }
				if (pickingMaterialsIron) { sp[4][27].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][27]); }
			}
			window.draw(txt[0][14]);

			//REMOVE, UPGRADE
			if (removingBuildings || upgradingBuildings) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
							sp[5][3].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][3]);
							if (upgradingBuildings) 
								if (mapFieldsBuildings[i][j] != "") 
									UPGRADE_BUILDING_COST(i, j, mapFieldsBuildings[i][j]);
						}
					}
				}
				if (removingBuildings) { sp[4][22].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][22]); }
				if (upgradingBuildings) { sp[4][23].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][23]); }
			}

			//MORE FOOD, MORE MATERIALS
			if (moreFood)	FOOD_MORE();
			if (moreMaterials)	MATERIALS_MORE();

			window.display();
		}
	}
}

void SHOW_BUILD() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 1; k++) {
				if (mapFieldsBuildings[i][j] == "townHall") { SHOW_BUILD_MAIN(4, 39, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "storage") { SHOW_BUILD_MAIN(4, 38, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "simpleHouse") { SHOW_BUILD_MAIN(4, 30, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "woodenHouse") { SHOW_BUILD_MAIN(4, 31, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "stoneHouse") { SHOW_BUILD_MAIN(4, 32, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "lumberjack") {
					if (mapFieldsWoodValue[i][j] < 1) SHOW_BUILD_MAIN(4, 33, i, j, darkRed); else SHOW_BUILD_MAIN(4, 33, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "quarry") {
					if (mapFieldsStoneValue[i][j] < 1) SHOW_BUILD_MAIN(4, 34, i, j, darkRed); else SHOW_BUILD_MAIN(4, 34, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "mine") {
					if (mapFieldsIronValue[i][j] < 1) SHOW_BUILD_MAIN(4, 35, i, j, darkRed); else SHOW_BUILD_MAIN(4, 35, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "farm") { SHOW_BUILD_MAIN(4, 40, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "fish") { SHOW_BUILD_MAIN(4, 41, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "hunting") { SHOW_BUILD_MAIN(4, 42, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "gather") { SHOW_BUILD_MAIN(4, 43, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "windmill") { SHOW_BUILD_MAIN(4, 44, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "carpenter") { 
					if (!playerMaterialsItems[0]) SHOW_BUILD_MAIN(4, 45, i, j, darkRed); else SHOW_BUILD_MAIN(4, 45, i, j, Color::Black); break; }
				if (mapFieldsBuildings[i][j] == "foundry") {
					if (!playerMaterialsItems[1]) SHOW_BUILD_MAIN(4, 46, i, j, darkRed); else SHOW_BUILD_MAIN(4, 46, i, j, Color::Black); break; }
				
			}
			if (upgradeBuilding[i][j] == true) { sp[1][3].setPosition(72 + (65 * i), 54 + (65 * j)); window.draw(sp[1][3]); }
		}
	}
}

void ADD_BUILDING(int x, int y, int id, string name) {
	if (name == "storage") {
		if (mapFieldsNames[x][y] != "water") {
			playerWoodCapacity = 200 * buildingsAmount[id];
			playerStoneCapacity = 175 * buildingsAmount[id];
			playerIronCapacity = 150 * buildingsAmount[id];
			playerFoodCapacity = (1000 * buildingsAmount[id]) + 200;
			ADD_BUILDING_MAIN(x, y, id, name);
		}
	}
	else if (name == "townHall") {
		if (mapFieldsNames[x][y] != "water") {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if ((name == "simpleHouse" || name == "woodenHouse" || name == "stoneHouse")  && (mapFieldsNames[x][y] != "water"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "lumberjack" || name == "quarry" || name == "mine") && (mapFieldsNames[x][y] != "water"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "farm") && (mapFieldsNames[x][y] != "water" && mapFieldsNames[x][y] != "mountain" && mapFieldsNames[x][y] != "forest")) 
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "fish") && (mapFieldsNames[x][y] == "water"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "hunting") && (mapFieldsNames[x][y] == "forest"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "gather") && (mapFieldsNames[x][y] == "forest" || mapFieldsNames[x][y] == "dirt"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "windmill") && (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] != "forest"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "carpenter") && (mapFieldsNames[x][y] != "water"))
		ADD_BUILDING_MAIN(x, y, id, name);
	else if ((name == "foundry") && (mapFieldsNames[x][y] != "water"))
		ADD_BUILDING_MAIN(x, y, id, name);
	
	CHECK_STATUS_1();
}

void REMOVE_BUILDING(int x, int y, int id) {
	buildingsAmount[id]--;
	mapFieldsBuildings[x][y] = "";
	upgradeBuilding[x][y] = false;
	CHECK_STATUS_1();
	SET_TEXT(incode);
	NEXT_TURN();
}

void UPGRADE_BUILDING(int x, int y, string name) {
	if (name == "storage") { UPGRADE_BUILDING_MAIN(x, y, 200, 200, 125); }
	else if (name == "simpleHouse") { UPGRADE_BUILDING_MAIN(x, y, 50, 50, 50); }
	else if (name == "woodenHouse") { UPGRADE_BUILDING_MAIN(x, y, 200, 50, 50); }
	else if (name == "stoneHouse") { UPGRADE_BUILDING_MAIN(x, y, 50, 200, 100); }
	else if (name == "lumberjack") { UPGRADE_BUILDING_MAIN(x, y, 200, 50, 50); }
	else if (name == "quarry") { UPGRADE_BUILDING_MAIN(x, y, 50, 200, 50); }
	else if (name == "mine") { UPGRADE_BUILDING_MAIN(x, y, 50, 50, 200); }
	else if (name == "farm") { UPGRADE_BUILDING_MAIN(x, y, 100, 100, 50); }
	else if (name == "fish") { UPGRADE_BUILDING_MAIN(x, y, 100, 100, 50); }
	else if (name == "hunting") { UPGRADE_BUILDING_MAIN(x, y, 250, 50, 50); }
	else if (name == "gather") { UPGRADE_BUILDING_MAIN(x, y, 200, 50, 100); }
	else if (name == "windmill") { UPGRADE_BUILDING_MAIN(x, y, 100, 100, 100); }
}

void UPGRADE_BUILDING_COST(int x, int y, string name) {
	if (name == "storage" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 200, 200, 125); }
	if (name == "simpleHouse" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 50, 50, 50); }
	if (name == "woodenHouse" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 200, 50, 50); }
	if (name == "stoneHouse" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 50, 200, 100); }
	if (name == "lumberjack" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 200, 50, 50); }
	if (name == "quarry" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 50, 200, 50); }
	if (name == "mine" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 50, 50, 200); }
	if (name == "farm" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 100, 100, 50); }
	if (name == "fish" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 100, 100, 50); }
	if (name == "hunting" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 250, 50, 50); }
	if (name == "gather" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 200, 50, 100); }
	if (name == "windmill" && !upgradeBuilding[x][y]) { UPGRADE_BUILDING_COST_MAIN(x, y, 100, 100, 100); }
}

void CHECK_STATUS_1() {
	playerWoodCapacity = 200 * buildingsAmount[1];
	playerStoneCapacity = 175 * buildingsAmount[1];
	playerIronCapacity = 150 * buildingsAmount[1];
	playerFoodCapacity = (1000 * buildingsAmount[1]) + 200;

	playerPopulation = 11;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mapFieldsBuildings[i][j] == "storage" && upgradeBuilding[i][j]) {
				playerWoodCapacity += 500;
				playerStoneCapacity += 350;
				playerIronCapacity += 200;
				playerFoodCapacity += 800;
			}
			if (mapFieldsBuildings[i][j] == "simpleHouse") {
				if (!upgradeBuilding[i][j]) playerPopulation += 4;
				else playerPopulation += 8;
			}
			if (mapFieldsBuildings[i][j] == "woodenHouse") {
				if (!upgradeBuilding[i][j]) playerPopulation += 7;
				else playerPopulation += 12;
			}
			if (mapFieldsBuildings[i][j] == "stoneHouse") {
				if (!upgradeBuilding[i][j]) playerPopulation += 12;
				else playerPopulation += 24;
			}
		}
	}

	if (playerWoodValue > playerWoodCapacity)	playerWoodValue = playerWoodCapacity;
	if (playerStoneValue > playerStoneCapacity)	playerStoneValue = playerStoneCapacity;
	if (playerIronValue > playerIronCapacity)	playerIronValue = playerIronCapacity;
	if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
}

void PLACE_BUILDING(string building) {
	txt[0][13].setFillColor(Color::Red);
	for (int k = 0; k < 1; k++) {
		if (building == "storage")		{ PLACE_BUILDING_MAIN(4, 38, 1); break; }
		if (building == "simpleHouse")	{ PLACE_BUILDING_MAIN(4, 30, 2); break; }
		if (building == "woodenHouse")	{ PLACE_BUILDING_MAIN(4, 31, 3); break; }
		if (building == "stoneHouse")   { PLACE_BUILDING_MAIN(4, 32, 4); break; }
		if (building == "lumberjack")	{ PLACE_BUILDING_MAIN(4, 33, 5); break; }
		if (building == "quarry")		{ PLACE_BUILDING_MAIN(4, 34, 6); break; }
		if (building == "mine")			{ PLACE_BUILDING_MAIN(4, 35, 7); break; }
		if (building == "farm")			{ PLACE_BUILDING_MAIN(4, 40, 8); break; }
		if (building == "fish")			{ PLACE_BUILDING_MAIN(4, 41, 9); break; }
		if (building == "hunting")		{ PLACE_BUILDING_MAIN(4, 42, 10); break; }
		if (building == "gather")		{ PLACE_BUILDING_MAIN(4, 43, 11); break; }
		if (building == "windmill")		{ PLACE_BUILDING_MAIN(4, 44, 12); break; }
		if (building == "carpenter")	{ PLACE_BUILDING_MAIN(4, 45, 13); break; }
		if (building == "foundry")		{ PLACE_BUILDING_MAIN(4, 46, 14); break; }
	}
}

void FOOD_MORE() {
	sp[5][46].setPosition(403, 47);
	window.draw(sp[5][46]);
	for (int j = 0; j < 1; j++) {
		for (int i = 0; i < 6; i++) {
			sp[2][i].setPosition(417 + (75 * j), 70 + (30 * i));
			window.draw(sp[2][i]);
			switch (i) {
			case 0:	//WHEAT
				if (playerFoodItems[0]) FOOD_MORE_MAIN(i, j, true);
				else FOOD_MORE_MAIN(i, j, false);
				break;
			case 1: //FISH
				if (playerFoodItems[1]) FOOD_MORE_MAIN(i, j, true);
				else FOOD_MORE_MAIN(i, j, false);
				break;
			case 2: //MEAT
				if (playerFoodItems[2]) FOOD_MORE_MAIN(i, j, true);
				else FOOD_MORE_MAIN(i, j, false);
				break;
			case 3:	//HERB
				if (playerFoodItems[3]) FOOD_MORE_MAIN(i, j, true);
				else FOOD_MORE_MAIN(i, j, false);
				break;
			case 4: //FOREST FRUIT
				if (playerFoodItems[4]) FOOD_MORE_MAIN(i, j, true);
				else FOOD_MORE_MAIN(i, j, false);
				break;
			case 5: //FLOUR
				if (playerFoodItems[5]) FOOD_MORE_MAIN(i, j, true);
				else FOOD_MORE_MAIN(i, j, false);
				break;
			
			}
		}
	}
}

void MATERIALS_MORE() {
	sp[5][45].setPosition(880, 47);
	window.draw(sp[5][45]);
	for (int j = 0; j < 1; j++) {
		for (int i = 0; i < 6; i++) {
			sp[3][i].setPosition(894 + (75 * j), 70 + (30 * i));
			window.draw(sp[3][i]);
			switch (i) {
			case 0:	//PLANK
				if (playerMaterialsItems[0]) MATERIALS_MORE_MAIN(i, j, true);
				else MATERIALS_MORE_MAIN(i, j, false);
				break;
			case 1:	//IRON INGOT
				if (playerMaterialsItems[1]) MATERIALS_MORE_MAIN(i, j, true);
				else MATERIALS_MORE_MAIN(i, j, false);
				break;
			case 2: 
				
				break;
			case 3:	
				
				break;
			case 4: 
				
				break;
			case 5: 
				
				break;

			}
		}
	}
}

void NEXT_TURN() {
	turn++;
	txt[5][10].setString(TO_STRINGSTREAM(turn));
	txt[5][10].setPosition(1225 - (txt[5][10].getLocalBounds().width / 2), 20);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mapFieldsBuildings[i][j] == "lumberjack") {
				if (mapFieldsWoodValue[i][j] > ((playerPopulation * 0.09) * 1)) {
					mapFieldsWoodValue[i][j] -= ((playerPopulation * 0.09) * 1);
					playerWoodValue += ((playerPopulation * 0.09) * 1);
					if (upgradeBuilding[i][j] && mapFieldsWoodValue[i][j] >((playerPopulation * 0.09) * 1)) {
						mapFieldsWoodValue[i][j] -= ((playerPopulation * 0.09) * 1);
						playerWoodValue += ((playerPopulation * 0.09) * 1);
					}
				}
				else if (mapFieldsWoodValue[i][j] < ((playerPopulation * 0.09) * 1) && mapFieldsWoodValue > 0) {
					playerWoodValue += mapFieldsWoodValue[i][j];
					mapFieldsWoodValue[i][j] -= mapFieldsWoodValue[i][j];
				}
				if (mapFieldsWoodValue[i][j] == 0) workField[i][j] = false;
			}
			else if (mapFieldsBuildings[i][j] == "quarry") {
				if (mapFieldsStoneValue[i][j] > ((playerPopulation * 0.06) * 1)) {
					mapFieldsStoneValue[i][j] -= ((playerPopulation * 0.06) * 1);
					playerStoneValue += ((playerPopulation * 0.06) * 1);
					if (upgradeBuilding[i][j] && mapFieldsStoneValue[i][j] > ((playerPopulation * 0.06) * 1)) {
						mapFieldsStoneValue[i][j] -= ((playerPopulation * 0.06) * 1);
						playerStoneValue += ((playerPopulation * 0.06) * 1);
					}
				}
				else if (mapFieldsStoneValue[i][j] < ((playerPopulation * 0.06) * 1) && mapFieldsWoodValue > 0) {
					playerStoneValue += mapFieldsStoneValue[i][j];
					mapFieldsStoneValue[i][j] -= mapFieldsStoneValue[i][j];
				}
				if (mapFieldsStoneValue[i][j] == 0) workField[i][j] = false;
			}
			else if (mapFieldsBuildings[i][j] == "mine") {
				if (mapFieldsIronValue[i][j] > ((playerPopulation * 0.04) * 1)) {
					mapFieldsIronValue[i][j] -= ((playerPopulation * 0.04) * 1);
					playerIronValue += ((playerPopulation * 0.04) * 1);
					if (upgradeBuilding[i][j] && mapFieldsIronValue[i][j] > ((playerPopulation * 0.04) * 1)) {
						mapFieldsIronValue[i][j] -= ((playerPopulation * 0.04) * 1);
						playerIronValue += ((playerPopulation * 0.04) * 1);
					}
				}
				else if (mapFieldsIronValue[i][j] < ((playerPopulation * 0.04) * 1) && mapFieldsIronValue > 0) {
					playerIronValue += mapFieldsIronValue[i][j];
					mapFieldsIronValue[i][j] -= mapFieldsIronValue[i][j];
				}
				if (mapFieldsIronValue[i][j] == 0) workField[i][j] = false;
			}
			else if (mapFieldsBuildings[i][j] == "farm") {
				playerFoodValue += (1 * (playerPopulation * 0.2));
				if (upgradeBuilding[i][j]) playerFoodValue += (1 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
				playerFoodItems[0] = true;
			}
			else if (mapFieldsBuildings[i][j] == "fish") {
				playerFoodValue += (1.2 * (playerPopulation * 0.2));
				if (upgradeBuilding[i][j]) playerFoodValue += (1.2 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
				playerFoodItems[1] = true;
			}
			else if (mapFieldsBuildings[i][j] == "hunting") {
				playerFoodValue += (1.3 * (playerPopulation * 0.2));
				if (upgradeBuilding[i][j]) playerFoodValue += (1.3 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
				playerFoodItems[2] = true;
			}
			else if (mapFieldsBuildings[i][j] == "gather") {
				playerFoodValue += (0.75 * (playerPopulation * 0.2));
				if (upgradeBuilding[i][j]) playerFoodValue += (0.75 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
				playerFoodItems[3] = true; playerFoodItems[4] = true;
			}
			else if (mapFieldsBuildings[i][j] == "windmill") {
				playerFoodValue += (1 * (playerPopulation * 0.2));
				if (upgradeBuilding[i][j]) playerFoodValue += (1 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
				if (buildingsAmount[8] > 0) playerFoodItems[5] = true;
			}
			else if (mapFieldsBuildings[i][j] == "carpenter") {
				if (playerWoodValue >= 1 * (playerPopulation * 0.1)) {
					playerWoodValue -= (1 * (playerPopulation * 0.1));
					playerMaterialsItems[0] = true;
				}
				else playerMaterialsItems[0] = false;
			}
			else if (mapFieldsBuildings[i][j] == "foundry") {
				if (playerIronValue >= 1 * (playerPopulation * 0.1)) {
					playerIronValue -= (1 * (playerPopulation * 0.1));
					playerMaterialsItems[1] = true;
				}
				else playerMaterialsItems[1] = false;
			}
		}
	}
	playerFoodValue -= (((playerPopulation * 0.1) * 10) + 1);
	for (int f = 30; f < playerPopulation; f += 30)
		playerFoodValue -= (((playerPopulation * 0.1) * 5) + 1);

	CHECK_STATUS_1();
	SET_TEXT(incode);
}

void CHECKBOX(int posX, int posY, bool argument[], wstring checkboxName, int boxesNumber, wstring box1, wstring box2, wstring box3, wstring box4, wstring box5, wstring box6) {
	txt[5][0].setString(checkboxName + ":");
	txt[5][0].setPosition(posX, posY);
	window.draw(txt[5][0]);
	for (int i = 0; i < boxesNumber; i++) {
		sp[5][0].setPosition(posX, (posY + 50) + (40 * i));
		switch (i) {
		case 0:	txt[5][i + 1].setString(box1); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 1:	txt[5][i + 1].setString(box2); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 2:	txt[5][i + 1].setString(box3); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 3:	txt[5][i + 1].setString(box4); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 4:	txt[5][i + 1].setString(box5); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 5:	txt[5][i + 1].setString(box6); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		}
		window.draw(sp[5][0]);
	}

	if (event.type == Event::MouseButtonPressed) {
		for (int i = 0; i < boxesNumber; i++) {
			if (mouseX >= posX && mouseX <= posX + 25) {
				if (mouseY >= (posY + 50) + (40 * i) && mouseY <= (posY + 50) + (40 * i) + 25) {
					if (argument[i] == false) {
						argument[i] = true;
						for (int j = 0; j < boxesNumber; j++) {
							if (j !=  i)	argument[j] = false;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < boxesNumber; i++) {
		if (argument[i] == true) {
			sp[5][1].setPosition(posX, (posY + 50) + (40 * i));
			window.draw(sp[5][1]);
			break;
		}
	}
}

string INPUT_TEXT(int posX, int posY, wstring inputTextName, string outputString) {
	txt[5][7].setString(inputTextName + ":");
	txt[5][7].setPosition(posX + 10, posY);
	window.draw(txt[5][7]);
	sp[5][2].setPosition(posX, posY + 35);
	window.draw(sp[5][2]);
	txt[5][8].setPosition(posX + 13, posY + 38);
	txt[5][8].setString(inputText);
	window.draw(txt[5][8]);
	if (event.type == Event::MouseButtonPressed) {
		if (mouseX >= posX && mouseX <= posX + 300 && mouseY >= posY + 35 && mouseY <= posY + 35 + 39) {
			if (textareaActive == false)
				textareaActive = true;
		}
		else {
			if (textareaActive == true)
				textareaActive = false;
		}
	}

	if (textareaActive == true) {
		txt[5][9].setPosition(posX + 13 + txt[5][8].getLocalBounds().width, posY + 38);
		mainTime = mainClock.getElapsedTime();
		timeSeconds = mainTime.asSeconds();
		if (timeSeconds % 2 == 0)
			window.draw(txt[5][9]);
	}

	if (event.type == Event::TextEntered && timer == 0 && textareaActive == true) {
		if (event.text.unicode == '\b' && inputText.getSize() > 0) {
			inputText.erase(inputText.getSize() - 1, 1);
			timer = 4;
		}
		else if (txt[5][8].getLocalBounds().width < 250) {
			inputText += static_cast<char>(event.text.unicode);
			timer = 4;
		}
	}
	outputString = inputText;
	if (timer > 0)
		timer--;
	else
		timer = 0;
	return outputString;
	/* DODA� DO window.pollEvent(event) [!] [!] [!] [!] [!] [!] [!] [!] [!] [!] [!]
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				textareaActive = false;
	*/
}

void YES_NO_BOX(wstring boxContent, wstring boxExtraContent) {
	sp[5][50].setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 100);
	window.draw(sp[5][50]);
	txt[5][50].setPosition(window.getSize().x / 2 - 120, window.getSize().y / 2 + 25);
	window.draw(txt[5][50]);
	txt[5][49].setPosition(window.getSize().x / 2 + 70, window.getSize().y / 2 + 25);
	window.draw(txt[5][49]);

	txt[5][48].setString(boxContent);
	txt[5][48].setPosition(window.getSize().x / 2 - txt[5][48].getLocalBounds().width/2, window.getSize().y / 2 - txt[5][48].getLocalBounds().height/2 - 60);
	txt[5][47].setString(boxExtraContent);
	txt[5][47].setPosition(window.getSize().x / 2 - txt[5][47].getLocalBounds().width / 2, window.getSize().y / 2 - txt[5][47].getLocalBounds().height / 2 - 10);
	window.draw(txt[5][48]);
	window.draw(txt[5][47]);

	if (mouseX >= window.getSize().x / 2 - 200 + 60 && mouseX <= window.getSize().x / 2 - 200 + 150 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169)
		txt[5][50].setFillColor(darkRed);
	else
		txt[5][50].setFillColor(Color::Black);

	if (mouseX >= window.getSize().x / 2 - 200 + 245 && mouseX <= window.getSize().x / 2 - 200 + 337 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169)
		txt[5][49].setFillColor(darkRed);
	else
		txt[5][49].setFillColor(Color::Black);

	/*	DODA� DO MouseButtonPressed [!] [!] [!] [!] [!] [!] [!]
	if (yesNoBoxActive == true) {
					if (mouseX >= window.getSize().x / 2 - 200 + 60 && mouseX <= window.getSize().x / 2 - 200 + 150 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						//yes...
					}
					if (mouseX >= window.getSize().x / 2 - 200 + 245 && mouseX <= window.getSize().x / 2 - 200 + 337 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						//no...
					}
				}
	*/
}

void FIELD_ZOOM(int i, int j) {
	if (lang == "english") {
		txt[0][1].setString("Field Type: " + mapFieldsNames[i][j]);
		txt[0][2].setString("Wood: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodCapacity[i][j])));
		txt[0][3].setString("Stone: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneCapacity[i][j])));
		txt[0][4].setString("Iron: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronCapacity[i][j])));
		//Budynki \/
		if (mapFieldsBuildings[i][j] == "townHall")
			FIELD_ZOOM_MAIN(i, j, L"Town Hall", "", false, "", false, false, false);
		else if (mapFieldsBuildings[i][j] == "storage")
			FIELD_ZOOM_MAIN(i, j, L"Storage", "", false, "", false, false, false);
		else if (mapFieldsBuildings[i][j] == "simpleHouse")
			FIELD_ZOOM_MAIN(i, j, L"Simple House", "(4 res.)", true, "(8 res.)", false, false, false);
		else if (mapFieldsBuildings[i][j] == "woodenHouse")
			FIELD_ZOOM_MAIN(i, j, L"Wooden House", "(7 res.)", true, "(14 res.)", false, false, false);
		else if (mapFieldsBuildings[i][j] == "stoneHouse")
			FIELD_ZOOM_MAIN(i, j, L"Stone House", "(12 res.)", true, "(24 res.)", false, false, false);
		else if (mapFieldsBuildings[i][j] == "lumberjack")
			FIELD_ZOOM_MAIN(i, j, L"Lumberjack", "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.09) * 1)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.09) * 2)) + ")", true, false, false);
		else if (mapFieldsBuildings[i][j] == "quarry")
			FIELD_ZOOM_MAIN(i, j, L"Quarry", "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.06) * 1)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.06) * 2)) + ")", true, false, false);
		else if (mapFieldsBuildings[i][j] == "mine")
			FIELD_ZOOM_MAIN(i, j, L"Mine", "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.04) * 1)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.04) * 2)) + ")", true, false, false);
		else if (mapFieldsBuildings[i][j] == "farm")
			FIELD_ZOOM_MAIN(i, j, L"Farm", "(" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "fish")
			FIELD_ZOOM_MAIN(i, j, L"Fisher Hut", "(" + TO_STRINGSTREAM_DOUBLE(1.2 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2.4 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "hunting")
			FIELD_ZOOM_MAIN(i, j, L"Hunting Cabine", "(" + TO_STRINGSTREAM_DOUBLE(1.3 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2.6 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "gather")
			FIELD_ZOOM_MAIN(i, j, L"Gather's Hut", "(" + TO_STRINGSTREAM_DOUBLE(0.75 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(1.5 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "windmill") 
			FIELD_ZOOM_MAIN(i, j, L"Windmill", "(" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2 * (playerPopulation * 0.2)) + ")", false, true, playerFoodItems[0]);
		else if (mapFieldsBuildings[i][j] == "carpenter")
			FIELD_ZOOM_MAIN(i, j, L"Carpenter", "(-" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.1)) + ")", false, "", false, true, playerMaterialsItems[0]);
		else if (mapFieldsBuildings[i][j] == "foundry")
			FIELD_ZOOM_MAIN(i, j, L"Foundry", "(-" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.1)) + ")", false, "", false, true, playerMaterialsItems[1]);
		else txt[0][12].setString("Building: None");
	}
	else if (lang == "polish") {
		RELOAD_LANGUAGE_STRINGS();
		txt[0][1].setString("Rodzaj Pola: " + mapFieldsNamesPol[i][j]);
		txt[0][2].setString("Drewno: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodCapacity[i][j])));
		txt[0][3].setString(L"Kamie�: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneCapacity[i][j])));
		txt[0][4].setString(L"�elazo: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronCapacity[i][j])));
		//Budynki \/
		if (mapFieldsBuildings[i][j] == "townHall")
			FIELD_ZOOM_MAIN(i, j, L"Ratusz", "", false, "", false, false, false);
		else if (mapFieldsBuildings[i][j] == "storage")
			FIELD_ZOOM_MAIN(i, j, L"Magazyn", "", false, "", false, false, false);
		else if (mapFieldsBuildings[i][j] == "simpleHouse")
			FIELD_ZOOM_MAIN(i, j, L"Zwyk�y Dom", "(4 miesz.)", true, "(8 miesz.)", false, false, false);
		else if (mapFieldsBuildings[i][j] == "woodenHouse")
			FIELD_ZOOM_MAIN(i, j, L"Drewniany Dom", "(7 miesz.)", true, "(14 miesz.)", false, false, false);
		else if (mapFieldsBuildings[i][j] == "stoneHouse")
			FIELD_ZOOM_MAIN(i, j, L"Kamienny Dom", "(12 miesz.)", true, "(24 miesz.)", false, false, false);
		else if (mapFieldsBuildings[i][j] == "lumberjack")
			FIELD_ZOOM_MAIN(i, j, L"Drwal", "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.09) * 1)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.09) * 2)) + ")", true, false, false);
		else if (mapFieldsBuildings[i][j] == "quarry")
			FIELD_ZOOM_MAIN(i, j, L"Kamienio�om", "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.06) * 1)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.06) * 2)) + ")", true, false, false);
		else if (mapFieldsBuildings[i][j] == "mine")
			FIELD_ZOOM_MAIN(i, j, L"Kopalnia", "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.04) * 1)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.04) * 2)) + ")", true, false, false);
		else if (mapFieldsBuildings[i][j] == "farm")
			FIELD_ZOOM_MAIN(i, j, L"Farma", "(" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "fish")
			FIELD_ZOOM_MAIN(i, j, L"Chata Rybaka", "(" + TO_STRINGSTREAM_DOUBLE(1.2 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2.4 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "hunting")
			FIELD_ZOOM_MAIN(i, j, L"Chata My�liwego", "(" + TO_STRINGSTREAM_DOUBLE(1.3 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2.6 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "gather")
			FIELD_ZOOM_MAIN(i, j, L"Chata Zbieracza", "(" + TO_STRINGSTREAM_DOUBLE(0.75 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(1.5 * (playerPopulation * 0.2)) + ")", false, false, false);
		else if (mapFieldsBuildings[i][j] == "windmill")
			FIELD_ZOOM_MAIN(i, j, L"M�yn", "(" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.2)) + ")", true, "(" + TO_STRINGSTREAM_DOUBLE(2 * (playerPopulation * 0.2)) + ")", false, true, playerFoodItems[0]);
		else if (mapFieldsBuildings[i][j] == "carpenter")
			FIELD_ZOOM_MAIN(i, j, L"Stolarz", "(-" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.1)) + ")", false, "", false, true, playerMaterialsItems[0]);
		else if (mapFieldsBuildings[i][j] == "foundry")
			FIELD_ZOOM_MAIN(i, j, L"Odlewnia Metalu", "(-" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.1)) + ")", false, "", false, true, playerMaterialsItems[1]);
		else txt[0][12].setString("Budynek: Brak");
	}
}

void RELOAD_LANGUAGE_STRINGS() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mapFieldsNames[i][j] == "grass") {
				mapFieldsNamesPol[i][j] = "trawa";
			}
			else if (mapFieldsNames[i][j] == "dirt") {
				mapFieldsNamesPol[i][j] = "ziemia";
			}
			else if (mapFieldsNames[i][j] == "water") {
				mapFieldsNamesPol[i][j] = "woda";
			}
			else if (mapFieldsNames[i][j] == "forest") {
				mapFieldsNamesPol[i][j] = "las";
			}
			else if (mapFieldsNames[i][j] == "mountain") {
				mapFieldsNamesPol[i][j] = "g�ra";
			}
		}
	}
}

void CHEATS() {
	string code = "";
	int codeInt1 = 0;
	int codeInt2 = 0;
	int codeInt3 = 0;
	cin >> code;
	if (code.find("map") != string::npos) {
		if (code.find("Generate") != string::npos)
			MAP_GENERATOR();
		else if (code.find("SetField") != string::npos) {
			cin >> code >> codeInt1 >> codeInt2;
			mapFieldsNames[codeInt1][codeInt2] = code;
		}
		else if (code.find("SetMaterials") != string::npos) {
			cin >> code >> codeInt1 >> codeInt2 >> codeInt3;
			if (code.find("Wood") != string::npos) {
				mapFieldsWoodValue[codeInt1][codeInt2] = codeInt3;
				if (mapFieldsWoodCapacity[codeInt1][codeInt2] < mapFieldsWoodValue[codeInt1][codeInt2])
					mapFieldsWoodCapacity[codeInt1][codeInt2] = codeInt3;
			}
			if (code.find("Stone") != string::npos) {
				mapFieldsStoneValue[codeInt1][codeInt2] = codeInt3;
				if (mapFieldsStoneCapacity[codeInt1][codeInt2] < mapFieldsStoneValue[codeInt1][codeInt2])
					mapFieldsStoneCapacity[codeInt1][codeInt2] = codeInt3;
			}
			if (code.find("Iron") != string::npos) {
				mapFieldsIronValue[codeInt1][codeInt2] = codeInt3;
				if (mapFieldsIronCapacity[codeInt1][codeInt2] < mapFieldsIronValue[codeInt1][codeInt2])
					mapFieldsIronCapacity[codeInt1][codeInt2] = codeInt3;
			}
		}
	}

	else if (code.find("return") != string::npos) {
		if (code.find("MainMenu") != string::npos)
			MAIN_MENU();
		else if (code.find("Settings") != string::npos)
			MAIN_MENU_SETTINGS();
		else if (code.find("StartGame") != string::npos)
			START_GAME();
	}

	else if (code.find("open") != string::npos) {
		if (code.find("YesNoBox") != string::npos)
			yesNoBoxActive = true;
	}

	else if (code.find("add") != string::npos) {
		cin >> code >> codeInt1;
		if (code.find("someMaterials") != string::npos) {
			playerWoodValue += codeInt1;
			playerStoneValue += codeInt1;
			playerIronValue += codeInt1;
		}
		else if (code.find("material") != string::npos) {
			if (code.find("Wood") != string::npos)
				playerWoodValue += codeInt1;
			else if (code.find("Stone") != string::npos)
				playerStoneValue += codeInt1;
			else if (code.find("Iron") != string::npos)
				playerIronValue += codeInt1;
		}
	}

	SET_TEXT(incode);

	/*	[!]
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) {	CHEATS();	}
	*/
}
