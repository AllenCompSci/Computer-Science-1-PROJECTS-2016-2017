/*
Guan Chen
Pranav Ambadasugari
Maicen Fontenot
Zayn Dharamsi
Comp Sci 1 Pre-Ap
Period 1
*/

#include <iostream>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
#include <Windows.h> // Sleep()
#include <ctime>
#include <chrono>
#include <thread>
#include <mmsystem.h> /// WAV
#include <mciapi.h> /// MP3
#pragma comment(lib, "winmm.lib") /// WAV also maybe MP3


using namespace std;

void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
int GrDriver, GrMode, ErrorCode;
int maxX, maxY, penColor; // max X and Y as well as penColor

class player
{
public:
	string name;
	int strength;
	int luck;
	int stealth;
	bool death;

	void make(string, int, int, int, bool);

};
void player::make(std::string nam, int str, int luk, int stl, bool dead)
{
	name = nam;
	strength = str;
	luck = luk;
	stealth = stl;
	death = dead;
}
player user;

static void char_build(string a, string b)
{
	int y = 1;
	string c;
	string d;
	int fq;
	string t_name;
	int t_str;
	int t_luck;
	int t_stl;
	double l = 0;
	if (a == "a")c = "twenty five";
	if (a == "t")c = "twenty";

	if (a == "a")fq = 25;
	if (a == "t")fq = 20;



	do {
		cout << "allocate" << d << "to your character skill points... they will be effective within your choices based on what what you choose" << endl;
		cout << "strength, luck, stealth, and death" << endl;
		cout << "strength" << endl;
		cin >> t_str;
		cout << "stealth" << endl;
		cin >> t_stl;
		cout << "luck" << endl;
		cin >> t_luck;
		cout << "" << endl;
		if (t_str + t_luck + t_stl > fq)
		{
			cout << "you are over the point allocation limit..." + d + "points" << endl;
			l = 1;
		}
		else { l = 0; }

	} while (l == 1);
	y++;
}
static void dogssemble()
{
	string t_name;
	cout << "you won't be going through life alone..." << endl;

	cout << "You will have a dog" << endl;
	cout << "What do you wanna name your dog!" << endl;
	cin >> t_name;



	Sleep(1000);

}
static void user_build()
{
	settextstyle(1, 4, 8);
	string temp_name;
	int t_str;

	int t_luk;
	int t_stl;
	bool q = 0;

	std::cout << "enter your first name:" << endl;
	std::cin >> temp_name;

	do
	{

		cout << "Give yourself twenty skill points to these 3 stats. these will serve as your main player's stats." << endl;
		cout << "strength, luck, stealth" << endl;
		cout << "strength:";
		cin >> t_str;

		cout << "luck:";
		cin >> t_luk;
		cout << "stealth:";
		cin >> t_stl;
		cout << " " << endl;

		if (t_str + t_luk + t_stl > 20)
		{
			std::cout << "You've given yourself over 20 skill points" << endl;
			q = 1;
		}

		else
		{
			q = 0;
		}

		user.make(temp_name, t_str, t_luk, t_stl, true);

	} while (q == 1);
}
static bool pcathbegin()
{
	int rand1 = rand() % 1 + 1;
	int Y;
	int N;
	string rand_name;
	settextstyle(1, 0, 4);
	cout << "Welcome to the CODING DEAD..." << endl;

	cout << "Are you ready to start...?" << endl;

	cleardevice();
	outtextxy(50, 500, ("This is a journey that will be decided by your choices"));
	Sleep(2000);
	cleardevice();
	outtextxy(50, 500, ("THE CODING DEAD."));
	Sleep(2000);
	cleardevice();
	outtextxy(50, 500, ("Please refer to the console for character input"));
	Sleep(2000);
	cleardevice();
	return true;
}
static bool graphica()

{
	settextstyle(1, 0, 4);
	cleardevice();
	outtextxy(50, 500, ("Thank You..."));
	system("pause");
	cleardevice();
	outtextxy(50, 500, ("Please, sit back and relax..."));
	system("pause");
	cleardevice();
	outtextxy(50, 500, ("COMP SCI 1 PRESENTS..."));
	system("pause");
	cleardevice();outtextxy(50, 500, ("THE CODING DEAD"));
	system("pause");
	cleardevice();
	return true;
}

static bool storym() {
	char a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v;
	settextstyle(1, 0, 4);
	outtextxy(50, 600, ("You need to wake up..."));
	Sleep(2000);
	cleardevice();
	outtextxy(50, 600, ("It's like 6 o clock..."));
	Sleep(2000);
	cleardevice();
	outtextxy(50, 600, ("You have a lotta things to do..."));
	Sleep(2000);
	cleardevice();
	outtextxy(50, 200, ("Do you want to 1.wake up or 2.snooze?"));
	outtextxy(50, 300, ("Refer to the console for input..."));
	system("pause");
	cin >> a;
	//Initial Storyline************************************************************************************************************************
	switch (a) {
		int t_str;

	case '1'://Storyline1*************************************************************************************************************************
		outtextxy(50, 400, ("You wake up!"));

		t_str = 2;
		outtextxy(50, 500, ("(-_-)"));
		system("pause");
		cleardevice();
		outtextxy(50, 100, ("You notice your wife is missing,"));
		system("pause");
		outtextxy(50, 200, ("but ever since her car accident leading to her death"));
		system("pause");
		outtextxy(50, 300, ("she has seemed a bit off."));
		system("pause");
		outtextxy(50, 400, ("You ponder if using the serum you created was the right choice,"));
		system("pause");
		outtextxy(50, 500, ("which brought her back to life… but at what cost?"));
		system("pause");
		outtextxy(50, 600, ("She mysteriously disappears some days, and doesn’t seem herself anymore."));
		system("pause");
		outtextxy(50, 700, ("It is to be expected that she is different, "));
		system("pause");
		outtextxy(50, 800, ("after all, she did come back from the dead, you reassure yourself."));
		system("pause");
		outtextxy(50, 900, ("You shake off the feelings of uneasiness and remind yourself that everything is ok"));
		system("pause");
		cleardevice();
		outtextxy(50, 100, ("Maybe she just went to work early ?"));
		outtextxy(50, 200, ("Press any key to continue..."));
		system("pause");
		cleardevice();
		outtextxy(100, 100, ("You wake up and go to the bathroom…"));
		outtextxy(100, 200, ("Do you wanna 1. Brush your teeth, or 2. Take a crap?"));
		cin >> b;
		cleardevice();
		outtextxy(100, 100, ("Once done you go down stairs..."));
		outtextxy(100, 500, ("1.Eat Breakfast"));
		outtextxy(100, 600, ("2.Take a walk"));
		cin >> b;
		cleardevice();
		switch (b) {
		case '1'://Storyline1 Cont...************************************************************************************************************************
			outtextxy(100, 100, ("You also notice that your dog has not been fed"));
			system("pause");
			outtextxy(100, 200, ("The house is a mess"));
			system("pause");
			outtextxy(100, 300, ("A note from your wife lay on the table"));
			system("pause");
			outtextxy(100, 400, ("Hey honey, it’s bee season again, I’m going to get you meds!"));
			system("pause");
			outtextxy(100, 500, ("I’ll see you later bye!! XOXO - (Wife)."));
			system("pause");
			outtextxy(100, 600, ("The dog barks at you angrily!"));
			system("pause");
			outtextxy(100, 700, ("1.Feed the dog and clean up house"));
			outtextxy(100, 750, ("2.Take a nap and and feed dog later. "));
			system("pause");
			cin >> c;
			cleardevice();

			switch (c) {
			case '1'://Storyline 1 Cont...************************************************************************************************************************
				outtextxy(100, 100, ("The dog barks at you and sits next to the door. He wants to go out for a walk."));
				system("pause");
				outtextxy(100, 200, ("You can take the red leash(1) or green leash(2)"));
				system("pause");
				cin >> d;
				outtextxy(100, 300, ("Something feels off while you're on the walk."));
				system("pause");
				outtextxy(100, 400, ("The sun shines brightly and the birds chirp on the oak trees..."));
				system("pause");
				outtextxy(100, 500, ("but in the far east, a mass of gray clouds seem to begin to materialize"));
				system("pause");
				outtextxy(100, 600, ("A wild scream emits from nearby."));
				system("pause");
				outtextxy(100, 700, ("Go investigate(1) or Return Home and pretend that the world is fine(2)"));
				system("pause");
				cin >> d;
				cleardevice();
				outtextxy(100, 100, ("You suddenly hear another scream...closer this time"));
				system("pause");
				outtextxy(100, 200, ("You turn the corner and encounter a scene of complete mayhem"));
				system("pause");
				outtextxy(100, 300, ("The local WaLLmart had been completely wrecked"));
				system("pause");
				outtextxy(100, 400, ("Cars were crushed and glass littered the floor..."));
				system("pause");
				outtextxy(100, 500, ("Blood decorated the parking lot, yet not a single body was seen"));
				system("pause");
				outtextxy(100, 600, ("You remember that your wife was getting medicine..."));
				system("pause");
				outtextxy(100, 700, ("WaLLmart had the closest pharmacy..."));
				system("pause");
				outtextxy(100, 700, ("You can go in to search for your wife(1) or look around the parking lot(2)"));
				system("pause");
				cin >> d;
				cleardevice();

				switch (d) {
				case '1'://Going Inside
					outtextxy(100, 100, ("You walk in through the front door...it is eerily empty and silent…"));
					system("pause");
					outtextxy(100, 200, ("You find the pharmacy in disorder.Papers and medicine littered the ground…"));
					system("pause");
					outtextxy(100, 300, ("You slip on the mess as you attempted to make your way through..."));
					system("pause");
					outtextxy(100, 400, ("Suddenly, wild screams come from one of the office doors..."));
					system("pause");
					outtextxy(100, 500, ("Your dog barks unconvincingly…"));
					system("pause");
					outtextxy(100, 600, ("The door spontaneously gets knocked off the hinges in a colossal crash."));
					system("pause");
					outtextxy(100, 700, ("You dog leaps at the unseen figure that advances towards you…"));
					system("pause");
					outtextxy(100, 800, ("You grab supplies and run...you look back to see your dog rip apart"));
					system("pause");
					cleardevice();
					outtextxy(100, 100, ("You decide to leave immediately and sprint for the front doors."));
					Sleep(2000);
					outtextxy(100, 200, ("You reach the doors...and meet an army of the dead."));
					Sleep(2000);
					outtextxy(100, 300, ("They dash towards the doors, but the lights flicker and the doors lock."));
					Sleep(2000);
					outtextxy(100, 400, ("You slowly back away feeling both terrified and relieved..."));
					Sleep(2000);
					outtextxy(100, 500, ("Footsteps echo behind you...you turn to see your wife..."));
					Sleep(2000);
					outtextxy(100, 600, ("Shocked by the chaos around you, you stand in awe"));
					Sleep(2000);
					outtextxy(100, 700, ("She walks up to you and in a single moment..."));
					Sleep(2000);
					outtextxy(100, 800, ("She bites your neck and you die. GAME OVER!"));
					cleardevice();
					system("pause");
					break;

				case '2'://Death
					outtextxy(100, 100, ("You find a cool hat and a Readbull"));
					system("pause");
					outtextxy(100, 200, ("There's nothing else to do so you go inside."));
					system("pause");
					outtextxy(100, 300, ("You walk in through the front door...it is eerily empty and silent…"));
					system("pause");
					outtextxy(100, 400, ("The lights flicker wildly"));
					system("pause");
					outtextxy(100, 500, ("You find the pharmacy in disorder.P;apers and medicine littered the ground…"));
					system("pause");
					outtextxy(100, 600, ("You slip on the mess as you attempted to make your way through..."));
					system("pause");
					cleardevice();
					outtextxy(100, 100, ("You grab medicine and supplies that could be useful later..."));
					system("pause");
					outtextxy(100, 200, ("Your dog suddenly whines...you turn to see your wife"));
					system("pause");
					outtextxy(100, 300, ("Your dog lies dead in a pool of blood..."));
					system("pause");
					outtextxy(100, 400, ("Your wife's eyes are wild and a blanket of trash masks her."));
					system("pause");
					outtextxy(100, 500, ("Fight Her(1) or Ask her how she feels(2)"));
					system("pause");
					cleardevice();
					cin >> e;
					break;
					switch (e) {
					case '1':
						outtextxy(100, 100, ("You grab a pen and stab her...but it has no effect."));
						Sleep(2000);
						outtextxy(100, 200, ("The next thing you know, you lie in a pool of blood..."));
						Sleep(2000);
						outtextxy(100, 300, ("Your wife's face gets closer to yours..."));
						Sleep(2000);
						outtextxy(100, 400, ("She eats you and you die an agonizing death. GAME OVER!"));
						cleardevice();
						system("pause");
						break;
					case'2':
						outtextxy(100, 100, ("She does not seem to understand english and screams..."));
						Sleep(2000);
						outtextxy(100, 200, ("She lunges and knocks you down."));
						Sleep(2000);
						outtextxy(100, 300, ("You kick her away but she grabs your foot and bites"));
						Sleep(2000);
						outtextxy(100, 400, ("You yell and attempt to shove her away but it has no effect."));
						Sleep(2000);
						outtextxy(100, 500, ("She bites your neck and your body goes limp. GAME OVER!"));
						cleardevice();
						system("pause");
						break;
					}
				}
			}
		}

		break;
	case '2'://Storyline2************************************************************************************************************************
		cleardevice();
		outtextxy(100, 100, ("You snooze... you lose."));
		system("pause");
		outtextxy(100, 200, ("You notice your wife is missing,"));
		system("pause");
		outtextxy(100, 300, ("but ever since her car accident leading to her death"));
		system("pause");
		outtextxy(100, 400, ("she has seemed a bit off."));
		system("pause");
		outtextxy(100, 500, ("You ponder if using the serum you created was the right choice,"));
		system("pause");
		outtextxy(100, 600, ("which brought her back to life… but at what cost?"));
		system("pause");
		outtextxy(100, 700, ("She mysteriously disappears some days, and doesn’t seem herself anymore."));
		system("pause");
		outtextxy(100, 800, ("But...it’s to be expected that she is different, "));
		system("pause");
		cleardevice();
		outtextxy(100, 100, ("after all, she did come back from the dead, you reassure yourself."));
		system("pause");
		outtextxy(100, 200, ("You shake off the feelings of uneasiness and remind yourself that everything is ok"));
		system("pause");
		outtextxy(100, 300, ("Maybe she just went to work early…?"));
		system("pause");
		cleardevice();
		outtextxy(100, 100, ("You wake up and go to the bathroom…"));
		outtextxy(100, 200, ("Do you wanna 1. Brush your teeth, or 2. Take a crap?"));
		cin >> b;
		cleardevice();
		outtextxy(100, 100, ("Once done you go down stairs..."));
		outtextxy(100, 200, ("(1)Eat Breakfast "));
		cin >> b;
		cleardevice();
		switch (b) {
		case '1':
			outtextxy(100, 100, ("(1)Ramen or (2)Donuts"));
			system("pause");
			cin >> c;
			outtextxy(100, 200, ("While the food cools, you notice the house is a mess"));
			system("pause");
			outtextxy(100, 300, ("You find a note on the fridge"));
			system("pause");
			outtextxy(100, 400, ("Bee season - out for some meds"));
			system("pause");
			outtextxy(100, 500, ("Hopefully it won’t be as bad as last year!"));
			system("pause");
			outtextxy(100, 600, ("I’ll see you later bye!! XOXO - (Wife).”"));
			system("pause");
			outtextxy(100, 700, ("You finish breakfast and your dog barks at you for a morning walk"));
			cleardevice();
			outtextxy(100, 100, ("You decide to go on a new route today with your dog"));
			system("pause");
			outtextxy(100, 200, ("It leads to a dead end so you’ll have to return through the same way"));
			system("pause");
			outtextxy(100, 300, ("But the scenery is nice. You notice clouds forming in the distance..."));
			system("pause");
			outtextxy(100, 400, ("(1)Cross the bridge or (2)Go Home"));
			system("pause");
			cin >> c;
			outtextxy(100, 500, ("Your dog dashes across the bridge without warning and you follow"));
			system("pause");
			outtextxy(100, 600, ("You reach the end of the trail and encounter the forest"));
			system("pause");
			cleardevice();//Dog Dies
			outtextxy(100, 100, ("Your dog still wants to explore and you follow him inside"));
			system("pause");
			outtextxy(100, 200, ("The clouds are directly above you now..."));
			system("pause");
			outtextxy(100, 300, ("The forest becomes darker as you go in further"));
			system("pause");
			outtextxy(100, 400, ("You seem to hear bushes rustle near you"));
			system("pause");
			outtextxy(100, 500, ("(1)Abandon your dog or (2)Keep going"));
			system("pause");
			cin >> c;
			outtextxy(100, 600, ("A disfigured humanoid entity leaps at you from your left..."));
			system("pause");
			cleardevice();
			outtextxy(100, 100, ("You get knocked down, but you kick it into a tree."));
			system("pause");
			outtextxy(100, 200, ("It's so dark in the forest, you can barely make out its silhouette."));
			system("pause");
			outtextxy(100, 300, ("(1)Try talking or (2)Grab a stick"));
			system("pause");
			cin >> c;
			outtextxy(100, 400, ("The figure seems to be intent on killing you and screams wildly..."));
			system("pause");
			outtextxy(100, 500, ("It lunges at you, but your dog suddenly attacks its flank"));
			system("pause");
			outtextxy(100, 600, ("You feel blood smear across your face, but it appears to have no effect."));
			system("pause");
			outtextxy(100, 700, ("The entity howls angrily and slams your dog into a tree"));
			system("pause");
			outtextxy(100, 800, ("Your dog lies inanimate and the entity focuses on you"));
			system("pause");
			cleardevice();
			outtextxy(100, 100, ("(1)Run or (2)RUNNN"));
			system("pause");
			cin >> c;
			outtextxy(100, 200, ("You dash towards the river."));
			system("pause");
			outtextxy(100, 300, ("The current appears to be strong...but you might make it"));
			system("pause");
			outtextxy(100, 400, ("The entity chases after you...you must decide quickly"));
			system("pause");
			outtextxy(100, 500, ("(1)Cross the river"));
			system("pause");
			cleardevice();
			cin >> c;
			switch (c) {
			case '1':
				outtextxy(100, 100, ("You almost drown under the current and get hit by a log..."));
				system("pause");
				outtextxy(100, 200, ("...but you manage to cross the river"));
				system("pause");
				outtextxy(100, 300, ("For the first time, you get a glimpse at the entity...the monster"));
				system("pause");
				outtextxy(100, 400, ("Its skin appears to be decaying, and its eyes sunken..."));
				system("pause");
				outtextxy(100, 500, ("Long fingernails protrude from its hands and its face bares red sharp teeth..."));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("Miraculously, it appears unable to cross the river and retreats in the opposite direction."));
				system("pause");
				outtextxy(100, 200, ("You have no time to waste, the monster could be anywhere..."));
				system("pause");
				outtextxy(100, 300, ("(1)Return the way you came or (2)Explore"));
				system("pause");
				cin >> d;
				outtextxy(100, 400, ("Exhaustion and rain make navigating the terrain difficult"));
				system("pause");
				outtextxy(100, 500, ("But eventually, you make your way back to the bridge"));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("Suddenly, lightning strikes down a tree..."));
				system("pause");
				outtextxy(100, 200, ("It smashes onto the bridge and causes a complete collapse"));
				system("pause");
				outtextxy(100, 300, ("The impact of the falling debris shake the entire area..."));
				system("pause");
				outtextxy(100, 400, ("Desperate to escape, you can..."));
				system("pause");
				outtextxy(100, 500, ("(1)Grab a log and float it across or (2)Swim across the river"));
				system("pause");
				cin >> d;
				switch (d) {
				case '1':
					cleardevice();
					outtextxy(100, 100, ("You turn around and see...your dog..."));
					system("pause");
					outtextxy(100, 200, ("It has a massive wound on its flank and legs...."));
					system("pause");
					outtextxy(100, 300, ("It limps towards you when it shouldn’t be able to move at all..."));
					system("pause");
					outtextxy(100, 400, ("It growls angrily as it approaches slowly..."));
					system("pause");
					outtextxy(100, 500, ("(1)Kill it or (2)Do nothing"));
					system("pause");
					cin >> e;
					cleardevice();
					outtextxy(100, 100, ("Your dog whines and collapses..."));
					system("pause");
					outtextxy(100, 200, ("Suddenly, something darts from the right and knocks you down..."));
					system("pause");
					outtextxy(100, 300, ("You recognize the monster’s face right before it bites into your left arm"));
					system("pause");
					outtextxy(100, 400, ("(1)Pick up a stick or (2)Grab a stone"));
					system("pause");
					outtextxy(100, 500, ("Before it gets an opportunity to bite again, you kill it with a blow to the head"));
					system("pause");
					cleardevice();
					outtextxy(100, 100, ("You lie on the ground stricken with pain..."));
					Sleep(2000);
					outtextxy(100, 200, ("The injuries are too great...the loss of your beloved pet was too much."));
					Sleep(2000);
					outtextxy(100, 300, ("You feel dizzy from blood loss."));
					Sleep(2000);
					outtextxy(100, 400, ("Soon you forget everything...all you know now...is a desire to eat..."));
					Sleep(2000);
					outtextxy(100, 500, ("GAME OVER!"));
					Sleep(2000);
					break;

				case '2':
					cleardevice();
					outtextxy(100, 100, ("You dive into the cold waters"));
					Sleep(2000);
					outtextxy(100, 200, ("You make it halfway, but the current becomes noticeably stronger…."));
					Sleep(2000);
					outtextxy(100, 300, ("(1)Keep going or (2)Swim back"));
					Sleep(2000);
					outtextxy(100, 400, ("The current overwhelms you and you go under"));
					Sleep(2000);
					outtextxy(100, 500, ("GAME OVER!!!"));
					Sleep(2000);
					break;
				}
		

			case'2':
				outtextxy(100, 100, ("You remember that you forgot vital files at the office last night."));
				system("pause");
				outtextxy(100, 200, ("Luckily, the company building is only a 20minute walk from your house."));
				system("pause");
				outtextxy(100, 300, ("Your dog is eager to walk and doesn’t mind taking a new route."));
				system("pause");
				outtextxy(100, 400, ("You live in a city called ComSciVille"));
				system("pause");
				outtextxy(100, 500, ("The population isn’t too big, but it is still a decent number of people living together in a close proximity."));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("ComSciVille is a beautiful city capable of self - sufficiency"));
				system("pause");
				outtextxy(100, 200, ("Organic farms grow the population"));
				system("pause");
				outtextxy(100, 300, ("And renewable energy power the entire city indefinitely"));
				system("pause");
				outtextxy(100, 400, ("On the way to your company, you see parks and fountains."));
				system("pause");
				outtextxy(100, 500, ("Today, however, something feels very wrong"));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("The sun shines beautifully, yet not a single person can be seen"));
				system("pause");
				outtextxy(100, 200, ("It’s 11:00 now, well past waking hours..."));
				system("pause");
				outtextxy(100, 300, ("You suddenly hear screams from the local supermarket"));
				system("pause");
				outtextxy(100, 400, ("The supermarket doors are abruptly knocked off their hinges"));
				system("pause");
				outtextxy(100, 500, ("And a horde of people and...chaos? spill forth from the doors"));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("(1)Run or (2)Get the *ell out"));
				system("pause");
				cin >> f;
				outtextxy(100, 200, ("You and your frightened dog make a mad dash to the company"));
				system("pause");
				outtextxy(100, 300, ("You hear yells and screams behind you…."));
				system("pause");
				outtextxy(100, 400, ("People are eati-...wait no...zombies infecting people."));
				system("pause");
				outtextxy(100, 500, ("It can only be one thing….."));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("The serum used on your wife must’ve somehow diffused among the population..."));
				system("pause");
				outtextxy(100, 200, ("Which meant that your wife...oh no..."));
				system("pause");
				outtextxy(100, 300, ("You sprint towards the office, but your dog gets knocked down by a fleeing person."));
				system("pause");
				outtextxy(100, 400, ("(1)Kill him or (2)Grab your dog"));
				system("pause");
				cin >> f;
				outtextxy(100, 500, ("A zombie leaps past you onto him and you rescue your dog"));
				system("pause");
				cleardevice();
				outtextxy(100, 100, ("There it is, the company building piercing the sky amidst the mayhem."));
				system("pause");
				outtextxy(100, 200, ("It’s reflective exterior walls appear to attract the undead..."));
				system("pause");
				outtextxy(100, 300, ("You make a mad dash for the doors..."));
				system("pause");
				outtextxy(100, 400, ("You and your dog barely manage to get in...but not without letting a zombie in"));
				system("pause");
				outtextxy(100, 500, ("(1)Bonk it on the head or (2)Grab a pen and stab it"));
				system("pause");
				cin >> f;
				cleardevice();
				outtextxy(100, 100, ("You successfully incapacitate the zombie and quickly lock the doors."));
				system("pause");
				outtextxy(100, 200, ("You can (1)Look for the serum files and begin creating a cure or..."));
				system("pause");
				outtextxy(100, 300, ("(2)Do nothing"));
				system("pause");
				cin >> f;
				switch (f) {
				case '1':
					outtextxy(100, 100, ("You go upstairs into your office."));
					system("pause");
					outtextxy(100, 200, ("Luckily, the files are just where you left them."));
					system("pause");
					outtextxy(100, 300, ("You quickly grab them and head downstairs."));
					system("pause");
					outtextxy(100, 400, ("You get your dog and enter the lab in the basement."));
					system("pause");
					outtextxy(100, 500, ("You can (1)Work on the cure or (2)Tend to your dog"));
					system("pause");
					cin >> g;
					switch (g) {
					case'1':
						outtextxy(100, 100, ("After several hours, you finish the plans for the cure."));
						system("pause");
						outtextxy(100, 200, ("You fall asleep despite your dog whining..."));
						system("pause");
						outtextxy(100, 300, ("18:00"));
						system("pause");
						outtextxy(100, 400, ("Your dog lies unmoving next to you...he must’ve died from infection."));
						system("pause");
						outtextxy(100, 500, ("You need to get supplies from the garage. You have no time to mourn."));
						system("pause");
						cleardevice();
						outtextxy(100, 100, ("You hastily open the door and start looking for materials..."));
						system("pause");
						outtextxy(100, 200, ("Snail eyes...salt...hydrochloric acid...snake skin..."));
						system("pause");
						outtextxy(100, 300, ("You hear a small scratching sound behind you"));
						system("pause");
						outtextxy(100, 400, ("(1)Turn around or (2)Keep gathering supplies"));
						system("pause");
						cin >> f;
						switch (f) {
						case'1':
							outtextxy(100, 100, ("Suddenly the power goes out..."));
							Sleep(2000);
							outtextxy(100, 200, ("It’s too dark to see anything"));
							Sleep(2000);
							outtextxy(100, 300, ("You move frantically to find a flashlight"));
							Sleep(2000);
							outtextxy(100, 400, ("You hear a deep growl... the next thing you know, you’re on the ground and pain rips into you from all directions..."));
							Sleep(2000);
							outtextxy(100, 500, ("GAME OVER!"));
							Sleep(2000);
							break;
						case'2':
							outtextxy(100, 100, ("You collect the needed materials and leave"));
							Sleep(2000);
							outtextxy(100, 200, ("You return to the basement and put down the elements"));
							Sleep(2000);
							outtextxy(100, 300, ("Suddenly an unseen force knocks you down and growls furiously"));
							Sleep(2000);
							outtextxy(100, 400, ("You turn to see your berserk undead dog tear into you..."));
							Sleep(2000);
							outtextxy(100, 500, ("GAME OVER!"));
							Sleep(2000);
							break;
						}


					case'2':
						outtextxy(100, 100, ("The world can wait...your fix up your dog."));
						system("pause");
						outtextxy(100, 200, ("You organize the plans and equipment. The materials are in the garage, you’re going to need those."));
						system("pause");
						outtextxy(100, 300, ("You go upstairs to ground level"));
						system("pause");
						outtextxy(100, 400, ("The zombie horde bangs on the doors when they see you"));
						system("pause");
						outtextxy(100, 500, ("Luckily, the doors seem to be holding"));
						system("pause");
						cleardevice();
						outtextxy(100, 100, ("You open the garage doors and turn on the lights"));
						system("pause");
						outtextxy(100, 200, ("To your relief, everything is organized and prepared"));
						system("pause");
						outtextxy(100, 300, ("You hastily grab the components and return to the lab"));
						system("pause");
						outtextxy(100, 400, ("The horde outside appears to be bigger this time and tiny cracks are visible"));
						system("pause");
						outtextxy(100, 500, ("Your time is ticking…."));
						system("pause");
						cleardevice();
						outtextxy(100, 100, ("Time to make the cure"));
						system("pause");
						outtextxy(100, 200, ("Add (1)Ginger Root or (2)Root Beer"));
						system("pause");
						cin >> h;
						outtextxy(100, 300, ("Add (1)Coke or (2)Dr. P"));
						system("pause");
						cin >> h;
						outtextxy(100, 400, ("Add (1)French Fries or (2)Tater Tots"));
						system("pause");
						cin >> h;
						outtextxy(100, 500, ("Finish with (1)Pancakes or (2)Waffles"));
						system("pause");
						cin >> h;
						cleardevice();
						break;
						switch (h) {
						case'1':
							outtextxy(100, 100, ("You add the finalizing touches to your cure"));
							Sleep(2000);
							outtextxy(100, 200, ("You step outside to the main lobby to confront the horde"));
							Sleep(2000);
							outtextxy(100, 300, ("The moment of truth...you open the door..."));
							Sleep(2000);
							outtextxy(100, 400, ("and use the cure….."));
							Sleep(2000);
							outtextxy(100, 500, ("It has no effect. You die along with the rest of the world. GAME OVER!"));
							Sleep(2000);
							break;

						case'2':
							outtextxy(100, 100, ("You add the finalizing touches to your cure"));
							Sleep(2000);
							outtextxy(100, 200, ("You exit the lab to confront the infected horde"));
							Sleep(2000);
							outtextxy(100, 300, ("Moment of truth..."));
							Sleep(2000);
							outtextxy(100, 400, ("You open the doors and release the cure"));
							Sleep(2000);
							outtextxy(100, 500, ("The people are initially incapacitated, but the cure works and you save the world. WELL DONE!"));
							Sleep(2000);
							break;

						}

						break;

					}
				case '2':
					outtextxy(100, 100, ("After ComSciVille gets completely infected, the disease spreads to the rest of the world.Everyone dies"));
					Sleep(2000);
					outtextxy(100, 200, ("GAME OVER!"));
					Sleep(2000);
					break;
				}
			}
			system("pause");
		}



		return true;
	}
	}

	void playSound(string, int)
	{
	}

	void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode){
		//set the graphics driver
		GrDriver = VGA; //800x600 by monitor
		GrMode = VGAMAX;//set graphics mode
		initgraph(&GrDriver, &GrMode, "");//start graphics
										  //check for problems
		ErrorCode = graphresult();
		if (ErrorCode != grOk)
		{
			cout << "Error:" << ErrorCode;
		}
	}

	int main(int argc, const char * argv[])
	{


		gr_Start(GrDriver, GrMode, ErrorCode);

		pcathbegin();
		user_build();
		dogssemble();
	
		PlaySound("N:\Computer Science 1\Period 1\Ambadasugari, Seshasai P\The Coding Dead\Crickets.mp3", NULL, SND_FILENAME);
		graphica();
		storym();


		system("pause");
		return 0;
	}

