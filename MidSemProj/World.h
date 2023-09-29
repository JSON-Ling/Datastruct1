#pragma once
#include "RoomIterator.cpp"
#include "Room.h"
#include "Player.h"
#include "InventoryDLLNode.h"
#include "Stack.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using std::vector;
using std::string;

//this is basically the game engine, will make or remove when necessary
//also handles text processing for player inputs

class World 
{
public:
	Room<string> listOfRooms[4];
	InventoryNode<Item>* _inventoryNodeList[5];
	Stack trackDam;
	World() {}
	~World() {}

	//functions

	//text processor, tells game what to do based on player inputs

	//puts > before user input
	void expInput()
	{
		cout << ">";
	}

	string userInput()
	{
		string word = "";

		//this ads > before input
		expInput();
		cin >> word;

		return word;
	}

	vector<string> getUserInput() //process player input 
	{
		string sentence = "";

		expInput();
		getline(cin, sentence);

		vector<string> words = split(sentence);

		return words;
	}

	vector<string> split(const string& s) //sanitize string and split it into vector
	{
		vector<string> ret;
		typedef string::size_type stringSize;
		stringSize i = 0;

		//loop throught the characters in sentence and sort them into worlds acording breaks
		while (i != s.size())
		{
			//check if there is space if is jump over it and if we are not at the end of sentence
			while (i != s.size() && isspace(s[i]))
			{
				++i;
			}
			//get the beggining of the word
			stringSize j = i;
			//if there are no spaces and we are not at the end increase j
			while (j != s.size() && !isspace(s[j]))
			{
				++j;
			}

			//if we found some nonwhite spaces put them into vector as one string
			if (i != j)
			{

				ret.push_back(s.substr(i, j - i));
				i = j;
			}
		}//stops at end of the sentence
		//return vector of strings
		return ret;

	}

	void createInventoryNodes(InventoryNode<Item>* nodelist[], Player& player)
	{
		for (int i = 0; i < 5; i++)
		{
			nodelist[i] = new InventoryNode<Item>(player.getPlayerItems(i));
		}
		for (int x = 4; x > 0; x--)
		{
			(*nodelist)[0].append(*nodelist[x]);
		}
	}

	void showInventory()
	{
		typedef InventoryNode<Item>::Node ItemNode;
		for (ItemNode* pn = _inventoryNodeList[0]; pn != &ItemNode::NIL; pn = &pn->getNext())
		{
			cout << pn->getValue().getName() << endl;
		}
	}

	void showHelp()
	{
		cout << "== Ripping and tearing for dummies ==\n" << endl;

		cout << ">> Interacting with items <<\n" << endl;

		cout << "[pickup <item name>] to take an item from a room and store it inside your inventory." << endl;
		cout << "[use <item name>] to use an item in your inventory." << endl;
		cout << "[equip <item name>] to equip an weapon that is in your inventory." << endl;
		cout << "[unequip] to unequip your currently equipped weapon." << endl;
		cout << "[remove <item name>] to remove an item from your inventory for good. If you have the item equipped, it will be removed too." << endl;
		cout << "[examine room <item name>] to inspect an item inside a room." << endl;
		cout << "[examine inventory <item name>] to inspect an item that is in your inventory.\n" << endl;

		cout << ">> Player interaction <<\n" << endl;

		cout << "[status] to have a look at your player's health, name, base damage and currently equipped item." << endl;
		cout << "[inventory] to have a look at your inventory.\n" << endl;

		cout << ">> Attacking demons <<\n" << endl;

		cout << "[attack <demon name>] to enter a fight sequence with a demon in the room." << endl;
		cout << "[attack] to fight the demon when in fight sequence with your currently equipped item. If you don't have an item equipped, you will attack with your fists instead.\n" << endl;

		cout << ">> Game <<\n" << endl;

		cout << "[exit] to quit game." << endl;
	}

	void parse(vector<string>& toprocess, RoomIterator<string>& iter, Player& player)
	{
		//looks for keywords then calls for function related to keyword
		if (toprocess.at(0) == "attack")
		{
			if ((*iter).getDemonInRoom().getName() == toprocess.at(1))
			{
				if (startFight((*iter).getDemonInRoom(), player))
				{
					iter++;
				}
			}
		}

		else if (toprocess.at(0) == "examine")
		{
			if (toprocess.at(1) == "room")
			{
				for (vector<Item>::iterator item_it = (*iter).getItemsInRoom().begin(); item_it != (*iter).getItemsInRoom().end(); item_it++)
				{
					if (toprocess.at(2) == item_it->getName())
					{
						cout << item_it->getDesc() << endl;
						getchar();
					}
				}
			}

			else if (toprocess.at(1) == "inventory")
			{
				for (int i = 0; i < 5; i++)
				{
					if (player.getPlayerItems(i).getName() == toprocess.at(2))
					{
						cout << player.getPlayerItems(i).getDesc() << endl;
						getchar();
					}
				}

			}
			
		}

		else if (toprocess.at(0) == "pickup") //remove item from room and copy it player's inventory
		{
			for (int i = 0; i < (*iter).getItemsInRoom().size(); i++)
			{
				if ((*iter).getItemsInRoom().at(i).getName() == toprocess.at(1))
				{
					if (player.addItem((*iter).getItemsInRoom().at(i)))
					{
						(*iter).removeItemFromRoom(toprocess.at(1));
						cout << "Item has been picked up and added to your inventory. Type \"Inventory\" to see it." << endl;
						getchar();
					}
					else
					{
						cout << "Your inventory is full." << endl;
						getchar();
					}
					
				}
			}
		}

		else if (toprocess.at(0) == "inventory")
		{
			system("cls");
			//do something
			showInventory();
			getchar();
		}

		else if (toprocess.at(0) == "remove")
		{
			player.removeItem(toprocess.at(1));
			getchar();
		}

		else if (toprocess.at(0) == "equip")
		{
			player.equipItem(toprocess.at(1));
			getchar();
		}

		else if (toprocess.at(0) == "unequip")
		{
			player.unequipItem();
			getchar();
		}

		else if (toprocess.at(0) == "use")
		{
			player.useItem(toprocess.at(1));
			getchar();
		}

		else if (toprocess.at(0) == "status")
		{
			system("cls");
			player.printStatus();
			getchar();
		}

		else if (toprocess.at(0) == "help")
		{
			system("cls");
			showHelp();
			getchar();
		}

		else if (toprocess.at(0) == "exit")
		{
			exit(0);
		}

		else
		{
			cout << "You have entered invalid command" << endl;
		}
		
	}

	//create the rooms
	RoomIterator<string> setupRooms()
	{
		vector<string> roomNames = { "generator room", "gore nest", "reactor outer core","waste processing" };
		//add items to room
		//create rooms
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				listOfRooms[i] = Room<string>(roomNames.at(i));
				listOfRooms[i].addItemsToRoom(createItems());
			}
			else
			{
				listOfRooms[i] = Room<string>(roomNames.at(i), &listOfRooms[i - 1]);
				listOfRooms[i].addItemsToRoom(createItems());
			}
		}

		//add demon to each room
		for (int i = 0; i < createDemons().size(); i++)
		{
			listOfRooms[i].addDemonToRoom(createDemons().at(i));
		}

		return RoomIterator<string>(&listOfRooms[3]);
	}

	//create game events

	vector<Demon> createDemons()
	{
		vector<Demon> newDemonList;
		vector<string> names = { "imp","marauder","cacodemon","zombie"};
		vector<int> health = { 10,200,50,30 };
		for (int i = 0; i < names.size() ; i++)
		{
			Demon newDemon(names.at(i), health.at(i), health.at(i) / 2);
			newDemonList.push_back(newDemon);
		}

		return newDemonList;
	}

	vector<Item> createItems()
	{
		vector<Item> newItemList;
		vector<string> itemDescList = { "[WEAPON] A double barrel shotgun with devastating damage, it looks old but demons seem to fear it", "[HEALTH] a medical syringe with a strange piece of meat in it, heals 100 health.", "[WEAPON] a big gun, if it doesn't kill them in one shot, you weren't big enough for this gun." };
		Item shotgun("supershotgun", itemDescList[0], 80, 0);
		Item stimpak("stimpak", itemDescList[1], 0, 100);
		Item bfg9000("bfg9000", itemDescList[2], 9000, 0);
		newItemList.push_back(shotgun);
		newItemList.push_back(stimpak);
		newItemList.push_back(bfg9000);

		return newItemList;
	}

	Player createPlayer()
	{
		cout << "Mars is being overrun by demons! But first, please enter your name: " << endl;
		string playerName = userInput();
		Player newPlayer(playerName,100,10);
		return newPlayer;
	}

	bool startFight(Demon& demon, Player& player)
	{
		system("cls");
		cout << "\nYou are now fighting: " << demon.getName() << endl;
		//calc health
		
		while (demon.isDead() != true)
		{
			system("cls");
			demon.printStatus();
			cout << "======" << endl;
			player.printStatus();
			/*cout << demon.getName() << " health is: " << demon.getHealth() << endl;
			cout << "Your health is: " << player.getHealth() << endl;
			cout << "Your equipped item is: " << player.getEquipped().getName() << endl;*/
			vector<string> fightSentence;
			while (fightSentence.size() == 0)
			{
				fightSentence = getUserInput();
			}
			
			if (fightSentence.at(0) == "attack") //if player initializes attack
			{
				if (player.hasEquipped()) //check if player has item equipped, use item's attack
				{
					//attack demon
					int playerDam = player.getEquipped().getDamage();
					int demonHealth = demon.getHealth();
					int demonNewHealth = demonHealth - playerDam;
					system("cls");
					cout << "You dealt " << playerDam << " damage to the " << demon.getName() << " using the " << player.getEquipped().getName() << endl;
					trackDam.push(playerDam);
					if (demonNewHealth <= 0)
					{
						cout << demon.getName() << " has been turned into a thin red paste on the floor." << endl;
						getchar();
						demon.setHealth(0);
					}
					else
					{
						cout << demon.getName() << "'s health is now " << demonNewHealth << endl;
						demon.setHealth(demonNewHealth);
						
						player.receiveDamage(demon.getBaseDamage()); //after attack demon, player will receive damage
						cout << "You were dealt " << demon.getBaseDamage() << " damage by the demon!" << endl;
						cout << "Your health is now: " << player.getHealth() << endl;
						getchar();
						if (player.isDead())
						{
							system("cls");
							cout << "You are dead. Not big suprise. Should've equipped the BFG, buddy." << endl;
							exit(0);
						}
					}
					
				}
				else //use player's base damage
				{
					int playerBaseDam = player.getBaseDamage();
					int demonHealth = demon.getHealth();
					int demonNewHealth = demonHealth - playerBaseDam;
					system("cls");
					cout << "You dealt " << playerBaseDam << " damage to the " << demon.getName() << " using your fists!" << endl;
					trackDam.push(playerBaseDam);
					if (demonNewHealth <= 0)
					{
						cout << demon.getName() << " has been turned into a thin red paste on the floor." << endl;
						getchar();
						demon.setHealth(0);
					}
					else
					{
						cout << demon.getName() << "'s health is now " << demonNewHealth << endl;
						demon.setHealth(demonNewHealth);
						
						player.receiveDamage(demon.getBaseDamage()); //after attack demon, player will receive damage 
						cout << "You were dealt " << demon.getBaseDamage() << " damage by the demon!" << endl;
						cout << "Your health is now: " << player.getHealth() << endl;
						getchar();

						if (player.isDead())
						{
							system("cls");
							cout << "You are dead. Not big suprise. Should've equipped the BFG, buddy." << endl;
							exit(0);
						}
					}
					
				}
			}
			else
			{
				cout << "You must enter \"Attack\" and kill the demon to exit " << endl;
				getchar();
			}
		}
		system("cls");
		cout << "You have killed the demon in the room!" << endl;
		getchar();
		
		return true;
	}

	void startGame()
	{
		RoomIterator<string> iter = setupRooms();
		
		Player currPlayer = createPlayer();
		
		while (iter != iter.end())
		{
			system("cls");
			createInventoryNodes(_inventoryNodeList, currPlayer);
			//display current room stats
			cout << "Type [help] to see available commands" << endl;
			cout << "You are in Room: " << (*iter)._roomName << endl;
			cout << "Demons in the room are: " << (*iter).getDemonInRoom().getName() << endl;
			
			cout << "Items in the room are: " << endl;
			if ((*iter).getItemsInRoom().size() != 0)
			{
				for (int i = 0; i < (*iter).getItemsInRoom().size(); i++)
				{
					cout << (*iter).getItemsInRoom().at(i).getName() << endl;
				}
			}
			else
			{
				cout << "No items are left in the room" << endl;
			}
			

			vector<string> sentence;
			while (sentence.size() == 0)
			{
				sentence = getUserInput(); //this will keep asking player for input if they dont type anything
			}

			parse(sentence, iter, currPlayer);
			
		}
		system("cls");
		cout << "You have finished ripping and tearing through the demons of hell." << endl;
		int totalDamage = 0;
		for (int i = 0; i < 5; i++)
		{
			totalDamage += trackDam.pop(); //pop the damage values one by one
		}
		cout << "You have dealt a total of " << totalDamage << " damage to the demons" << endl;
		system("pause");
		//player completes the game
	}
};

