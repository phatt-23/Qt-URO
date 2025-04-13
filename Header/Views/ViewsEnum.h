//
// Created by phatt on 4/8/25.
//

#ifndef VIEWSENUM_H
#define VIEWSENUM_H


enum class ViewsEnum : int {
    COMPOSE_VIEW,
    EMAIL_VIEW,
    CONTACTS_VIEW,
    LOGOUT,
    QUIT
};


inline QDebug operator<<(QDebug dbg, const ViewsEnum& view)
{
    switch (view)
    {
        case ViewsEnum::COMPOSE_VIEW:
            dbg.nospace() << "ViewsEnum::COMPOSE_VIEW"; break;
        case ViewsEnum::EMAIL_VIEW:
            dbg.nospace() << "ViewsEnum::EMAIL_VIEW"; break;
        case ViewsEnum::CONTACTS_VIEW:
            dbg.nospace() << "ViewsEnum::CONTACTS_VIEW"; break;
        case ViewsEnum::LOGOUT:
            dbg.nospace() << "ViewsEnum::LOGOUT"; break;
        case ViewsEnum::QUIT:
            dbg.nospace() << "ViewsEnum::QUIT"; break;
    }
    return dbg;
}


#endif //VIEWSENUM_H
