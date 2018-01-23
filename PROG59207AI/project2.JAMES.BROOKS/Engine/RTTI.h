#ifndef RTTI_H
#define RTTI_H

/*
Student: James Brooks
Class: Game Architecture

File: RTTI.h

Description: Macros for creating dynamic type definitions so components can be created
    with the use of strings
*/


// Generate dynamic component types

#define REGISTER_COMPONENT(_class_type_)                    \
                                                            \
    friend class ComponentManager;                          \
    friend class GameObject;                                \
                                                            \
protected:                                                  \
                                                            \
    _class_type_##(unsigned int uniqueID);                  \
                                                            \
    _class_type_##(unsigned int uniqueID, const char *type);\
                                                            \
    virtual ~##_class_type_##();                            \
                                                            \
public:                                                     \
                                                            \
    static Component *createComponent(unsigned int id) {    \
                                                            \
        return new _class_type_(id);                        \
    }                                                       \
                                                            \
    class __TypeRegister {                                  \
                                                            \
    public:                                                 \
                                                            \
        __TypeRegister() {                                  \
                                                            \
            ComponentManager::Instance().addComponentType(  \
                #_class_type_,                              \
                &##_class_type_##::createComponent          \
            );                                              \
        }                                                   \
    };



#define REGISTER_ABSTRACT_COMPONENT(_class_type_)           \
                                                            \
    friend class ComponentManager;                          \
    friend class GameObject;                                \
                                                            \
protected:                                                  \
                                                            \
    _class_type_##(unsigned int uniqueID, const char *type);\
                                                            \
    virtual ~##_class_type_##() = default;



#define IMPLEMENT_COMPONENT(_class_type_)                   \
                                                            \
static _class_type_##::__TypeRegister _class_type_##_tr;    \



// Generate dynamic asset types

#define REGISTER_ASSET(_class_type_)                        \
                                                            \
public:                                                     \
                                                            \
    friend class AssetManager;                              \
                                                            \
    static Asset *createAsset(unsigned int id) {            \
                                                            \
        return new _class_type_(id);                        \
    }                                                       \
                                                            \
    class __TypeRegister {                                  \
                                                            \
    public:                                                 \
                                                            \
        __TypeRegister() {                                  \
                                                            \
            AssetManager::Instance().addAssetType(          \
                #_class_type_,                              \
                &##_class_type_##::createAsset              \
            );                                              \
        }                                                   \
    };


#define IMPLEMENT_ASSET(_class_type_) static _class_type_##::__TypeRegister _class_type_##_tr;


#endif // !RTTI