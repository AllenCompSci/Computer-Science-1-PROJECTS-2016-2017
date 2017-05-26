/*Holden Essman Devin Petersen Denny Pham
4/12/17
DankScape 4
Comp-Sci 1st
*/

#include<iostream>
#include<cmath>
#include<string>
#include<ctime>
#include<thread> 
#include<graphics.h>
#include<winbgi.cpp>
#include<Windows.h>  
#include <stdio.h> 
#include<mmsystem.h>  
#include <mciapi.h> 
#include "VirtualKeys.h" 
#pragma comment(lib, "winmm.lib") 
#pragma region GLOBALVARs;

using namespace std;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
void playSound(string, int);

int setMyColor(int color, int rectColor);
int GrDriver, GrMode, ErrorCode;
bool ispressed = false;
bool running = true;
bool cursorVisible;
int centerX, centerY;
HCURSOR visible, hCur1, hCur3;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//keylistener for spacebar to continue

int maxX, maxY, penColor; 
enum Gamestate {start, END, game};
Gamestate Dankscape = start;

/*struct button {
	int top, left, right, bottom;
	if (x1 < x2) {
	left = x1;
	right = x2;
	}
	else {
		left = x2;
		right = x1;
	}
	if (y1 < y2) {
	top = y1;
	bottom = y2;
}
	else {
		top = y2;
		bottom = y1;
	}
}*/

;
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	// screen holds string length of 75 with settextstyle(3, 0, 5)
	// screen holds string length of 93 with settextstyle(3, 0, 4)
	string theme = "RunescapeSwag.mp3";
	string suck = "SadViolin.mp3";
	string Welcome = "Welcome traveler";
	string Gnome1 = "I am the Gnome Child";
	string narrator1 = "You have been summoned by the grace of our lord Harambae to find one of his Yu-Gi-Oh Cards.";
	string narrator1B = "Someone broke into the house of Harambae and stole his favorite card, the legendary Blue";
	string yeet = "Eyes White Dragon. You must adventure forth and steal it back!";
	string narrator2 = "You start off your adventure between two paths, to the left leads into the town of Lumbridge and";
	string narrator2B = "to the right leads to the spooky woods. Where do you want to go first ? ";
	string ayylamao = "1)  Town of Lumbridge";
	string ayylamao2 = "2)  The dark scary woods";
	string narrator3 = "You walk into the town of Lumbridge where you see a horde of GF’s run at you. They all demand";
	string narrator3B = "420k Poke Dollars and won’t leave you alone until you buy at least one of them. What do you do?";
	string narrator4 = "You run into the ghost of Billy Mays. “HEY BILLY MAYS HERE!” he exclaimed. You try to attack";
	string narrator4B = "him, but he already started the commercial.You try to reach for the remote to mute the";
	string narrator4C = "commercial but it was too late; your ears start to foam with Oxiclean and you die.";
	string answer1A = "1)  Submit to their desires";
	string answer21 = "2)  Run away";
	string answerA1 = "You are mugged by the GF’s and lose all of your belongings and your desire to continue";
	string answerA12 = "your quest.";
	string answerB1 = "You manage to force your way through the mob of GF’s and escape into a house.";
	string narrator5 = "You run into the house and slam the door behind you. Once inside the house, you see a green";
	string narrator5B = "figure riding on a unicycle. What do you do ?";
	string answer4 = "1)  Oh shit Waddup?";
	string answer5 = "2)  Grab your sword and fight the creature.";
	string answer6 = "The creature turns around and reveals itself as “Dat Boi”. You kneel and worship a meme";
	string answer6B = "connoisseur.";
	string answer7 = "You draw your sword and dash toward the creature. It quickly leaps from the unicycle and lands";
	string answer7B = "right behind you.It unleashes the stolen Yu - Gi - Oh card Blue Eyes White Dragon and quickly";
	string answer7C = "introduces himself by dabbing.’Much wow, such unfair’ you shout.You are quickly overwhelmed by";
	string answer7D = "his immense knowledge of memes and faint.You lost 420 poke dollars.";
	string narrator6 = "Dat Boi slowly wheels his way toward you. “What is it that you are seeking child?”";
	string answer8 = "1)  “Are you my Dad?”";
	string answer9 = "2)  “My Lord, do you know where the sacred Blue Eyes White Dragon is?”";
	string narrator7 = "Dat Boi places his silky-soft hands on your shoulder. He then starts to cry his eyes out.";
	string narrator7B = "He wheels himself toward your ear and whispers, “I have not cried since the first time I got";
	string narrator7C = "the first child support check with the DNA test proving that I was your father. She then sent me";
	string narrator7D = "pictures of all the unicycles that she bought specifically not for me. Now tell me my son, what";
	string narrator7E = "do you desire ?";
	string narrator8 = "Dat Boi looks down upon you with eyes glowing black with hatred. He summons his might and";
	string narrator8B = "smites you. You faint and lose 420 Poke Dollars.";
	string narrator9 = "looks around the room. To his right, was the legendary Blue Eyes White Dragon and to the left";
	string narrator9B = "100 CS:GO cases. Which do you choose?";
	string answer10 = "1)  I choose you! Blue Eyes White Dragon!";
	string answer11 = "2)  I choose to open the hundred CS:GO cases!";
	string narrator10 = "You move toward the right and throw a Great Ball at the Yu-Gi-Oh Card. The Ball lands on the";
	string narrator10B = "ground.It proceeds to shake 3 times.Success! Blue Eyes White Dragon has been captured!";
	string narrator11 = "You move toward the 100 CS:GO Cases. One by one, you open each individual case. However, after";
	string narrator11B = "opening the cases, you end up with only blues and you’re kicked from the session due to a";
	string narrator11C = "host migration.";
	string narrator12 = "You leave Dat Boi’s home and return to the house of Harambae. In the front of the house, you see";
	string narrator12B = "the Gnome Child. “Congratulations my friend, you have completed your quest.” “ Harambae shall";
	string narrator12C = "be pleased to see his prized Yu - Gi - Oh card returned!” As a reward my young adventurer, you";
	string narrator12D = "may have a drink of either Clorox’s Lavender flavored bleach or Oxiclean";
	string answer12 = "1)  I choose you Clorox Lavender flavored bleach!!!!!!!!!!!";
	string answer13 = "2)  I choose you Oxiclean!!!!!!!!!!!!";
	string narrator13 = "As you go to drink the lavender flavored bleach Harambae himself comes down from the heavens to";
	string narrator13B = "stop you. He then takes you up to heaven with him and you become a meme god.";
	string narrator14 = "You grab the oxiclean and proceed to gulp it down, and when you finish the bottle you start to";
	string narrator14B = "have foam come out of your ears and mouth and die an excruciating death.";
	string Nextscreen = "Press space to continue";
	string lost = "YOU LOST HAHA";
	string rekt = "Lel top kek";
	string ddAB = "Are you up to the task?";
	string no = "1) No, I'm scared";
	string penis = "2) Yes";
	string hi = "You a little bitch";
	string dankscape = "DankScape 4";
	string continuity = "Press 1 to continue";
	string hey = "Hey! You are not supposed to be back here";
	string aids = "You see the gnome child standing there.....He looks so easy to defeat.....What do you do?";
	string aidsanswer1 = "1)  Challenge Him to a game of Destiny PVP";
	string aidsanswer2 = "2)  Challenge Him to a game of 'Which one is bleach?'";
	string ball = "You load into a match against the Gnome Child. As you enter the battlefield, you see him";
	string ball2 = "staring right into your soul.You instantly run behind a wall for cover.However, as soon";
	string ball3 = "as you make it to the wall, you see a orange ball fly past you.You believe that you are";
	string ball4 = "safe, but from downtown, the orange ball does a 90 degree turn and lands directly on you.";
	string ball5 = "Just before you blow up, you see the gnome child before you.He doesn't say anthing. Instead.....";
	string ball6 = "he dabs. You blow up.";
	string meme = "You walk up to the gnome child with two buckets. You place them before him and challenge him. He";
	string meme2 = "first looks at you, then he begins to laugh. 'How blinded are you, You honestly believe that you";
	string meme3 = "have the power to defeat me in this silly challenge ? You proceed to pour bleach into one gold";
	string meme4 = "cup and then Red Flavored Koolaid in the other.The Gnome Child steps up and chooses the Golden";
	string meme5 = "cup. He swallows the clear liquid down in one gulp and then looks at you.The Gnome Child begins";
	string meme6 = "to float in the air and chant a spell; cursing your bloodline with his eternal hatred. He";
	string meme7 = "dissolves into tiny fragments of past memes.The tiny fragments are absorbed into you and you";
	string meme8 = "become a meme connioissuer.";
	string win = "You have now become a meme god and will be forever immortalized";

	int answer;
	cleardevice();
	//Start Menu
	/*playSound(theme, 10000);*/
	Sleep(50);
	setfillstyle(1, 7);
	bar(0, 0, 1920, 1080);
	settextstyle(3, 0, 8);
	outtextxy(650, 340, dankscape.c_str());
	Sleep(1000);
	settextstyle(3, 0, 4);
	outtextxy(750, 640, continuity.c_str());
	cin >> answer;

	if (answer == 1){
	cleardevice();
	setfillstyle(1, 0);
	bar(0, 0, 1920, 1080);
	settextstyle(3, 0, 5);
	outtextxy(750, 440, Welcome.c_str()); /*welcome*/
	outtextxy(80, 640, Gnome1.c_str()); /*gnome child*/
	settextstyle(3, 0, 4);
	Sleep(3000);
	cleardevice();
	outtextxy(50, 50, narrator1.c_str()); /*beginning*/
	outtextxy(50, 150, narrator1B.c_str());
	outtextxy(50, 250, yeet.c_str());
	outtextxy(50, 350, ddAB.c_str());
	outtextxy(50, 450, no.c_str());
	outtextxy(50, 550, penis.c_str());
	cin >> answer;

	if (answer == 1) {
		cleardevice();
		outtextxy(750, 500, hi.c_str());
		system("pause");
	}

	else if (answer == 2) {

		cleardevice();
		outtextxy(50, 50, narrator2.c_str()); /*choice of woods or lumbridge*/
		outtextxy(50, 150, narrator2B.c_str());
		outtextxy(75, 250, ayylamao.c_str());
		outtextxy(75, 350, ayylamao2.c_str());
		cin >> answer;

		if (answer == 1) {
			cleardevice();
			outtextxy(50, 50, narrator3.c_str()); /*town of lumbridge*/
			outtextxy(50, 150, narrator3B.c_str());
			outtextxy(100, 250, answer1A.c_str()); /*submit to desires*/
			outtextxy(100, 350, answer21.c_str()); /*run away from gf's*/

			cin >> answer;

			if (answer == 1) {
				cleardevice();
				outtextxy(50, 50, answerA1.c_str()); /*die to gf's*/
				outtextxy(50, 150, answerA12.c_str());
				Sleep(5000);
				cleardevice();
				for (int i = 0; i < 25; i++) {
					setfillstyle(1, 14);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					setfillstyle(1, 3);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 4);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 2);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 1);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 5);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
				}
				system("pause");
			}

			else if (answer == 2) {
				cleardevice();
				outtextxy(50, 50, answerB1.c_str()); /*escape gf's*/
				cleardevice();
				outtextxy(50, 50, narrator5.c_str()); /*see dat boi's shadow*/
				outtextxy(50, 150, answer4.c_str()); /*oh shit waddup*/
				outtextxy(50, 250, answer5.c_str()); /*fight dat boi*/

				cin >> answer;

				if (answer == 1) {
					cleardevice();
					outtextxy(100, 50, answer6.c_str());
					outtextxy(100, 150, answer6B.c_str());
					Sleep(4000);
					cleardevice();
					outtextxy(50, 50, narrator6.c_str()); /*goes to billy mays*/
					outtextxy(100, 150, answer8.c_str()); /*are you my dad*/
					outtextxy(100, 250, answer9.c_str()); /*ask where blue eyes white dragon is*/

					cin >> answer;

					if (answer == 1) {
						cleardevice();
						outtextxy(50, 50, narrator7.c_str()); /**/
						outtextxy(50, 150, narrator7B.c_str());
						outtextxy(50, 250, narrator7C.c_str());
						outtextxy(50, 350, narrator7D.c_str());
						outtextxy(50, 450, narrator7E.c_str());
						outtextxy(100, 550, answer10.c_str());/**/
						outtextxy(100, 650, answer11.c_str()); /**/

						cin >> answer;

						if (answer == 1) {
							cleardevice();
							outtextxy(50, 50, narrator10.c_str()); /*Get card*/
							outtextxy(50, 150, narrator10B.c_str());
							Sleep(5000);
							cleardevice();
							outtextxy(50, 50, narrator12.c_str()); /*Choice to drink either bleach or oxyclean after getting the card back*/
							outtextxy(50, 150, narrator12B.c_str());
							outtextxy(50, 250, narrator12C.c_str());
							outtextxy(50, 350, narrator12D.c_str());
							outtextxy(100, 450, answer12.c_str()); /*bleach*/
							outtextxy(100, 550, answer13.c_str()); /*Oxyclean*/

							cin >> answer;

							if (answer == 1) {
								cleardevice();
								outtextxy(50, 50, narrator13.c_str()); /*Drink bleach and win*/
								outtextxy(50, 150, narrator13B.c_str());
								//win screen
								Sleep(5000);
								cleardevice();
								setfillstyle(1, 7);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, win.c_str());

								system("pause");
							}

							else if (answer == 2) {
								cleardevice();
								outtextxy(50, 50, narrator14.c_str()); /*Drink oxyclean and die*/
								outtextxy(50, 150, narrator14B.c_str());
								Sleep(5000);
								cleardevice();
								for (int i = 0; i < 25; i++) {
									setfillstyle(1, 14);
									bar(0, 0, 1920, 1080);
									outtextxy(750, 540, rekt.c_str());
									Sleep(100);
									setfillstyle(1, 3);
									bar(0, 0, 1920, 1080);
									outtextxy(750, 540, rekt.c_str());
									Sleep(100);
									cleardevice();
									setfillstyle(1, 4);
									bar(0, 0, 1920, 1080);
									outtextxy(750, 540, rekt.c_str());
									Sleep(100);
									cleardevice();
									setfillstyle(1, 2);
									bar(0, 0, 1920, 1080);
									outtextxy(750, 540, rekt.c_str());
									Sleep(100);
									cleardevice();
									setfillstyle(1, 1);
									bar(0, 0, 1920, 1080);
									outtextxy(750, 540, rekt.c_str());
									Sleep(100);
									cleardevice();
									setfillstyle(1, 5);
									bar(0, 0, 1920, 1080);
									outtextxy(750, 540, rekt.c_str());
									Sleep(100);
									cleardevice();
								}
								system("pause");
							}
						}

						else if (answer == 2) {
							cleardevice();
							outtextxy(50, 50, narrator11.c_str()); /*csgo cases and kicked from session*/
							outtextxy(50, 150, narrator11B.c_str());
							outtextxy(50, 250, narrator11C.c_str());
							Sleep(5000);
							cleardevice();
							for (int i = 0; i < 25; i++) {
								setfillstyle(1, 14);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, rekt.c_str());
								Sleep(100);
								setfillstyle(1, 3);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, rekt.c_str());
								Sleep(100);
								cleardevice();
								setfillstyle(1, 4);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, rekt.c_str());
								Sleep(100);
								cleardevice();
								setfillstyle(1, 2);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, rekt.c_str());
								Sleep(100);
								cleardevice();
								setfillstyle(1, 1);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, rekt.c_str());
								Sleep(100);
								cleardevice();
								setfillstyle(1, 5);
								bar(0, 0, 1920, 1080);
								outtextxy(750, 540, rekt.c_str());
								Sleep(100);
								cleardevice();
							}
							system("pause");
						}
					}

					else if (answer == 2) {
						cleardevice();
						outtextxy(50, 50, narrator8.c_str()); /*Dat boi smites you*/
						outtextxy(50, 150, narrator8B.c_str());
						Sleep(5000);
						cleardevice();
						for (int i = 0; i < 25; i++) {
							setfillstyle(1, 14);
							bar(0, 0, 1920, 1080);
							outtextxy(750, 540, rekt.c_str());
							Sleep(100);
							setfillstyle(1, 3);
							bar(0, 0, 1920, 1080);
							outtextxy(750, 540, rekt.c_str());
							Sleep(100);
							cleardevice();
							setfillstyle(1, 4);
							bar(0, 0, 1920, 1080);
							outtextxy(750, 540, rekt.c_str());
							Sleep(100);
							cleardevice();
							setfillstyle(1, 2);
							bar(0, 0, 1920, 1080);
							outtextxy(750, 540, rekt.c_str());
							Sleep(100);
							cleardevice();
							setfillstyle(1, 1);
							bar(0, 0, 1920, 1080);
							outtextxy(750, 540, rekt.c_str());
							Sleep(100);
							cleardevice();
							setfillstyle(1, 5);
							bar(0, 0, 1920, 1080);
							outtextxy(750, 540, rekt.c_str());
							Sleep(100);
							cleardevice();
						}
						system("pause");
					}
				}
			}
		}

		else if (answer == 3) {
			cleardevice();
			outtextxy(50, 150, hey.c_str());
			Sleep(100);
			outtextxy(50, 250, aids.c_str());
			outtextxy(100, 350, aidsanswer1.c_str());
			outtextxy(100, 450, aidsanswer2.c_str());

			cin >> answer;

			if (answer == 1) {
				cleardevice();
				outtextxy(50, 150, ball.c_str());
				outtextxy(50, 250, ball2.c_str());
				outtextxy(50, 350, ball3.c_str());
				outtextxy(50, 450, ball4.c_str());
				outtextxy(50, 550, ball5.c_str());
				outtextxy(50, 650, ball6.c_str());
				Sleep(15000);
				cleardevice();
				for (int i = 0; i < 25; i++) {
					setfillstyle(1, 14);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					setfillstyle(1, 3);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 4);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 2);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 1);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
					setfillstyle(1, 5);
					bar(0, 0, 1920, 1080);
					outtextxy(750, 540, rekt.c_str());
					Sleep(100);
					cleardevice();
				}
				system("pause");
			}

			else if (answer == 2) {
				cleardevice();
				outtextxy(50, 150, meme.c_str());
				outtextxy(50, 250, meme2.c_str());
				outtextxy(50, 350, meme3.c_str());
				outtextxy(50, 450, meme4.c_str());
				outtextxy(50, 550, meme5.c_str());
				outtextxy(50, 650, meme6.c_str());
				outtextxy(50, 750, meme7.c_str());
				outtextxy(50, 850, meme8.c_str());
			}
		}

		else if (answer == 2) {
			cleardevice();
			settextstyle(3, 0, 4);
			outtextxy(50, 50, narrator4.c_str());/*Billy mays death*/
			outtextxy(50, 150, narrator4B.c_str());
			outtextxy(50, 250, narrator4C.c_str());
			Sleep(8000);
			cleardevice();
			for (int i = 0; i < 25; i++) {
				setfillstyle(1, 14);
				bar(0, 0, 1920, 1080);
				outtextxy(750, 540, rekt.c_str());
				Sleep(100);
				setfillstyle(1, 3);
				bar(0, 0, 1920, 1080);
				outtextxy(750, 540, rekt.c_str());
				Sleep(100);
				cleardevice();
				setfillstyle(1, 4);
				bar(0, 0, 1920, 1080);
				outtextxy(750, 540, rekt.c_str());
				Sleep(100);
				cleardevice();
				setfillstyle(1, 2);
				bar(0, 0, 1920, 1080);
				outtextxy(750, 540, rekt.c_str());
				Sleep(100);
				cleardevice();
				setfillstyle(1, 1);
				bar(0, 0, 1920, 1080);
				outtextxy(750, 540, rekt.c_str());
				Sleep(100);
				cleardevice();
				setfillstyle(1, 5);
				bar(0, 0, 1920, 1080);
				outtextxy(750, 540, rekt.c_str());
				Sleep(100);
				cleardevice();
			}
			playSound(suck, 21000);
			Sleep(50);
			//play sad airhorn and you died screen
		}

		system("pause");
	}
}
}

void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode) {
	GrDriver = VGA; 
	GrMode = VGAMAX;
	initgraph(&GrDriver, &GrMode, "");				  
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{	cout << "Error:" << ErrorCode;}
}
int setMyColor(int color, int rectColor) {
	int val;
	do { val = rand() % 16; } while (val == color || val == rectColor);
	return val;
}

void Background()
{
	
	bool game = false;
	while (running) {
		/*while (Dankscape != end) {
			playsoundSFX(backgroundmusic, );
			game = true;*/
		}
		}


void playSound(string fileName, int duration) {
	if (fileName.substr(fileName.length() - 2) == "v") {
		PlaySound(TEXT(fileName.c_str()), NULL, SND_ASYNC);
		Sleep(duration);
		PlaySound(TEXT(fileName.c_str()), 0, 0);
		return;
	}
	string concat = "open " + fileName + " type mpegvideo alias MP3_Device";
	LPCSTR a = concat.c_str();
	mciSendString(a, NULL, 0, 0);

	mciSendString("play MP3_Device", NULL, 0, 0);
	Sleep(duration);
	mciSendString("stop MP3_Device", NULL, 0, 0);
	mciSendString("close MP3_Device", NULL, 0, 0);
}
