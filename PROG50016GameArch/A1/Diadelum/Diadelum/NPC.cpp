/*
Student: James Brooks
Class: Game Architecture

File: NPC.h

Class: NPC

Description: NPC version of a game object, can be talked too.
*/


#include "NPC.h"


NPC::NPC(int idNum, std::string n)
    : Interactable(idNum, n){

    talkText = "";
}

NPC::~NPC() {


}

std::string &NPC::talk() {

    return talkText;
}

void NPC::setTalkText(const char *txt) {

    talkText = txt;
}

void NPC::setTalkText(std::string &txt) {

    this->setTalkText(txt.c_str());
}