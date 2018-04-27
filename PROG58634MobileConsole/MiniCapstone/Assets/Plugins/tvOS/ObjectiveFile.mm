//
//  ObjectiveFile.mm
//  
//
//  Created by Xcode User on 2018-03-21.
//

#import <Foundation/Foundation.h>
//#include "ObjectiveFile.h"

extern "C"
{
    int _add(int x, int y)
    {
        // Just a simple example of returning an int value
        return x + y;
    }
}
