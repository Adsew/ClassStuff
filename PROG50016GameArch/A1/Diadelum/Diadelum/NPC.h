#ifndef NPC_H
#define NPC_H

/*
Student: James Brooks
Class: Game Architecture

File: NPC.h

Class: NPC

Description: NPC version of a game object, can be talked too.
*/


#include "Interactable.h"


class NPC : public Interactable {

private:

    std::string talkText;

public:

    NPC(int idNum, std::string n);
    
    virtual ~NPC();

    std::string &talk();

    void setTalkText(const char *txt);

    void setTalkText(std::string &txt);
};

#endif
